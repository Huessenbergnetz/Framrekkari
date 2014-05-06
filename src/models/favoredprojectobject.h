#ifndef FAVOREDPROJECTOBJECT_H
#define FAVOREDPROJECTOBJECT_H

#include<QString>

class FavoredProjectObject {
public:
  FavoredProjectObject(const QString &nameString, const QString &slugString, const QString &descString, const QString &srcLangString, int accountIdxInt):
    name(nameString),
    slug(slugString),
    desc(descString),
    srcLang(srcLangString),
    accountIdx(accountIdxInt){}
  QString name;
  QString slug;
  QString desc;
  QString srcLang;
  int accountIdx;
};

#endif // FAVOREDPROJECTOBJECT_H
