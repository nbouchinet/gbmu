#include "PPU.class.h"
#include "Gameboy.hpp"
#include "MemoryBus.hpp"
#include "cpu/InterruptController.hpp"

//------------------------------------------------------------------------------
PPU::PPU(ComponentsContainer& components) : _components(components)
{
	if (_debug_PPU == true)
		std::cerr << "[PPU default constructor called]" << std::endl;
	PPU::_nb_PPU++;
	init();
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

//------------------------------------------------------------------------------
void				PPU::init()
{
	for (int i = 0; i < 8192; i++)
	{
		_lcdMemoryBank_0[i] = 0;
		_lcdMemoryBank_1[i] = 0;
	}

	for (int i = 0; i < LCD_WIDTH; i++)
	{
		_lcdOamRam[i] = 0;

		_pixelPipeline[i].value = false;
		_pixelPipeline[i].isSprite = false;
		_pixelPipeline[i].spriteInfo.yPos = 0;
		_pixelPipeline[i].spriteInfo.xPos = 0;
		_pixelPipeline[i].spriteInfo.tileNumber = 0;
		_pixelPipeline[i].spriteInfo.flags = 0;
		_pixelPipeline[i].spriteInfo.objNumber = 0;
	}

	for (int i = 0; i < MAX_SPRITE_PER_LINE; i++)
	{
		_spritesLine[i].yPos = 0;
		_spritesLine[i].xPos = 0;
		_spritesLine[i].tileNumber = 0;
		_spritesLine[i].flags = 0;
		_spritesLine[i].objNumber = 0;
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_backgroundColorPalettes_translated[i][j] = 0;
			_spriteColorPalettes_translated[i][j] = 0;
			_backgroundColorPalettes[i][j] = 0;
			_spriteColorPalettes[i][j] = 0;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		_backgroundDMGPalette_translated[i] = 0;
		_spritesDMGPalettes_translated[0][i] = 0;
		_spritesDMGPalettes_translated[1][i] = 0;
	}

	translatePalettes();

	_lcdc = 0x91;
	_stat = 0;
	_scy = 0;
	_scx = 0;
	_ly = 0;
	_lyc = 0;
	_dma = 0;
	_bgp = 0xFC;
	_obp0 = 0xFF;
	_obp1 = 0xFF;
	_wy = 0;
	_wx = 0;
	_hdma1 = 0;
	_hdma2 = 0;
	_hdma3 = 0;
	_hdma4 = 0;
	_hdma5 = 0;
	_bcps = 0;
	_ocps = 0;
	_bcpd = 0;
	_bcpd = 0;

	_scanlineCounter = 0;
	_backgroundDataStart = 0;
	_backgroundChrAttrStart = 0;
	_spriteDataStart = 0;
	_windowChrAttrStart = 0;
	_spriteSize = 0;
	_unsignedTileNumbers = false;
	_windowingOn = false;
	_nbSprites = 0;
}

//==============================================================================
bool				PPU::testBit(uint32_t byte, uint8_t bit_number) const
{
	if ((byte) & (1 << (bit_number)))
		return (true);
	return (false);
}

//------------------------------------------------------------------------------
uint8_t					PPU::setBit(uint8_t src, uint8_t bit_number)
{
	src |= 1UL << bit_number;
	return (src);
}

//------------------------------------------------------------------------------
uint8_t					PPU::unsetBit(uint8_t src, uint8_t bit_number)
{
	src &= ~(1UL << bit_number);
	return (src);
}

//------------------------------------------------------------------------------
uint16_t				PPU::colorPaletteArrayCaseWrapper(uint8_t specifier) const
{
	uint8_t				paletteNumber;
	uint8_t				paletteDataNumber;
	uint16_t			ret = 0;

	paletteNumber = extractValue(specifier, 3, 5);
	paletteDataNumber = extractValue(specifier, 1, 2);

	ret	+= (paletteNumber * 4) + (paletteDataNumber);

	return (ret);
}

//------------------------------------------------------------------------------
void				PPU::write(Word address, Byte value)
{
	uint16_t		paletteTmpValue = 0;
	uint8_t			array_case = 0;

	if (address >= 0x8000 && address < 0xA000)
	{
		//		if (VEBEKA == 1)
		//		{
		//			_lcdMemoryBank_1[address - 0x8000] = value;
		//			return ;
		//		}
		//		else
		//		{
		_lcdMemoryBank_0[address - 0x8000] = value;
		return ;
		//		}
	}
	if (address >= 0xFE00 && address < 0xFEA0)
	{
		_lcdOamRam[address - 0xFE00] = value;
		return ;
	}

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
			uint16_t	dmaAddr;
			dmaAddr = address << 8;
			if (1) // IS DMG
			{
				for (int i = 0; i < 0xA0; i++)
				{
					write(0xFE00 + i, _components.mem_bus->read<Byte>(dmaAddr + i));
				}
			}
			else if (2) // IS CGB
			{

			}
			break;
		case 0xFF47:
			_bgp = value;
			translatePalettes();
			break;
		case 0xFF48:
			_obp0 = value;
			translatePalettes();
			break;
		case 0xFF49:
			_obp1 = value;
			translatePalettes();
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
			array_case = colorPaletteArrayCaseWrapper(_bcps);
			if (testBit(_bcps, 7) == true)
				array_case += 1;
			if (testBit(_bcps, 0) == true) // high byte
			{
				paletteTmpValue = value;
				paletteTmpValue = paletteTmpValue << 8;
				paletteTmpValue += _backgroundColorPalettes[array_case / 4][array_case % 4] & 0x00FF;
			}
			else // low byte
			{
				paletteTmpValue = paletteTmpValue & 0xFF00;
				paletteTmpValue += value;
			}
			_backgroundColorPalettes[array_case / 4][array_case % 4] = paletteTmpValue;
			_backgroundColorPalettes_translated[array_case / 4][array_case % 4] = translateCGBColorValue(_backgroundColorPalettes[array_case / 4][array_case % 4]);
			break;
		case 0xFF6A:
			_ocps = value;
			break;
		case 0xFF6B:
			_ocpd = value;
			array_case = colorPaletteArrayCaseWrapper(_ocps);
			if (testBit(_ocps, 7) == true)
				array_case += 1;
			if (testBit(_ocps, 0) == true) // high byte
			{
				paletteTmpValue = value;
				paletteTmpValue = paletteTmpValue << 8;
				paletteTmpValue += _spriteColorPalettes[array_case / 4][array_case % 4] & 0x00FF;
			}
			else // low byte
			{
				paletteTmpValue = paletteTmpValue & 0xFF00;
				paletteTmpValue += value;
			}
			_spriteColorPalettes[array_case / 4][array_case % 4] = paletteTmpValue;
			_spriteColorPalettes_translated[array_case / 4][array_case % 4] = translateCGBColorValue(_spriteColorPalettes[array_case / 4][array_case % 4]);

			break;
	}
}

