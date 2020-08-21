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

void Tooltip::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QPainterPath path;
    path.addRoundedRect(this->rect, 5, 5);

    QPointF point = mapFromParent(this->chart->mapToPosition(this->anchor));
    if (!this->rect.contains(point)) {
        modifyPathWithAnchorCorner(path, point);
    }
    
    painter->setBrush(QColor(255, 255, 255));
    painter->drawPath(path);
    painter->drawText(this->textRect, this->text);
}

void Tooltip::modifyPathWithAnchorCorner(QPainterPath& path, const QPointF& point) {
    QPointF point1 = firstPointOnPerimeter(point);
    QPointF point2 = secondPointOnPerimeter(point);

    path.moveTo(point1);
    path.lineTo(point);
    path.lineTo(point2);
    path = path.simplified();
}

QPointF Tooltip::firstPointOnPerimeter(const QPointF& point) {
    return pointOnPerimeter(point, 10, 20);
}

QPointF Tooltip::secondPointOnPerimeter(const QPointF& point) {
    return pointOnPerimeter(point, 20, 10);
}

QPointF Tooltip::pointOnPerimeter(const QPointF& point, int modifier1, int modifier2) {
    QPointF corner = nearestCorner(point);

    qreal x = corner.x() + pointLeftOfCenter(point) * modifier1
        - pointRightOfCenter(point) * modifier2
        + cornerCase(point) * !vertical(point, corner)
        * (pointOnLeft(point) * modifier1 - pointOnRight(point) * modifier2);
    qreal y = corner.y() + pointAboveCenter(point) * modifier1
        - pointBelowCenter(point) * modifier2
        + cornerCase(point) * vertical(point, corner)
        * (pointAbove(point) * modifier1 - pointBelow(point) * modifier2);

    return QPointF(x, y);
}

QPointF Tooltip::nearestCorner(const QPointF& anchor) {
    qreal x = (pointOnRight(anchor) + pointRightOfCenter(anchor)) * this->rect.width();
    qreal y = (pointBelow(anchor) + pointBelowCenter(anchor)) * this->rect.height();
    return QPointF(x, y);
}

bool Tooltip::cornerCase(const QPointF& anchor) {
    return (pointAbove(anchor) && pointOnLeft(anchor)) || 
        (pointAbove(anchor) && pointOnRight(anchor)) || 
        (pointBelow(anchor) && pointOnLeft(anchor)) || 
        (pointBelow(anchor) && pointOnRight(anchor));
}

bool Tooltip::vertical(const QPointF& anchor, const QPointF& corner) {
    return qAbs(anchor.x() - corner.x()) > qAbs(anchor.y() - corner.y());
}

bool Tooltip::pointAbove(const QPointF& point) {
    return point.y() <= this->rect.top();
}

bool Tooltip::pointAboveCenter(const QPointF& point) {
    return point.y() > this->rect.top() && point.y() <= this->rect.center().y();
}

bool Tooltip::pointBelow(const QPointF& point) {
    return point.y() > this->rect.bottom();
}

bool Tooltip::pointBelowCenter(const QPointF& point) {
    return point.y() > this->rect.center().y() && point.y() <= this->rect.bottom();
}

bool Tooltip::pointOnLeft(const QPointF& point) {
    return point.x() <= this->rect.left();
}

bool Tooltip::pointLeftOfCenter(const QPointF& point) {
    return point.x() > this->rect.left() && point.x() <= this->rect.center().x(); 
}

bool Tooltip::pointOnRight(const QPointF& point) {
    return point.x() > this->rect.right();
}

bool Tooltip::pointRightOfCenter(const QPointF& point) {
    return point.x() > this->rect.center().x() && point.x() <= this->rect.right();
}

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
