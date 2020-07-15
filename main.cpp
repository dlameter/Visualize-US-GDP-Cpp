#include "Window.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication graphapp(argc, argv);

    Window window;
    window.show();

    return graphapp.exec();
}
