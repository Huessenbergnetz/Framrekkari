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

#include "projectsmodel.h"
#include "projectobject.h"

const int ProjectsModel::SlugRole = Qt::UserRole + 1;
const int ProjectsModel::NameRole = Qt::UserRole + 2;
const int ProjectsModel::DescriptionRole = Qt::UserRole + 3;
const int ProjectsModel::SourceLanguageCodedRole = Qt::UserRole + 4;

ProjectsModel::ProjectsModel(QObject *parent) :
    QAbstractListModel(parent)
{
    connect(&pAPI, &ProjectsAPI::gotProjects, this, &ProjectsModel::populate);
    connect(&pAPI, &ProjectsAPI::gotProjectsError, this, &ProjectsModel::errorHandler);
}

QHash<int, QByteArray> ProjectsModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(SlugRole, QByteArray("slug"));
    roles.insert(NameRole, QByteArray("name"));
    roles.insert(DescriptionRole, QByteArray("description"));
    roles.insert(SourceLanguageCodedRole, QByteArray("sourceLanguageCode"));
    return roles;
}


int ProjectsModel::rowCount(const QModelIndex &) const
{
    return m_projects.size();
}

//int ProjectsModel::columnCount(const QModelIndex&) const
//{
//    return 4;
//}


QVariant ProjectsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant(); // Return Null variant if index is invalid

    if (index.row() > (m_projects.size()-1) )
        return QVariant();

    ProjectObject *pobj = m_projects.at(index.row());
    switch (role) {
    case Qt::DisplayRole: // The default display role now displays the first name as well
    case SlugRole:
        return QVariant::fromValue(pobj->slug);
    case NameRole:
        return QVariant::fromValue(pobj->name);
    case DescriptionRole:
        return QVariant::fromValue(pobj->description);
    case SourceLanguageCodedRole:
        return QVariant::fromValue(pobj->sourceLanguageCode);
    default:
        return QVariant();
    }
}


void ProjectsModel::refresh(int accountIdx, int start, int end)
{
    clear();

    pAPI.getProjects(accountIdx, start, end);
}


QModelIndex ProjectsModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
             return QModelIndex();

    return createIndex(row, column);
}


void ProjectsModel::populate(const QVariantList &data)
{
    int length = data.length();

    beginInsertRows(QModelIndex(), 0, length-1);

    for (int i = 0; i < data.length(); ++i)
    {
        QVariantMap map = data.at(i).toMap();
        ProjectObject *pobj = new ProjectObject(map[QStringLiteral("slug")].toString(), map[QStringLiteral("name")].toString(), map[QStringLiteral("description")].toString(), map[QStringLiteral("source_language_code")].toString());
        m_projects.append(pobj);
    }

    endInsertRows();

    emit gotData(length);
}


void ProjectsModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount()-1);

    m_projects.clear();

    endRemoveRows();
}


void ProjectsModel::errorHandler(const QString &errorString)
{
    emit gotError(errorString);
}
