#include <QApplication>
#include <QHBoxLayout>
#include <QWidget>

#include "mainwindow.h"

MainWindow::MainWindow() {

    this->schema_area = new SchemaArea();

    QHBoxLayout *layout = new QHBoxLayout();
    this->view = new QGraphicsView(schema_area);

    layout->addWidget(view);

    QWidget *w = new QWidget();
    w->setLayout(layout);

    setCentralWidget(w);
    setWindowTitle(tr("BlockEditor"));
    setUnifiedTitleAndToolBarOnMac(true);
}
