#include <QGraphicsSceneMouseEvent>

#include "block_graphics_object.h"
#include "debug.h"
#include "schema_area.h"

SchemaArea::SchemaArea() {}

SchemaArea::SchemaArea(const Schema &s) {}

void SchemaArea::propagate_data(const Schema &s) {}

void SchemaArea::addBlock() {}

void SchemaArea::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {

    LOGD("Mouse press event in scene");

    if (mouseEvent->button() != Qt::LeftButton) {
        return;
    }

    //auto new_block = this->schema.newSubBlock();
    auto new_block = this->schema.newOutBlock(42);
    BlockGraphicsObject *block_graphics = new BlockGraphicsObject(new_block, 100, 100);
    addItem(block_graphics);
    block_graphics->setPos(mouseEvent->scenePos());

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void SchemaArea::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    LOGD("Mouse move event in scene");
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void SchemaArea::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    LOGD("Mouse released event in scene");
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
