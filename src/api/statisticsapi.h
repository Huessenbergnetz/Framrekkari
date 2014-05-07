#ifndef STATISTICSAPI_H
#define STATISTICSAPI_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QStringList>
#include <QLocale>
#include "apihelper.h"
#include "../network.h"

class StatisticsAPI : public QObject
{
    Q_OBJECT
public:
    explicit StatisticsAPI(QObject *parent = 0);

    void getAllProjectLangStats(const QString & projectSlug, const QVariantList &resources, int accountIdx);
    Q_INVOKABLE void getLangResourcesStats(const QString &projectSlug, const QString &lang, const QVariantList &resources, int accountIdx);

signals:
    void gotAllProjectLangStats(const QVariantMap &projectStats);
    void gotAllProjectLangStatsError(const QString &gotAllProjectsLangStatsErrorString);
    void gotLangResourcesStats(const QVariantList &langStats);
    void gotLangResourcesStatsError(const QString &gotLangResourcesStatsErrorString);

public slots:

private slots:
    void getAllProjectLangStatsFinished(QNetworkReply *rep);
    void getLangResourcesStatsFinished(QNetworkReply *rep);

private:
    Network nm;
    APIHelper helper;


    QMap<QString, QVariant> projectLangStats;
    int projectLangStatsCounter;

    QVariantList langResourceStats;
    int langResourceStastsCounter;

};

#endif // STATISTICSAPI_H
