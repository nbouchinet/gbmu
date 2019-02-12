#pragma once
#ifndef FWD_HPP
#define FWD_HPP

#include <cstdint>

using Byte = uint8_t;
using Word = uint16_t;

class MemoryBus;
class IReadWrite;
class Core;
class Cartridge;
class InterruptController;
class Timer;
class LCDRegisters;
class Gameboy;
struct ComponentsContainer;


#endif // FWD_HPP
