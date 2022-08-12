#pragma once

#include <QMainWindow>

namespace tl
{
  class FormMain : public QMainWindow
  {
    Q_OBJECT

  public:
    FormMain(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    virtual ~FormMain() = default;

  private:
  };
} // namespace tl
