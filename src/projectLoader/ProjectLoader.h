#pragma once

namespace Project {

class Chain {
public:
    using Params = std::unordered_map<QString, QVariant>;
    virtual bool run() = 0;

protected:
    Params mParams;
};

class Loader : public Chain {
public:
    explicit Loader(const QString &repo, const QString &destination);

    bool run() override;
private:
};

class Unpacker : public Chain {
public:
    explicit Unpacker(const QString &targetPath, const QString &destination);

    bool run() override;
private:
};

class Cleaner : public Chain {
public:
    explicit Cleaner(const QString &directory);

    bool run() override;
};

class Executor {
public:
    Executor &operator=(const Executor &other);

    template<class ChainType, class ...Args>
    bool pushTask(Args ...args) {
        auto chain{ std::make_shared<ChainType>(args...) };
        if(nullptr == chain || !dynamic_cast<Chain *>(chain.get())) {
            return false;
        }
        mTasks.push_back(chain);
        return true;
    }

    bool execute();
private:
    using Tasks = std::vector<std::shared_ptr<Chain>>;
    Tasks mTasks;
};
using ExecutorPtr = std::shared_ptr<Executor>;

class Manager {
public:
    ExecutorPtr makeCloneRepo(const QString &repo, const QString &path) const;
    ExecutorPtr makeExtractAll(const QString &repoDir, const QString &path) const;
    ExecutorPtr makeCloneAndExtractAll(const QString &repo, const QString &path) const;
private:
    QString makeTempPath(QString path) const;
};

}
