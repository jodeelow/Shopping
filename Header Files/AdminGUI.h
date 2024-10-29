#pragma once

#include <QWidget>
#include "ui_AdminGUI.h"
#include "CoatException.h"
#include <QtWidgets/QMainWindow>
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QHBoxLayout>
#include <QFormLayout>
#include <fstream>
#include <QTableWidget>
#include <QHeaderView>

class AdminGUI : public QWidget
{
	Q_OBJECT

public:
	AdminGUI(Controller& controller, QWidget* parent = nullptr);
	~AdminGUI();

	void readCoats(string filename);
	void writeCoats(string filename);
	void populateTable();

private:
	Controller& controller;

	QPushButton* addButton;
	QPushButton* updateButton;
	QPushButton* removeButton;
	QTableWidget* coatsTable;
	QLineEdit* sizeFill, * colourFill, * priceFill, * quantityFill, * photographFill;
	string oldSize, oldColour, oldPhotograph;

	void initAdminGUI();
	void connectSignalsAndSlots();

	//slot for filling the form
	void tableSelectionChanged();

	void addCoat();
	void removeCoat();
	void updateCoat();

	Ui::AdminGUIClass ui;

	//private slots:
	//	void tableSelectionChanged();
};
