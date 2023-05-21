/* Copyright (c) 2023, Lucas Mösch
 * All Rights Reserved.
 */
// ----------------------------------------------------------------------------
namespace modm
{

template <typename Uart>
NMEA0183<Uart>::NMEA0183()
{

}

template <typename Uart>
ResumableResult<void>
NMEA0183<Uart>::update()
{
    uint8_t c;

    RF_BEGIN();

    while(uart.read(c)) {
        if (c == '$' || message.size > 81) {
            message.clear();
        }

        message += c;

        if(c == '\r') {
            parse();
            message.clear();
        }
    }

    RF_END();
}

template <class Uart>
void NMEA0183<Uart>::parse()
{

}

template <class Uart>
void NMEA0183<Uart>::parseRMC()
{
}

template <class Uart>
void NMEA0183<Uart>::parseGSA()
{
}

}