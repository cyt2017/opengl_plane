#ifndef QMYNODEMATRIX_H
#define QMYNODEMATRIX_H

#include "tool/CELLMath.hpp"

class QMyNodeMatrix
{
public:
    CELL::float3    _pos;
    CELL::float3    _scale;
    CELL::quatr     _quat;
    CELL::matrix4   _matModel;
    CELL::float2    _size;
    CELL::aabbr     _aabb;

public:
     QMyNodeMatrix();

    void setPosition(CELL::float3& pos)
    {
        _pos  =   pos;
    }
    const CELL::float3 getPosition()
    {
        return _pos;
    }

    void setScale(CELL::float3& scale)
    {
        _scale  =   scale;
    }
    const CELL::float3 getScale()
    {
        return _scale;
    }

    void setQuatr(CELL::quatr& quatr)
    {
        _quat  =   quatr;
    }
    const CELL::quatr getQuatr()
    {
        return _quat;
    }
    const CELL::matrix4 getMatModel()
    {
        return _matModel;
    }

    void setSize(float w,float h)
    {
        _size = CELL::float2(w,h);
        CELL::float3   xmin = -CELL::float3(w*0.5,h*0.5,0);
        CELL::float3   xmax = CELL::float3(w*0.5,h*0.5,0);
        _aabb.setExtents(xmin,xmax);
        _aabb.transform(_matModel);
    }
    const CELL::float2 getSize()
    {
        return _size;
    }

    virtual void upDate()
    {
        _matModel = CELL::makeTransform(_pos,_scale,_quat);
        CELL::float3 minPos = -CELL::float3(_size.x*0.5,_size.y*0.5,0);
        CELL::float3 maxPos = CELL::float3(_size.x*0.5,_size.y*0.5,0);
        _aabb.setExtents(minPos,maxPos);
        _aabb.transform(_matModel);
    }

};

#endif // QMYNODEMATRIX_H
