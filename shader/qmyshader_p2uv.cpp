#include "qmyshader_p2uv.h"

QMyShader_P2UV::QMyShader_P2UV()
{
    _MVP        =   -1;
    _color      =   -1;
    _texture    =   -1;
    _position   =   -1;
    _uv         =   -1;
}

bool QMyShader_P2UV::initialize()
{
    const char* vs =
    {
        "uniform    mat4    _MVP;"
        "attribute  vec3    _position;"
        "attribute  vec2    _uv;"

        "varying    vec2    _outUV;"

        "void main()"
        "{"
        "   _outUV      =   _uv;"
        "   gl_Position =   _MVP * vec4(_position,1.0);"
        "}"
    };
    const char* ps =
    {
        "precision  lowp        float; "
        "uniform    sampler2D   _texture;"
        "uniform    vec4        _outColor;"
        "varying    vec2        _outUV;"
        "void main()"
        "{"
        "   vec4 color      =   texture2D(_texture,_outUV);"
        "   gl_FragColor    =   color + _outColor ;"
        "}"
    };
    bool    res =   createProgram(vs,ps);
    if(res)
    {
        //!~需要注意变量的类型
        _position   =   glGetAttribLocation(_programId,"_position");
        _uv         =   glGetAttribLocation(_programId,"_uv");
        _color      =   glGetUniformLocation(_programId,"_color");
        _texture    =   glGetUniformLocation(_programId,"_texture");
        _MVP        =   glGetUniformLocation(_programId,"_MVP");
    }
    return  res;
}

void QMyShader_P2UV::begin()
{
    glUseProgram(_programId);
    glEnableVertexAttribArray(_position);
    glEnableVertexAttribArray(_uv);
}

void QMyShader_P2UV::end()
{
    glDisableVertexAttribArray(_position);
    glDisableVertexAttribArray(_uv);
    glUseProgram(0);
}


