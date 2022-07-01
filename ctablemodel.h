#ifndef CTABLEMODEL_H
#define CTABLEMODEL_H
#include <QAbstractTableModel>
#include "cuserobj.h"
#include <QSet>

class CTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    CTableModel( QObject* parent = nullptr);

    int rowCount( const QModelIndex& parent = QModelIndex()) const;
    int columnCount( const QModelIndex& parent = QModelIndex()) const;
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    QVariant data( const QModelIndex& index, int role ) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags( const QModelIndex& index ) const;

    void random_fill();
    QStringList get_obj_info(int column);
    void clearData(const QModelIndex &index);
private:
    QVector<CUserObj> _user_data;
    QList<QString> _headers_vertical;   // keys

    void calc_headers();
    bool key_in_obj(int obj_id, QString key) const;
};

#endif // CTABLEMODEL_H
