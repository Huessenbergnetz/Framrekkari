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

    getStringReply = nm.get(QNetworkRequest(url));

    connect(getStringReply, SIGNAL(finished()), this, SLOT(getStringsFinished()));
}




void TranslationStringsAPI::getStringsFinished()
{
    if (getStringReply->error() == QNetworkReply::NoError)
    {

        QVariantList results = helper.jsonToVariantList(getStringReply->readAll());

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


void TranslationStringsAPI::saveString(const QString &project, const QString &resource, const QString &lang, const QVariantMap &translation, const QString &hash, int modelIdx, int accountIdx)
{
    nm.setAccountIndex(accountIdx);

    transToSave.clear();
    transToSave["modelIdx"] = QVariant::fromValue(modelIdx);
    transToSave["translation"] = translation;

    QVariantMap data;
    if (translation.count() > 1) {
        data["translation"] = translation;
    } else {
        data["translation"] = translation["1"].toString();
    }

    QJsonDocument jsonDoc = QJsonDocument::fromVariant(data);

    QUrl url = helper.buildUrl("/project/" + project + "/resource/" + resource + "/translation/" + lang + "/string/" + hash + "/", accountIdx);

#ifdef QT_DEBUG
    qDebug() << transToSave;
    qDebug() << url.toString();
    qDebug() << jsonDoc.object().toVariantMap();
#endif

    QByteArray parameters = jsonDoc.toBinaryData();
    QNetworkRequest request(url);

    request.setRawHeader("Content-Type", "application/json; charset=utf-8");
    request.setRawHeader("Content-Length", QByteArray::number(parameters.size()));

    saveStringReply = nm.put(request, QString(parameters).toUtf8());

    connect(saveStringReply, SIGNAL(finished()), this, SLOT(saveStringFinished()));

}



void TranslationStringsAPI::saveStringFinished()
{
    if (saveStringReply->error() == QNetworkReply::NoError)
    {

#ifdef QT_DEBUG
        qDebug() << "SAVED";
#endif
        savedString(transToSave);



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
            emit savedStringError(tr("Could not save content on server. Maybe wrong entitiy hash. Code %1.").arg(saveStringReply->error()));
            break;
        default:
            emit savedStringError(saveStringReply->errorString());
            break;
        }
    }

    saveStringReply->deleteLater();
}
