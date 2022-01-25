#ifndef JotStatusBar_H
#define JotStatusBar_H
#include <QtGui>

class JotStatusBar:public QWidget
{
     CS_OBJECT(JotStatusBar)
public:
    explicit JotStatusBar(QWidget *parent = nullptr);
    ~JotStatusBar();
    void setMessage(QString &msg);
private:
       QLabel *ptrMsg = nullptr;
protected:
void paintEvent(QPaintEvent *event) override;

};
#endif // JotStatusBar_H
