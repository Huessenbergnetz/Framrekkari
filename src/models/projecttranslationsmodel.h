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

#ifndef PROJECTTRANSLATIONSMODEL_H
#define PROJECTTRANSLATIONSMODEL_H

#include <QAbstractTableModel>
#include <QMapIterator>
#include "../api/translationstringsapi.h"

class TranslationsObject;

class ProjectTranslationsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ProjectTranslationsModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex& = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

signals:
    void gotError(const QString &projectTranslationsModelErrorString);
    void gotStrings();
    void savedStringSuccess(const QVariantMap &changedData);

public slots:
    void refresh(const QString &project, const QString &resource, const QString &lang, int filter, int accountIdx);
    void saveString(const QString &project, const QString &resource, const QString &lang, const QVariantMap &translation, const QString &hash, const bool &reviewed, int modelIdx, int accountIdx);
    void clear();
    QVariantMap get(int modelIdx);

private slots:
    void populate(const QVariantList &data);
    void savedString(const QVariantMap &data);
    void errorHandler(const QString &errorString);

private:
    QList<TranslationsObject*> m_translations;

    static const int KeyRole;
    static const int ContextRole;
    static const int CommentRole;
    static const int SourceRole;
    static const int TranslationRole;
    static const int ReviewedRole;
    static const int PluralizedRole;
    static const int LastUpdateRole;
    static const int UserRole;
    static const int OccurrencesRole;
    static const int CharacterLimitRole;
    static const int TagsRole;

    TranslationStringsAPI tAPI;

};

#endif // PROJECTTRANSLATIONSMODEL_H
