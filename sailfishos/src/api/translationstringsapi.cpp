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
#include "translationstringsapi.h"

TranslationStringsAPI::TranslationStringsAPI(QObject *parent) :
    QObject(parent)
{
}



void TranslationStringsAPI::getStrings(const QString &project, const QString &resource, const QString &lang, int filter, int accountIdx)
{
    nm.setAccountIndex(accountIdx);
    getStringFilter = filter;

    QUrl url = helper.buildUrl("/project/" + project + "/resource/" + resource + "/translation/" + lang + "/strings/", accountIdx);

    QUrlQuery uq;
    uq.addQueryItem(QStringLiteral("details"), QString());
    url.setQuery(uq);

    getStringReply = nm.get(QNetworkRequest(url));

    connect(getStringReply, &QNetworkReply::finished, this, &TranslationStringsAPI::getStringsFinished);
}




void TranslationStringsAPI::getStringsFinished()
{
    if (getStringReply->error() == QNetworkReply::NoError)
    {
        QVariantList results;

        QVariantList m_results = helper.jsonToVariantList(getStringReply->readAll());

        int dataIndex = 0;
        for (int i = 0; i < m_results.length(); ++i)
        {
            QVariantMap map = m_results.at(i).toMap();

            QVariantList context;
            if(map[QStringLiteral("context")].type() == QVariant::List) {
                context = map[QStringLiteral("context")].toList();
            } else {
                context << map[QStringLiteral("context")].toString();
            }

            map[QStringLiteral("context")] = context;

            QVariantMap sources;
            QVariantMap translations;
            bool pluralized = map[QStringLiteral("pluralized")].toBool();
            if (pluralized)
            {
                sources = map[QStringLiteral("source_string")].toMap();
                translations = map[QStringLiteral("translation")].toMap();
            } else {
                sources[QStringLiteral("1")] = map[QStringLiteral("source_string")].toString();
                translations[QStringLiteral("1")] = map[QStringLiteral("translation")].toString();
            }

            map[QStringLiteral("source_string")] = sources;
            map[QStringLiteral("translation")] = translations;

            if (getStringFilter == 0) {

                map[QStringLiteral("dataIndex")] = dataIndex++;
                results << map;

            } else if (getStringFilter == 1) {

                if (translations[QStringLiteral("1")].toString().isEmpty()) {
                    map[QStringLiteral("dataIndex")] = dataIndex++;
                    results << map;
                }

            } else if (getStringFilter == 2) {

                if (!map[QStringLiteral("reviewed")].toBool()) {
                    map[QStringLiteral("dataIndex")] = dataIndex++;
                    results << map;
                }

            } else if (getStringFilter == 3) {
                if (map[QStringLiteral("reviewed")].toBool()) {
                    map[QStringLiteral("dataIndex")] = dataIndex++;
                    results << map;
                }
            }
        }

#ifdef QT_DEBUG
        qDebug() << results;
#endif
        if (results.isEmpty())
        {
            emit gotStringsError(tr("Server reply was empty."));
        } else {
            emit gotStrings(results);
        }

    } else {
#ifdef QT_DEBUG
        qDebug() << "HTTP-Error:" << getStringReply->errorString();
#endif
        switch (getStringReply->error()) {
        case QNetworkReply::ContentNotFoundError:
            emit gotStringsError(tr("Not found"));
            break;
        case QNetworkReply::OperationCanceledError:
            emit gotStringsError(tr("Operation canceled. Wrong username and/or password or SSL handshake failed."));
            break;
        default:
            emit gotStringsError(getStringReply->errorString());
            break;
        }
    }

    getStringReply->deleteLater();
}


void TranslationStringsAPI::saveString(const QString &project, const QString &resource, const QString &lang, const QVariantMap &translation, const QString &hash, bool reviewed, int modelIdx, int dataIndex, int accountIdx)
{
    nm.setAccountIndex(accountIdx);

    transToSave.clear();
    transToSave[QStringLiteral("modelIdx")] = QVariant::fromValue(modelIdx);
    transToSave[QStringLiteral("translation")] = translation;
    transToSave[QStringLiteral("reviewed")] = QVariant::fromValue(reviewed);
    transToSave[QStringLiteral("dataIndex")] = QVariant::fromValue(dataIndex);

    QVariantMap data;
    if (translation.count() > 1) {
        data[QStringLiteral("translation")] = translation;
    } else {
        data[QStringLiteral("translation")] = translation[QStringLiteral("1")].toString();
    }
    data[QStringLiteral("reviewed")] = reviewed;

    QJsonDocument jsonDoc = QJsonDocument::fromVariant(data);

    QUrl url = helper.buildUrl("/project/" + project + "/resource/" + resource + "/translation/" + lang + "/string/" + hash + "/", accountIdx);

#ifdef QT_DEBUG
    qDebug() << transToSave;
    qDebug() << url.toString();
    qDebug() << jsonDoc;
#endif

    QNetworkRequest request(url);

    request.setRawHeader("Content-Type", "application/json");

    saveStringReply = nm.put(request, jsonDoc.toJson(QJsonDocument::Compact));

    connect(saveStringReply, &QNetworkReply::finished, this, &TranslationStringsAPI::saveStringFinished);

}



void TranslationStringsAPI::saveStringFinished()
{
    if (saveStringReply->error() == QNetworkReply::NoError)
    {

#ifdef QT_DEBUG
        qDebug() << "SAVED";
#endif
        emit savedString(transToSave);



    } else {
#ifdef QT_DEBUG
        qDebug() << "HTTP-Error-Code:"  << saveStringReply->error();
        qDebug() << "HTTP-Error:" << saveStringReply->errorString();
#endif
        switch (saveStringReply->error()) {
        case QNetworkReply::ContentNotFoundError:
            emit savedStringError(tr("Not found. Code %1.").arg(saveStringReply->error()));
            break;
        case QNetworkReply::OperationCanceledError:
            emit savedStringError(tr("Operation canceled. Wrong username and/or password or SSL handshake failed. Code %1.").arg(saveStringReply->error()));
            break;
        case QNetworkReply::UnknownContentError:
            emit savedStringError(tr("Could not save content on server. Maybe wrong entity hash. Code %1.").arg(saveStringReply->error()));
            break;
        default:
            emit savedStringError(saveStringReply->errorString());
            break;
        }
    }

    saveStringReply->deleteLater();
}
