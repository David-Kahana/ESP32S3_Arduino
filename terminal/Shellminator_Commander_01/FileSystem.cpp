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
    std::string directory = "/";
    directory += dirName;
    if (!FFat.mkdir(directory.c_str()))
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
    std::string directory = "/";
    directory += dirName;
    if (!FFat.rmdir(directory.c_str()))
    {
        lastError = "removeDir: Failed to remove directory: ";
        lastError += dirName;
        return false;
    }
    lastError = "";
    return true;
}

bool writeFile(const char *path, const char *message)
{
    if (!isInitialized()) return false;
    //Serial.printf("Writing file: %s\r\n", path);

    File file = fs.open(path, FILE_WRITE);
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
    int argResult = sscanf(args, "%s", pathStr);
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
    sscanf(args, "%s%u", pathStr, &levels);
    checkResult(fs.listDir(response, pathStr, levels), response);
}

//static 
void FileSystemInterface::writeFileSystem(char *args, Stream *response)
{
  
}

// void readFile(fs::FS &fs, const char *path)
// {
//     Serial.printf("Reading file: %s\r\n", path);

//     File file = fs.open(path);
//     if (!file || file.isDirectory())
//     {
//         Serial.println("- failed to open file for reading");
//         return;
//     }

//     Serial.println("- read from file:");
//     while (file.available())
//     {
//         Serial.write(file.read());
//     }
//     file.close();
// }


// void appendFile(fs::FS &fs, const char *path, const char *message)
// {
//     Serial.printf("Appending to file: %s\r\n", path);

//     File file = fs.open(path, FILE_APPEND);
//     if (!file)
//     {
//         Serial.println("- failed to open file for appending");
//         return;
//     }
//     if (file.print(message))
//     {
//         Serial.println("- message appended");
//     }
//     else
//     {
//         Serial.println("- append failed");
//     }
//     file.close();
// }

// void renameFile(fs::FS &fs, const char *path1, const char *path2)
// {
//     Serial.printf("Renaming file %s to %s\r\n", path1, path2);
//     if (fs.rename(path1, path2))
//     {
//         Serial.println("- file renamed");
//     }
//     else
//     {
//         Serial.println("- rename failed");
//     }
// }

// void deleteFile(fs::FS &fs, const char *path)
// {
//     Serial.printf("Deleting file: %s\r\n", path);
//     if (fs.remove(path))
//     {
//         Serial.println("- file deleted");
//     }
//     else
//     {
//         Serial.println("- delete failed");
//     }
// }

// void testFileIO(fs::FS &fs, const char *path)
// {
//     Serial.printf("Testing file I/O with %s\r\n", path);

//     static uint8_t buf[512];
//     size_t len = 0;
//     File file = fs.open(path, FILE_WRITE);
//     if (!file)
//     {
//         Serial.println("- failed to open file for writing");
//         return;
//     }

//     size_t i;
//     Serial.print("- writing");
//     uint32_t start = millis();
//     for (i = 0; i < 2048; i++)
//     {
//         if ((i & 0x001F) == 0x001F)
//         {
//             Serial.print(".");
//         }
//         file.write(buf, 512);
//     }
//     Serial.println("");
//     uint32_t end = millis() - start;
//     Serial.printf(" - %u bytes written in %u ms\r\n", 2048 * 512, end);
//     file.close();

//     file = fs.open(path);
//     start = millis();
//     end = start;
//     i = 0;
//     if (file && !file.isDirectory())
//     {
//         len = file.size();
//         size_t flen = len;
//         start = millis();
//         Serial.print("- reading");
//         while (len)
//         {
//             size_t toRead = len;
//             if (toRead > 512)
//             {
//                 toRead = 512;
//             }
//             file.read(buf, toRead);
//             if ((i++ & 0x001F) == 0x001F)
//             {
//                 Serial.print(".");
//             }
//             len -= toRead;
//         }
//         Serial.println("");
//         end = millis() - start;
//         Serial.printf("- %u bytes read in %u ms\r\n", flen, end);
//         file.close();
//     }
//     else
//     {
//         Serial.println("- failed to open file for reading");
//     }
// }

// void setup()
// {
//     Serial.begin(115200);
//     Serial.setDebugOutput(true);
//     if (FORMAT_FFAT) FFat.format();
//     if (!FFat.begin())
//     {
//         Serial.println("FFat Mount Failed");
//         return;
//     }

//     Serial.printf("Total space: %10u\n", FFat.totalBytes());
//     Serial.printf("Free space: %10u\n", FFat.freeBytes());
//     listDir(FFat, "/", 0);
//     writeFile(FFat, "/hello.txt", "Hello ");
//     appendFile(FFat, "/hello.txt", "World!\r\n");
//     readFile(FFat, "/hello.txt");
//     renameFile(FFat, "/hello.txt", "/foo.txt");
//     readFile(FFat, "/foo.txt");
//     deleteFile(FFat, "/foo.txt");
//     testFileIO(FFat, "/test.txt");
//     Serial.printf("Free space: %10u\n", FFat.freeBytes());
//     deleteFile(FFat, "/test.txt");
//     Serial.println("Test complete");
// }

