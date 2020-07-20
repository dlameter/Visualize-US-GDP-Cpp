#include "tooltip.h"

Tooltip::Tooltip(QChart* parent) :
    QGraphicsItem(parent),
    chart(parent)
{
}

void Tooltip::setText(const QString& text) {
    this->text = text;
    QFontMetrics metrics(font);
    this->textRect = metrics.boundingRect(QRect(0, 0, 150, 150), Qt::AlignLeft, this->text);
    this->textRect.translate(5, 5);
    prepareGeometryChange();
    this->rect = this->textRect.adjusted(-5, -5, 5, 5);
}

void Tooltip::setAnchor(QPointF anchor) {
    this->anchor = anchor;
}

void Tooltip::updateGeometry() {
    prepareGeometryChange();
    setPos(this->chart->mapToPosition(this->anchor) + QPoint(10, -50);
}

QRectF boundingRect() const {}

void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {}

protected:

void mousePressEvent(QGraphicsSceneMouseEvent* event);

void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
