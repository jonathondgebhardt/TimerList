#include "FormMain.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  // https://github.com/ColinDuquesnoy/QDarkStyleSheet/releases/tag/v3.0.2
  QFile f(":qdarkstyle/dark/style.qss");
  if(f.exists() == true)
  {
    f.open(QFile::ReadOnly | QFile::Text);
    QTextStream ts(&f);
    qApp->setStyleSheet(ts.readAll());
  }

  tl::FormMain fm;
  fm.show();

  return app.exec();
}
