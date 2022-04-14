#ifndef ARMY_TABLE_H
#define ARMY_TABLE_H

#include <QWidget>

namespace Ui {
class Army_Table;
}

class Army_Table : public QWidget
{
    Q_OBJECT

public:
    explicit Army_Table(QWidget *parent = nullptr);
    ~Army_Table();

private:
    Ui::Army_Table *ui;
};

#endif // ARMY_TABLE_H
