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
#include "projectsapi.h"

ProjectsAPI::ProjectsAPI(QObject *parent) :
    QObject(parent)
{
}


void ProjectsAPI::getProjects(int accountIdx, int start, int end)
{
    nm.setAccountIndex(accountIdx);

    QUrl url = helper.buildUrl("/projects/", accountIdx);

    if (start > 0 && end > start)
    {
        QUrlQuery uq;
        uq.addQueryItem("start", QString::number(start));
        uq.addQueryItem("end", QString::number(end));
        url.setQuery(uq);
    }

    getProjectsReply = nm.get(QNetworkRequest(url));

    connect(getProjectsReply, SIGNAL(finished()), this, SLOT(getProjectsFinished()));
}


void ProjectsAPI::getProjectsFinished()
{
    if (getProjectsReply->error() == QNetworkReply::NoError)
    {
        QVariantList getProjectsResult = helper.jsonToVariantList(getProjectsReply->readAll());

#ifdef QT_DEBUG
        qDebug() << getProjectsResult;
#endif

        if (getProjectsResult.isEmpty())
        {
            emit gotProjectsError(tr("Server reply was empty."));
        } else {
            emit gotProjects(getProjectsResult);
        }

    } else {
#ifdef QT_DEBUG
        qDebug() << "HTTP-Error:" << getProjectsReply->errorString();
#endif
        switch (getProjectReply->error()) {
        case QNetworkReply::ContentNotFoundError:
            emit gotProjectsError(tr("Not found"));
            break;
        case QNetworkReply::OperationCanceledError:
            emit gotProjectsError(tr("Operation canceled. Wrong username and/or password or SSL handshake failed."));
            break;
        default:
            emit gotProjectsError(getProjectReply->errorString());
            break;
        }
    }
}



void ProjectsAPI::getProject(int accountIdx, const QString &slug, bool details)
{
    nm.setAccountIndex(accountIdx);

    QUrl url = helper.buildUrl("/project/" + slug.toLower().replace(" ", "-") + "/", accountIdx);

    if (details)
    {
        QUrlQuery uq;
        uq.addQueryItem("details", QString());
        url.setQuery(uq);
    }

    getProjectReply = nm.get(QNetworkRequest(url));

    connect(getProjectReply, SIGNAL(finished()), this, SLOT(getProjectFinished()));
}


void ProjectsAPI::getProjectFinished()
{
    if (getProjectReply->error() == QNetworkReply::NoError)
    {

        QVariantMap getProjectResult = helper.jsonToVariantMap(getProjectReply->readAll());

#ifdef QT_DEBUG
        qDebug() << getProjectResult;
#endif

        if (getProjectResult.isEmpty())
        {
            emit gotProjectError(tr("Server reply was empty."));
        } else {
            emit gotProject(getProjectResult);
        }

    } else {
#ifdef QT_DEBUG
        qDebug() << "HTTP-Error:" << getProjectReply->errorString();
#endif
        switch (getProjectReply->error()) {
        case QNetworkReply::ContentNotFoundError:
            emit gotProjectError(tr("Not found"));
            break;
        case QNetworkReply::OperationCanceledError:
            emit gotProjectError(tr("Operation canceled. Wrong username and/or password or SSL handshake failed."));
            break;
        default:
            emit gotProjectError(getProjectReply->errorString());
            break;
        }
    }
}
