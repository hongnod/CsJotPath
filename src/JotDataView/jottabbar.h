/* ============================================================
* QuiteRSS is a open-source cross-platform RSS/Atom news feeds reader
* Copyright (C) 2011-2016 QuiteRSS Team <quiterssteam@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
* ============================================================ */
#ifndef JotTabBar_H
#define JotTabBar_H
/*
#ifdef HAVE_QT5
#include <QtWidgets>
#else
#include <QtGui>
#endif*/

#include <QtGui>
#include <QtCore>
#include <QtGui>

class JotTabBar : public QTabBar
{
  CS_OBJECT(JotTabBar)
public:
  explicit JotTabBar(QWidget *parent = nullptr);

  enum CloseTabsState {
    CloseTabIdle = 0,
    CloseTabCurrentIndex,
    CloseTabOtherIndex
  };

  CloseTabsState closingTabState_;

public :
  //CS_SLOT_1(Public, void slotCloseTab())
  void slotCloseTab();
  //CS_SLOT_2(slotCloseTab)
  //CS_SLOT_1(Public, void slotCloseOtherTabs())
  void slotCloseOtherTabs();
  //CS_SLOT_2(slotCloseOtherTabs)
  //CS_SLOT_1(Public, void slotCloseAllTab())
  void slotCloseAllTab();
  //CS_SLOT_2(slotCloseAllTab)
  //CS_SLOT_1(Public, void slotNextTab())
  void slotNextTab();
  //CS_SLOT_2(slotNextTab)
  //CS_SLOT_1(Public, void slotPrevTab())
  void slotPrevTab();
  //CS_SLOT_2(slotPrevTab)

public:
  CS_SIGNAL_1(Public, void closeTab(int index))
   //void closeTab(int index);
  CS_SIGNAL_2(closeTab,index)

protected:
  bool eventFilter(QObject *obj, QEvent *ev) override;

private :
  //CS_SLOT_1(Private, void showContextMenuJotTabBar(const QPoint & pos))
  void showContextMenuJotTabBar(const QPoint & pos);
  //CS_SLOT_2(showContextMenuJotTabBar)

private:
  int indexClickedTab_;
  bool tabFixed_;

};

#endif // JotTabBar_H
