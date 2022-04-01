#pragma once

#include <QWidget>
#include <QStandardItemModel>
#include <QList>
#include <QStandardItem>

#include <database/text.h>
#include <generic/vec_ops.h>
#include <generic/qt_conversions.h>
#include <generic/qt_table.h>


namespace Ui {
class TextTable;
}

class TextTable : public QWidget
{
    Q_OBJECT

public:
    explicit TextTable(QWidget *parent = nullptr,
                       Texts* texts = nullptr);
    ~TextTable();

    void prep_text_table();

private:
    Ui::TextTable* ui;
    Texts* texts_;
    QStandardItemModel* table_model_;
};
