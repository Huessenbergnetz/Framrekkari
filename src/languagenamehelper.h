#ifndef LANGUAGENAMEHELPER_H
#define LANGUAGENAMEHELPER_H

#include <QObject>
#include <QLocale>

class LanguageNameHelper : public QObject
{
    Q_OBJECT
public:
    explicit LanguageNameHelper(QObject *parent = 0);

    Q_INVOKABLE QString getLanguageName(const QString &lang);

signals:

public slots:

};

#endif // LANGUAGENAMEHELPER_H
