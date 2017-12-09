#ifndef QMYSHADER_P2UV_H
#define QMYSHADER_P2UV_H

#include "qmyshadersrc.h"

class QMyShader_P2UV : public QMyShaderSrc
{
public:
    uniform     _MVP;
    uniform     _color;
    uniform     _texture;
    attribute   _position;
    attribute   _uv;

    virtual bool initialize();
    virtual void begin();
    virtual void end();
public:
    QMyShader_P2UV();
};

#endif // QMYSHADER_P2UV_H
