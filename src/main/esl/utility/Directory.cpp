#include <esl/utility/Directory.h>
#include <esl/utility/String.h>
#include <esl/Logger.h>

#include <esl/system/Stacktrace.h>

#include <stdexcept>

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <unistd.h>

namespace esl {
inline namespace v1_6 {
namespace utility {

namespace {
Logger logger("esl::utility::Directory");

Directory::Entry _getEntry(const std::string& path, const std::string& fileName) {
    Directory::Entry entry;

    std::string fullPath = path + "/" + fileName;
    struct stat st;

    if (stat(fullPath.c_str(), &st) == -1) {
        throw esl::system::Stacktrace::add(std::runtime_error("stat failed for path \"" + fullPath + "\""));
    }

    // falls es kein Verzeichnis und keine regulaere Datei ist (Bsp. Socket, FIFO, Device, ...)
    if((st.st_mode & S_IFDIR) == 0 && (st.st_mode & S_IFREG) == 0) {
        throw esl::system::Stacktrace::add(std::runtime_error("no regular file: \"" + fullPath + "\""));
    }

    entry.name = fileName;
    entry.isExecutable = ((st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) != 0) && ((st.st_mode & S_IFDIR) == 0);
    entry.isDirectory = ((st.st_mode & S_IFDIR) != 0);
    entry.size = st.st_size;
    entry.path = path;
    //entry.ts = esl::Time(st.st_mtime);

    return entry;
}

void _scan(std::vector<Directory::Entry>& entries, bool recursive, const std::string& aPath) {
    std::string path = (!aPath.empty() && aPath.back() != '/') ? aPath + '/' : aPath;
    DIR* dir = opendir(path.c_str());
    if(dir == nullptr) {
        logger.warn << "Cannot open directory \"" << path << "\"\n";
    }

    struct dirent* ent = nullptr;
    while(dir != nullptr && (ent = readdir(dir)) != nullptr) {
        std::string name = ent->d_name;
        const std::string fullFileName = path + name;

        if(name.size() == 0 || name[0] == '.') {
            continue;
        }

        Directory::Entry entry;
        try {
        	entry = _getEntry(path, name);
        }
        catch(...) {
            continue;
        }

        if(entry.isDirectory && recursive) {
            _scan(entries, recursive, fullFileName);
        }

        entries.push_back(std::move(entry));
    }

    closedir(dir);
}
}

Directory::Directory(std::string path)
: path(std::move(path))
{
}

Directory::Entry Directory::getEntry() const {
    Entry entry;

    std::vector<std::string> folders = String::split(path, '/');
    if(folders.empty()) {
        throw esl::system::Stacktrace::add(std::runtime_error("invalid path"));
    }

    for(unsigned int i=0; i<folders.size()-1; ++i) {
    	entry.path += "/" + folders[i];
    }
    entry.name = folders[folders.size()-1];

    entry = _getEntry(entry.path, entry.name);

    return entry;
}

std::vector<Directory::Entry> Directory::scan(bool recursive) const {
    std::vector<Entry> entries;

    _scan(entries, recursive, path);

    return entries;
}

} /* namespace utility */
} /* inline namespace v1_6 */
} /* namespace esl */
