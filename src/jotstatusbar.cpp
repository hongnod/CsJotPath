#include "jotstatusbar.h"

JotStatusBar::JotStatusBar(QWidget *parent):
    QWidget(parent)
{
     setFixedHeight(25);

     ptrMsg = new QLabel(this);
     ptrMsg->setFixedWidth(300); //for testing
     ptrMsg->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
     ptrMsg->setStyleSheet("QLabel{margin-left:10px;color:white}QLabel:hover{color:#00AA00;}");

}

JotStatusBar::~JotStatusBar()
{

}

void JotStatusBar::setMessage(QString &msg)
{
  ptrMsg->setText(msg);
}

void JotStatusBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

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
    //painter.setBrush(Qt::NoBrush);
    //painter.setPen(QColor(171, 171, 171));
    //painter.drawLine(reducedSize.width() - 1, 1, reducedSize.width() - 1,
    //    reducedSize.height() - 1);

}
