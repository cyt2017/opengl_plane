#ifndef QMYTEXTURE_H
#define QMYTEXTURE_H

#include <FreeImage.h>
#define MESA_EGL_NO_X11_HEADERS
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <QString>

class QMyTexture
{
public:
    QMyTexture();

    unsigned int _texId;
    int     _width ;
    int     _height;

    unsigned int loadTexture(const char *fileName);

    unsigned int createTexture(int width, int height);

    unsigned int loadTextureMipmap(std::vector<QString> fName);
};

#endif // QMYTEXTURE_H
