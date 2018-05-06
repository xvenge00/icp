/**
 * @file block_graphics_item.h
 * @author Matej Kastak <xkasta02>
 * @author Adam  Venger <xvenge00>
 *
 * File containing internal block graphics representations.
 */

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

/**
 * Internal graphical representation of the block
 */
class BlockGraphicsObject : public QGraphicsObject {
  public:
    /**
     * @param b data representation of block
     * @param width witdth of rectangle
     * @param height height of rectangle
     */
    BlockGraphicsObject(Block *b, unsigned width = WIDTH, unsigned height = HEIGHT);

    enum { Type = UserType + 20 };
    int type() const Q_DECL_OVERRIDE { return Type; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    QRectF boundingRect() const Q_DECL_OVERRIDE;

    /**
     * Function that is called when any change is done to block.
     * In this function every connection leading to the block is updated, to new position.
     */
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

    /**
     * Function to get input connection point for given index
     * @param index index to calculate the point, starting from top
     * @return point of input connection
     */
    QPointF getInputPoint(unsigned index);
    /**
     * Function to get output connection point
     * Blocks can have only one output point
     * @return point of output connection
     */
    QPointF getOutputPoint();

    /**
     * @return Data representation of this block
     */
    Block *getBlock() { return this->_block; };

    friend std::ostream &operator<<(std::ostream &s, const BlockGraphicsObject &b);

  private:
    unsigned width;
    unsigned height;
    Block *_block;

    /**
     * Function to paint block name(type).
     */
    void paintBlockName(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    /**
     * Function to paint block value.
     */
    void paintBlockValue(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    /**
     * Function to paint block connection points.
     */
    void paintConnectionPoints(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    /**
     * Helper function to paint ellipse from center point.
     */
    void paintEllipseFromCenter(QPainter *painter, qreal x, qreal y, unsigned edge);
};

#endif // ICP_BLOCK_GRAPHICS_OBJECT_H
