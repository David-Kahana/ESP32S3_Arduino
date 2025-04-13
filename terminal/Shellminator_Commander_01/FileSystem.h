#include <stdint.h>
#include "BaseCommands.h"

class FileSystem
{
  public:
  bool initFileSystem();
  bool formatFileSystem();
  bool spaceFileSystem(size_t& totalBytes, size_t& freeBytes);
  bool listDir(Stream* stream, const char *dirName, uint8_t levels);
  bool makeDir(const char *dirName);
  bool removeDir(const char *dirName);
  bool writeFile(const char *path, const char *message);
  bool appendFile(const char *path, const char *message);
  bool readFile(Stream* stream, const char *path);
  bool renameFile(const char *path1, const char *path2);
  bool deleteFile(const char *path);
  bool isInitialized();
  const char* getLastError();

  private:
  bool initialized = false;
  bool formatted = false;
  static std::string lastError;
};

class FileSystemInterface : public BaseCommands
{
    public:
    FileSystemInterface(Stream* channel)
    {
        addAllCommands();
        if (checkResult(fs.initFileSystem(), channel))
        {
            Logger::log(channel, INF, 1, "File system initialized");
        };
    };

    static void formatFileSystem(char *args, Stream *response);
    static void spaceFileSystem(char *args, Stream *response);
    static void mkdirFileSystem(char *args, Stream *response);
    static void rmdirFileSystem(char *args, Stream *response);
    static void listFileSystem(char *args, Stream *response);
    static void writeFileSystem(char *args, Stream *response);
    static void appendFileSystem(char *args, Stream *response);
    static void readFileSystem(char *args, Stream *response);
    static void renameFileSystem(char *args, Stream *response);
    static void deleteFileSystem(char *args, Stream *response);

    bool addAllCommands() override 
    {
        bool ret = true;

        ret &= addCommand("format", "Format file system.", formatFileSystem);
        ret &= addCommand("space", "Display file system space.", spaceFileSystem);
        ret &= addCommand("mkdir", "Make directory.", mkdirFileSystem);
        ret &= addCommand("rmdir", "Remove directory.", rmdirFileSystem);
        ret &= addCommand("l", "List files in directory.", listFileSystem);
        ret &= addCommand("w", "Write to file, enter file path and content.", writeFileSystem);
        ret &= addCommand("a", "Append to a file, enter file path and content.", appendFileSystem);
        ret &= addCommand("r", "Read from a file, enter file path.", readFileSystem);
        ret &= addCommand("ren", "Rename file, enter file path and new file name.", renameFileSystem);
        ret &= addCommand("del", "Delete file, enter file path.", deleteFileSystem);
        
        return ret;
    };

    static FileSystem fs;

    private:
    static bool checkResult(bool result, Stream *response);
    static bool checkForPathName(char* args, Stream *response);
    inline static const uint16_t MaxPathSize = 64; 
    static char pathStr[MaxPathSize];
};


