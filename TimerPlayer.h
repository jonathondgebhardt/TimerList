#pragma once

#include "Timer.h"
#include <QObject>
#include <QTimer>
#include <memory>
#include <vector>

namespace tl
{
  class TimerPlayer : public QObject
  {
    Q_OBJECT
  public:
    struct Item
    {
      QString title;
      int duration{0};
      int timeRemaining{0};
    };

    TimerPlayer(QObject* parent = nullptr);
    virtual ~TimerPlayer() = default;

    int size() const;

    tl::TimerPlayer::Item* getItem(int x) const;

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
    tl::Timer timer;
    std::vector<std::unique_ptr<tl::TimerPlayer::Item>> items;
    size_t currentTimerIndex{0};
    bool loop{false};

  private slots:
    void startNextTimer();
  };
} // namespace tl
