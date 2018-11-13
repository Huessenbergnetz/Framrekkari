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

#ifndef STATISTICSAPI_H
#define STATISTICSAPI_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QStringList>
#include <QLocale>
#include "apihelper.h"
#include "../network.h"

class StatisticsAPI : public QObject
{
    Q_OBJECT
public:
    explicit StatisticsAPI(QObject *parent = 0);

    void getAllProjectLangStats(const QString & projectSlug, const QVariantList &resources, int accountIdx);
    Q_INVOKABLE void getLangResourcesStats(const QString &projectSlug, const QString &lang, const QVariantList &resources, int accountIdx);

signals:
    void gotAllProjectLangStats(const QVariantMap &projectStats);
    void gotAllProjectLangStatsError(const QString &gotAllProjectsLangStatsErrorString);
    void gotLangResourcesStats(const QVariantList &langStats);
    void gotLangResourcesStatsError(const QString &gotLangResourcesStatsErrorString);

public slots:

private slots:
    void getAllProjectLangStatsFinished(QNetworkReply* rep);
    void getLangResourcesStatsFinished(QNetworkReply* rep);

private:
    Network getAllProjectLangStatsNm, getResourcesStatsNm;
    APIHelper helper;

    QMap<QString, QVariant> projectLangStats;
    int projectLangStatsCounter;

    QVariantList langResourceStats;
    int langResourceStastsCounter;

};

#endif // STATISTICSAPI_H
