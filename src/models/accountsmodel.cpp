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

#include <QDebug>
#include "accountsmodel.h"
#include "accountobject.h"

const int AccountsModel::NameRole = Qt::UserRole + 1;
const int AccountsModel::ServerRole = Qt::UserRole + 2;
const int AccountsModel::UserRole = Qt::UserRole + 3;
const int AccountsModel::PasswordRole = Qt::UserRole + 4;
const int AccountsModel::IgnoreSSLErrorsRole = Qt::UserRole + 5;
const int AccountsModel::TypeRole = Qt::UserRole + 6;

AccountsModel::AccountsModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    init();
}

QHash<int, QByteArray> AccountsModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(NameRole, QByteArray("name"));
    roles.insert(ServerRole, QByteArray("server"));
    roles.insert(UserRole, QByteArray("user"));
    roles.insert(PasswordRole, QByteArray("password"));
    roles.insert(IgnoreSSLErrorsRole, QByteArray("ignoreSSLErrors"));
    roles.insert(TypeRole, QByteArray("type"));
    return roles;
}

int AccountsModel::rowCount(const QModelIndex &) const
{
    return m_accounts.size();
}

int AccountsModel::columnCount(const QModelIndex&) const
{
    return 6;
}


QVariant AccountsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant(); // Return Null variant if index is invalid

    if (index.row() > (m_accounts.size()-1) )
        return QVariant();

    AccountObject *aobj = m_accounts.at(index.row());
    switch (role) {
    case Qt::DisplayRole: // The default display role now displays the first name as well
    case NameRole:
        return QVariant::fromValue(aobj->name);
    case ServerRole:
        return QVariant::fromValue(aobj->server);
    case UserRole:
        return QVariant::fromValue(aobj->user);
    case PasswordRole:
        return QVariant::fromValue(aobj->password);
    case IgnoreSSLErrorsRole:
        return QVariant::fromValue(aobj->ignoreSSLErrors);
    case TypeRole:
        return QVariant::fromValue(aobj->type);
    default:
        return QVariant();
    }
}


void AccountsModel::init()
{
    QList<Configuration::Account> accounts = config.loadAccounts();

    for (int i = 0; i < accounts.length(); ++i)
    {
        AccountObject *acc = new AccountObject(accounts.at(i).name, accounts.at(i).server, accounts.at(i).user, accounts.at(i).password, accounts.at(i).ignoreSSLErrors, accounts.at(i).type);
        m_accounts.append(acc);
    }
}


void AccountsModel::append(const QString &name, const QString &server, const QString &user, const QString &password, bool ignoreSSLErrors, int type)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    config.saveAccount(name, server, user, password, ignoreSSLErrors, type);
    AccountObject *acc = new AccountObject(name,server, user, password, ignoreSSLErrors, type);
    m_accounts.append(acc);

    endInsertRows();
}


void AccountsModel::remove(int idx)
{
    beginRemoveRows(QModelIndex(), idx, idx);

    config.removeAccount(idx);
    m_accounts.removeAt(idx);

    endRemoveRows();
}


void AccountsModel::edit(const QString &name, const QString &server, const QString &user, const QString &password, bool ignoreSSLErrors, int type, int idx)
{
    config.editAccount(name, server, user, password, ignoreSSLErrors, type, idx);
    AccountObject *acc = m_accounts.at(idx);

    acc->name = name;
    acc->server = server;
    acc->user = user;
    acc->password = password;
    acc->ignoreSSLErrors = ignoreSSLErrors;
    acc->type = type;

    m_accounts[idx] = acc;

    emit dataChanged(index(idx, 0), index(idx, columnCount()-1));
}


bool AccountsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;


    if (index.row() > (m_accounts.size()-1))
        return false;

    switch(role) {
    case NameRole:
        m_accounts.at(index.row())->name = value.toString();
        return true;
    case ServerRole:
        m_accounts.at(index.row())->server = value.toString();
        return true;
    case UserRole:
        m_accounts.at(index.row())->user = value.toString();
        return true;
    case PasswordRole:
        m_accounts.at(index.row())->password = value.toString();
        return true;
    case IgnoreSSLErrorsRole:
        m_accounts.at(index.row())->ignoreSSLErrors = value.toBool();
        return true;
    default:
        return false;
    }

    emit dataChanged(index, index);

}


QModelIndex AccountsModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
             return QModelIndex();

    return createIndex(row, column);
}


Qt::ItemFlags AccountsModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    flags |= (Qt::ItemIsEditable
            |Qt::ItemIsSelectable
            |Qt::ItemIsEnabled);
   return flags;

}
