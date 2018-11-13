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
    m_defaultFilter = value(QStringLiteral("display/stringListFilter"), 0).toInt();
    m_sourceFontSize = value(QStringLiteral("display/sourceFontSize"), 24).toInt();
    m_translationFontSize = value(QStringLiteral("display/translationFontSize"), 32).toInt();
    m_language = value(QStringLiteral("display/language"), QStringLiteral("C")).toString();
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
 * \fn QList<Configuration::Project> Configuration::loadFavoredProjects(int accountIdx)
 * \brief Function to load favored projects
 *
 * Loads the favored projects fromo the configuration system into the internal structure.
 *
 * \param accountIdx int that specifies the account to use, if lower than zero all projects are retrieved
 * \return QList<Configuration::Project> List of project structs
 */
QList<Configuration::Project> Configuration::loadFavoredProjects(int accountIdx)
{
    QList<Project> projects;
    int size = beginReadArray("favoredProjectsAccount" + QString::number(accountIdx));
    for (int i = 0; i < size; ++i)
    {
        setArrayIndex(i);
        Project prj;
        prj.name = value(QStringLiteral("name")).toString();
        prj.slug = value(QStringLiteral("slug")).toString();
        prj.description = value(QStringLiteral("description")).toString();
        prj.srcLang = value(QStringLiteral("srcLang")).toString();
        prj.accountIdx = value(QStringLiteral("accountIdx")).toInt();
        projects.append(prj);
    }
    endArray();

    return projects;
}


/*!
 * \fn Configuration::writeFavoredProjects(const QList<Project> &projects)
 * \brief Internal function to write favored projects to config
 *
 * Writes the projects in the parameter accounts into the configuration system.
 *
 * \param projects QList<Project> list of projects to write to configuration system
 * \param accountIdx the account the project belongs to
 */
void Configuration::writeFavoredProjects(const QList<Project> &projects, int accountIdx)
{
    beginWriteArray("favoredProjectsAccount" + QString::number(accountIdx));
    for (int i = 0; i < projects.length(); ++i)
    {
        setArrayIndex(i);
        setValue(QStringLiteral("name"), projects.at(i).name);
        setValue(QStringLiteral("slug"), projects.at(i).slug);
        setValue(QStringLiteral("description"), projects.at(i).description);
        setValue(QStringLiteral("srcLang"), projects.at(i).srcLang);
        setValue(QStringLiteral("accountIdx"), projects.at(i).accountIdx);
    }
    endArray();

    emit savedFavoredProject();
}


/*!
 * \fn void Configuration::favorProject(const QString &name, const QString &slug, const QString &description, const QString &srcLang, int accountIdx)
 * \brief Saves a favored project to the configuration system
 *
 * Saves a new favored project into the configuration system
 *
 * \param name QString project name
 * \param slug QString project slug
 * \param description QString project description
 * \param srcLang QString project source language
 * \param accountIdx int account index this project belongs to
 */
void Configuration::favorProject(const QString &name, const QString &slug, const QString &description, const QString &srcLang, int accountIdx)
{
    QList<Project> projects = loadFavoredProjects(accountIdx);

    Project prj;
    prj.name = name;
    prj.slug = slug;
    prj.description = description;
    prj.srcLang = srcLang;
    prj.accountIdx = accountIdx;

    projects.append(prj);

    writeFavoredProjects(projects, accountIdx);
}



void Configuration::unfavorProject(int idx, int accountIdx)
{
    QList<Project> projects = loadFavoredProjects(accountIdx);

    projects.removeAt(idx);

    writeFavoredProjects(projects, accountIdx);
}



/*!
 * \fn QList<Configuration::Account> Configuration::loadAccounts()
 * \brief Function to load accounts from config
 *
 * Loads the accounts from the configuration system into the internal structure.
 *
 * \return QList<Configuration::Account> List of account structs
 */
