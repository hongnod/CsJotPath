#ifndef RESNAVI_H
#define RESNAVI_H
#include <QtGui>
#include "jottoolbutton.h"
#include "findview.h"


class QSqlDatabase;

class JotResNavi : public QWidget
{
    CS_OBJECT(JotResNavi)

public:
    explicit JotResNavi(QWidget *parent = nullptr);
    ~JotResNavi();

private:
     //QToolBar *naviToolBar;
     
     QTableWidget      *table = nullptr;

};



#endif // RESNAVI_H
