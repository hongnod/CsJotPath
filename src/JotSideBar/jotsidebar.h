#ifndef JotSideBar_H
#define JotSideBar_H

#include <QWidget>
#include <QVector>
#include <QRect>


#include <QString>
#include <QIcon>



class SideTab : public QObject
{
 CS_OBJECT(SideTab)
 public:
    SideTab(QIcon &icon, QString text);

    QString m_text;
    QIcon m_icon;
};


class JotSideBar : public QWidget
{
    CS_OBJECT(JotSideBar)
public:
    enum Error{
        SUCESS = 0,
        INDEX_OUT_OF_RANGE
    };

    JotSideBar();
    explicit JotSideBar(QWidget *widget);
    virtual ~JotSideBar();

    qint32 addSideTab(QIcon icon, QString text);

    qint32 getActiveIndex() const;
    Error setActiveIndex(qint32 index);
    void  SetIconOnly(bool icononly = false);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;


    QRect getTabRect(qint32 index);
    QRect getIconRect(qint32 index);
    QRect getTextRect(qint32 index);
    qint32 getTabYPos(qint32 index);

    qint32 getTabIndexByPoint(qint32 x, qint32 y);

    void drawTabContent(QPainter *painter, qint32 index,
                        bool invertTextColor = false);

public:
    CS_SIGNAL_1(Public, void activeIndexChanged(qint32 index))
    //void activeIndexChanged(qint32 index);
    CS_SIGNAL_2(activeIndexChanged,index)

private:
    void init();
    bool HasText;

    QVector<SideTab*> tabVector;
    qint32 activeIndex;

    qint32 barWidth;
    qint32 iconSize;
    qint32 textHeight;
    qint32 textWidth;
    qint32 tabHeight;
    qint32 tabWidth;
    qint32 tabTopSpaceing;
    qint32 hower;

};

#endif // JotSideBar_H
