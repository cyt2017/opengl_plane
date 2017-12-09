#ifndef QMYPROGRAMID_H
#define QMYPROGRAMID_H

#include <stdio.h>
#include <assert.h>
#include <GLES2/gl2.h>

class    ShaderId
{
public:
    ShaderId()
    {
        _shaderId   =   -1;
    }
    int _shaderId;
};

class QMyProgramId
{
public:
    QMyProgramId();

public:
    int         _programId;
    ShaderId    _vertex;
    ShaderId    _fragment;

    bool createProgram( const char* vertex,const char* fragment );
    /**
    *   使用程序
    */
    virtual void    begin();
    /**
    *   使用完成
    */
    virtual void    end();
};

#endif // QMYPROGRAMID_H
