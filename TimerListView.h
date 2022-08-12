#pragma once

#include "TimerListModel.h"
#include <QTableView>

namespace tl
{
  class TimerListView : public QTableView
  {
    Q_OBJECT
  public:
    TimerListView(QWidget* parent = nullptr);
    virtual ~TimerListView() = default;

  private:
  };
} // namespace tl
