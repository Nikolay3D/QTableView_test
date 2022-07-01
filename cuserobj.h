#ifndef CUSEROBJ_H
#define CUSEROBJ_H
#include <QString>
#include <QMap>
#include <QVariant>
#include "cuserdata.h"

class CUserObj
{
    QString _name;
    QMap<QString, CUserData> _data;
public:
    CUserObj(QString name = "default");
    CUserObj(QMap<QString, CUserData> data, QString name = "default");

    QString name() const;
    void append(QString key, CUserData val);
    void modify(QString key, CUserData val);
    void clear(QString key);
    QMap<QString, CUserData> data() const;

    bool key_in_obj(QString key) const;
};

#endif // CUSEROBJ_H
