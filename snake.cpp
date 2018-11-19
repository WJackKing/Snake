#include "snake.h"

#include <QBrush>
#include <QColor>

Snake::Snake()
{
    this->setRect(0, 0, 10, 10);
    this->setBrush(QBrush(QColor(0, 0, 0)));
}
