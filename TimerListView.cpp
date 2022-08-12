#include "TimerListView.h"

tl::TimerListView::TimerListView(QWidget* parent) : QTableView(parent)
{
  this->setModel(new tl::TimerListModel(this));
}
