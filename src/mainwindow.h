#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QMainWindow>

#include "schema_area.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow();
    void addNewBlock(Block & b);

  private:
    SchemaArea *schema_area;
    QGraphicsView *view;
    QFrame * templates;
};

#endif // MAINWINDOW_H
