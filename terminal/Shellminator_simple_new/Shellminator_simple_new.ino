/*
 * Created on June 8 2024
 *
 * Copyright (c) 2023 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Shellminator project.
 * Modified 2023.05.13
*/
#include "Shellminator.hpp"

Shellminator shell( &Serial );

void setup()
{
    Serial.begin(115200);
    shell.clear(); // Clear the terminal
    shell.begin( "arnold" ); // Initialize shell object.
}

void loop()
{
    shell.update(); // Process the new data.
}