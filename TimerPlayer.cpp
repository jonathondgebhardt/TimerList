#include "TimerPlayer.h"

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

tl::TimerPlayer::Item* tl::TimerPlayer::getCurrentItem() const
{
  return this->getItem(this->currentTimerIndex);
}

bool tl::TimerPlayer::getIsPaused() const
{
  return false;
}

void tl::TimerPlayer::setProgressBar(QProgressBar* const x)
{
  this->progressBar = x;
  this->timer.setProgressBar(x);
}

void tl::TimerPlayer::play()
{
  if(this->items.empty() == false)
  {
    const auto duration = this->items[this->currentTimerIndex]->duration;

    if(this->progressBar != nullptr)
    {
      this->progressBar->setRange(0, duration);
    }

    this->timer.setDuration(duration);
    this->timer.start();

    this->timerStarted(this->currentTimerIndex);
  }
}

void tl::TimerPlayer::pause()
{
  this->timer.pause();
}

void tl::TimerPlayer::stop()
{
  this->timer.stop();

  if(this->progressBar != nullptr)
  {
    this->progressBar->reset();
  }

  this->currentTimerIndex = 0;
  this->timer.setDuration(0);
}

void tl::TimerPlayer::addItem()
{
  this->items.push_back(std::make_unique<tl::TimerPlayer::Item>());
}

void tl::TimerPlayer::removeItem(int x)
{
  this->items.erase(std::begin(this->items) + x);
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
    this->currentTimerIndex = 0;
  }

  if(this->currentTimerIndex < static_cast<size_t>(this->size()))
  {
    const auto duration = this->items[this->currentTimerIndex]->duration;

    if(this->progressBar != nullptr)
    {
      this->progressBar->setRange(0, duration);
    }

    this->timer.setDuration(duration);
    this->timer.start();

    this->timerStarted(this->currentTimerIndex);
  }
  else
  {
    this->currentTimerIndex = 0;
    this->done();
  }
}