//------------------------------------------------------------------------------
Byte				PPU::read(Word address) const
{
	Byte			ret = 0;
	uint8_t			array_case = 0;
	uint16_t		paletteTmpValue = 0;

	if (address >= 0x8000 && address < 0xA000)
	{
		//		if (VEBEKA == 1)
		//		{
		//			ret = _lcdMemoryBank_1[address - 0x8000];
		//			return (ret) ;
		//		}
		//		else
		//		{
		ret = _lcdMemoryBank_0[address - 0x8000];
		return (ret);
		//		}
	}
	if (address >= 0xFE00 && address < 0xFEA0)
	{
		ret = _lcdOamRam[address - 0xFE00];
		return (ret);
	}

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
			array_case = colorPaletteArrayCaseWrapper(_bcps);
			paletteTmpValue = _backgroundColorPalettes[array_case / 4][array_case % 4];
			if (testBit(_bcps, 0) == true)
			{
				// high byte
				paletteTmpValue = paletteTmpValue & 0xFF00;
				paletteTmpValue = paletteTmpValue >> 8;
				ret = paletteTmpValue;
			}
			else
			{
				// low byte
				paletteTmpValue = paletteTmpValue & 0x00FF;
				ret = paletteTmpValue;
			}
			break;
		case 0xFF6A:
			ret = _ocps;
			break;
		case 0xFF6B:
			array_case = colorPaletteArrayCaseWrapper(_ocps);
			paletteTmpValue = _spriteColorPalettes[array_case / 4][array_case % 4];
			if (testBit(_ocps, 0) == true)
			{
				// high byte
				paletteTmpValue = paletteTmpValue & 0xFF00;
				paletteTmpValue = paletteTmpValue >> 8;
				ret = paletteTmpValue;
			}
			else
			{
				// low byte
				paletteTmpValue = paletteTmpValue & 0x00FF;
				ret = paletteTmpValue;
			}
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
void				PPU::setPixel(uint8_t y, uint8_t x, uint32_t value)
{
	_components.driver_screen->setRGBA(y, x, value);
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
			_spritesLine[_nbSprites].objNumber = sprite;
			_nbSprites++;
		}
		if (_nbSprites >= MAX_SPRITE_PER_LINE) // this allows to only take up to 10 sprites by default
			return ;
	}
}

