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
     * Valid operation mode for scema.
     */
    enum Operation { InsertBlock, InsertConnection, MoveBlock };

    /**
     * Set the operation mode.
     * @param o Opearation to be set.
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

    /**
     * Prepare schema for the calculation and reset block values.
     */
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
    void setEdited(bool e) { LOGD("Schema edited " << e); this->schema_edited = e; }

    /**
     * Wrapper function for the schema values to be reseted.
     */
    void unsetValues() {
	this->schema.unset();
    }

    /**
     * Return the file name of the current schema.
     *
     * If the file name was not selected, prompt the user to do it.
     */
    std::string getFilePath();

    /**
     * Prompt the user to set the file name of the current schema.
     */
    std::string setFilePath();

    /**
     * Wrapper for the schema delete block.
     */
    void removeBlock(Block *b);

    /**
     * Wrapper for the schema delete connection.
     */
    void removeConnection(Connection *c);

    friend BlockGraphicsObject *parseGraphicsBlock(std::ifstream &s, SchemaArea &area);
    friend std::ostream &operator<<(std::ostream &s, const SchemaArea &a);
    friend std::istream &operator>>(std::ifstream &s, SchemaArea &area);
    friend ConnectionGraphicsObject *parseGraphicsConn(std::ifstream &s, SchemaArea &area);

  private:
    /**
     * Schema data represenation.
     */
    Schema schema;

    /**
     * File name of the current schema file.
     */
    std::string file_path;

    /**
     * Currently selected operation.
     *
     * When the new event ocurs in the GUI, this variable indicates how to process it.
     */
    Operation operationMode;

    /**
     * Currently selected block type.
     *
     * When the new block is inserted, this type will be used as the type of the new block.
     */
    blck_type selectedBlockType;

    /**
     * Bool indicating whether the schema was edited or not.
     */
    bool schema_edited;

    /**
     * Helper variable used when new connection is being created by the user.
     */
    QGraphicsLineItem *line;

    /**
     * Generate the new block based on the current settings.
     */
    Block *getNewBlock();

    /**
     * Background image of the painting area.
     */
    QPixmap background_image;

  signals:
    void itemSelected(QGraphicsItem *item);

  protected:
    /**
     * MousePressedHandler
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;

    /**
     * Function for drawing the background using the background image.
     */
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
