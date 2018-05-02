#include <QApplication>
#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>

#include "mainwindow.h"
#include "block.h"

MainWindow::MainWindow() {

    this->schema_area = new SchemaArea();

    QHBoxLayout * layout = new QHBoxLayout();
    this->templates = new QFrame();
    QGridLayout * template_layout = new QGridLayout();
    template_layout->addWidget(new QPushButton("My button"), 0, 0);
    template_layout->addWidget(new QPushButton("Suck my dick"), 1, 0);
    template_layout->addWidget(new QPushButton("Suck my dick2"), 0, 1);
    this->templates->setLayout(template_layout);
    

    this->view = new QGraphicsView(schema_area);
    layout->addWidget(this->templates);
    layout->addWidget(this->view);

    QWidget *w = new QWidget();
    w->setLayout(layout);

    setCentralWidget(w);
    setWindowTitle(tr("BlockEditor"));
    setUnifiedTitleAndToolBarOnMac(true);
}
