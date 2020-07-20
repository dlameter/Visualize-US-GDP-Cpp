#ifndef WINDOW_H
#define WINDOW_H

#include "DataRetriever.h"
#include "tooltip.h"
#include <QtCharts/QChartGlobal>
#include <QtWidgets/QGraphicsView>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

QT_USE_NAMESPACE

class Window : public QGraphicsView {

    Q_OBJECT

public:

    Window(QWidjet* parent = 0);

public slots:
    void keepCallout();
    void tooltip(QPointF point, bool state);

private:
    DataRetriever m_retriever;
    QChart* m_chart;
    Tooltip* m_tooltip;
    QList<Tooltip*> m_tooltips;
};

#endif
