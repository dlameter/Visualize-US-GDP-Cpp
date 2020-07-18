#include "Window.h"
#include <QVector>
#include <string>

Window::Window() {
    std::string filename("US_GDP.csv");
    retriever.retrieve_data(filename);

    QList<double> data;
    double max = 0;
    for (auto& elem : retriever.getY()) {
        data.push_back(elem);

        if (elem > max) {
            max = elem;
        }
    }
    max = max + (max / 10);
  
    QtCharts::QBarSet* set = new QtCharts::QBarSet("Numbers");
    set->append(data);

    QtCharts::QBarSeries* series = new QtCharts::QBarSeries;
    series->append(set);

    QtCharts::QChart* chart = new QtCharts::QChart;
    chart->addSeries(series);
    chart->setTitle("United States GDP by year.");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    QtCharts::QBarCategoryAxis* axisX = new QtCharts::QBarCategoryAxis;
    for (auto& name : retriever.getX()) {
        axisX->append(QString::fromStdString(name));
    }
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QtCharts::QValueAxis* axisY = new QtCharts::QValueAxis;
    axisY->setRange(0, max);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->show();
    chart->legend()->setAlignment(Qt::AlignBottom);

    chart->show();

    chartview = new QtCharts::QChartView(chart);

    setCentralWidget(chartview);
    resize(420, 300);
}
