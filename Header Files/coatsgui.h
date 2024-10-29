#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_coatsgui.h"
#include "CoatException.h"
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
#include "AdminGUI.h"
#include "UserGUI.h"

class coatsgui : public QMainWindow
{
    Q_OBJECT

public:
    coatsgui(Controller& controller, QWidget* parent = nullptr);
    ~coatsgui();

private:
    Controller& controller;

    QPushButton* adminButton;
    QPushButton* userButton;
    QPushButton* exitButton;

    void initGUI();
    void connectSignalsAndSlots();
    void startAdminGUI();
    void startUserGUI();

    Ui::coatsguiClass ui;
};
