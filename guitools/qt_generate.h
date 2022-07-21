#pragma once

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QString>
#include <QTableView>
#include <QWidget>

#include <tools/types.h>
#include <guitools/qt_conversions.h>

namespace qt_generate {

// Draw set of vertical labels in layout, updating row
void
draw_label_column(QWidget* parent,
                  QGridLayout* layout,
                  const vector<string>& label_txts,
                  i32& starting_row,
                  const i32 column);

// Draw set of vertical line edits in layout, updating row
vector<QLineEdit*>
draw_line_edit_column(QWidget* parent,
                      QGridLayout* layout,
                      i32& starting_row,
                      const i32 column,
                      const u32 quantity);

// Qt Table
template<typename T>
void
append_col(QStandardItemModel* model, const vector<T>& column)
{
  QList<QStandardItem*> col;
  for (const auto& val : column)
    col.append(new QStandardItem(qt_conv(val)));
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

template<typename... Ts>
void
append_row(QStandardItemModel* model, Ts&... values)
{
  QList<QStandardItem*> items;
  auto add_value_to_qlist = [](QList<QStandardItem*>& items, auto val) {
    items.append(new QStandardItem(qt_conv(val)));
  };
  (add_value_to_qlist(items, values), ...);
  model->appendRow(items);
}

void
delete_row(QStandardItemModel* model, const u32 row_index);

}
