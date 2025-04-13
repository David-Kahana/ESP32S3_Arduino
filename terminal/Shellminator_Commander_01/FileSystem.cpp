#include <stdint.h>
#include "FileSystem.h"
#include "FS.h"
#include "FFat.h"

// This file should be compiled with 'Partition Scheme' (in Tools menu)
// set to 'Default with ffat' if you have a 4MB ESP32 dev module or
// set to '16M Fat' if you have a 16MB ESP32 dev module.

// You only need to format FFat the first time you run a test
// #define FORMAT_FFAT false

//static 
std::string FileSystem::lastError;

bool FileSystem::initFileSystem()
{
    initialized = FFat.begin();
    return isInitialized();
}

bool FileSystem::isInitialized()
{
    if (!initialized)
    {
        lastError = "FileSystem not initialized";
    }
    return initialized;
}

const char* FileSystem::getLastError()
{
    return lastError.c_str();
}

bool FileSystem::formatFileSystem()
{
    if (initialized) FFat.end();
    delay(1);
    initialized = false;
    formatted = FFat.format();
    if (!formatted)
    {
        lastError = "formatFileSystem failed, FFat format failed";
        return false;
    }
    lastError = "";
    return initFileSystem();
}
    
bool FileSystem::spaceFileSystem(size_t& totalBytes, size_t& freeBytes)
{
    if (!isInitialized()) return false;
    totalBytes =  FFat.totalBytes();
    freeBytes = FFat.freeBytes();
    lastError = "";
    return true;
}

bool FileSystem::listDir(Stream* stream, const char *dirName, uint8_t levels)
{
    if (!isInitialized()) return false;
    stream->printf("Listing directory: %s\r\n", dirName);
    File root = FFat.open(dirName);
    if (!root)
    {
        lastError = "listDir: failed to open directory";
        return false;
    }
    if (!root.isDirectory())
    {
        lastError = "listDir: not a directory";
        return false;
    }
    File file = root.openNextFile();
    if (!file)
    {
        stream->printf("Directory empty\r\n");
    }
    while (file)
    {
        if (file.isDirectory())
        {
            stream->printf("  DIR : %s\r\n", file.name());
            if (levels)
            {
                listDir(stream, file.path(), levels - 1);
            }
        }
        else
        {
            stream->printf("  File: %s\t Size: %d \r\n", file.name(), file.size());
        }
        file = root.openNextFile();
    }
    lastError = "";
    return true;
}

bool FileSystem::makeDir(const char *dirName)
{
    if (!isInitialized()) return false;
    if (!FFat.mkdir(dirName))
    {
        lastError = "makeDir: Failed to create directory: ";
        lastError += dirName;
        return false;
    }
    lastError = "";
    return true;
}

bool FileSystem::removeDir(const char *dirName)
{
    if (!isInitialized()) return false;
    if (!FFat.rmdir(dirName))
    {
        lastError = "removeDir: Failed to remove directory: ";
        lastError += dirName;
        return false;
    }
    lastError = "";
    return true;
}

bool FileSystem::writeFile(const char *path, const char *message)
{
    if (!isInitialized()) return false;
    File file = FFat.open(path, FILE_WRITE);
    if (!file)
    {
        lastError = "writeFile: Failed to open file for writing: ";
        lastError += path;
        return false;
    }
    if (!file.print(message))
    {
        lastError = "writeFile: Failed to write: ";
        lastError += path;
        return false;
    }
    lastError = "";
    file.close();
    return true;
}

bool FileSystem::appendFile(const char *path, const char *message)
{
    if (!isInitialized()) return false;
    File file = FFat.open(path, FILE_APPEND);
    if (!file)
    {
        lastError = "appendFile: Failed to open file for appending: ";
        lastError += path;
        return false;
    }
    if (!file.print(message))
    {
        lastError = "appendFile: Failed to append: ";
        lastError += path;
        return false;
    }
    lastError = "";
    file.close();
    return true;
}

bool FileSystem::readFile(Stream* stream, const char *path)
{
    if (!isInitialized()) return false;
    File file = FFat.open(path);
    if (!file)
    {
        lastError = "readFile: Failed to open file for reading: ";
        lastError += path;
        return false;
    }
    if (file.isDirectory())
    {
        lastError = "readFile: file is a directory: ";
        lastError += path;
        return false;
    }
    while (file.available())
    {
        stream->write(file.read());
    }
    file.close();
    return true;
}

