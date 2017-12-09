#include "qmyprogramid.h"

QMyProgramId::QMyProgramId()
{
    _programId  =   -1;
}
bool QMyProgramId::createProgram(const char *vertex, const char *fragment)
{
    bool        error   =   false;
    do
    {
        if (vertex)
        {
            _vertex._shaderId   = glCreateShader( GL_VERTEX_SHADER );
            glShaderSource( _vertex._shaderId, 1, &vertex, 0 );
            glCompileShader( _vertex._shaderId );

            GLint   compileStatus;
            glGetShaderiv( _vertex._shaderId, GL_COMPILE_STATUS, &compileStatus );
            error   =   compileStatus == GL_FALSE;
            if( error )
            {
                GLchar messages[256];
                glGetShaderInfoLog( _vertex._shaderId, sizeof(messages), 0,messages);
                printf("error:%s\n",messages);
                assert( messages && 0 != 0);
                break;
            }
        }
        if (fragment)
        {
            _fragment._shaderId   = glCreateShader( GL_FRAGMENT_SHADER );
            glShaderSource( _fragment._shaderId, 1, &fragment, 0 );
            glCompileShader( _fragment._shaderId );

            GLint   compileStatus;
            glGetShaderiv( _fragment._shaderId, GL_COMPILE_STATUS, &compileStatus );
            error   =   compileStatus == GL_FALSE;

            if( error )
            {
                GLchar messages[256];
                glGetShaderInfoLog( _fragment._shaderId, sizeof(messages), 0,messages);
                assert( messages && 0 != 0);
                break;
            }
        }
        _programId  =   glCreateProgram( );

        if (_vertex._shaderId)
        {
            glAttachShader( _programId, _vertex._shaderId);
        }
        if (_fragment._shaderId)
        {
            glAttachShader( _programId, _fragment._shaderId);
        }

        glLinkProgram( _programId );

        GLint linkStatus;
        glGetProgramiv( _programId, GL_LINK_STATUS, &linkStatus );
        if (linkStatus == GL_FALSE)
        {
            GLchar messages[256];
            glGetProgramInfoLog( _programId, sizeof(messages), 0, messages);
            break;
        }
        glUseProgram(_programId);

    } while(false);

    if (error)
    {
        if (_fragment._shaderId)
        {
            glDeleteShader(_fragment._shaderId);
            _fragment._shaderId =   0;
        }
        if (_vertex._shaderId)
        {
            glDeleteShader(_vertex._shaderId);
            _vertex._shaderId   =   0;
        }
        if (_programId)
        {
            glDeleteProgram(_programId);
            _programId          =   0;
        }
    }
    return  true;
}

void QMyProgramId::begin()
{
    glUseProgram(_programId);
}

void QMyProgramId::end()
{
    glUseProgram(0);
}
