#include "FormMain.h"
#include <QApplication>

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  tl::FormMain fm;
  fm.show();

  return app.exec();
}
