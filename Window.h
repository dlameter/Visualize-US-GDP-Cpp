#ifndef WINDOW_H
#define WINDOW_H

#include "DataRetriever.h"
#include "tooltip.h"
#include <QtCharts/QChartGlobal>
#include <QtWidgets/QGraphicsView>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QMouseEvent;
class QResizeEvent;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
class QLineSeries;
QT_CHARTS_END_NAMESPACE

QT_USE_NAMESPACE

class Window : public QGraphicsView {

    Q_OBJECT

public:

    Window(QWidget* parent = 0);

protected:
    void resizeEvent(QResizeEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

public slots:
    void keepTooltip();
    void tooltip(QPointF point, bool state);

private:
    DataRetriever m_retriever;
    QChart* m_chart;
    Tooltip* m_tooltip;
    QList<Tooltip*> m_tooltips;

    void setupGraphicsView();
    void buildAndShowChart(const std::string& filename);
    int readDataFromFileAndReturnMax(QLineSeries* series, const std::string& filename);
    void setupChart(QLineSeries* series);
    void addXAxis(QLineSeries* series);
    void addYAxis(QLineSeries* series, int max);
    void setupTooltip(QLineSeries* series);
    void showChart();
};

#endif
