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
#include "network.h"

Network::Network(QObject *parent) :
    QNetworkAccessManager(parent)
{
    connect(this, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)), this, SLOT(slotAuthenticationRequired(QNetworkReply*,QAuthenticator*)));

    connect(this, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT(sslErrorHandler(QNetworkReply*,QList<QSslError>)));
}



void Network::setAccountIndex(int idx)
{
    if (accountIndex != idx) {
        clearAccessCache();
        accountIndex = idx;
        account = config.getAccount(accountIndex);
    }
}


/*!
 * \fn void Network::slotAuthenticationRequired(QNetworkReply* rep, QAuthenticator *authenticator)
 * \brief Handles network authentication requests
 *
 * This slot handles the network authentication requests. It takes the login data from the settings.
 *
 * \param rep               The reply that requests the authentication
 * \param authenticator     The used QAuthenticator
 */

void Network::slotAuthenticationRequired(QNetworkReply* rep, QAuthenticator *authenticator)
{
//    QVariantMap account = config.getAccount(accountIndex);

#ifdef QT_DEBUG
        qDebug() << "Account: " << account;
        qDebug() << "Current user: " << authenticator->user();
        qDebug() << "Current password: " << authenticator->password();
#endif

    if (authenticator->user().isEmpty() && authenticator->password().isEmpty())
    {
        authenticator->setUser(account["user"].toString());
        authenticator->setPassword(account["password"].toString());
    } else {
        if ((authenticator->user() != account["user"].toString()) || (authenticator->password() !=  account["password"].toString() ))
        {
            authenticator->setUser(account["user"].toString());
            authenticator->setPassword(account["password"].toString());
        } else {
            rep->abort();
#ifdef QT_DEBUG
            qDebug() << "Abort authentication!";
#endif
        }
    }
}



/*!
 * \fn void OcNetwork::sslErrorHandler(QNetworkReply* rep,const QList<QSslError> &errors)
 * \brief Handles SSL errors
 *
 * This slot handles the SSL erorrs produced by the network connection. On Harmattan it uses
 * aegis-certman to verify and trust not known certificates.
 *
 * \param rep           The reply that contents the SSL error information
 * \param errors        The list of SSL errors
 */

void Network::sslErrorHandler(QNetworkReply* rep,const QList<QSslError> &errors)
{
    QVariantMap account = config.getAccount(accountIndex);

    if (account["ignoreSSLErrors"].toBool())
    {
        rep->ignoreSslErrors();

#ifdef QT_DEBUG
        qDebug() << "Ignore SSL-Errors";
#endif

    } else {

        rep->abort();
        qDebug() << "Abort network operation...";
    }
}