bool FileSystem::renameFile(const char *path1, const char *path2)
{
    if (!isInitialized()) return false;
    
    if (!FFat.rename(path1, path2))
    {
        lastError = "renameFile: Failed to rename file from: ";
        lastError += path1;
        lastError += " to: ";
        lastError += path2;
        return false;
    }
    lastError = "";
    return true;
}

bool FileSystem::deleteFile(const char *path)
{
    if (!isInitialized()) return false;
    if (!FFat.remove(path))
    {
        lastError = "deleteFile: Failed to delete file: ";
        lastError += path;
        return false;
    }
    lastError = "";
    return true;
}

//static 
FileSystem FileSystemInterface::fs;
//static 
char FileSystemInterface::pathStr[MaxPathSize];

//static
bool FileSystemInterface::checkResult(bool result,  Stream *response)
{
    if (!result)
    {
        Logger::log(response, ERR, 1, fs.getLastError());
        return false;
    }
    return true;
}

//static
bool FileSystemInterface::checkForPathName(char* args, Stream *response)
{
    memset(pathStr, 0, MaxPathSize);
    pathStr[0] = '/';
    int argResult = sscanf(args, "%s", pathStr+1);
    // We have to check that we parsed successfully directory name
    if (argResult != 1)
    {
        Logger::log(response, ERR, 1, "checkForPathName: Argument error! one string required (no spaces)");
        return false;
    }
    return true;
}

//static
void FileSystemInterface::formatFileSystem(char *args, Stream *response)
{
    Logger::log(response, INF, 1, "Formatting file system");
    if (checkResult(fs.formatFileSystem(), response))
    {
        Logger::log(response, INF, 1, "Formatting done");
    }
}

//static
void FileSystemInterface::spaceFileSystem(char *args, Stream *response)
{
    size_t totalBytes = 0;
    size_t freeBytes = 0;
    if (checkResult(fs.spaceFileSystem(totalBytes, freeBytes), response))
    {
        Logger::log(response, INF, 1, "Total space:\t%10u", totalBytes);
        Logger::log(response, INF, 1, "Free space:\t%10u", freeBytes);
    }
}

//static
void FileSystemInterface::mkdirFileSystem(char *args, Stream *response)
{
    if (!checkForPathName(args, response)) return;
    checkResult(fs.makeDir(pathStr), response);
}

//static
void FileSystemInterface::rmdirFileSystem(char *args, Stream *response)
{
    if (!checkForPathName(args, response)) return;
    checkResult(fs.removeDir(pathStr), response);
}

//static
void FileSystemInterface::listFileSystem(char *args, Stream *response)
{
    memset(pathStr, 0, MaxPathSize);
    pathStr[0] = '/';
    uint16_t levels = 0;
    sscanf(args, "%s%u", pathStr+1, &levels);
    checkResult(fs.listDir(response, pathStr, levels), response);
}

//static 
void FileSystemInterface::writeFileSystem(char *args, Stream *response)
{
    if (!checkForPathName(args, response)) return;
    char* msg = nullptr;
    msg = strchr(args, ' ');
    checkResult(fs.writeFile(pathStr, msg + 1), response);
}

//static 
void FileSystemInterface::appendFileSystem(char *args, Stream *response)
{
    if (!checkForPathName(args, response)) return;
    char* msg = nullptr;
    msg = strchr(args, ' ');
    checkResult(fs.appendFile(pathStr, msg + 1), response);
}

//static 
void FileSystemInterface::readFileSystem(char *args, Stream *response)
{
    if (!checkForPathName(args, response)) return;
    checkResult(fs.readFile(response, pathStr), response);
}

//static 
void FileSystemInterface::renameFileSystem(char *args, Stream *response)
{
    if (!checkForPathName(args, response)) return;
    char* newName = strchr(args, ' ');
    if (newName == nullptr)
    {
        Logger::log(response, ERR, 1, "checkForPathName: Argument error! second string required (no spaces)");
        return;
    }
    newName[0] = '/';
    checkResult(fs.renameFile(pathStr, newName), response);
}

//static 
void FileSystemInterface::deleteFileSystem(char *args, Stream *response)
{
    if (!checkForPathName(args, response)) return;
    checkResult(fs.deleteFile(pathStr), response);
}
