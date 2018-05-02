#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsView>
#include <QMainWindow>

#include "schema_area.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow();

  private:
    SchemaArea *schema_area;
    QGraphicsView *view;
};

#endif // MAINWINDOW_H
