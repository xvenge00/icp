#include <QApplication>
#include <QGraphicsView>

#include "debug.h"
#include "mainwindow.h"
#include "schema.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.setGeometry(100, 100, 900, 600);
    w.show();

    /*
    Schema schema{};
    // priklad pouzitia
    auto blk1 = schema.newMulBlock();
    auto blk2 = schema.newSubBlock();
    auto blk3 = schema.newOutBlock(2);
    auto blk4 = schema.newOutBlock(10);
    schema.newConnection(blk3, blk1, 0);
    schema.newConnection(blk4, blk1, 1);

    schema.newConnection(blk1, blk2, 1);
    schema.newConnection(blk1, blk2, 0);
    schema.compute();
    cout << blk1->getValue();
    cout << blk2->getValue();

    //    schema.deleteConnection(1);
    schema.deleteBlock(blk1);
    cout << schema;

    //    bool succ=schema.compute();
    //    cout << "Podarilo sa? " << succ << "\n";
    //    cout << schema.getBlckByID(blk1)->getValue()<<"\n";
    //    cout << schema.getBlckByID(blk2)->getValue()<<"\n";

    //    Schema schema2{};
    //    schema2.load("tmp");
    //
    //    schema2.compute();
    //    cout << schema2.getBlckByID(blk1)->getValue()<<"\n";
    //    cout << schema2.getBlckByID(blk2)->getValue()<<"\n";

    //    std::cout << schema;
    //    schema.save("tmp");
    //
    //    Schema s2{};
    //    s2.load("tmp");
    //    std::cout << s2;

    */

    return a.exec();
}
