#pragma once

#include <QStandardItemModel>

#include <generic/qt_conversions.h>
#include <generic/types.h>

namespace qt_table {

template<typename T>
void
append_col(QStandardItemModel* model, const vector<T>& column)
{
  QList<QStandardItem*> col;

  for (const auto& val : column) {
    col.append(new QStandardItem(qt_conv(val)));
  }
  model->appendColumn(col);
}

template<typename... Ts>
void
create_table_model(QStandardItemModel* model,
                   const vector<string>& header_labels,
                   const Ts&... columns)
{

  (append_col(model, columns), ...);
  model->setHorizontalHeaderLabels(qt_conv(header_labels));
}

}
