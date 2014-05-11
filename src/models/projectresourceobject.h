/*
    Framrekkari - Transifex Client for SailfishOS
    Copyright (C) 2014  Buschtrommel/Matthias Fehring
    Contact: Matthias Fehring <kontakt@buschmann23.de>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

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
