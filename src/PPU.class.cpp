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
		_windowChrAttrStart = 0x9C00;
	else
		_windowChrAttrStart = 0x9800;
}

//------------------------------------------------------------------------------
void				PPU::setupBackgroundMemoryStart()
{
	if (testBit(_lcdc, 4) == true)
	{
		_backgroundDataStart = 0x8000;
		_unsignedTileNumbers = true;
	}
	else
	{
		_backgroundDataStart = 0x8800;
		_unsignedTileNumbers = false;
	}

	if (testBit(_lcdc, 3) == true)
		_backgroundChrAttrStart = 0x9C00;
	else
		_backgroundChrAttrStart = 0x9800;
}

//------------------------------------------------------------------------------
uint16_t			PPU::getTileDataAddress(uint8_t tileIdentifier)
{
	uint8_t		offset = 128;
	uint8_t		tileMemorySize = 16;
	uint16_t	tileDataAddress;

	if (_unsignedTileNumbers == true)
		tileDataAddress = _backgroundDataStart + (tileIdentifier * tileMemorySize);
	else
		tileDataAddress = _backgroundDataStart + ((tileIdentifier + offset) * tileMemorySize);
	return (tileDataAddress);
}

//------------------------------------------------------------------------------
void				PPU::setPixelDMG(uint8_t y, uint8_t x, uint8_t colorID)
{
	if (_currentScanline < LCD_HEIGHT && y < LCD_HEIGHT && x < LCD_WIDTH)
	{
		switch (colorID) // only for DMG, will be different for CGB
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
std::cout << ">>getSpritesForLine called\n" << std::endl;
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
			_spritesLine[_nbSprites].yPos = yPosTmp; // -16 !!!!
			_spritesLine[_nbSprites].xPos = xPosTmp; // -8 !!!!
			_spritesLine[_nbSprites].tileNumber = _components.mem_bus->read<Byte>(spriteAttributesTableStart + spriteAttributesOffset + 2); // the number of the tile data we have to read<Byte> for pixel values
			_spritesLine[_nbSprites].flags = _components.mem_bus->read<Byte>(spriteAttributesTableStart + spriteAttributesOffset + 3); // for flips and other datas
			_nbSprites++;
		}
		if (_nbSprites >= MAX_SPRITE_PER_LINE) // this allows to only take up to 10 sprites by default
			return ;
	}
}

//------------------------------------------------------------------------------
void				PPU::blendPixels(t_pixelSegment &holder, t_pixelSegment &contender)
{
	t_pixelSegment	*pix;
	t_pixelSegment	*pox;

	pix = &holder;
	pox = &contender;
}

//------------------------------------------------------------------------------
void				PPU::renderSprites()
{
std::cout << ">>renderSprites called\n" << std::endl;
	getSpritesForLine();
	for (int sprite = _nbSprites - 1; sprite >= 0; sprite--) // up to 10 sprites on the line
	{
		bool		xFlip = testBit(_spritesLine[sprite].flags, 5) == true ? true : false;
		bool		yFlip = testBit(_spritesLine[sprite].flags, 6) == true ? true : false;

		int		spriteLine = _currentScanline - _spritesLine[sprite].yPos; // which line of the sprite does the scanline go through ?
		if (yFlip == true)
			spriteLine = (spriteLine - _spriteSize) * (-1);
		uint16_t	tileLineDataAddress = (_spriteDataStart + (_spritesLine[sprite].tileNumber * 16)) + spriteLine;

		uint8_t data1 = _components.mem_bus->read<Byte>(tileLineDataAddress);
		uint8_t data2 = _components.mem_bus->read<Byte>(tileLineDataAddress + 1);

		for (int pixel = 0; pixel < 8; pixel++)
		{
			uint8_t		linePixel = pixel;
			uint8_t		colorID = 0;

			if (xFlip == true)
				linePixel = (linePixel - 7) * (-1);
			if (testBit(data1, linePixel) == true)
				colorID += 2;
			if (testBit(data2, linePixel) == true)
				colorID += 1;
			
			setPixelDMG(_currentScanline, _spritesLine[sprite].xPos - _scrollX + pixel, colorID);
		}
	}
}

