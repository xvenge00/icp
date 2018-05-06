/**
 * @file main.cpp
 * @author Matej Kastak <xkasta02>
 * @author Adam  Venger <xvenge00>
 *
 * @mainpage Project ICP 2018
 * Blockeditor is program used for editing and calculating nodes.
 * @section Make
 * Make contains helper functions for packing, testing on merlin and such
 */

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

    return a.exec();
}
