#ifndef HEADERBAR_H
#define HEADERBAR_H

#include <QtGui>
#include <QtCore>
#include <QtGui>
#include "jotpushbutton.h"
#include "jottabbar.h"
class MainWindow;
class JotHeaderBar : public QWidget
{
    CS_OBJECT(JotHeaderBar)

public:
    explicit JotHeaderBar(QWidget *parent = nullptr);
    ~JotHeaderBar();

    void updateMaxIcon(bool max = true);
    void  AddTab(QIcon icon,QString text);
    void setActiveTab(qint32 index);
    //void AddToolBar(QToolBar *bar);
public:
    //void signal_menu(QPoint pt);
    CS_SIGNAL_1(Public, void sigSysBtn(int id))
    //void sigSysBtn(int id);
    CS_SIGNAL_2(sigSysBtn,id)

    CS_SIGNAL_1(Public, void sigTabClicked(int index))
    //void sigTabClicked(int index);
    CS_SIGNAL_2(sigTabClicked,index)
    CS_SIGNAL_1(Public, void CloseItem(int index))
    //void CloseItem(int index);
    CS_SIGNAL_2(CloseItem,index)

    CS_SIGNAL_1(Public, void sig_currentChanged(int index))
    //void sig_currentChanged(int index);
    CS_SIGNAL_2(sig_currentChanged,index)


private :
   // void slot_menu();
    //CS_SLOT_1(Private, void slot_sigTabClicked(int index))
    void slot_sigTabClicked(int index);
    //CS_SLOT_2(slot_sigTabClicked)
    //CS_SLOT_1(Private, void slotCloseItem(int index))
    void slotCloseItem(int index);
    //CS_SLOT_2(slotCloseItem)



private:
    MainWindow *rootParent = nullptr;
    //QLabel *ptrLabelIcon;
    JotTabBar *tabBar = nullptr;
    //PushButton *ptrBtnFind;
    JotPushButton *ptrBtnMin = nullptr;
    JotPushButton *ptrBtnMax = nullptr;
    JotPushButton *ptrBtnClose = nullptr;
    //QStackedLayout *stack;
    QHBoxLayout *ptrTitleLayout = nullptr;

    void CreateWidget();//创建子部件
    //void SetWidgetStyle();//设置子部件样式(qss)
    void CreateLayout();  //创建设置布局
};


#endif // HEADERBAR_H
