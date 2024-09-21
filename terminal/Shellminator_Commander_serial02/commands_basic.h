#include "file_system.h"
#include "Commander-API.hpp"
#include "Commander-IO.hpp"
#include "Commander-API-Commands.hpp"

// We have to create the prototype functions for our commands.
// The arguments has to be the same for all command functions.

void sum_func(char *args, Stream *response);

class CommandsBasic
{
  public:
  CommandsBasic();
  void init(Stream* debugChannel);
  void initPSRAM();
  void initFileSystem();
  
  // commands
  static void rgb_func(char *args, Stream *response);
  static void id_func(char *args, Stream *response);
  static void psram_func(char *args, Stream *response);
  static void format_func(char *args, Stream *response);
  static void space_func(char *args, Stream *response);
  static void mkdir_func(char *args, Stream *response);
  static void rmdir_func(char *args, Stream *response);
  static void list_func(char *args, Stream *response);

  // variables
  static CommandsBasic& cbs;
  FileSystem fs;
  Commander commander;
  Commander::API_t API_tree[23] = {
      apiElement("id", "Display chip ID.", id_func),
      apiElement("psram", "Display PSRAM data", psram_func),
      apiElement("sum", "This function sums two number from the argument list.", sum_func),
      apiElement("rgb", "RGB led control.", rgb_func),
      apiElement("format", "Format file system.", format_func),
      apiElement("space", "Display file system space.", space_func),
      apiElement("mkdir", "Make directory.", mkdir_func),
      apiElement("rmdir", "Remove directory.", rmdir_func),
      apiElement("l", "List files in directory.", list_func),
      API_ELEMENT_MILLIS,
      API_ELEMENT_MICROS,
      API_ELEMENT_UPTIME,
      API_ELEMENT_PINMODE,
      API_ELEMENT_DIGITALWRITE,
      API_ELEMENT_DIGITALREAD,
      API_ELEMENT_ANALOGREAD,
      //API_ELEMENT_IPCONFIG,
      //API_ELEMENT_WIFISTAT,
      //API_ELEMENT_WIFISCAN,
      //API_ELEMENT_CONFIGTIME,
      //API_ELEMENT_DATETIME,
      API_ELEMENT_NEOFETCH,
      API_ELEMENT_SIN,
      API_ELEMENT_COS,
      API_ELEMENT_ABS,
      API_ELEMENT_RANDOM,
      API_ELEMENT_NOT,
      API_ELEMENT_REBOOT
  };

  private:
  static bool psRamInitialized;
  
};

static CommandsBasic* cbptr;