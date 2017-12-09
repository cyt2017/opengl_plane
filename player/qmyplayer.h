#ifndef QMYPLAYER_H
#define QMYPLAYER_H

#include <QObject>
#include <QMouseEvent>
#include <QTimer>
#include "widget/qmytexture.h"
#include "qmynodematrix.h"
#include "shader/qmyshader_p2uv.h"
#include "player/qmybullet.h"

class QMyPlayer : public QObject
{
    Q_OBJECT
public:
    explicit QMyPlayer(QObject *parent = 0);
    ~QMyPlayer();

public:
    int             _width;
    int             _height;
    QMyTexture      _texPlane;
    QMyTexture      _texBullet;
    QMyShader_P2UV  _shaderPlane;

    QMyNodeMatrix   _node;
    std::vector<QMyBullet*>  _bullet;
public:
    CELL::float2    _pos;
    bool            _leftB;
    QTimer          *timer;

public:
    virtual void initilize(int w, int h);
    virtual void onRender(CELL::matrix4 proj);

    virtual void mouseMoveEvent(QMouseEvent *ev);
    virtual void mousePressEvent(QMouseEvent *ev);
    virtual void mouseReleaseEvent(QMouseEvent *ev);
    virtual void wheelEvent(QWheelEvent *event){}

signals:

public slots:
    void onTimerout();
};

#endif // QMYPLAYER_H
