#include "qmynodematrix.h"

QMyNodeMatrix::QMyNodeMatrix()
{
    _pos        =   CELL::float3(0,0,0);
    _scale      =   CELL::float3(1.0,1.0,1.0);
    _quat       =   CELL::quatr(0.0,0.0,0.0,1.0);
    _matModel   =   CELL::makeTransform(_pos,_scale,_quat);
    setSize(8,8);
}
