#include "Commander-API.hpp"
#include "Commander-IO.hpp"
#include "Commander-API-Commands.hpp"

// We have to create the prototype functions for our commands.
// The arguments has to be the same for all command functions.
void id_func(char *args, Stream *response);
void sum_func(char *args, Stream *response);
void led_func(char *args, Stream *response);
void rgb_func(char *args, Stream *response);

class CommandsBasic
{
  public:
  CommandsBasic();
  void init(Stream* debugChannel);
  
  int num = 0;
  Commander commander;
  Commander::API_t API_tree[17] = {
      apiElement("id", "Display chip ID.", id_func),
      apiElement("led", "Toggle the buit-in LED.", led_func),
      apiElement("sum", "This function sums two number from the argument list.", sum_func),
      apiElement("rgb", "RGB led control.", rgb_func),
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
      API_ELEMENT_NOT
  };
};
