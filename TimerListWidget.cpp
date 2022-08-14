#include "TimerListWidget.h"

#include "TimerListModel.h"
#include <QBoxLayout>

tl::TimerListWidget::TimerListWidget(tl::TimerPlayer* const player, QWidget* parent)
    : QWidget(parent),
      vTimerList(new tl::TimerListView(this)),
      btnPlay(new QPushButton("Play", this)),
      btnPause(new QPushButton("Pause", this)),
      btnStop(new QPushButton("Stop", this)),
      chkLoop(new QCheckBox("Loop", this)),
      btnAdd(new QPushButton("Add", this)),
      btnRemove(new QPushButton("Remove", this))
{
  const auto parentLayout = new QVBoxLayout(this);

  {
    const auto hLayout = new QHBoxLayout();
    parentLayout->addLayout(hLayout);

    hLayout->addWidget(this->btnPlay);

    this->btnPause->setEnabled(false);
    hLayout->addWidget(this->btnPause);

    this->btnStop->setEnabled(false);
    hLayout->addWidget(this->btnStop);
  }

  {
    const auto hLayout = new QHBoxLayout();
    parentLayout->addLayout(hLayout);

    hLayout->addWidget(this->vTimerList);

    const auto buttonLayout = new QVBoxLayout();

    this->chkLoop->setChecked(true);
    this->loopChanged(Qt::Checked);
    buttonLayout->addWidget(this->chkLoop);

    buttonLayout->addWidget(this->btnAdd);

    buttonLayout->addWidget(this->btnRemove);
    this->btnRemove->setEnabled(false);

    hLayout->addLayout(buttonLayout);
  }

  this->connect(this->btnPlay, &QPushButton::clicked, this, &tl::TimerListWidget::play);
  this->connect(this->btnPause, &QPushButton::clicked, this, &tl::TimerListWidget::pause);
  this->connect(this->btnStop, &QPushButton::clicked, this, &tl::TimerListWidget::stop);
  this->connect(this->chkLoop, &QCheckBox::stateChanged, this, &tl::TimerListWidget::loopChanged);
  this->connect(this->btnAdd, &QPushButton::clicked, this, &tl::TimerListWidget::addItem);
  this->connect(this->btnRemove, &QPushButton::clicked, this, &tl::TimerListWidget::removeItem);

  this->setPlayer(player);
}

void tl::TimerListWidget::setPlayer(tl::TimerPlayer* const x)
{
  this->player = x;

  if(this->player != nullptr)
  {
    this->player->setLoop(this->chkLoop->isChecked());
    this->connect(this->player, &tl::TimerPlayer::done, this, &tl::TimerListWidget::stop);
  }

  const auto model = qobject_cast<tl::TimerListModel*>(this->vTimerList->model());
  model->setPlayer(x);
}

void tl::TimerListWidget::play()
{

  if(this->player != nullptr)
  {
    this->player->play();
  }

  this->btnPlay->setEnabled(false);
  this->btnPause->setEnabled(true);
  this->btnStop->setEnabled(true);
}

void tl::TimerListWidget::pause()
{
  if(this->player != nullptr)
  {
    this->player->pause();
  }

  this->btnPlay->setEnabled(true);
  this->btnPause->setEnabled(false);
  this->btnStop->setEnabled(true);
}

void tl::TimerListWidget::stop()
{
  if(this->player != nullptr)
  {
    this->player->stop();
  }

  this->btnPlay->setEnabled(true);
  this->btnPause->setEnabled(false);
  this->btnStop->setEnabled(false);
}

void tl::TimerListWidget::loopChanged(int x)
{
  if(this->player != nullptr)
  {
    this->player->setLoop(x == Qt::Checked);
  }
}

void tl::TimerListWidget::addItem()
{
  const auto model = qobject_cast<tl::TimerListModel*>(this->vTimerList->model());
  const auto row = model->addItem();

  const auto selectionModel = this->vTimerList->selectionModel();
  selectionModel->clearSelection();
  selectionModel->setCurrentIndex(model->index(row, 0), QItemSelectionModel::SelectCurrent);

  this->btnRemove->setEnabled(true);
}

void tl::TimerListWidget::removeItem()
{
  const auto selectionModel = this->vTimerList->selectionModel();
  const auto removeIndex = selectionModel->currentIndex();
  const auto model = qobject_cast<tl::TimerListModel*>(this->vTimerList->model());
  model->removeItem(removeIndex);
  selectionModel->clearSelection();

  const auto selectIndex = model->index(removeIndex.row() - 1, 0);
  if(selectIndex.isValid() == true)
  {
    selectionModel->setCurrentIndex(removeIndex, QItemSelectionModel::SelectCurrent);
  }

  this->btnRemove->setEnabled(model->rowCount() > 0);
}
