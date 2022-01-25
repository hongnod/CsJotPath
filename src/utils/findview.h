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
#ifndef FINDVIEW_H
#define FINDVIEW_H


#include <QtGui>


class FindView : public QLineEdit
{
  CS_OBJECT(FindView)
public:
  FindView(QWidget *parent = nullptr);
  void retranslateStrings();

  QActionGroup *findGroup_ = nullptr;
  void AddFilter(QAction *act);
public:
  CS_SIGNAL_1(Public, void signalClear())
  //void signalClear();
  CS_SIGNAL_2(signalClear)
  CS_SIGNAL_1(Public, void signalSelectFind())
  //void signalSelectFind();
  CS_SIGNAL_2(signalSelectFind)

protected:
  void resizeEvent(QResizeEvent *) override;
  void focusInEvent(QFocusEvent *event) override;
  void focusOutEvent(QFocusEvent *event) override;

private :
  //CS_SLOT_1(Private, void updateClearButton(const QString & text))
  void updateClearButton(const QString & text);
  //CS_SLOT_2(updateClearButton)
  //CS_SLOT_1(Private, void slotClear())
  void slotClear();
  //CS_SLOT_2(slotClear)
  //CS_SLOT_1(Private, void slotMenuFind())
  void slotMenuFind();
  //CS_SLOT_2(slotMenuFind)
  //CS_SLOT_1(Private, void slotSelectFind(QAction * act))
  void slotSelectFind(QAction * act);
  //CS_SLOT_2(slotSelectFind)

private:
  QMenu *findMenu_ = nullptr;
   QAction *findInSitesAct = nullptr;
   QAction *findInNetworksAct = nullptr;
   QAction *findInPlanAct = nullptr;
   QAction *findInCircuitAct = nullptr;


  QLabel *findLabel_ = nullptr;
  QToolButton *findButton_ = nullptr;
  QToolButton *clearButton_ = nullptr;

};

#endif // FINDVIEW_H
