#ifndef NODEITEM_H
#define NODEITEM_H

#include <QtGui>

class JotPortLinkItem;

class JotNodeItem : public QGraphicsPixmapItem
{
public:
    enum {Type = UserType + 1};
    JotNodeItem();
    void setMyText(QString &text);
    void addLink(JotPortLinkItem *link);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)  override;
    void setColor(const QColor &color) { brushColor = color; }
    int type() const override {return Type;}
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent (QGraphicsSceneHoverEvent * event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
private:
    QColor brushColor;
    QString nodeText;
    QList<JotPortLinkItem *> links;
};



#endif // NODEITEM_H
