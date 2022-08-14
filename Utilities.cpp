#include "Utilities.h"

#include <QTime>

QString tl::util::MsToTimeString(int x)
{
  const auto ms = x % 1000;
  x /= 1000;

  const auto s = x % 60;
  x /= 60;

  const auto m = x % 60;
  x /= 60;

  const auto h = x % 60;

  return QTime(h, m, s, ms).toString();
}
