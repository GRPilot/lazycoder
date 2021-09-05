#pragma once

class QSettings;

namespace Utils {

class Settings {
    Settings();
    Settings(const Settings &);
    Settings &operator=(Settings &);

    using SettingsMap = std::unordered_map<std::string_view, std::shared_ptr<QSettings>>;
public:
    static Settings &get();
    QSettings *operator[](const QString &type);
    QSettings *operator[](const std::string &type);

    QString getStyleSheet();
    QLocale getLocale();
    void restore();

private:
    SettingsMap mSettingsMap;

    SettingsMap makeSettingsMap() const;
    QString root() const;
    QString defaultStyleSheetString() const;
};

QSettings *getSettings(const QString &type);

}  // namespace Utils
