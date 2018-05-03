#include <QGraphicsSceneMouseEvent>

#include "block_graphics_object.h"
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
        break;

    case InsertConnection:
        LOGD("Adding new connection");
        new_block = this->schema.newAddBlock(2);
        block_graphics = new BlockGraphicsObject(new_block);
        addItem(block_graphics);
        block_graphics->setPos(mouseEvent->scenePos());
        break;
    default:
        LOGE("Wrong opeartion mode");
    }

    QGraphicsScene::mousePressEvent(mouseEvent);
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

void SchemaArea::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) { QGraphicsScene::mouseMoveEvent(mouseEvent); }

void SchemaArea::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void SchemaArea::setMode(Operation o) {
    // LOGD("Operation ID " << static_cast<int>(o));
    this->operationMode = o;
}

void SchemaArea::setBlockType(blck_type t) {
    // LOGD("Operation ID " << static_cast<int>(o));
    this->selectedBlockType = t;
}
