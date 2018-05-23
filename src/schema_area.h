/**
 * @file schema_area.h
 * @author Matej Kastak <xkasta02>
 * @author Adam  Venger <xvenge00>
 *
 * File containing container(scene) for graphics objects.
 */

#ifndef ICP_SCHEMA_AREA_H
#define ICP_SCHEMA_AREA_H

#include <QGraphicsScene>

#include "block.h"
#include "block_graphics_object.h"
#include "connection_graphics_object.h"
#include "debug.h"
#include "schema.h"

/**
 * Container(scene) for graphics objects.
 * Handles drawing, removing, mouse events,...
 */
class SchemaArea : public QGraphicsScene {
  public:
    SchemaArea();
    /**
     * Valid operation mode for scena
     */
    enum Operation { InsertBlock, InsertConnection, MoveBlock };
    /**
     * Set the operation mode.
     * @param o Opearation to be used.
     */
    void setMode(Operation o);
    /**
     * Set the block type to be currently selected.
     * @param t Type to be selected.
     */
    void setBlockType(blck_type t);
    /**
     * Load the schema.
     * @param path File path be load schema from.
     */
    void loadSchema(std::string path);
    /**
     * Clear the display and reset the schema
     */
    void resetSchema();

    bool beforeCalc();
    /**
     * Start the schema calculation.
     * @return True on success, else false.
     */
    bool calculate();
    /**
     * Step the calculation.
     * @return True on success, else false.
     */
    bool calculateStep();
    /**
     * Save the schema.
     * @param path File to save schema into.
     * @return True on success, else false.
     */
    bool save(string file_name);
    /**
     * Load the schema.
     * @param path File path be load schema from.
     * @return True on success, else false.
     */
    bool load(string file_name);
    /**
     * Function to return if schema was edited.
     * @return True if schema was edited, else false
     */
    bool getEdited() { return this->schema_edited; };

    /**
     * Set the schema edited variable
     * @param e True if schema was edited, else false
     */
    void setEdited(bool e) {
    LOGD("Schema edited " << e); this->schema_edited = e; }

    void unsetValues() {
	this->schema.unset();
    }

    std::string getFilePath();
    std::string setFilePath();

    void removeBlock(Block *b);
    void removeConnection(Connection *c);

    friend BlockGraphicsObject *parseGraphicsBlock(std::ifstream &s, SchemaArea &area);
    friend std::ostream &operator<<(std::ostream &s, const SchemaArea &a);
    friend std::istream &operator>>(std::ifstream &s, SchemaArea &area);
    friend ConnectionGraphicsObject *parseGraphicsConn(std::ifstream &s, SchemaArea &area);

  private:
    Schema schema;
    std::string file_path;
    Operation operationMode;
    blck_type selectedBlockType;
    bool schema_edited;
    QGraphicsLineItem *line;
    Block *getNewBlock();
    QPixmap background_image;

  signals:
    void itemSelected(QGraphicsItem *item);

  protected:
    /**
     * MousePressedHandler
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;

    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;

    /**
     * MouseMoveHandler
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    /**
     * MouseReleaseHandler
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
};

#endif // ICP_SCHEMA_AREA_H
