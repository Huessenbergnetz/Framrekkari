#ifndef PROJECTTRANSLATIONSMODEL_H
#define PROJECTTRANSLATIONSMODEL_H

#include <QAbstractTableModel>
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

public slots:
    void refresh(const QString &project, const QString &resource, const QString &lang, int accountIdx);
    void saveString(const QString &project, const QString &resource, const QString &lang, const QVariantMap &translation, const QString &hash, int modelIdx, int accountIdx);
    void clear();

private slots:
    void populate(const QVariantList &data);
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

    TranslationStringsAPI tAPI;

};

#endif // PROJECTTRANSLATIONSMODEL_H
