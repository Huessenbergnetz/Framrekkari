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

#include "dbmanager.h"
#include "globals.h"

/*!
 * \class DbManager
 * \brief The DbManager class procvides base functions for database access and creation.
 *
 * This class is a helper class that can open and create the SQLite database.
 *
 * \param parent
 */
DbManager::DbManager(QObject *parent) :
    QObject(parent)
{
}

/*!
 * \fn bool DbManager::openDB()
 * \brief Opens the database
 *
 * This funtion opens the database file and returns true if it was successful
 *
 * \return true if successful
 */
bool DbManager::openDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");

    QString path(QDir::homePath().append(DATA_DIR).append("/database.sqlite"));
    db.setDatabaseName(path);

    return db.open();
}



/*!
 * \fn DbManager::createTables()
 * \brief Creates tables, triggers and indexes
 *
 * This function creates the necessary tables, triggers and indexes and
 * returns true if it was successful.
 *
 * \return true if successful
 */
bool DbManager::createTables()
{
    bool ret = true;
    if(db.isOpen())
    {
        QSqlQuery build;
        QSqlDatabase::database().transaction();

        build.exec(QString("CREATE TABLE IF NOT EXISTS projects "
                           "(accountId INTEGER NOT NULL, "
                           "name TEXT NOT NULL, "
                           "slug TEXT NOT NULL, "
                           "desc TEXT NOT NULL, "
                           "srcLang TEXT NOT NULL, "
                           "longDesc TEXT, "
                           "homepage TEXT, "
                           "feed TEXT, "
                           "created INTEGER, "
                           "anyoneSubmit BOOLEAN, "
                           "bugTracker TEXT, "
                           "transInstructions TEXT, "
                           "tags TEXT, "
                           "outsource BOOLEAN, "
                           "autoJoin BOOLENA, "
                           "maintainers TEXT, "
                           "owner TEXT, "
                           "fillUp BOOLEAN, "
                           "lastMod INTEGER, "
                           "favorite BOOLEAN);"
                           ));

        QSqlDatabase::database().commit();

    } else {
        ret = false;
    }

    return ret;
}


/*!
 * \fn DbManager::closeDB()
 * \brief Closes the database
 *
 * This function closes the database connection.
 *
 * \return true by default
 */
bool DbManager::closeDB()
{
    db.close();
    return true;
}
