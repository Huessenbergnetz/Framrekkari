#ifndef MD5GENERATOR_H
#define MD5GENERATOR_H

#include <QObject>
#include <QCryptographicHash>
#include <QStringList>
#include <QVariantList>

class MD5generator : public QObject
{
    Q_OBJECT
public:
    explicit MD5generator(QObject *parent = 0);

    Q_INVOKABLE QString genMd5(const QString &entity, const QVariantList &context);

signals:

public slots:

};

#endif // MD5GENERATOR_H
