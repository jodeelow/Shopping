#include "UserGUI.h"
#include <QComboBox>
#include <QMessageBox>
using namespace std;

UserGUI::UserGUI(Controller& controller, QWidget* parent) : QWidget(parent), controller{controller}
{
	//ui.setupUi(this);
    this->initUserGUI();
    this->connectSignalsAndSlots();
}

UserGUI::~UserGUI()
{}

void UserGUI::initUserGUI()
{
    //main layout
    QVBoxLayout* mainLayout = new QVBoxLayout{};

    //layout for choosing file type
    this->chooseFileComboBox = new QComboBox{};
    this->chooseFileComboBox->addItem("CSV");
    this->chooseFileComboBox->addItem("HTML");
    QFormLayout* fileTypeLayout = new QFormLayout{};
    QLabel* chooseFileLabel = new QLabel{ "File type:" };
    chooseFileLabel->setBuddy(this->chooseFileComboBox);
    fileTypeLayout->addRow(chooseFileLabel, this->chooseFileComboBox);

    mainLayout->addLayout(fileTypeLayout);

    //layout for selecting the size of the coat
    QHBoxLayout* selectSizeLayout = new QHBoxLayout{};

    selectSizeLayout->addWidget(new QLabel{ "Size: " });
    this->sizeFillQLineEdit = new QLineEdit{};
    selectSizeLayout->addWidget(this->sizeFillQLineEdit);
    this->filterCoatsButton = new QPushButton{"Filter coats"};
    selectSizeLayout->addWidget(this->filterCoatsButton);
    mainLayout->addLayout(selectSizeLayout);

    //layout for next button and add to basket button
    QHBoxLayout* buttonsLayout = new QHBoxLayout{};
    this->nextButton = new QPushButton{ "Next" };
    this->addToBasketButton = new QPushButton{ "Add to basket" };

    this->seeCurrentCoatButton = new QPushButton{ "See coat" };

    buttonsLayout->addWidget(this->nextButton);
    buttonsLayout->addWidget(this->seeCurrentCoatButton);
    buttonsLayout->addWidget(this->addToBasketButton);
    mainLayout->addLayout(buttonsLayout);

    //layout for showing the basket
    QVBoxLayout* basketLayout = new QVBoxLayout{};
    basketLayout->addWidget(new QLabel{ "Your shopping basket:" });
    this->shoppingBasketTable = new QTableWidget{};
    this->shoppingBasketTable->setColumnCount(5);

    //headers of columns in table
    QStringList headers;
    headers << "Size" << "Colour" << "Price" << "Quantity" << "Photograph";
    this->shoppingBasketTable->setHorizontalHeaderLabels(headers);
    this->shoppingBasketTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    this->shoppingBasketTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Stretch columns to fill available space
    basketLayout->addWidget(this->shoppingBasketTable);
    mainLayout->addLayout(basketLayout);

    //label for showing the total sum of the basket
    this->totalSumLabel = new QLabel{ "Total: 0 lei" };
    mainLayout->addWidget(this->totalSumLabel);

    //button for exitting the current shopping session
    this->exitShoppingSession = new QPushButton{ "Exit shopping session" };
    mainLayout->addWidget(this->exitShoppingSession);

    this->controller.read_coats("coats.txt");
    this->totalBasketSum = 0;
    this->fileType = "CSV";
    this->setLayout(mainLayout);
    this->show();
}

void UserGUI::fileTypeChange()
{
    this->fileType = this->chooseFileComboBox->currentText().toStdString();
}

void UserGUI::openLink()
{
    if (this->filteredCoats.size() != 0)
    {
        string link = this->filteredCoats[this->currentCoatIndex].get_photograph();
        const char* command = "start ";
        string open_link = command + link;
        system(open_link.c_str());
    }
    else
    {
        QMessageBox* errors = new QMessageBox{};
        errors->setText("No coat with chosen size was found!");
        errors->setIcon(QMessageBox::Critical);
        errors->setWindowTitle("Errors");
        errors->exec();
    }
}

