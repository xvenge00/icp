/**
 * @file block_graphics_object.cpp
 * @author Matej Kastak <xkasta02>
 * @author Adam  Venger <xvenge00>
 */

#include <QGraphicsScene>
#include <QInputDialog>
#include <iomanip>
#include <sstream>

#include "block_graphics_object.h"
#include "connection_graphics_object.h"
#include "debug.h"
#include "schema_area.h"

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
    QPen p;
    QBrush b;
    QPainterPath path;
    path.addRoundedRect(0, 0, this->width, this->height, 10.0, 10.0);
    p.setColor(Qt::black);
    // b.setColor(QColor::fromRgb(82, 82, 82));
    // painter->fillPath(path, QColor::fromRgb(82, 82, 82));
    if (isSelected()) {
        // p.setColor(Qt::blue);
        // b.setColor(QColor::fromRgb(92, 116, 116));
        painter->fillPath(path, QColor::fromRgb(92, 116, 116));
    }
    // painter->setPen(p);

    painter->fillPath(path, b);
    // painter->fillPath(path, QColor::fromRgb(90, 90, 90));
    painter->drawPath(path);

    painter->fillRect(0, 17, this->width, this->height - 30, QColor::fromRgb(95, 95, 95));
    painter->drawRect(0, 17, this->width, this->height - 30);

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
    painter->setBrush(Qt::yellow);
    paintEllipseFromCenter(painter, 0 + this->width, 0 + this->height / 2, CONNECTION_POINT_SIZE);

    // input connection points
    painter->setBrush(QColor::fromRgb(70, 200, 40));
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
        for (auto item : scene()->items()) {
            ConnectionGraphicsObject *casted_item = qgraphicsitem_cast<ConnectionGraphicsObject *>(item);
            if (casted_item) {
                casted_item->updateConnectionPoints();
            }
        }
    }
    SchemaArea *parent = dynamic_cast<SchemaArea *>(scene());
    if (parent) {
        parent->setEdited(true);
    }

    return value;
}

void BlockGraphicsObject::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    if (this->_block->getType() == OUT) {
        double block_output = QInputDialog::getDouble(dynamic_cast<QWidget *>(this),
                                                      tr("Input the constant block value"), tr("Output: "));
        this->_block->setValue(block_output);
    }
    this->scene()->update();
}

QRectF BlockGraphicsObject::boundingRect() const { return QRectF(0, 0, this->width, this->height); }
