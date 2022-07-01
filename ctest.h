#ifndef CTEST_H
#define CTEST_H
#include <cuserobj.h>
#include <QDebug>
#include "types.h"

class CTest
{
public:
    CTest();
    static QVector<CUserObj> generate_data();
};

#endif // CTEST_H
