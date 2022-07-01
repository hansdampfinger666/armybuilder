#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>

#include <generic/types.h>
#include <generic/qt_table.h>
#include <database/database.h>

class DatabaseViewer : public QWidget
{
	Q_OBJECT

public:
		DatabaseViewer(QWidget* parent, const db* db);
		~DatabaseViewer();

private:
		const db* db_;

		QTableView* table_view_ = nullptr;

		QStandardItemModel* tab_model_ = nullptr;
		QGridLayout* layout_ = nullptr;
		vector<QPushButton*> buttons_ = {}; 

		void switch_tables();
};
