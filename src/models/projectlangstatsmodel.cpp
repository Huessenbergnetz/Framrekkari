#include "projectlangstatsmodel.h"
#include "langstatobject.h"

const int ProjectLangstatsModel::LangRole = Qt::UserRole + 1;
const int ProjectLangstatsModel::TranslatedRole = Qt::UserRole + 2;
const int ProjectLangstatsModel::UntranslatedRole = Qt::UserRole + 3;
const int ProjectLangstatsModel::ReviewedRole = Qt::UserRole + 4;
const int ProjectLangstatsModel::NameRole = Qt::UserRole + 5;

ProjectLangstatsModel::ProjectLangstatsModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    connect(&sAPI, SIGNAL(gotAllProjectLangStats(QVariantMap)), this, SLOT(populate(QVariantMap)));
    connect(&sAPI, SIGNAL(gotAllProjectLangStatsError(QString)), this, SLOT(errorHandler(QString)));
}

QHash<int, QByteArray> ProjectLangstatsModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(LangRole, QByteArray("lang"));
    roles.insert(TranslatedRole, QByteArray("translated"));
    roles.insert(UntranslatedRole, QByteArray("untranslated"));
    roles.insert(ReviewedRole, QByteArray("reviewed"));
    roles.insert(NameRole, QByteArray("name"));
    return roles;
}


int ProjectLangstatsModel::rowCount(const QModelIndex &) const
{
    return m_stats.size();
}

int ProjectLangstatsModel::columnCount(const QModelIndex&) const
{
    return 5;
}


QVariant ProjectLangstatsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant(); // Return Null variant if index is invalid

    if (index.row() > (m_stats.size()-1) )
        return QVariant();

    LangstatObject *sobj = m_stats.at(index.row());
    switch (role) {
    case Qt::DisplayRole: // The default display role now displays the first name as well
    case LangRole:
        return QVariant::fromValue(sobj->lang);
    case TranslatedRole:
        return QVariant::fromValue(sobj->translated);
    case UntranslatedRole:
        return QVariant::fromValue(sobj->untranslated);
    case ReviewedRole:
        return QVariant::fromValue(sobj->reviewed);
    case NameRole:
        return QVariant::fromValue(sobj->name);
    default:
        return QVariant();
    }
}


void ProjectLangstatsModel::refresh(const QString &projectSlug, const QVariantList &resources, int accountIdx)
{
    clear();

    sAPI.getAllProjectLangStats(projectSlug, resources, accountIdx);
}


QModelIndex ProjectLangstatsModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
             return QModelIndex();

    return createIndex(row, column);
}


void ProjectLangstatsModel::populate(const QVariantMap &data)
{
    int length = data.count();

    beginInsertRows(QModelIndex(), 0, length-1);

    QMapIterator<QString, QVariant> i(data);
    while (i.hasNext())
    {
        i.next();

        QVariantMap map = i.value().toMap();

        LangstatObject *sobj = new LangstatObject(i.key(), map.value("translated").toDouble(), map.value("untranslated").toDouble(), map.value("reviewed").toDouble(), map.value("name").toString());

        m_stats.append(sobj);
    }

    endInsertRows();
}


void ProjectLangstatsModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount()-1);

    m_stats.clear();

    endRemoveRows();
}


void ProjectLangstatsModel::errorHandler(const QString &errorString)
{
    emit gotError(errorString);
}
