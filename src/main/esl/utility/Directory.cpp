/*
MIT License
Copyright (c) 2019, 2020 Sven Lukas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <esl/utility/Directory.h>
#include <esl/utility/String.h>
#include <esl/Stacktrace.h>
#include <esl/logging/Logger.h>
#include <exception>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <unistd.h>

namespace esl {
namespace utility {

namespace {

Directory::Entry getEntry(const std::string& path, const std::string& fileName) {
    Directory::Entry entry;

    std::string fullPath = path + "/" + fileName;
    struct stat st;

    if (stat(fullPath.c_str(), &st) == -1) {
        throw esl::addStacktrace(std::runtime_error("stat failed for path \"" + fullPath + "\""));
    }

    // falls es kein Verzeichnis und keine regulaere Datei ist (Bsp. Socket, FIFO, Device, ...)
    if((st.st_mode & S_IFDIR) == 0 && (st.st_mode & S_IFREG) == 0) {
        throw esl::addStacktrace(std::runtime_error("no regular file: \"" + fullPath + "\""));
    }

    entry.name = fileName;
    entry.isExecutable = ((st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) != 0) && ((st.st_mode & S_IFDIR) == 0);
    entry.isDirectory = ((st.st_mode & S_IFDIR) != 0);
    entry.size = st.st_size;
    entry.path = path;
    //entry.ts = esl::Time(st.st_mtime);

    return entry;
}

void scan(std::vector<Directory::Entry>& entries, bool recursive, const std::string& aPath) {
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
        	entry = getEntry(path, name);
        }
        catch(...) {
            continue;
        }

        if(entry.isDirectory && recursive) {
            scan(entries, recursive, fullFileName);
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

    std::vector<std::string> folders = esl::utility::String::split(path, '/');
    if(folders.empty()) {
        throw esl::addStacktrace(std::runtime_error("invalid path"));
    }

    for(unsigned int i=0; i<folders.size()-1; ++i) {
    	entry.path += "/" + folders[i];
    }
    entry.name = folders[folders.size()-1];

    entry = esl::utility::getEntry(entry.path, entry.name);

    return entry;
}

std::vector<Directory::Entry> Directory::scan(bool recursive) const {
    std::vector<Entry> entries;

    esl::utility::scan(entries, recursive, path);

    return entries;
}

} /* namespace utility */
} /* namespace esl */
