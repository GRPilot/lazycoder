#include "common.h"

#include "mainwindow.h"
// #include "appversion.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "lazycoder_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    MainWindow w;
    // w.setWindowTitle(AppInfo::qName() + " | " + AppInfo::Version::qStr());
    w.show();

    return a.exec();
}
