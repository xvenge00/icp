/**
 * @file mainwindow.h
 * @author Matej Kastak <xkasta02>
 * @author Adam  Venger <xvenge00>
 *
 * File containing main window definitions, layouts, actions...
 */

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

  private slots:
    /**
     * Reset the scene and create new file to work on
     */
    void newFile();
    /**
     * Open saved scheme file
     */
    void openFile();
    /**
     * If schema is edited, save the file.
     */
    void saveFile();
    /**
     * Promt user for new schema name and save it
     */
    void saveAsFile();
    /**
     * Quit the program
     */
    void quit();
    /**
     * Delete selected blocks
     */
    void deleteSelection();

    void rerender();
    /**
     * Display the author of program
     */
    void authors();
    /**
     * Display the license of program
     */
    void license();
    /**
     * Display info about the program
     */
    void about();
    /**
     * Display the info about Qt used
     */
    void QtInfo();

    /**
     * Bring selected block to front
     */
    void toFront();
    /**
     * Send selected block to back
     */
    void toBack();
    /**
     * Calculate the schema
     */
    void calculate();
    /**
     * Step the calculation
     */
    void calculateStep();

    void sceneScaleChanged(const QString &scale);
    void pointerGroupClicked(int id);
    void toolGroupClicked(int id);

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
    QAction *QtInfoAction;

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
    QButtonGroup *blockTypeGroup;
    QButtonGroup *pointerTypeGroup;
    QButtonGroup *backgroundButtonGroup;
    QToolButton *fillColorToolButton;
    QToolButton *lineColorToolButton;
    QAction *textAction;
    QAction *fillAction;
    QAction *lineAction;

    /**
     * Link and create corespoding actions used in window
     */
    void createActions();
    void createMenus();
    void createTemplates();
    QMenu *createColorMenu(const char *slot, QColor defaultColor);
    QIcon createColorIcon(QColor color);
    QIcon createColorToolButtonIcon(const QString &imageFile, QColor color);
};

#endif // MAINWINDOW_H
