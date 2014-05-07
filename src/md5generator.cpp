#include <QDebug>
#include "md5generator.h"

MD5generator::MD5generator(QObject *parent) :
    QObject(parent)
{
}


QString MD5generator::genMd5(const QString &entity, const QVariantList &context)
{
    QCryptographicHash md5(QCryptographicHash::Md5);

    md5.addData(entity.toUtf8());

    if (context.isEmpty()) {
        md5.addData("");
    } else {
        for (int i = 0; i < context.length(); ++i)
        {
            md5.addData(context.at(i).toString().toUtf8());
        }
    }

#ifdef QT_DEBUG
    qDebug() << entity;
    qDebug() << context;
    qDebug() << QString(md5.result().toHex());
#endif

    return QString(md5.result().toHex());



//    QStringList keys(entity);

//    if (context.isEmpty())
//    {
//        keys << "";
//    } else {
//        for (int i = 0; i < context.length(); ++i)
//        {
//            keys << context.at(i).toString();
//        }
//    }

//    QString keyString = keys.join("");


//#ifdef QT_DEBUG
//    qDebug() << keys;
//    qDebug() << keyString;
//    qDebug() << QString(QCryptographicHash::hash(keyString.toUtf8(), QCryptographicHash::Md5).toHex());
//#endif

//    return QString(QCryptographicHash::hash(keyString.toUtf8(), QCryptographicHash::Md5).toHex());
}
