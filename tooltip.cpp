#include "tooltip.h"

public:

Tooltip::Tooltip(QChart* parent) :
    QGraphicsItem(parent),
    chart(parent)
{
}

void Tooltip::setText(const QString& text) {}

void Tooltip::setAnchor(QPointF anchor) {
    this->anchor = anchor;
}

void Tooltip::updateGeometry() {}

QRectF boundingRect() const {}

void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {}

protected:

void mousePressEvent(QGraphicsSceneMouseEvent* event);

void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
