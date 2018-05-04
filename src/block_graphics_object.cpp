#include <iomanip>
#include <sstream>

#include "block_graphics_object.h"
#include "debug.h"

BlockGraphicsObject::BlockGraphicsObject(Block *b, unsigned width, unsigned height) {
    this->_block = b;
    this->width = width;
    this->height = height;

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void BlockGraphicsObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // painter->drawRect(0, 0, this->width, this->height);
    painter->drawRect(0, 0, this->width, this->height);

    paintBlockName(painter, option, widget);
    paintConnectionPoints(painter, option, widget);
}

void BlockGraphicsObject::paintBlockName(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QString output = "?";
    if (this->_block->getType() == OUT) {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << this->_block->getValue();
        output = QString::fromUtf8(stream.str().c_str());
    } else {
        output = QString::fromUtf8(blck_type_strings[this->_block->getType()].c_str());
    }
    painter->drawText(0, 0, this->width, this->height, Qt::AlignCenter, output);
}

void BlockGraphicsObject::paintConnectionPoints(QPainter *painter, const QStyleOptionGraphicsItem *option,
                                                QWidget *widget) {
    // output connection points
    paintEllipseFromCenter(painter, 0 + this->width, 0 + this->height / 2, CONNECTION_POINT_SIZE);

    // input connection points
    unsigned connection_step = this->height / (this->_block->getInputSize() + 1);
    for (unsigned i = 1; i <= this->_block->getInputSize(); ++i) {
        paintEllipseFromCenter(painter, 0, 0 + connection_step * i, CONNECTION_POINT_SIZE);
    }
}

void BlockGraphicsObject::paintEllipseFromCenter(QPainter *painter, qreal x, qreal y, unsigned edge) {
    unsigned half_edge = edge / 2;
    painter->drawEllipse(x - half_edge, y - half_edge, edge, edge);
}

QRectF BlockGraphicsObject::boundingRect() const {
    return QRectF(0 - CONNECTION_POINT_SIZE / 2, 0, this->width + CONNECTION_POINT_SIZE, this->height);
    // return QRectF(this->pos().x() - CONNECTION_POINT_SIZE / 2, this->pos().y(), this->pos().x() + this->width +
    // CONNECTION_POINT_SIZE / 2, this->pos().y() + this->height);
}
