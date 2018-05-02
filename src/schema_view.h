#ifndef ICP_SCHEMA_VIEW_H
#define ICP_SCHEMA_VIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>

class SchemaView : public QGraphicsView {
  public:
    SchemaView(const Schema &s);
    ~SchemaView();
    void populate_scene();

  private:
    QGraphicsScene *scene;
}
#endif /* ICP_SCHEMA_VIEW_H */
