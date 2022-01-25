#include "jotrouteview.h"
#include <QGraphicsItem>
#include <QGraphicsScene>


JotRouteView::JotRouteView(QWidget *parent) : QWidget(parent)
{
     scene = new QGraphicsScene();
     v = new QGraphicsView(this);
     v->setScene(scene);
     v->setSceneRect(0,0,50,50);
     v->setAlignment(Qt::AlignLeft | Qt::AlignTop);
     v->setFrameStyle(QFrame::NoFrame);


     //DrawRoute();
     QHBoxLayout *hbox = new QHBoxLayout();

     hbox->setSpacing(0);
     hbox->setContentsMargins(0,0,0,0);
     hbox->addWidget(v);
     setLayout(hbox);
     //connect(v->horizontalScrollBar(),&QAbstractSlider::actionTriggered,this, &JotRouteView::showsth);
     connect(v->horizontalScrollBar(),&QScrollBar::valueChanged,this, &JotRouteView::sigHsliderMove);
}

void JotRouteView::slotMoveWithHead(int col,int o_size,int newsize)
{
    qDebug("catched the header resize");
    //if(col==1)
    //{
    //    grpTxt->moveBy(newsize-o_size,0);
    //}
    //if(col==2)
    DrawRoute();
    QRectF	rct = v->sceneRect();
    v->horizontalScrollBar()->setRange(0,rct.width()+newsize-o_size);
}

void JotRouteView::SetData(QList<NODE> *nodes,QList<LINK> *links)
{
    nods = nodes;
    lnks =links;
}
void JotRouteView::SetHeader(QHeaderView *h)
{
    hdr = h;
}

void JotRouteView::DrawRoute()
{
 hdr->resizeSection(1,2*metaWidth);
 qDebug("entering drawroute");
 scene->clear();
 qDebug("sene cleared");
 QGraphicsLineItem *lt;
 QGraphicsRectItem *rt;

 QGraphicsEllipseItem *et;
 QGraphicsSimpleTextItem *tt;
 QGraphicsSimpleTextItem *nodname;
 QFont font  = qApp->font();
 QFontMetrics fontWidth(font);
 QPen gridpen;
 gridpen.setColor(Qt::lightGray);
 gridpen.setStyle(Qt::DashLine);
 gridpen.setWidth(1);

 QPen edgepen;
 edgepen.setColor(Qt::lightGray);
 edgepen.setWidth(1);

 QPen linepen;
 linepen.setColor(Qt::black);
 linepen.setWidth(1);


 int start= hdr->sectionSize(0)+hdr->sectionSize(1);


 int col2size =metaWidth;
 for(NODE n : *nods)
 {
   if(n.type==ntELEMENT)
   {
       rt = scene->addRect(0,0,n.sz_col*metaWidth-10,(n.sz_row-0.5)*metaHeight-5);
       rt->setPos(metaWidth*(n.pos_col+1)+5,metaHeight*(n.pos_row+0.5));
       rt->setZValue(-30);
       rt->setPen(edgepen);
       rt->setBrush(QColor(Qt::lightGray));
       rt->setFlags(QGraphicsItem::ItemIsFocusable|QGraphicsItem::ItemSendsGeometryChanges|QGraphicsItem::ItemIsSelectable);

       nodname = scene->addSimpleText(fontWidth.elidedText(n.Name,Qt::ElideRight,hdr->sectionSize(2)));

       nodname->setPos(start+3,n.pos_row*metaHeight+3);
       //grpTxt->addToGroup(nodname);

   }
   qDebug("draw element finished!");
   if(n.type==ntPORT)
   {
       //et = scene->addEllipse(metaWidth*(n.pos_col+2.5)-8,metaHeight*(n.pos_row+0.5)-8,16,16);
       et = scene->addEllipse(0,0,16,16);
       et->setPos(metaWidth*(n.pos_col+1.5)-8,metaHeight*(n.pos_row+0.5)-8);
       et->setZValue(-10);
       et->setPen(edgepen);
       et->setBrush(QColor(Qt::darkGreen));
       et->setFlags(QGraphicsItem::ItemIsFocusable|QGraphicsItem::ItemSendsGeometryChanges|QGraphicsItem::ItemIsSelectable);

       if(fontWidth.size(Qt::TextSingleLine,n.Name).width() > col2size) col2size = fontWidth.size(Qt::TextSingleLine,n.Name).width() ;
       //nodname = scene->addSimpleText(fontWidth.elidedText(n.Name,Qt::ElideRight,hdr->sectionSize(2)));
       nodname = scene->addSimpleText(n.Name);
       nodname->setPos(start+6,n.pos_row*metaHeight+3);
   }
 }
 qDebug("draw ports finished!");
 //QGraphicsLineItem lnt;
 for(LINK l : *lnks)
 {
    if(l.lt !=ltRELATE)
    {
        auto lnt = scene->addLine((l.from->pos_col+1.5)*metaWidth,(l.from->pos_row+0.5)*metaHeight,(l.to->pos_col+1.5)*metaWidth,(l.to->pos_row+0.5)*metaHeight);
        lnt->setZValue(-20);
        lnt->setPen(linepen);
        lnt->setFlags(QGraphicsItem::ItemIsFocusable|QGraphicsItem::ItemSendsGeometryChanges|QGraphicsItem::ItemIsSelectable);
    }


 }

 hdr->resizeSection(2,col2size+metaWidth);
 int end = hdr->sectionSize(0)+hdr->sectionSize(1)+hdr->sectionSize(2);
 lt = scene->addLine(hdr->sectionSize(0),0,hdr->sectionSize(0),17*metaHeight);
 lt->setZValue(-100);
 lt->setPen(gridpen);
 lt = scene->addLine(hdr->sectionSize(0)+hdr->sectionSize(1),0,hdr->sectionSize(0)+hdr->sectionSize(1),17*metaHeight);
 lt->setZValue(-100);
 lt->setPen(gridpen);
 lt = scene->addLine(hdr->sectionSize(0)+hdr->sectionSize(1)+hdr->sectionSize(2),0,hdr->sectionSize(0)+hdr->sectionSize(1)+hdr->sectionSize(2),17*metaHeight);
 lt->setZValue(-100);
 lt->setPen(gridpen);

 for(int i=0; i<18; i++)
 {
     lt = scene->addLine(0,i*metaHeight,end,i*metaHeight);
     lt->setPen(gridpen);
     lt->setZValue(-100);
     if(i<17)
     {
       tt= scene->addSimpleText(QString("%1").formatArg(i+1));
       tt->setPos(5,(i+0.5)*metaHeight);
     }
 }
   qDebug("draw grid finished");
 v->setSceneRect(0,0,scene->width(), scene->height());
 v->update();
}

//void JotRouteView::showEvent ( QShowEvent * event )
//{
//    v->setSceneRect(0, 0, scene->width(), scene->height());
//    QWidget::showEvent(event);
//}
//
//void JotRouteView::resizeEvent(QResizeEvent* event)
//{
//      QWidget::resizeEvent(event);
//}
