#ifndef ICP_BLOCK_GRAPHICS_OBJECT_H
#define ICP_BLOCK_GRAPHICS_OBJECT_H

#include <QGraphicsObject>
#include <QPainter>

#include "block.h"

const unsigned WIDTH = 300;
const unsigned HEIGHT = 300;

class BlockGraphicsObject : public QGraphicsObject {
  public:
    BlockGraphicsObject(Block *b, unsigned width = WIDTH,
                        unsigned height = HEIGHT);
    ~BlockGraphicsObject();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    Block * getBlock() {
	return this->_block;
    };

  private:
    unsigned width;
    unsigned height;
    Block *_block;
};

#endif // ICP_BLOCK_GRAPHICS_OBJECT_H
