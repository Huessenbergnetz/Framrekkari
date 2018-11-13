/*
    Framrekkari - Transifex Client for SailfishOS
    Copyright (C) 2014-2018  Hüssenbergnetz/Matthias Fehring
    https://github.com/Buschtrommel/Framrekkari

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

#include <QDebug>
#include "md5generator.h"

MD5generator::MD5generator(QObject *parent) :
    QObject(parent)
{
}


QString MD5generator::genMd5(const QString &entity, const QVariantList &context)
{
    QStringList keyList;
    keyList << entity;

    if (context.isEmpty()) {
        keyList << QString();
    } else {
        for (int i = 0; i < context.length(); ++i)
            keyList << context.at(i).toString();
    }

    QString keys = keyList.join(QLatin1Char(':'));

    qDebug() << keys;
    qDebug() << QString(QCryptographicHash::hash(keys.toUtf8(), QCryptographicHash::Md5).toHex());

    return QString(QCryptographicHash::hash(keys.toUtf8(), QCryptographicHash::Md5).toHex());
}
