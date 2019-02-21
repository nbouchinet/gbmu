#include "Bios.hpp"

std::vector <Byte>Bios::dump_logo()
{
	std::vector	<Byte>cartridge_nintendo_logo(47);
	int i, j;

	for (i = 0, j = 0x104; i <= 47; ++i, ++j) {
		cartridge_nintendo_logo[i] = _components.cartridge->read(j);
	}
	return cartridge_nintendo_logo;
}

void Bios::compare_logo()
{
	std::vector	<Byte>cartridge_nintendo_logo;

	cartridge_nintendo_logo = dump_logo();
	if (!equal(_nintendo_logo.begin(), _nintendo_logo.end(), cartridge_nintendo_logo.begin())) {
		throw BadLogo();
	}
}