void UserGUI::filterCoatsBySize()
{
    filteredCoats.clear();
    for (Coat& c : this->controller.get_coats_repo().get_coats())
    {
        if(c.get_size() == this->sizeFillQLineEdit->text().toStdString())
            this->filteredCoats.push_back(c);
    }
    this->currentCoatIndex = 0;
}

void UserGUI::populateTable()
{
    this->shoppingBasketTable->clear();
    QStringList headers;
    headers << "Size" << "Colour" << "Price" << "Quantity" << "Photograph";
    this->shoppingBasketTable->setHorizontalHeaderLabels(headers);
    vector<Coat> coats = this->shoppingBasket;
    int row = 0;
    for (Coat& c : coats)
    {
        this->shoppingBasketTable->insertRow(row);
        this->shoppingBasketTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(c.get_size())));
        this->shoppingBasketTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(c.get_colour())));
        this->shoppingBasketTable->setItem(row, 2, new QTableWidgetItem(QString::number(c.get_price())));
        this->shoppingBasketTable->setItem(row, 3, new QTableWidgetItem(QString::number(c.get_quantity())));
        this->shoppingBasketTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(c.get_photograph())));
        row++;
    }
    this->totalSumLabel->setText(QString::fromStdString("Total: " + to_string(this->totalBasketSum) + "lei"));
}

void UserGUI::addCoatToBasket()
{
    if (this->filteredCoats.size() != 0)
    {
        this->totalBasketSum += this->filteredCoats[this->currentCoatIndex].get_price();
        this->shoppingBasket.push_back(this->filteredCoats[this->currentCoatIndex]);
        this->populateTable();
    }
    else
    {
        QMessageBox* errors = new QMessageBox{};
        errors->setText("No coat with chosen size was found!");
        errors->setIcon(QMessageBox::Critical);
        errors->setWindowTitle("Errors");
        errors->exec();
    }
}

void UserGUI::goToNextCoat()
{
    if (this->filteredCoats.size() == 0 || this->currentCoatIndex == this->filteredCoats.size() - 1)
    {
        this->currentCoatIndex = 0;
    }
    else
        this->currentCoatIndex++;
}

void UserGUI::writeBasketToFile()
{
    if (this->fileType == "CSV")
    {
        CSVRepository csvRepo{};
        for (Coat& c : this->shoppingBasket)
        {
            csvRepo.add_coat(c);
        }
        csvRepo.write_coats("basket.csv");
    }
    else if (this->fileType == "HTML")
    {
        HTMLRepository htmlRepo{};
        for (Coat& c : this->shoppingBasket)
        {
            htmlRepo.add_coat(c);
        }
        htmlRepo.write_coats("basket.html");
    }
}

void UserGUI::openBasketFile()
{
    if (this->fileType == "CSV")
    {
        string filename = "basket.csv";
		string command = "notepad \"" + filename + "\"";
		system(command.c_str());
    }
    else if (this->fileType == "HTML")
    {
        string filename = "basket.html";
        string command = "start " + filename;
        system(command.c_str());
    }
}

void UserGUI::exitUserGUI()
{
    this->close();
}

void UserGUI::connectSignalsAndSlots()
{
    QObject::connect(this->chooseFileComboBox, &QComboBox::currentTextChanged, this, &UserGUI::fileTypeChange);
    QObject::connect(this->filterCoatsButton, &QPushButton::clicked, this, &UserGUI::filterCoatsBySize);
    QObject::connect(this->seeCurrentCoatButton, &QPushButton::clicked, this, &UserGUI::openLink);
    QObject::connect(this->addToBasketButton, &QPushButton::clicked, this, &UserGUI::addCoatToBasket);
    QObject::connect(this->nextButton, &QPushButton::clicked, this, &UserGUI::goToNextCoat);
    QObject::connect(this->exitShoppingSession, &QPushButton::clicked, this, &UserGUI::exitUserGUI);
    QObject::connect(this->exitShoppingSession, &QPushButton::clicked, this, &UserGUI::writeBasketToFile);
    QObject::connect(this->exitShoppingSession, &QPushButton::clicked, this, &UserGUI::openBasketFile);
}
