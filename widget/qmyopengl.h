#ifndef QMYOPENGL_H
#define QMYOPENGL_H

#include <QWidget>
#define MESA_EGL_NO_X11_HEADERS
#include <EGL/egl.h>
#include <GLES2/gl2.h>

class QMyOpengl : public QWidget
{
    Q_OBJECT
public:
    explicit QMyOpengl(QWidget *parent = 0);
    ~QMyOpengl();

public:
    //! 窗口的高度
    int         _width;
    //! 窗口的宽度
    int         _height;
    /// for gles2.0
    EGLConfig   _config;
    EGLSurface  _surface;
    EGLContext  _context;
    EGLDisplay  _display;

    QObject *parent;


public:
    virtual bool init();
    bool initOpenGLES20();
    void destroyOpenGLES20();

signals:

public slots:
};

#endif // QMYOPENGL_H
