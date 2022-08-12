#include "TimerPlayer.h"

tl::TimerPlayer::TimerPlayer(QObject* parent) : QObject(parent)
{
}

int tl::TimerPlayer::size() const
{
  return static_cast<int>(this->timers.size());
}

tl::Timer* tl::TimerPlayer::getTimer(int x) const
{
  if(x >= 0 && x < this->size())
  {
    return this->timers[x].get();
  }

  return nullptr;
}

bool tl::TimerPlayer::getIsPaused() const
{
  if(const auto timer = this->getTimer(this->currentTimerIndex))
  {
    return timer->getIsPaused();
  }

  return false;
}

void tl::TimerPlayer::play()
{
  if(this->timers.empty() == false)
  {
    const auto firstTimer = this->timers.front().get();
    firstTimer->start();

    this->connect(firstTimer, &tl::Timer::expired, this, &tl::TimerPlayer::startNextTimer);

    this->timerStarted(this->currentTimerIndex);
  }
}

void tl::TimerPlayer::pause()
{
  if(const auto timer = this->getTimer(this->currentTimerIndex))
  {
    timer->pause();
  }
}

void tl::TimerPlayer::stop()
{
}

void tl::TimerPlayer::addTimer()
{
  this->timers.push_back(std::make_unique<tl::Timer>());
}

void tl::TimerPlayer::removeTimer(int x)
{
  this->timers.erase(std::begin(this->timers) + x);
}

void tl::TimerPlayer::setLoop(bool x)
{
  this->loop = x;
}

void tl::TimerPlayer::startNextTimer()
{
  if(const auto currentTimer = this->getTimer(this->currentTimerIndex))
  {
    this->disconnect(currentTimer);
  }

  this->currentTimerIndex += 1;

  if(this->loop == true && this->currentTimerIndex >= static_cast<size_t>(this->size()))
  {
    this->currentTimerIndex = 0;
  }

  if(const auto nextTimer = this->getTimer(this->currentTimerIndex))
  {
    nextTimer->start();
    this->connect(nextTimer, &tl::Timer::expired, this, &tl::TimerPlayer::startNextTimer);

    this->timerStarted(this->currentTimerIndex);
  }
  else
  {
    this->currentTimerIndex = 0;
    this->done();
  }
}
