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

class Tooltip : QGraphicsItem {
    Q_OBJECT

    public:
        Callout(QChart* parent);

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
};

#endif