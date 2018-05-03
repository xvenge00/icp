#include <QApplication>
#include <QButtonGroup>
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

    fillColorToolButton = new QToolButton;
    fillColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fillColorToolButton->setMenu(
        createColorMenu(SLOT(itemColorChanged()), Qt::white));
    fillAction = fillColorToolButton->menu()->defaultAction();
    fillColorToolButton->setIcon(
        createColorToolButtonIcon(":/images/floodfill.png", Qt::white));
    connect(fillColorToolButton, SIGNAL(clicked()), this,
            SLOT(fillButtonTriggered()));

    lineColorToolButton = new QToolButton;
    lineColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    lineColorToolButton->setMenu(
        createColorMenu(SLOT(lineColorChanged()), Qt::black));
    lineAction = lineColorToolButton->menu()->defaultAction();
    lineColorToolButton->setIcon(
        createColorToolButtonIcon(":/images/linecolor.png", Qt::black));
    connect(lineColorToolButton, SIGNAL(clicked()), this,
            SLOT(lineButtonTriggered()));

    colorToolbar = addToolBar(tr("Color"));
    colorToolbar->addWidget(fillColorToolButton);
    colorToolbar->addWidget(lineColorToolButton);

    this->view = new QGraphicsView(schema_area);
    layout->addWidget(this->templates);
    layout->addWidget(this->view);

    QToolButton *pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":/images/pointer.png"));
    QToolButton *linePointerButton = new QToolButton;
    linePointerButton->setCheckable(true);
    linePointerButton->setIcon(QIcon(":/images/linepointer.png"));

    pointerTypeGroup = new QButtonGroup(this);
    pointerTypeGroup->addButton(pointerButton, int(SchemaArea::MoveBlock));
    pointerTypeGroup->addButton(linePointerButton,
                                int(SchemaArea::InsertConnection));
    connect(pointerTypeGroup, SIGNAL(buttonClicked(int)), this,
            SLOT(pointerGroupClicked(int)));

    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, SIGNAL(currentIndexChanged(QString)), this,
            SLOT(sceneScaleChanged(QString)));

    pointerToolbar = addToolBar(tr("Pointer type"));
    pointerToolbar->addWidget(pointerButton);
    pointerToolbar->addWidget(linePointerButton);
    pointerToolbar->addWidget(sceneScaleCombo);

    calculationToolbar = addToolBar(tr("Calculations"));
    calculationToolbar->addAction(calculateAction);
    calculationToolbar->addAction(calculateStepAction);

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
    quitAction->setShortcut(tr("Ctrl+Q"));
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

    calculateAction = new QAction(tr("Calculate all blocks"), this);
    connect(calculateAction, SIGNAL(triggered()), this, SLOT(calculate()));

    calculateStepAction = new QAction(tr("Step calculation"), this);
    connect(calculateStepAction, SIGNAL(triggered()), this,
            SLOT(calculateStep()));
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

QMenu *MainWindow::createColorMenu(const char *slot, QColor defaultColor) {
    QList<QColor> colors;
    colors << Qt::black << Qt::white << Qt::red << Qt::blue << Qt::yellow;
    QStringList names;
    names << tr("black") << tr("white") << tr("red") << tr("blue")
          << tr("yellow");

    QMenu *colorMenu = new QMenu(this);
    for (int i = 0; i < colors.count(); ++i) {
        QAction *action = new QAction(names.at(i), this);
        action->setData(colors.at(i));
        action->setIcon(createColorIcon(colors.at(i)));
        connect(action, SIGNAL(triggered()), this, slot);
        colorMenu->addAction(action);
        if (colors.at(i) == defaultColor)
            colorMenu->setDefaultAction(action);
    }
    return colorMenu;
}

QIcon MainWindow::createColorToolButtonIcon(const QString &imageFile,
                                            QColor color) {
    QPixmap pixmap(50, 80);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPixmap image(imageFile);
    // Draw icon centred horizontally on button.
    QRect target(4, 0, 42, 43);
    QRect source(0, 0, 42, 43);
    painter.fillRect(QRect(0, 60, 50, 80), color);
    painter.drawPixmap(target, image, source);

    return QIcon(pixmap);
}

QIcon MainWindow::createColorIcon(QColor color) {
    QPixmap pixmap(20, 20);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, 20, 20), color);

    return QIcon(pixmap);
}

void MainWindow::itemColorChanged() { LOGE("NOT YET IMPLEMENTED"); }

void MainWindow::fillButtonTriggered() { LOGE("NOT YET IMPLEMENTED"); }

void MainWindow::lineColorChanged() { LOGE("NOT YET IMPLEMENTED"); }

void MainWindow::lineButtonTriggered() { LOGE("NOT YET IMPLEMENTED!"); }

void MainWindow::sceneScaleChanged(QString) { LOGE("NOT YET IMPLEMENTED!"); }

void MainWindow::pointerGroupClicked(int id) {
    LOGD("CheckedID: " << pointerTypeGroup->checkedId());
    schema_area->setMode(SchemaArea::Operation(pointerTypeGroup->checkedId()));
}

void MainWindow::newFile() { LOGE("NOT YET IMPLEMENTED!"); }
void MainWindow::openFile() { LOGE("NOT YET IMPLEMENTED!"); }
void MainWindow::saveFile() {
    if (schema_area->edited()) {
        LOGE("NOT YET IMPLEMENTED!");
    }
}
void MainWindow::saveAsFile() { LOGE("NOT YET IMPLEMENTED!"); }

void MainWindow::quit() {
    saveFile();
    this->close();
}

void MainWindow::add() { LOGE("NOT YET IMPLEMENTED!"); }
void MainWindow::deleteSelection() { LOGE("NOT YET IMPLEMENTED!"); }
void MainWindow::connectBlocks() { LOGE("NOT YET IMPLEMENTED!"); }
void MainWindow::rerender() { LOGE("NOT YET IMPLEMENTED!"); }
void MainWindow::authors() { LOGE("NOT YET IMPLEMENTED!"); }
void MainWindow::license() { LOGE("NOT YET IMPLEMENTED!"); }
void MainWindow::about() { LOGE("NOT YET IMPLEMENTED!"); }

void MainWindow::toFront() { LOGE("NOT YET IMPLEMENTED!"); }
void MainWindow::toBack() { LOGE("NOT YET IMPLEMENTED!"); }
void MainWindow::calculate() { LOGE("NOT YET IMPLEMENTED!"); }
void MainWindow::calculateStep() { LOGE("NOT YET IMPLEMENTED!"); }
