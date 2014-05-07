#include <QDebug>
#include "translationstringsapi.h"

TranslationStringsAPI::TranslationStringsAPI(QObject *parent) :
    QObject(parent)
{
}



void TranslationStringsAPI::getStrings(const QString &project, const QString &resource, const QString &lang, int accountIdx)
{
    nm.setAccountIndex(accountIdx);

    QUrl url = helper.buildUrl("/project/" + project + "/resource/" + resource + "/translation/" + lang + "/strings/", accountIdx);

    connect(&nm, SIGNAL(finished(QNetworkReply*)), this, SLOT(getStringsFinished(QNetworkReply*)));

    nm.get(QNetworkRequest(url));
}




void TranslationStringsAPI::getStringsFinished(QNetworkReply *rep)
{
    if (rep->error() == QNetworkReply::NoError)
    {

        QVariantList results = helper.jsonToVariantList(rep->readAll());

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
        qDebug() << "HTTP-Error:" << rep->errorString();
#endif
        switch (rep->error()) {
        case QNetworkReply::ContentNotFoundError:
            emit gotStringsError(tr("Not found"));
            break;
        case QNetworkReply::OperationCanceledError:
            emit gotStringsError(tr("Operation canceled. Wrong username and/or password or SSL handshake failed."));
            break;
        default:
            emit gotStringsError(rep->errorString());
            break;
        }
    }

    rep->deleteLater();
}
