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

#ifndef PROJECTTRANSLATIONSMODEL_H
#define PROJECTTRANSLATIONSMODEL_H

#include <QAbstractListModel>
#include <QMapIterator>
#include "../api/translationstringsapi.h"

class TranslationsObject;

class ProjectTranslationsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString search READ search WRITE setSearch NOTIFY searchChanged)
    Q_PROPERTY(QVariantList modelData READ modelData WRITE setModelData NOTIFY modelDataChanged)
    Q_PROPERTY(int searchTarget READ searchTarget WRITE setSearchTarget NOTIFY searchTargetChanged)
public:
    explicit ProjectTranslationsModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;
    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const;

    QString search() const;
    QVariantList modelData() const;
    int searchTarget() const;

signals:
    void gotError(const QString &projectTranslationsModelErrorString);
    void gotStrings();
    void savedStringSuccess(const QVariantMap &changedData);

    void searchChanged(const QString &nSearch);
    void modelDataChanged(const QVariantList &nModelData);
    void searchTargetChanged(int nSearchTarget);

public slots:
    void refresh(const QString &project, const QString &resource, const QString &lang, int filter, int accountIdx);
    void saveString(const QString &project, const QString &resource, const QString &lang, const QVariantMap &translation, const QString &hash, bool reviewed, int modelIdx, int dataIndex, int accountIdx);
    void clear();
    QVariantMap get(int modelIdx);

    void setSearch(const QString &nSearch);
    void setModelData(const QVariantList &nModelData);
    void setSearchTarget(int nSearchTarget);

private slots:
    void populate();
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
    static const int DataIndexRole;

    TranslationStringsAPI tAPI;

    QString m_search;
    QVariantList m_modelData;
    QVariantList m_filteredModelData;
    int m_searchTarget;

};

#endif // PROJECTTRANSLATIONSMODEL_H
