#include "TimerListView.h"

#include "TimeEditDelegate.h"
#include <QStyledItemDelegate>
#include <QTimeEdit>

tl::TimerListView::TimerListView(QWidget* parent) : QTableView(parent)
{
  this->setModel(new tl::TimerListModel(this));

  this->setItemDelegateForColumn(tl::TimerListModel::Column::Duration, new tl::TimeEditDelegate());
}
