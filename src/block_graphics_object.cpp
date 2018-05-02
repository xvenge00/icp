#include "block_graphics_object.h"
#include "debug.h"

BlockGraphicsObject::BlockGraphicsObject(Block *b, double pos_x, double pos_y,
                                         unsigned width, unsigned height) {
    this->positon = QPointF(pos_x, pos_y);
    this->_block = b;
    this->width = width;
    this->height = height;
}

void BlockGraphicsObject::paint(QPainter *painter,
                                const QStyleOptionGraphicsItem *option,
                                QWidget *widget) {
    painter->drawRect(this->pos().x(), this->pos().y(), this->width,
                      this->height);
    painter->drawText(this->pos().x(), this->pos().y(), this->width, this->height, Qt::AlignCenter, "+");

    paintConnectionPoints(painter, option, widget);

}

void BlockGraphicsObject::paintConnectionPoints(QPainter *painter,
                                const QStyleOptionGraphicsItem *option,
                                QWidget *widget) {
    // output connection points
    // painter->drawEllipse(this->pos().x() + this->width - CONNECTION_POINT_SIZE / 2, (this->pos().y() + this->height / 2) - CONNECTION_POINT_SIZE / 2, CONNECTION_POINT_SIZE, CONNECTION_POINT_SIZE);
    paintEllipseFromCenter(painter, this->pos().x() + this->width, this->pos().y() + this->height / 2, CONNECTION_POINT_SIZE);

    // input connection points
    unsigned connection_step = this->height / (this->_block->getInputSize() + 1);
    for(unsigned i = 1; i <= this->_block->getInputSize(); ++i) {
	paintEllipseFromCenter(painter, this->pos().x(), this->pos().y() + connection_step * i, CONNECTION_POINT_SIZE);
    }
}

void BlockGraphicsObject::paintEllipseFromCenter(QPainter * painter, qreal x, qreal y, unsigned edge) {
    unsigned half_edge = edge / 2;
    painter->drawEllipse(x - half_edge, y - half_edge, edge, edge);
}

QRectF BlockGraphicsObject::boundingRect() const {
    // LOGE("NOT IMPLEMENTED!");
    return {};
}

