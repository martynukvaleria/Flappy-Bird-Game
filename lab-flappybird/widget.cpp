#include "widget.h"
#include "./ui_widget.h"
#include <QGraphicsPixmapItem>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget){
    ui->setupUi(this);

    scene = new Scene(this);
    scene->setSceneRect(-250,-300,500,600);

    QGraphicsPixmapItem * pixItem = new QGraphicsPixmapItem(QPixmap("/home/martynuk/Desktop/labs/lab-flappybird/images/game-back.png"));
    scene->addItem(pixItem);
    pixItem->setPos(QPointF(0,0)-QPointF(pixItem->boundingRect().width()/2,
                                         pixItem->boundingRect().height()/2));

    ui->graphicsView->setScene(scene);

    scene->addBird();
}

void Widget::on_startGameButton_clicked(){
    scene->startGame();
}

Widget::~Widget(){
    delete ui;
}



