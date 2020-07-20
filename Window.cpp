#include "Window.h"
#include "tooltip.h"
#include <QtCharts/QChart>
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
    // setup graphics view
    setDragMode(QGraphicsView::NoDrag);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // read data from file
    std::string filename("US_GDP.csv");
    m_retriever.retrieve_data(filename);

    QList<QPointF> data;
    double max = 0;
    for (int i = 0; i < (int) m_retriever.getY().size(); i++) {
        data.push_back(QPointF(i, m_retriever.getY()[i]));

        if (m_retriever.getY()[i] > max) {
            max = m_retriever.getY()[i];
        }
    }
    max = max + (max / 10);

    // build chart
    QLineSeries* series = new QLineSeries;
    series->append(data);

    m_chart = new QtCharts::QChart;
    m_chart->addSeries(series);
    m_chart->setTitle("United States GDP by year.");
    m_chart->setMinimumSize(640, 480);
    m_chart->setAnimationOptions(QChart::SeriesAnimations);

    auto* axisX = new QValueAxis;
    axisX->setRange(0, m_retriever.getY().size());
    m_chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis* axisY = new QValueAxis;
    axisY->setRange(0, max);
    m_chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    m_chart->setAcceptHoverEvents(true);
    m_chart->legend()->show();
    m_chart->legend()->setAlignment(Qt::AlignBottom);

    m_chart->show();
    scene()->addItem(m_chart);

    this->setMouseTracking(true);
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

void Window::keepCallout() {
    m_tooltips.push_back(m_tooltip);
    m_tooltip = new Tooltip(m_chart);
}

void Window::tooltip(QPointF point, bool state) {
    if (m_tooltip == 0) {
        m_tooltip = new Tooltip(m_chart);
    }

    if (state) {
        m_tooltip->setText(QString("X: %1 \nY: %2 ").arg(point.x(), point.y()));
        m_tooltip->setAnchor(point);
        m_tooltip->setZValue(11);
        m_tooltip->updateGeometry();
        m_tooltip->show();
    }
    else {
        m_tooltip->hide();
    }
}
