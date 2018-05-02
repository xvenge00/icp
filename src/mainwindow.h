#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>

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

    QToolBar *editToolbar;
    QToolBar *colorToolbar;
    QToolBar *pointerToolbar;

    void createActions();
    void createMenus();
    void createTemplates();
};

#endif // MAINWINDOW_H
