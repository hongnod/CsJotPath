

#include "jotheaderbar.h"
#include "defs.h"


JotHeaderBar::JotHeaderBar(QWidget *parent) :
    QWidget(parent)
{
    setFixedHeight(HEADER_H);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);


    CreateWidget();
    CreateLayout();
}

JotHeaderBar::~JotHeaderBar()
{
}

void JotHeaderBar::updateMaxIcon(bool max)
{
    if(max)
    {
        if(nullptr != ptrBtnMax) ptrBtnMax->setPix(":/res/image/sysButton/Restores.png");
    }
    else
    {
        if(nullptr != ptrBtnMax) ptrBtnMax->setPix(":/res/image/sysButton/Maxs.png");
    }
}

void JotHeaderBar::CreateWidget() //创建子部件
{
    tabBar = new JotTabBar(this);
    tabBar->setTabsClosable(true);

    tabBar->setObjectName("tabBar");

    tabBar->setStyleSheet(QString("#tabBar QToolButton {border: 2px solid %1; border-radius: 2px; background: 2%;}").
                  formatArg(qApp->palette().color(QPalette::Shadow).name()).
                  formatArg(qApp->palette().background().color().name()));


   // ptrLabelIcon = new QLabel(this);  //图像标签--logo
   //     QPixmap objPixmap(":/res/image/logo.png");
   //     ptrLabelIcon->setPixmap(objPixmap);

    //ptrBtnFind = new PushButton(this);
    //ptrBtnFind->setPix(":/res/image/sysButton/find.png");
    ptrBtnMin = new JotPushButton();
    ptrBtnMin->setPix(":/res/image/sysButton/Mins.png");

    ptrBtnMax = new JotPushButton();
    ptrBtnMax->setPix(":/res/image/sysButton/Maxs.png");

    ptrBtnClose = new JotPushButton();
    ptrBtnClose->setPix(":/res/image/sysButton/Closes.png");

    //qDebug("CreateWidget()");

    connect(ptrBtnMin,&JotPushButton::clicked,this,[this](){qDebug("hdr min!"); emit sigSysBtn(1);});
    connect(ptrBtnMax,&JotPushButton::clicked,this,[this](){qDebug("hdr max!");emit sigSysBtn(2);});
    connect(ptrBtnClose,&JotPushButton::clicked,this,[this](){qDebug("hdr close!"); emit sigSysBtn(3);});
   // connect(tabBar, &TabBar::closeTab, this, &JotHeaderBar::CloseItem);
    //connect(tabBar, &TabBar::tabCloseRequested,this, &JotHeaderBar::slotCloseItem);
    //connect(this,&JotHeaderBar::sig_switchtab,stack,&QStackedLayout::setCurrentIndex);
    connect(tabBar,&JotTabBar::currentChanged,this,&JotHeaderBar::sig_currentChanged);
}



void JotHeaderBar::CreateLayout()  //创建设置布局
{ 
    ptrTitleLayout = new QHBoxLayout(); //水平布局

    ptrTitleLayout->setContentsMargins(0,2,10,0); //设置Margin
    //ptrTitleLayout->setSpacing(0); //设置部件之间的space

    //ptrTitleLayout->addWidget(ptrLabelIcon, 0, Qt::AlignCent);  //添加部件
    ptrTitleLayout->addSpacing(0);
    //
    //ptrTitleLayout->addLayout(stack);
    ptrTitleLayout->addWidget(tabBar, 0, Qt::AlignBottom);
    ptrTitleLayout->addStretch();
    //ptrTitleLayout->addWidget(ptrBtnFind, 0, Qt::AlignCenter);
    ptrTitleLayout->addSpacing(5);
    ptrTitleLayout->addWidget(ptrBtnMin, 0, Qt::AlignTop);
    ptrTitleLayout->addSpacing(5);
    ptrTitleLayout->addWidget(ptrBtnMax, 0, Qt::AlignTop);
    ptrTitleLayout->addSpacing(5);
    ptrTitleLayout->addWidget(ptrBtnClose, 0, Qt::AlignTop);
    setLayout(ptrTitleLayout);
}


void JotHeaderBar::slot_sigTabClicked(int index)
{
   emit sigTabClicked(index);
}


void JotHeaderBar::AddTab(QIcon icon, QString text)
{
    tabBar->addTab(icon,text);
    //return tabBar->count();
}

void JotHeaderBar::slotCloseItem(int index)
{
    if(index>0)
    {
        //tabBar->removeTab(index);
        emit CloseItem(index);
    }
}


