#include "jotsidebar.h"

#include <QPainter>
#include <QDebug>
#include <QLinearGradient>
#include <QMouseEvent>
#include <QDebug>
#include "defs.h"

SideTab::SideTab(QIcon &icon, QString text)
{
    m_icon = icon;
    m_text = text;
}


JotSideBar::JotSideBar() : QWidget(NULL)
{
    init();
}


JotSideBar::JotSideBar(QWidget *widget) :
    QWidget(widget),HasText(true)
{
    init();
}


JotSideBar::~JotSideBar()
{
    for(int i = 0; i < tabVector.size(); i++)
    {
        delete tabVector.at(i);
    }
    tabVector.clear();
}



void  JotSideBar::SetIconOnly(bool icononly)
{
    if(icononly) HasText = false;
}

qint32 JotSideBar::addSideTab(QIcon icon, QString text)
{
    SideTab *fancyTab = new SideTab(icon, text);
    tabVector.append(fancyTab);
    setMinimumHeight((tabHeight * tabVector.size()) + 2);
    return tabVector.size() - 1;
}


qint32 JotSideBar::getActiveIndex() const
{
    return activeIndex;
}


JotSideBar::Error JotSideBar::setActiveIndex(qint32 index)
{
    if(index >= tabVector.size() || index < 0)
        return INDEX_OUT_OF_RANGE;

    activeIndex = index;
    emit activeIndexChanged(activeIndex);

    return SUCESS;
}


void JotSideBar::paintEvent(QPaintEvent *event)
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
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QColor(171, 171, 171));
    painter.drawLine(reducedSize.width() - 1, 1, reducedSize.width() - 1,
        reducedSize.height() - 1);

    //IN THE LEFT TOP CORNER,DRAW APP LOGO
    QPixmap logoicon(":res/image/OTN.png");
    logoicon = logoicon.scaled(tabWidth,HEADER_H);
    painter.drawPixmap((barWidth-tabWidth)/2,0,logoicon);

    if(hower >= 0 && hower != activeIndex)
    {
        QLinearGradient lineaGradientHover = QLinearGradient(0, 0, reducedSize.width(), 0);
        lineaGradientHover.setColorAt(0, QColor(200,200,200, 20));
        lineaGradientHover.setColorAt(0.5, QColor(200,200,200, 100));
        lineaGradientHover.setColorAt(1, QColor(200,200,200, 20));
        painter.setPen(Qt::NoPen);
        painter.setBrush(lineaGradientHover);
        painter.drawRect(getTabRect(hower));
    }

    for(int i = 0; i < tabVector.size(); i++)
    {
        // Active tab must be drawen last because it will draw into neighbours
        // tabs... This is most easy way how to draw specific frames
        if(activeIndex != i)
        {
            drawTabContent(&painter, i);
        }
    }

    // Draw activ tab if any
    // Will draw into neighbors tab!!!
    if(activeIndex >= 0)
    {
        // Make gradient more lighter. This indicate active tab
        QColor color1(170,170,170);
        QColor color2(233,233,233);
        linearGradient.setColorAt(0, color1);
        linearGradient.setColorAt(1, color2);

        painter.setBrush(linearGradient);
        painter.setPen(Qt::NoPen);
        painter.drawRect(getTabRect(activeIndex));

        drawTabContent(&painter, activeIndex, true);

        painter.setPen(QColor(49, 49, 49));

        QRect r = getTabRect(activeIndex).adjusted(-1, -1, 1, 1);
        // Draw top line
        painter.drawLine(r.topLeft(), r.topRight());
        // Draw bottom line
        painter.drawLine(r.bottomLeft(), r.bottomRight());

        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush());
        color1.setRgb(100, 100, 100);
        color2.setRgb(150, 150, 150);
        linearGradient.setColorAt(0, color1);
        linearGradient.setColorAt(1, color2);
        painter.setBrush(linearGradient);
        r.adjust(1, -1, 0, 1);
        // Draw top line
        painter.drawRect(r.left(), r.top(), r.right()-1, 1);
        // Draw bottom line
        painter.drawRect(r.left(), r.bottom(), r.right()-1, 1);
    }
    QWidget::paintEvent(event);
}


void JotSideBar::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        qint32 ret = getTabIndexByPoint(event->x(), event->y());

        // If non of the tabs is clicked dont change the curent activeIndex.
        if(ret != -1)
            activeIndex = ret;

        update();

        emit activeIndexChanged(activeIndex);
    }
    QWidget::mouseReleaseEvent(event);
}


void JotSideBar::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    hower = getTabIndexByPoint(event->x(), event->y());
    update();
}


void JotSideBar::enterEvent(QEvent *event)
{
    QEnterEvent *enterEvent = static_cast<QEnterEvent*>(event);
    hower = getTabIndexByPoint(enterEvent->x(), enterEvent->y());
    update();
}


void JotSideBar::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    // disable hower
    hower = -1;
    // repaint
    update();
}


QRect JotSideBar::getTabRect(qint32 index)
{
    qint32 tabPos = getTabYPos(index);
    return QRect(1, tabPos, tabWidth, tabHeight);
}


QRect JotSideBar::getIconRect(qint32 index)
{
    qint32 iconPos = getTabYPos(index) + tabTopSpaceing;
    return QRect((tabWidth - iconSize) / 2, iconPos, iconSize, iconSize);
}


QRect JotSideBar::getTextRect(qint32 index)
{
    qint32 textPos = getTabYPos(index) + tabTopSpaceing + iconSize;
    return QRect(1, textPos, tabWidth, textHeight);
}


qint32 JotSideBar::getTabYPos(qint32 index)
{
    return HEADER_H+10+ (tabHeight * index) + 1;
}


qint32 JotSideBar::getTabIndexByPoint(qint32 x, qint32 y)
{
    if(x < 1 || x > tabWidth)
        return -1;
    if(y > (HEADER_H+10 +(tabVector.size() * tabHeight) - 2)||y <= HEADER_H+10)
        return -1;

    return (y-HEADER_H-10-1)/tabHeight;
}


void JotSideBar::drawTabContent(QPainter *painter, qint32 index,
                                 bool invertTextColor)
{
    if(invertTextColor)
        painter->setPen(QColor(65, 65, 65));
    else
        painter->setPen(QColor(255, 255, 255));

    QFont font = painter->font();
    font.setBold(true);
    font.setPixelSize(10);
    painter->setFont(font);

    QPixmap pixmap = tabVector[index]->m_icon.pixmap(iconSize, iconSize);

    QRect iconRect = getIconRect(index);
    QRect textRect = getTextRect(index);

    painter->drawPixmap(iconRect.topLeft(), pixmap);
    if(HasText)painter->drawText(textRect, Qt::AlignBottom | Qt::AlignHCenter,
                      tabVector[index]->m_text);
}


void JotSideBar::init()
{
    activeIndex = -1;

    barWidth = 50;

    setMaximumWidth(barWidth);
    setMinimumWidth(barWidth);

    iconSize = 36;
    textHeight = 16;
    tabWidth  = barWidth - 2;   // Two are substraceted because there are two
                                // pixels of frame.
    textWidth  = tabWidth;
    tabHeight = 56;
                     // on the left side
    tabTopSpaceing = 1;

    setMouseTracking(true);
    hower = -1;
    SetIconOnly(false);
    addSideTab(QIcon(":/res/image/info.png"), "Info");
    addSideTab(QIcon(":/res/image/networking.png"), "Network");
    addSideTab(QIcon(":/res/image/building.png"), "Element");
    addSideTab(QIcon(":/res/image/circuit.png"), "Circuit");
    setActiveIndex(0);

}
