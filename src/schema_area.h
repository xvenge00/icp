#ifndef ICP_SCHEMA_AREA_H
#define ICP_SCHEMA_AREA_H

#include <QGraphicsScene>

#include "block.h"
#include "block_graphics_object.h"
#include "schema.h"

class SchemaArea : public QGraphicsScene {
  public:
    SchemaArea();
    SchemaArea(const Schema &s);
    void propagate_data(const Schema &s);
    void addBlock();
    bool save(string file_name);
    bool load(string file_name);

    friend std::ostream &operator<<(std::ostream &s, const SchemaArea &a);

  private:
    Schema schema;

  signals:
    void itemInserted(BlockGraphicsObject *item);
    void itemSelected(QGraphicsItem *item);

  protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void
    mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
};

#endif // ICP_SCHEMA_AREA_H
