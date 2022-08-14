#include "TimerPlayer.h"

#include <iostream>

tl::TimerPlayer::TimerPlayer(QObject* parent) : QObject(parent)
{
  this->connect(&this->timer, &tl::Timer::expired, this, &tl::TimerPlayer::startNextTimer);
}

int tl::TimerPlayer::size() const
{
  return static_cast<int>(this->items.size());
}

tl::TimerPlayer::Item* tl::TimerPlayer::getItem(int x) const
{
  if(x >= 0 && x < this->size())
  {
    return this->items[x].get();
  }

  return nullptr;
}

bool tl::TimerPlayer::getIsPaused() const
{

  return false;
}

void tl::TimerPlayer::play()
{
  if(this->items.empty() == false)
  {
    std::cout << "TimerPlayer: Starting timer " << this->currentTimerIndex << " with duration "
              << this->items[this->currentTimerIndex]->duration << "\n";

    this->timer.setDuration(this->items[this->currentTimerIndex]->duration);
    this->timer.start();
  }
}

void tl::TimerPlayer::pause()
{
  this->timer.pause();
}

void tl::TimerPlayer::stop()
{
  this->timer.pause();
}

void tl::TimerPlayer::addTimer()
{
}

void tl::TimerPlayer::removeTimer(int)
{
}

void tl::TimerPlayer::setLoop(bool x)
{
  this->loop = x;
}

void tl::TimerPlayer::startNextTimer()
{
  this->currentTimerIndex += 1;

  if(this->loop == true && this->currentTimerIndex >= static_cast<size_t>(this->size()))
  {
    std::cout << "TimerPlayer: looping\n";

    this->currentTimerIndex = 0;
  }

  if(this->currentTimerIndex <= static_cast<size_t>(this->size()))
  {
    std::cout << "TimerPlayer: Starting timer " << this->currentTimerIndex << " with duration "
              << this->items[this->currentTimerIndex]->duration << "\n";

    this->timer.setDuration(this->items[this->currentTimerIndex]->duration);
    this->timer.start();
  }
  else
  {
    std::cout << "TimerPlayer: stopping\n";

    this->currentTimerIndex = 0;
    this->done();
  }
}
