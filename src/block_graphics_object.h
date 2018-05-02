#ifndef ICP_BLOCK_GRAPHICS_OBJECT_H
#define ICP_BLOCK_GRAPHICS_OBJECT_H

#include <QGraphicsObject>
#include <QPainter>

#include "block.h"

const unsigned WIDTH = 50;
const unsigned HEIGHT = 50;

class BlockGraphicsObject : public QGraphicsObject {
  public:
    BlockGraphicsObject(Block *b, unsigned width = WIDTH,
                        unsigned height = HEIGHT);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    QRectF boundingRect() const Q_DECL_OVERRIDE;

    Block *getBlock() { return this->_block; };

  private:
    unsigned width;
    unsigned height;
    Block *_block;
};

#endif // ICP_BLOCK_GRAPHICS_OBJECT_H
