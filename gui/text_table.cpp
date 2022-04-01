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


//    for(int i = 0; auto& col_name : qt_conv(TextLabels))
//    {
//        table_model_->setHorizontalHeaderItem(i, new QStandardItem(col_name));
//        i++;
//    }
//    auto txt_indexes = texts_->get_indexes(NotInitial);

//    for(auto txt_index : txt_indexes)
//    {
//        QList<QStandardItem*> row{
//            new QStandardItem(QString::number(texts_->id_[txt_index])),
//            new QStandardItem(QString::fromStdString(texts_->txt_[txt_index]))
//        };
//        table_model_->appendRow(row);
//    }
    this->ui->tv_texts->resizeColumnsToContents();
}


TextTable::~TextTable()
{
    delete ui;
}
