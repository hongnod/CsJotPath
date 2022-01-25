#include "jottoolbutton.h"

#ifdef Q_OS_MAC
JotToolButton::JotToolButton(QWidget *parent)
  : QPushButton(parent)
  , autoRise_(false)
  , buttonFixedSize_(18, 18)
{
}

void JotToolButton::setIconSize(const QSize &size)
{
  QPushButton::setIconSize(size);
  buttonFixedSize_ = QSize(size.width() + 2, size.height() + 2);
}

void JotToolButton::setAutoRaise(bool enable)
{
  autoRise_ = enable;
  setFlat(enable);
  if (enable) {
    setFixedSize(buttonFixedSize_);
  }
}

bool JotToolButton::autoRaise() const
{
  return autoRise_;
}
#else
JotToolButton::JotToolButton(QWidget *parent)
  : QToolButton(parent)
{
}
#endif
