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

}  // namespace Utils
