#include <QApplication>

#include "computable.h"
#include "mainwindow.h"
#include "schema.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Schema schema{};
    auto blkID1 = schema.newBlock(ADD);
    auto blkID2 = schema.newBlock(SUB);
    auto blkID3 = schema.newBlock(ADD);
    schema.newConnection(schema.getBlckByID(blkID1), schema.getBlckByID(blkID2));
//    std::cout << schema;
    schema.save("tmp");

    Schema s2{};
    s2.load("tmp");
    std::cout << s2;

    return a.exec();
}
