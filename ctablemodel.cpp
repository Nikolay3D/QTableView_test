#include "ctablemodel.h"
#include "ctest.h"


CTableModel::CTableModel(QObject *parent): QAbstractTableModel (parent)
{
    random_fill();
}

int CTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED( parent )
    return _headers_vertical.size();
}

int CTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED( parent )
    return _user_data.size();
}

QVariant CTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( role != Qt::DisplayRole ) {
        return QVariant();
    }

    if( orientation == Qt::Vertical ) {
        return _headers_vertical.at(section);
    }

    if( orientation == Qt::Horizontal ) {
        return _user_data.at(section).name();
    }

    return QVariant();
}

QVariant CTableModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        QString key = _headers_vertical.at(index.row());
        if(key_in_obj(index.column(), key)){
            if(_user_data.at(index.column()).data().value(key).is_empty()){
                return QString("[") + _user_data.at(index.column()).data().value(key).typeName() + "]";
            }else{
                return _user_data.at(index.column()).data().value(key);
            }
        }else{
            //qDebug() << "Key [" << key << "] not find in [" << _user_data.at(index.column()).name() << "]";
        }
    }

    if(role == Qt::EditRole)
    {
        QString key = _headers_vertical.at(index.row());
        if(key_in_obj(index.column(), key)){
            return QVariant::fromValue(_user_data.at(index.column()).data().value(key));
        }else{
            //qDebug() << "Key [" << key << "] not find in [" << _user_data.at(index.column()).name() << "]";
        }
    }

    return QVariant();
}

bool CTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == Qt::EditRole){
        QString key = _headers_vertical.at(index.row());
        CUserData cell_data = qvariant_cast<CUserData>(value);
        _user_data[index.column()].modify(key, cell_data);
        emit dataChanged(index, index);
        return true;
    }

    return false;
}

Qt::ItemFlags CTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags fl = Qt::NoItemFlags;

    QString key = _headers_vertical.at(index.row());
    if(key_in_obj(index.column(), key)){
        fl |= Qt::ItemIsEnabled | Qt::ItemIsEditable;
    }else{
        // нет объекта
    }

    return fl;
}

void CTableModel::random_fill()
{
    beginResetModel();

    _user_data = CTest::generate_data();
    calc_headers();

    endResetModel();
}

QStringList CTableModel::get_obj_info(int column)
{
    QStringList out;

    if(column < _user_data.size()){
        out << _user_data.at(column).name();

        foreach(QString key, _user_data.at(column).data().keys()){
            QVariant val = _user_data.at(column).data()[key];
            if(_user_data.at(column).data()[key].is_empty()){
                out << QString("[%1] [%2]: [empty]").arg(key).arg(val.typeToName(val.type()));
            }else{
                out << QString("[%1] [%2]: %3").arg(key).arg(val.typeToName(val.type())).arg(val.toString());
            }
        }
    }

    return out;
}

void CTableModel::clearData(const QModelIndex &index)
{
    QString key = _headers_vertical.at(index.row());
    _user_data[index.column()].clear(key);
}

void CTableModel::calc_headers()
{
    _headers_vertical.clear();

    QSet<QString> keys_set;
    foreach (CUserObj uo, _user_data) {
        QList<QString> obj_keys = uo.data().keys();
        QSet<QString> tmp(obj_keys.constBegin(), obj_keys.constEnd());
        keys_set.unite(tmp);
    }

    _headers_vertical = keys_set.values();
    std::sort(_headers_vertical.begin(), _headers_vertical.end());
}

bool CTableModel::key_in_obj(int obj_id, QString key) const
{
    return _user_data.at(obj_id).key_in_obj(key);
}
