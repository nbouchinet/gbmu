#include "PPU.class.h"
#include "Gameboy.hpp"
#include "MemoryBus.hpp"

//------------------------------------------------------------------------------
PPU::PPU(ComponentsContainer& components) : _components(components)
{
	if (_debug_PPU == true)
		std::cerr << "[PPU default constructor called]" << std::endl;
	PPU::_nb_PPU++;
	return;
}

//------------------------------------------------------------------------------
PPU::~PPU()
{
	if (_debug_PPU == true)
		std::cerr << "[PPU destructor called]" << std::endl;
	PPU::_nb_PPU--;
	return;
}

//==============================================================================
bool				PPU::testBit(uint32_t byte, uint8_t bit_number)
{
	if (_debug_PPU == true)
		std::cerr << "testBit " << static_cast<unsigned int>(byte)
			<< " at bit " << static_cast<unsigned int>(bit_number)
			<< " will return";

	if ((byte) & (1 << (bit_number)))
	{
		if (_debug_PPU == true)
			std::cerr << " true" << std::endl;
		return (true);
	}
	if (_debug_PPU == true)
		std::cerr << " false" << std::endl;
	return (false);
}

//------------------------------------------------------------------------------
uint16_t				PPU::colorPaletteArrayCaseWrapper(uint8_t specifier)
{
	uint8_t				paletteNumber;
	uint8_t				paletteDataNumber;
	uint16_t			ret;

	paletteNumber = extractValue(specifier, 3, 5);
	paletteDataNumber = extractValue(specifier, 1, 2);

	ret = 0; /* start address of sprites palettes */
	ret	+= (paletteNumber * 4) + (paletteDataNumber);

	return (ret);
}

//------------------------------------------------------------------------------
void				PPU::write(Word address, Byte value)
{
	Byte			*paletteAddr;
	uint8_t			array_case;
	uint8_t			hilo;

	paletteAddr = 0;
	array_case = 0;
	hilo = 0;

	switch (address)
	{
		case 0xFF40:
			_lcdc = value;
			break;
		case 0xFF41:
			_stat = value;
			break;
		case 0xFF42:
			_scy = value;
			break;
		case 0xFF43:
			_scx = value;
			break;
		case 0xFF44:
			_ly = value;
			break;
		case 0xFF45:
			_lyc = value;
			break;
		case 0xFF46:
			_dma = value;
			break;
		case 0xFF47:
			_bgp = value;
			break;
		case 0xFF48:
			_obp0 = value;
			break;
		case 0xFF49:
			_obp1 = value;
			break;
		case 0xFF4A:
			_wy = value;
			break;
		case 0xFF4B:
			_wx = value;
			break;
		case 0xFF51:
			_hdma1 = value;
			break;
		case 0xFF52:
			_hdma2 = value;
			break;
		case 0xFF53:
			_hdma3 = value;
			break;
		case 0xFF54:
			_hdma4 = value;
			break;
		case 0xFF55:
			_hdma5 = value;
			break;
		case 0xFF68:
			_bcps = value;
			break;
		case 0xFF69:
			_bcpd = value;
//			array_case = colorPaletteArrayCaseWrapper(_bcps);
//			hilo = array_case % 2;
//			array_case -= hilo;
//			paletteAddr = (_backgroundColorPalette[array_case / 8][array_case % 4]) + hilo;
//			*paletteAddr = value;
//			_backgroundColorPalette_translated[array_case / 8][array_case % 4] = translateCGBColorValue(_backgroundColorPalette[array_case / 8][array_case % 4]);
			break;
		case 0xFF6A:
			_ocps = value;
			break;
		case 0xFF6B:
			_ocpd = value;
//			array_case = colorPaletteArrayCaseWrapper(_ocps);
//			hilo = array_case % 2;
//			array_case -= hilo;
//			paletteAddr = (_spriteColorPalette[array_case / 8][array_case % 4]) + hilo;
//			*paletteAddr = value;
//			_spriteColorPalette_translated[array_case / 8][array_case % 4] = translateCGBColorValue(_spriteColorPalette[array_case / 8][array_case % 4]);
			break;
	}
}

