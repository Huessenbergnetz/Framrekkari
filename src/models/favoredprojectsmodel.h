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

#ifndef FAVOREDPROJECTSMODEL_H
#define FAVOREDPROJECTSMODEL_H

#include <QAbstractListModel>

#include "../configuration.h"

class FavoredProjectObject;

class FavoredProjectsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit FavoredProjectsModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;
    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const;

    Q_INVOKABLE bool isFavored(const QString &slug, int accountIdx);

signals:

public slots:
    void append(const QString &name, const QString &slug, const QString &desc, const QString &srcLang, int accountIdx);
    void remove(const QString &slug, int accountIdx);
    void init(int accountIdx);

private:
    QList<FavoredProjectObject*> m_projects;
    static const int NameRole;
    static const int SlugRole;
    static const int DescRole;
    static const int SrcLangRole;
    static const int AccountIdxRole;

    Configuration config;

    void clear();

};

#endif // FAVOREDPROJECTSMODEL_H
