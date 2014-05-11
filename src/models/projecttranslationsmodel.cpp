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

#include "projecttranslationsmodel.h"
#include "translationsobject.h"

const int ProjectTranslationsModel::KeyRole = Qt::UserRole + 1;
const int ProjectTranslationsModel::ContextRole = Qt::UserRole + 2;
const int ProjectTranslationsModel::CommentRole = Qt::UserRole + 3;
const int ProjectTranslationsModel::SourceRole = Qt::UserRole + 4;
const int ProjectTranslationsModel::TranslationRole = Qt::UserRole + 5;
const int ProjectTranslationsModel::ReviewedRole = Qt::UserRole + 6;
const int ProjectTranslationsModel::PluralizedRole = Qt::UserRole + 7;

ProjectTranslationsModel::ProjectTranslationsModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    connect(&tAPI, SIGNAL(gotStrings(QVariantList)), this, SLOT(populate(QVariantList)));
    connect(&tAPI, SIGNAL(gotStringsError(QString)), this, SLOT(errorHandler(QString)));
    connect(&tAPI, SIGNAL(savedStringError(QString)), this, SLOT(errorHandler(QString)));
    connect(&tAPI, SIGNAL(savedString(QVariantMap)), this, SLOT(savedString(QVariantMap)));
}


QHash<int, QByteArray> ProjectTranslationsModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(KeyRole, QByteArray("key"));
    roles.insert(ContextRole, QByteArray("context"));
    roles.insert(CommentRole, QByteArray("comment"));
    roles.insert(SourceRole, QByteArray("source"));
    roles.insert(TranslationRole, QByteArray("translation"));
    roles.insert(ReviewedRole, QByteArray("reviewed"));
    roles.insert(PluralizedRole, QByteArray("pluralized"));
    return roles;
}


int ProjectTranslationsModel::rowCount(const QModelIndex &) const
{
    return m_translations.size();
}

int ProjectTranslationsModel::columnCount(const QModelIndex&) const
{
    return 7;
}

QVariantMap ProjectTranslationsModel::get(int modelIdx)
{
    if (modelIdx > m_translations.size()-1)
        return QVariantMap();

    TranslationsObject *tobj = m_translations.at(modelIdx);
    QVariantMap result;

    result["key"] = tobj->key;
    result["context"] = tobj->context;
    result["comment"] = tobj->comment;
    result["source"] = tobj->source;
    result["translation"] = tobj->translation;
    result["reviewed"] = tobj->reviewed;
    result["pluralized"] = tobj->pluralized;

    return result;
}


QVariant ProjectTranslationsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant(); // Return Null variant if index is invalid

    if (index.row() > (m_translations.size()-1) )
        return QVariant();

    TranslationsObject *tobj = m_translations.at(index.row());
    switch (role) {
    case Qt::DisplayRole: // The default display role now displays the first name as well
    case KeyRole:
        return QVariant::fromValue(tobj->key);
    case ContextRole:
        return QVariant::fromValue(tobj->context);
    case CommentRole:
        return QVariant::fromValue(tobj->comment);
    case SourceRole:
        return QVariant::fromValue(tobj->source);
    case TranslationRole:
        return QVariant::fromValue(tobj->translation);
    case ReviewedRole:
        return QVariant::fromValue(tobj->reviewed);
    case PluralizedRole:
        return QVariant::fromValue(tobj->pluralized);
    default:
        return QVariant();
    }
}



void ProjectTranslationsModel::refresh(const QString &project, const QString &resource, const QString &lang, int filter, int accountIdx)
{
    clear();

    tAPI.getStrings(project, resource, lang, filter, accountIdx);
}



QModelIndex ProjectTranslationsModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
             return QModelIndex();

    return createIndex(row, column);
}


void ProjectTranslationsModel::populate(const QVariantList &data)
{
    int length = data.length();

    beginInsertRows(QModelIndex(), 0, length-1);

    for (int i = 0; i < data.length(); ++i)
    {
        QVariantMap map = data.at(i).toMap();

        TranslationsObject *tobj = new TranslationsObject(map["key"].toString(), map["context"].toList(), map["comment"].toString(), map["source_string"].toMap(), map["translation"].toMap(), map["reviewed"].toBool(), map["pluralized"].toBool());
        m_translations.append(tobj);
    }

    endInsertRows();
}


void ProjectTranslationsModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount()-1);

    m_translations.clear();

    endRemoveRows();
}


void ProjectTranslationsModel::errorHandler(const QString &errorString)
{
    emit gotError(errorString);
}


void ProjectTranslationsModel::saveString(const QString &project, const QString &resource, const QString &lang, const QVariantMap &translation, const QString &hash, int modelIdx, int accountIdx)
{
    tAPI.saveString(project, resource, lang, translation, hash, modelIdx, accountIdx);
}


void ProjectTranslationsModel::savedString(const QVariantMap &data)
{
    int idx = data["modelIdx"].toInt();


    TranslationsObject *tobj = m_translations.at(idx);

    QVariant trData = data["translation"];

    if (trData.type() == QVariant::Map) {
        tobj->translation = trData.toMap();
    } else {
        QVariantMap strMap;
        strMap["1"] = trData.toString();
        tobj->translation = strMap;
    }


    emit dataChanged(index(idx, 0), index(idx, columnCount()-1));
    emit savedStringSuccess();
}
