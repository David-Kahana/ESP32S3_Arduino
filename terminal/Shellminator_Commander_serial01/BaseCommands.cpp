#include "BaseCommands.h"

bool BaseCommands::addCommand(const char* command, const char* description, void(*function)( char*, Stream *))
{
    commands.push_back(apiElement(command, description, function));
    return true;
};