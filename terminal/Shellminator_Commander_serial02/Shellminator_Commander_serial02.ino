#include "Shellminator.hpp"
#include "Shellminator-IO.hpp"
#include "file_system.h"
//#include "commands_basic.h"

// Create a Shellminator object, and initialize it to use Serial
// If we use Commander, we don't need an execution function,
// because Shellminator internally manages that.
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

// We have to create an object from Commander class.
//CommandsBasic cb;
FileSystemInterface fsi;

void setup()
{
    // initialize Serial with 115200 baudrate.
    Serial.begin(115200);
    // If you using Atmega32U4, the code will wait, until
    // you open the serial port.
    while (!Serial);
    // Clear the terminal
    shell.clear();
    // Attach the logo.
    shell.attachLogo(logo);
    // Print start message
    Serial.println("Program begin...");
    fsi.initialize();
    fsi.addAllCommands();
    BaseCommands::initializeCommander(&Serial);

    
    //cb.init(&Serial);
    //shell.attachCommander(&cb.commander);
    shell.attachCommander(BaseCommands::getCommanderPtr());
    // psram
    //cb.initPSRAM();
    // file system
    //cb.initFileSystem();
    // Initialize shell object.
    shell.begin("arnold");
}

void loop()
{
    shell.update();
}

