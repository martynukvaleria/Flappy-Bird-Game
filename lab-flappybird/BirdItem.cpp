#include "BirdItem.h"
#include <QTimer>
#include <QGraphicsScene>

BirdItem::BirdItem(QPixmap pixmap) :
    wingPosition(WingPosition::Up),
    wingDirection(0){
    setPixmap(pixmap);

    QTimer *birdWingstimer = new QTimer(this);
    connect(birdWingstimer, &QTimer::timeout,[=](){
        updatePixmap();
    });
    birdWingstimer->start(80);

    groundPosition = scenePos().y() + 200;

    yAnimation = new QPropertyAnimation(this, "y", this);
    yAnimation->setStartValue(scenePos().y());
    yAnimation->setEndValue(groundPosition);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);

    rotationAnimation = new QPropertyAnimation(this,"rotation",this);
}

void BirdItem::updatePixmap(){
   if(wingPosition == WingPosition::Middle){
       if(wingDirection){
           //up
           setPixmap(QPixmap("/home/martynuk/Desktop/labs/lab-flappybird/images/bird-up.png"));
           wingPosition = WingPosition::Up;
           wingDirection = 0;
       }else{
           //down
           setPixmap(QPixmap("/home/martynuk/Desktop/labs/lab-flappybird/images/bird-down.png"));
           wingPosition = WingPosition::Down;
           wingDirection = 1;
       }
   }else{
       setPixmap(QPixmap("/home/martynuk/Desktop/labs/lab-flappybird/images/bird-middle.png"));
       wingPosition = WingPosition::Middle;
   }
}

qreal BirdItem::rotation() const{
    return m_rotation;
}

qreal BirdItem::y() const{
    return m_y;
}

void BirdItem::shootUp(){
    yAnimation->stop();
    rotationAnimation->stop();

    qreal curPosY = y();

    yAnimation->setStartValue(curPosY);
    yAnimation->setEndValue(curPosY - scene()->sceneRect().height()/8);
    yAnimation->setEasingCurve(QEasingCurve::OutQuad);
    yAnimation->setDuration(285);

    connect(yAnimation,&QPropertyAnimation::finished,[=](){
        fallToGroundIfNecessary();
    });

    yAnimation->start();

    rotateTo(-20,200, QEasingCurve::OutCubic);
}

void BirdItem::startFlying(){
    yAnimation->start();
    rotateTo(90,1200,QEasingCurve::InQuad);
}

void BirdItem::freezeInplace(){
    yAnimation->stop();
    rotationAnimation->stop();
}

void BirdItem::setRotation(qreal rotation){
    m_rotation = rotation;

    QPointF c = boundingRect().center();

    QTransform t;
    t.translate(c.x(),c.y());
    t.rotate(rotation);
    t.translate(-c.x(),-c.y());
    setTransform(t);
}

void BirdItem::setY(qreal y){
    moveBy(0,y-m_y);
    m_y = y;

}

void BirdItem::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve){
    rotationAnimation->setStartValue(rotation());
    rotationAnimation->setEndValue(end);
    rotationAnimation->setEasingCurve(curve);
    rotationAnimation->setDuration(duration);

    rotationAnimation->start();
}

void BirdItem::fallToGroundIfNecessary(){
    if(y() < groundPosition){
        rotationAnimation->stop();
        yAnimation->stop();

        yAnimation->setStartValue(y());
        yAnimation->setEndValue(groundPosition);
        yAnimation->setEasingCurve(QEasingCurve::OutQuad);
        yAnimation->setDuration(1300);
        yAnimation->start();

        rotateTo(90,600,QEasingCurve::InCubic);
    }
}


