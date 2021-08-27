#include "common.h"

#include "archive.h"

namespace Utils {

Archive::Archive(const std::string &filename, bool throwable)
    : mFile{ unzOpen(filename.c_str()) }, mThrowable{ throwable } {
    if(filename.empty() && nullptr == mFile) {
        if(mThrowable) {
            throw ArchiveException{ "Cannot open '" + filename + "' archive" };
        }
        return;
    }
    
    if(int status{ unzGetGlobalInfo(mFile, &mInfo) }; status != UNZ_OK) {
        if(mThrowable) {
            std::stringstream error;
            error << "Cannot get information about '" << filename << "' archive: ";
            error << status << " (" << std::hex << status << ")";
            throw ArchiveException{ error.str() };
        }
        return;
    }
    if(!collectArchiveInformation()) {
        if(mThrowable) {
            throw ArchiveException{ "Cannot collect archive information" };
        }
        return;
    }
    mValid = true;
}

Archive::~Archive() {
    unzClose(mFile);
}

bool Archive::valid() const {
    return mValid;
}

size_t Archive::size(bool uncompressed) const {
    if(!mValid) {
        return 0;
    }
    return (uncompressed ? mUncompressedSize : mCompressedSize);
}

size_t Archive::count(int entries) const {
    auto is = [entries](int entry){
        return (entries & entry) == entry;
    };
    if(is(Entries::Files | Entries::Directories)) {
        return mFileCount + mDirCount;
    }
    if(is(Entries::Files)) {
        return mFileCount;
    }
    if(is(Entries::Directories)) {
        return mDirCount;
    }
    return 0;
}

bool Archive::unpack(const std::string &path) {
    if(path.empty()) {
        return false;
    }
    QDir dir;
    dir.mkdir(QString::fromStdString(path));

    /// @todo: create path directory

    constexpr size_t READ_SIZE{ 8192 };
    char readBuffer[READ_SIZE]{};
    unz_file_pos initPosition;
    unzGetFilePos(mFile, &initPosition);
    for(uLong i{}; i < mInfo.number_entry; ++i) {
        // Get info about current file.
        unz_file_info file_info;
        char filename[mMaxFilenameSize]{};
        const int status{
            unzGetCurrentFileInfo(
                mFile, &file_info,
                filename, mMaxFilenameSize,
                nullptr, 0, nullptr, 0 )
        };
        if(status != UNZ_OK) {
            unzGoToFilePos(mFile, &initPosition);
            return false;
        }

        // Check if this entry is a directory or file.
        const size_t filename_length{ std::strlen(filename) };

        if(filename[ filename_length-1 ] != '/') {
            // Entry is a file, so extract it.
            if(unzOpenCurrentFile(mFile) != UNZ_OK) {
                unzGoToFilePos(mFile, &initPosition);
                return false;
            }

            // Open a file to write out the data.
            std::ofstream out{ path + "/" + filename };
            auto readbytes{ [&]() {
                    return unzReadCurrentFile(mFile, readBuffer, READ_SIZE);
                }
            };
            int size{readbytes()};
            for(; size != 0; size = readbytes()) {
                if(size < 0) {
                    unzCloseCurrentFile(mFile);
                    unzGoToFilePos(mFile, &initPosition);
                    return false;
                }
                out << readBuffer;
            }
        } else {
            // Entry is a directory, so create it.
            QDir{}.mkdir( QString::fromStdString(path + "/" + filename) );
        }

        unzCloseCurrentFile(mFile);

        // Go the the next entry listed in the zip file.
        if(i + 1 < mInfo.number_entry) {
            const int status{ unzGoToNextFile(mFile) };
            if (status != UNZ_OK) {
                unzGoToFilePos(mFile, &initPosition);
                return false;
            }
        }
    }
    unzGoToFilePos(mFile, &initPosition);
    return true;
}

bool Archive::collectArchiveInformation() {
    size_t dirCount{};
    size_t fileCount{};
    size_t uncompressedSize{};
    size_t compressedSize{};

    unz_file_pos initPosition;
    unzGetFilePos(mFile, &initPosition);

    for(uLong i{}; i < mInfo.number_entry; ++i) {
        unz_file_info fileInfo;
        char filename[mMaxFilenameSize]{};
        int status{
            unzGetCurrentFileInfo(
                mFile, &fileInfo,
                filename, mMaxFilenameSize,
                nullptr, 0, nullptr, 0
            )
        };
        if(status != UNZ_OK) {
            return false;
        }
        uncompressedSize += fileInfo.uncompressed_size;
        compressedSize += fileInfo.compressed_size;
        const size_t fnameLen{ std::strlen(filename) };
        const char lastChar{filename[fnameLen - 1]};
        if(lastChar == '/' || lastChar == '\\') {
            ++dirCount;
        } else {
            ++fileCount;
        }
        if(unzGoToNextFile(mFile) != UNZ_OK) {
            break;
        }
    }
    unzGoToFilePos(mFile, &initPosition);
    mFileCount = fileCount;
    mDirCount = dirCount;
    mUncompressedSize = uncompressedSize;
    mCompressedSize = compressedSize;
    return true;
}


}
