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

#ifndef NETWORK_H
#define NETWORK_H

#include <QNetworkAccessManager>
#include <QAuthenticator>
#include <QNetworkReply>
#include <QSslError>
#include "configuration.h"

class Network : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit Network(QObject *parent = 0);

    enum ApiCall {GetProjects, GetProject};

    void setAccountIndex(int idx);

signals:

public slots:

private slots:
    void slotAuthenticationRequired(QNetworkReply*,QAuthenticator *);
    void sslErrorHandler(QNetworkReply *rep,const QList<QSslError> &errors);

private:
    int accountIndex;

    QVariantMap account;

    Configuration config;


};

#endif // NETWORK_H
