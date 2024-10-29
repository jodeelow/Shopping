#pragma once

#include <QWidget>
#include "ui_UserGUI.h"
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

class UserGUI : public QWidget
{
	Q_OBJECT

public:
	UserGUI(Controller& controller, QWidget *parent = nullptr);
	~UserGUI();

private:
	Controller& controller;
	//string totalSum;
	int currentCoatIndex, totalBasketSum;
	string fileType, selectedSize;
	vector<Coat> shoppingBasket, filteredCoats;
	CSVRepository csvRepo;
	HTMLRepository htmlRepo;
	QComboBox* chooseFileComboBox;
	QPushButton* nextButton, * addToBasketButton, * exitShoppingSession, *filterCoatsButton, *seeCurrentCoatButton;
	QLabel* totalSumLabel;
	QLineEdit* sizeFillQLineEdit;
	QTableWidget* shoppingBasketTable;

	Ui::UserGUIClass ui;

	/*void readCoats(string filename);
	void writeCoats(string filename);*/

	void initUserGUI();
	void connectSignalsAndSlots();

	void fileTypeChange();
	void populateTable();
	void filterCoatsBySize();
	void addCoatToBasket();
	void goToNextCoat();
	void openLink();
	void writeBasketToFile();
	void openBasketFile();
	void exitUserGUI();
};
