#ifndef VIEW_H
#define VIEW_H

#include "snake.h"
#include "egg.h"

#include <QList>
#include <stdlib.h>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>

class View : public QGraphicsView
{
    Q_OBJECT
public:
    View();
    void keyPressEvent(QKeyEvent *event);
    void new_egg();
    bool is_eat();
    bool is_dead();
    void restart();

private:
    QGraphicsScene *scene;
    QList<Snake *> snake;
    Egg *egg;
    QTimer *timer;
    int direction;
    int speed;
    bool is_stop;

private slots:
    void move();
};

#endif // VIEW_H
