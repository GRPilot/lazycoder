#include "common.h"

#include "mainwindow.h"
#include "settings.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Sets stylesheet on startup.
    auto settings{ &Utils::Settings::get() };
    a.setStyleSheet(settings->getStyleSheet());

    MainWindow w;
    w.show();
    return a.exec();
}
