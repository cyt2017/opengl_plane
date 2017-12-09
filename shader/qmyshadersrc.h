#ifndef QMYSHADERSRC_H
#define QMYSHADERSRC_H

#include "qmyprogramid.h"

class QMyShaderSrc : public QMyProgramId
{
public:
    QMyShaderSrc();
    ~QMyShaderSrc();
public:
    typedef     int uniform;
    typedef     int attribute;


    virtual	void 	destroy();
    /**
    *   舒适化函数，做基本的OpenGL和应用程序直接的接口
    */
    virtual bool    initialize(){}
    /**
    *   使用程序
    */
    virtual void    begin(){}
    /**
    *   使用完成
    */
    virtual void    end(){}
};

#endif // QMYSHADERSRC_H
