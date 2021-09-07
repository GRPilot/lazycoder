#include "common.h"
#include "appversion.h"

#include "init_logger.h"

namespace {
std::string extractPath(const std::string &path) {
    size_t sepPos{ path.find_last_of("\\/") };
    if(std::string::npos == sepPos) {
        return path;
    }
    return path.substr(0, sepPos);
}
void makeLogDir(const std::string &path) {
    QDir{}.mkpath(QString::fromStdString(path));
}
std::string makeDateTime() {
    char buffer[sizeof("DDMMYYYY_HHMMSS")]{};
    std::tm tm;
    auto timestamp{ time(nullptr) };
    localtime_s(&tm, &timestamp);
    size_t size{ std::strftime(buffer, sizeof(buffer), "%d%m%y_%H%M%S", &tm) };
    if(size <= 0) {
        return "";
    }
    return std::string{ buffer, size };
}
}  // namespace

void Utils::initLogger(const std::string &path) {
    ///@todo: Make configurable path for logs
    auto logsDir{ extractPath(path).append("/logs") };
    makeLogDir(logsDir);
    std::stringstream logfname;
    logfname << logsDir << "/" << AppInfo::Version::str()
             << "_" << makeDateTime() << ".csv";

    constexpr size_t maxLogSize{ 1000000 };
    auto fname{ logfname.str() };
    static plog::RollingFileAppender<plog::CsvFormatter> file{
        fname.c_str(), maxLogSize, 1
    };
    plog::Severity lvl{ plog::info };
#if defined(DEBUG)
    static plog::ConsoleAppender<plog::TxtFormatter> console;
    lvl = plog::debug;
#endif
    plog::init(lvl, &file)
#if defined(DEBUG)
        .addAppender(&console)
#endif
        ;
    PLOGI << "----------" << AppInfo::name() << " " << AppInfo::Version::str() << "----------";
    PLOGI << "PLog initialized";
}
