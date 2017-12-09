#ifndef QMYWIDGET_H
#define QMYWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include "tool/CELLMath.hpp"
#include "qmytexture.h"
#include "qmyopengl.h"
#include "shader/qmyshader_p2uv.h"
#include "player/qmyplayer.h"

class QMyWidget : public QMyOpengl
{
public:
    QMyWidget(QWidget *parent = 0);

    float offset;
public:
    QMyShader_P2UV  _shader;
    QMyTexture      _texture;
    QMyPlayer       _player;
public:
    virtual bool init();
    virtual void onRender();
    void drawImage();


    bool eventFilter(QObject *target, QEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *ev);
    virtual void mousePressEvent(QMouseEvent *ev);
    virtual void mouseReleaseEvent(QMouseEvent *ev);
    virtual void wheelEvent(QWheelEvent *event){}
};

#endif // QMYWIDGET_H
