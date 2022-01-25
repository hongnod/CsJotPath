#ifndef JotRouteView_H
#define JotRouteView_H

#include <QtGui>
#include <QtSql>
#include "defs.h"

class JotRouteView : public QWidget
{
    CS_OBJECT(JotRouteView)
public:
    explicit JotRouteView(QWidget *parent = nullptr);
    void DrawRoute();
    void SetData(QList<NODE> *nodes,QList<LINK> *links);
    void SetHeader(QHeaderView *h);
protected:
//    void paintEvent(QPaintEvent *event);
    //void showEvent ( QShowEvent * event );
    //void resizeEvent(QResizeEvent* event);
public:
     CS_SIGNAL_1(Public, void sigHsliderMove(int val))
    //void sigHsliderMove(int val);
     CS_SIGNAL_2(sigHsliderMove,val)
public :
    //CS_SLOT_1(Public, void slotMoveWithHead(int col,int o_size,int newsize))
    void slotMoveWithHead(int col,int o_size,int newsize);
    //CS_SLOT_2(slotMoveWithHead)
private:
    QGraphicsView *v = nullptr;
    QGraphicsScene *scene= nullptr;
    QHeaderView *hdr=nullptr;
    QList<NODE> *nods = nullptr;
    QList<LINK> *lnks = nullptr;
};


#endif // JotRouteView_H
