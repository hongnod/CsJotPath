#ifndef JotDataView_H
#define JotDataView_H

#include <QtGui>
class JotHeaderBar;



class JotDataView : public QWidget
{
    CS_OBJECT(JotDataView)
public:
    explicit JotDataView(QWidget *parent = nullptr);
    void     updateMaxIcon(bool max = true);

public:
    CS_SIGNAL_1(Public, void sigSysCmd(int id))
    //void sigSysCmd(int id);
    CS_SIGNAL_2(sigSysCmd,id)

public :

protected:
//    void paintEvent(QPaintEvent *event) override;
private:
    JotHeaderBar       *ptrSysHeadBar = nullptr;
    QStackedLayout     *jotdataviewstack = nullptr;

public:
   void OpenNetPlan();
   void OpenResView();
   void OpenRouteView();
   void OpenTitleView();

private :
    CS_SLOT_1(Private, void slot_switchView(int index))
    CS_SLOT_2(slot_switchView) 
    CS_SLOT_1(Private, void CloseView(int index))
    CS_SLOT_2(CloseView) 


};

#endif // JotDataView_H
