#include "Window.h"
#include <QVector>
#include <string>

Window::Window() {
    std::string filename("US_GDP.csv");
    retriever.retrieve_data(filename);

    QList<QPointF> data;
    double max = 0;
    for (int i = 0; i < (int) retriever.getY().size(); i++) {
        data.push_back(QPointF(i, retriever.getY()[i]));

        if (retriever.getY()[i] > max) {
            max = retriever.getY()[i];
        }
    }
    max = max + (max / 10);

    QtCharts::QLineSeries* series = new QtCharts::QLineSeries;
    series->append(data);

    QtCharts::QChart* chart = new QtCharts::QChart;
    chart->addSeries(series);
    chart->setTitle("United States GDP by year.");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    auto* axisX = new QtCharts::QValueAxis;
    axisX->setRange(0, retriever.getY().size());
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
