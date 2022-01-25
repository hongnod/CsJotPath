#ifndef JotNetNaviView_H
#define JotNetNaviView_H
#include <QtGui>


#include "jottoolbutton.h"

class JotTreeModel;
class QSqlDatabase;


class JotNetNaviView : public QWidget
{
    CS_OBJECT(JotNetNaviView)

public:
    explicit JotNetNaviView(QWidget *parent = nullptr);
    ~JotNetNaviView();
    void setDatabase(QSqlDatabase db);

public:


private:
     QTreeView *netTree;
     JotTreeModel *netmodel = nullptr;
     JotToolButton *netHead;

private :
     //CS_SLOT_1(Private, void showNetTree())
     //CS_SLOT_2(showNetTree) 
     //CS_SLOT_1(Private, void slotPlaceClicked(const QModelIndex &idx))
     //CS_SLOT_2(slotPlaceClicked) 
     //CS_SLOT_1(Private, void slotNetworkClicked(const QModelIndex &idx))
     //CS_SLOT_2(slotNetworkClicked) 
};



#endif //JotNetNaviView_H
