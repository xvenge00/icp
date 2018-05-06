/**
 * @file connection_graphics_item.h
 * @author Matej Kastak <xkasta02>
 * @author Adam  Venger <xvenge00>
 *
 * File containing internal connection graphics representations.
 */

#ifndef ICP_CONNECTION_GRAPHICS_OBJECT_H
#define ICP_CONNECTION_GRAPHICS_OBJECT_H

#include <QGraphicsLineItem>
#include <QGraphicsObject>
#include <QPainter>
#include <QPoint>

#include "block_graphics_object.h"
#include "connection.h"

/**
 * Internal graphical representation of connection between blocks
 */
class ConnectionGraphicsObject : public QGraphicsLineItem {
  public:
    /**
     * @param s starting graphics block
     * @param e ending graphics block
     * @param c data connection representation
     */
    ConnectionGraphicsObject(BlockGraphicsObject *s, BlockGraphicsObject *e, Connection *c);

    enum { Type = UserType + 21 };
    int type() const Q_DECL_OVERRIDE { return Type; }

    Connection *getConnection() { return this->_connection; };

    /**
     * Update the line connection is represented by.
     * This method is used when connection points move.
     */
    void updateConnectionPoints();

    /**
     * Function used to get the updated line of connection.
     * @return Line with properly set starting and ending points.
     */
    QLineF getConnectionLine();

    friend std::ostream &operator<<(std::ostream &s, const ConnectionGraphicsObject &c);

  private:
    /**
     * Starting block of connection
     * Line is connected to output of this block
     */
    BlockGraphicsObject *start_block;
    /**
     * Ending block of connection
     * Line is connected to input of this block
     */
    BlockGraphicsObject *end_block;
    Connection *_connection;
};

#endif // ICP_CONNECTION_GRAPHICS_OBJECT_H
