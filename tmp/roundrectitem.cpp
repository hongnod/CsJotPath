#include "roundrectitem.h"
#include <math.h>
#include <QPen>
#include <QPainter>

RoundRectItem::RoundRectItem(QGraphicsItem *parent)
{  this->setFlags(
        QGraphicsItem::ItemIsFocusable
      | QGraphicsItem::ItemIsMovable
      | QGraphicsItem::ItemIsSelectable);
}


void RoundRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
  if (this->isSelected())
  {
    QPen pen;
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);
  }
  painter->drawRoundedRect(this->rect(),m_radius_x,m_radius_y);
}

void RoundRectItem::setRoundedRect(const QRectF rect, const double radius_x, const double radius_y)
{
  this->setRect(rect);
  this->setRadiusX(radius_x);
  this->setRadiusY(radius_y);
}
