/**
 * @file connection_graphics_object.h
 * @author Matej Kastak <xkasta02>
 * @author Adam  Venger <xvenge00>
 *
 * File containing internal connection graphics representations.
 */

#ifndef ICP_CONNECTION_GRAPHICS_OBJECT_H
#define ICP_CONNECTION_GRAPHICS_OBJECT_H

#include <QGraphicsLineItem>
#include <QGraphicsObject>
#include <QGraphicsSceneHoverEvent>
#include <QPainter>
#include <QPoint>

#include "block_graphics_object.h"
#include "connection.h"

/**
 * Internal graphical representation of connection between blocks.
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
    BlockGraphicsObject *getStartBlock() { return this->start_block; };
    BlockGraphicsObject *getEndBlock() { return this->end_block; };

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

    /**
     * Function used for displaying tooltip when hovering with mouse on connection
     * objects.
     */
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;

    /**
     * Helper function to convert the double value from the data representation to
     * string representation.
     *
     * This function is used when displaying the tooltip on hover events.
     */
    QString getStringValue();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

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

    /**
     * Pointer to connection data representation.
     */
    Connection *_connection;
};

#endif // ICP_CONNECTION_GRAPHICS_OBJECT_H