//------------------------------------------------------------------------------
Byte				PPU::read(Word address) const
{
	Byte			ret;
	Byte			*paletteAddr;

	paletteAddr = 0;

	switch (address)
	{
		case 0xFF40:
			ret = _lcdc;
			break;
		case 0xFF41:
			ret = _stat;
			break;
		case 0xFF42:
			ret = _scy;
			break;
		case 0xFF43:
			ret = _scx;
			break;
		case 0xFF44:
			ret = _ly;
			break;
		case 0xFF45:
			ret = _lyc;
			break;
		case 0xFF46:
			ret = _dma;
			break;
		case 0xFF47:
			ret = _bgp;
			break;
		case 0xFF48:
			ret = _obp0;
			break;
		case 0xFF49:
			ret = _obp1;
			break;
		case 0xFF4A:
			ret = _wy;
			break;
		case 0xFF4B:
			ret = _wx;
			break;
		case 0xFF51:
			ret = _hdma1;
			break;
		case 0xFF52:
			ret = _hdma2;
			break;
		case 0xFF53:
			ret = _hdma3;
			break;
		case 0xFF54:
			ret = _hdma4;
			break;
		case 0xFF55:
			ret = _hdma5;
			break;
		case 0xFF68:
			ret = _bcps;
			break;
		case 0xFF69:
//			_bcpd = _backgroundColorPalette + colorPaletteArrayCaseWrapper(_bcps);
			ret = _bcpd;
			break;
		case 0xFF6A:
			ret = _ocps;
			break;
		case 0xFF6B:
//			_ocpd = _backgroundColorPalette + colorPaletteArrayCaseWrapper(_ocps);
			ret = _ocpd;
			break;
	}
	return (ret);
}

//------------------------------------------------------------------------------
uint8_t				PPU::readMemBank(uint8_t bank, uint16_t address)
{
	uint8_t			ret = 0;

	if (bank == 0)
	{
		_components.mem_bus->write(0xFF4F, 0);
		ret = _components.mem_bus->read<Byte>(address); // in screen !!
	}
	else if (bank == 1)
	{
		_components.mem_bus->write(0xFF4F, 1);
		ret = _components.mem_bus->read<Byte>(address); // in screen !!
	}
	return (ret);
}

//------------------------------------------------------------------------------
bool				PPU::isLCDEnabled()
{
	if (testBit(_components.mem_bus->read<Byte>(0xFF40), 7))
		return (true);
	return (false);
}

