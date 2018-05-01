//#include <QApplication>
//#include "mainwindow.h"
#include "schema.h"

int main(int argc, char *argv[]) {
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    Schema schema{};
    auto blk1 = schema.newMulBlock();
//    auto blk2 = schema.newSubBlock();
    auto blk3 = schema.newOutBlock(2);
    auto blk4 = schema.newOutBlock(10);
    schema.newConnection(schema.getBlckByID(blk3),
                         schema.getBlckByID(blk1), 0);
    schema.newConnection(schema.getBlckByID(blk4),
                         schema.getBlckByID(blk1), 1);
    //2*10
//    schema.newConnection(schema.getBlckByID(blk1),
//                         schema.getBlckByID(blk2), 1);

    schema.compute();
    cout << *schema.getBlckByID(blk1);
//    cout << schema.getBlckByID(blk1)->getValue()<<"\n";
//    cout << schema.getBlckByID(blk2)->getValue()<<"\n";

//    std::cout << schema;
//    schema.save("tmp");
//
//    Schema s2{};
//    s2.load("tmp");
//    std::cout << s2;

//    return a.exec();
}
