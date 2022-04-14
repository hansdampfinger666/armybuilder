#pragma once

#include <QWidget>
#include <QStandardItemModel>
#include <QList>
#include <QStandardItem>

#include <database/text.h>
#include <database/army.h>
#include <database/unit.h>
#include <generic/vec_ops.h>
#include <generic/qt_conversions.h>
#include <generic/qt_table.h>


namespace Ui {
class MasterData;
}

class MasterData : public QWidget
{
    Q_OBJECT

public:
    enum mode : uint32
    {
        none    = 0,
        texts   = 1,
        armies  = 2,
        units   = 3
    };

    explicit MasterData(QWidget *parent = nullptr, Texts* texts = nullptr,
                        Armies* armies = nullptr, Units* units = nullptr);
    ~MasterData();

    void show_texts_table();
    void show_army_table();
    void show_unit_table();
    bool update_mode_and_clear_model(const mode new_mode);

private:
    Ui::MasterData* ui;
    mode mode_;
    QStandardItemModel* table_model_;
    Texts* texts_;
    Armies* armies_;
    Units* units_;
};
