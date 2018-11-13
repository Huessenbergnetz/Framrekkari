#include <QDebug>

#include "statisticsapi.h"

StatisticsAPI::StatisticsAPI(QObject *parent) :
    QObject(parent)
{
}



void StatisticsAPI::getAllProjectLangStats(const QString &projectSlug, const QVariantList &resources, int accountIdx)
{
    if (resources.isEmpty()) {
        emit gotAllProjectLangStatsError(tr("No resources set."));
        return;
    }

    getAllProjectLangStatsNm.setAccountIndex(accountIdx);
    projectLangStats.clear();
    projectLangStatsCounter = resources.length();


    for (int i = 0; i < resources.length(); ++i)
    {
        QUrl url = helper.buildUrl("/project/" + projectSlug + "/resource/" + resources.at(i).toString() + "/stats/", accountIdx);

        connect(&getAllProjectLangStatsNm, &Network::finished, this, &StatisticsAPI::getAllProjectLangStatsFinished, Qt::UniqueConnection);

        getAllProjectLangStatsNm.get(QNetworkRequest(url));
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

        if (!results.isEmpty()) {
            QMapIterator<QString, QVariant> i(results);
            while(i.hasNext()) {
                i.next();

                QMap<QString, QVariant> valueMap;

                if (projectLangStats.contains(i.key()))
                    valueMap = projectLangStats[i.key()].toMap();

                QVariantMap map = i.value().toMap();

                valueMap[QStringLiteral("translated")] = QVariant::fromValue(valueMap[QStringLiteral("translated")].toDouble() + map.value(QStringLiteral("translated_entities")).toDouble());
                valueMap[QStringLiteral("untranslated")] = QVariant::fromValue(valueMap[QStringLiteral("untranslated")].toDouble() + map.value(QStringLiteral("untranslated_entities")).toDouble());
                valueMap[QStringLiteral("reviewed")] = QVariant::fromValue(valueMap[QStringLiteral("reviewed")].toDouble() + map.value(QStringLiteral("reviewed")).toDouble());

                projectLangStats[i.key()] = QVariant::fromValue(valueMap);
            }
        }

        projectLangStatsCounter--;

#ifdef QT_DEBUG
        qDebug() << projectLangStats;
        qDebug() << projectLangStatsCounter;
#endif

        if (projectLangStatsCounter == 0) {
            if (!projectLangStats.isEmpty()) {
                emit gotAllProjectLangStats(projectLangStats);
            } else {
                emit gotAllProjectLangStatsError(tr("Server reply was empty."));
            }
        }

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
    if (resources.isEmpty()) {
        emit gotLangResourcesStatsError(tr("No resources set."));
        return;
    }

    getResourcesStatsNm.setAccountIndex(accountIdx);
    langResourceStats.clear();
    langResourceStastsCounter = resources.length();
    qDebug() << "RESOURCES: " << langResourceStastsCounter;


    for (int i = 0; i < langResourceStastsCounter; ++i)
    {
        QUrl url = helper.buildUrl("/project/" + projectSlug + "/resource/" + resources.at(i).toString() + "/stats/" + lang + "/", accountIdx);
        qDebug() << url.toString();

        connect(&getResourcesStatsNm, &Network::finished, this, &StatisticsAPI::getLangResourcesStatsFinished, Qt::UniqueConnection);

        getResourcesStatsNm.get(QNetworkRequest(url));
    }
}


void StatisticsAPI::getLangResourcesStatsFinished(QNetworkReply* rep)
{
    if (rep->error() == QNetworkReply::NoError)
    {

        QStringList path(rep->url().path().split(QLatin1Char('/')));

        QVariantMap results = helper.jsonToVariantMap(rep->readAll());

#ifdef QT_DEBUG
        qDebug() << results;
#endif
        results[QStringLiteral("resourceSlug")] = QVariant::fromValue(path.at(6));

        langResourceStats << results;

        langResourceStastsCounter--;

#ifdef QT_DEBUG
        qDebug() << langResourceStats;
        qDebug() << langResourceStastsCounter;
#endif

        if (langResourceStastsCounter == 0) {
            if (!langResourceStats.isEmpty()) {
                emit gotLangResourcesStats(langResourceStats);
            } else {
                emit gotLangResourcesStatsError(tr("Server reply was empty."));
            }
        }

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
