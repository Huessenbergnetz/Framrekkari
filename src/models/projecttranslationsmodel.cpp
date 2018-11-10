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
#include <QDebug>

const int ProjectTranslationsModel::KeyRole = Qt::UserRole + 1;
const int ProjectTranslationsModel::ContextRole = Qt::UserRole + 2;
const int ProjectTranslationsModel::CommentRole = Qt::UserRole + 3;
const int ProjectTranslationsModel::SourceRole = Qt::UserRole + 4;
const int ProjectTranslationsModel::TranslationRole = Qt::UserRole + 5;
const int ProjectTranslationsModel::ReviewedRole = Qt::UserRole + 6;
const int ProjectTranslationsModel::PluralizedRole = Qt::UserRole + 7;
const int ProjectTranslationsModel::LastUpdateRole = Qt::UserRole + 8;
const int ProjectTranslationsModel::UserRole = Qt::UserRole + 9;
const int ProjectTranslationsModel::OccurrencesRole = Qt::UserRole + 10;
const int ProjectTranslationsModel::CharacterLimitRole = Qt::UserRole + 11;
const int ProjectTranslationsModel::TagsRole = Qt::UserRole + 12;
const int ProjectTranslationsModel::DataIndexRole = Qt::UserRole + 13;

ProjectTranslationsModel::ProjectTranslationsModel(QObject *parent) :
    QAbstractListModel(parent)
{
    m_searchTarget = 0;
    connect(&tAPI, &TranslationStringsAPI::gotStrings, this, &ProjectTranslationsModel::setModelData);
    connect(this, &ProjectTranslationsModel::modelDataChanged, this, &ProjectTranslationsModel::populate);
    connect(this, &ProjectTranslationsModel::searchChanged, this, &ProjectTranslationsModel::populate);
    connect(this, &ProjectTranslationsModel::searchTargetChanged, this, &ProjectTranslationsModel::populate);
    connect(&tAPI, &TranslationStringsAPI::gotStringsError, this, &ProjectTranslationsModel::errorHandler);
    connect(&tAPI, &TranslationStringsAPI::savedStringError, this, &ProjectTranslationsModel::errorHandler);
    connect(&tAPI, &TranslationStringsAPI::savedString, this, &ProjectTranslationsModel::savedString);
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
    roles.insert(LastUpdateRole, QByteArray("lastUpdate"));
    roles.insert(UserRole, QByteArray("user"));
    roles.insert(OccurrencesRole, QByteArray("occurrences"));
    roles.insert(CharacterLimitRole, QByteArray("characterLimit"));
    roles.insert(TagsRole, QByteArray("tags"));
    roles.insert(DataIndexRole, QByteArray("dataIndex"));
    return roles;
}


int ProjectTranslationsModel::rowCount(const QModelIndex &) const
{
    return m_translations.size();
}


QVariantMap ProjectTranslationsModel::get(int modelIdx)
{
    if (modelIdx > m_translations.size()-1)
        return QVariantMap();

    TranslationsObject *tobj = m_translations.at(modelIdx);
    QVariantMap result;

    result[QStringLiteral("key")] = tobj->key;
    result[QStringLiteral("context")] = tobj->context;
    result[QStringLiteral("comment")] = tobj->comment;
    result[QStringLiteral("source")] = tobj->source;
    result[QStringLiteral("translation")] = tobj->translation;
    result[QStringLiteral("reviewed")] = tobj->reviewed;
    result[QStringLiteral("pluralized")] = tobj->pluralized;
    result[QStringLiteral("last_update")] = tobj->lastUpdate.toLocalTime().toString(Qt::DefaultLocaleLongDate);
    result[QStringLiteral("user")] = tobj->user;
    result[QStringLiteral("occurences")] = tobj->occurrences;
    result[QStringLiteral("character_limit")] = tobj->characterLimit;
    result[QStringLiteral("tags")] = tobj->tags;
    result[QStringLiteral("dataIndex")] = tobj->dataIndex;

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
    case LastUpdateRole:
        return QVariant::fromValue(tobj->lastUpdate.toLocalTime().toString(Qt::DefaultLocaleLongDate));
    case UserRole:
        return QVariant::fromValue(tobj->user);
    case OccurrencesRole:
        return QVariant::fromValue(tobj->occurrences);
    case CharacterLimitRole:
        return QVariant::fromValue(tobj->characterLimit);
    case TagsRole:
        return QVariant::fromValue(tobj->tags);
    case DataIndexRole:
        return QVariant::fromValue(tobj->dataIndex);
    default:
        return QVariant();
    }
}



void ProjectTranslationsModel::refresh(const QString &project, const QString &resource, const QString &lang, int filter, int accountIdx)
{
    clear();
    setModelData(QVariantList());

    tAPI.getStrings(project, resource, lang, filter, accountIdx);
}



QModelIndex ProjectTranslationsModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
             return QModelIndex();

    return createIndex(row, column);
}


