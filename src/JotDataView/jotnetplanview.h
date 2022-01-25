#ifndef JotNetPlanView_H
#define JotNetPlanView_H


#include <QtGui>

class JotNetPlanView : public QWidget
{
    CS_OBJECT(JotNetPlanView)
public:
    explicit JotNetPlanView(QWidget *parent = nullptr);

public:

public :

private:
    //void fillToolBar();
private:
  QGraphicsScene *scene = nullptr;
  QGraphicsPixmapItem *pixItem = nullptr;
  QGraphicsView *v = nullptr;
};

#endif // JotNetPlanView_H
