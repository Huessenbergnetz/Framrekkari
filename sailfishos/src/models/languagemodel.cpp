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

#include "languagemodel.h"
#include <QDir>
#include <QFileInfo>
#ifndef CLAZY
#include <sailfishapp.h>
#endif

const int LanguageModel::NameRole = Qt::UserRole + 1;
const int LanguageModel::ValueRole = Qt::UserRole + 2;

LanguageModel::LanguageModel(QObject *parent) :
    QAbstractListModel(parent)
{
#ifndef CLAZY
    const QDir transDir(SailfishApp::pathTo(QStringLiteral("translations")).toString(QUrl::RemoveScheme));
#else
    const QDir transDir;
#endif

    const QFileInfoList files = transDir.entryInfoList(QStringList(QStringLiteral("framrekkari_*.qm")), QDir::Files);

    for (const QFileInfo &file : files) {
        const QString base = file.baseName();
        const int underScoreIdx = base.indexOf(QLatin1Char('_'));
        if (underScoreIdx > -1) {
            const QString lc = base.right(base.length() - underScoreIdx -1 );
            qDebug("Adding %s to the list of app translations.", qUtf8Printable(lc));
            m_langs << lc;
        }
    }
}


QHash<int, QByteArray> LanguageModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(NameRole, QByteArrayLiteral("name"));
    roles.insert(ValueRole, QByteArrayLiteral("value"));
    return roles;
}



int LanguageModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_langs.size();
}


QVariant LanguageModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() > rowCount()-1)
        return QVariant();

    QString value = m_langs.at(index.row());
    switch(role) {
    case NameRole:
        return QVariant::fromValue(langHelper.getLanguageName(value));
    case ValueRole:
        return QVariant::fromValue(value);
    default:
        return QVariant();
    }
}


QModelIndex LanguageModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
             return QModelIndex();

    return createIndex(row, column);
}
