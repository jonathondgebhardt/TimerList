#pragma once

#include "TimerPlayer.h"
#include <QAbstractTableModel>
#include <memory>
#include <vector>

namespace tl
{
  class TimerListModel : public QAbstractTableModel
  {
    Q_OBJECT

  public:
    enum Column
    {
      NowPlaying = 0,
      Title,
      Duration,
      Count
    };

    TimerListModel(QObject* parent = nullptr);
    virtual ~TimerListModel() = default;

    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = 0) const override;
    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;

  public slots:
    void setPlayer(tl::TimerPlayer* const x);

    int addItem();
    void removeItem(const QModelIndex& index);

  private:
    tl::TimerPlayer* player{nullptr};
  };
} // namespace tl
