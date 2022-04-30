#ifndef LAB_FLAPPYBIRD_BIRDITEM_H
#define LAB_FLAPPYBIRD_BIRDITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class BirdItem : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal y READ y WRITE setY)

public:

    explicit BirdItem(QPixmap pixmap);

    qreal rotation() const;

    qreal y() const;

    void shootUp();

    void startFlying();

    void freezeInplace();

signals:

public slots:

    void setRotation(qreal newRotation);
    void setY(qreal newY);
    void rotateTo(const qreal &end, const int& duration, const QEasingCurve& curve);
    void fallToGroundIfNecessary();

private:

    enum WingPosition{
        Up,
        Middle,
        Down
    };
    void updatePixmap();

    WingPosition wingPosition;
    bool wingDirection; // 0:down, 1:up

    qreal m_rotation;
    qreal m_y;

    QPropertyAnimation * yAnimation;
    QPropertyAnimation * rotationAnimation;

    qreal groundPosition;
};


#endif //LAB_FLAPPYBIRD_BIRDITEM_H
