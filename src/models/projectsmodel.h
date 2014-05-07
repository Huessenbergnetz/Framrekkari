#ifndef PROJECTSMODEL_H
#define PROJECTSMODEL_H

#include <QAbstractTableModel>
#include <QVariantMap>
#include "../api/projectsapi.h"

class ProjectObject;

class ProjectsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ProjectsModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex& = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

signals:
    void gotData(int projectCount);
    void gotError(const QString &projectsModelErrorString);

public slots:
    void refresh(int accountIdx, int start = 0, int end = 0);
    void clear();

private slots:
    void populate(QVariantList data);
    void errorHandler(const QString &errorString);

private:
    QList<ProjectObject*> m_projects;
    static const int SlugRole;
    static const int NameRole;
    static const int DescriptionRole;
    static const int SourceLanguageCodedRole;

    ProjectsAPI pAPI;
};

#endif // PROJECTSMODEL_H
