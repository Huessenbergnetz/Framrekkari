#ifndef PROJECTRESOURCEOBJECT_H
#define PROJECTRESOURCEOBJECT_H

#include<QString>
#include<QDateTime>

class ProjectResourceObject {
public:
  ProjectResourceObject(const QString &resSlug, const double &trans, const double &untrans, const double &rev, const QDateTime &lup, const QString &lcommit):
    slug(resSlug),
    translated(trans),
    untranslated(untrans),
    reviewed(rev),
    lastUpdate(lup),
    lastCommiter(lcommit){}
  QString slug;
  double translated;
  double untranslated;
  double reviewed;
  QDateTime lastUpdate;
  QString lastCommiter;
};

#endif // PROJECTRESOURCEOBJECT_H
