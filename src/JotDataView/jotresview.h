#ifndef JotResView_H
#define JotResView_H

#include <QtGui>


class JotRouteView;

class JotResView : public QWidget
{
    CS_OBJECT(JotResView)
public:
    explicit JotResView(QWidget *parent = nullptr);

public:

private:

    JotRouteView *route =nullptr;
    QHeaderView       *header = nullptr;

private :
    CS_SLOT_1(Private, void slotMoveHeader(int val))
    CS_SLOT_2(slotMoveHeader) 

};

#endif // JotResView_H
