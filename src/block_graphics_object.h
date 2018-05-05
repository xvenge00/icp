#ifndef ICP_BLOCK_GRAPHICS_OBJECT_H
#define ICP_BLOCK_GRAPHICS_OBJECT_H

#include <QGraphicsObject>
#include <QPainter>
#include <QPoint>
#include <string>

#include "block.h"

const unsigned WIDTH = 60;
const unsigned HEIGHT = 80;
const unsigned CONNECTION_POINT_SIZE = 10;

const std::string blck_type_strings[] = {"+", "-", "*", "/", "^", "!", "CONST"};

class BlockGraphicsObject : public QGraphicsObject {
  public:
    BlockGraphicsObject(Block *b, unsigned width = WIDTH, unsigned height = HEIGHT);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    QPointF getInputPoint(unsigned index);
    QPointF getOutputPoint();

    Block *getBlock() { return this->_block; };

    friend std::ostream &operator<<(std::ostream &s, const BlockGraphicsObject &b);

  private:
    unsigned width;
    unsigned height;
    Block *_block;

    void paintBlockName(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void paintBlockValue(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void paintConnectionPoints(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void paintEllipseFromCenter(QPainter *painter, qreal x, qreal y, unsigned edge);
};

#endif // ICP_BLOCK_GRAPHICS_OBJECT_H
