#include "jotnetplanview.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "jotnodeitem.h"
#include "jotportlinkitem.h"
//#include "defs.h"

JotNetPlanView::JotNetPlanView(QWidget *parent) : QWidget(parent)
{
    scene = new QGraphicsScene();
     scene->setSceneRect(-683, -384, 1366, 768);
    //
    pixItem =new QGraphicsPixmapItem();
    pixItem->setPixmap(QPixmap(":/res/image/background.png"));
    pixItem->setOpacity(0.3);
    pixItem->setPos(-517,-379);
    pixItem->setZValue(-500.0);
    scene->addItem(pixItem);


    JotNodeItem *item1 = new JotNodeItem();
    //item1->setMyText("ITMC(中蒙)-N-二连浩特廉租楼-H-OTM/6853-ITMC(中蒙)-N-二连浩特廉租楼-H-OTM-01");
    item1->setPos( - 90, -50);
    scene->addItem(item1);
    JotNodeItem *item2 = new JotNodeItem();
    //item2->setPlainText(QStringLiteral("ITMC(中蒙)-N-二连浩特廉租楼-H-OTM/6853-ITMC(中蒙)-N-二连浩特廉租楼-H-OTM-02"));
    item2->setPos( 90, -50);
    scene->addItem(item2);

    JotNodeItem *item3 = new JotNodeItem();
    //item3->setPlainText(QStringLiteral("ITMC(中蒙)-N-二连浩特廉租楼-H-OTM/6853-ITMC(中蒙)-N-二连浩特廉租楼-H-OTM-03"));
    item3->setPos( 0, 100);
    scene->addItem(item3);


    JotPortLinkItem *link1 = new JotPortLinkItem(item1,item2);
    scene->addItem(link1);

    JotPortLinkItem *link2 = new JotPortLinkItem(item1,item3);
    scene->addItem(link2);

    JotPortLinkItem *link3 = new JotPortLinkItem(item2,item3);
    scene->addItem(link3);

    v =new QGraphicsView(scene);
    //

    v->setFrameStyle(QFrame::NoFrame);
    v->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    QHBoxLayout *planLay = new QHBoxLayout;
    planLay->setContentsMargins(0,0,0,0);
    planLay->setSpacing(0);
    planLay->addWidget(v);
    setLayout(planLay);

}