void ProjectTranslationsModel::populate()
{
    clear();

    if (!search().isEmpty()) {

        for (int i = 0; i < m_modelData.length(); ++i)
        {
            switch (searchTarget())
            {
            case 1:
                if (m_modelData.at(i).toMap().value(QStringLiteral("translation")).toMap().value(QStringLiteral("1")).toString().contains(search(), Qt::CaseInsensitive))
                    m_filteredModelData << m_modelData.at(i).toMap();
                break;
            case 0:
            default:
                if (m_modelData.at(i).toMap().value(QStringLiteral("source_string")).toMap().value(QStringLiteral("1")).toString().contains(search(), Qt::CaseInsensitive))
                    m_filteredModelData << m_modelData.at(i).toMap();
                break;
            }
        }

    } else {
        m_filteredModelData = m_modelData;
    }

    int length = m_filteredModelData.length();

    beginInsertRows(QModelIndex(), 0, length-1);

    for (int i = 0; i < m_filteredModelData.length(); ++i)
    {
        QVariantMap map = m_filteredModelData.at(i).toMap();

        TranslationsObject *tobj = new TranslationsObject(
                                        map[QStringLiteral("key")].toString(),
                                        map[QStringLiteral("context")].toList(),
                                        map[QStringLiteral("comment")].toString(),
                                        map[QStringLiteral("source_string")].toMap(),
                                        map[QStringLiteral("translation")].toMap(),
                                        map[QStringLiteral("reviewed")].toBool(),
                                        map[QStringLiteral("pluralized")].toBool(),
                                        QDateTime::fromString(map[QStringLiteral("last_update")].toString(), QStringLiteral("yyyy-MM-ddThh:mm:ss.zzz")),
                                        map[QStringLiteral("user")].toString(),
                                        map[QStringLiteral("occurrences")].toString(),
                                        map[QStringLiteral("character_limit")].toInt(),
                                        map[QStringLiteral("tags")].toList(),
                                        map[QStringLiteral("dataIndex")].toInt());

        m_translations.append(tobj);
    }

    endInsertRows();

    emit gotStrings();
}


void ProjectTranslationsModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount()-1);

    m_translations.clear();
    m_filteredModelData.clear();

    endRemoveRows();
}


void ProjectTranslationsModel::errorHandler(const QString &errorString)
{
    emit gotError(errorString);
}


void ProjectTranslationsModel::saveString(const QString &project, const QString &resource, const QString &lang, const QVariantMap &translation, const QString &hash, bool reviewed, int modelIdx, int dataIndex, int accountIdx)
{
    tAPI.saveString(project, resource, lang, translation, hash, reviewed, modelIdx, dataIndex, accountIdx);
}


void ProjectTranslationsModel::savedString(const QVariantMap &data)
{
    QVariantMap changed;

    int idx = data[QStringLiteral("modelIdx")].toInt();
    int dataIdx = data[QStringLiteral("dataIndex")].toInt();

    TranslationsObject *tobj = m_translations.at(idx);
    QVariantMap modelObject = m_modelData.at(dataIdx).toMap();

    QVariant trData = data[QStringLiteral("translation")];

    changed[QStringLiteral("newTrans")] = tobj->translation.value(QStringLiteral("1")).toString().isEmpty();


    if (trData.type() == QVariant::Map) {
        tobj->translation = trData.toMap();
        modelObject[QStringLiteral("translation")] = trData.toMap();
    } else {
        QVariantMap strMap;
        strMap[QStringLiteral("1")] = trData.toString();
        tobj->translation = strMap;
        modelObject[QStringLiteral("translation")] = strMap;
    }


    int revCount = 0;
    bool rev = data[QStringLiteral("reviewed")].toBool();
    if (!tobj->reviewed && rev) {
        revCount = 1;
    } else if (tobj->reviewed && !rev) {
        revCount = -1;
    }

    tobj->reviewed = rev;
    modelObject[QStringLiteral("reviewed")] = rev;

    m_modelData.replace(dataIdx, modelObject);


    changed[QStringLiteral("revCount")] = revCount;
    changed[QStringLiteral("modelIdx")] = idx;

    emit dataChanged(index(idx, 0), index(idx));
    emit savedStringSuccess(changed);
}


QString ProjectTranslationsModel::search() const
{
    return m_search;
}


void ProjectTranslationsModel::setSearch(const QString &nSearch)
{
    if (nSearch != m_search) {
        m_search = nSearch;
        emit searchChanged(search());
    }
}


QVariantList ProjectTranslationsModel::modelData() const
{
    return m_modelData;
}

void ProjectTranslationsModel::setModelData(const QVariantList &nModelData)
{
    if (nModelData != m_modelData) {
        m_modelData = nModelData;
        emit modelDataChanged(modelData());
    }
}


int ProjectTranslationsModel::searchTarget() const
{
    return m_searchTarget;
}


void ProjectTranslationsModel::setSearchTarget(int nSearchTarget)
{
    if (nSearchTarget != m_searchTarget) {
        m_searchTarget = nSearchTarget;
        emit searchTargetChanged(searchTarget());
    }
}
