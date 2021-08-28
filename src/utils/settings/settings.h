#pragma once

#include <QMap>
#include <QSettings>
#include <QStandardPaths>

namespace Utils {

class Settings {
    // Default config location to write settings on current system.
    QString configLocation{ QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) };

public:
    static Settings &get();
    QSettings &operator[](const QString &type);

private:
    Settings();
    Settings(const Settings &);
    Settings &operator=(Settings &);

    QMap<QString, QSettings> mSettingsMap;
};

Settings &getSettings();

}  // namespace Utils
