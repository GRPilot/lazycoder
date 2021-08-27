#pragma once

namespace Project {

class Task {
public:
    using Params = std::unordered_map<QString, QVariant>;
    virtual bool run() = 0;

protected:
    Params mParams;
};

class Loader : public Task {
public:
    explicit Loader(const QString &repo, const QString &destination);

    bool run() override;
private:
};

class Unpacker : public Task {
public:
    explicit Unpacker(const QString &targetPath, const QString &destination);

    bool run() override;
private:
};

class Cleaner : public Task {
public:
    explicit Cleaner(const QString &directory);

    bool run() override;
};

class TaskExecutor {
public:
    TaskExecutor &operator=(const TaskExecutor &other);

    template<class TaskType, class ...Args>
    bool pushTask(Args ...args) {
        auto chain{ std::make_shared<TaskType>(args...) };
        if(nullptr == chain || !dynamic_cast<Task *>(chain.get())) {
            return false;
        }
        mTasks.push_back(chain);
        return true;
    }

    bool execute();
private:
    using Tasks = std::vector<std::shared_ptr<Task>>;
    Tasks mTasks;
};
using ExecutorPtr = std::shared_ptr<TaskExecutor>;

class Manager {
public:
    ExecutorPtr makeCloneRepo(const QString &repo, const QString &path) const;
    ExecutorPtr makeExtractAll(const QString &repoDir, const QString &path) const;
    ExecutorPtr makeCloneAndExtractAll(const QString &repo, const QString &path) const;
private:
    QString makeTempPath(QString path) const;
};

}
