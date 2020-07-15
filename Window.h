#ifndef WINDOW_H
#define WINDOW_H

#include "DataRetriever.h"
#include <string>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_barchart.h>
#include <QMainWindow>

class Window : public QMainWindow {

    Q_OBJECT

public:

    Window();

private:
    DataRetriever retriever;
    QwtPlot* plot;
    QwtPlotBarChart* plot_chart;
};

#endif
