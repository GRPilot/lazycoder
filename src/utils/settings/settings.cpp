#include <QSettings>
#include <QStandardPaths>

namespace setm {
QSettings &Settings() {
    static QSettings settings(
        QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + "/settings.ini",
        QSettings::IniFormat);

    return settings;
}
}  // namespace setm
