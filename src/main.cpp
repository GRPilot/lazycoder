#include "common.h"

#include "mainwindow.h"

int main(int argc, char *argv[]) {
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
