#include "Shellminator.hpp"
#include "Shellminator-IO.hpp"
#include "SimpleCommands.h"

Shellminator shell(&Serial);

const char logo[] =

  "   _____ __         ____          _             __            \r\n"
  "  / ___// /_  ___  / / /___ ___  (_)___  ____ _/ /_____  _____\r\n"
  "  \\__ \\/ __ \\/ _ \\/ / / __ `__ \\/ / __ \\/ __ `/ __/ __ \\/ ___/\r\n"
  " ___/ / / / /  __/ / / / / / / / / / / / /_/ / /_/ /_/ / /    \r\n"
  "/____/_/ /_/\\___/_/_/_/ /_/ /_/_/_/ /_/\\__,_/\\__/\\____/_/     \r\n"
  "\r\n\033[0;37m"
  "Visit on GitHub:\033[1;32m https://github.com/dani007200964/Shellminator\r\n\r\n"
  ;

SimpleCommands sc;

void setup()
{
    Serial.begin(115200);
    while (!Serial);
    // Clear the terminal
    shell.clear();
    // Attach the logo.
    shell.attachLogo(logo);
    // Print start message
    Serial.println("Program begin...");
    // Initialize Commander.
    BaseCommands::initializeCommander(&Serial);
    shell.attachCommander(BaseCommands::getCommanderPtr());
    // Initialize shell object.
    shell.begin("arnold");
}

void loop()
{
    shell.update();
}
