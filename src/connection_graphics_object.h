#ifndef ICP_CONNECTION_GRAPHICS_OBJECT_H
#define ICP_CONNECTION_GRAPHICS_OBJECT_H

#include <QGraphicsObject>
#include <QPainter>
#include <QPoint>

#include "connection.h"

class ConnectionGraphicsObject : public QGraphicsLineItem {
  public:
    ConnectionGraphicsObject(Connection *c);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRectF boundingRect() const Q_DECL_OVERRIDE;

    Connection *getConnection() { return this->_connection; };

    // friend std::ostream &operator<<(std::ostream &s, const
    // BlockGraphicsObject &b);

  private:
    Connection *_connection;
};

#endif // ICP_CONNECTION_GRAPHICS_OBJECT_H
