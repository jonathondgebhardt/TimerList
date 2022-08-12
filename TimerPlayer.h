#pragma once

#include "Timer.h"
#include <QObject>
#include <memory>
#include <vector>

namespace tl
{
  class TimerPlayer : public QObject
  {
    Q_OBJECT
  public:
    TimerPlayer(QObject* parent = nullptr);
    virtual ~TimerPlayer() = default;

    int size() const;

    tl::Timer* getTimer(int x) const;

    bool getIsPaused() const;

  public slots:
    void play();
    void pause();
    void stop();

    void addTimer();
    void removeTimer(int x);

    void setLoop(bool x);

  signals:
    void timerStarted(int x);
    void done();

  private:
    std::vector<std::unique_ptr<tl::Timer>> timers;
    size_t currentTimerIndex{0};
    bool loop{false};

  private slots:
    void startNextTimer();
  };
} // namespace tl
