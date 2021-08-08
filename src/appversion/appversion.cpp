#include "common.h"

#include "appversion.h"

std::string AppInfo::Version::str() {
    std::stringstream out;
    out << "v" << major << "." << minor << "." << patch;
    return out.str();
}
QString AppInfo::Version::qStr() {
    return QString::fromStdString(Version::str());
}
