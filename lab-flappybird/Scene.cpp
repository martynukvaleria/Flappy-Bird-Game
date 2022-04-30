#include "Scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>

Scene::Scene(QObject *parent) : QGraphicsScene(parent),
    gameOn(false),score(0), bestScore(0){
    setUpPillarTimer();
}

void Scene::addBird(){
    bird = new BirdItem(QPixmap("/home/martynuk/Desktop/labs/lab-flappybird/images/bird-up.png"));
    addItem(bird);
}

void Scene::startGame(){
    //bird
    bird->startFlying();
    //pillars
    if(!pillarTimer->isActive()){
        cleanPillars();
        setGameOn(true);
        setScore(0);
        hideGameOverGraphics();
        pillarTimer->start(1000);
    }
}

void Scene::setUpPillarTimer(){
    pillarTimer = new QTimer(this);
    connect(pillarTimer,&QTimer::timeout,[=](){

        PillarItem * pillarItem = new PillarItem();
        connect(pillarItem,&PillarItem::collideFail,[=](){
            pillarTimer->stop();
            freezeBirdAndPillarsInPlace();
            setGameOn(false);
            showGameOverGraphics();
        });

        addItem(pillarItem);
    });
}

void Scene::freezeBirdAndPillarsInPlace(){
    //bird
   bird->freezeInplace();
   //pillar
   QList<QGraphicsItem *> sceneItems = items();
   foreach (QGraphicsItem *item, sceneItems){
       PillarItem * pillar = dynamic_cast<PillarItem *>(item);
       if(pillar){
           pillar->freezeInPlace();
       }
   }

}

void Scene::setScore(int newScore){
    score = newScore;
}

void Scene::incrementScore(){
    score++;
    if(score > bestScore){
        bestScore = score;
        qDebug() << "Score : " << score << "Best score : " << bestScore;
    }
}

bool Scene::getGameOn() const{
    return gameOn;
}

void Scene::setGameOn(bool newGameOn){
    gameOn = newGameOn;
}

void Scene::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Space){
        if(gameOn){
            bird->shootUp();
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        if(gameOn){
            bird->shootUp();
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void Scene::showGameOverGraphics(){
    gameOverPix = new QGraphicsPixmapItem(QPixmap("/home/martynuk/Desktop/labs/lab-flappybird/images/game_over.jpg"));
    addItem(gameOverPix);
    gameOverPix->setPos(QPointF(0,0) - QPointF(gameOverPix->boundingRect().width()/2,
                                               gameOverPix->boundingRect().height()/2));
    scoreTextItem = new QGraphicsTextItem();

    QString htmlString = "<p> Score : " + QString::number(score) + "</p>"
            + "<p> Best Score : " + QString::number(bestScore) + "</p>";
    QFont mFont ("Consolas", 30, QFont::Bold);

    scoreTextItem->setHtml(htmlString);
    scoreTextItem->setFont(mFont);
    scoreTextItem->setDefaultTextColor(Qt::black);
    addItem(scoreTextItem);

    scoreTextItem->setPos(QPointF(0,0) - QPointF(scoreTextItem->boundingRect().width()/2,
                                               scoreTextItem->boundingRect().height()/2 + 180));
}

void Scene::hideGameOverGraphics(){
    if(gameOverPix){
        removeItem(gameOverPix);
        delete gameOverPix;
        gameOverPix = nullptr;
    }
    if(scoreTextItem){
        removeItem(scoreTextItem);
        delete scoreTextItem;
        scoreTextItem = nullptr;
    }
}

void Scene::cleanPillars(){
    QList<QGraphicsItem *> sceneItems = items();
    foreach (QGraphicsItem *item, sceneItems){
        PillarItem * pillar = dynamic_cast<PillarItem *>(item);
        if(pillar){
            removeItem(pillar);
            delete pillar;
        }
    }
}
