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
    connect(schema_area, SIGNAL(itemInserted(BlockGraphicsObject *)), this, SLOT(itemInserted(BlockGraphicsObject *)));

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

    deleteAction = new QAction(QIcon(":/images/delete.png"), tr("Delete Block"), this);
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
    helpMenu->addAction(QtInfoAction);
    helpMenu->addAction(aboutAction);
}

void MainWindow::createTemplates() {
    editToolbar = addToolBar(tr("Edit"));
    editToolbar->addAction(toFrontAction);
    editToolbar->addAction(toBackAction);
    editToolbar->addAction(deleteAction);
}

QMenu *MainWindow::createColorMenu(const char *slot, QColor defaultColor) {
    QList<QColor> colors;
    colors << Qt::black << Qt::white << Qt::red << Qt::blue << Qt::yellow;
    QStringList names;
    names << tr("black") << tr("white") << tr("red") << tr("blue") << tr("yellow");

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

QIcon MainWindow::createColorToolButtonIcon(const QString &imageFile, QColor color) {
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
    (void)id;
    LOGD("CheckedID: " << pointerTypeGroup->checkedId());
    schema_area->setMode(SchemaArea::Operation(pointerTypeGroup->checkedId()));
}

void MainWindow::itemInserted(BlockGraphicsObject *o) {
    pointerTypeGroup->button(int(SchemaArea::MoveBlock))->setChecked(true);
    this->schema_area->setMode(SchemaArea::Operation(pointerTypeGroup->checkedId()));
    // buttonGroup->button(int(o->diagramType()))->setChecked(false);
    // uncheck all button from left panel
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
    LOGE("PARTIALY IMPLEMENTED!");
    if (schema_area->getEdited()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Are you sure?", "Schema was edited, do you want to save current schema?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            saveFile();
        }
    }
    schema_area->resetSchema();
}
void MainWindow::openFile() {
    LOGE("PARTIALY IMPLEMENTED!");
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
}

void MainWindow::saveFile() {
    LOGE("PARTIALY IMPLEMENTED!");
    if (schema_area->getEdited()) { // TODO: correct edits handling
        schema_area->save(QFileDialog::getSaveFileName(this, tr("Save file"), "~/").toStdString());
        schema_area->setEdited(true);
    }
}

void MainWindow::saveAsFile() {
    schema_area->save(QFileDialog::getSaveFileName(this, tr("Save file"), "~/").toStdString());
}

void MainWindow::quit() {
    saveFile();
    this->close();
}

void MainWindow::add() { LOGE("NOT YET IMPLEMENTED!"); }

void MainWindow::deleteSelection() {
    for (QGraphicsItem *item : this->schema_area->selectedItems()) {
        this->schema_area->removeItem(item);
        delete item;
        // TODO: vymazanie objektu zo schemy ci uz je to connection alebo blok
    }
}
void MainWindow::connectBlocks() { LOGE("NOT YET IMPLEMENTED!"); }
void MainWindow::rerender() { LOGE("NOT YET IMPLEMENTED!"); }
void MainWindow::authors() {
    // TODO: na macu my nevypisuje Title :/ overit
    QMessageBox::about(this, "BlockEditor Authors", "Matej Kastak <xkasta02>\nAdam Venger <xvenge00>\n");
}
void MainWindow::license() { LOGE("NOT YET IMPLEMENTED!"); }

void MainWindow::about() {
    QMessageBox aboutBox(this);
    aboutBox.setWindowTitle("About");
    aboutBox.setTextFormat(Qt::RichText); // this is what makes the links clickable
    // aboutBox.setText("<a href='mailto:someone@somewhere.com?Subject=My%20Subject>Email me</a>");
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
    this->schema_area->calculate();
    this->schema_area->update();
}
void MainWindow::calculateStep() { LOGE("NOT YET IMPLEMENTED!"); }
