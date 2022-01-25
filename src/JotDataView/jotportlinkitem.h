#ifndef PORTLINKITEM_H
#define PORTLINKITEM_H
#include <QGraphicsLineItem>

#include "jotnodeitem.h"
QT_BEGIN_NAMESPACE
class QGraphicsPolygonItem;
class QGraphicsLineItem;
class QGraphicsScene;
class QRectF;
class QGraphicsSceneMouseEvent;
class QPainterPath;
QT_END_NAMESPACE

class JotPortLinkItem : public QGraphicsLineItem
{
public:
    enum { Type = UserType + 4 };

    JotPortLinkItem(JotNodeItem *startItem=nullptr, JotNodeItem *endItem=nullptr,
      QGraphicsItem *parent = nullptr);

    int type() const override { return Type; }
   // QRectF boundingRect() const Q_DECL_OVERRIDE;
    //QPainterPath shape() const Q_DECL_OVERRIDE;
    void setColor(const QColor &color) { myColor = color; }
    JotNodeItem *startItem() const { return myStartItem; }
    JotNodeItem *endItem() const { return myEndItem; }

    void updatePosition();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private:
    JotNodeItem *myStartItem = nullptr;
    JotNodeItem *myEndItem = nullptr;
    QColor myColor;
    QPolygonF JotPortLinkItemHead;
};
#endif // PORTLINKITEM_H
