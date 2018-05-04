#include <QGraphicsSceneMouseEvent>

#include "block_graphics_object.h"
#include "connection_graphics_object.h"
#include "debug.h"
#include "schema_area.h"

SchemaArea::SchemaArea() {
    this->operationMode = InsertBlock;
    this->schema_edited = false;
    this->selectedBlockType = OUT;
}

SchemaArea::SchemaArea(const Schema &s) {}

void SchemaArea::propagate_data(const Schema &s) {}

void SchemaArea::addBlock() {}

void SchemaArea::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {

    if (mouseEvent->button() != Qt::LeftButton) {
        return;
    }

    Block *new_block;
    BlockGraphicsObject *block_graphics;
    switch (this->operationMode) {
    case InsertBlock:
        LOGD("Adding new block");

        new_block = getNewBlock();
        block_graphics = new BlockGraphicsObject(new_block);
        addItem(block_graphics);
        block_graphics->setPos(mouseEvent->scenePos());
        LOGD("Moving to: " << mouseEvent->scenePos().x());
        LOGD("Moving to: " << mouseEvent->scenePos().y());
        // emit itemInserted(block_graphics); ?
        break;

    case InsertConnection:
        LOGD("Adding new connection");

        line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(), mouseEvent->scenePos()));
        line->setPen(QPen(Qt::blue, 2));
        addItem(line);
        break;
    }
    // update(QRectF(0, 0, 5000, 5000));
    update();
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void SchemaArea::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if (this->operationMode == InsertConnection && line != 0) {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    } else if (this->operationMode == MoveBlock) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void SchemaArea::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if (line != 0 && this->operationMode == InsertConnection) {
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();

        removeItem(line);
        delete line;

        if (startItems.count() > 0 && endItems.count() > 0 && startItems.first() != endItems.first()) {
            BlockGraphicsObject *startItem = qgraphicsitem_cast<BlockGraphicsObject *>(startItems.first());
            BlockGraphicsObject *endItem = qgraphicsitem_cast<BlockGraphicsObject *>(endItems.first());
            Connection *con = new Connection(0, startItem->getBlock(), endItem->getBlock(), 0);
            ConnectionGraphicsObject *con_graphics = new ConnectionGraphicsObject(con);
            // con_graphics->setColor(myLineColor);
            // startItem->addArrow(arrow);
            // endItem->addArrow(arrow);
            con_graphics->setZValue(-1000.0);
            addItem(con_graphics);
            // con_graphics->updatePosition();
        }
    }
    line = 0;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

Block *SchemaArea::getNewBlock() {
    LOGD("Creating new block... type: " << static_cast<int>(this->selectedBlockType));
    switch (this->selectedBlockType) {
    case ADD:
        return this->schema.newAddBlock(2);
    case SUB:
        return this->schema.newSubBlock();
    case MUL:
        return this->schema.newMulBlock(2);
    case DIV:
        // return this->schema.newDivBlock();
        LOGE("NOT YET IMPLEMENTED!");
        break;
    case POW:
        // return this->schema.newAddBlock(2);
        LOGE("NOT YET IMPLEMENTED!");
        break;
    case NEG:
        // return this->schema.newAddBlock(2);
        LOGE("NOT YET IMPLEMENTED!");
        break;
    case OUT:
        return this->schema.newOutBlock(42);
        // TODO(mato): volba hodnoty
        break;
    default:
        LOGE("Unsuported block type!");
    }
}

void SchemaArea::setMode(Operation o) {
    // LOGD("Operation ID " << static_cast<int>(o));
    this->operationMode = o;
}

void SchemaArea::setBlockType(blck_type t) {
    // LOGD("Operation ID " << static_cast<int>(o));
    this->selectedBlockType = t;
}
