#include "jotmainwindow.h"
#include <QApplication>
#include "database.h"

int main(int argc, char *argv[])
{
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    QApplication a(argc, argv);
    DataLayer        db;
    db.initdbcon();
    JotMainWindow w;
    w.show();

    return a.exec();
}
