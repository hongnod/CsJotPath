#ifndef JotToolButton_H
#define JotToolButton_H

#include <QPushButton>
#include <QToolButton>

#ifdef Q_OS_MAC
class JotToolButton : public QPushButton
{
  CS_OBJECT(JotToolButton)
public:
  explicit JotToolButton(QWidget *parent = nullptr);

  void setIconSize(const QSize &size);

  void setAutoRaise(bool enable);
  bool autoRaise() const;

private:
  bool autoRise_;
  QSize buttonFixedSize_;

};
#else
class JotToolButton : public QToolButton
{
  CS_OBJECT(JotToolButton)
public:
  explicit JotToolButton(QWidget *parent = nullptr);

};
#endif

#endif // JotToolButton_H
