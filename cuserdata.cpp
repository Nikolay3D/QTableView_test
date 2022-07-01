#include "cuserdata.h"


bool CUserData::is_empty() const
{
    return _is_empty;
}

void CUserData::setIs_empty(bool is_empty)
{
    _is_empty = is_empty;
}

void CUserData::clear_only_value()
{

    setIs_empty(true);

    TCell type = user_type();
    if(TCELL_DOUBLE == type){
        setValue(double(0.0));
    }else if(TCELL_BOOL == type){
        setValue(false);
    }else if(TCELL_STR == type){
        setValue(QString(""));
    }
}

TCell CUserData::user_type() const
{
    if(this->QVariant::type() == Double){ return TCell::TCELL_DOUBLE; }
    if(this->QVariant::type() == Bool){ return TCell::TCELL_BOOL; }
    if(this->QVariant::type() == String){ return TCell::TCELL_STR; }

    return TCell::TCELL_NONE;
}

CUserData::CUserData()
    : QVariant()
    , _is_empty(true)
{

}

CUserData::CUserData(QVariant val, bool empty)
    : QVariant(val)
    , _is_empty(empty)
{

}
