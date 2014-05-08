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

#ifndef ACCOUNTSMODEL_H
#define ACCOUNTSMODEL_H

#include <QAbstractTableModel>

#include "../configuration.h"

class AccountObject;

class AccountsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit AccountsModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex& = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

signals:

public slots:
    void append(const QString &name, const QString &server, const QString &user, const QString &password, bool ignoreSSLErrors, int type);
    void remove(int idx);
    void edit(const QString &name, const QString &server, const QString &user, const QString &password, bool ignoreSSLErrors, int type, int idx);

private:
    QList<AccountObject*> m_accounts;
    static const int NameRole;
    static const int ServerRole;
    static const int UserRole;
    static const int PasswordRole;
    static const int IgnoreSSLErrorsRole;
    static const int TypeRole;

    void init();

//    bool setData(QModelIndex &index, QVariant &value, int role);

    Configuration config;

};

#endif // ACCOUNTSMODEL_H
