#include "jotplacenaviview.h"
#include "jottreemodel.h"
#include "defs.h"


JotPlaceNaviView::JotPlaceNaviView(QWidget *parent) :
    QWidget(parent)
{
 
    ///Begin places Tree View
    QLabel *placeHeadLabel = new QLabel(this);
    placeHeadLabel->setText("Places");

    JotToolButton *placeHead = new JotToolButton(this);
    placeHead->setIcon(QIcon(":/res/image/naviBar/placeShow.png"));
    placeHead->setFocusPolicy(Qt::NoFocus);
    placeHead->setMaximumSize(16, 16);
    placeHead->setAutoRaise(true);
    QHBoxLayout *placePanelLayout = new QHBoxLayout();
    placePanelLayout->setContentsMargins(0,0,0,0);
    placePanelLayout->addSpacing(2);
    placePanelLayout->addWidget(placeHeadLabel, 1);
    placePanelLayout->addWidget(placeHead);
    QWidget *placePanel = new QWidget(this);
    placePanel->setObjectName("placePanel");
    placePanel->setLayout(placePanelLayout);
    placePanel->setStyleSheet(QString("#placePanel { border-bottom: 1px solid %1;}").
                                   formatArg(qApp->palette().color(QPalette::Dark).name()));
    placeTree = new QTreeView(this);
    QStringList headers;
    headers << tr("Name") << tr("Type");

    plcmodel = new JotTreeModel(headers, "place");

    placeTree->setModel(plcmodel);
    placeTree->setObjectName("placeTree");
    QHeaderView *header = placeTree->header();
    header->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    //header->setSectionHidden(2,true);
    QVBoxLayout *placeLayout = new QVBoxLayout();

    placeLayout->setContentsMargins(0,0,0,0);
    placeLayout->setSpacing(0);
    placeLayout->addWidget(placePanel);
    placeLayout->addWidget(placeTree, 1);
 
//End place Tree

    setLayout(placeLayout);


    //connect(netHead, &ToolButton::clicked,this, &JotPlaceNaviView::showNetTree);
    //connect(placeTree,&QTreeView::pressed, this, &JotPlaceNaviView::slotPlaceClicked);
    

}


JotPlaceNaviView::~JotPlaceNaviView()
{

}

//void JotPlaceNaviView::showNetTree()
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
//void JotPlaceNaviView::slotPlaceClicked(const  QModelIndex &idx)
//{
//
//    QString id = plcmodel->getItemId(idx);
//    qDebug() << id <<": is pressed";
//    if(QGuiApplication::mouseButtons() == Qt::RightButton){
//        qDebug() << "RightMouse";
//    }
//}
//
//void JotPlaceNaviView::slotNetworkClicked(const  QModelIndex &idx)
//{
//    QString id = plcmodel->getItemId(idx);
//    qDebug() << id <<": is pressed";
//    if(QGuiApplication::mouseButtons() == Qt::RightButton){
//        qDebug() << "RightMouse";
//    }
//}





