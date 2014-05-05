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

#ifndef PROJECTSAPI_H
#define PROJECTSAPI_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonParseError>
#include "apihelper.h"
#include "../network.h"

class ProjectsAPI : public QObject
{
    Q_OBJECT
public:
    explicit ProjectsAPI(QObject *parent = 0);

    void getProjects(int accountIdx, int start = 0, int end = 0);
    Q_INVOKABLE void getProject(int accountIdx, const QString &slug, bool details = true);

signals:
    void gotProjects(QVariantList projects);
    void gotProjectsError(const QString &gotProjectsErrorString);
    void gotProject(QVariantMap project);
    void gotProjectError(const QString &gotProjectErrorString);

public slots:

private slots:
    void getProjectsFinished();
    void getProjectFinished();

private:
    Network nm;
    QNetworkReply *getProjectsReply, *getProjectReply;
    APIHelper helper;

};

#endif // PROJECTSAPI_H
