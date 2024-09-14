#include <cstdint>
class FileSystem
{
  public:
  void initFileSystem();
  void formatFileSystem();
  void spaceFileSystem();
  void listDir(const char *dirname, uint8_t levels);
  void makeDir(const char *dirname);
  void removeDir(const char *dirname);

  private:
  bool initialized = false;
  bool formatted = false; 
};
