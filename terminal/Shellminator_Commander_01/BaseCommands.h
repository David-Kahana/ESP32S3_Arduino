#pragma once
#include "Logger.h"
#include "Commander-API.hpp"
#include "Commander-IO.hpp"

class BaseCommands
{
    public:

    static void id_func(char *args, Stream *response)
    {
        uint32_t chipId = 0;
        for (int i = 0; i < 17; i = i + 8)
        {
            chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
        }
        Logger::log(response, "Chip ID: %d", chipId);
    }

    bool addCommand(const char* command, const char* description, void(*func)( char*, Stream *))
    {
        commands.push_back(apiElement(command, description, func));
        return true;
    };

    virtual bool addAllCommands() = 0;
    // {
    //     bool ret = true;
    //     ret &= addCommand("id", "Show chip ID.", id_func);
    //     //ret &= addCommand("space", "Display file system space.", spaceFileSystem);
    //     //ret &= addCommand("mkdir", "Make directory.", mkdirFileSystem);
    //     //ret &= addCommand("rmdir", "Remove directory.", rmdirFileSystem);
    //     //ret &= addCommand("l", "List files in directory.", listFileSystem);
    //     return ret;
    // };

    static bool initializeCommander(Stream* debugChannel)
    {
        commander.attachDebugChannel(&Serial);
        commander.attachTreeFunction(commands.data(), commands.size());
        commander.init();
        return true;
    }

    static Commander* getCommanderPtr()
    {
        return &commander;
    }
    //

    public:
    static std::vector<Commander::API_t> commands;
    static Commander commander;
};