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
}

QRectF BlockGraphicsObject::boundingRect() const {
    // LOGE("NOT IMPLEMENTED!");
    return {};
}

