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
    newAction->setShortcut(tr("Ctrl+N"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

    openAction = new QAction(tr("Open..."), this);
    openAction->setShortcut(tr("Ctrl+O"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));

    saveAction = new QAction(tr("Save"), this);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveFile()));

    saveAsAction = new QAction(tr("Save As..."), this);
    saveAsAction->setShortcut(tr("Ctrl+S"));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAsFile()));

    quitAction = new QAction(tr("Quit"), this);
    saveAsAction->setShortcut(tr("Ctrl+Q"));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(quit()));

    addAction = new QAction(tr("Add Block"), this);
    addAction->setShortcut(tr("Ctrl+A"));
    connect(addAction, SIGNAL(triggered()), this, SLOT(add()));

    deleteAction = new QAction(tr("Delete Block"), this);
    deleteAction->setShortcut(tr("Ctrl+D"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteSelection()));

    connectAction = new QAction(tr("Connect Blocks"), this);
    connectAction->setShortcut(tr("Ctrl+C"));
    connect(connectAction, SIGNAL(triggered()), this, SLOT(connectBlocks()));

    rerenderAction = new QAction(tr("Rerender"), this);
    rerenderAction->setShortcut(tr("Ctrl+R"));
    connect(rerenderAction, SIGNAL(triggered()), this, SLOT(rerender()));

    authorsAction = new QAction(tr("Authors"), this);
    connect(authorsAction, SIGNAL(triggered()), this, SLOT(authors()));

    licenseAction = new QAction(tr("License"), this);
    connect(licenseAction, SIGNAL(triggered()), this, SLOT(license()));

    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("Ctrl+B"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    toFrontAction = new QAction(tr("Move object to front"), this);
    connect(toFrontAction, SIGNAL(triggered()), this, SLOT(toFront()));
    toBackAction = new QAction(tr("Move object to back"), this);
    connect(toBackAction, SIGNAL(triggered()), this, SLOT(toBack()));
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(quitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(addAction);
    editMenu->addAction(deleteAction);
    editMenu->addAction(connectAction);
    editMenu->addAction(rerenderAction);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(authorsAction);
    helpMenu->addAction(licenseAction);
    helpMenu->addAction(aboutAction);
}

void MainWindow::createTemplates() {
    editToolbar = addToolBar(tr("Edit"));
    editToolbar->addAction(deleteAction);
    editToolbar->addAction(toFrontAction);
    editToolbar->addAction(toBackAction);
}

void MainWindow::newFile() { LOGE("NOT YET IMPLEMENTED!"); }
void MainWindow::openFile() { LOGE("NOT YET IMPLEMENTED!"); }
void MainWindow::saveFile() { LOGE("NOT YET IMPLEMENTED!"); }
void MainWindow::saveAsFile() { LOGE("NOT YET IMPLEMENTED!"); }
void MainWindow::quit() { LOGE("NOT YET IMPLEMENTED!"); }
void MainWindow::add() { LOGE("NOT YET IMPLEMENTED!"); }
void MainWindow::deleteSelection() { LOGE("NOT YET IMPLEMENTED!"); }
void MainWindow::connectBlocks() { LOGE("NOT YET IMPLEMENTED!"); }
void MainWindow::rerender() { LOGE("NOT YET IMPLEMENTED!"); }
void MainWindow::authors() { LOGE("NOT YET IMPLEMENTED!"); }
void MainWindow::license() { LOGE("NOT YET IMPLEMENTED!"); }
void MainWindow::about() { LOGE("NOT YET IMPLEMENTED!"); }

void MainWindow::toFront() { LOGE("NOT YET IMPLEMENTED!"); }
void MainWindow::toBack() { LOGE("NOT YET IMPLEMENTED!"); }
