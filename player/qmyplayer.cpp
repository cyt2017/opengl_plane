#include "qmyplayer.h"

QMyPlayer::QMyPlayer(QObject *parent) : QObject(parent)
{
    _leftB = false;
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimerout()));
    timer->start(30);
}

QMyPlayer::~QMyPlayer()
{
    if(timer)
    {
        timer->deleteLater();
    }
}

void QMyPlayer::initilize(int w,int h)
{
    _width  =   w;
    _height =   h;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    _texPlane._texId = _texPlane.loadTexture("/home/cty/workspace/OPENGL/opengl_Together/Lesson01/build/image/plane1.png");
    _node.setSize(_texPlane._width,_texPlane._height);
    CELL::float3 pos(100,100,0);
    _node.setPosition(pos);
    _node.upDate();
    _shaderPlane.initialize();
}



void QMyPlayer::onRender(CELL::matrix4 proj)
{
    struct Vertex
    {
        float x,y,z;
        float u,v;
    };

    CELL::matrix4 matMvp = proj * _node.getMatModel();

    CELL::float2    halfData = CELL::float2(_node.getSize().x*0.5,_node.getSize().y*0.5);
    CELL::float3    minPos   = -CELL::float3(halfData.x,halfData.y,0);
    CELL::float3    maxPos   = CELL::float3(halfData.x,halfData.y,0);

    Vertex pos[]=
    {
        {minPos.x,minPos.y,0.0, 0.0,0.0},
        {maxPos.x,minPos.y,0.0, 1.0,0.0},
        {minPos.x,maxPos.y,0.0, 0.0,1.0},
        {maxPos.x,maxPos.y,0.0, 1.0,1.0}
    };

    _shaderPlane.begin();
    {
        glBindTexture(GL_TEXTURE_2D,_texPlane._texId);

        glUniformMatrix4fv(_shaderPlane._MVP,1,false,matMvp.data());
        glUniform4f(_shaderPlane._color,1.0,1.0,1.0,1.0);
        glUniform1i(_shaderPlane._texture,0);
        glVertexAttribPointer(_shaderPlane._position,3,GL_FLOAT,false,sizeof(Vertex),&pos[0].x);
        glVertexAttribPointer(_shaderPlane._uv,2,GL_FLOAT,false,sizeof(Vertex),&pos[0].u);

        glDrawArrays(GL_TRIANGLE_STRIP,0,4);

        std::vector<QMyBullet*>::iterator itr = _bullet.begin();
        for ( ;itr != _bullet.end() ; )
        {
            QMyBullet* bullet  =   *itr;
            if (bullet->isDead())
            {
                itr =   _bullet.erase(itr);
                delete  bullet;
                continue;
            }
            else
            {
                ++itr;
            }
//            static float angle = 1.0f;
            bullet->upDate(2);
//            angle += 1.0;

            CELL::float2    halfSz  =   bullet->getSize() * 0.5f;

            CELL::float3    vMin    =   -CELL::float3(halfSz.x,halfSz.y,0);
            CELL::float3    vMax    =   CELL::float3(halfSz.x,halfSz.y,0);

            Vertex vert[]   =
            {
                {   vMin.x,vMin.y,0.0,    0,0},
                {   vMax.x,vMin.y,0.0,    1,0},
                {   vMin.x,vMax.y,0.0,    0,1},
                {   vMax.x,vMax.y,0.0,    1,1},
            };

            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D,bullet->_texture._texId);
            matMvp     =   proj * bullet->getMatModel();
            glUniformMatrix4fv(_shaderPlane._MVP, 1, false, matMvp.data());
            glUniform1i(_shaderPlane._texture,1);
            glVertexAttribPointer(_shaderPlane._position,  3,  GL_FLOAT,   false,  sizeof(Vertex),vert);
            glVertexAttribPointer(_shaderPlane._uv,        2,  GL_FLOAT,   false,  sizeof(Vertex),&vert[0].u);

            glDrawArrays(GL_TRIANGLE_STRIP,0,4);
        }
    }
    _shaderPlane.end();
}


void QMyPlayer::mouseMoveEvent(QMouseEvent *ev)
{
    if(_leftB)
    {
        CELL::float3 offset = CELL::float3(float(ev->pos().x())-_pos.x,float(ev->pos().y())-_pos.y,0);
        CELL::float3 pos = CELL::float3(_node.getPosition().x+offset.x,_node.getPosition().y+offset.y,0);
        _node.setPosition(pos);
        _node.upDate();
        _pos = CELL::float2(ev->pos().x(),ev->pos().y());
    }
}

void QMyPlayer::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton && _node._aabb.contains(CELL::float3(ev->pos().x(),ev->pos().y(),0)))
    {
        _pos    = CELL::float2(ev->pos().x(),ev->pos().y());
        _leftB  = true;
    }
}

void QMyPlayer::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        _leftB = false;
    }
}

void QMyPlayer::onTimerout()
{
    QMyBullet* bullet = new QMyBullet();
    CELL::float3 dir(0.0,-1.0,0.0);
    bullet->setDir(dir);
    bullet->setMaxDistance(400.0);
    bullet->_texture._texId = _texBullet.loadTexture("/home/cty/workspace/OPENGL/opengl_Together/Lesson01/build/image/planebullet3.png");
    bullet->setSize(float(_texBullet._width),float(_texBullet._height));
    bullet->setSpeed(8.0);
    bullet->setSrcPosition(_node.getPosition());
    _bullet.push_back(bullet);
}


