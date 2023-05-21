/*
 * Copyright (c) 2023, Lucas Mösch
 * All Rights Reserved.
 */
// ----------------------------------------------------------------------------
#ifndef NMEA0183_DEFINITIONS_HPP
#define NMEA0183_DEFINITIONS_HPP

#include <stdint.h>

struct nmea0183
{
    typedef struct {
        uint32_t time;
        char status;
        double latitude;
        double longitude;
        float speed;
        float course;
        uint32_t date;
        float variation;
        char hemisphere;
        uint8_t checksum;
    } RMC; 

    typedef struct {
        char mode1;
        char mode2;
        uint8_t satId[12];
        float pdop;
        float hdop;
        float vdop;
    } GSA;
};

#endif