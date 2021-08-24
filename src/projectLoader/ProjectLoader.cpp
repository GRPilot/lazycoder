#include "common.h"

#include "ProjectLoader.h"

namespace Project {

//============================ Loader ============================//
Loader::Loader(const QString &repo, const QString &destination) {
    mParams["repository"] = repo;
    mParams["destination"] = destination;
}

bool Loader::run() {
}

//=========================== Unpacker ===========================//
Unpacker::Unpacker(const QString &targetPath, const QString &destination) {
    mParams["target_path"] = targetPath;
    mParams["destination"] = destination;
}

bool Unpacker::run() {
}

//=========================== Cleaner ============================//
Cleaner::Cleaner(const QString &directory) {
    mParams["clean_dir"] = directory;
}

bool Cleaner::run() {
    QString dir{ mParams["clean_dir"].toString() };
    QDir directory{ dir };
    if(!directory.exists()) {
        return false;
    }
    return directory.removeRecursively();
}

//=========================== Executor ===========================//

Executor& Executor::operator=(const Executor &other) {
    if(this == &other) {
        return *this;
    }
    mTasks.insert(mTasks.end(), other.mTasks.begin(), other.mTasks.end());
    return *this;
}

bool Executor::execute() {
    for(auto &task : mTasks) {
        if(task && !task->run()) {
            return false;
        }
    }
    return true;
}

//=========================== Manager ============================//

ExecutorPtr Manager::makeCloneRepo(const QString &repo, const QString &path) const {
    auto executor{ std::make_shared<Executor>() };
    executor->pushTask<Loader>(repo, path);
    return executor;
}

ExecutorPtr Manager::makeExtractAll(const QString &repoDir, const QString &path) const {
    const QString projectInfo{ "project_info.json" };
    QDirIterator it{
        repoDir, QStringList() << projectInfo,
        QDir::Files, QDirIterator::Subdirectories
    };
    auto executor{ std::make_shared<Executor>() };
    while(it.hasNext()) {
        auto dir{ it.next() };
        dir.remove(projectInfo);
        QString dest{ path + QString{ dir }.remove(repoDir) };
        executor->pushTask<Unpacker>(dir, dest);
    }
    return executor;
}

ExecutorPtr Manager::makeCloneAndExtractAll(const QString &repo, const QString &path) const {
    auto tmpPath{ makeTempPath(path) };
    auto executor{ makeCloneRepo(repo, tmpPath) };
    auto extracter{ makeExtractAll(tmpPath, path) };
    *executor = *extracter;
    executor->pushTask<Cleaner>(tmpPath);
    return executor;
}

QString Manager::makeTempPath(QString path) const {
    auto pathstr{ path.toStdString() };
    auto sep{ pathstr.find_last_of("\\/") };
    if(sep != std::string::npos) {
        pathstr = pathstr.substr(0, sep);
    }
    pathstr.append("/tmp");
    return QString::fromStdString(pathstr);
}

}
