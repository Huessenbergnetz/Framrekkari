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

#ifndef APIHELPER_H
#define APIHELPER_H

#include <QObject>
#include <QVariantMap>
#include <QVariantList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include "../configuration.h"

class APIHelper : public QObject
{
    Q_OBJECT
public:
    explicit APIHelper(QObject *parent = 0);

    QUrl buildUrl(const QString &apipart, int accountIdx);
    QVariantMap jsonToVariantMap(const QByteArray &json);
    QVariantList jsonToVariantList(const QByteArray &json);

signals:

public slots:

private:
    Configuration config;

};

#endif // APIHELPER_H
