/**
 * @file mainwindow.cpp
 * @author Matej Kastak <xkasta02>
 * @author Adam  Venger <xvenge00>
 */

#include <QApplication>
#include <QButtonGroup>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QMessageBox>
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
    schema_area->setSceneRect(QRectF(0, 0, 5000, 5000));

    QHBoxLayout *layout = new QHBoxLayout();
    this->templates = new QFrame();
    QGridLayout *template_layout = new QGridLayout();

    blockTypeGroup = new QButtonGroup(this);
    QPushButton *button_addition = new QPushButton("Addition");
    QPushButton *button_subtraction = new QPushButton("Subtraction");
    QPushButton *button_multiplication = new QPushButton("Multiplication");
    QPushButton *button_division = new QPushButton("Division");
    QPushButton *button_power = new QPushButton("Power");
    QPushButton *button_negation = new QPushButton("Negation");
    QPushButton *button_constant = new QPushButton("Constant");

    button_addition->setChecked(true);
    button_addition->setCheckable(true);
    button_subtraction->setCheckable(true);
    button_multiplication->setCheckable(true);
    button_division->setCheckable(true);
    button_power->setCheckable(true);
    button_negation->setCheckable(true);
    button_constant->setCheckable(true);

    button_addition->setMinimumHeight(100);
    button_subtraction->setMinimumHeight(100);
    button_multiplication->setMinimumHeight(100);
    button_division->setMinimumHeight(100);
    button_power->setMinimumHeight(100);
    button_negation->setMinimumHeight(100);
    button_constant->setMinimumHeight(100);

    blockTypeGroup->addButton(button_addition, int(ADD));
    blockTypeGroup->addButton(button_subtraction, int(SUB));
    blockTypeGroup->addButton(button_multiplication, int(MUL));
    blockTypeGroup->addButton(button_division, int(DIV));
    blockTypeGroup->addButton(button_power, int(POW));
    blockTypeGroup->addButton(button_negation, int(NEG));
    blockTypeGroup->addButton(button_constant, int(OUT));

    connect(blockTypeGroup, SIGNAL(buttonClicked(int)), this, SLOT(toolGroupClicked(int)));

    template_layout->addWidget(button_addition, 0, 0);
    template_layout->addWidget(button_subtraction, 0, 1);
    template_layout->addWidget(button_multiplication, 1, 0);
    template_layout->addWidget(button_division, 1, 1);
    template_layout->addWidget(button_power, 2, 0);
    template_layout->addWidget(button_negation, 2, 1);
    template_layout->addWidget(button_constant, 3, 0);

    this->templates->setLayout(template_layout);

    this->view = new QGraphicsView(schema_area);
    this->view->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    layout->addWidget(this->templates);
    layout->addWidget(this->view);

    QToolButton *pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":/images/cursor.png"));
    QToolButton *linePointerButton = new QToolButton;
    linePointerButton->setCheckable(true);
    linePointerButton->setIcon(QIcon(":/images/connection.png"));

    pointerTypeGroup = new QButtonGroup(this);
    pointerTypeGroup->addButton(pointerButton, int(SchemaArea::MoveBlock));
    pointerTypeGroup->addButton(linePointerButton, int(SchemaArea::InsertConnection));
    connect(pointerTypeGroup, SIGNAL(buttonClicked(int)), this, SLOT(pointerGroupClicked(int)));

    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, SIGNAL(currentIndexChanged(QString)), this, SLOT(sceneScaleChanged(QString)));

    pointerToolbar = addToolBar(tr("Pointer type"));
    pointerToolbar->addWidget(pointerButton);
    pointerToolbar->addWidget(linePointerButton);
    pointerToolbar->addWidget(sceneScaleCombo);

    calculationToolbar = addToolBar(tr("Calculations"));
    calculationToolbar->addAction(calculateAction);
    calculationToolbar->addAction(calculateStepAction);
    calculationToolbar->addAction(beforeStepAction);

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

    deleteAction = new QAction(QIcon(":/images/delete.png"), tr("Delete Block"), this);
    deleteAction->setShortcut(tr("Ctrl+D"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteSelection()));

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

    QtInfoAction = new QAction(tr("Qt Info"), this);
    connect(QtInfoAction, SIGNAL(triggered()), this, SLOT(QtInfo()));

    toFrontAction = new QAction(QIcon(":/images/bringtofront.png"), tr("Move object to front"), this);
    connect(toFrontAction, SIGNAL(triggered()), this, SLOT(toFront()));

    toBackAction = new QAction(QIcon(":/images/sendtoback.png"), tr("Move object to back"), this);
    connect(toBackAction, SIGNAL(triggered()), this, SLOT(toBack()));

    calculateAction = new QAction(QIcon(":/images/calculate.png"), tr("Calculate all blocks"), this);
    connect(calculateAction, SIGNAL(triggered()), this, SLOT(calculate()));

    calculateStepAction = new QAction(QIcon(":/images/step.png"), tr("Step calculation"), this);
    connect(calculateStepAction, SIGNAL(triggered()), this, SLOT(calculateStep()));

    beforeStepAction = new QAction(QIcon(":/images/reset.png"), tr("Prepare stepping calculation"), this);
    connect(beforeStepAction, SIGNAL(triggered()), this, SLOT(beforeStep()));
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(quitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    // editMenu->addAction(addAction);
    editMenu->addAction(deleteAction);
    // editMenu->addAction(connectAction);
    editMenu->addAction(rerenderAction);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(authorsAction);
    helpMenu->addAction(licenseAction);
    helpMenu->addAction(QtInfoAction);
    helpMenu->addAction(aboutAction);
}