//------------------------------------------------------------------------------
void				PPU::renderTiles()
{
std::cout << ">>renderTiles called\n" << std::endl;
	uint8_t			xPos;
	uint8_t			yPos;
	bool			boiItsaWindow = false;

	for (int i = 0; i < 160; i++)
	{
		if (_windowingOn == true && i >= _windowX - 7 && _currentScanline >= _windowY) // are we in the window and is it enabled ?
			boiItsaWindow = true;

		int16_t			tileNumber;
		uint16_t		tileCol;
		uint16_t		tileRow; // which row of pixels in the tile ? (8 rows of 8 pixels per tile) position in the 256 * 256 area
		uint16_t		tileLine;
		uint16_t		tileNumberAddress;
		uint16_t		tileLocation;

		if (boiItsaWindow == true)
		{
			xPos = i - _windowX - 7;
			yPos = _currentScanline - _windowY;
		}
		else
		{
			xPos = _scrollX + i;
			yPos = _scrollY + _currentScanline;
		}

		tileRow = (((uint8_t)(yPos / 8)) * 32);								// (0-992) add that to tiledata (0x9800 or 0x9C00) start address to get real memory address of first tile in the row
		tileCol = xPos / 8;													// (0-32) 

		if (boiItsaWindow == true)
			tileNumberAddress = _windowChrAttrStart + tileRow + tileCol;	// 1 byte per tileData, just the tile number
		tileCol = xPos / 8;
		tileNumberAddress = _backgroundDataStart + tileRow + tileCol;
		if (_unsignedTileNumbers)
		{
			tileNumber = (uint8_t)_components.mem_bus->read<Byte>(tileNumberAddress);
			// in CBG probably get the ATTR stuff from bank 1;
		}
		else
		{
			tileNumber = (int8_t)_components.mem_bus->read<Byte>(tileNumberAddress);
			// in CBG probably get the ATTR stuff from bank 1;
		}

		tileLocation = getTileDataAddress(tileNumber);
		tileLine = ((yPos % 8) * 2);										// 16 bits (2 bytes) per 8 pixels

		uint8_t firstByte = _components.mem_bus->read<Byte>(tileLocation + tileLine);
		uint8_t secondByte = _components.mem_bus->read<Byte>(tileLocation + tileLine + 1);

		// some shenanigans for color palette here;

		uint8_t colorID = 0;
		if (testBit(firstByte, xPos % 8) == true)
			colorID += 2;
		if (testBit(secondByte, xPos % 8) == true)
			colorID += 1;
		//put in pipeline
		_pixelPipeline[i].value = colorID;
		_pixelPipeline[i].isSprite = false;
		setPixelDMG(_currentScanline, i, colorID);
	}
}

//------------------------------------------------------------------------------
void				PPU::sendPixelPipeline()
{
	int mode = 0;

	for (int i = 0; i < LCD_WIDTH; i++)
	{
		switch (mode /* DMG, CGB etc */)
		{
			case 0:
				break ;
			case 1:
				break ;
			case 2:
				break ;
		}
//		setPixelDMG(_currentScanline, i, colorValue);
	}
}

//------------------------------------------------------------------------------
void				PPU::renderScanLine()
{
std::cout << ">>renderScanLine called\n" << std::endl;
	_lcdc = _components.mem_bus->read<Byte>(0xFF40); // lcdc register
	_stat = _components.mem_bus->read<Byte>(0xFF41); // stat register
	_scrollX = _components.mem_bus->read<Byte>(0xFF42); // start position of the screen in the area (0-255)
	_scrollY = _components.mem_bus->read<Byte>(0xFF43); // same for Y (0-255)
	_currentScanline = _components.mem_bus->read<Byte>(0xFF44);
	_windowX = _components.mem_bus->read<Byte>(0xFF4A); // start position of the window in the screen (7-166)
	_windowY = _components.mem_bus->read<Byte>(0xFF4B) - 7; // same for Y (0-143)

	setupWindow();
	setupBackgroundMemoryStart();
	setupSpriteAddressStart();

	if (testBit(_lcdc, 0) == true)
		renderTiles();
	if (testBit(_lcdc, 1) == true)
		renderSprites();
	sendPixelPipeline();
}

//==============================================================================
void					PPU::switchPPUDebug(bool status) { PPU::_debug_PPU = status; }
int						PPU::getPPUNumber(void) { return (PPU::_nb_PPU); }

//------------------------------------------------------------------------------
int						PPU::_nb_PPU = 0;
bool					PPU::_debug_PPU = false;
