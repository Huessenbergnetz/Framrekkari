#include "languagenamehelper.h"

LanguageNameHelper::LanguageNameHelper(QObject *parent) :
    QObject(parent)
{
}


QString LanguageNameHelper::getLanguageName(const QString &lang)
{
    QLocale locale(lang);
    QString name;
    if (locale.language() != QLocale::C) {
        name = locale.nativeLanguageName();
        name[0] = name[0].toUpper();
    }

    if (name.isEmpty())
        name = lang;

    return name;
}
