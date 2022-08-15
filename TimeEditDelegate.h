#pragma once

#include "Utilities.h"
#include <QLineEdit>
#include <QStyledItemDelegate>
#include <QTime>

namespace tl
{
  /// https://stackoverflow.com/questions/29500920/qt-model-view-defining-format-of-items-holding-date
  class TimeEditDelegate : public QStyledItemDelegate
  {
    Q_OBJECT
  public:
    TimeEditDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent)
    {
    }

    virtual QString displayText(const QVariant& value, const QLocale&) const override
    {
      QString text;

      if(value.type() == QVariant::Time)
      {
        return value.toTime().toString();
      }

      return text;
    }

    virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex&) const override
    {
      const auto editor = new QLineEdit(parent);
      editor->setInputMask("00:00:00");
      return editor;
    }

    virtual void setEditorData(QWidget* editor, const QModelIndex& index) const override
    {
      const auto model = index.model();
      const auto data = model->data(index, Qt::DisplayRole);
      if(data.type() == QVariant::Time)
      {
        qobject_cast<QLineEdit*>(editor)->setText(data.toTime().toString());
      }
    }

    virtual void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override
    {
      const auto time = QTime::fromString(qobject_cast<QLineEdit*>(editor)->text());
      const auto ms = tl::util::QTimeToMs(time);
      model->setData(index, QVariant(ms), Qt::EditRole);
    }
  };
} // namespace tl
