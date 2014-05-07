#ifndef TRANSLATIONSTRINGSAPI_H
#define TRANSLATIONSTRINGSAPI_H

#include <QObject>
#include "../network.h"
#include "apihelper.h"

class TranslationStringsAPI : public QObject
{
    Q_OBJECT
public:
    explicit TranslationStringsAPI(QObject *parent = 0);

    void getStrings(const QString &project, const QString &resource, const QString &lang, int accountIdx);

signals:
    void gotStrings(const QVariantList &translationStrings);
    void gotStringsError(const QString &gotStringsErrorString);

public slots:

private slots:
    void getStringsFinished(QNetworkReply *rep);

private:
    Network nm;
    APIHelper helper;

};

#endif // TRANSLATIONSTRINGSAPI_H