//------------------------------------------------------------------------------
bool				PPU::isScreenFilled()
{
	if (_ly >= LCD_HEIGHT)
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
	if (testBit(_lcdc, 5) == true && (_wy <= _ly))
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
	if (_ly < LCD_HEIGHT && y < LCD_HEIGHT && x < LCD_WIDTH)
	{
		switch (colorID) // only for DMG, will be different for CGB
		{
			case 3 :
				// black
				_components.driverScreen->setRGBA(y, x, 0, 0, 0, 255);
				break;
			case 2 :
				_components.driverScreen->setRGBA(y, x, 119, 119, 119, 255);
				// dark grey
				break;
			case 1 :
				_components.driverScreen->setRGBA(y, x, 204, 204, 204, 255);
				// light grey
				break;
			case 0 :
				_components.driverScreen->setRGBA(y, x, 255, 255, 255, 255);
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
		if (_ly >= yPosTmp && (_ly < (yPosTmp + _spriteSize)) && xPosTmp != 0) // IMPORTANT : _spriteSize here might be a flat 16 instead !
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
	t_pixelSegment t1;
	t_pixelSegment t2;

	t1 = holder;
	t2 = contender;

	if (1 /* IS_DMG */)
	{
		if (holder.isSprite == false)
		{
			if (1)
			{
				
			}
			if (2)
			{
				
			}
		}
		else if (holder.isSprite == true)
		{
			
		}
	}

	else if (2 /* IS_CGB */)
	{
		
	}
}

//------------------------------------------------------------------------------
void				PPU::renderSprites()
{
	getSpritesForLine();
	for (int sprite = _nbSprites - 1; sprite >= 0; sprite--) // up to 10 sprites on the line
	{
		bool		xFlip = testBit(_spritesLine[sprite].flags, 5) == true ? true : false;
		bool		yFlip = testBit(_spritesLine[sprite].flags, 6) == true ? true : false;

		int		spriteLine = _ly - _spritesLine[sprite].yPos; // which line of the sprite does the scanline go through ?
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
			
			setPixelDMG(_ly, _spritesLine[sprite].xPos - _scx + pixel, colorID);
		}
	}
}

//------------------------------------------------------------------------------
void				PPU::renderTiles()
{
	uint8_t			xPos;
	uint8_t			yPos;
	bool			boiItsaWindow = false;

	for (int i = 0; i < 160; i++)
	{
		if (_windowingOn == true && i >= _wx - 7 && _ly >= _wy) // are we in the window and is it enabled ?
			boiItsaWindow = true;

		int16_t			tileNumber;
		uint16_t		tileCol;
		uint16_t		tileRow; // which row of pixels in the tile ? (8 rows of 8 pixels per tile) position in the 256 * 256 area
		uint16_t		tileLine;
		uint16_t		tileNumberAddress;
		uint16_t		tileLocation;

		if (boiItsaWindow == true)
		{
			xPos = i - _wx - 7;
			yPos = _ly - _wy;
		}
		else
		{
			xPos = _scx + i;
			yPos = _scy + _ly;
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
		setPixelDMG(_ly, i, colorID);
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
//		setPixelDMG(_ly, i, colorValue);
	}
}

//------------------------------------------------------------------------------
void				PPU::renderScanLine()
{
	setupWindow();
	setupBackgroundMemoryStart();
	setupSpriteAddressStart();

	if (testBit(_lcdc, 0) == true)
		renderTiles();
	if (testBit(_lcdc, 1) == true)
		renderSprites();
	sendPixelPipeline();
}

//------------------------------------------------------------------------------
uint8_t					PPU::extractValue(uint32_t val, uint8_t bit_start, uint8_t bit_end)
{
	uint8_t				weight = 1;
	uint8_t				ret = 0;

	while (bit_start <= bit_end)
	{
		if (testBit(val, bit_start) == true)
			ret += weight;
		bit_start++;
		weight *= 2;
	} 
	return (ret);
}

//------------------------------------------------------------------------------
uint32_t				PPU::translateCGBColorValue(uint16_t value)
{
	uint32_t			ret = 0;
	uint32_t			extracc;

	extracc = extractValue(value, 0, 4) * 8; // extract red
	ret += extracc;
	ret = ret << 8;
	extracc = extractValue(value, 5, 9) * 8; // extract green
	ret += extracc;
	ret = ret << 8;
	extracc = extractValue(value, 10, 14) * 8; // extact blue
	ret += extracc;
	ret = ret << 8;
	ret += 255; // alpha value, default 255;
	return (ret);
}

//------------------------------------------------------------------------------
uint32_t				PPU::translateDMGColorValue(uint8_t value)
{
	uint32_t			ret = 0;
	uint32_t			reversedValue = 255 - (85 * value);

	ret += reversedValue;
	ret = ret << 8;
	ret += reversedValue;
	ret = ret << 8;
	ret += reversedValue;
	ret = ret << 8;
	ret += 255; // we set alpha value to 255 by default
	return (ret);
}

//------------------------------------------------------------------------------
void					PPU::translatePalettes()
{
	if (1 /* IS_DMG */)
	{
		_backgroundDMGPalette_translated[0] = translateDMGColorValue(extractValue(_bgp, 0, 1));
		_backgroundDMGPalette_translated[1] = translateDMGColorValue(extractValue(_bgp, 2, 3));
		_backgroundDMGPalette_translated[2] = translateDMGColorValue(extractValue(_bgp, 4, 5));
		_backgroundDMGPalette_translated[3] = translateDMGColorValue(extractValue(_bgp, 6, 7));

		_spritesDMGPalettes_translated[0][0] = translateDMGColorValue(extractValue(_obp0, 0, 1));
		_spritesDMGPalettes_translated[0][1] = translateDMGColorValue(extractValue(_obp0, 2, 3));
		_spritesDMGPalettes_translated[0][2] = translateDMGColorValue(extractValue(_obp0, 4, 5));
		_spritesDMGPalettes_translated[0][3] = translateDMGColorValue(extractValue(_obp0, 6, 7));

		_spritesDMGPalettes_translated[1][0] = translateDMGColorValue(extractValue(_obp1, 0, 1));
		_spritesDMGPalettes_translated[1][1] = translateDMGColorValue(extractValue(_obp1, 2, 3));
		_spritesDMGPalettes_translated[1][2] = translateDMGColorValue(extractValue(_obp1, 4, 5));
		_spritesDMGPalettes_translated[1][3] = translateDMGColorValue(extractValue(_obp1, 6, 7));
	}

	if (2 /* IS_CGB */)
	{
		
	}
}

//==============================================================================
void					PPU::switchPPUDebug(bool status) { PPU::_debug_PPU = status; }
int						PPU::getPPUNumber(void) { return (PPU::_nb_PPU); }

//------------------------------------------------------------------------------
int						PPU::_nb_PPU = 0;
bool					PPU::_debug_PPU = false;
