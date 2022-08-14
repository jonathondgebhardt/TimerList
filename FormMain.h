#pragma once

#include "TimerPlayer.h"
#include <QMainWindow>
#include <memory>

namespace tl
{
  class FormMain : public QMainWindow
  {
    Q_OBJECT
  public:
    FormMain(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    virtual ~FormMain() = default;

  private:
    std::unique_ptr<tl::TimerPlayer> player;
  };
} // namespace tl
