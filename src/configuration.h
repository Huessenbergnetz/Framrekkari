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

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>
#include <QSettings>
#include <QVariant>
#include <QVariantMap>

class Configuration : public QSettings
{
    Q_OBJECT
public:
    explicit Configuration(QObject *parent = 0);

    Q_INVOKABLE QVariant get(const QString &key, const QVariant &def = QVariant()) const;
    Q_INVOKABLE bool getBool(const QString &key, const QVariant &def = QVariant()) const;
    Q_INVOKABLE void set(const QString &key, const QVariant &val);

    // account management
    Q_INVOKABLE void saveAccount(const QString &name, const QString &server, const QString &user, const QString &password, bool ignoreSSLErrors, int type);
    Q_INVOKABLE void editAccount(const QString &name, const QString &server, const QString &user, const QString &password, bool ignoreSSLErrors, int type, int idx);
    Q_INVOKABLE QVariantMap getAccount(int idx);
    Q_INVOKABLE void removeAccount(int idx);

    // favorite projects
    Q_INVOKABLE void favorProject(const QString &name, const QString &slug, const QString &description, const QString &srcLang, int accountIdx);
    Q_INVOKABLE void unfavorProject(int idx, int accountIdx);


    // check if transifex account available
    Q_INVOKABLE int getTransifexAccount();

    struct Account {
        QString name;
        QString server;
        QString user;
        QString password;
        bool ignoreSSLErrors;
        int type;
    };

    struct Project {
        QString name;
        QString slug;
        QString description;
        QString srcLang;
        int accountIdx;
    };

    QList<Account> loadAccounts();
    QList<Project> loadFavoredProjects(int accountIdx);

signals:
    void savedAccout();
    void savedFavoredProject();

public slots:

private:
    void writeAccounts(const QList<Account> &accounts);
    void writeFavoredProjects(const QList<Project> &projects, int accountIdx);

};

#endif // CONFIGURATION_H