QList<Configuration::Account> Configuration::loadAccounts()
{
    QList<Account> accounts;
    int size = beginReadArray(QStringLiteral("accounts"));
    for (int i = 0; i < size; ++i)
    {
        setArrayIndex(i);
        Account acc;
        acc.name = value(QStringLiteral("name")).toString();
        acc.server = value(QStringLiteral("server")).toString();
        acc.user = value(QStringLiteral("user")).toString();
        acc.password = value(QStringLiteral("password")).toString();
        acc.ignoreSSLErrors = value(QStringLiteral("ignoreSSLErrors")).toBool();
        acc.type = value(QStringLiteral("type"), 0).toInt();
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
    beginWriteArray(QStringLiteral("accounts"));
    for (int i = 0; i < accounts.length(); ++i)
    {
        setArrayIndex(i);
        setValue(QStringLiteral("name"), accounts.at(i).name);
        setValue(QStringLiteral("server"), accounts.at(i).server);
        setValue(QStringLiteral("user"), accounts.at(i).user);
        setValue(QStringLiteral("password"), accounts.at(i).password);
        setValue(QStringLiteral("ignoreSSLErrors"), accounts.at(i).ignoreSSLErrors);
        setValue(QStringLiteral("type"), accounts.at(i).type);
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
 * \param ignoreSSLErrors bool if SSL should be ignored
 * \param type int that determines the account type. 0: Transifex
 */
void Configuration::saveAccount(const QString &name, const QString &server, const QString &user, const QString &password, bool ignoreSSLErrors, int type)
{
    QList<Account> accounts = loadAccounts();

    Account acc;
    acc.name = name;
    acc.server = server;
    acc.user = user;
    acc.password = password;
    acc.ignoreSSLErrors = ignoreSSLErrors;
    acc.type = type;

    accounts.append(acc);

    writeAccounts(accounts);
}



/*!
 * \fn void Configuration::editAccount(const QString &name, const QString &server, const QString &user, const QString &password, bool ignoreSSLErrors, int type, int idx)
 * \brief Edit an account in the configuration system
 *
 * Edits an existing account in the configuration system
 *
 * \param name QString display name
 * \param server QString name of the server
 * \param user QString username
 * \param password QString password
 * \param ignoreSSLErrors bool if SSL should be ignored
 * \param type int that determines the account type. 0: Transifex
 * \param idx int index number of the account to edit
 */
void Configuration::editAccount(const QString &name, const QString &server, const QString &user, const QString &password, bool ignoreSSLErrors, int type, int idx)
{
    QList<Account> accounts = loadAccounts();

    Account acc = accounts.at(idx);
    acc.name = name;
    acc.server = server;
    acc.user = user;
    acc.password = password;
    acc.ignoreSSLErrors = ignoreSSLErrors;
    acc.type = type;

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

    account[QStringLiteral("name")] = accounts.at(idx).name;
    account[QStringLiteral("server")] = accounts.at(idx).server;
    account[QStringLiteral("user")] = accounts.at(idx).user;
    account[QStringLiteral("password")] = accounts.at(idx).password;
    account[QStringLiteral("ignoreSSLErrors")] = accounts.at(idx).ignoreSSLErrors;
    account[QStringLiteral("type")] = accounts.at(idx).type;

    return account;
}


/*!
 * \fn int Configuration::getTransifexAccount()
 * \brief Checks if a transifex.com account is set and returns it's index
 *
 * Returns the account index if the user has configured an account for transifex.com
 *
 * \return int account index
 */
int Configuration::getTransifexAccount()
{
    QList<Account> accounts = loadAccounts();

    for (int i = 0; i < accounts.length(); ++i)
    {
        if (accounts.at(i).server.contains(QStringLiteral("transifex.com"), Qt::CaseInsensitive))
        {
            return i;
        }
    }

    return -1;
}



/*!
 * \fn int Configuration::defaultFilter() const
 * \brief Returns the default filter
 * \return int default filter type
 */
int Configuration::defaultFilter() const { return m_defaultFilter; }

/*!
 * \fn void Configuration::setDefaultFilter(const int &nDefaultFilter)
 * \brief Sets the default filter
 * \param nDefaultFilter int filter type
 */
void Configuration::setDefaultFilter(int nDefaultFilter)
{
    if (nDefaultFilter != m_defaultFilter) {
        m_defaultFilter = nDefaultFilter;
        setValue(QStringLiteral("display/stringListFilter"), defaultFilter());
        emit defaultFilterChanged(defaultFilter());
    }
}


/*!
 * \fn int Configuration::sourceFontSize() const
 * \brief Returns the font size for source strings
 * \return int source font size
 */
int Configuration::sourceFontSize() const { return m_sourceFontSize; }

/*!
 * \fn void Configuration::setSourceFontSize(const int &nSourceFontSize)
 * \brief Sets the font size for source strings
 * \param nSourceFontSize int source font size
 */
void Configuration::setSourceFontSize(int nSourceFontSize)
{
    if (nSourceFontSize != m_sourceFontSize) {
        m_sourceFontSize = nSourceFontSize;
        setValue(QStringLiteral("display/sourceFontSize"), sourceFontSize());
        emit sourceFontSizeChanged(sourceFontSize());
    }
}


/*!
 * \fn int Configuration::translationFontSize() const
 * \brief Returns the font size for translation strings
 * \return int translation font size
 */
int Configuration::translationFontSize() const { return m_translationFontSize; }

/*!
 * \fn void Configuration::setTranslationFontSize(const int &nTranslationFontSize)
 * \brief Sets the font size for translation strings
 * \param nTranslationFontSize int translation font size
 */
void Configuration::setTranslationFontSize(int nTranslationFontSize)
{
    if (nTranslationFontSize != m_translationFontSize) {
        m_translationFontSize = nTranslationFontSize;
        setValue(QStringLiteral("display/translationFontSize"), translationFontSize());
        emit translationFontSizeChanged(translationFontSize());
    }
}

/*!
 * \fn QString Configuration::language() const
 * \brief Returns the current set UI language code
 * \return QString UI language code
 */
QString Configuration::language() const { return m_language; }

/*!
 * \fn void Configuration::setLanguage(const QString &nLanguage)
 * \brief Sets the UI language to use
 * \param nLanguage QString language code
 */
void Configuration::setLanguage(const QString &nLanguage)
{
    if (nLanguage != m_language) {
        m_language = nLanguage;
        setValue(QStringLiteral("display/language"), language());
        emit languageChanged(language());
    }
}
