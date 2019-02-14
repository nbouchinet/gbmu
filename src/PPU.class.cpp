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
void				PPU::setupSpriteAddressStart()
{
	_spriteDataStart = 0x8000;
	_spriteSize = 8;
	if (testBit(_lcdc, 2) == true)
		_spriteSize = 16;
}

//------------------------------------------------------------------------------
void				PPU::setupWindow()
{
	if (testBit(_lcdc, 5) == true && (_windowY <= _currentScanline))
		_windowingOn = true;

	if (testBit(_lcdc, 6) == true)
		_windowAttrStart = 0x9C00;
	else
		_windowAttrStart = 0x9800;
}

//------------------------------------------------------------------------------
void				PPU::setupBackgroundMemoryStart()
{
	if (testBit(_lcdc, 4) == true)
	{
		_backgroundDataStart = 0x8000;
		_unsignedTileValues = true;
	}
	else
	{
		_backgroundDataStart = 0x8800;
		_unsignedTileValues = false;
	}

	if (testBit(_lcdc, 3) == true)
		_backgroundAttrStart = 0x9C00;
	else
		_backgroundAttrStart = 0x9800;
}

//------------------------------------------------------------------------------
uint16_t			PPU::getTileDataAddress(uint8_t tileIdentifier)
{
	uint8_t		offset = 128;
	uint8_t		tileMemorySize = 16;
	uint16_t	tileDataAddress;

	if (_unsignedTileValues == true)
		tileDataAddress = _backgroundDataStart + (tileIdentifier * tileMemorySize);
	else
		tileDataAddress = _backgroundDataStart + ((tileIdentifier + offset) * tileMemorySize);
	return (tileDataAddress);
}

//------------------------------------------------------------------------------
void				PPU::setPixelDMG(uint8_t y, uint8_t x, uint8_t colorValue)
{
	if (_currentScanline < LCD_HEIGHT && y < LCD_HEIGHT && x < LCD_WIDTH)
	{
		switch (colorValue) // only for DMG, will be different for CGB
		{
			case 3 :
				// black
				_driverScreen.setRGBA(y, x, 0, 0, 0, 255);
				break;
			case 2 :
				_driverScreen.setRGBA(y, x, 119, 119, 119, 255);
				// dark grey
				break;
			case 1 :
				_driverScreen.setRGBA(y, x, 204, 204, 204, 255);
				// light grey
				break;
			case 0 :
				_driverScreen.setRGBA(y, x, 255, 255, 255, 255);
				// transparent (white)
				break;
		}
	}
}

//------------------------------------------------------------------------------
void				PPU::getSpritesForLine() // takes up to MAX_SPRITE_PER_LINE sprites and loads attributes in _spritesLine tab for use later in renderSprites()
{
	uint16_t		spriteAttributesOffset; // offset from the start of the Table in bytes
	uint16_t		spriteAttributesTableStart = 0xFE00; // start of OAM ram for sprites
	uint8_t			yPosTmp;
	uint8_t			xPosTmp;

	_nbSprites = 0;
	for (int sprite = 0; sprite < 40; sprite++)
	{
		spriteAttributesOffset = sprite * 4; // 4 bytes of attributes data per sprite;
		yPosTmp = _components.mem_bus->read<Byte>(spriteAttributesTableStart + spriteAttributesOffset); // in screen !!
		xPosTmp = _components.mem_bus->read<Byte>(spriteAttributesTableStart + spriteAttributesOffset + 1); // in screen !!
		if (_currentScanline >= yPosTmp && (_currentScanline < (yPosTmp + _spriteSize)) && xPosTmp != 0) // IMPORTANT : _spriteSize here might be a flat 16 instead !
		{
			_spritesLine[_nbSprite].yPos = yPosTmp // -16 !!!!
			_spritesLine[_nbSprite].xPos = xPosTmp // -8 !!!!
			_spritesLine[_nbSprite].tileNumber = _components.mem_bus->read<Byte>(spriteAttributesTableStart + spriteAttributesOffset + 2); // the number of the tile data we have to read<Byte> for pixel values
			_spritesLine[_nbSprite].flags = _components.mem_bus->read<Byte>(spriteAttributesTableStart + spriteAttributesOffset + 3); // for flips and other datas
			_nbSprites++;
		}
		if (_nbSprites >= MAX_SPRITE_PER_LINE) // this allows to only take up to 10 sprites by default
			return ;
	}
}

