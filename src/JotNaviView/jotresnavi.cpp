#include "jotresnavi.h"


JotResNavi::JotResNavi(QWidget *parent) :
    QWidget(parent)
{
    table = new QTableWidget();
    //table->setStyleSheet("QTableWidget { border: 0px; padding: 2px;}");
    table->setColumnCount(5);
    table->setRowCount(10);
    // table->setHorizontalHeaderLabels();


    QVBoxLayout *navilay = new QVBoxLayout(this);
    navilay->setContentsMargins(0,0,0,0);
    navilay->setSpacing(0);
    navilay->setContentsMargins(0,0,0,0);
    navilay->addWidget(table);
    setLayout(navilay);
}


JotResNavi::~JotResNavi()
{

}



