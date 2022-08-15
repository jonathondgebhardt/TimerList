#include "Timer.h"

#include <iostream>

tl::Timer::Timer(QObject* parent) : QObject(parent), timer(new QTimer(this))
{
  this->connect(this->timer, &QTimer::timeout, this, &tl::Timer::tick);
}

void tl::Timer::setDuration(int x)
{
  this->duration = x;
  this->timeRemaining = x;
}

int tl::Timer::getDuration() const
{
  return this->duration;
}

int tl::Timer::getTimeRemaining() const
{
  return this->timeRemaining;
}

void tl::Timer::setResolution(int x)
{
  this->resolution = x;
}

int tl::Timer::getResolution() const
{
  return this->resolution;
}

bool tl::Timer::getIsPaused() const
{
  return this->paused;
}

void tl::Timer::setProgressBar(QProgressBar* const x)
{
  this->progressBar = x;
}

void tl::Timer::start()
{
  this->paused = false;
  this->timeRemaining = this->duration;
  this->timer->start(this->resolution);
}

void tl::Timer::pause()
{
  this->paused = true;
}

void tl::Timer::stop()
{
  this->timer->stop();
}

void tl::Timer::tick()
{
  if(this->paused == false)
  {
    this->timeRemaining -= this->resolution;

    if(this->progressBar != nullptr)
    {
      this->progressBar->setValue(this->duration - this->timeRemaining);
    }

    if(this->timeRemaining <= 0)
    {
      this->timeRemaining = 0;
      this->timer->stop();

      this->expired();
    }
    else
    {
      this->timer->start(this->resolution);
    }
  }
  else
  {
    this->timer->stop();
  }
}
