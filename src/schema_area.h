#ifndef ICP_SCHEMA_AREA_H
#define ICP_SCHEMA_AREA_H

#include <QGraphicsScene>

#include "block.h"
#include "block_graphics_object.h"
#include "schema.h"

class SchemaArea : public QGraphicsScene {
  public:
    SchemaArea();
    enum Operation { InsertBlock, InsertConnection, MoveBlock };
    void setMode(Operation o);
    void setBlockType(blck_type t);
    void loadSchema(QString path);
    bool save(string file_name);
    bool load(string file_name);
    bool getEdited() { return this->schema_edited; };

    void setEdited(bool e) { this->schema_edited = e; }

    friend std::ostream &operator<<(std::ostream &s, const SchemaArea &a);

  private:
    Schema schema;
    Operation operationMode;
    blck_type selectedBlockType;
    bool schema_edited;
    QGraphicsLineItem *line;
    Block *getNewBlock();

  signals:
    void itemInserted(BlockGraphicsObject *item);
    void itemSelected(QGraphicsItem *item);

  protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
};

#endif // ICP_SCHEMA_AREA_H
