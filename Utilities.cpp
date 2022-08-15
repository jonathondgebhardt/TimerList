#include "Utilities.h"

#include <QTime>

QString tl::util::MsToTimeString(int x)
{
  return tl::util::MsToQTime(x).toString();
}

QTime tl::util::MsToQTime(int x)
{
  const auto ms = x % 1000;
  x /= 1000;

  const auto s = x % 60;
  x /= 60;

  const auto m = x % 60;
  x /= 60;

  const auto h = x % 60;

  return QTime(h, m, s, ms);
}

int tl::util::QTimeToMs(const QTime& x)
{
  int result = 0;

  result += x.hour() * 3600000;
  result += x.minute() * 60000;
  result += x.second() * 1000;

  return result;
}
