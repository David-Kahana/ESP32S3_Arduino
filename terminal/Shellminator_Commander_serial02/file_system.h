#include "BaseCommands.h"

class FileSystem
{
    public:
    bool initFileSystem();
    void formatFileSystem();
    void spaceFileSystem();
    void listDir(const char *dirname, uint8_t levels);
    void makeDir(const char *dirname);
    void removeDir(const char *dirname);

    private:
    bool initialized = false;
    bool formatted = false; 
};

class FileSystemInterface : public BaseCommands
{
    public:
    // commands
    static void formatFileSystem(char *args, Stream *response);
    static void spaceFileSystem(char *args, Stream *response);
    static void mkdirFileSystem(char *args, Stream *response);
    static void rmdirFileSystem(char *args, Stream *response);
    static void listFileSystem(char *args, Stream *response);

    bool initialize()
    {
        fs.initFileSystem();
    }

    bool addAllCommands()
    {
        bool ret = true;
        ret &= addCommand("format", "Format file system.", formatFileSystem);
        ret &= addCommand("space", "Display file system space.", spaceFileSystem);
        //ret &= addCommand("mkdir", "Make directory.", mkdirFileSystem);
        //ret &= addCommand("rmdir", "Remove directory.", rmdirFileSystem);
        //ret &= addCommand("l", "List files in directory.", listFileSystem);
        return ret;
    };

    static FileSystem fs;

    private:
    static bool common(Stream *response);

};


