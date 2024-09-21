#include <stdlib.h>
#include <cstdio>
#include "esp32-hal-psram.h"
#include "commands_basic.h"

bool CommandsBasic::psRamInitialized = false;

CommandsBasic::CommandsBasic()
{
}

void CommandsBasic::init(Stream *debugChannel)
{
    Commander::API_t* apiFuncs;
    commander.attachDebugChannel(debugChannel);
    commander.attachTree(API_tree);
    commander.init();
    cbptr = this;
}

void CommandsBasic::initPSRAM()
{
    psRamInitialized = psramInit();
    if (psRamInitialized)
    {
        Serial.printf("PSRAM is correctly initialized\r\n");
        Serial.printf("PSRAM Size available (bytes): %d\r\n", ESP.getFreePsram());
    }
    else
    {
        Serial.printf("PSRAM not available\r\n");
    }
    //ESP.ps_calloc(size_t n, size_t size)
    //ESP.ps_malloc(size_t size)
    //ESP.ps_realloc(void *ptr, size_t size)
    //free(void *)
}

void CommandsBasic::initFileSystem()
{
    fs.initFileSystem();
}

void CommandsBasic::format_func(char *args, Stream *response)
{
    response->printf("Formatting file system\r\n");
    cbptr->fs.formatFileSystem();
}

void CommandsBasic::space_func(char *args, Stream *response)
{
    cbptr->fs.spaceFileSystem();
}

void CommandsBasic::mkdir_func(char *args, Stream *response)
{
    int argResult;
    char dirName[64];
    memset(dirName, 0, 64);
    argResult = sscanf(args, "%s", dirName);
    // We have to check that we parsed successfully  the three
    // numbers from the argument string.
    if (argResult != 1)
    {
        // If we could not parse three numbers, we have an argument problem.
        // We print out the problem to the response channel.
        response->print("Argument error! one string required (no spaces).\r\n");
        // Sadly we have to stop the command execution and return.
        return;
    }
    cbptr->fs.makeDir(dirName);
}

void CommandsBasic::rmdir_func(char *args, Stream *response)
{
    int argResult;
    char dirName[64];
    memset(dirName, 0, 64);
    argResult = sscanf(args, "%s", dirName);
    // We have to check that we parsed successfully  the three
    // numbers from the argument string.
    if (argResult != 1)
    {
        // If we could not parse three numbers, we have an argument problem.
        // We print out the problem to the response channel.
        response->print("Argument error! one string required (no spaces).\r\n");
        // Sadly we have to stop the command execution and return.
        return;
    }
    cbptr->fs.removeDir(dirName);
}

void CommandsBasic::list_func(char *args, Stream *response)
{
    int argResult;
    char dirName[64];
    memset(dirName, 0, 64);
    argResult = sscanf(args, "%s", dirName);
    // We have to check that we parsed successfully  the three
    // numbers from the argument string.
    if (argResult != 1)
    {
        // If we could not parse three numbers, we have an argument problem.
        // We print out the problem to the response channel.
        response->print("Argument error! one string required (no spaces).\r\n");
        // Sadly we have to stop the command execution and return.
        return;
    }
    cbptr->fs.listDir(dirName, 4);
}

void CommandsBasic::id_func(char *args, Stream *response)
{
    uint32_t chipId = 0;
    for (int i = 0; i < 17; i = i + 8)
    {
        chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
    }
    response->printf("Chip ID: %d\r\n", chipId);
}

void led_func(char *args, Stream *response)
{

    // Toggle your LED pin here, if you have on your board
    // digitalWrite( LED_PIN, !digitalRead( LED_PIN ) );
    response->print("LED toggle!\r\n");
}

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

void CommandsBasic::rgb_func(char *args, Stream *response)
{
    int r = 0;
    int g = 0;
    int b = 0;
    // argument parser.
    int argResult;
    argResult = sscanf(args, "%d %d %d", &r, &g, &b);
    // We have to check that we parsed successfully  the three
    // numbers from the argument string.
    if (argResult != 3)
    {
        // If we could not parse three numbers, we have an argument problem.
        // We print out the problem to the response channel.
        response->print("Argument error! 3 numbers required, separated with a blank space.\r\n");
        // Sadly we have to stop the command execution and return.
        return;
    }
    neopixelWrite(RGB_BUILTIN, r, g, b);

    // Print out the result.
    response->printf("R = %d, G = %d, B = %d \033[38;5;206;48;5;57m\r\n", r, g, b);
}

void CommandsBasic::psram_func(char *args, Stream *response)
{
    response->printf("Total heap: %d\r\n", ESP.getHeapSize());
    response->printf("Free heap: %d\r\n", ESP.getFreeHeap());
    if (psRamInitialized)
    {
        response->printf("Total PSRAM: %d\r\n", ESP.getPsramSize());
        response->printf("Free PSRAM: %d\r\n", ESP.getFreePsram());
    }
    else
    {
        Serial.printf("PSRAM not available\r\n");
    }
}