#include "BaseCommands.h"

std::vector<Commander::API_t> BaseCommands::commands;
Commander BaseCommands::commander;

bool BaseCommands::addCommand(const char* command, const char* description, void(*func)( char*, Stream *))
{
    commands.push_back(apiElement(command, description, func));
    return true;
};

bool BaseCommands::addCommand(Commander::API_t command)
{
    commands.push_back(command);
    return true;
};

//static 
bool BaseCommands::initializeCommander(Stream* debugChannel)
{
    commander.attachDebugChannel(debugChannel);
    commander.attachTreeFunction(commands.data(), commands.size());
    commander.init();
    return true;
};

//static 
Commander* BaseCommands::getCommanderPtr()
{
    return &commander;
};
