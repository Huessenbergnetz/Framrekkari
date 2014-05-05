#include "projectsmodel.h"
#include "projectobject.h"

const int ProjectsModel::SlugRole = Qt::UserRole + 1;
const int ProjectsModel::NameRole = Qt::UserRole + 2;
const int ProjectsModel::DescriptionRole = Qt::UserRole + 3;
const int ProjectsModel::SourceLanguageCodedRole = Qt::UserRole + 4;

ProjectsModel::ProjectsModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    connect(&pAPI, SIGNAL(gotProjects(QVariantList)), this, SLOT(populate(QVariantList)));
    connect(&pAPI, SIGNAL(gotProjectsError(QString)), this, SLOT(errorHandler(QString)));
}

QHash<int, QByteArray> ProjectsModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(SlugRole, QByteArray("slug"));
    roles.insert(NameRole, QByteArray("name"));
    roles.insert(DescriptionRole, QByteArray("description"));
    roles.insert(SourceLanguageCodedRole, QByteArray("sourceLanguageCode"));
    return roles;
}


int ProjectsModel::rowCount(const QModelIndex &) const
{
    return m_projects.size();
}

int ProjectsModel::columnCount(const QModelIndex&) const
{
    return 4;
}


QVariant ProjectsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant(); // Return Null variant if index is invalid

    if (index.row() > (m_projects.size()-1) )
        return QVariant();

    ProjectObject *pobj = m_projects.at(index.row());
    switch (role) {
    case Qt::DisplayRole: // The default display role now displays the first name as well
    case SlugRole:
        return QVariant::fromValue(pobj->slug);
    case NameRole:
        return QVariant::fromValue(pobj->name);
    case DescriptionRole:
        return QVariant::fromValue(pobj->description);
    case SourceLanguageCodedRole:
        return QVariant::fromValue(pobj->sourceLanguageCode);
    default:
        return QVariant();
    }
}


void ProjectsModel::refresh(int accountIdx, int start, int end)
{
    clear();

    pAPI.getProjects(accountIdx, start, end);
}


QModelIndex ProjectsModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
             return QModelIndex();

    return createIndex(row, column);
}


void ProjectsModel::populate(QVariantList data)
{
    int length = data.length();

    beginInsertRows(QModelIndex(), 0, length-1);

    for (int i = 0; i < data.length(); ++i)
    {
        QVariantMap map = data.at(i).toMap();
        ProjectObject *pobj = new ProjectObject(map["slug"].toString(), map["name"].toString(), map["description"].toString(), map["source_language_code"].toString());
        m_projects.append(pobj);
    }

    endInsertRows();

    emit gotData(length);
}


void ProjectsModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount()-1);

    m_projects.clear();

    endRemoveRows();
}


void ProjectsModel::errorHandler(const QString &errorString)
{
    emit gotError(errorString);
}
