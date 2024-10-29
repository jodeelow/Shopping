#include "coatsgui.h"
//#include "AdminGUI.h"

coatsgui::coatsgui(Controller& controller, QWidget* parent) : QMainWindow(parent), controller{ controller }
{
    //ui.setupUi(this);
    this->initGUI();
    this->connectSignalsAndSlots();
}

coatsgui::~coatsgui()
{}

void coatsgui::initGUI()
{
    this->adminButton = new QPushButton{ "Administrator" };
    this->userButton = new QPushButton{ "User" };
    this->exitButton = new QPushButton{ "Exit" };
    QHBoxLayout* buttonsLayout = new QHBoxLayout{};
    buttonsLayout->addWidget(this->adminButton);
    buttonsLayout->addWidget(this->userButton);
    buttonsLayout->addWidget(this->exitButton);
    QWidget* mainWindow = new QWidget{};
    mainWindow->setLayout(buttonsLayout);
    setCentralWidget(mainWindow);
}

void coatsgui::startAdminGUI()
{
    AdminGUI* agui = new AdminGUI{ this->controller };
}

void coatsgui::startUserGUI()
{
    UserGUI* ugui = new UserGUI{ this->controller };
}

void coatsgui::connectSignalsAndSlots()
{
    QObject::connect(this->adminButton, &QPushButton::clicked, this, &coatsgui::startAdminGUI);
    QObject::connect(this->userButton, &QPushButton::clicked, this, &coatsgui::startUserGUI);
    QObject::connect(this->exitButton, &QPushButton::clicked, this, &coatsgui::close);
}