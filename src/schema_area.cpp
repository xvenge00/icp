#include <QGraphicsSceneMouseEvent>

#include "schema_area.h"
#include "debug.h"

SchemaArea::SchemaArea() {
}

SchemaArea::SchemaArea(const Schema &s) {
}

void SchemaArea::propagate_data(const Schema &s) {}

void SchemaArea::addBlock(BlockGraphicsObject * b) {
}

void SchemaArea::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {

    LOGD("Mouse pressed event in scene");

    if(mouseEvent->button() != Qt::LeftButton) {
	return;
    }

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void SchemaArea::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void SchemaArea::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {

}
