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

/*
    QTranslator translator;
    for (const QString &locale : QLocale::system().uiLanguages()) {
        const QString baseName{ "lazycoder_" + QLocale(locale).name() };
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    QLocale::setDefault({QLocale::English, QLocale::UnitedStates});
*/