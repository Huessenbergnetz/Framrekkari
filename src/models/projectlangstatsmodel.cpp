/*
    Framrekkari - Transifex Client for SailfishOS
    Copyright (C) 2014  Buschtrommel/Matthias Fehring
    Contact: Matthias Fehring <kontakt@buschmann23.de>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "projectlangstatsmodel.h"
#include "langstatobject.h"

const int ProjectLangstatsModel::LangRole = Qt::UserRole + 1;
const int ProjectLangstatsModel::TranslatedRole = Qt::UserRole + 2;
const int ProjectLangstatsModel::UntranslatedRole = Qt::UserRole + 3;
const int ProjectLangstatsModel::ReviewedRole = Qt::UserRole + 4;

ProjectLangstatsModel::ProjectLangstatsModel(QObject *parent) :
    QAbstractListModel(parent)
{
    connect(&sAPI, SIGNAL(gotAllProjectLangStats(QVariantMap)), this, SLOT(populate(QVariantMap)));
    connect(&sAPI, SIGNAL(gotAllProjectLangStatsError(QString)), this, SLOT(errorHandler(QString)));
}

QHash<int, QByteArray> ProjectLangstatsModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(LangRole, QByteArray("lang"));
    roles.insert(TranslatedRole, QByteArray("translated"));
    roles.insert(UntranslatedRole, QByteArray("untranslated"));
    roles.insert(ReviewedRole, QByteArray("reviewed"));
    return roles;
}


int ProjectLangstatsModel::rowCount(const QModelIndex &) const
{
    return m_stats.size();
}


QVariant ProjectLangstatsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant(); // Return Null variant if index is invalid

    if (index.row() > (m_stats.size()-1) )
        return QVariant();

    LangstatObject *sobj = m_stats.at(index.row());
    switch (role) {
    case Qt::DisplayRole: // The default display role now displays the first name as well
    case LangRole:
        return QVariant::fromValue(sobj->lang);
    case TranslatedRole:
        return QVariant::fromValue(sobj->translated);
    case UntranslatedRole:
        return QVariant::fromValue(sobj->untranslated);
    case ReviewedRole:
        return QVariant::fromValue(sobj->reviewed);
    default:
        return QVariant();
    }
}


void ProjectLangstatsModel::refresh(const QString &projectSlug, const QVariantList &resources, int accountIdx)
{
    clear();

    sAPI.getAllProjectLangStats(projectSlug, resources, accountIdx);
}


QModelIndex ProjectLangstatsModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
             return QModelIndex();

    return createIndex(row, column);
}


void ProjectLangstatsModel::populate(const QVariantMap &data)
{
    int length = data.count();

    beginInsertRows(QModelIndex(), 0, length-1);

    QMapIterator<QString, QVariant> i(data);
    while (i.hasNext())
    {
        i.next();

        QVariantMap map = i.value().toMap();

        LangstatObject *sobj = new LangstatObject(i.key(), map.value("translated").toDouble(), map.value("untranslated").toDouble(), map.value("reviewed").toDouble());

        m_stats.append(sobj);
    }

    endInsertRows();

    emit gotData();
}


void ProjectLangstatsModel::updateTranslationCount(const int &idx, const QVariantMap &changed)
{
    LangstatObject *sobj = m_stats.at(idx);

    if (changed["newTrans"].toBool()) {
        sobj->translated = sobj->translated + 1;
        sobj->untranslated = sobj->untranslated -1;
    }

    sobj->reviewed = sobj->reviewed + changed["revCount"].toInt();

    QVariantMap changedStats;
    changedStats["translated"] = sobj->translated;
    changedStats["untranslated"] = sobj->untranslated;
    changedStats["reviewed"] = sobj->reviewed;

    m_stats[idx] = sobj;

    emit dataChanged(index(idx, 0), index(idx));
    emit langStatsChanged(changedStats);
}


void ProjectLangstatsModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount()-1);

    m_stats.clear();

    endRemoveRows();
}


void ProjectLangstatsModel::errorHandler(const QString &errorString)
{
    emit gotError(errorString);
}
