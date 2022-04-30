#ifndef LAB_FLAPPYBIRD_SCENE_H
#define LAB_FLAPPYBIRD_SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include "PillarItem.h"
#include "BirdItem.h"

class Scene : public QGraphicsScene{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    void addBird();

    void startGame();

    bool getGameOn() const;
    void setGameOn(bool newGameOn);

    void incrementScore();

    void setScore(int newScore);

signals:

public slots:

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    void showGameOverGraphics();
    void hideGameOverGraphics();
    void cleanPillars();
    void setUpPillarTimer();
    void freezeBirdAndPillarsInPlace();


    QTimer * pillarTimer;
    BirdItem * bird;
    bool gameOn;
    int score;
    int bestScore;

    QGraphicsPixmapItem * gameOverPix;
    QGraphicsTextItem * scoreTextItem;


    // QGraphicsScene interface

};

#endif //LAB_FLAPPYBIRD_SCENE_H
