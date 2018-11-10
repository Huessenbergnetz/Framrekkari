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

#ifndef PROJECTLANGSTATSMODEL_H
#define PROJECTLANGSTATSMODEL_H

#include <QAbstractListModel>
#include "../api/statisticsapi.h"

class LangstatObject;

class ProjectLangstatsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ProjectLangstatsModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;
    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const;

signals:
    void gotError(const QString &projectsModelErrorString);
    void gotData();
    void langStatsChanged(const QVariantMap &changedLangStats);

public slots:
    void refresh(const QString &projectSlug, const QVariantList &resources, int accountIdx);
    void updateTranslationCount(int idx, const QVariantMap &changed);
    void clear();

private slots:
    void populate(const QVariantMap &data);
    void errorHandler(const QString &errorString);

private:
    QList<LangstatObject*> m_stats;
    static const int LangRole;
    static const int TranslatedRole;
    static const int UntranslatedRole;
    static const int ReviewedRole;

    StatisticsAPI sAPI;

};

#endif // PROJECTLANGSTATSMODEL_H
