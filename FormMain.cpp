#include "FormMain.h"

#include "TimerListWidget.h"

tl::FormMain::FormMain(QWidget* parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags), player(std::make_unique<tl::TimerPlayer>())
{
  this->setCentralWidget(new tl::TimerListWidget(player.get(), this));
}
