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

#ifndef LANGUAGEMODELFILTER_H
#define LANGUAGEMODELFILTER_H

#include <QSortFilterProxyModel>
#include "languagemodel.h"

class LanguageModelFilter : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString search READ search WRITE setSearch NOTIFY searchChanged)
public:
    explicit LanguageModelFilter(QObject *parent = 0);

    QString search() const;

signals:
    void searchChanged(const QString &nSearch);

public slots:
    void setSearch(const QString &nSearch);

private:
    QString m_search;

    LanguageModel m_sourceModel;

};

#endif // LANGUAGEMODELFILTER_H
