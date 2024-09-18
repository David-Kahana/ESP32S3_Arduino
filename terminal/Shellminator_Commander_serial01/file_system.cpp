#include "file_system.h"
#include "FS.h"
#include "FFat.h"

// This file should be compiled with 'Partition Scheme' (in Tools menu)
// set to 'Default with ffat' if you have a 4MB ESP32 dev module or
// set to '16M Fat' if you have a 16MB ESP32 dev module.

// You only need to format FFat the first time you run a test
// #define FORMAT_FFAT false

bool FileSystem::initFileSystem()
{
    initialized = FFat.begin();
    if (!initialized)
    {
        Serial.printf("FFat mount failed, try formatting\r\n");
        return false;
    }
    FileSystemInterface::fs = this;
    return true;
}

void FileSystem::formatFileSystem()
{
    formatted = FFat.format();
    if (!formatted)
    {
        Serial.printf("FFat format failed\r\n");
        initialized = false;
    }
}

void FileSystem::spaceFileSystem()
{
    if (initialized)
    {
        Serial.printf("Total space: %10u\r\n", FFat.totalBytes());
        Serial.printf("Free space: %10u\r\n", FFat.freeBytes());
    }
    else
    {
        Serial.printf("FFat not initialized\r\n");
    }
}

void FileSystem::listDir(const char *dirname, uint8_t levels)
{
    Serial.printf("Listing directory: %s\r\n", dirname);
    File root = FFat.open(dirname);
    if (!root)
    {
        Serial.printf("- failed to open directory\r\n");
        return;
    }
    if (!root.isDirectory())
    {
        Serial.printf(" - not a directory\r\n");
        return;
    }
    File file = root.openNextFile();
    while (file)
    {
        if (file.isDirectory())
        {
            Serial.printf("  DIR : %s\r\n", file.name());
            if (levels)
            {
                listDir(file.path(), levels - 1);
            }
        }
        else
        {
            Serial.printf("  File: %s\t Size: %d \r\n", file.name(), file.size());
        }
        file = root.openNextFile();
    }
}

void FileSystem::makeDir(const char *dirname)
{
  char* directory = new char[strlen(dirname) + 1];
  directory[0] = '/';
  strcpy(directory+1,dirname);
  if (initialized)
    {
        if (FFat.mkdir(directory))
        {
            Serial.printf("Directory created: %s\r\n", dirname);
        }
        else
        {
            Serial.printf("Failed to create directory: %s\r\n", dirname);
        }
    }
    else
    {
        Serial.printf("FFat not initialized\r\n");
    }
}

void FileSystem::removeDir(const char *dirname)
{
  char* directory = new char[strlen(dirname) + 1];
  directory[0] = '/';
  strcpy(directory+1,dirname);
  if (initialized)
    {
        if (FFat.rmdir(directory))
        {
            Serial.printf("Directory removed: %s\r\n", dirname);
        }
        else
        {
            Serial.printf("Failed to remove directory: %s\r\n", dirname);
        }
    }
    else
    {
        Serial.printf("FFat not initialized\r\n");
    }
}

FileSystem* FileSystemInterface::fs = nullptr;

bool FileSystemInterface::common(Stream *response)
{
  if (fs)
  {
    return true;
  }
  response->printf("Error: File system not initialized\r\n");
  return false;
}

void FileSystemInterface::formatFileSystem(char *args, Stream *response)
{
  if (common(response))
  {
    response->printf("Formatting file system\r\n");
    fs->formatFileSystem();
  }

}

void FileSystemInterface::spaceFileSystem(char *args, Stream *response)
{

}

void FileSystemInterface::mkdirFileSystem(char *args, Stream *response)
{

}

void FileSystemInterface::rmdirFileSystem(char *args, Stream *response)
{

}

void FileSystemInterface::listFileSystem(char *args, Stream *response)
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

// void writeFile(fs::FS &fs, const char *path, const char *message)
// {
//     Serial.printf("Writing file: %s\r\n", path);

//     File file = fs.open(path, FILE_WRITE);
//     if (!file)
//     {
//         Serial.println("- failed to open file for writing");
//         return;
//     }
//     if (file.print(message))
//     {
//         Serial.println("- file written");
//     }
//     else
//     {
//         Serial.println("- write failed");
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

