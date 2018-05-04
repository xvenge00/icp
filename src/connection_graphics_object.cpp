#include "connection_graphics_object.h"
#include "debug.h"

ConnectionGraphicsObject::ConnectionGraphicsObject(BlockGraphicsObject *s, BlockGraphicsObject *e, Connection *c) {
    this->start_block = s;
    this->end_block = e;
    this->_connection = c;

    pen().setColor(Qt::black);
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void ConnectionGraphicsObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    LOGD("Drawing connection");
    setLine(getConnectionLine());
}

QLineF ConnectionGraphicsObject::getConnectionLine() {
    QPointF start_point = this->start_block->getOutputPoint();
    QPointF end_point = this->start_block->getInputPoint(this->_connection->getIdx());
    LOGD("Connection line [" << start_point.x() << "][" << start_point.y() << "] ---- [" << end_point.x() << "]["
                             << end_point.y() << "]");
    return QLineF(start_point, end_point);
}
