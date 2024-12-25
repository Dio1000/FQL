#include <string>
#include <fstream>
#include <vector>
#include <sys/stat.h>
#include <filesystem>
namespace fs = std::filesystem;

#include "io.h"

bool validFile(const std::string &filePath){
    if (filePath.empty()){
        throw std::runtime_error("File path " + filePath + " was not provided!");
    }

    std::ifstream fin(filePath);
    return fin.good();
}

bool validDirectory(const std::string &dirPath) {
    if (dirPath.empty()){
        throw std::runtime_error("Directory path " + dirPath + " was not provided!");
    }

    struct stat info{};

    if (stat(dirPath.c_str(), &info) != 0) return false;
    return (info.st_mode & S_IFDIR) != 0;
}


std::vector<std::string> readLines(const std::string &filePath){
    if (filePath.empty()){
        throw std::runtime_error("File path " + filePath + " was not provided!");
    }

    if (!validFile(filePath)){
        throw std::runtime_error("File path " + filePath + " does not exist!");
    }

    std::ifstream fin(filePath);
    std::vector<std::string> lines;

    std::string line;
    while (getline(fin, line)){
        lines.push_back(line);
    }
    fin.close();

    return lines;
}

void writeLines(const std::string &filePath, const std::vector<std::string> &lines){
    if (filePath.empty()){
        throw std::runtime_error("File path " + filePath + " was not provided!");
    }

    if (!validFile(filePath)){
        throw std::runtime_error("File path " + filePath + " does not exist!");
    }

    std::ofstream fout(filePath);

    for (const auto& line : lines){
        fout << line << std::endl;
    }
    fout.close();
}

void createFile(const std::string &filePath){
    if (filePath.empty()){
        throw std::runtime_error("File path " + filePath + " was not provided!");
    }

    std::ofstream fout;
    fout.open(filePath);
    fout.close();
}

void deleteFile(const char *filePath){
    if (filePath == nullptr){
        return;
    }

    bool deleted = remove(filePath);
    if (deleted){
        throw std::runtime_error("Could not remove file!");
    }
}

void createDirectory(const char *dirPath){
    if (validDirectory(dirPath)) return;

    if (mkdir(dirPath, 0666) == -1){
        throw std::runtime_error("Could not create directory!");
    }
}

void deleteDirectory(const char *dirPath) {
    if (!validDirectory(dirPath)) return;

    try {
        fs::remove_all(dirPath);
    } catch (const std::filesystem::filesystem_error& e) {
        throw std::runtime_error("Could not remove directory: " + std::string(e.what()));
    }
}