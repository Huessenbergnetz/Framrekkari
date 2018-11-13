/*
    Framrekkari - Transifex Client for SailfishOS
    Copyright (C) 2014-2018  Hüssenbergnetz/Matthias Fehring
    https://github.com/Buschtrommel/Framrekkari

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

    QUrl url = helper.buildUrl(QStringLiteral("/projects/"), accountIdx);

    if (start > 0 && end > start)
    {
        QUrlQuery uq;
        uq.addQueryItem(QStringLiteral("start"), QString::number(start));
        uq.addQueryItem(QStringLiteral("end"), QString::number(end));
        url.setQuery(uq);
    }

    getProjectsReply = nm.get(QNetworkRequest(url));

    connect(getProjectsReply, &QNetworkReply::finished, this, &ProjectsAPI::getProjectsFinished);
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
        switch (getProjectsReply->error()) {
        case QNetworkReply::ContentNotFoundError:
            emit gotProjectsError(tr("Not found"));
            break;
        case QNetworkReply::OperationCanceledError:
            emit gotProjectsError(tr("Operation canceled. Wrong username and/or password or SSL handshake failed."));
            break;
        default:
            emit gotProjectsError(getProjectsReply->errorString());
            break;
        }
    }

    getProjectsReply->deleteLater();
}



void ProjectsAPI::getProject(int accountIdx, const QString &slug, bool details)
{
    nm.setAccountIndex(accountIdx);

    QUrl url = helper.buildUrl("/project/" + slug + "/", accountIdx);

    if (details)
    {
        QUrlQuery uq;
        uq.addQueryItem(QStringLiteral("details"), QString());
        url.setQuery(uq);
    }

    getProjectReply = nm.get(QNetworkRequest(url));

    connect(getProjectReply, &QNetworkReply::finished, this, &ProjectsAPI::getProjectFinished);
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

    getProjectReply->deleteLater();
}
