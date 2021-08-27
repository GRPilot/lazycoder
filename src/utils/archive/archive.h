#pragma once

namespace Utils {

class ArchiveException : public std::exception {
    const std::string mMsg;
public:
    explicit ArchiveException(const std::string &msg) : mMsg{msg} {}

    inline const char *what() const noexcept override {
        return mMsg.c_str();
    }
};

class Archive {
public:
    explicit Archive(const std::string &filename, bool throwable = false);
    ~Archive();

    bool valid() const;

    /**
     * @brief Get archive's size in bytes
     * 
     * @param uncompressed get uncompressed size or compressed
     * @return 0 if archive is invalid or getting information failed. > 0 - size
     */
    size_t size(bool uncompressed = false) const;

    enum Entries {
        Files       = (1 << 0),
        Directories = (1 << 1)
    };
    /**
     * @brief Get count of entries
     * 
     * @param entires the type of entires, is bitmap
     * @return size_t count or 0 if archive is invalid
     */
    size_t count(int entries = Entries::Files | Entries::Directories) const;

    /**
     * @brief Extract zip file
     * 
     * @param path The extracted folder directory
     * @return true
     * @return false
     */
    bool unpack(const std::string &path);

private:
    const size_t mMaxFilenameSize{ 512 };
    unzFile mFile{};
    unz_global_info mInfo{};
    const bool mThrowable{ false };
    bool mValid{ false };
    size_t mUncompressedSize{};
    size_t mCompressedSize{};
    size_t mFileCount{};
    size_t mDirCount{};

    bool collectArchiveInformation();
};

}
