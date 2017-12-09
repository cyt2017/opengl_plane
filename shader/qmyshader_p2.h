#ifndef QMYSHADER_P2_H
#define QMYSHADER_P2_H

#include "qmyshadersrc.h"

class QMyshader_P2 : public QMyShaderSrc
{
public:
    QMyshader_P2();

public:
    uniform     _MVP;
    attribute   _position;
    attribute   _color;

    virtual bool initialize();
    virtual void begin();
    virtual void end();
};

#endif // QMYSHADER_P2_H
