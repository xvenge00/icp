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

    /**
     * Prepare the calculation
     */
    void beforeStep();

    /**
     * Function to handle scale changes. It scales the scene
     * acording to what was selected by the user.
     */
    void sceneScaleChanged(const QString &scale);
    /**
     * Function to deselect other block type from the pointer group, when the new block type is selected.
     */
    void pointerGroupClicked(int id);
    /**
     * Function to deselect tool type from the tool group, when the new tool is selected.
     */
    void toolGroupClicked(int id);

  private:
    /**
     * Pointer to painting area of the main program.
     *
     * This area also contains all graphics objects for painting.
     */
    SchemaArea *schema_area;

    /**
     * View handling the schema area.
     */
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
    QAction *beforeStepAction;

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
    /**
     * Function to inflate the menus.
     */
    void createMenus();
    /**
     * Function to inflate the templates.
     */
    void createTemplates();
};

#endif // MAINWINDOW_H
