/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */
 
/*
 * Modified by (February 2014): AESS Estudiants - <aess@aess.upc.es>
 * Function changes:
 *	SPI.begin(mode) --> mode: SPI_MASTER or SPI_SLAVE
 *	SPI.attachInterrupt(function) --> function is the SPI ISR. When a interrupt occurs it will be called. 
 *	This function must take no parameters and return nothing.
 *
 *	Other functions act as the standard library
 */

#ifndef SpiSlave_h
#define SpiSlave_h

#include <Arduino.h>


typedef void (*event_cb_t)(uint8_t byte);

class SPISlave {
public:

    static void begin(uint8_t MOSI, uint8_t SCK, event_cb_t _callback);
    static void end();


//private:
    static uint8_t mosiPin;
    static uint8_t sckPin;
    static event_cb_t callback;

    static uint8_t dataByte;
    static uint8_t pos;

    static void process();
};


#endif
