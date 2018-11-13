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
#include "apihelper.h"

APIHelper::APIHelper(QObject *parent) :
    QObject(parent)
{
}


/*!
 * \fn QUrl APIHelper::buildUrl(const QString &apipart, int accountIdx)
 * \brief Return the API URL
 *
 * This function uses the stored server address and combines it with the
 * used API part and the used protocol to build the API URL.
 *
 * \param apipart       The part of the API that is used
 * \param accountIdx    Index of the account to use
 * \return              QString with the complete URL
 */

QUrl APIHelper::buildUrl(const QString &apipart, int accountIdx)
{
    QVariantMap account = config.getAccount(accountIdx);
    QString server = account[QStringLiteral("server")].toString();

    if (server.endsWith(QLatin1Char('/')))
        server.chop(1);

    server.append("/api/2");
    server.append(apipart);

    QUrl url(server);

#ifdef QT_DEBUG
    qDebug() << url.toString();
#endif

    return url;
}



/*!
 * \fn QVariantMap APIHelper::jsonToVariantMap(const QByteArray &json)
 * \brief Converts th JSON server reply into a QVariantMap
 *
 * This functions takes the server JSON reply as a QByteArray and
 * converts it into a QVariantMap.
 *
 * \param json      QByteArray that holds the JSON reply
 * \return          The reply as QVariantMap
 */

QVariantMap APIHelper::jsonToVariantMap(const QByteArray &json)
{
#ifdef QT_DEBUG
        qDebug() << "Start to parse JSON into QVariantMap.";
#endif
        QString jsonString(json);

#ifdef QT_DEBUG
        qDebug() << json;
#endif
        QJsonParseError err;

        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8(), &err);

#ifdef QT_DEBUG
        qDebug() << err.errorString();
#endif

    return jsonDoc.object().toVariantMap();
}



/*!
 * \fn QVariantList APIHelper::jsonToVariantList(const QByteArray &json)
 * \brief Converts th JSON server reply into a QVariantList
 *
 * This functions takes the server JSON reply as a QByteArray and
 * converts it into a QVariantList.
 *
 * \param json      QByteArray that holds the JSON reply
 * \return          The reply as QVariantList
 */

QVariantList APIHelper::jsonToVariantList(const QByteArray &json)
{
#ifdef QT_DEBUG
        qDebug() << "Start to parse JSON into QVariantMap.";
#endif
        QString jsonString(json);

#ifdef QT_DEBUG
        qDebug() << json;
#endif
        QJsonParseError err;

        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8(), &err);

#ifdef QT_DEBUG
        qDebug() << err.errorString();
#endif

    return jsonDoc.array().toVariantList();
}
