#include "cuserobj.h"
#include <QDebug>

QString CUserObj::name() const
{
    return _name;
}

void CUserObj::append(QString key, CUserData val)
{
    _data.insert(key, val);
}

void CUserObj::modify(QString key, CUserData val)
{
    if(key_in_obj(key)){
        _data[key] = val;
    }
    else{
        qWarning() << Q_FUNC_INFO << "key not found";
    }
}

void CUserObj::clear(QString key)
{
    if(key_in_obj(key)){
        _data[key].clear_only_value();
    }
    else{
        qWarning() << Q_FUNC_INFO << "key not found";
    }
}

QMap<QString, CUserData> CUserObj::data() const
{
    return _data;
}

bool CUserObj::key_in_obj(QString key) const
{
    return -1 != _data.keys().indexOf(key);
}

CUserObj::CUserObj(QString name):
    _name(name)
{

}

CUserObj::CUserObj(QMap<QString, CUserData> data, QString name):
    _name(name), _data(data)
{

}
