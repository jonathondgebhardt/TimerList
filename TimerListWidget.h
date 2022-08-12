#pragma once

#include "TimerListView.h"
#include <QCheckBox>
#include <QPushButton>
#include <QWidget>

namespace tl
{
  class TimerListWidget : public QWidget
  {
    Q_OBJECT
  public:
    TimerListWidget(QWidget* parent = nullptr);
    virtual ~TimerListWidget() = default;

  private:
    tl::TimerListView* vTimerList{nullptr};
    QPushButton* btnPlayPause{nullptr};
    QPushButton* btnStop{nullptr};
    QCheckBox* chkLoop{nullptr};
    QPushButton* btnAdd{nullptr};
    QPushButton* btnRemove{nullptr};

  private slots:
    void playPause();
    void stop();
    void addTimer();
    void removeTimer();
    void loopChanged(int x);
  };
} // namespace tl
