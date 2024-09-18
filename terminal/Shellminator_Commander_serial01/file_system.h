#include <cstdint>
#include <Stream.h>

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

class FileSystemInterface
{
    public:
    static void formatFileSystem(char *args, Stream *response);
    static void spaceFileSystem(char *args, Stream *response);
    static void mkdirFileSystem(char *args, Stream *response);
    static void rmdirFileSystem(char *args, Stream *response);
    static void listFileSystem(char *args, Stream *response);

    static FileSystem* fs;

    private:
    static bool common(Stream *response);

};


