#include "MemoryBus.hpp"
#include <iostream>

MemoryBus::MemoryBus(Cartridge *c, InterruptController *ic)
	: cartridge(c), interrupt_controller(ic) {
}
