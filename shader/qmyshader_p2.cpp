#include "qmyshader_p2.h"

QMyshader_P2::QMyshader_P2()
{
    _MVP        =   -1;
    _position   =   -1;
    _color      =   -1;
}

bool QMyshader_P2::initialize()
{
    const char* vs =
    {
        "uniform    mat4    _MVP;"
        "attribute  vec3    _position;"
        "attribute  vec3    _color;"

        "varying    vec3    _outColor;"

        "void main()"
        "{"
        "   _outColor   =   _color;"
        "   gl_Position =   _MVP * vec4(_position,1.0);"
        "}"
    };
    const char* ps =
    {
        "precision  lowp    float; "
        "varying    vec3    _outColor;"
        "void main()"
        "{"
        "   gl_FragColor   =   vec4(_outColor,1.0);"
        "}"
    };
    bool    res =   createProgram(vs,ps);
    if(res)
    {
        //!~需要注意变量的类型
        _position   =   glGetAttribLocation(_programId,"_position");
        _color      =   glGetAttribLocation(_programId,"_color");
        _MVP        =   glGetUniformLocation(_programId,"_MVP");
    }
    return  res;
}

void QMyshader_P2::begin()
{
    glUseProgram(_programId);
    glEnableVertexAttribArray(_position);
    glEnableVertexAttribArray(_color);
}

void QMyshader_P2::end()
{
    glDisableVertexAttribArray(_position);
    glDisableVertexAttribArray(_color);
    glUseProgram(0);
}
