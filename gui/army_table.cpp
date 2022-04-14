#include "army_table.h"
#include "ui_army_table.h"

Army_Table::Army_Table(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Army_Table)
{
    ui->setupUi(this);
}

Army_Table::~Army_Table()
{
    delete ui;
}
