#include "BaseCommands.h"
#include "Commander-API-Commands.hpp"

class SimpleCommands : public BaseCommands
{
    public:
    SimpleCommands()
    {
        addAllCommands();
    };
    
    static void id_func(char *args, Stream *response)
    {
        uint32_t chipId = 0;
        for (int i = 0; i < 17; i = i + 8)
        {
            chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
        }
        Logger::log(response, "Chip ID: %d", chipId);
    };

    bool addAllCommands() override 
    {
        bool ret = true;
        ret &= addCommand("id", "Show chip ID.", id_func);
        ret &= addCommand(API_ELEMENT_MILLIS);
        ret &= addCommand(API_ELEMENT_MICROS);
        ret &= addCommand(API_ELEMENT_UPTIME);
        ret &= addCommand(API_ELEMENT_PINMODE);
        ret &= addCommand(API_ELEMENT_DIGITALWRITE);
        ret &= addCommand(API_ELEMENT_DIGITALREAD);
        ret &= addCommand(API_ELEMENT_NEOFETCH);
        ret &= addCommand(API_ELEMENT_REBOOT);
     
      // //API_ELEMENT_IPCONFIG,
      // //API_ELEMENT_WIFISTAT,
      // //API_ELEMENT_WIFISCAN,
      // //API_ELEMENT_CONFIGTIME,
      // //API_ELEMENT_DATETIME,
      // API_ELEMENT_SIN,
      // API_ELEMENT_COS,
      // API_ELEMENT_ABS,
      // API_ELEMENT_RANDOM,
      // API_ELEMENT_NOT,

        return ret;
    };
};