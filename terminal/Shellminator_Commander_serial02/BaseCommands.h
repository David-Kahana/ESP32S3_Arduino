#pragma once
#include "Logger.h"
#include "Commander-API.hpp"
#include "Commander-IO.hpp"

class BaseCommands
{
    public:
    bool addCommand(const char* command, const char* description, void(*func)( char*, Stream *));
    virtual bool addAllCommands() = 0;
    static bool initializeCommander(Stream* debugChannel);
    static Commander* getCommanderPtr();
    //

    protected:
    static uint16_t commandCount;
    static Commander::API_t commands[50];
    //static std::vector<Commander::API_t> commands;
    static Commander commander;
};