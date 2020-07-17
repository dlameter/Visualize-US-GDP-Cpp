#include "Window.h"
#include <QVector>

Window::Window() {
    QList<double> data;
    data.push_back(100.13);
    data.push_back(30.0);
    data.push_back(24);
    data.push_back(206);
    data.push_back(328.3);
    data.push_back(160.1);
  
    QtCharts::QBarSet* set = new QtCharts::QBarSet("Numbers");
    set->append(data);

    QtCharts::QBarSeries* series = new QtCharts::QBarSeries;
    series->append(set);

    QtCharts::QChart* chart = new QtCharts::QChart;
    chart->addSeries(series);
    chart->setTitle("United States GDP by year.");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    QtCharts::QBarCategoryAxis* axisX = new QtCharts::QBarCategoryAxis;
    axisX->append("test");
    axisX->append("test1");
    axisX->append("test2");
    axisX->append("test3");
    axisX->append("test4");
    axisX->append("test5");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QtCharts::QValueAxis* axisY = new QtCharts::QValueAxis;
    axisY->setRange(0, 350);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->show();

    chartview = new QtCharts::QChartView(chart);

    setCentralWidget(chartview);
    resize(420, 300);
}