//------------------------------------------------------------------------------
void				PPU::renderSprites()
{
	for (int sprite = 0; sprite < _nbSprites; sprite++)
	{
		bool		xFlip = testBit(spriteAttributes, 5) == true ? true : false;
		bool		yFlip = testBit(spriteAttributes, 6) == true ? true : false;


		int		spriteLine = _currentScanline - yPos; // which line of the sprite does the scanline go through ?
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
			setPixelDMG(_currentScanline, xPos - _scrollX + pixel, colorValue);
		}
	}
}

//------------------------------------------------------------------------------
void				PPU::finishLineBackgroundAsWindow()
{
	for (int pix = _windowX; x < LCD_WIDTH; x++)
	{
		uint8_t		yPos = _currentScanline - _windowY;
		
	}
}

//------------------------------------------------------------------------------
void				PPU::renderTiles()
{
	uint8_t			yPos = _currentScanline + _scrollY;
	uint8_t			xPos = _scrollX;
	uint16_t		tileRow; // which row of pixels in the tile ? (8 rows of 8 pixels per tile)


	tileRow = (((uint8_t)(yPos / 8)) * 32); // add that to tiledata (0x9800 or 0x9C00) start address to get real memory address of first tile in the row
	for (int i = 0; i < 160; i++)
	{
		if (_windowingOn == true && i >= _windowX && _currentScanline >= windowY) // are we in the window and is it enabled ?
		{
			finishLineBackgroundAsWindow();
			return ;
		}

		int16_t			tileNumber;
		uint16_t		tileCol;
		uint16_t		tileAddress;
		uint16_t		tileLocation;
		uint8_t			tileLine;
		uint8_t			firstByte;
		uint8_t			secondByte;
		uint8_t			colorValue;

		xPos = _scrollX + i;
		if (_windowingOn && i >= _windowX)
		{
			xPos = i - _windowX;
		}
		tileCol = xPos / 8;
		tileAddress = _backgroundDataStart + tileRow + tileCol;
		if (_unsignedTileValues)
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

		setPixelDMG(_currentScanline, i, colorValue);
	}
}

//------------------------------------------------------------------------------
void				PPU::renderScanLine()
{
	_lcdc = _components.mem_bus->read<Byte>(0xFF40); // lcdc register
	_stat = _components.mem_bus->read<Byte>(0xFF41); // stat register
	_scrollX = _components.mem_bus->read<Byte>(0xFF42); // start position of the screen in the area (0-255)
	_scrollY = _components.mem_bus->read<Byte>(0xFF43); // same for Y (0-255)
	_currentScanline = _components.mem_bus->read<Byte>(0xFF44);
	_windowX = _components.mem_bus->read<Byte>(0xFF4A); // start position of the window in the screen (7-166)
	_windowY = _components.mem_bus->read<Byte>(0xFF4B) - 7; // same for Y (0-143)

	// 10 lines of vertical blank
	setupWindow();
	setupBackgroundMemoryStart();
	setupSpriteAddressStart();

	if (testBit(_lcdc, 0) == true)
		renderTiles();
	if (testBit(_lcdc, 1) == true)
		renderSprites();
}

//==============================================================================
void					PPU::switchPPUDebug(bool status) { PPU::_debug_PPU = status; }
int						PPU::getPPUNumber(void) { return (PPU::_nb_PPU); }

//------------------------------------------------------------------------------
int						PPU::_nb_PPU = 0;
bool					PPU::_debug_PPU = false;
