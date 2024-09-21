#include "BaseCommands.h"

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

    bool addAllCommands()
    {
        bool ret = true;
        ret &= addCommand("id", "Show chip ID.", id_func);
        //ret &= addCommand("space", "Display file system space.", spaceFileSystem);
        //ret &= addCommand("mkdir", "Make directory.", mkdirFileSystem);
        //ret &= addCommand("rmdir", "Remove directory.", rmdirFileSystem);
        //ret &= addCommand("l", "List files in directory.", listFileSystem);
        return ret;
    };
};