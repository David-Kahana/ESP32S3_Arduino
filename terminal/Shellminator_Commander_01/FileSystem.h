#include "BaseCommands.h"

class FileSystem
{
  public:
  bool initFileSystem();
  bool formatFileSystem();
  bool spaceFileSystem(size_t& totalBytes, size_t& freeBytes);
  void listDir(const char *dirname, uint8_t levels);
  void makeDir(const char *dirname);
  void removeDir(const char *dirname);
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
        //Logger::log(INF, 1, "P1!!!!!");
        addAllCommands();
        //Logger::log(INF, 1, "P2!!!!!");
        //fs.initFileSystem();
        //Logger::log(INF, 1, "P3!!!!!");
        if (checkResult(fs.initFileSystem(), channel))
        {
            Logger::log(channel, INF, 1, "File system initialized");
        };
    };

    static void formatFileSystem(char *args, Stream *response);
    static void spaceFileSystem(char *args, Stream *response);
    //static void mkdirFileSystem(char *args, Stream *response);
    //static void rmdirFileSystem(char *args, Stream *response);
    static void listFileSystem(char *args, Stream *response);

    bool addAllCommands() override 
    {
        bool ret = true;
        ret &= addCommand("format", "Format file system.", formatFileSystem);
        ret &= addCommand("space", "Display file system space.", spaceFileSystem);
        //ret &= addCommand("mkdir", "Make directory.", mkdirFileSystem);
        //ret &= addCommand("rmdir", "Remove directory.", rmdirFileSystem);
        ret &= addCommand("l", "List files in directory.", listFileSystem);
        return ret;
    };

    static FileSystem fs;

    private:
    static bool common(Stream *response);
    static bool checkResult(bool result,  Stream *response);
};


