#include "toptabwidget.h"
#include "tabbar.h"

topTabWidget::topTabWidget(QTabWidget *parent) : QTabWidget(parent)
{
   bar = new TabBar(this);
   bar->setObjectName("topBar");
   //bar->setStyleSheet(QString("#tabBar QToolButton {border: 1px solid %1; border-radius: 2px; background: %2;}").
   //              arg(qApp->palette().color(QPalette::Dark).name()).
   //              arg(qApp->palette().background().color().name()));
   setTabBar(bar);
}
