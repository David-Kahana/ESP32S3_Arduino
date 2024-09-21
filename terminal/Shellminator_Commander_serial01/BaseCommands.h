#pragma once
#include "Logger.h"
#include "Commander-API.hpp"
#include "Commander-IO.hpp"

class BaseCommands
{
    public:
    bool addCommand(const char* command, const char* description, void(*func)( char*, Stream *));

    //

    protected:
    static std::vector<Commander::API_t> commands;
};