#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")


#include <iphlpapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <thread>
#include <unordered_map>
#include <atomic>
#include <iostream>

#pragma pack(push, 1)
struct PacketHeader
{
    uint16_t opcode;  
    uint32_t length;  
};
#pragma pack(pop)