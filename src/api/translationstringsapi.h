#ifndef TRANSLATIONSTRINGSAPI_H
#define TRANSLATIONSTRINGSAPI_H

#include <QObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include "../network.h"
#include "apihelper.h"

class TranslationStringsAPI : public QObject
{
    Q_OBJECT
public:
    explicit TranslationStringsAPI(QObject *parent = 0);

    void getStrings(const QString &project, const QString &resource, const QString &lang, int accountIdx);
    void saveString(const QString &project, const QString &resource, const QString &lang, const QVariantMap &translation, const QString &hash, int modelIdx, int accountIdx);

signals:
    void gotStrings(const QVariantList &translationStrings);
    void gotStringsError(const QString &gotStringsErrorString);
    void savedString(const QVariantMap &savedStrings);
    void savedStringError(const QString &savedStringErrorString);

public slots:

private slots:
    void getStringsFinished(QNetworkReply *rep);
    void saveStringFinished();

private:
    Network nm;
    APIHelper helper;

    QVariantMap transToSave;
    QNetworkReply *saveStringReply;


};

#endif // TRANSLATIONSTRINGSAPI_H
