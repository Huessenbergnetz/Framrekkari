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

#ifndef TRANSLATIONSOBJECT_H
#define TRANSLATIONSOBJECT_H

#include <QString>
#include <QVariant>
#include <QDateTime>
#include <QVariantList>

class TranslationsObject {
public:
  TranslationsObject(const QString &keyString, const QVariantList &contextList, const QString &commentString, const QVariantMap &sourceMap, const QVariantMap &transMap, const bool &revBool, const bool &plur, const QDateTime &lUpdate, const QString &usr, const QString &occ, const int &charLim, const QVariantList &t, const int &dIdx):
    key(keyString),
    context(contextList),
    comment(commentString),
    source(sourceMap),
    translation(transMap),
    reviewed(revBool),
    pluralized(plur),
    lastUpdate(lUpdate),
    user(usr),
    occurrences(occ),
    characterLimit(charLim),
    tags(t),
    dataIndex(dIdx){}
  QString key;
  QVariantList context;
  QString comment;
  QVariantMap source;
  QVariantMap translation;
  bool reviewed;
  bool pluralized;
  QDateTime lastUpdate;
  QString user;
  QString occurrences;
  int characterLimit;
  QVariantList tags;
  int dataIndex;
};

#endif // TRANSLATIONSOBJECT_H
