#pragma once

#include <QObject>
#include <QTimer>

namespace tl
{
  class Timer : public QObject
  {
    Q_OBJECT
  public:
    Timer(QObject* parent = nullptr);
    virtual ~Timer() = default;

    void setTitle(const QString& x);
    QString getTitle() const;

    int getTimeRemaining() const;

    void setResolution(int x);
    int getResolution() const;

    void setDuration(int x);
    int getDuration() const;

    bool getIsPaused() const;

  public slots:
    void start();
    void pause();

  signals:
    void expired();

  private:
    QTimer* timer{nullptr};
    QString title;

    int duration{0};
    int timeRemaining{0};
    int resolution{1000};

    bool paused{true};

  private slots:
    void tick();
  };
} // namespace tl
