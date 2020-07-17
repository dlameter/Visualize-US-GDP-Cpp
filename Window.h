#ifndef WINDOW_H
#define WINDOW_H

#include "DataRetriever.h"
#include <string>
#include <QtCharts>
#include <QMainWindow>

class Window : public QMainWindow {

    Q_OBJECT

public:

    Window();

private:
    DataRetriever retriever;
    QtCharts::QChartView* chartview;
};

#endif
