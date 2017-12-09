#include "qmyshadersrc.h"

QMyShaderSrc::QMyShaderSrc()
{

}
QMyShaderSrc::~QMyShaderSrc()
{
    destroy();
}

void QMyShaderSrc::destroy()
{
    if (this->_fragment._shaderId)
    {
        glDeleteShader(this->_fragment._shaderId);
        this->_fragment._shaderId =   -1;
    }
    if (this->_vertex._shaderId)
    {
        glDeleteShader(this->_vertex._shaderId);
        this->_vertex._shaderId   =   -1;
    }
    if (this->_programId)
    {
        glDeleteProgram(this->_programId);
        this->_programId          =   -1;
    }
}
