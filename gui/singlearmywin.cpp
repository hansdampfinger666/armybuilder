#include "singlearmywin.h"
#include "ui_singlearmywin.h"

SingleArmyWin::SingleArmyWin(QWidget *parent, Armies* armies) :
    QDialog(parent),
    ui(new Ui::SingleArmyWin),
	armies_(armies)
{
	auto line = new QLineEdit(this);
	

    ui->setupUi(this);
	QObject::connect(this->ui->buttonBox, &QDialogButtonBox::rejected,
					 this, &SingleArmyWin::close);
	

}

SingleArmyWin::~SingleArmyWin()
{
    delete ui;
}
