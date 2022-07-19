#include "qt_generate.h"

void
qt_generate::draw_label_column(QWidget* parent,
                               QGridLayout* layout,
                               const vector<string>& label_txts,
                               i32& starting_row,
                               const i32 column)
{
  for (const auto& label_txt : label_txts) {
    layout->addWidget(new QLabel(QString::fromStdString(label_txt), parent),
                      starting_row,
                      column);
    starting_row++;
  }
}

vector<QLineEdit*>
qt_generate::draw_line_edit_column(QWidget* parent,
                                   QGridLayout* layout,
                                   i32& starting_row,
                                   const i32 column,
                                   const u32 quantity)
{
  vector<QLineEdit*> result;
  for (u32 i = 1; i <= quantity; i++) {
    auto line = new QLineEdit(parent);
    layout->addWidget(line, starting_row, column);
    starting_row = starting_row + i;
    result.emplace_back(line);
  }
  return result;
}

void
qt_generate::delete_row(QStandardItemModel* model, const u32 row_index)
{
  model->takeRow(row_index);
}
