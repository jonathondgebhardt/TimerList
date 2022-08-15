#pragma once

#include <QObject>
#include <QProgressBar>
#include <QTime>
#include <QTimer>

namespace tl
{
  class Timer : public QObject
  {
    Q_OBJECT
  public:
    Timer(QObject* parent = nullptr);
    virtual ~Timer() = default;

    void setDuration(int x);
    int getDuration() const;

    int getTimeRemaining() const;

    void setResolution(int x);
    int getResolution() const;

    bool getIsPaused() const;

    void setProgressBar(QProgressBar* const x);

  public slots:
    void start();
    void pause();
    void stop();

  signals:
    void expired();

  private:
    QTimer* timer{nullptr};
    QProgressBar* progressBar{nullptr};

    int duration{0};
    int timeRemaining{0};
    int resolution{1000};

    bool paused{true};

  private slots:
    void tick();
  };
} // namespace tl
