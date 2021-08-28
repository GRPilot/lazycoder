#include "common.h"
#include "init_logger.h"

#include "mainwindow.h"

int main(int argc, char *argv[]) {
    Utils::initLogger(argv[0]);
    QApplication a(argc, argv);

    QTranslator translator;
    for (const QString &locale : QLocale::system().uiLanguages()) {
        const QString baseName{ "lazycoder_" + QLocale(locale).name() };
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    MainWindow w;
    w.show();
    return a.exec();
}
