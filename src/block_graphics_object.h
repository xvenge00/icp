/**
 * @file block_graphics_object.h
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

/**
 * Default values for the width and height of the block. Although they can
 * be changed.
 */
const unsigned WIDTH = 110;
const unsigned HEIGHT = 120;

/**
 * Size of connection circle drawn on blocks.
 */
const unsigned CONNECTION_POINT_SIZE = 10;

/**
 * String representation of each block type. This constant array contains the
 * titles that will be displayed on the corresponding blocks.
 */
const std::string blck_type_strings[] = {"+", "-", "*", "÷", "^", "!", "CONST"};

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
     * In this function every connection leading to the block is updated, to a new position.
     */
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

    /**
     * Function that alows user to edit value of the constant block.
     */
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

    /**
     * Function to get input connection point for given index.
     * @param index index to calculate the point, starting from top
     * @return point of input connection
     */
    QPointF getInputPoint(unsigned index);

    /**
     * Function to get output connection point(coordinates).
     * Blocks can have only one output point
     * @return point of output connection
     */
    QPointF getOutputPoint();

    /**
     * @return Data representation of this block.
     */
    Block *getBlock() { return this->_block; };

    friend std::ostream &operator<<(std::ostream &s, const BlockGraphicsObject &b);

  private:
    /**
     * Width of the block.
     */

    unsigned width;
    /**
     * Height of the block.
     */

    unsigned height;

    /**
     * Pointer to data representation of the block.
     */
    Block *_block;

    /**
     * Function to paint block name(type).
     *
     * This function uses the names specified in the constant array of strings in this file.
     */
    void paintBlockName(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * Function to paint block value.
     *
     * Paint the block value in the center of current block.
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
