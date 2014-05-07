#ifndef TRANSLATIONSOBJECT_H
#define TRANSLATIONSOBJECT_H

#include <QString>
#include <QVariant>

class TranslationsObject {
public:
  TranslationsObject(const QString &keyString, const QVariantList &contextList, const QString &commentString, const QVariantMap &sourceMap, const QVariantMap &transMap, const bool &revBool, const bool &plur):
    key(keyString),
    context(contextList),
    comment(commentString),
    source(sourceMap),
    translation(transMap),
    reviewed(revBool),
    pluralized(plur){}
  QString key;
  QVariantList context;
  QString comment;
  QVariantMap source;
  QVariantMap translation;
  bool reviewed;
  bool pluralized;
};

#endif // TRANSLATIONSOBJECT_H
