#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>

#include "block.h"
#include "debug.h"
#include "mainwindow.h"

MainWindow::MainWindow() {

    createActions();
    createMenus();
    createTemplates();

    this->schema_area = new SchemaArea();

    QHBoxLayout *layout = new QHBoxLayout();
    this->templates = new QFrame();
    QGridLayout *template_layout = new QGridLayout();
    template_layout->addWidget(new QPushButton("Addition"), 0, 0);
    template_layout->addWidget(new QPushButton("Subtraction"), 0, 1);
    template_layout->addWidget(new QPushButton("Multiplication"), 1, 0);
    template_layout->addWidget(new QPushButton("Division"), 1, 1);
    template_layout->addWidget(new QPushButton("Power"), 2, 0);
    template_layout->addWidget(new QPushButton("Negation"), 2, 1);
    template_layout->addWidget(new QPushButton("Constant"), 3, 0);
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

void MainWindow::createActions() {
    newAction = new QAction(tr("New..."), this);
    openAction = new QAction(tr("Open..."), this);
    saveAction = new QAction(tr("Save..."), this);
    quitAction = new QAction(tr("Quit"), this);
    addAction = new QAction(tr("Add Block"), this);
    deleteAction = new QAction(tr("Delete Block"), this);
    connectAction = new QAction(tr("Connect Blocks"), this);
    rerenderAction = new QAction(tr("Rerender"), this);
    authorsAction = new QAction(tr("Authors"), this);
    licenseAction = new QAction(tr("License"), this);
    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("Ctrl+B"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    toFrontAction = new QAction(tr("Move object to front"), this);
    toBackAction = new QAction(tr("Move object to back"), this);
}

void MainWindow::createMenus() {
    // fileMenu = menuBar()->addMenu(tr("&File"));

    // editMenu = menuBar()->addMenu(tr("&Edit"));

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
}

void MainWindow::createTemplates() {
    editToolbar = addToolBar(tr("Edit"));
    editToolbar->addAction(deleteAction);
    editToolbar->addAction(toFrontAction);
    editToolbar->addAction(toBackAction);
}

void MainWindow::about() { LOGE("NOT IMPLEMENTED!"); }
