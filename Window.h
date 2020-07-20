#ifndef WINDOW_H
#define WINDOW_H

#include "DataRetriever.h"
#include "tooltip.h"
#include <string>
#include <QtCharts>
#include <QMainWindow>

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

QT_USE_NAMESPACE

class Window : public QMainWindow {

    Q_OBJECT

public:

    Window();

private:
    DataRetriever retriever;
    QChartView* chartview;
    Tooltip* tooltip;
    QList<Tooltip*> tooltips;
};

#endif
