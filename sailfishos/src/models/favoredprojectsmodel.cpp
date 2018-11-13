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

#include "favoredprojectsmodel.h"
#include "favoredprojectobject.h"

const int FavoredProjectsModel::NameRole = Qt::UserRole + 1;
const int FavoredProjectsModel::SlugRole = Qt::UserRole + 2;
const int FavoredProjectsModel::DescRole = Qt::UserRole + 3;
const int FavoredProjectsModel::SrcLangRole = Qt::UserRole + 4;
const int FavoredProjectsModel::AccountIdxRole = Qt::UserRole + 5;

FavoredProjectsModel::FavoredProjectsModel(QObject *parent) :
    QAbstractListModel(parent)
{
}


QHash<int, QByteArray> FavoredProjectsModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(NameRole, QByteArray("name"));
    roles.insert(SlugRole, QByteArray("slug"));
    roles.insert(DescRole, QByteArray("description"));
    roles.insert(SrcLangRole, QByteArray("sourceLanguageCode"));
    roles.insert(AccountIdxRole, QByteArray("accountIdx"));
    return roles;
}


int FavoredProjectsModel::rowCount(const QModelIndex &) const
{
    return m_projects.size();
}


QVariant FavoredProjectsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant(); // Return Null variant if index is invalid

    if (index.row() > (m_projects.size()-1) )
        return QVariant();

    FavoredProjectObject *fpobj = m_projects.at(index.row());
    switch (role) {
    case NameRole:
        return QVariant::fromValue(fpobj->name);
    case SlugRole:
        return QVariant::fromValue(fpobj->slug);
    case DescRole:
        return QVariant::fromValue(fpobj->desc);
    case SrcLangRole:
        return QVariant::fromValue(fpobj->srcLang);
    case AccountIdxRole:
        return QVariant::fromValue(fpobj->accountIdx);
    default:
        return QVariant();
    }
}


void FavoredProjectsModel::init(int accountIdx)
{
    clear();

    QList<Configuration::Project> projects = config.loadFavoredProjects(accountIdx);
    int length = projects.length();

    beginInsertRows(QModelIndex(), 0, length-1);

    for (int i = 0; i < length; ++i)
    {
        FavoredProjectObject *prj = new FavoredProjectObject(projects.at(i).name, projects.at(i).slug, projects.at(i).description, projects.at(i).srcLang, projects.at(i).accountIdx);
        m_projects.append(prj);
    }

    endInsertRows();
}



void FavoredProjectsModel::append(const QString &name, const QString &slug, const QString &desc, const QString &srcLang, int accountIdx)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    config.favorProject(name, slug, desc, srcLang, accountIdx);

    FavoredProjectObject *prj = new FavoredProjectObject(name ,slug, desc, srcLang, accountIdx);
    m_projects.append(prj);

    endInsertRows();
}


void FavoredProjectsModel::remove(const QString &slug, int accountIdx)
{
    int modelIdx = 0, i = 0;
    int configIdx = 0, j = 0;
    bool modelFound = false;
    bool configFound = false;

    QList<Configuration::Project> projects = config.loadFavoredProjects(accountIdx);

    while (!modelFound && i < rowCount())
    {
        if (m_projects.at(i)->slug == slug) {
            modelIdx = i;
            modelFound = true;
        }
        ++i;
    }

    while (!configFound && j < projects.length())
    {
        if (projects.at(j).slug == slug) {
            configIdx = j;
            configFound = true;
        }
        ++j;
    }

    beginRemoveRows(QModelIndex(), modelIdx, modelIdx);

    config.unfavorProject(configIdx, accountIdx);
    m_projects.removeAt(modelIdx);

    endRemoveRows();
}


void FavoredProjectsModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount()-1);

    m_projects.clear();

    endRemoveRows();
}


QModelIndex FavoredProjectsModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
             return QModelIndex();

    return createIndex(row, column);
}


bool FavoredProjectsModel::isFavored(const QString &slug, int accountIdx)
{
    bool favored = false;
    int i = 0;

    QList<Configuration::Project> projects = config.loadFavoredProjects(accountIdx);

    while (!favored && i < projects.length())
    {
        if (projects.at(i).slug == slug)
            favored = true;
        ++i;
    }

    return favored;
}
