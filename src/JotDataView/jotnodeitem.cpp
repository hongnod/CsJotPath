#include "jotnodeitem.h"
#include "jotportlinkitem.h"

JotNodeItem::JotNodeItem()
{
    setFlags(QGraphicsItem::ItemIsFocusable|QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemSendsGeometryChanges|QGraphicsItem::ItemIsSelectable);
    //setFlag();// QGraphicsItem::ItemSendsGeometryChanges非常重要，没有这个，移动item时link不会跟着变

    setPixmap(QPixmap(":/res/image/NodeIcon/OTN.png"));
    nodeText =   QString("ITMC(中蒙)-N-二连浩特廉租楼-H-OTM/6853-ITMC(中蒙)-N-二连浩特廉租楼-H-OTM");
}

void JotNodeItem::setMyText(QString &text)
{
    nodeText = text;
}

QRectF JotNodeItem::boundingRect() const
{
    QRect rect = this->pixmap().rect();
    return QRectF(-10-rect.width()/2.0,-rect.height()/2.0,rect.width()+20,rect.height()+50);
}

QPainterPath JotNodeItem::shape() const
{
    QRectF r = this->pixmap().rect();
    QRectF shaperect;
    shaperect.setCoords(-r.width()/2.0-10,-r.height()/2.0-5,r.width()/2.0+10,r.height()/2.0+5);

    QPainterPath p;
    p.addRect(shaperect);
    return p;
}

void JotNodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)
    QPixmap pixmap = this->pixmap();
    QRect rect = pixmap.rect();

    painter->drawPixmap(static_cast<int>(-rect.width()/2.0),static_cast<int>(-rect.height()/2.0),pixmap);


    //print name,calculate the text's heigh & width for center layout
    QPen pen(Qt::black);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    QFont font("SimSun",10, QFont::Normal);
    painter->setFont(font);

    //QFontMetrics fm(font);
    //QString str = fm.elidedText(nodeText, Qt::ElideRight, 3*(rect.width()+20)-10);

    /*
    enum Qt::TextElideMode
            Constant	Value	Description
            Qt::ElideLeft	0	The ellipsis should appear at the beginning of the text.
            Qt::ElideRight	1	The ellipsis should appear at the end of the text.
            Qt::ElideMiddle	2	The ellipsis should appear in the middle of the text.
            Qt::ElideNone	3	Ellipsis should NOT appear in the text.
    painter->drawText(QRectF(-10-rect.width()/2.0,rect.height()/2.0+5,rect.width()+20,45),Qt::AlignLeft|Qt::TextWrapAnywhere,str);
    if (this->isSelected())
    {
        painter->setPen(QPen(Qt::yellow, 1, Qt::SolidLine));
        painter->drawRect(QRectF(-10-rect.width()/2.0,-rect.height()/2.0,rect.width()+20,rect.height()+3));
    }*/
}


// 鼠标按下事件处理函数，设置被点击的图形项获得焦点，并改变光标外观
void JotNodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    if(!( QApplication::keyboardModifiers () == Qt::ControlModifier))
    {
        scene()->clearSelection();
        setSelected(true);
    }
    qDebug("************JotNodeItem::mousePressEvent*****************");
    QGraphicsItem::mousePressEvent(event);
}

void JotNodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
     QGraphicsItem::mouseReleaseEvent(event);
}


// 键盘按下事件处理函数，判断是否是向下方向键，如果是，则向下移动图形项
void JotNodeItem::keyPressEvent(QKeyEvent *event)
{
    qDebug("************JotNodeItem::keyPressEvent*****************");
    //if(event->key() == Qt::CTRL)
        //moveBy(0, 10);
    Q_UNUSED(event)
}

// 悬停事件处理函数，设置光标外观和提示
void JotNodeItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
     Q_UNUSED(event)
    qDebug("************JotNodeItem::hoverEnterEvent*****************");
    setCursor(Qt::OpenHandCursor);
    setToolTip(nodeText);
}

void JotNodeItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    qDebug("************JotNodeItem::hoverLeaveEvent*****************");
    setCursor(Qt::ArrowCursor);
}


// 右键菜单事件处理函数，为图形项添加一个右键菜单
void JotNodeItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    setSelected(true);
    QMenu menu;
    QAction *moveAction = menu.addAction( QString("相关circuit"));
    QAction *actAction = menu.addAction( QString("网元属性"));
    QAction *selectedAction = menu.exec(event->screenPos());
    if(selectedAction == moveAction) {
        //setPos(0, 0);
    }

     Q_UNUSED(actAction)
}

void JotNodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("************JotNodeItem::mouseMoveEvent*****************");

    QGraphicsItem::mouseMoveEvent(event);
}


void JotNodeItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("************JotNodeItem::mouseDoubleClickEvent*****************");
    QGraphicsItem::mouseDoubleClickEvent(event);
}



QVariant JotNodeItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        for (JotPortLinkItem *link : links) {
            link->updatePosition();
        }
    }

    return value;
}
void JotNodeItem::addLink(JotPortLinkItem *link)
{
    links.append(link);
}
