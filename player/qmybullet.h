#ifndef QMYBULLET_H
#define QMYBULLET_H

#include "qmynodematrix.h"
#include "widget/qmytexture.h"

class QMyBullet : public QMyNodeMatrix
{
public:
    QMyBullet();
public:
    float           _speed;
    float           _maxDistance;
    CELL::float3    _dir;
    CELL::float3    _posSrc;
    QMyTexture      _texture;
public:
    void setSrcPosition(CELL::float3 pos)
    {
        _posSrc = pos;
        QMyNodeMatrix::setPosition(pos);
    }
    const CELL::float3 getSrcPosition()
    {
        return _posSrc;
    }
    void setDir(CELL::float3& dir)
    {
        _dir = dir;
    }
    const CELL::float3 getDir()
    {
        return _dir;
    }
    void setSpeed(float speed)
    {
        _speed = speed;
    }
    const float getSpeed()
    {
        return _speed;
    }
    void setMaxDistance(float maxDistance)
    {
        _maxDistance = maxDistance;
    }
    const float getMaxDistance()
    {
        return _maxDistance;
    }
    virtual bool isDead()
    {
        return  CELL::distance(_posSrc,_pos) >= _maxDistance;
    }

    virtual bool upDate(float time)
    {
        _pos += _dir * _speed * time;
        QMyNodeMatrix::upDate();
    }

};

#endif // QMYBULLET_H
