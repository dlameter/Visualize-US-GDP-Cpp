#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <QtCharts/QChartGlobal>
#include <QtWidgets/QGraphicsItem>
#include <QtGui/QFont>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class Tooltip : public QGraphicsItem {
    public:
        Tooltip(QChart* parent);

        void setText(const QString &text);
        void setAnchor(QPointF anchor);
        void updateGeometry();

        QRectF boundingRect() const;
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent* event);
        void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

    private:
        QString text;
        QRectF textRect;
        QRectF rect;
        QPointF anchor;
        QFont font;
        QChart* chart;

        void modifyPathWithAnchorCorner(QPainterPath& path, const QPointF& point);
        QPointF firstPointOnPerimeter(const QPointF& point);
        QPointF secondPointOnPerimeter(const QPointF& point);
        QPointF pointOnPerimeter(const QPointF& point, int modifier1, int modifier2);
        QPointF nearestCorner(const QPointF& anchor);
        bool cornerCase(const QPointF& anchor);
        bool vertical(const QPointF& anchor, const QPointF& corner);
        bool pointAbove(const QPointF& point);
        bool pointAboveCenter(const QPointF& point);
        bool pointBelow(const QPointF& point);
        bool pointBelowCenter(const QPointF& point);
        bool pointOnLeft(const QPointF& point);
        bool pointLeftOfCenter(const QPointF& point);
        bool pointOnRight(const QPointF& point);
        bool pointRightOfCenter(const QPointF& point);
};

#endif
