#ifndef ICP_CONNECTION_GRAPHICS_OBJECT_H
#define ICP_CONNECTION_GRAPHICS_OBJECT_H

#include <QGraphicsLineItem>
#include <QGraphicsObject>
#include <QPainter>
#include <QPoint>

#include "block_graphics_object.h"
#include "connection.h"

class ConnectionGraphicsObject : public QGraphicsLineItem {
  public:
    ConnectionGraphicsObject(BlockGraphicsObject *s, BlockGraphicsObject *e, Connection *c);

    enum { Type = UserType + 21 };
    int type() const Q_DECL_OVERRIDE { return Type; }

    Connection *getConnection() { return this->_connection; };

    void updateConnectionPoints();

    QLineF getConnectionLine();

    friend std::ostream &operator<<(std::ostream &s, const ConnectionGraphicsObject &c);

  private:
    BlockGraphicsObject *start_block;
    BlockGraphicsObject *end_block;
    Connection *_connection;
};

#endif // ICP_CONNECTION_GRAPHICS_OBJECT_H
