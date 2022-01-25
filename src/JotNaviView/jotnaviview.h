#ifndef JotNaviView_H
#define JotNaviView_H
#include <QtGui>


#include "jottoolbutton.h"
#include "findview.h"


class TreeModel;
class QSqlDatabase;
class JotNaviHeadBar;
class FindView;
class JotNetNaviView;
class JotPlaceNaviView;
class JotNaviView : public QWidget
{
    CS_OBJECT(JotNaviView)

public:
    explicit JotNaviView(QWidget *parent = nullptr);
    ~JotNaviView();
    void setDatabase(QSqlDatabase db);

public:
    CS_SLOT_1(Public, void slot_switchNavi(int index))
    CS_SLOT_2(slot_switchNavi)


private:

     JotNaviHeadBar     *ptrNaviHeadBar = nullptr;
     FindView        *find = nullptr;
     JotNetNaviView *netnav  = nullptr;
     JotPlaceNaviView *placenav = nullptr;
     QStackedLayout  *jotnavistack = nullptr;
     void CreateInfoNavi();
     void CreateNetNavi();
     void CreatePlaceNavi();
     void CreateResNavi();

private :
     CS_SLOT_1(Private, void showNetTree())
     CS_SLOT_2(showNetTree) 
     CS_SLOT_1(Private, void slotPlaceClicked(const QModelIndex &idx))
     CS_SLOT_2(slotPlaceClicked) 
     CS_SLOT_1(Private, void slotNetworkClicked(const QModelIndex &idx))
     CS_SLOT_2(slotNetworkClicked) 
     CS_SLOT_1(Private, void slotShowFind(bool show))
     CS_SLOT_2(slotShowFind)
};



#endif //JotNaviView_H