void MainWindow::createTemplates() {
    editToolbar = addToolBar(tr("Edit"));
    editToolbar->addAction(toFrontAction);
    editToolbar->addAction(toBackAction);
    editToolbar->addAction(deleteAction);
}

void MainWindow::sceneScaleChanged(const QString &scale) {
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = view->matrix();
    view->resetMatrix();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}

void MainWindow::pointerGroupClicked(int id) {
    (void)id;
    LOGD("CheckedID: " << pointerTypeGroup->checkedId());
    schema_area->setMode(SchemaArea::Operation(pointerTypeGroup->checkedId()));
    blockTypeGroup->setExclusive(false);
    for (auto button : blockTypeGroup->buttons()) {
        button->setChecked(false);
    }
    blockTypeGroup->setExclusive(true);
}

void MainWindow::toolGroupClicked(int id) {
    pointerTypeGroup->setExclusive(false);
    // If button group is exclusive at least one button needs to checked
    // this is a workaround
    pointerTypeGroup->button(int(SchemaArea::MoveBlock))->setChecked(false);
    pointerTypeGroup->button(int(SchemaArea::InsertConnection))->setChecked(false);
    pointerTypeGroup->setExclusive(true);
    this->schema_area->setBlockType(blck_type(blockTypeGroup->checkedId()));
    this->schema_area->setMode(SchemaArea::InsertBlock);
}

void MainWindow::newFile() {
    if (schema_area->getEdited()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Are you sure?", "Schema was edited, do you want to save current schema?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            saveFile();
        }
    }
    schema_area->resetSchema();
    schema_area->setEdited(false);
}

void MainWindow::openFile() {
    if (schema_area->getEdited()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Are you sure?", "Schema was edited, do you want to save current schema?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            saveFile();
        }
    }
    schema_area->resetSchema();
    schema_area->loadSchema(QFileDialog::getOpenFileName(this, tr("Open file"), "~/").toStdString());
    schema_area->beforeCalc();
    schema_area->setEdited(false);
//    QMessageBox::warning(this, tr("Load file error"), tr("Currently not implemented"));
}

void MainWindow::saveFile() {
    if (schema_area->getEdited()) {
        schema_area->save(schema_area->getFilePath());
        schema_area->setEdited(false);
    }
}

void MainWindow::saveAsFile() { schema_area->save(schema_area->setFilePath()); }

void MainWindow::quit() {
    if (schema_area->getEdited()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Are you sure?",
                                      "Schema was edited, do you want to save schema before quitting the program?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            saveFile();
        }
    }
    this->close();
}

