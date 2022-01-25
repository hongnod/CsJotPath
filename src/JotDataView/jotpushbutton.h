

#ifndef JotPushButton_H
#define JotPushButton_H

#include <QtGui>

class JotPushButton : public QPushButton
{
	CS_OBJECT(JotPushButton)

public:
    explicit JotPushButton(QWidget *parent = nullptr);
	~JotPushButton();
    void setPix(QString origPix);
protected:

    void enterEvent(QEvent *) override;
    void leaveEvent(QEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *) override;

private:


    enum ButtonStatus{NORMAL, ENTER, PRESS, NOSTATUS}; //枚举按钮的几种状态
	ButtonStatus status;
    QString namePixFile;

    QPixmap normPix;
    QPixmap enterPix;
    QPixmap pressPix;
    int btn_width =0; //按钮宽度
    int btn_height =0; //按钮高度
	bool mouse_press; //按钮左键是否按下

};

#endif //JotPushButton

