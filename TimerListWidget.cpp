#include "TimerListWidget.h"

#include "TimerListModel.h"
#include <QBoxLayout>

tl::TimerListWidget::TimerListWidget(QWidget* parent)
    : QWidget(parent),
      vTimerList(new tl::TimerListView(this)),
      btnPlayPause(new QPushButton("Play", this)),
      btnStop(new QPushButton("Stop", this)),
      chkLoop(new QCheckBox("Loop", this)),
      btnAdd(new QPushButton("Add", this)),
      btnRemove(new QPushButton("Remove", this))
{
  const auto layout = new QHBoxLayout(this);

  layout->addWidget(this->btnPlayPause);

  this->btnStop->setEnabled(false);
  layout->addWidget(this->btnStop);

  layout->addWidget(this->vTimerList);

  const auto buttonLayout = new QVBoxLayout();

  this->chkLoop->setChecked(true);
  this->loopChanged(Qt::Checked);
  buttonLayout->addWidget(this->chkLoop);

  buttonLayout->addWidget(this->btnAdd);

  buttonLayout->addWidget(this->btnRemove);
  this->btnRemove->setEnabled(false);

  layout->addLayout(buttonLayout);

  this->connect(this->btnPlayPause, &QPushButton::clicked, this, &tl::TimerListWidget::playPause);
  this->connect(this->btnStop, &QPushButton::clicked, this, &tl::TimerListWidget::stop);
  this->connect(this->chkLoop, &QCheckBox::stateChanged, this, &tl::TimerListWidget::loopChanged);
  this->connect(this->btnAdd, &QPushButton::clicked, this, &tl::TimerListWidget::addTimer);
  this->connect(this->btnRemove, &QPushButton::clicked, this, &tl::TimerListWidget::removeTimer);
}

void tl::TimerListWidget::playPause()
{
  const auto model = qobject_cast<tl::TimerListModel*>(this->vTimerList->model());
  model->playPause();

  this->btnStop->setEnabled(true);
}

void tl::TimerListWidget::stop()
{
  const auto model = qobject_cast<tl::TimerListModel*>(this->vTimerList->model());
  model->stop();

  this->btnStop->setEnabled(false);
}

void tl::TimerListWidget::addTimer()
{
  const auto model = qobject_cast<tl::TimerListModel*>(this->vTimerList->model());
  const auto row = model->addTimer();

  const auto selectionModel = this->vTimerList->selectionModel();
  selectionModel->clearSelection();
  selectionModel->setCurrentIndex(model->index(row, 0), QItemSelectionModel::SelectCurrent);

  this->btnRemove->setEnabled(true);
}

void tl::TimerListWidget::removeTimer()
{
  const auto selectionModel = this->vTimerList->selectionModel();
  const auto removeIndex = selectionModel->currentIndex();
  const auto model = qobject_cast<tl::TimerListModel*>(this->vTimerList->model());
  model->removeTimer(removeIndex);
  selectionModel->clearSelection();

  const auto selectIndex = model->index(removeIndex.row() - 1, 0);
  if(selectIndex.isValid() == true)
  {
    selectionModel->setCurrentIndex(removeIndex, QItemSelectionModel::SelectCurrent);
  }

  this->btnRemove->setEnabled(model->rowCount() > 0);
}

void tl::TimerListWidget::loopChanged(int x)
{
  const auto model = qobject_cast<tl::TimerListModel*>(this->vTimerList->model());
  model->setLoop(x == Qt::Checked);
}