void MainWindow::deleteSelection() {
    for (QGraphicsItem *item : this->schema_area->selectedItems()) {
        BlockGraphicsObject *block = qgraphicsitem_cast<BlockGraphicsObject *>(item);
        if (block) {
            this->schema_area->removeBlock(block->getBlock());
            for (auto i : this->schema_area->items()) {
                ConnectionGraphicsObject *c = qgraphicsitem_cast<ConnectionGraphicsObject *>(i);
                if (c) {
                    if (c->getStartBlock() == block || c->getEndBlock() == block) {
                        this->schema_area->removeItem(i);
                        // Connection *remove_c = c->getConnection();
                        // this->schema_area->removeConnection(remove_c);
                    }
                }
            }
        }

        ConnectionGraphicsObject *conn = qgraphicsitem_cast<ConnectionGraphicsObject *>(item);
        if (conn) {
            this->schema_area->removeConnection(conn->getConnection());
        }

        this->schema_area->removeItem(item);
        delete item;
        // TODO: vymazanie objektu zo schemy ci uz je to connection alebo blok
    }
}
void MainWindow::rerender() { this->schema_area->update(); }
void MainWindow::authors() {
    // TODO: na macu my nevypisuje Title :/ overit
    QMessageBox::about(this, "BlockEditor Authors", "Matej Kastak xkasta02\nAdam Venger xvenge00\n");
}
void MainWindow::license() {
    QMessageBox licenseBox(this);
    licenseBox.setWindowTitle("License");
    licenseBox.setTextFormat(Qt::RichText);
    licenseBox.setText("<p align='center'>Copyright 2018 Matej Kastak <xkasta02><br/>"
                       "Copyright 2018 Adam  Venger <xvenge00><hr/>"
                       "Permission is hereby granted, free of charge, to any person obtaining a copy of this software "
                       "and associated documentation files (the \"Software\"), to deal in the Software without "
                       "restriction, including without limitation the rights to use, copy, modify, merge, publish, "
                       "distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the "
                       "Software is furnished to do so, subject to the following conditions:<br/>"
                       "The above copyright notice and this permission notice shall be included in all copies or "
                       "substantial portions of the Software.<br/><br/>"
                       "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, "
                       "INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR "
                       "PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR "
                       "ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, "
                       "ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE "
                       "SOFTWARE.<br/></p>");
    licenseBox.exec();
}

void MainWindow::about() {
    QMessageBox aboutBox(this);
    aboutBox.setWindowTitle("About");
    aboutBox.setTextFormat(Qt::RichText);
    aboutBox.setText(
        "This program was created as a project for ICP<br/>We are using <a href='https://icons8.com/'>Icons8</a>");
    aboutBox.exec();
}

void MainWindow::QtInfo() { QMessageBox::aboutQt(this, "BlockEditor QT"); }

void MainWindow::toFront() {
    if (this->schema_area->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = this->schema_area->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() >= zValue && item->type() == BlockGraphicsObject::Type)
            zValue = item->zValue() + 0.1;
    }
    selectedItem->setZValue(zValue);
}

void MainWindow::toBack() {
    if (this->schema_area->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = this->schema_area->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() <= zValue && item->type() == BlockGraphicsObject::Type)
            zValue = item->zValue() - 0.1;
    }
    selectedItem->setZValue(zValue);
}

void MainWindow::calculate() {
    if (this->schema_area->calculate()) {
        this->schema_area->update();
    } else {
        QMessageBox::warning(this, tr("Calculation error"), tr("Schema could not be calculated..."));
    }
}

/*
 * Needs to be called after this->schema_area->beforeCalc();
 */
void MainWindow::calculateStep() {
    if (this->schema_area->calculateStep()) {
        this->schema_area->update();
    } else {
        QMessageBox::warning(this, tr("Calculation error"), tr("Schema could not be calculated..."));
    }
}

void MainWindow::beforeStep() {
    this->schema_area->unsetValues();
    this->schema_area->beforeCalc();
    this->schema_area->update();
}
