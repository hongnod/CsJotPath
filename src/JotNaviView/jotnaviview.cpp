#include "jotnaviview.h"

#include  "defs.h"
#include  "jotnaviheadbar.h"
#include  "findview.h"
#include  "jotresnavi.h"
#include  "jotnetnaviview.h"
#include  "jotplacenaviview.h"

JotNaviView::JotNaviView(QWidget *parent) :
    QWidget(parent)
{
    ptrNaviHeadBar     = new JotNaviHeadBar();
    find               = new FindView();
    find->hide();

    QVBoxLayout *lvbox = new QVBoxLayout(this);
    jotnavistack             = new QStackedLayout();
    jotnavistack->setSpacing(0);

    jotnavistack->setContentsMargins(0,0,0,0);
    lvbox->setSpacing(0);

    lvbox->setContentsMargins(0,0,0,0);
    lvbox->addWidget(ptrNaviHeadBar);
    lvbox->addWidget(find);
    lvbox->addLayout(jotnavistack);


    CreateInfoNavi();
    CreateNetNavi();
    CreatePlaceNavi();
    CreateResNavi();
connect(ptrNaviHeadBar,&JotNaviHeadBar::sigShowFind,this,&JotNaviView::slotShowFind);

}


JotNaviView::~JotNaviView()
{

}

void JotNaviView::showNetTree()
{

}


void JotNaviView::slotPlaceClicked(const  QModelIndex &idx)
{

  //  QString id = plcmodel->getItemId(idx);
  //  qDebug() << id <<": is pressed";
  //  if(QGuiApplication::mouseButtons() == Qt::RightButton){
  //      qDebug() << "RightMouse";
  //  }
}

void JotNaviView::slotNetworkClicked(const  QModelIndex &idx)
{
   // QString id = plcmodel->getItemId(idx);
   // qDebug() << id <<": is pressed";
   // if(QGuiApplication::mouseButtons() == Qt::RightButton){
   //     qDebug() << "RightMouse";
   // }
}


void JotNaviView::slotShowFind(bool show)
{
    show?find->show():find->hide();
}

void JotNaviView::slot_switchNavi(int index)
{
    jotnavistack->setCurrentIndex(index);
}



void JotNaviView::CreateInfoNavi()
{
    QWidget *infonavi = new QWidget();
    jotnavistack->addWidget(infonavi);
}

void JotNaviView::CreateNetNavi()
{
   netnav = new JotNetNaviView();
   jotnavistack->addWidget(netnav);
   //NetPlanView  *netplan = new NetPlanView();
   //rstack->addWidget(netplan);
   //ptrSysHeadBar->AddTab(QIcon(":/res/image/toolButton/topo.png"),"Network");

}
void JotNaviView::CreatePlaceNavi()
{
    placenav = new JotPlaceNaviView();
    jotnavistack->addWidget(placenav);
}

void JotNaviView::CreateResNavi()
{
   JotResNavi *netnav = new JotResNavi();
   jotnavistack->addWidget(netnav);


}
