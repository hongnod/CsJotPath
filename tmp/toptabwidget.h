#ifndef TOPTABWIDGET_H
#define TOPTABWIDGET_H

#include <QTabWidget>
class TabBar;

class topTabWidget : public QTabWidget
{
    CS_OBJECT(topTabWidget)
public:
    explicit topTabWidget(QTabWidget *parent = nullptr);

public:
private:
    TabBar *bar;
};

#endif // TOPTABWIDGET_H
