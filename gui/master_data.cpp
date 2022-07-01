#include "master_data.h"
#include "ui_master_data.h"

MasterData::MasterData(QWidget *parent, Texts* texts, Armies *armies,
                       Units* units, Models* models)
    : QWidget(parent)
    , ui(new Ui::MasterData)
    , mode_(none)
    , table_model_(new QStandardItemModel)
    , texts_(texts)
    , armies_(armies)
    , units_(units)
    , models_(models)
{
    ui->setupUi(this);
    this->ui->tv_master_data->setModel(table_model_);

    QObject::connect(this->ui->pb_texts, &QPushButton::clicked,
                     this, &MasterData::show_texts_table);
    QObject::connect(this->ui->pb_armies, &QPushButton::clicked,
                     this, &MasterData::show_army_table);
    QObject::connect(this->ui->pb_units, &QPushButton::clicked,
                     this, &MasterData::show_unit_table);
    QObject::connect(this->ui->pb_models, &QPushButton::clicked,
                     this, &MasterData::show_model_table);

	QObject::connect(this->ui->pb_add, &QPushButton::clicked,
					 this, &MasterData::add_data_set);
	QObject::connect(this->ui->pb_delete, &QPushButton::clicked,
					 this, &MasterData::delete_data_set);

    QObject::connect(this->ui->bb_okcanc, &QDialogButtonBox::rejected,
                     this, &MasterData::close);
}

bool MasterData::add_data_set()
{
	switch(mode_) {
	case mode::texts:
		 break;
	case mode::armies:

	    //		 single_army_win_ = new SingleArmyWin(this, armies_);
	    //		 single_army_win_->show();
	    break;
	case mode::units:
		 break;
	case mode::models:
		 break;		
	}
}

bool MasterData::delete_data_set()
{
	switch(mode_) {
	case mode::texts:
		 break;
	case mode::armies:
		 break;
	case mode::units:
		 break;
	case mode::models:
		 break;		
	}
}

bool MasterData::update_mode_and_clear_model(const mode new_mode) 
{
    if (mode_ != new_mode) 
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

void MasterData::show_model_table()
{
    if(update_mode_and_clear_model(mode::models))
    {
        create_table_model(table_model_, models_->ModelFields,
                           models_->army_id_, models_->unit_id_, models_->id_,
                           models_->txt_id_);
        this->ui->tv_master_data->resizeColumnsToContents();
    }
}

MasterData::~MasterData()
{
    delete ui;
}
