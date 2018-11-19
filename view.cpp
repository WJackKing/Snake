#include "view.h"
#include <stdlib.h>
#include <QDebug>

View::View()
{
    direction = 0;
    speed = 100;
    is_stop = false;
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 500, 500);

    Snake *s = new Snake();
    snake.append(s);
    scene->addItem(snake.at(0));

    egg = new Egg();
    egg->setPos((rand() % 50) * 10, (rand() % 50) * 10);
    scene->addItem(egg);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(speed);

    this->resize(502, 502);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setScene(scene);
}

void View::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Right) {
        direction = 0;
    }else if (event->key() == Qt::Key_Left) {
        direction = 1;
    }else if (event->key() == Qt::Key_Down) {
        direction = 2;
    }else if (event->key() == Qt::Key_Up) {
        direction = 3;
    }else if (event->key() == Qt::Key_Space) {
        if(is_stop){
            timer->start(speed);
            is_stop = false;
        }else{
            timer->stop();
            is_stop = true;
        }
    }
}

void View::new_egg()
{
    egg->setPos((rand() % 50) * 10, (rand() % 50) * 10);
}

bool View::is_eat()
{
    if(snake.at(0)->x() == egg->x() && snake.at(0)->y() == egg->y()) {
        return true;
    }else{
        return false;
    }
}

void View::move()
{
    Snake *new_s = new Snake();
    new_s->setPos(snake.last()->x(), snake.last()->y());
    for(int i = snake.length() - 1; i > 0; i--){
        snake.at(i)->setPos(snake.at(i - 1)->x(), snake.at(i - 1)->y());
    }
    switch(direction)
    {
    case 0:
        snake.at(0)->setPos(snake.at(0)->x() + 10, snake.at(0)->y());
        break;
    case 1:
        snake.at(0)->setPos(snake.at(0)->x() - 10, snake.at(0)->y());
        break;
    case 2:
        snake.at(0)->setPos(snake.at(0)->x(), snake.at(0)->y() + 10);
        break;
    case 3:
        snake.at(0)->setPos(snake.at(0)->x(), snake.at(0)->y() - 10);
        break;
    }

    if(is_eat()){
        snake.append(new_s);
        scene->addItem(new_s);
        new_egg();
    }

    if(is_dead()) {
        //qDebug() << "dead";
        //timer->stop();
        restart();
    }

}

bool View::is_dead()
{
    bool dead = false;
    if(snake.at(0)->x() < 0 || snake.at(0)->y() < 0 || snake.at(0)->x() > 490 || snake.at(0)->y() > 490)
    {
        dead = true;
    }
    for(int i = 1; i < snake.length(); i++) {
        if(snake.at(0)->x() == snake.at(i)->x() && snake.at(0)->y() == snake.at(i)->y()) {
            dead = true;
        }
    }
    return dead;
}

void View::restart()
{
    for(int i = 0; i < snake.length(); i++) {
        scene->removeItem(snake.at(i));
    }
    snake.clear();
    Snake *s = new Snake();
    s->setPos(0, 0);
    snake.append(s);
    scene->addItem(s);
    direction = 0;
    timer->start(speed);
}
