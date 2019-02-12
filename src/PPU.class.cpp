#include "PPU.class.h"
#include "Gameboy.hpp"
#include "MemoryBus.hpp"

//------------------------------------------------------------------------------
PPU::PPU(ComponentsContainer& components) : _components(components)
{
	if (_debug_PPU == true)
		std::cout << "[PPU default constructor called]" << std::endl;
	PPU::_nb_PPU++;
	return;
}

//------------------------------------------------------------------------------
PPU::~PPU()
{
	if (_debug_PPU == true)
		std::cout << "[PPU destructor called]" << std::endl;
	PPU::_nb_PPU--;
	return;
}

//==============================================================================
bool				PPU::testBit(uint8_t byte, uint8_t bit_number)
{
	if (_debug_PPU == true)
		std::cout << "testBit " << static_cast<unsigned int>(byte)
			<< " at bit " << static_cast<unsigned int>(bit_number)
			<< " will return";

	if ((byte) & (1 << (bit_number)))
	{
		if (_debug_PPU == true)
			std::cout << " true" << std::endl;
		return (true);
	}
	if (_debug_PPU == true)
		std::cout << " false" << std::endl;
	return (false);
}

//------------------------------------------------------------------------------
bool				PPU::isLCDEnabled()
{
	if (testBit(_components.mem_bus->read<Byte>(0xFF40), 7))
		return (true);
	return (false);
}

//------------------------------------------------------------------------------
void				PPU::setupTileData()
{
	if (testBit(lcdc, 4) == true)
	{
		tileDataStart = 0x8000;
		unsignedTileValues = true;
	}
	else
	{
		tileDataStart = 0x8800;
		unsignedTileValues = false;
	}
}

//------------------------------------------------------------------------------
void				PPU::setupUsingWindow()
{
	if (testBit(lcdc, 5) == true && (windowY <= currentScanline))
		usingWindow = true;	
}

//------------------------------------------------------------------------------
uint16_t			PPU::getTileDataAddress(uint8_t tileIdentifier)
{
	uint8_t		offset = 128;
	uint8_t		tileMemorySize = 16;
	uint16_t	tileDataAddress;

	if (unsignedTileValues == true)
		tileDataAddress = tileDataStart + (tileIdentifier * tileMemorySize);
	else
		tileDataAddress = tileDataStart + ((tileIdentifier + offset) * tileMemorySize);
	return (tileDataAddress);
}

//------------------------------------------------------------------------------
void				PPU::setupBackgroundMemory()
{
	uint8_t			lcdc = _components.mem_bus->read<Byte>(0xFF40);

	if (usingWindow == true)
	{
		if (testBit(lcdc, 3) == true)
			backgroundMemory = 0x9C00;
		else
			backgroundMemory = 0x9800;
	}
	else
	{
		if (testBit(lcdc, 6) == true)
			backgroundMemory = 0x9C00;
		else
			backgroundMemory = 0x9800;
	}
}

//------------------------------------------------------------------------------
void				PPU::setPixelDMG(uint8_t y, uint8_t x, uint8_t colorValue)
{
	if (currentScanline < PPU_HEIGHT)
	{
		switch (colorValue) // only for DMG, will be different for CGB
		{
			case 3 :
				// black
				driverScreen.setRGBA(y, x, 0, 0, 0, 255);
				break;
			case 2 :
				driverScreen.setRGBA(y, x, 119, 119, 119, 255);
				// dark grey
				break;
			case 1 :
				driverScreen.setRGBA(y, x, 204, 204, 204, 255);
				// light grey
				break;
			case 0 :
				driverScreen.setRGBA(y, x, 255, 255, 255, 255);
				// transparent (white)
				break;
		}
	}
}

