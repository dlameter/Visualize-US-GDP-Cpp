#ifndef WINDOW_H
#define WINDOW_H

#include "DataRetriever.h"
#include <string>
#include <QWidget>

class Window : public QWidget {

    Q_OBJECT

public:

    Window();

    ~Window();

private:
    DataRetriever retriever;
};

#endif
