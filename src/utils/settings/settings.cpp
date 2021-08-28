#include "settings.h"

namespace Utils {

Settings::Settings() {
    mSettingsMap.insert("app", {configLocation + "/appSettings.ini", QSettings::IniFormat});
    mSettingsMap.insert("log", {configLocation + "/logSettings.ini", QSettings::IniFormat});
}

Settings &Settings::get() {
    static Settings instance;
    return instance;
}

Settings &getSettings() {
    return Settings::get();
}

QSettings &Settings::operator[](const QString &type) {
    return mSettingsMap[type];
}

}  // namespace Utils
