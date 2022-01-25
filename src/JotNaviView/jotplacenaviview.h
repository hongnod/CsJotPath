#ifndef JotPlaceNaviView_H
#define JotPlaceNaviView_H
#include <QtGui>


#include "jottoolbutton.h"

class JotTreeModel;
class QSqlDatabase;


class JotPlaceNaviView : public QWidget
{
    CS_OBJECT(JotPlaceNaviView)

public:
    explicit JotPlaceNaviView(QWidget *parent = nullptr);
    ~JotPlaceNaviView();
    void setDatabase(QSqlDatabase db);

public:


private:
     QTreeView *placeTree = nullptr;
     JotTreeModel *plcmodel = nullptr;


private :
     //CS_SLOT_1(Private, void slotPlaceClicked(const QModelIndex &idx))
     //CS_SLOT_2(slotPlaceClicked)

};



#endif //JotPlaceNaviView_H
