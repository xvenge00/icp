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

QPointF BlockGraphicsObject::getInputPoint(unsigned index) {
    return QPointF(this->pos().x(), this->pos().y() + this->height / (this->_block->getInputSize() + 1) * (index + 1));
}

QPointF BlockGraphicsObject::getOutputPoint() {
    return QPointF(this->pos().x() + this->width, this->pos().y() + this->height / 2);
}

void BlockGraphicsObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->fillRect(0, 0, this->width, this->height, Qt::white);
    painter->drawRect(0, 0, this->width, this->height);

    // TODO(mato): zvazit parametre nasledujucich funkcii
    paintBlockName(painter, option, widget);
    paintBlockValue(painter, option, widget);
    paintConnectionPoints(painter, option, widget);
}

void BlockGraphicsObject::paintBlockName(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QString output = "?";
    output = QString::fromUtf8(blck_type_strings[this->_block->getType()].c_str());
    painter->drawText(0, 0, this->width, this->height, Qt::AlignTop | Qt::AlignHCenter, output);
}

void BlockGraphicsObject::paintBlockValue(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QString output = "?";
    if (this->_block->isSet()) {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << this->_block->getValue();
        output = QString::fromUtf8(stream.str().c_str());
    } else {
        output = "None";
        // TODO(mato): Co vypisat v pripade ze block nema hodnotu?
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

QVariant BlockGraphicsObject::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == QGraphicsItem::ItemPositionChange) {
        LOGE("NOT YET IMPLEMENTED;");
        // TODO: Tu treba zistit vsetky connection napojene na tento block a zavolat na nich updateConnectionpoints();
        // V najhorsom pripdate tu zavolajme updateConnectionPoints() na vsetky itemy ktore idu pretypovat na
        // ConnectionGraphicsItem
    }

    return value;
}

QRectF BlockGraphicsObject::boundingRect() const { return QRectF(0, 0, this->width, this->height); }
