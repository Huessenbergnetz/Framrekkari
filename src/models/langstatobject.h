#ifndef LANGSTATOBJECT_H
#define LANGSTATOBJECT_H

#include<QString>

class LangstatObject {
public:
  LangstatObject(const QString &langCode, const double &trans, const double &untrans, const double &rev, const QString &langName):
    lang(langCode),
    translated(trans),
    untranslated(untrans),
    reviewed(rev),
    name(langName){}
  QString lang;
  double translated;
  double untranslated;
  double reviewed;
  QString name;
};

#endif // LANGSTATOBJECT_H
