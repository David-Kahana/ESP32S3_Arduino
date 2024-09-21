#include "Shellminator.hpp"
#include "Shellminator-IO.hpp"
#include "SimpleCommands.h"

//std::vector<Commander::API_t> BaseCommands::commands;
//Commander BaseCommands::commander;


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
//BaseCommands bc;

void setup()
{
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
    
    // There is an option to attach a debug channel to Commander.
    // It can be handy to find any problems during the initialization
    // phase. In this example we will use Serial for this.
    //commander.attachDebugChannel(&Serial);

    //sc.addAllCommands();
    // At start, Commander does not know anything about our commands.
    // We have to attach the API_tree array from the previous steps
    // to Commander to work properly.
    //commander.attachTree(API_tree);

    // Initialize Commander.
    BaseCommands::initializeCommander(&Serial);
    //commander.init();

    shell.attachCommander(BaseCommands::getCommanderPtr());

    // Initialize shell object.
    shell.begin("arnold");
}

void loop()
{

    shell.update();
}

/// This is an example function for the cat command
void id_func(char *args, Stream *response)
{
    uint32_t chipId = 0;
    for (int i = 0; i < 17; i = i + 8)
    {
        chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
    }
    Logger::log(response, "Chip ID: %d", chipId);
}

/// This is an example function for the dog command
void dog_func(char *args, Stream *response)
{

    response->print("Hello from dog function!\r\n");
}

/// This is an example function for the led command
void led_func(char *args, Stream *response)
{

    // Toggle your LED pin here, if you have on your board
    // digitalWrite( LED_PIN, !digitalRead( LED_PIN ) );
    response->print("LED toggle!\r\n");
}

/// This is an example function for the sum command
void sum_func(char *args, Stream *response)
{

    // These variables will hold the value of the
    // two numbers, that has to be summed.
    int a = 0;
    int b = 0;

    // This variable will hold the result of the
    // argument parser.
    int argResult;

    // This variable will hold the sum result.
    int sum = 0;

    argResult = sscanf(args, "%d %d", &a, &b);

    // We have to check that we parsed successfully  the two
    // numbers from the argument string.
    if (argResult != 2)
    {

        // If we could not parse two numbers, we have an argument problem.
        // We print out the problem to the response channel.
        response->print("Argument error! Two numbers required, separated with a blank space.\r\n");

        // Sadly we have to stop the command execution and return.
        return;
    }

    // Calculate the sum.
    sum = a + b;

    // Print out the result.
    response->print(a);
    response->print(" + ");
    response->print(b);
    response->print(" = ");
    response->println(sum);
}
