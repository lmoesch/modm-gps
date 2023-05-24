/* Copyright (c) 2023, Lucas Mösch
 * All Rights Reserved.
 */
// ----------------------------------------------------------------------------
namespace Beitian 
{

template <class Uart>
BN280<Uart>::BN280()
{
}

template <class Uart>
ResumableResult<void> 
BN280<Uart>::onRMC(NMEA0183<Uart>::RMC rmc)
{
    RF_BEGIN();

    longitude = rmc.longitude;
    latitude = rmc.latitude;

    RF_END();
}

}