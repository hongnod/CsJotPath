/**
	ä¸»èåï¼åæ¬å³äºæä»¬ãæ°çç¹æ§ç­
	ä½èï¼â°âå¥æingâ¤å­©å­`
	åå®¢å°åï¼http://blog.sina.com.cn/liang19890820
	QQï¼550755606
	Qtåäº«ãäº¤æµç¾¤ï¼26197884

	æ³¨ï¼è¯·å°éåä½èå³å¨ææï¼ä»ä¾å­¦ä¹ ä½¿ç¨ï¼è¯·å¿çç¨ï¼è¿èå¿ç©¶ï¼
*/

#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMenu>


class MainMenu : public QMenu
{
	CS_OBJECT(MainMenu)

public:

    explicit MainMenu(QWidget *parent = nullptr);
	void translateActions();

public:

    CS_SIGNAL_1(Public, void showSettingDialog())
    //void showSettingDialog();
    CS_SIGNAL_2(showSettingDialog)
    CS_SIGNAL_1(Public, void showNewCharacter())
    //void showNewCharacter();
    CS_SIGNAL_2(showNewCharacter)
    CS_SIGNAL_1(Public, void showAboutUs())
    //void showAboutUs();
    CS_SIGNAL_2(showAboutUs)


private:
	
	void createActions();

private:

    QAction *action_setting = nullptr; //设置
    QAction *action_check_update = nullptr; //检查更新
    QAction *action_help_online = nullptr; //在线帮助
    QAction *action_about_us = nullptr; //关于我们

};

#endif //MAINMENU_H