//------------------------------------------------------------------------------
void				PPU::renderSprites()
{
	uint8_t			ySize = 8;
	uint8_t			spriteAttributesOffset; // offset from the start of the Table in bytes
	uint16_t		spriteAttributesTableStart = 0xFE00;

	if (testBit(lcdc, 2) == true)
		ySize = 16; // extra thicc sprites
	for (int sprite = 0; sprite < 40; sprite++)
	{
		uint8_t		xPos = _components.mem_bus->read<Byte>(spriteAttributesTableStart + spriteAttributesOffset) - 8;
		uint8_t		yPos = _components.mem_bus->read<Byte>(spriteAttributesTableStart + spriteAttributesOffset + 1) - 16;
		uint8_t		tileNumber = _components.mem_bus->read<Byte>(spriteAttributesTableStart + spriteAttributesOffset + 2); // the number of the tile data we have to read<Byte> for pixel values
		uint8_t		spriteAttributes = _components.mem_bus->read<Byte>(spriteAttributesTableStart + spriteAttributesOffset + 3); // for flips and other datas
		bool		xFlip = testBit(spriteAttributes, 5) == true ? true : false;
		bool		yFlip = testBit(spriteAttributes, 6) == true ? true : false;

		spriteAttributesOffset = sprite * 4; // 4 bytes of attributes data per sprite;
		spriteAttributes = _components.mem_bus->read<Byte>(spriteAttributesTableStart + spriteAttributesOffset);

		if (currentScanline >= yPos && (currentScanline < (yPos + ySize))) // does scanline intersects the sprite ?
		{
			int		spriteLine = currentScanline - yPos; // which line of the sprite does the scanline go through ?
			if (yFlip == true)
				spriteLine = (spriteLine - ySize) * (-1);
			uint16_t	tileLineDataAddress = (0x8000 + (tileNumber * 16)) + spriteLine;
			for (int pixel = 0; pixel < 8; pixel++)
			{
				uint8_t		linePixel = pixel;
				uint8_t		data1;
				uint8_t		data2;
				uint8_t		colorValue = 0;

				if (xFlip == true)
					linePixel = (linePixel - 7) * (-1);
				data1 = _components.mem_bus->read<Byte>(tileLineDataAddress);
				data2 = _components.mem_bus->read<Byte>(tileLineDataAddress + 1);
				if (testBit(data1, linePixel) == true)
					colorValue += 2;
				if (testBit(data2, linePixel) == true)
					colorValue += 1;
				setPixelDMG(xPos - scrollX + pixel, currentScanline, colorValue);
			}
		}
	}
}

//------------------------------------------------------------------------------
void				PPU::renderTiles()
{
	lcdc = _components.mem_bus->read<Byte>(0xFF40); // lcdc register
	stat = _components.mem_bus->read<Byte>(0xFF41); // stat register
	scrollX = _components.mem_bus->read<Byte>(0xFF42); // start position of the screen in the area (0-255)
	scrollY = _components.mem_bus->read<Byte>(0xFF43); // same for Y (0-255)
	currentScanline = _components.mem_bus->read<Byte>(0xFF44);
	windowX = _components.mem_bus->read<Byte>(0xFF4A); // start position of the window in the screen (7-166)
	windowY = _components.mem_bus->read<Byte>(0xFF4B) - 7; // same for Y (0-143)
	// 10 lines of vertical blank


	setupUsingWindow();
	setupBackgroundMemory();
	setupTileData();

	uint8_t			yPos = 0;
	uint8_t			xPos = 0;
	uint16_t		tileRow; // which row of pixels in the tile ? (8 rows of 8 pixels per tile)

	if (!usingWindow)
		yPos = scrollY + currentScanline;
	else
		yPos = currentScanline - windowY;

	tileRow = (((uint8_t)(yPos / 8)) * 32); // add that to tiledata (0x9800 or 0x9C00) start address to get real memory address of first tile in the row
	for (int i = 0; 
			i < 160; i++)
	{
		int16_t			tileNumber;
		uint16_t		tileCol;
		uint16_t		tileAddress;
		uint16_t		tileLocation;
		uint8_t			tileLine;
		uint8_t			firstByte;
		uint8_t			secondByte;
		uint8_t			colorValue;

		xPos = scrollX + i;
		if (usingWindow && i >= windowX)
		{
			xPos = i - windowX;
		}
		tileCol = xPos / 8;
		tileAddress = backgroundMemory + tileRow + tileCol;
		if (unsignedTileValues)
			tileNumber = (uint8_t)_components.mem_bus->read<Byte>(tileAddress);
		else
			tileNumber = (int8_t)_components.mem_bus->read<Byte>(tileAddress);

		tileLocation = getTileDataAddress(tileNumber);
		tileLine = ((yPos % 8) * 2); // 16 bits (2 bytes) per 8 pixels
		firstByte = _components.mem_bus->read<Byte>(tileLocation + tileLine);
		secondByte = _components.mem_bus->read<Byte>(tileLocation + tileLine + 1);

		colorValue = 0;
		if (testBit(firstByte, xPos % 8) == true)
			colorValue += 2;
		if (testBit(secondByte, xPos % 8) == true)
			colorValue += 1;

		setPixelDMG(i, currentScanline, colorValue);
	}
}

//------------------------------------------------------------------------------
void				PPU::renderScanLine()
{
	lcdc = _components.mem_bus->read<Byte>(0xFF40);

	if (testBit(lcdc, 0) == true)
		renderTiles();
	if (testBit(lcdc, 1) == true)
		renderSprites();
}

//==============================================================================
void					PPU::switchPPUDebug(bool status) { PPU::_debug_PPU = status; }
int						PPU::getPPUNumber(void) { return (PPU::_nb_PPU); }

//------------------------------------------------------------------------------
int						PPU::_nb_PPU = 0;
bool					PPU::_debug_PPU = false;
