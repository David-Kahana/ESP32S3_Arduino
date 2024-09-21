#pragma once
#include "Logger.h"
#include "Commander-API.hpp"
#include "Commander-IO.hpp"

class BaseCommands
{
    public:
    bool addCommand(const char* command, const char* description, void(*func)( char*, Stream *));
    bool addCommand(Commander::API_t command);
    virtual bool addAllCommands() = 0;
    static bool initializeCommander(Stream* debugChannel);
    static Commander* getCommanderPtr();

    protected:
    static std::vector<Commander::API_t> commands;
    static Commander commander;
};