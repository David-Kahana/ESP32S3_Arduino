#include "commands_basic.h"

CommandsBasic::CommandsBasic()
{
}

void CommandsBasic::init(Stream* debugChannel)
{
  commander.attachDebugChannel(debugChannel);
  commander.attachTree(API_tree);
  commander.init();
}

/// This is an example function for the cat command
void id_func(char *args, Stream *response)
{
    uint32_t chipId = 0;
    for (int i = 0; i < 17; i = i + 8)
    {
        chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
    }
    response->printf("Chip ID: %d\r\n",chipId);
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

void rgb_func(char *args, Stream *response)
{
    int r = 0;
    int g = 0;
    int b = 0;
    // This variable will hold the result of the
    // argument parser.
    int argResult;
    // This variable will hold the sum result.
    //int sum = 0;
    argResult = sscanf(args, "%d %d %d", &r, &g, &b);
    // We have to check that we parsed successfully  the two
    // numbers from the argument string.
    if (argResult != 3)
    {
        // If we could not parse two numbers, we have an argument problem.
        // We print out the problem to the response channel.
        response->print("Argument error! 3 numbers required, separated with a blank space.\r\n");

        // Sadly we have to stop the command execution and return.
        return;
    }
    neopixelWrite(RGB_BUILTIN, r, g, b);
    
    // Print out the result.
    response->printf("R = %d, G = %d, B = %d\n", r, g, b);
}