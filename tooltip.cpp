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
        QPointF point1, point2;

        // establish the position of the anchor point in relation to m_rect
        bool above = point.y() <= this->rect.top();
        bool aboveCenter = point.y() > this->rect.top() && point.y() <= this->rect.center().y();
        bool belowCenter = point.y() > this->rect.center().y() && point.y() <= this->rect.bottom();
        bool below = point.y() > this->rect.bottom();

        bool onLeft = point.x() <= this->rect.left();
        bool leftOfCenter = point.x() > this->rect.left() && point.x() <= this->rect.center().x();
        bool rightOfCenter = point.x() > this->rect.center().x() && point.x() <= this->rect.right();
        bool onRight = point.x() > this->rect.right();

        // get the nearest m_rect corner.
        qreal x = (onRight + rightOfCenter) * this->rect.width();
        qreal y = (below + belowCenter) * this->rect.height();
        bool cornerCase = (above && onLeft) || (above && onRight) || (below && onLeft) || (below && onRight);
        bool vertical = qAbs(point.x() - x) > qAbs(point.y() - y);

        qreal x1 = x + leftOfCenter * 10 - rightOfCenter * 20 + cornerCase * !vertical * (onLeft * 10 - onRight * 20);
        qreal y1 = y + aboveCenter * 10 - belowCenter * 20 + cornerCase * vertical * (above * 10 - below * 20);;
        point1.setX(x1);
        point1.setY(y1);

        qreal x2 = x + leftOfCenter * 20 - rightOfCenter * 10 + cornerCase * !vertical * (onLeft * 20 - onRight * 10);;
        qreal y2 = y + aboveCenter * 20 - belowCenter * 10 + cornerCase * vertical * (above * 20 - below * 10);;
        point2.setX(x2);
        point2.setY(y2);

        path.moveTo(point1);
        path.lineTo(point);
        path.lineTo(point2);
        path = path.simplified();
    }
    painter->setBrush(QColor(255, 255, 255));
    painter->drawPath(path);
    painter->drawText(this->textRect, this->text);
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
