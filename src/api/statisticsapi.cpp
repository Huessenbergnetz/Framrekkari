#include <QDebug>

#include "statisticsapi.h"

StatisticsAPI::StatisticsAPI(QObject *parent) :
    QObject(parent)
{
}



void StatisticsAPI::getAllProjectLangStats(const QString &projectSlug, const QVariantList &resources, int accountIdx)
{
    nm.setAccountIndex(accountIdx);
    projectLangStats.clear();
    projectLangStatsCounter = resources.length();


    for (int i = 0; i < resources.length(); ++i)
    {
        QUrl url = helper.buildUrl("/project/" + projectSlug + "/resource/" + resources.at(i).toString() + "/stats/", accountIdx);

        connect(&nm, SIGNAL(finished(QNetworkReply*)), this, SLOT(getAllProjectLangStatsFinished(QNetworkReply*)), Qt::UniqueConnection);

        nm.get(QNetworkRequest(url));
    }
}


void StatisticsAPI::getAllProjectLangStatsFinished(QNetworkReply* rep)
{
    if (rep->error() == QNetworkReply::NoError)
    {

        QVariantMap results = helper.jsonToVariantMap(rep->readAll());

#ifdef QT_DEBUG
        qDebug() << results;
#endif

        QMapIterator<QString, QVariant> i(results);
        while(i.hasNext()) {
            i.next();

            QMap<QString, QVariant> valueMap;

            if (projectLangStats.contains(i.key()))
                valueMap = projectLangStats[i.key()].toMap();

            QVariantMap map = i.value().toMap();

            if (valueMap["name"].toString().isEmpty()) {
                QLocale locale(i.key());
                if (locale.language() != QLocale::C) {
                    QString name = locale.nativeLanguageName();
                    name[0] = name[0].toUpper();
                    valueMap["name"] = QVariant::fromValue(name);
                }
            }


            valueMap["translated"] = QVariant::fromValue(valueMap["translated"].toDouble() + map.value("translated_entities").toDouble());
            valueMap["untranslated"] = QVariant::fromValue(valueMap["untranslated"].toDouble() + map.value("untranslated_entities").toDouble());
            valueMap["reviewed"] = QVariant::fromValue(valueMap["reviewed"].toDouble() + map.value("reviewed").toDouble());

            projectLangStats[i.key()] = QVariant::fromValue(valueMap);
        }

        projectLangStatsCounter--;

#ifdef QT_DEBUG
        qDebug() << projectLangStats;
        qDebug() << projectLangStatsCounter;
#endif

//        if (getProjectResult.isEmpty())
//        {
//            emit gotProjectError(tr("Server reply was empty."));
//        } else {
//            emit gotProject(getProjectResult);
//        }

        if (projectLangStatsCounter == 0)
            emit gotAllProjectLangStats(projectLangStats);

    } else {
#ifdef QT_DEBUG
        qDebug() << "HTTP-Error:" << rep->errorString();
#endif
        switch (rep->error()) {
        case QNetworkReply::ContentNotFoundError:
            emit gotAllProjectLangStatsError(tr("Not found"));
            break;
        case QNetworkReply::OperationCanceledError:
            emit gotAllProjectLangStatsError(tr("Operation canceled. Wrong username and/or password or SSL handshake failed."));
            break;
        default:
            emit gotAllProjectLangStatsError(rep->errorString());
            break;
        }
    }

    rep->deleteLater();
}



void StatisticsAPI::getLangResourcesStats(const QString &projectSlug, const QString &lang, const QVariantList &resources, int accountIdx)
{
    nm.setAccountIndex(accountIdx);
    langResourceStats.clear();
    langResourceStastsCounter = resources.length();


    for (int i = 0; i < resources.length(); ++i)
    {
        QUrl url = helper.buildUrl("/project/" + projectSlug + "/resource/" + resources.at(i).toString() + "/stats/" + lang + "/", accountIdx);
        qDebug() << url.toString();

        connect(&nm, SIGNAL(finished(QNetworkReply*)), this, SLOT(getLangResourcesStatsFinished(QNetworkReply*)), Qt::UniqueConnection);

        nm.get(QNetworkRequest(url));
    }
}


void StatisticsAPI::getLangResourcesStatsFinished(QNetworkReply *rep)
{
    if (rep->error() == QNetworkReply::NoError)
    {

        QStringList path(rep->url().path().split("/"));

        QVariantMap results = helper.jsonToVariantMap(rep->readAll());

#ifdef QT_DEBUG
        qDebug() << results;
#endif
        results["resourceSlug"] = QVariant::fromValue(path.at(6));

        langResourceStats << results;

        langResourceStastsCounter--;

#ifdef QT_DEBUG
        qDebug() << langResourceStats;
        qDebug() << langResourceStastsCounter;
#endif

//        if (getProjectResult.isEmpty())
//        {
//            emit gotProjectError(tr("Server reply was empty."));
//        } else {
//            emit gotProject(getProjectResult);
//        }

        if (langResourceStastsCounter == 0)
            emit gotLangResourcesStats(langResourceStats);

    } else {
#ifdef QT_DEBUG
        qDebug() << "HTTP-Error:" << rep->errorString();
#endif
        switch (rep->error()) {
        case QNetworkReply::ContentNotFoundError:
            emit gotLangResourcesStatsError(tr("Not found"));
            break;
        case QNetworkReply::OperationCanceledError:
            emit gotLangResourcesStatsError(tr("Operation canceled. Wrong username and/or password or SSL handshake failed."));
            break;
        default:
            emit gotLangResourcesStatsError(rep->errorString());
            break;
        }
    }

    rep->deleteLater();
}
