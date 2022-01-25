#include <QtGui>
#include "jotdataview.h"
#include "jotheaderbar.h"
#include "defs.h"
#include "jotnetplanview.h"
#include "jotresview.h"
#include "animated_tiles.h"
#include "pieview.h"
#include "tiledlistview.hpp"

JotDataView::JotDataView(QWidget *parent) : QWidget(parent)
{  

    ptrSysHeadBar  = new JotHeaderBar(this);//创建标题栏

    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->setSpacing(0);

    vbox->setContentsMargins(0,0,0,0);

    jotdataviewstack             = new QStackedLayout();
    jotdataviewstack->setSpacing(0);

    jotdataviewstack->setContentsMargins(0,0,0,0);

    vbox->addWidget(ptrSysHeadBar);
    vbox->addLayout(jotdataviewstack);

    OpenNetPlan();
    OpenResView();
    OpenRouteView();
    OpenTitleView();
    setLayout(vbox);

    connect(ptrSysHeadBar,&JotHeaderBar::sigSysBtn,this,[this](int id){qDebug("sigSysCmd!");emit sigSysCmd(id);});
    connect(ptrSysHeadBar,&JotHeaderBar::sig_currentChanged,this,&JotDataView::slot_switchView);
}

void JotDataView::updateMaxIcon(bool max)
{
    ptrSysHeadBar->updateMaxIcon(max);
}



void JotDataView::CloseView(int index)
{

}

void JotDataView::slot_switchView(int index)
{
    jotdataviewstack->setCurrentIndex(index);
}

//Switch Left Navigation Panel,done



//void JotDataView::paintEvent(QPaintEvent *event)
//{
//    Q_UNUSED(event);
//
//    QPainter painter(this);
//
//    // Reduced size is size reduced by one becouse we need to draw from 0
//    // so size - 1. That how all arrays works ;)
//    QSize reducedSize = this->size() - QSize(1, 1);
//
//    // Draw separation rect
//    // Rest of parameters are zeros becouse we want to do only vertical
//    // gradient.
//    QLinearGradient linearGradient(0, 0, reducedSize.width(), 0);
//    linearGradient.setColorAt(0, QColor(64, 64, 64));
//    linearGradient.setColorAt(1, QColor(130, 130, 130));
//
//    painter.setBrush(linearGradient);
//    painter.setPen(QColor(49, 49, 49));
//    painter.drawRect(0, 0, reducedSize.width(), reducedSize.height());
//
//
//    // Draw additional separation line to right side of bar
//    // This makes it more fancy ;)
//    painter.setBrush(Qt::NoBrush);
//    painter.setPen(QColor(171, 171, 171));
//    painter.drawLine(reducedSize.width() - 1, 1, reducedSize.width() - 1,
//        reducedSize.height() - 1);
//    QWidget::paintEvent(event);
//}


void JotDataView::OpenNetPlan()
{
    qDebug("OpenNetPlan");
    JotNetPlanView  *netplan = new JotNetPlanView(this);
    //AnimatedTiles  *netplan = new AnimatedTiles(this);
    jotdataviewstack->addWidget(netplan);
    ptrSysHeadBar->AddTab(QIcon(":/res/image/toolButton/topo.png"),"Network");
}


void JotDataView::OpenResView()
{
    JotResView  *resplan = new JotResView(this);
    jotdataviewstack->addWidget(resplan);
    ptrSysHeadBar->AddTab(QIcon(":/res/image/toolButton/cable.png"),"Path1");
}

void JotDataView::OpenRouteView()
{
    PieView  *rtplan = new PieView;
    QAbstractItemModel *model = new QStandardItemModel(8, 2, this);
    model->setHeaderData(0, Qt::Horizontal, tr("route"));
    model->setHeaderData(1, Qt::Horizontal, tr("node"));
    rtplan->setModel(model);

    QFile file("d:/qtdata.cht");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug("open file failed.");
        return;
     }
    QTextStream stream(&file);

    model->removeRows(0, model->rowCount(QModelIndex()), QModelIndex());

    int row = 0;
    while (!stream.atEnd()) {
        const QString line = stream.readLine();
        qDebug()<< line;
        if (!line.isEmpty()) {
            model->insertRows(row, 1, QModelIndex());

            const QStringList pieces = line.split(QLatin1Char(','));
            if (pieces.size() < 3)
                continue;
            model->setData(model->index(row, 0, QModelIndex()),
                           pieces.value(0));
            model->setData(model->index(row, 1, QModelIndex()),
                           pieces.value(1));
            model->setData(model->index(row, 0, QModelIndex()),
                           QColor(pieces.value(2)), Qt::DecorationRole);
            row++;
        }
    };
    qDebug()<<model;
    file.close();

    jotdataviewstack->addWidget(rtplan);
    ptrSysHeadBar->AddTab(QIcon(":/res/image/toolButton/cable.png"),"Path2");
}

void JotDataView::OpenTitleView()
{
    qDebug("in OpenTitleView");
    QStandardItemModel *model = new QStandardItemModel;
    QStringList l;
            l << "Barack Obama" << "George W. Bush" << "Bill Clinton"
            << "George H. W. Bush" << "Ronald Reagan"
            << "Jimmy Carter" << "Gerald Ford" << "Richard Nixon"
            << "Lyndon B. Johnson" << "John F. Kennedy"
            << "Dwight D. Eisenhower" << "Harry S. Truman"
            << "Franklin D. Roosevelt" << "Herbert Hoover"
            << "Calvin Coolidge" << "Warren G. Harding"
            << "Woodrow Wilson" << "William Howard Taft"
            << "Theodore Roosevelt" << "William McKinley"
            << "Grover Cleveland" << "Benjamin Harrison"
            << "Grover Cleveland" << "Chester A. Arthur"
            << "James A. Garfield" << "Rutherford B. Hayes"
            << "Ulysses S. Grant" << "Andrew Johnson"
            << "Abraham Lincoln" << "James Buchanan"
            << "Franklin Pierce" << "Millard Fillmore"
            << "Zachary Taylor" << "James K. Polk" << "John Tyler"
            << "William Henry Harrison" << "Martin Van Buren"
            << "Andrew Jackson" << "John Quincy Adams"
            << "James Monroe" << "James Madison"
            << "Thomas Jefferson" << "John Adams"
            << "George Washington";
            qDebug() << l;
    for(auto name : l){
        qDebug() << name;
    model->appendRow(new QStandardItem(name));

    }

    TiledListView  *title = new TiledListView(this);
    title->setModel(model);
    jotdataviewstack->addWidget(title);
    ptrSysHeadBar->AddTab(QIcon(":/res/image/toolButton/cable.png"),"title");

}
