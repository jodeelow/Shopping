#include "AdminGUI.h"
#include <QMessageBox>

AdminGUI::AdminGUI(Controller& controller, QWidget* parent) : QWidget(parent), controller{ controller }
{
    //ui.setupUi(this);
    this->initAdminGUI();
    this->connectSignalsAndSlots();
}

AdminGUI::~AdminGUI()
{}

void AdminGUI::readCoats(string filename)
{
    ifstream fin(filename);
    if (!fin.is_open())
        return;

    Coat c;
    while (fin >> c)
    {
        this->controller.add_element_controller(c);
        //cout << c << endl;
    }

    fin.close();
}

void AdminGUI::writeCoats(string filename)
{
    ofstream fout(filename);
    if (!fout.is_open())
        return;

    for (const auto& coat : this->controller.get_coats_repo().get_coats())
        fout << coat;

    fout.close();
}

void AdminGUI::addCoat()
{
    CoatValidator cv{ this->controller };
    string size = this->sizeFill->text().toStdString();
    string colour = this->colourFill->text().toStdString();
    double price = this->priceFill->text().toDouble();
    int quantity = this->quantityFill->text().toInt();
    string photograph = this->photographFill->text().toStdString();

    Coat c{ size, colour, price, quantity, photograph };
    try
    {
        cv.validate_add(c);
        this->controller.add_element_controller(c);
        this->populateTable();

        //write to file!!!
        this->writeCoats("coats.txt");
    }
    catch (CoatException& ex)
    {
        QMessageBox* errors = new QMessageBox{};
        errors->setText(QString::fromStdString(ex.get_message()));
        errors->setIcon(QMessageBox::Critical);
        errors->setWindowTitle("Errors");
        errors->exec();
    }
}

void AdminGUI::removeCoat()
{
    CoatValidator cv{ this->controller };
    string size = this->sizeFill->text().toStdString();
    string colour = this->colourFill->text().toStdString();
    string photograph = this->photographFill->text().toStdString();

    try
    {
        cv.validate_remove(size, colour, photograph);
        this->controller.remove_element_controller(size, colour, photograph);
        this->populateTable();

        //write to file!!!
        this->writeCoats("coats.txt");
    }
    catch (CoatException& ex)
    {
        QMessageBox* errors = new QMessageBox{};
        errors->setText(QString::fromStdString(ex.get_message()));
        errors->setIcon(QMessageBox::Critical);
        errors->setWindowTitle("Errors");
        errors->exec();
    }
}

void AdminGUI::updateCoat()
{
    CoatValidator cv{ this->controller };

    try
    {
        cv.validate_remove(this->oldSize, this->oldColour, this->oldPhotograph);

        string new_size = this->sizeFill->text().toStdString();
        string new_colour = this->colourFill->text().toStdString();
        double new_price = this->priceFill->text().toDouble();
        int new_quantity = this->quantityFill->text().toInt();
        string new_photograph = this->photographFill->text().toStdString();
        Coat c{ new_size, new_colour, new_price, new_quantity, new_photograph };
        cv.validate_add(c);
        this->controller.update_element_controller(this->oldSize, this->oldColour, this->oldPhotograph, c);
        this->populateTable();

        //write to file!!!
        this->writeCoats("coats.txt");
    }
    catch (CoatException& ex)
    {
        QMessageBox* errors = new QMessageBox{};
        errors->setText(QString::fromStdString(ex.get_message()));
        errors->setIcon(QMessageBox::Critical);
        errors->setWindowTitle("Errors");
        errors->exec();
    }
}

void AdminGUI::tableSelectionChanged()
{
    //Get the selected row
    int selectedRow = this->coatsTable->currentRow();
    if (selectedRow < 0)
    {
        //nothing was selected
        return;
    }

    //retrieving data from the selected row and setting it to the form fields
    this->sizeFill->setText(this->coatsTable->item(selectedRow, 0)->text());
    this->colourFill->setText(this->coatsTable->item(selectedRow, 1)->text());
    this->priceFill->setText(this->coatsTable->item(selectedRow, 2)->text());
    this->quantityFill->setText(this->coatsTable->item(selectedRow, 3)->text());
    this->photographFill->setText(this->coatsTable->item(selectedRow, 4)->text());

    this->oldSize = this->sizeFill->text().toStdString();
    this->oldColour = this->colourFill->text().toStdString();
    this->oldPhotograph = this->photographFill->text().toStdString();
}

