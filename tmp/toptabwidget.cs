#ifndef TOPTABWIDGET_H
#define TOPTABWIDGET_H

#include <QTabWidget>
class TabBar;

class topTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit topTabWidget(QTabWidget *parent = nullptr);

signals:
private:
    TabBar *bar;
};

#endif // TOPTABWIDGET_H
