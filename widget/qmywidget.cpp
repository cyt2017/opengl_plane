#include "qmywidget.h"

QMyWidget::QMyWidget(QWidget *parent):QMyOpengl(parent)
{

}
bool QMyWidget::init()
{
    QMyOpengl::init();
    printf("QMyDevice::init\n");
    _shader.initialize();
    _texture._texId = _texture.loadTexture("/home/cty/workspace/OPENGL/opengl_Together/Lesson01/build/image/main.jpg");
    _player.initilize(_width,_height);
}

void QMyWidget::onRender()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glViewport(0,0,_width,_height);

    struct Vertex
    {
        CELL::float3    vert;
        CELL::float2    uv;
    };

    _shader.begin();
    {
        //! 创建一个投影矩阵
        CELL::matrix4   screenProj  =   CELL::ortho<float>(0,float(_width),float(_height),0,-100.0f,100);

        float pX =   _width;
        float pY =   _height;
        offset  += 20.0f;
        Vertex  pos[]   =
        {
            CELL::float3(0,     0 ,  0.0),   CELL::float2(0.0,0.0+offset),
            CELL::float3(pX,    0 ,  0.0),   CELL::float2(1.0,0.0+offset),
            CELL::float3(0,     pY, 0.0),    CELL::float2(0.0,1.0+offset),
            CELL::float3(pX,    pY, 0.0),    CELL::float2(1.0,1.0+offset),
        };
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,_texture._texId);

        glUniform1i(_shader._texture,0);
        glUniformMatrix4fv(_shader._MVP, 1, false, screenProj.data());
        glUniform4f(_shader._color,1.0f,1.0f,1.0f,1.0f);
        glVertexAttribPointer(_shader._position,3,GL_FLOAT,false,sizeof(Vertex),&pos[0].vert.x);
        glVertexAttribPointer(_shader._uv,2,GL_FLOAT,false,sizeof(Vertex),&pos[0].uv.x);
        glDrawArrays(GL_TRIANGLE_STRIP,0,4);

        _player.onRender(screenProj);
    }
    _shader.end();
}

void QMyWidget::drawImage()
{
    onRender();
    eglSwapBuffers(_display,_surface);
}

bool QMyWidget::eventFilter(QObject *target, QEvent *event)
{
    if( target == parent )
     {
         if( event->type() == QEvent::KeyPress )
         {
             QKeyEvent *ke = (QKeyEvent *) event;
             keyPressEvent(ke);
          }
         if( event->type() == QEvent::MouseTrackingChange )
         {
             QMouseEvent *mouse = (QMouseEvent *) event;
             mouseMoveEvent(mouse);
             mousePressEvent(mouse);
             mouseReleaseEvent(mouse);
             QWheelEvent *wheel = (QWheelEvent *) event;
             wheelEvent(wheel);
         }
     }
    return true;
}

void QMyWidget::mouseMoveEvent(QMouseEvent *ev)
{
    _player.mouseMoveEvent(ev);
}

void QMyWidget::mousePressEvent(QMouseEvent *ev)
{
    _player.mousePressEvent(ev);
}

void QMyWidget::mouseReleaseEvent(QMouseEvent *ev)
{
    _player.mouseReleaseEvent(ev);
}
