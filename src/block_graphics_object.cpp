#include "block_graphics_object.h"

BlockGraphicsObject::BlockGraphicsObject(Block *b, unsigned width,
                                         unsigned height) {
    this->_block = b;
    this->width = width;
    this->height = height;
}

BlockGraphicsObject::~BlockGraphicsObject() {}

void BlockGraphicsObject::paint(QPainter *painter,
                                const QStyleOptionGraphicsItem *option,
                                QWidget *widget) {
    painter->drawRoundedRect(-10, -10, 20, 20, 5, 5);
}
