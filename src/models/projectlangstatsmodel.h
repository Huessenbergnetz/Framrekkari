#ifndef PROJECTLANGSTATSMODEL_H
#define PROJECTLANGSTATSMODEL_H

#include <QAbstractTableModel>
#include "../api/statisticsapi.h"

class LangstatObject;

class ProjectLangstatsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ProjectLangstatsModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex& = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

signals:
    void gotError(const QString &projectsModelErrorString);

public slots:
    void refresh(const QString &projectSlug, const QVariantList &resources, int accountIdx);

private slots:
    void populate(const QVariantMap &data);
    void errorHandler(const QString &errorString);

private:
    QList<LangstatObject*> m_stats;
    static const int LangRole;
    static const int TranslatedRole;
    static const int UntranslatedRole;
    static const int ReviewedRole;
    static const int NameRole;

    StatisticsAPI sAPI;

    void clear();

};

#endif // PROJECTLANGSTATSMODEL_H
