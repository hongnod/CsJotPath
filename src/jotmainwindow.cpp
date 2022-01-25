#include <QWidget>
#include "jotmainwindow.h"

#include "jotstatusbar.h"
#include "defs.h"
#include "mainmenu.h"
#include "framelesshelper.h"

#include "jotsidebar.h"
#include "jotnaviview.h"
#include "jotdataview.h"

#include <QTime>

JotMainWindow::JotMainWindow(QFrame *parent)
    : QFrame(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);

    setMouseTracking(true);
    setAttribute(Qt::WA_Hover, true);
    QString fileName(":/res/style/system.qss");
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
      file.setFileName(":/res/style/system.qss");
      file.open(QFile::ReadOnly);
    }
    setStyleSheet(file.readAll());
    file.close();

    //createToolBarNull();
    QHBoxLayout *ptrHLayout = new QHBoxLayout();
    ptrHLayout->setContentsMargins(0,0,1,0);
    ptrHLayout->setSpacing(0);
    ptrSideBar = new JotSideBar(this);
    ptrHLayout->addWidget(ptrSideBar);
    ptrJotNaviView =new JotNaviView();
    ptrDataView = new JotDataView();
    QSplitter *hsplit  = new QSplitter(this);
    hsplit->setFrameStyle(QFrame::NoFrame);
    hsplit->setHandleWidth(1);
    hsplit->setChildrenCollapsible(false);
    hsplit->addWidget(ptrJotNaviView);
    hsplit->addWidget(ptrDataView);
    //QList<int> size{200,800};
    //hsplit->setSizes(size);
    hsplit->setStretchFactor(1,1);


    ptrStatusBar = new JotStatusBar();
    QString msg = "Ready";
    ptrStatusBar->setMessage(msg);

    QVBoxLayout *VBox = new QVBoxLayout();//创建布局
    VBox->addWidget(hsplit);//将部件加入到布局中
    VBox->addWidget(ptrStatusBar);
    VBox->setSpacing(0);  //设置间距与边缘空白
    VBox->setContentsMargins(0,0,0,0);


     ptrHLayout->addLayout(VBox);

    setLayout(ptrHLayout);
    setMinimumWidth(800);
    setMinimumHeight(600);


     createActions();

    FramelessHelper *pHelper = new FramelessHelper(this);

    pHelper->activateOn(this);  //激活当前窗体
    pHelper->setBorderWidth(VALUE_DIS);
    pHelper->setTitleHeight(HEADER_H);  //设置窗体的标题栏高度
    pHelper->setWidgetMovable(true);  //设置窗体可移动
    pHelper->setWidgetResizable(true);  //设置窗体可缩放



    connect(ptrDataView, &JotDataView::sigSysCmd, this, [this](int id){if(id==1) showMinimized();
                                                                    if(id==2) showMaxRestore();
                                                                    if(id==3) close();});

   connect(ptrSideBar,&JotSideBar::activeIndexChanged,ptrJotNaviView,&JotNaviView::slot_switchNavi);
}

JotMainWindow::~JotMainWindow()
{

}

void JotMainWindow::showMenu(QPoint pt)
{
   MainMenu *m = new MainMenu(this);
   m->exec(pt);
}

void JotMainWindow::showMaxRestore()
{
   qDebug("Entering showMaxRestore()");
   if(isMaximized()||isFullScreen())
   {
        //qDebug("Entering showNormal()");
       this->showNormal();
   }
   else
   {
      //qDebug("Entering showMaximized()");
       this->showMaximized();
   }

}

void JotMainWindow::changeEvent(QEvent *e)
{
    if(e->type() == QEvent::WindowStateChange)
    {
        if(isMaximized()||isFullScreen())
        {
            ptrDataView->updateMaxIcon();
        }
        else
        {
            ptrDataView->updateMaxIcon(false);
        }
    }
}


void JotMainWindow::createActions()
{
   //connect(ptrMainView,&MainView::sigTabClicked,this, &JotMainWindow::slot_switchPage);
}



