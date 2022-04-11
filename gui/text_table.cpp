#include "text_table.h"
#include "ui_text_table.h"

TextTable::TextTable(QWidget *parent, Texts* texts) :
    QWidget(parent),
    ui(new Ui::TextTable),
    table_model_(new QStandardItemModel())
{
    ui->setupUi(this);
    texts_ = texts;

    this->ui->tv_texts->setModel(table_model_);
    prep_text_table();

    QObject::connect(this->ui->bb_okcanc, &QDialogButtonBox::rejected,
                     this, &TextTable::close);
}


void TextTable::prep_text_table()
{
    create_table_model(table_model_, TextFields, texts_->id_, texts_->txt_);
    this->ui->tv_texts->resizeColumnsToContents();
}


TextTable::~TextTable()
{
    delete ui;
}
