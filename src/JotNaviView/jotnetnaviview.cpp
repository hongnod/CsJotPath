#include "jotnetnaviview.h"
#include "jottreemodel.h"
#include "defs.h"

JotNetNaviView::JotNetNaviView(QWidget *parent) :
    QWidget(parent)
{
///Begin Network Tree
    QLabel *netHeadLabel = new QLabel(this);
    netHeadLabel->setText("Networks");
    netHead = new JotToolButton(this);
    netHead->setIcon(QIcon(":/res/image/naviBar/netShow.png"));
    netHead->setFocusPolicy(Qt::NoFocus);
    netHead->setMaximumSize(16, 16);
    netHead->setAutoRaise(true);
    QHBoxLayout *netPanelLayout = new QHBoxLayout();
    netPanelLayout->setContentsMargins(0,0,0,0);
    netPanelLayout->addSpacing(2);
    netPanelLayout->addWidget(netHeadLabel, 1);
    netPanelLayout->addWidget(netHead);
    QWidget *netPanel = new QWidget(this);
    netPanel->setObjectName("netPanel");
    netPanel->setLayout(netPanelLayout);
    netPanel->setStyleSheet(QString("#netPanel { border-bottom: 1px solid %1;}").
                                   formatArg(qApp->palette().color(QPalette::Dark).name()));
    QStringList headers;
    headers << tr("Name") << tr("Type");

    netmodel = new JotTreeModel(headers, "network");
    netTree =  new QTreeView(this);
    netTree->setModel(netmodel);
    netTree->header()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    netTree->setObjectName("netTree");
    netTree->setStyleSheet("#netTree { border: none; padding: 0px;}");
    QVBoxLayout *netLayout = new QVBoxLayout();
    netLayout->setContentsMargins(0,0,0,0);
    netLayout->setSpacing(0);
    netLayout->addWidget(netPanel);
    netLayout->addWidget(netTree, 1);
 
//End Network Tree

    setLayout(netLayout);


    //connect(netHead, &ToolButton::clicked,this, &JotNetNaviView::showNetTree);
    //connect(placeTree,&QTreeView::pressed, this, &JotNetNaviView::slotPlaceClicked);
    //connect(netTree,&QTreeView::pressed, this, &JotNetNaviView::slotNetworkClicked);

    netHeadLabel->installEventFilter(this);
    netTree->installEventFilter(this);
}


JotNetNaviView::~JotNetNaviView()
{

}

//void JotNetNaviView::showNetTree()
//{
//  if (netTree->isHidden()) {
//    netHead->setIcon(QIcon(":/res/image/naviBar/netHide.png"));
//    netHead->setToolTip(tr("Hide Network"));
//    netTree->show();
//    vSplit->restoreState(vSplitState);
//  } else {
//    vSplitState = vSplit->saveState();
//    netHead->setIcon(QIcon(":/res/image/naviBar/netShow.png"));
//    netHead->setToolTip(tr("Show Network"));
//    netTree->hide();
//    QList <int> sizes;
//    sizes << height() << 20;
//    vSplit->setSizes(sizes);
//  }
//}
//
//
//void JotNetNaviView::slotPlaceClicked(const  QModelIndex &idx)
//{
//
//    QString id = plcmodel->getItemId(idx);
//    qDebug() << id <<": is pressed";
//    if(QGuiApplication::mouseButtons() == Qt::RightButton){
//        qDebug() << "RightMouse";
//    }
//}
//
//void JotNetNaviView::slotNetworkClicked(const  QModelIndex &idx)
//{
//    QString id = plcmodel->getItemId(idx);
//    qDebug() << id <<": is pressed";
//    if(QGuiApplication::mouseButtons() == Qt::RightButton){
//        qDebug() << "RightMouse";
//    }
//}





