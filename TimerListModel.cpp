#include "TimerListModel.h"

#include "Utilities.h"
#include <QIcon>

tl::TimerListModel::TimerListModel(QObject* parent) : QAbstractTableModel(parent)
{
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

  if(index.isValid() == true && this->player != nullptr)
  {
    if(const auto item = this->player->getItem(index.row()))
    {
      const auto column = static_cast<tl::TimerListModel::Column>(index.column());

      if(role == Qt::DisplayRole)
      {
        switch(column)
        {
        case tl::TimerListModel::Column::NowPlaying:
          break;
        case tl::TimerListModel::Column::Title:
          data = item->title;
          break;
        case tl::TimerListModel::Column::Duration:
          data = tl::util::MsToQTime(item->duration);
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
  if(index.isValid() == true && this->player != nullptr)
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
  if(this->player != nullptr)
  {
    return this->player->size();
  }

  return -1;
}

void tl::TimerListModel::setPlayer(tl::TimerPlayer* const x)
{
  this->player = x;
}

int tl::TimerListModel::addItem()
{
  auto row = -1;

  if(this->player != nullptr)
  {
    row = this->rowCount();
    this->beginInsertRows(QModelIndex(), row, row);
    this->player->addItem();
    this->endInsertRows();
  }

  return row;
}

void tl::TimerListModel::removeItem(const QModelIndex& index)
{
  if(this->player != nullptr)
  {
    if(index.isValid() == true && index.row() >= 0 && index.row() < this->player->size())
    {
      this->beginRemoveRows(QModelIndex(), index.row(), index.row());
      this->player->removeItem(index.row());
      this->endRemoveRows();
    }
  }
}
