#include "connection_graphics_object.h"
#include "debug.h"

ConnectionGraphicsObject::ConnectionGraphicsObject(Connection *c) { this->_connection = c; }

void ConnectionGraphicsObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawText(100, 100, 100, 100, Qt::AlignCenter, "This is connection test");
}

QRectF ConnectionGraphicsObject::boundingRect() const {
    // LOGE("NOT IMPLEMENTED!");
    return {};
}
