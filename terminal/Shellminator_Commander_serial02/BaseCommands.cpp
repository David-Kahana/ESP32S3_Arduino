#include "BaseCommands.h"

uint16_t BaseCommands::commandCount = 0;

bool BaseCommands::addCommand(const char* command, const char* description, void(*function)( char*, Stream *))
{
    //commands.push_back(apiElement(command, description, function));
    commands[commandCount] = apiElement(command, description, function);
    commandCount++;
    return true;
};

bool BaseCommands::initializeCommander(Stream* debugChannel)
{
    commander.attachDebugChannel(debugChannel);
    //commander.attachTreeFunction(commands.data(), commands.size());
    commander.attachTreeFunction(commands, commandCount);
    commander.init();
    return true;
};

Commander* BaseCommands::getCommanderPtr()
{
    return &commander;
}