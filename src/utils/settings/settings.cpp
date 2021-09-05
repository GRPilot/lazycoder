#include "common.h"

#include "settings.h"

namespace Utils {

QSettings *getSettings(const QString &type) {
    return Settings::get()[type];
}

//=========================================== Settings ===========================================//

Settings::Settings() : mSettingsMap{ makeSettingsMap() } {}

Settings &Settings::get() {
    static Settings instance;
    return instance;
}

QSettings *Settings::operator[](const QString &type) {
    return (*this)[type.toStdString()];
}

QSettings *Settings::operator[](const std::string &type) {
    return mSettingsMap[type].get();
}

Settings::SettingsMap Settings::makeSettingsMap() const {
    auto make_page{
        [](std::string_view page, std::shared_ptr<QSettings> settings) {
            return std::pair{ page, settings };
        }
    };
    return {
        make_page("app", std::make_shared<QSettings>(root() + "/appSettings.ini", QSettings::IniFormat)),
        make_page("log", std::make_shared<QSettings>(root() + "/logSettings.ini", QSettings::IniFormat)),
    };
}

QString Settings::root() const {
    return QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
}

QString Settings::getStyleSheet() {
    // Opens CSS file with stylesheet.
    QString pathToStyleSheet{ (*this)[QString("app")]->value("theme").toString() };
    QFile styleSheetFile(pathToStyleSheet);
    if (!styleSheetFile.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "File not opened!";
        return defaultStyleSheetString();
    }

    // Reads all strings from this file and simplifies them.
    QTextStream styleSheetStream(&styleSheetFile);
    QString styleSheetString{ styleSheetStream.readAll() };
    styleSheetString = styleSheetString.simplified();
    styleSheetFile.close();
    if (styleSheetStream.status() != QTextStream::Ok) {
        qDebug() << "QTextStream status error!";
        return defaultStyleSheetString();
    }

    return styleSheetString;
}

void Settings::restore() {
    // Restores default app settings in .ini file.
    auto appSettings{ (*this)[QString("app")] };
    appSettings->setValue("theme", root() + "/themes/default.css");
    appSettings->setValue("lang", QLocale());
    appSettings->setValue("default_dir", "some_dir");
    appSettings->setValue("repos", QStringList{"repo1", "repo2", "repo3"});
    appSettings->setValue("autosync", true);

    // Recreates default theme css file.
    QFile defaultThemeFile(root() + "/themes/default.css");
    if (!defaultThemeFile.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "File not opened!";
        return;
    }

    // Writes default stylesheet to default.css file.
    QTextStream styleSheetStream(&defaultThemeFile);
    styleSheetStream << defaultStyleSheetString();
    defaultThemeFile.close();

    if (styleSheetStream.status() != QTextStream::Ok) {
        qDebug() << "QTextStream status error!";
        return;
    }

    // Sets default stylesheet to app.
    qApp->setStyleSheet(defaultStyleSheetString());
}

QString Settings::defaultStyleSheetString() const {
    return "/* Main app style */\n"
           "* {\n"
           "    background-color: rgb(244,244,244);\n"
           "    border: none;\n"
           "}\n"
           "/* Menu buttons style */\n"
           "QFrame#menu QPushButton {\n"
           "    /* border: none; */\n"
           "    padding: 5px;\n"
           "}\n"
           "/* Menu buttons style on hover */\n"
           "QFrame#menu QPushButton::hover {\n"
           "    border: 1px solid black;\n"
           "    border-radius: 5px;\n"
           "}\n"
           "/* Menu buttons style when checked */\n"
           "QFrame#menu QPushButton::checked {\n"
           "    background-color: rgb(220,220,220);\n"
           "    border-radius: 5px;\n"
           "}\n"
           "/* Window control buttons style  */\n"
           "QFrame#headerRight QPushButton {\n"
           "    /* Your styles here */\n"
           "}\n"
           "/* Content widget style (page placeholder) */\n"
           "QWidget#widget {\n"
           "    background-color: white;\n"
           "}";
}

QLocale Settings::getLocale() {
    return {};
}

}  // namespace Utils
