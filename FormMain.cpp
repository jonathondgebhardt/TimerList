#include "FormMain.h"

#include "TimerListWidget.h"

tl::FormMain::FormMain(QWidget* parent, Qt::WindowFlags flags) : QMainWindow(parent, flags)
{
  this->setCentralWidget(new tl::TimerListWidget(this));
}
