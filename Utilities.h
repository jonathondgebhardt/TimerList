#pragma once

#include <QString>
#include <QTime>

namespace tl::util
{
  QString MsToTimeString(int x);

  QTime MsToQTime(int x);

  int QTimeToMs(const QTime& x);
} // namespace tl::util
