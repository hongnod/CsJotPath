#ifndef JotMainWindow_H
#define JotMainWindow_H

#include <QtGui>




class HeaderBar;
class StatusBar;
class LeftNavi;
class JotSideBar;
class JotNaviView;
class JotDataView;
class JotStatusBar;

class JotMainWindow : public QFrame
{
    CS_OBJECT(JotMainWindow)

public:
    explicit JotMainWindow(QFrame *parent = nullptr);
    ~JotMainWindow();
    void changeEvent(QEvent *e) override;

public :
    CS_SLOT_1(Public, void showMenu(QPoint pt))
    CS_SLOT_2(showMenu) 
    CS_SLOT_1(Public, void showMaxRestore())
    CS_SLOT_2(showMaxRestore) 

private:
    void createActions();
private:
    JotSideBar     *ptrSideBar = nullptr;
    JotNaviView    *ptrJotNaviView  = nullptr;
    JotDataView       *ptrDataView = nullptr;
    JotStatusBar       *ptrStatusBar = nullptr;

private :

};



#endif // JotMainWindow_H

