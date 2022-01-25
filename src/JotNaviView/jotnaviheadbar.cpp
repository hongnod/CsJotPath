

#include "jotnaviheadbar.h"
#include "defs.h"
#include "findview.h"

JotNaviHeadBar::JotNaviHeadBar(QWidget *parent) :
    QWidget(parent)
{
    setFixedHeight(HEADER_H);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    //find = new FindView();
    //find->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    naviToolBar = new QToolBar(this);
    naviToolBar->setObjectName("naviToolBar");
    naviToolBar->setStyleSheet(QString("QToolBar{ border-bottom: 1px solid %1;background: %2;}").
                               formatArg(qApp->palette().color(QPalette::Dark).name()));
    fillToolBar();
    hplay = new QHBoxLayout(); //水平布局
    hplay->addWidget(naviToolBar);

    hplay->setSpacing(0);
    hplay->setContentsMargins(0,1,0,0);
    setLayout(hplay);
}

JotNaviHeadBar::~JotNaviHeadBar()
{
}




void JotNaviHeadBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    // Reduced size is size reduced by one becouse we need to draw from 0
    // so size - 1. That how all arrays works ;)
    QSize reducedSize = this->size() - QSize(1, 1);

    // Draw separation rect
    // Rest of parameters are zeros becouse we want to do only vertical
    // gradient.
    QLinearGradient linearGradient(0, 0, reducedSize.width(), 0);
    linearGradient.setColorAt(0, QColor(64, 64, 64));
    linearGradient.setColorAt(1, QColor(130, 130, 130));

    painter.setBrush(linearGradient);
    painter.setPen(QColor(49, 49, 49));
    painter.drawRect(0, 0, reducedSize.width(), reducedSize.height());

    // Draw additional separation line to right side of bar
    // This makes it more fancy ;)
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QColor(171, 171, 171));
    painter.drawLine(reducedSize.width() - 1, 1, reducedSize.width() - 1,
        reducedSize.height() - 1);

}

void JotNaviHeadBar::fillToolBar()
{
    QAction *actAdd = new QAction(this);
    actAdd->setText("Add");
    actAdd->setIcon(QIcon(":/res/image/naviBar/add.png"));
    naviToolBar->addAction(actAdd);
    naviToolBar->addSeparator();

    QAction *actFilter = new QAction(this);
    actFilter->setText("Filter");
    actFilter->setIcon(QIcon(":/res/image/naviBar/filter.png"));
    naviToolBar->addAction(actFilter);
    naviToolBar->addSeparator();

    QAction *actUpdate = new QAction(this);
    actUpdate->setText("Update");
    actUpdate->setIcon(QIcon(":/res/image/naviBar/update.png"));
    naviToolBar->addAction(actUpdate);
    naviToolBar->addSeparator();

    actSearch = new QAction(this);
    actSearch->setText("Search");
    actSearch->setIcon(QIcon(":/res/image/naviBar/find.png"));
    naviToolBar->addAction(actSearch);
    actSearch->setCheckable(true);
    actSearch->setChecked(false);

    connect(actSearch,&QAction::triggered,this,&JotNaviHeadBar::slotShowFind);
}

void JotNaviHeadBar::slotShowFind()
{
    bool show=false;
    show = actSearch->isChecked();
    emit sigShowFind(show);
}
