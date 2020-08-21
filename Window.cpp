#include "Window.h"
#include "tooltip.h"
#include <QtCharts/QChart>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtWidgets/QGraphicsScene>
#include <QtGui/QMouseEvent>
#include <QtGui/QResizeEvent>
#include <QVector>
#include <string>

Window::Window(QWidget* parent): 
    QGraphicsView(new QGraphicsScene, parent), 
    m_chart(0), 
    m_tooltip(0)
{
    setupGraphicsView();
    buildAndShowChart("US_GDP.csv");
    this->setMouseTracking(true);
}

void Window::setupGraphicsView() {
    setDragMode(QGraphicsView::NoDrag);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Window::buildAndShowChart(const std::string& filename) {
    m_chart = new QtCharts::QChart;

    QLineSeries* series = new QLineSeries;
    int max = readDataFromFileAndReturnMax(series, filename);

    setupChart(series);
    addXAxis(series);
    addYAxis(series, max);
    setupTooltip(series);
    showChart();
}

int Window::readDataFromFileAndReturnMax(QLineSeries* series, const std::string& filename) {
    m_retriever.retrieve_data(filename);

    QList<QPointF> data;
    double max = 0;
    for (int i = 0; i < (int) m_retriever.getY().size(); i++) {
        data.push_back(
                QPointF(
                    m_retriever.stringToDate(m_retriever.getX()[i]).toMSecsSinceEpoch(), 
                    m_retriever.getY()[i]
                )
            );

        if (m_retriever.getY()[i] > max) {
            max = m_retriever.getY()[i];
        }
    }
    max = max + (max / 10);

    series->append(data);
    return max;
}

void Window::setupChart(QLineSeries* series) {
    m_chart->addSeries(series);
    m_chart->setTitle("United States GDP by year.");
    m_chart->setMinimumSize(640, 480);
    m_chart->setAnimationOptions(QChart::SeriesAnimations);
    m_chart->setAcceptHoverEvents(true);
    m_chart->legend()->show();
    m_chart->legend()->setAlignment(Qt::AlignBottom);
}


void Window::addXAxis(QLineSeries* series) {
    auto* axisX = new QDateTimeAxis;
    axisX->setFormat("yyyy");
    axisX->setTickCount(10);
    axisX->setTitleText("Year");

    m_chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
}

void Window::addYAxis(QLineSeries* series, int max) {
    auto* axisY = new QValueAxis;
    axisY->setRange(0, max);
    axisY->setLabelFormat("$%.0f");
    axisY->setTickCount(8);
    axisY->setTitleText("Billion dollar(s) USD");

    m_chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
}

void Window::setupTooltip(QLineSeries* series) {
    connect(series, &QLineSeries::clicked, this, &Window::keepTooltip);
    connect(series, &QLineSeries::hovered, this, &Window::tooltip);
}

void Window::showChart() {
    m_chart->show();
    scene()->addItem(m_chart);
}

void Window::resizeEvent(QResizeEvent* event) {
    if (scene()) {
        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
        m_chart->resize(event->size());

        const auto tooltips = m_tooltips;
        for (Tooltip* tooltip : tooltips) {
            tooltip->updateGeometry();
        }
    }

    QGraphicsView::resizeEvent(event);
}

void Window::mouseMoveEvent(QMouseEvent* event) {
    QGraphicsView::mouseMoveEvent(event);
}

void Window::keepTooltip() {
    m_tooltips.push_back(m_tooltip);
    m_tooltip = new Tooltip(m_chart);
    m_tooltip->hide();
}

void Window::tooltip(QPointF point, bool state) {
    if (m_tooltip == 0) {
        m_tooltip = new Tooltip(m_chart);
    }

    if (state) {
        QDateTime date = QDateTime::fromMSecsSinceEpoch(point.x());
        m_tooltip->setText(QString("X: %1 \nY: $%2 billion ").arg(date.toString("MM-yyyy")).arg(point.y()));
        m_tooltip->setAnchor(point);
        m_tooltip->setZValue(11);
        m_tooltip->updateGeometry();
        m_tooltip->show();
    }
    else {
        m_tooltip->hide();
    }
}
