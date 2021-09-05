#include "common.h"

#include "mainwindow.h"
#include "settings.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Sets stylesheet on startup.
    auto settings{ &Utils::Settings::get() };
    a.setStyleSheet(settings->getStyleSheet());

    // qDebug() << Utils::getSettings("app")->value("lang");
    QLocale::setDefault(Utils::getSettings("app")->value("lang").toLocale());

    // Sets default locale on startup.
    // TODO: Set this from Settings OR exclude this 4ever 😁.
    // QLocale::setDefault({ QLocale::English, QLocale::LatinScript, QLocale::UnitedStates });
    // qDebug() << Utils::getSettings("app")->value("lang").toLocale();
    // qDebug() << QVariant("rus").toLocale();

    MainWindow w;
    w.show();
    return a.exec();
}
