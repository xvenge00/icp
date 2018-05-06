/**
 * @file connection_graphics_object.cpp
 * @author Matej Kastak <xkasta02>
 * @author Adam  Venger <xvenge00>
 */

#include <QToolTip>
#include <iomanip>
#include <sstream>

#include "connection_graphics_object.h"
#include "debug.h"

ConnectionGraphicsObject::ConnectionGraphicsObject(BlockGraphicsObject *s, BlockGraphicsObject *e, Connection *c)
    : QGraphicsLineItem() {
    this->start_block = s;
    this->end_block = e;
    this->_connection = c;

    updateConnectionPoints();
    pen().setColor(Qt::black);
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void ConnectionGraphicsObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsLineItem::paint(painter, option, widget);
}

void ConnectionGraphicsObject::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    QToolTip::hideText();
    QGraphicsLineItem::hoverLeaveEvent(event);
}

void ConnectionGraphicsObject::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
    QToolTip::showText(event->screenPos(), this->getStringValue());
    QGraphicsLineItem::hoverMoveEvent(event);
}

void ConnectionGraphicsObject::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    LOGD("HOVER ENTER");
    QToolTip::showText(event->screenPos(), this->getStringValue());
    QGraphicsLineItem::hoverEnterEvent(event);
}

QString ConnectionGraphicsObject::getStringValue() {
    QString output = "?";
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << this->_connection->getValue();
    output = QString::fromUtf8(stream.str().c_str());
    LOGD("Output of the connection is: " << output.toStdString());
    return output;
}

void ConnectionGraphicsObject::updateConnectionPoints() { setLine(getConnectionLine()); }

QLineF ConnectionGraphicsObject::getConnectionLine() {
    QPointF start_point = this->start_block->getOutputPoint();
    QPointF end_point = this->end_block->getInputPoint(this->_connection->getIdx());
    LOGD("Connection line [" << start_point.x() << "][" << start_point.y() << "] ---- [" << end_point.x() << "]["
                             << end_point.y() << "]");
    return QLineF(start_point, end_point);
}