//------------------------------------------------------------------------------
void				PPU::replacePixelSegment(t_pixelSegment &holder, t_pixelSegment &contender)
{
	holder.value = contender.value;
	holder.isSprite = contender.isSprite;
	holder.spriteInfo = contender.spriteInfo;
}

//------------------------------------------------------------------------------
void				PPU::blendPixels(t_pixelSegment &holder, t_pixelSegment &contender)
{
	// tmp

	if (1) // is DMG
	{
		if (holder.isSprite == false) // VS background
		{
			if (contender.isSprite == true // contender is a sprite
					&& testBit(contender.spriteInfo.flags, 7) == false // sprite has priority to BG
					&& contender.value > 0) // == not transparent pixel
			{
				replacePixelSegment(holder, contender);
			}
			else if (contender.isSprite == true // contender is a sprite
					&& testBit(contender.spriteInfo.flags, 7) == true // sprite does not have priority to BG
					&& _backgroundDMGPalette[holder.value] == 0) // background is transparent;
			{
				replacePixelSegment(holder, contender);
			}
		}
		else if (holder.isSprite == true) // VS sprite
		{
			if (holder.value == 0 && contender.value != 0) // transparent pixel vs not transparent
				replacePixelSegment(holder, contender);
			else if (holder.value != 0 && contender.value != 0) // neither sprites pixels are transparent
			{
				if (contender.spriteInfo.xPos < holder.spriteInfo.xPos // comparing xPos
						|| (contender.spriteInfo.xPos == holder.spriteInfo.xPos // if still can't determine, use obj number instead
							&& contender.spriteInfo.objNumber < holder.spriteInfo.objNumber))
				{
					replacePixelSegment(holder, contender);
				}
			}
		}
	}

	else if (2) // is CGB
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
			uint8_t				linePixel = pixel;
			uint8_t				colorID = 0;
			t_pixelSegment		contender;

			if (xFlip == true)
				linePixel = (linePixel - 7) * (-1);
			if (testBit(data1, linePixel) == true)
				colorID += 2;
			if (testBit(data2, linePixel) == true)
				colorID += 1;

			if (_spritesLine[sprite].xPos + pixel > 7 && _spritesLine[sprite].xPos + pixel < LCD_WIDTH)
			{
				contender.value = colorID;
				contender.isSprite = true;
				contender.spriteInfo = _spritesLine[sprite];

				blendPixels(_pixelPipeline[contender.spriteInfo.xPos], contender);
			}
		}
	}
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
uint16_t			PPU::determineTileNumberAddress(uint8_t yPos, uint8_t xPos, bool boiItsaWindow)
{
	uint16_t		tileRow; // 32 Tiles per line
	uint16_t		tileCol; // add to Row  
	uint16_t		tileNumberAddress; // where's the tile CHR number ?

	tileRow = (((uint16_t)(yPos / 8)) * 32);		// (0-992) 32 tiles per 8 vertical pixels
	tileCol = xPos / 8;								// (0-32) 1 tile per 8 horizontal pixel

	if (boiItsaWindow == true)
		tileNumberAddress = _windowChrAttrStart + tileRow + tileCol;	// 1 byte per tile number (uint8_t), just the tile number
	tileNumberAddress = _backgroundChrAttrStart + tileRow + tileCol;

	return (tileNumberAddress);
}

