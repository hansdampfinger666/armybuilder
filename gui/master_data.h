#pragma once

#include <QWidget>
#include <QStandardItemModel>
#include <QList>
#include <QStandardItem>

#include <database/database.h>
#include <generic/vec_ops.h>
#include <generic/qt_conversions.h>
#include <generic/qt_table.h>
#include <gui/singlearmywin.h>

namespace Ui {
class MasterData;
}

class MasterData : public QWidget
{
    Q_OBJECT

public:
    enum mode : i32
    {
        none    = 0,
        texts   = 1,
        armies  = 2,
        units   = 3,
        models  = 4
    };

    explicit MasterData(QWidget *parent = nullptr, Texts* texts = nullptr,
                        Armies* armies = nullptr, Units* units = nullptr,
                        Models* moddels = nullptr);
    ~MasterData();

    void show_texts_table();
    void show_army_table();
    void show_unit_table();
    void show_model_table();
    bool update_mode_and_clear_model(const mode new_mode);
	bool add_data_set();
	bool delete_data_set();
	
	bool open_single_army_win();

private:
    Ui::MasterData* ui;
    mode mode_;
    QStandardItemModel* table_model_;
    Texts* texts_;
    Armies* armies_;
    Units* units_;
    Models* models_;
	SingleArmyWin* single_army_win_;
};
