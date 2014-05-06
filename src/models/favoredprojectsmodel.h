#ifndef FAVOREDPROJECTSMODEL_H
#define FAVOREDPROJECTSMODEL_H

#include <QAbstractTableModel>

#include "../configuration.h"

class FavoredProjectObject;

class FavoredProjectsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit FavoredProjectsModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex& = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

    Q_INVOKABLE bool isFavored(const QString &slug, int accountIdx);

signals:

public slots:
    void append(const QString &name, const QString &slug, const QString &desc, const QString &srcLang, int accountIdx);
    void remove(const QString &slug, int accountIdx);
    void init(int accountIdx);

private:
    QList<FavoredProjectObject*> m_projects;
    static const int NameRole;
    static const int SlugRole;
    static const int DescRole;
    static const int SrcLangRole;
    static const int AccountIdxRole;

    Configuration config;

    void clear();

};

#endif // FAVOREDPROJECTSMODEL_H
