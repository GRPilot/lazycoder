#include "common.h"

#include "appversion.h"

std::string AppInfo::Version::str() {
    std::stringstream out;
    out << "v" << major << "." << minor << "." << patch;
    return out.str();
}

QString AppInfo::qName() {
    return QString::fromStdString(name());
}

QString AppInfo::Version::qStr() {
    return QString::fromStdString(Version::str());
}
