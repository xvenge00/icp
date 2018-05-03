#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QComboBox>
#include <QGraphicsView>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QToolBox>
#include <QToolButton>

#include "schema_area.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow();
    void addNewBlock(Block &b);

  private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();
    void quit();
    void add();
    void deleteSelection();
    void connectBlocks();
    void rerender();
    void authors();
    void license();
    void about();

    void toFront();
    void toBack();
    void calculate();
    void calculateStep();

    void lineButtonTriggered();
    void itemColorChanged();
    void fillButtonTriggered();
    void lineColorChanged();
    void sceneScaleChanged(QString);
    void pointerGroupClicked(int id);

  private:
    SchemaArea *schema_area;
    QGraphicsView *view;
    QFrame *templates;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;

    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *quitAction;
    QAction *addAction;
    QAction *deleteAction;
    QAction *connectAction;
    QAction *rerenderAction;
    QAction *authorsAction;
    QAction *licenseAction;
    QAction *aboutAction;

    QAction *toFrontAction;
    QAction *toBackAction;
    QAction *calculateAction;
    QAction *calculateStepAction;

    QToolBar *editToolbar;
    QToolBar *colorToolbar;
    QToolBar *pointerToolbar;
    QToolBar *calculationToolbar;

    QComboBox *sceneScaleCombo;
    QComboBox *itemColorCombo;

    QToolBox *toolBox;
    QButtonGroup *buttonGroup;
    QButtonGroup *pointerTypeGroup;
    QButtonGroup *backgroundButtonGroup;
    QToolButton *fillColorToolButton;
    QToolButton *lineColorToolButton;
    QAction *textAction;
    QAction *fillAction;
    QAction *lineAction;

    void createActions();
    void createMenus();
    void createTemplates();
    QMenu *createColorMenu(const char *slot, QColor defaultColor);
    QIcon createColorIcon(QColor color);
    QIcon createColorToolButtonIcon(const QString &imageFile, QColor color);
};

#endif // MAINWINDOW_H
