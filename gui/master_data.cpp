#include "master_data.h"
#include "ui_master_data.h"

MasterData::MasterData(QWidget *parent, Texts* texts, Armies *armies,
                       Units* units)
    : QWidget(parent)
    , ui(new Ui::MasterData)
    , mode_(none)
    , table_model_(new QStandardItemModel)
    , texts_(texts)
    , armies_(armies)
{
    ui->setupUi(this);
    this->ui->tv_master_data->setModel(table_model_);

    QObject::connect(this->ui->pb_texts, &QPushButton::clicked,
                     this, &MasterData::show_texts_table);
    QObject::connect(this->ui->pb_armies, &QPushButton::clicked,
                     this, &MasterData::show_army_table);


    QObject::connect(this->ui->bb_okcanc, &QDialogButtonBox::rejected,
                     this, &MasterData::close);
}

bool MasterData::update_mode_and_clear_model(const mode new_mode)
{
    if(mode_ != new_mode)
    {
        table_model_->clear();
        mode_ = new_mode;
        return true;
    }
    return false;
}

void MasterData::show_texts_table()
{
    if(update_mode_and_clear_model(mode::texts))
    {
        create_table_model(table_model_, texts_->TextFields,
                           texts_->id_, texts_->txt_);
        this->ui->tv_master_data->resizeColumnsToContents();
    }
}

void MasterData::show_army_table()
{
    if(update_mode_and_clear_model(mode::armies))
    {
        create_table_model(table_model_, armies_->ArmyFields, armies_->id_,
                           armies_->txt_id_);
        this->ui->tv_master_data->resizeColumnsToContents();
    }
}

void MasterData::show_unit_table()
{
    if(update_mode_and_clear_model(mode::units))
    {
        create_table_model(table_model_, units_->UnitFields, units_->id_,
                           units_->txt_id_);
        this->ui->tv_master_data->resizeColumnsToContents();
    }
}


MasterData::~MasterData()
{
    delete ui;
}
