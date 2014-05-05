#ifndef PROJECTMODEL_H
#define PROJECTMODEL_H

#include <QAbstractItemModel>
#include "../api/projectsapi.h"

class ProjectModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ProjectModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex& = QModelIndex()) const;
//    QHash<int, QByteArray> roleNames() const;
//    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

signals:

public slots:
    void refresh(int accountIdx, const QString &slug, bool details = true);

private:
    ProjectsAPI pAPI;

};

#endif // PROJECTMODEL_H
