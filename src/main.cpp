#include <QApplication>

#include "mainwindow.h"
#include "computable.h"
#include "schema.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Schema schema{};
    schema.newBlock(ADD);
    schema.newBlock(SUB);
    schema.newConnection(schema.getBlckByID(0), schema.getBlckByID(1));
    cout << schema;
    cout << "Toto je test" << std::endl;
    schema.save("tmp");

    return a.exec();
}
