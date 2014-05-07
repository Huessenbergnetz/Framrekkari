#ifndef PROJECRESOURCESMODEL_H
#define PROJECRESOURCESMODEL_H

#include <QAbstractTableModel>
#include "../api/statisticsapi.h"

class ProjectResourceObject;

class ProjectResourcesModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ProjectResourcesModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex& = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

signals:
    void gotError(const QString &projectResourcesModelErrorString);

public slots:
    void refresh(const QString &projectSlug, const QString &lang, const QVariantList &resources, int accountIdx);

private slots:
    void populate(const QVariantList &data);
    void errorHandler(const QString &errorString);

private:
    QList<ProjectResourceObject*> m_resources;
    static const int SlugRole;
    static const int TranslatedRole;
    static const int UntranslatedRole;
    static const int ReviewedRole;
    static const int LastUpdateRole;
    static const int LastCommiterRole;

    StatisticsAPI sAPI;

    void clear();

};

#endif // PROJECRESOURCESMODEL_H
