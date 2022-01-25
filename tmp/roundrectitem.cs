#ifndef ROUNDRECTITEM_H
#define ROUNDRECTITEM_H

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>

class RoundRectItem : public QGraphicsRectItem
{
    //Q_OBJECT
public:
    RoundRectItem(QGraphicsItem *parent = nullptr);
    double getRadiusX() const { return m_radius_x; }
    double getRadiusY() const { return m_radius_y; } //Get the rounded rect corner y radiu
    void setRadiusX(const double radius_x) { m_radius_x = radius_x; } //Set the rounded rect corner x radius
    void setRadiusY(const double radius_y) { m_radius_y = radius_y; } //Set the rounded rect corner y radius
    void setRoundedRect(const QRectF rect, const double radius_x, const double radius_y); //Set the rounded rect

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
     double m_radius_x; //The rounded rect corner x radius
     double m_radius_y;   //The rounded rect corner y radius

};

#endif // ROUNDRECTITEM_H
