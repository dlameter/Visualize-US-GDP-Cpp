#include "Window.h"
#include <QVector>

Window::Window() {
    QVector<double> data;
    data.push_back(100.13);
    data.push_back(30.0);
    data.push_back(24);
    data.push_back(206);
    data.push_back(328.3);
    data.push_back(160.1);
  
    plot_chart = new QwtPlotBarChart;
    plot = new QwtPlot;

    plot_chart->setSamples(data);
    plot_chart->attach(plot);

    plot->replot();
    plot->show();
}
