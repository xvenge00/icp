#include <QApplication>
#include "mainwindow.h"
#include "schema.h"
#include "debug.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    LOGE("First error");
    LOGI("First info");
    LOGD("First debug");

    Schema schema{};
    //priklad pouzitia
    auto blk1 = schema.newMulBlock();
    auto blk2 = schema.newSubBlock();
    auto blk3 = schema.newOutBlock(2);
    auto blk4 = schema.newOutBlock(10);
    schema.newConnection(schema.getBlckByID(blk3),
                         schema.getBlckByID(blk1), 0);
    schema.newConnection(schema.getBlckByID(blk4),
                         schema.getBlckByID(blk1), 1);

    schema.newConnection(schema.getBlckByID(blk1),
                         schema.getBlckByID(blk2), 1);
    schema.newConnection(schema.getBlckByID(blk1),
                          schema.getBlckByID(blk2),0);

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

    return a.exec();
}
