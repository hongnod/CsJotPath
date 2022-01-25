#ifndef JotNaviHeadBar_H
#define JotNaviHeadBar_H

#include <QtGui>
#include <QtCore>
#include <QtGui>
class FindView;

class JotNaviHeadBar : public QWidget
{
    CS_OBJECT(JotNaviHeadBar)

public:
    explicit JotNaviHeadBar(QWidget *parent = nullptr);
    ~JotNaviHeadBar();


public:
    CS_SIGNAL_1(Public, void sigShowFind(bool show))
    //void sigShowFind(bool show);
    CS_SIGNAL_2(sigShowFind,show)
protected:
    void paintEvent(QPaintEvent *event) override;

public :
    
private :
    //CS_SLOT_1(Private, void slotShowFind())
    void slotShowFind();
    //CS_SLOT_2(slotShowFind)

private:
    QHBoxLayout *hplay = nullptr;
    QToolBar *naviToolBar = nullptr;
    void     fillToolBar();
    QAction *actSearch = nullptr;
};


#endif // JotNaviHeadBar
