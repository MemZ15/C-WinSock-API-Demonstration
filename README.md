# WinSock API Demonstration

# NetworkHandler (C++ TCP Server Framework)

A lightweight C++ TCP server framework built on Winsock, designed for handling multiple client connections using a threaded accept-and-dispatch architecture.

# Notes
Uses raw Winsock API (no Boost / no wrappers)
Designed for low-level control and extensibility
Thread-per-client model (can be upgraded to thread pool / async model later)
Currently focused on server-side connection handling (no full protocol implementation yet)

WIP
