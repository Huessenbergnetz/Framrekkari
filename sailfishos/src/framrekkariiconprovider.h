/*
    Framrekkari - Transifex Client for SailfishOS
    Copyright (C) 2014-2018  Buschtrommel/Matthias Fehring
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

#ifndef FRAMREKKARIIMAGEPROVIDER_H
#define FRAMREKKARIIMAGEPROVIDER_H

#include <sailfishapp.h>
#include <QQuickImageProvider>
#include <QPainter>
#include <QColor>
#include <QStringBuilder>

class FramrekkariIconProvider : public QQuickImageProvider
{
public:
    FramrekkariIconProvider(const QString &basePath, qreal pixelRatio = 1.0, bool large = false) : QQuickImageProvider(QQuickImageProvider::Pixmap)
    {
        qreal nearestScale = 1.0;
        qreal lastDiff = 999.0;
        for (qreal currenScale : {1.0, 1.25, 1.5, 1.75, 2.0}) {
            qreal diff = currenScale - pixelRatio;
            if (diff < 0) {
                diff *= -1.0;
            }
            if (diff < lastDiff) {
                nearestScale = currenScale;
                lastDiff = diff;
            }
            if (lastDiff == 0.0) {
                break;
            }
        }
        m_iconsDir = basePath % QStringLiteral("/z") % QString::number(nearestScale) % (large ? QStringLiteral("-large/") : QStringLiteral("/"));

        qDebug("Constructing a new FramrekkariIconProvider object for a pixel ratio of %.2f on a %s screen. Input pixel ratio was %.2f Loading icons from \"%s\".", nearestScale, large ? "large" : "small", pixelRatio, qUtf8Printable(m_iconsDir));
    }

    ~FramrekkariIconProvider() override
    {
        qDebug("Deconstructing the FramrekkariIconProvider object.");
    }

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
    {
        const QStringList parts = id.split('?');
        const QString filePath = m_iconsDir % parts.at(0) % QStringLiteral(".png");
        QPixmap sourcePixmap(filePath);

        if (!sourcePixmap.isNull()) {

            if (size) {
                *size  = sourcePixmap.size();
            }

            if (parts.length() > 1 && QColor::isValidColor(parts.at(1))) {
                QPainter painter(&sourcePixmap);
                painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
                painter.fillRect(sourcePixmap.rect(), parts.at(1));
                painter.end();
            }

        }

        if (!sourcePixmap.isNull() && requestedSize.width() > 0 && requestedSize.height() > 0 && sourcePixmap.size() != requestedSize) {
            return sourcePixmap.scaled(requestedSize.width(), requestedSize.height(), Qt::IgnoreAspectRatio);
        } else {
            return sourcePixmap;
        }
    }

private:
    QString m_iconsDir;
};

#endif // FRAMREKKARIIMAGEPROVIDER_H
