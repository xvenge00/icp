#ifndef ICP_CONNECTION_GRAPHICS_OBJECT_H
#define ICP_CONNECTION_GRAPHICS_OBJECT_H

#include <QGraphicsObject>
#include <QPainter>
#include <QPoint>

#include "block_graphics_object.h"
#include "connection.h"

class ConnectionGraphicsObject : public QGraphicsLineItem {
  public:
    ConnectionGraphicsObject(BlockGraphicsObject *s, BlockGraphicsObject *e, Connection *c);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    Connection *getConnection() { return this->_connection; };

    QLineF getConnectionLine();

    friend std::ostream &operator<<(std::ostream &s, const ConnectionGraphicsObject &c);

  private:
    BlockGraphicsObject *start_block;
    BlockGraphicsObject *end_block;
    Connection *_connection;
};

#endif // ICP_CONNECTION_GRAPHICS_OBJECT_H
