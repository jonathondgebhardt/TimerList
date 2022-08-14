#include "TimerListModel.h"

#include "Utilities.h"
#include <QTime>

tl::TimerListModel::TimerListModel(QObject* parent) : QAbstractTableModel(parent), player(new tl::TimerPlayer(this))
{
  this->connect(this->player, &tl::TimerPlayer::timerStarted, this, &tl::TimerListModel::timerChanged);
}

Qt::ItemFlags tl::TimerListModel::flags(const QModelIndex& index) const
{
  Qt::ItemFlags flags(Qt::NoItemFlags);

  if(index.isValid() == true)
  {
    flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    const auto column = static_cast<tl::TimerListModel::Column>(index.column());
    switch(column)
    {
    case tl::TimerListModel::Column::NowPlaying:
      break;
    case tl::TimerListModel::Column::Title:
    case tl::TimerListModel::Column::Duration:
      flags |= Qt::ItemIsEditable;
      break;
    default:
      break;
    }
  }

  return flags;
}

QVariant tl::TimerListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  QVariant header;

  if(role == Qt::DisplayRole)
  {
    if(orientation == Qt::Horizontal)
    {
      const auto column = static_cast<tl::TimerListModel::Column>(section);
      switch(column)
      {
      case tl::TimerListModel::Column::NowPlaying:
        header = "Now Playing";
        break;
      case tl::TimerListModel::Column::Title:
        header = "Title";
        break;
      case tl::TimerListModel::Column::Duration:
        header = "Duration";
        break;
      default:
        break;
      }
    }
  }

  return header;
}

int tl::TimerListModel::columnCount(const QModelIndex&) const
{
  return tl::TimerListModel::Column::Count;
}

QVariant tl::TimerListModel::data(const QModelIndex& index, int role) const
{
  QVariant data;

  if(index.isValid() == true)
  {
    if(role == Qt::DisplayRole)
    {
      if(const auto item = this->player->getItem(index.row()))
      {
        const auto column = static_cast<tl::TimerListModel::Column>(index.column());
        switch(column)
        {
        case tl::TimerListModel::Column::NowPlaying:
          data = (index.row() == this->currentTimer) ? "This" : "";
          break;
        case tl::TimerListModel::Column::Title:
          data = item->title;
          break;
        case tl::TimerListModel::Column::Duration:
          data = tl::util::MsToTimeString(item->duration);
          break;
        default:
          break;
        }
      }
    }
  }

  return data;
}

bool tl::TimerListModel::setData(const QModelIndex& index, const QVariant& value, int)
{
  if(index.isValid() == true)
  {
    if(const auto item = this->player->getItem(index.row()))
    {
      const auto column = static_cast<tl::TimerListModel::Column>(index.column());
      switch(column)
      {
      case tl::TimerListModel::Column::NowPlaying:
        break;
      case tl::TimerListModel::Column::Title:
        item->title = value.toString();
        this->dataChanged(index, index, {Qt::EditRole});
        break;
      case tl::TimerListModel::Column::Duration:
        item->duration = value.toInt();
        this->dataChanged(index, index, {Qt::EditRole});
        break;
      default:
        break;
      }

      return true;
    }
  }

  return false;
}

int tl::TimerListModel::rowCount(const QModelIndex&) const
{
  return this->player->size();
}

void tl::TimerListModel::playPause()
{
  if(this->player->getIsPaused() == true)
  {
    this->player->play();
  }
  else
  {
    this->player->pause();
  }
}

void tl::TimerListModel::stop()
{
  this->player->stop();
}

void tl::TimerListModel::pause()
{
  this->player->pause();
}

int tl::TimerListModel::addTimer()
{
  const auto row = this->rowCount();
  this->beginInsertRows(QModelIndex(), row, row);
  this->player->addTimer();
  this->endInsertRows();

  return row;
}

void tl::TimerListModel::removeTimer(const QModelIndex& index)
{
  if(index.isValid() == true && index.row() >= 0 && index.row() < this->player->size())
  {
    this->beginRemoveRows(QModelIndex(), index.row(), index.row());
    this->player->removeTimer(index.row());
    this->endRemoveRows();
  }
}

void tl::TimerListModel::timerChanged(int x)
{
  this->currentTimer = x;
}

void tl::TimerListModel::setLoop(bool x)
{
  this->player->setLoop(x);
}
