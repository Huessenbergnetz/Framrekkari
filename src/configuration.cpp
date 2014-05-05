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

#include "configuration.h"

Configuration::Configuration(QObject *parent) :
    QSettings(parent)
{
}



/*!
 * \fn void Configuration::set(const QString &key, const QVariant &val)
 * \brief Sets a configuration from inside QML
 *
 * Reimplementation of QSettings::setValue() that is accessible from inside QML
 *
 * \param key Key to store into
 * \param val Value to store
 */
void Configuration::set(const QString &key, const QVariant &val)
{
    setValue(key, val);
}


/*!
 * \fn QVariant Configuration::get(const QString &key, const QVariant &def) const
 * \brief Gets a configuration from inside QML
 *
 * Reimplementation of QSettings::value() that is accessible from inside QML
 *
 * \param key Key to retrieve
 * \param def Default value if key is not set
 * \return QVariant with the stored data or the default value
 */
QVariant Configuration::get(const QString &key, const QVariant &def) const
{
    return value(key, def);
}


/*!
 * \fn bool Configuration::getBool(const QString &key, const QVariant &def) const
 * \brief Gets explicitely a boolean value from the configuration
 *
 * Reimplemenation of QSettings::value() that is accessible from inside QML,
 * that explicitely retrieves a boolen value instead of a QVariant
 *
 * \param key Key to retreive
 * \param def Default value if key is not set
 * \return bool value of the stored data or the default value
 */
bool Configuration::getBool(const QString &key, const QVariant &def) const
{
    return value(key, def).toBool();
}



/*!
 * \fn QList<Configuration::Account> Configuration::loadAccounts()
 * \brief Internal function to load accounts from config
 *
 * Loads the accounts from the configuration system into the internal structure.
 *
 * \return QList<Configuration::Account> List of account structs
 */
QList<Configuration::Account> Configuration::loadAccounts()
{
    QList<Account> accounts;
    int size = beginReadArray("accounts");
    for (int i = 0; i < size; ++i)
    {
        setArrayIndex(i);
        Account acc;
        acc.name = value("name").toString();
        acc.server = value("server").toString();
        acc.user = value("user").toString();
        acc.password = value("password").toString();
        acc.ignoreSSLErrors = value("ignoreSSLErrors").toBool();
        accounts.append(acc);
    }
    endArray();

    return accounts;
}



/*!
 * \fn void Configuration::writeAccounts(const QList<Account> &accounts)
 * \brief Internal function to write accounts to config
 *
 * Writes the accounts in the parameter accounts into the configuration system
 *
 * \param accounts QList<Account> list of accounts to write to configuration system
 */
void Configuration::writeAccounts(const QList<Account> &accounts)
{
    beginWriteArray("accounts");
    for (int i = 0; i < accounts.length(); ++i)
    {
        setArrayIndex(i);
        setValue("name", accounts.at(i).name);
        setValue("server", accounts.at(i).server);
        setValue("user", accounts.at(i).user);
        setValue("password", accounts.at(i).password);
        setValue("ignoreSSLErrors", accounts.at(i).ignoreSSLErrors);
    }
    endArray();

    emit savedAccout();
}



/*!
 * \fn void Configuration::saveAccount(const QString &server, const QString &user, const QString &password)
 * \brief Saves an account into the configuration system
 *
 * Saves a new account into the configuration system
 *
 * \param name QString display name
 * \param server QString name of the server
 * \param user QString username
 * \param password QString password
 */
void Configuration::saveAccount(const QString &name, const QString &server, const QString &user, const QString &password, bool ignoreSSLErrors)
{
    QList<Account> accounts = loadAccounts();

    Account acc;
    acc.name = name;
    acc.server = server;
    acc.user = user;
    acc.password = password;
    acc.ignoreSSLErrors = ignoreSSLErrors;

    accounts.append(acc);

    writeAccounts(accounts);
}


void Configuration::editAccount(const QString &name, const QString &server, const QString &user, const QString &password, bool ignoreSSLErrors, int idx)
{
    QList<Account> accounts = loadAccounts();

    Account acc = accounts.at(idx);
    acc.name = name;
    acc.server = server;
    acc.user = user;
    acc.password = password;
    acc.ignoreSSLErrors = ignoreSSLErrors;

    accounts.replace(idx, acc);

    writeAccounts(accounts);
}


/*!
 * \fn void Configuration::removeAccount(int idx)
 * \brief Removes account at index idx
 *
 * Removes an account identified by its index number
 *
 * \param idx int index of the account to remove
 */
void Configuration::removeAccount(int idx)
{
    QList<Account> accounts = loadAccounts();

    accounts.removeAt(idx);

    writeAccounts(accounts);
}


/*!
 * \fn QVariantMap Configuration::getAccount(int idx)
 * \brief Return account data in a QVariantMap
 *
 * Returns the data of the account identified by its index number as a QVariantMap
 *
 * \param idx int index number of the account
 * \return QVariantMap holds the account data
 */
QVariantMap Configuration::getAccount(int idx)
{
    QVariantMap account;
    QList<Account> accounts = loadAccounts();

    account["name"] = accounts.at(idx).name;
    account["server"] = accounts.at(idx).server;
    account["user"] = accounts.at(idx).user;
    account["password"] = accounts.at(idx).password;
    account["ignoreSSLErrors"] = accounts.at(idx).ignoreSSLErrors;

    return account;
}
