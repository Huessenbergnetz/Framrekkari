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

#ifndef TRANSLATIONSTRINGSAPI_H
#define TRANSLATIONSTRINGSAPI_H

#include <QObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QUrlQuery>
#include "../network.h"
#include "apihelper.h"

class TranslationStringsAPI : public QObject
{
    Q_OBJECT
public:
    explicit TranslationStringsAPI(QObject *parent = 0);

    void getStrings(const QString &project, const QString &resource, const QString &lang, int filter, int accountIdx);
    void saveString(const QString &project, const QString &resource, const QString &lang, const QVariantMap &translation, const QString &hash, bool reviewed, int modelIdx, int dataIndex, int accountIdx);

signals:
    void gotStrings(const QVariantList &translationStrings);
    void gotStringsError(const QString &gotStringsErrorString);
    void savedString(const QVariantMap &savedStrings);
    void savedStringError(const QString &savedStringErrorString);

public slots:

private slots:
    void getStringsFinished();
    void saveStringFinished();

private:
    Network nm;
    APIHelper helper;

    int getStringFilter; // 0 = all, 1 = untranslated, 2 = not reviewed, 3 = reviewed

    QVariantMap transToSave;
    QNetworkReply *saveStringReply, *getStringReply;


};

#endif // TRANSLATIONSTRINGSAPI_H
