#pragma once

#include "TimerListView.h"
#include "TimerPlayer.h"
#include <QCheckBox>
#include <QPushButton>
#include <QWidget>

namespace tl
{
  class TimerListWidget : public QWidget
  {
    Q_OBJECT
  public:
    TimerListWidget(tl::TimerPlayer* const player, QWidget* parent = nullptr);
    virtual ~TimerListWidget() = default;

  public slots:
    void setPlayer(tl::TimerPlayer* const x);

  private:
    tl::TimerPlayer* player{nullptr};

    tl::TimerListView* vTimerList{nullptr};
    QPushButton* btnPlay{nullptr};
    QPushButton* btnPause{nullptr};
    QPushButton* btnStop{nullptr};
    QCheckBox* chkLoop{nullptr};
    QPushButton* btnAdd{nullptr};
    QPushButton* btnRemove{nullptr};

  private slots:
    void play();
    void pause();
    void stop();
    void loopChanged(int x);
    void addItem();
    void removeItem();
  };
} // namespace tl
