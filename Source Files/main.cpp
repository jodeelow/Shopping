#include "coatsgui.h"
#include "AdminGUI.h"
#include <QtWidgets/QApplication>
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

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Controller controller{};
    coatsgui mainGUI{ controller };
    mainGUI.show();
    return a.exec();
}
