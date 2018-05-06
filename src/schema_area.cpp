#include <QGraphicsSceneMouseEvent>
#include <QInputDialog>
#include <fstream>

#include "block_graphics_object.h"
#include "connection_graphics_object.h"
#include "debug.h"
#include "schema_area.h"

SchemaArea::SchemaArea() {
    this->operationMode = InsertBlock;
    this->schema_edited = false;
    this->selectedBlockType = OUT;
}

void SchemaArea::loadSchema(std::string path) {
    // path.toStdString() vrati std::string utf8
    ifstream s;
    s.open(path); // TODO if fail

    s >> *this;

    s.close();

    LOGD("Trying to load schema from path = " << path);

}

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

        line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(), mouseEvent->scenePos()));
        line->setPen(QPen(Qt::blue, 2));
        addItem(line);
        break;
    default:
        LOGD("Other action [ID] = " << static_cast<int>(this->operationMode));
    }
    update();
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void SchemaArea::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if (this->operationMode == InsertConnection && line != 0) {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    } else if (this->operationMode == MoveBlock) {
        // LOGD("Moving the block");
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void SchemaArea::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if (line != 0 && this->operationMode == InsertConnection) {
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        LOGD("Getting items at [ " << line->line().p1().x() << "][" << line->line().p1().y() << "]");
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        LOGD("Getting items at [ " << line->line().p2().x() << "][" << line->line().p2().y() << "]");
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();

        removeItem(line);
        delete line;

        if (startItems.count() > 0 && endItems.count() > 0 && startItems.first() != endItems.first()) {
            LOGD("Adding new connection");
            BlockGraphicsObject *startItem = qgraphicsitem_cast<BlockGraphicsObject *>(startItems.first());
            BlockGraphicsObject *endItem = qgraphicsitem_cast<BlockGraphicsObject *>(endItems.first());
            Connection *con = this->schema.newConnection(startItem->getBlock(), endItem->getBlock());
            ConnectionGraphicsObject *con_graphics = new ConnectionGraphicsObject(startItem, endItem, con);
            con_graphics->setZValue(-1000.0);
            addItem(con_graphics);
        }
    }
    line = 0;
    update();
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

Block *SchemaArea::getNewBlock() {
    LOGD("Creating new block... type: " << static_cast<int>(this->selectedBlockType));
    double block_output = 0;
    switch (this->selectedBlockType) {
    case ADD:
        return this->schema.newAddBlock(2);
    case SUB:
        return this->schema.newSubBlock();
    case MUL:
        return this->schema.newMulBlock(2);
    case DIV:
        return this->schema.newDivBlock();
    case POW:
        return this->schema.newPowBlock();
    case NEG:
        // return this->schema.newAddBlock(2);
        LOGE("NOT YET IMPLEMENTED!");
        break;
    case OUT:
        block_output = QInputDialog::getDouble(dynamic_cast<QWidget *>(this), tr("Input the constant block value"),
                                               tr("Output: "));
        return this->schema.newOutBlock(block_output);
        break;
    default:
        LOGE("Unsuported block type!");
    }

    return nullptr;
}

void SchemaArea::setMode(Operation o) {
    // LOGD("Operation ID " << static_cast<int>(o));
    this->operationMode = o;
}

void SchemaArea::setBlockType(blck_type t) {
    // LOGD("Operation ID " << static_cast<int>(o));
    this->selectedBlockType = t;
}

bool SchemaArea::save(string file_name) {
    std::ofstream out_stream;
    out_stream.open(file_name);

    out_stream << *this;
    out_stream.close();

    return true; // TODO(adam): bool je pre error handling?
}

void SchemaArea::resetSchema() {
    LOGD("Reseting the schema");
    clear();
    update();
    // TODO(adam): vymazat obsah schemy, ulozeny by uz mal byt staci len clear vsetko
}

bool SchemaArea::calculate() { this->schema.compute(); }

bool SchemaArea::calculateStep() {}
