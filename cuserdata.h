#ifndef CUSERDATA_H
#define CUSERDATA_H
#include <QVariant>
#include "types.h"

class CUserData: public QVariant
{
    bool _is_empty;
public:
    CUserData();
    CUserData(QVariant val, bool is_empty);
    bool is_empty() const;
    void setIs_empty(bool is_empty);
    void clear_only_value();
    TCell user_type() const;
};

Q_DECLARE_METATYPE(CUserData)
Q_DECLARE_METATYPE(CUserData*)

#endif // CUSERDATA_H
