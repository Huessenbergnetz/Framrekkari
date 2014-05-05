#include "projectmodel.h"

ProjectModel::ProjectModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}


void ProjectModel::refresh(int accountIdx, const QString &slug, bool details)
{
    pAPI.getProject(accountIdx, slug, details);
}


QVariant ProjectModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}


int ProjectModel::rowCount(const QModelIndex &parent) const
{
    return 0;
}


int ProjectModel::columnCount(const QModelIndex &) const
{
    return 0;
}