void AdminGUI::populateTable()
{
    this->coatsTable->clear();
    QStringList headers;
    headers << "Size" << "Colour" << "Price" << "Quantity" << "Photograph";
    this->coatsTable->setHorizontalHeaderLabels(headers);
    vector<Coat> coats = this->controller.get_coats_repo().get_coats();
    int row = 0;
    for (Coat& c : coats)
    {
        this->coatsTable->insertRow(row);
        this->coatsTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(c.get_size())));
        this->coatsTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(c.get_colour())));
        this->coatsTable->setItem(row, 2, new QTableWidgetItem(QString::number(c.get_price())));
        this->coatsTable->setItem(row, 3, new QTableWidgetItem(QString::number(c.get_quantity())));
        this->coatsTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(c.get_photograph())));
        row++;
    }
}

void AdminGUI::initAdminGUI()
{
    QVBoxLayout* layout = new QVBoxLayout{};
    this->addButton = new QPushButton{ "Add" };
    this->updateButton = new QPushButton{ "Update" };
    this->removeButton = new QPushButton{ "Remove" };

    QGridLayout* buttonslayout = new QGridLayout{};

    buttonslayout->addWidget(addButton, 0, 0);
    buttonslayout->addWidget(updateButton, 0, 1);
    buttonslayout->addWidget(removeButton, 0, 2);

    layout->addLayout(buttonslayout);

    // Create a table widget
    this->coatsTable = new QTableWidget{};
    this->coatsTable->setColumnCount(5); // Set the number of columns

    // Set column headers
    QStringList headers;
    headers << "Size" << "Colour" << "Price" << "Quantity" << "Photograph";
    this->coatsTable->setHorizontalHeaderLabels(headers);

    //populating the table and extracting the coats in memory
    this->readCoats("coats.txt");
    this->populateTable();

    this->coatsTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    this->coatsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Stretch columns to fill available space

    QHBoxLayout* tableAndFormLayout = new QHBoxLayout{};
    tableAndFormLayout->addWidget(coatsTable);

    QFormLayout* fl = new QFormLayout{};

    this->sizeFill = new QLineEdit{};
    QLabel* sizeLabel = new QLabel{ "Size: " };
    sizeLabel->setBuddy(this->sizeFill);

    this->colourFill = new QLineEdit{};
    QLabel* colourLabel = new QLabel{ "Colour: " };
    colourLabel->setBuddy(this->colourFill);

    this->priceFill = new QLineEdit{};
    QLabel* priceLabel = new QLabel{ "Price: " };
    priceLabel->setBuddy(this->priceFill);

    this->quantityFill = new QLineEdit{};
    QLabel* quantityLabel = new QLabel{ "Quantity: " };
    quantityLabel->setBuddy(this->quantityFill);

    this->photographFill = new QLineEdit{};
    QLabel* photographLabel = new QLabel{ "Photograph: " };
    photographLabel->setBuddy(this->photographFill);

    fl->addRow(sizeLabel, this->sizeFill);
    fl->addRow(colourLabel, this->colourFill);
    fl->addRow(priceLabel, this->priceFill);
    fl->addRow(quantityLabel, this->quantityFill);
    fl->addRow(photographLabel, this->photographFill);

    tableAndFormLayout->addLayout(fl);

    layout->addLayout(tableAndFormLayout);

    this->setLayout(layout);
    this->show();
}

void AdminGUI::connectSignalsAndSlots()
{
    QObject::connect(this->coatsTable, &QTableWidget::itemSelectionChanged, this, &AdminGUI::tableSelectionChanged);
    QObject::connect(this->addButton, &QPushButton::clicked, this, &AdminGUI::addCoat);
    QObject::connect(this->removeButton, &QPushButton::clicked, this, &AdminGUI::removeCoat);
    QObject::connect(this->updateButton, &QPushButton::clicked, this, &AdminGUI::updateCoat);   
}

