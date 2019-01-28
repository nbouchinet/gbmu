#ifndef PPU_CLASS_H
# define PPU_CLASS_H

# define PPU_WIDTH 160
# define PPU_HEIGHT 144

#include <iostream>
#include <string>
#include "ScreenOutput.class.h"
#include "Fwd.hpp"

uint8_t ReadMem(uint16_t addr);

class PPU
{
public:
	PPU(ComponentsContainer& components);
	~PPU();

	static int				getPPUNumber(void);
	static void				switchPPUDebug(bool status);

	bool					testBit(uint8_t byte, uint8_t bit_number);
	void					renderScreen();
	void					updateGraphics(int cycles);
	void					updateStatus();
	ScreenOutput			*getDriverScreen() { return (&driverScreen); } // UGO call dis to get screen

private:
	uint16_t				getTileDataAddress(uint8_t tileIdentifier);
	void					setupUsingWindow();
	void					setupBackgroundMemory();
	void					setupTileData();
	bool					isLCDEnabled();
	void					renderScanLine();
	void					setPixelDMG(uint8_t x, uint8_t y, uint8_t value);
	void					renderTiles();
	void					renderSprites();

	ScreenOutput			driverScreen;
	ComponentsContainer&	_components;


	uint8_t					lcdc; // PPU controller register (0xFF41)
	uint8_t					stat; // PPU status register (flags) (0xFF40)
	uint8_t					scrollX;
	uint8_t					scrollY;
	uint8_t					currentScanline;
	uint8_t					windowX;
	uint8_t					windowY;
	uint16_t				backgroundMemory;
	uint16_t				tileDataStart;
	bool					unsignedTileValues;
	bool					usingWindow;

	static int				_nb_PPU;
	static bool				_debug_PPU;
};


#endif
