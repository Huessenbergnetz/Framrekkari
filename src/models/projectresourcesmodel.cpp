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

#include "projectresourcesmodel.h"
#include "projectresourceobject.h"

const int ProjectResourcesModel::SlugRole = Qt::UserRole + 1;
const int ProjectResourcesModel::TranslatedRole = Qt::UserRole + 2;
const int ProjectResourcesModel::UntranslatedRole = Qt::UserRole + 3;
const int ProjectResourcesModel::ReviewedRole = Qt::UserRole + 4;
const int ProjectResourcesModel::LastUpdateRole = Qt::UserRole + 5;
const int ProjectResourcesModel::LastCommiterRole = Qt::UserRole + 6;

ProjectResourcesModel::ProjectResourcesModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    connect(&sAPI, SIGNAL(gotLangResourcesStats(QVariantList)), this, SLOT(populate(QVariantList)));
    connect(&sAPI, SIGNAL(gotLangResourcesStatsError(QString)), this, SLOT(errorHandler(QString)));
}


QHash<int, QByteArray> ProjectResourcesModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(SlugRole, QByteArray("slug"));
    roles.insert(TranslatedRole, QByteArray("translated"));
    roles.insert(UntranslatedRole, QByteArray("untranslated"));
    roles.insert(ReviewedRole, QByteArray("reviewed"));
    roles.insert(LastUpdateRole, QByteArray("lastUpdate"));
    roles.insert(LastCommiterRole, QByteArray("lastCommiter"));
    return roles;
}


int ProjectResourcesModel::rowCount(const QModelIndex &) const
{
    return m_resources.size();
}

int ProjectResourcesModel::columnCount(const QModelIndex&) const
{
    return 6;
}


QVariant ProjectResourcesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant(); // Return Null variant if index is invalid

    if (index.row() > (m_resources.size()-1) )
        return QVariant();

    ProjectResourceObject *robj = m_resources.at(index.row());
    switch (role) {
    case Qt::DisplayRole: // The default display role now displays the first name as well
    case SlugRole:
        return QVariant::fromValue(robj->slug);
    case TranslatedRole:
        return QVariant::fromValue(robj->translated);
    case UntranslatedRole:
        return QVariant::fromValue(robj->untranslated);
    case ReviewedRole:
        return QVariant::fromValue(robj->reviewed);
    case LastUpdateRole:
        return QVariant::fromValue(robj->lastUpdate);
    case LastCommiterRole:
        return QVariant::fromValue(robj->lastCommiter);
    default:
        return QVariant();
    }
}


void ProjectResourcesModel::refresh(const QString &projectSlug, const QString &lang, const QVariantList &resources, int accountIdx)
{
    clear();

    sAPI.getLangResourcesStats(projectSlug, lang, resources, accountIdx);
}


QModelIndex ProjectResourcesModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
             return QModelIndex();

    return createIndex(row, column);
}


void ProjectResourcesModel::populate(const QVariantList &data)
{
    int length = data.count();

    beginInsertRows(QModelIndex(), 0, length-1);

    for (int i = 0; i < length; ++i)
    {
        QVariantMap map = data.at(i).toMap();

        ProjectResourceObject *robj = new ProjectResourceObject(
                    map["resourceSlug"].toString(),
                    map["translated_entities"].toDouble(),
                    map["untranslated_entities"].toDouble(),
                    map["reviewed"].toDouble(),
                    QDateTime::fromString(map["last_update"].toString(), "yyyy-MM-dd hh:mm:ss"),
                    map["last_commiter"].toString()
                );

        m_resources.append(robj);
    }

    endInsertRows();
}


void ProjectResourcesModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount()-1);

    m_resources.clear();

    endRemoveRows();
}


void ProjectResourcesModel::errorHandler(const QString &errorString)
{
    emit gotError(errorString);
}
