#include "tooltip.h"
#include <QtGui/QPainter>
#include <QtGui/QFontMetrics>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QtGui/QMouseEvent>
#include <QtCharts/QChart>

Tooltip::Tooltip(QChart* parent):
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
    setPos(this->chart->mapToPosition(this->anchor) + QPoint(10, -50));
}

QRectF Tooltip::boundingRect() const {
    QPointF point = mapFromParent(this->chart->mapToPosition(this->anchor));
    QRectF boundingRect;
    boundingRect.setLeft(qMin(this->rect.left(), point.x()));
    boundingRect.setRight(qMax(this->rect.right(), point.x()));
    boundingRect.setTop(qMin(this->rect.top(), point.y()));
    boundingRect.setBottom(qMax(this->rect.bottom(), point.y()));
    return boundingRect;
}

void Tooltip::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {}

void Tooltip::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    event->setAccepted(true);
}

void Tooltip::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        setPos(mapToParent(event->pos() - event->buttonDownPos(Qt::LeftButton)));
        event->setAccepted(true);
    }
    else {
        event->setAccepted(false);
    }
}