//------------------------------------------------------------------------------
void				PPU::renderTiles()
{
	uint8_t			xPos;
	uint8_t			yPos;
	bool			boiItsaWindow = false;
	uint16_t		tileNumberAddress; // from tileNumberAddress we get the tileNumber (in BG display Data)
	uint8_t			tileNumber; // from BG display data we get tileNumber
	uint16_t		tileLocation; // from tileNumber we deduce where the data for each pixel of the tile starts
//	uint8_t			tileAttr; // needed for CGB, same location as tileNumberAddress in the BG display Data except in the Bank 1 

	for (int i = 0; i < 160; i++)
	{
		if (_windowingOn == true && i >= _wx - 7 && _ly >= _wy) // are we in the window and is it enabled ?
			boiItsaWindow = true;

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
		tileNumberAddress = determineTileNumberAddress(yPos, xPos, boiItsaWindow);
		//if (CGB)
		//	tileAttr =

		if (_unsignedTileNumbers)
		{
			tileNumber = (uint8_t)read(tileNumberAddress);
		}
		else
		{
			tileNumber = (int8_t)read(tileNumberAddress);
		}

		tileLocation = getTileDataAddress(tileNumber);

		uint8_t			pixelLineInTile = yPos % 8;
		uint8_t			pixelInTileLine = xPos % 8;
		//if (CGB)
		//{
		//	if (testBit(tileAttr, 6) == true) // we check the vertical flip flag, only in CGB
		//		pixelLineInTile = 7 - pixelLineInTile;
		//	if (testBit(tileAttr, 5) == true) // we check horizontal flip flag, only in CGB
		//		pixelInTileLine = 7 - pixelInTileLine
		//}

		uint16_t		tileLine = (pixelLineInTile * 2);						// 16 bits (2 bytes) per 8 pixels, get the right horizontal line of pixels
		uint8_t			firstByte = read(tileLocation + tileLine);
		uint8_t			secondByte = read(tileLocation + tileLine + 1);

		//extract the color value
		uint8_t			colorID = 0;
		if (testBit(firstByte, pixelInTileLine) == true)
			colorID += 2;
		if (testBit(secondByte, pixelInTileLine) == true)
			colorID += 1;

		//put in pipeline
		_pixelPipeline[i].value = colorID;
		_pixelPipeline[i].isSprite = false;
		_pixelPipeline[i].spriteInfo.tileNumber = tileNumber;
		//_pixelPipeline[i].spriteinfo.flags = tileAttr;
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
			case 0:// DMG
				if (_pixelPipeline[i].isSprite == false)
				{
					setPixel(_ly, i, _backgroundDMGPalette_translated[_pixelPipeline[i].value]);
				}
				else if (_pixelPipeline[i].isSprite == true)
				{
					if (testBit(_pixelPipeline[i].spriteInfo.flags, 4) == true)
						setPixel(_ly, i, _spritesDMGPalettes_translated[1][_pixelPipeline[i].value]);
					else
						setPixel(_ly, i, _spritesDMGPalettes_translated[0][_pixelPipeline[i].value]);
				}
				break ;
			case 1:
				break ;
			case 2:
				break ;
		}
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
uint8_t					PPU::extractValue(uint32_t val, uint8_t bit_start, uint8_t bit_end) const
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
		_backgroundDMGPalette[0] = extractValue(_bgp, 0, 1);
		_backgroundDMGPalette[1] = extractValue(_bgp, 2, 3);
		_backgroundDMGPalette[2] = extractValue(_bgp, 4, 5);
		_backgroundDMGPalette[3] = extractValue(_bgp, 6, 7);

		_backgroundDMGPalette_translated[0] = translateDMGColorValue(extractValue(_bgp, 0, 1));
		_backgroundDMGPalette_translated[1] = translateDMGColorValue(extractValue(_bgp, 2, 3));
		_backgroundDMGPalette_translated[2] = translateDMGColorValue(extractValue(_bgp, 4, 5));
		_backgroundDMGPalette_translated[3] = translateDMGColorValue(extractValue(_bgp, 6, 7));


		_spritesDMGPalettes[0][0] = extractValue(_obp0, 0, 1);
		_spritesDMGPalettes[0][1] = extractValue(_obp0, 2, 3);
		_spritesDMGPalettes[0][2] = extractValue(_obp0, 4, 5);
		_spritesDMGPalettes[0][3] = extractValue(_obp0, 6, 7);

		_spritesDMGPalettes[1][0] = extractValue(_obp1, 0, 1);
		_spritesDMGPalettes[1][1] = extractValue(_obp1, 2, 3);
		_spritesDMGPalettes[1][2] = extractValue(_obp1, 4, 5);
		_spritesDMGPalettes[1][3] = extractValue(_obp1, 6, 7);


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

//------------------------------------------------------------------------------
void					PPU::setLCDstatus()
{
	uint8_t				statusTmp;

	statusTmp = read(0xFF41);
	if (isLCDEnabled() == false)
	{
		_scanlineCounter = 456;
		write(0xFF44, 0);
		statusTmp &= 252;
		statusTmp = setBit(statusTmp, 0);
		write(0xFF41, statusTmp);
		return ;
	}

	uint8_t				currentMode = statusTmp & 0x3;
	uint8_t				mode = 0;
	bool				requestInterruptFlag = false;

	if (read(0xFF44) >= 144)
	{
		mode = 1;
		statusTmp = setBit(statusTmp, 0);
		statusTmp = unsetBit(statusTmp, 1);
		requestInterruptFlag = testBit(statusTmp, 4);
	}
	else
	{
		uint32_t mode2Bounds = 456 - 80;
		uint32_t mode3Bounds = mode2Bounds - 172;

		if (_scanlineCounter >= mode2Bounds)
		{
			mode = 2;
			statusTmp = setBit(statusTmp, 1);
			statusTmp = unsetBit(statusTmp, 0);
			requestInterruptFlag = testBit(statusTmp, 5);
		}
		else if (_scanlineCounter >= mode3Bounds)
		{
			mode = 3;
			statusTmp = setBit(statusTmp, 1);
			statusTmp = setBit(statusTmp, 0);
		}
		else
		{
			mode = 0;
			statusTmp = unsetBit(statusTmp, 1);
			statusTmp = unsetBit(statusTmp, 0);
			requestInterruptFlag = testBit(statusTmp, 3);
		}
	}

	if (requestInterruptFlag == true && mode != currentMode)
		_components.interrupt_controller->request_interrupt(0x0048);

	if (read(0xFF45))
	{
		statusTmp = setBit(statusTmp, 2);
		if (testBit(statusTmp, 6))
			_components.interrupt_controller->request_interrupt(0x0048);
	}
	else
	{
		statusTmp = unsetBit(statusTmp, 2);
	}
	write(0xFF41, statusTmp);
}

//------------------------------------------------------------------------------
void					PPU::updateGraphics(Word cycles)
{
	uint8_t				currentScanline;

	setLCDstatus();
	if (isLCDEnabled())
	{
		if (static_cast<int>(_scanlineCounter) - cycles <= 0)
			_scanlineCounter = 0;
		else
			_scanlineCounter -= cycles;
	}
	else
		return ;

	if (_scanlineCounter <= 0)
	{
		_ly++;
		currentScanline = _ly;
		_scanlineCounter = 456;
		if (currentScanline == 144)
			_components.interrupt_controller->request_interrupt(0x0040);
		if (currentScanline > 153)
			_ly = 0;
		else if (currentScanline < 144)
			renderScanLine();
	}
}

//==============================================================================
void					PPU::switchPPUDebug(bool status) { PPU::_debug_PPU = status; }
int						PPU::getPPUNumber(void) { return (PPU::_nb_PPU); }

//------------------------------------------------------------------------------
int						PPU::_nb_PPU = 0;
bool					PPU::_debug_PPU = false;
