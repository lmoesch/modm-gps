/* Copyright (c) 2023, Lucas Mösch
 * All Rights Reserved.
 */
// ----------------------------------------------------------------------------
#include "board/board.hpp"
namespace Beitian 
{

template <class Uart>
BN280<Uart>::BN280()
{
}

template <class Uart>
void BN280<Uart>::getGeoCoordinates(double& latitude, double& longitude)
{
    latitude = this->latitude;
    longitude = this->longitude;
}

template <class Uart>
ResumableResult<void> 
BN280<Uart>::onRMC(RMC rmc)
{
    Board::usb::ioStream << rmc.latitude;

    RF_BEGIN();
    longitude = rmc.longitude;
    latitude = rmc.latitude;

    RF_END();
}

}