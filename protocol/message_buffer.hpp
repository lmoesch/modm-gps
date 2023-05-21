/*
 * Copyright (c) 2023, Lucas Mösch
 * All Rights Reserved.
 */
// ----------------------------------------------------------------------------
#ifndef MESSAGE_BUFFER_HPP
#define MESSAGE_BUFFER_HPP

#include <cstddef>
#include <cstring>

template<uint8_t N>
class MessageBuffer
{
public:
    MessageBuffer();

    void
    clear();

    MessageBuffer& 
    operator+=(const char c);

    MessageBuffer& 
    operator+=(const char* str);

    uint8_t
    maxSize();

private:
    char data[N + 1];
    uint8_t size;
};

#include "message_buffer_impl.hpp"

#endif