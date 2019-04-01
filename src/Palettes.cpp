#include "Gameboy.hpp"
#include "MemoryBus.hpp"
#include "PPU.hpp"
#include "cpu/InterruptController.hpp"

#include <bitset>
#include <unistd.h>

//------------------------------------------------------------------------------
void PPU::handle_cgb_bg_palette_write(uint8_t bcpd_arg) {
	uint16_t palette_tmp_value = 0;

	_bcpd = bcpd_arg;
	if (test_bit(_bcps, 0) == true) // high byte
	{
		palette_tmp_value = bcpd_arg;
		palette_tmp_value = palette_tmp_value << 8;
		palette_tmp_value |=
			_background_color_palettes[extract_value(_bcps, 3, 5)]
			[extract_value(_bcps, 1, 2)] &
			0x00FF;
	} else // low byte
	{
		palette_tmp_value = _background_color_palettes[extract_value(_bcps, 3, 5)]
			[extract_value(_bcps, 1, 2)] &
			0xFF00;
		palette_tmp_value |= bcpd_arg;
	}
	_background_color_palettes[extract_value(_bcps, 3, 5)]
		[extract_value(_bcps, 1, 2)] = palette_tmp_value;
	_background_color_palettes_translated[extract_value(
			_bcps, 3, 5)][extract_value(_bcps, 1, 2)] =
		translate_cgb_color_value(palette_tmp_value);
	if (test_bit(_bcps, 7) == true) {
		_bcps += 1;
	}
	//  std::cerr << "================" << std::endl;
}

//------------------------------------------------------------------------------
void PPU::handle_cgb_obj_palette_write(uint8_t ocpd_arg) {
	uint16_t palette_tmp_value = 0;

	_ocpd = ocpd_arg;
	if (test_bit(_ocps, 0) == true) // high byte
	{
		palette_tmp_value = ocpd_arg;
		palette_tmp_value = palette_tmp_value << 8;
		palette_tmp_value |= _sprite_color_palettes[extract_value(_ocps, 3, 5)]
			[extract_value(_ocps, 1, 2)] &
			0x00FF;
	} else // low byte
	{
		palette_tmp_value = _sprite_color_palettes[extract_value(_ocps, 3, 5)]
			[extract_value(_ocps, 1, 2)] &
			0xFF00;
		palette_tmp_value |= ocpd_arg;
	}
	_sprite_color_palettes[extract_value(_ocps, 3, 5)]
		[extract_value(_ocps, 1, 2)] = palette_tmp_value;
	_sprite_color_palettes_translated[extract_value(_ocps, 3, 5)][extract_value(
			_ocps, 1, 2)] = translate_cgb_color_value(palette_tmp_value);
	if (test_bit(_ocps, 7) == true) {
		_ocps += 1;
	}
}

//------------------------------------------------------------------------------
Byte PPU::handle_cgb_obj_palette_read() const {
	uint16_t palette_tmp_value = 0;
	Byte ret = 0;

	palette_tmp_value = _background_color_palettes[extract_value(_bcps, 3, 5)]
		[extract_value(_bcps, 1, 2)];
	if (test_bit(_bcps, 0) == true) {
		// high byte
		palette_tmp_value = palette_tmp_value & 0xFF00;
		palette_tmp_value = palette_tmp_value >> 8;
		ret = palette_tmp_value;
	} else {
		// low byte
		palette_tmp_value = palette_tmp_value & 0x00FF;
		ret = palette_tmp_value;
	}
	return (ret);
}

//------------------------------------------------------------------------------
Byte PPU::handle_cgb_bg_palette_read() const {
	uint16_t palette_tmp_value = 0;
	Byte ret = 0;

	palette_tmp_value = _sprite_color_palettes[extract_value(_ocps, 3, 5)]
		[extract_value(_ocps, 1, 2)];
	if (test_bit(_ocps, 0) == true) {
		// high byte
		palette_tmp_value = palette_tmp_value & 0xFF00;
		palette_tmp_value = palette_tmp_value >> 8;
		ret = palette_tmp_value;
	} else {
		// low byte
		palette_tmp_value = palette_tmp_value & 0x00FF;
		ret = palette_tmp_value;
	}
	return (ret);
}
//------------------------------------------------------------------------------
uint32_t PPU::translate_cgb_color_value(uint16_t value) {
	uint32_t ret = 0;
	uint32_t extracc;

	extracc = extract_value(value, 0, 4) << 3; // * 8; // extract red
	ret += extracc;
	ret = ret << 8;
	extracc = extract_value(value, 5, 9) << 3; // * 8; // extract green
	ret += extracc;
	ret = ret << 8;
	extracc = extract_value(value, 10, 14) << 3; // * 8; // extact blue
	ret += extracc;
	ret = ret << 8;
	ret += 255; // alpha value, default 255;
	return (ret);
}

//------------------------------------------------------------------------------
uint32_t PPU::translate_dmg_color_value(uint8_t value) {
	switch (value) {
		case 0:
			return (0xFFFFFFFF);
		case 1:
			return (0xCCCCCCFF);
		case 2:
			return (0x777777FF);
		case 3:
			return (0x000000FF);
	}
	return (0);
}

//------------------------------------------------------------------------------
void PPU::translate_dmg_palettes() {
	for (int i = 0; i < 4; i++) {
		_background_dmg_palette[i] = extract_value(_bgp, (i * 2), (i * 2) + 1);
		_background_dmg_palette_translated[i] =
			translate_dmg_color_value(extract_value(_bgp, (i * 2), (i * 2) + 1));

		_sprites_dmg_palettes[0][i] = extract_value(_obp0, (i * 2), (i * 2) + 1);
		_sprites_dmg_palettes[1][i] = extract_value(_obp1, (i * 2), (i * 2) + 1);
		_sprites_dmg_palettes_translated[0][i] =
			translate_dmg_color_value(extract_value(_obp0, (i * 2), (i * 2) + 1));
		_sprites_dmg_palettes_translated[1][i] =
			translate_dmg_color_value(extract_value(_obp1, (i * 2), (i * 2) + 1));
	}
}

//------------------------------------------------------------------------------
void PPU::enforce_debug_palettes() {
	_background_color_palettes_translated[0][0] = 0xFFE6E6FF; // Rouge
	_background_color_palettes_translated[0][1] = 0xFF4D4DFF;
	_background_color_palettes_translated[0][2] = 0xe60000FF;
	_background_color_palettes_translated[0][3] = 0x800000FF;

	_background_color_palettes_translated[1][0] = 0xFFCCE6FF; // Rose
	_background_color_palettes_translated[1][1] = 0xFF66B5FF;
	_background_color_palettes_translated[1][2] = 0xFF0084FF;
	_background_color_palettes_translated[1][3] = 0xB3005CFF;

	_background_color_palettes_translated[2][0] = 0xf9e6ffFF; // Violet
	_background_color_palettes_translated[2][1] = 0xd966ffFF;
	_background_color_palettes_translated[2][2] = 0xFF0084FF;
	_background_color_palettes_translated[2][3] = 0x9900ccFF;

	_background_color_palettes_translated[3][0] = 0xe6e6ffFF; // Bleu
	_background_color_palettes_translated[3][1] = 0x6666ffFF;
	_background_color_palettes_translated[3][2] = 0x0000ccFF;
	_background_color_palettes_translated[3][3] = 0x000099FF;

	_background_color_palettes_translated[4][0] = 0xe6ffffFF; // Cyan
	_background_color_palettes_translated[4][1] = 0x66ffffFF;
	_background_color_palettes_translated[4][2] = 0x00ccccFF;
	_background_color_palettes_translated[4][3] = 0x009999FF;

	_background_color_palettes_translated[5][0] = 0xf2ffe6FF; // Vert
	_background_color_palettes_translated[5][1] = 0xb3ff66FF;
	_background_color_palettes_translated[5][2] = 0x66cc00FF;
	_background_color_palettes_translated[5][3] = 0x4d9900FF;

	_background_color_palettes_translated[6][0] = 0xffffe6FF; // Jaune
	_background_color_palettes_translated[6][1] = 0xffff66FF;
	_background_color_palettes_translated[6][2] = 0xcccc00FF;
	_background_color_palettes_translated[6][3] = 0x999900FF;

	_background_color_palettes_translated[7][0] = 0xfff0e6FF; // Orange
	_background_color_palettes_translated[7][1] = 0xffa366FF;
	_background_color_palettes_translated[7][2] = 0xcc5200FF;
	_background_color_palettes_translated[7][3] = 0x993d00FF;

	_sprite_color_palettes_translated[7][0] = 0xFFE6E6FF; // Orange
	_sprite_color_palettes_translated[7][1] = 0xFF4D4DFF;
	_sprite_color_palettes_translated[7][2] = 0xe60000FF;
	_sprite_color_palettes_translated[7][3] = 0x800000FF;

	_sprite_color_palettes_translated[6][0] = 0xFFCCE6FF; // Jaune
	_sprite_color_palettes_translated[6][1] = 0xFF66B5FF;
	_sprite_color_palettes_translated[6][2] = 0xFF0084FF;
	_sprite_color_palettes_translated[6][3] = 0xB3005CFF;

	_sprite_color_palettes_translated[5][0] = 0xf9e6ffFF; // Vert
	_sprite_color_palettes_translated[5][1] = 0xd966ffFF;
	_sprite_color_palettes_translated[5][2] = 0xFF0084FF;
	_sprite_color_palettes_translated[5][3] = 0x9900ccFF;

	_sprite_color_palettes_translated[4][0] = 0xe6e6ffFF; // Cyan
	_sprite_color_palettes_translated[4][1] = 0x6666ffFF;
	_sprite_color_palettes_translated[4][2] = 0x0000ccFF;
	_sprite_color_palettes_translated[4][3] = 0x000099FF;

	_sprite_color_palettes_translated[3][0] = 0xe6ffffFF; // Bleu
	_sprite_color_palettes_translated[3][1] = 0x66ffffFF;
	_sprite_color_palettes_translated[3][2] = 0x00ccccFF;
	_sprite_color_palettes_translated[3][3] = 0x009999FF;

	_sprite_color_palettes_translated[2][0] = 0xf2ffe6FF; // Violet
	_sprite_color_palettes_translated[2][1] = 0xb3ff66FF;
	_sprite_color_palettes_translated[2][2] = 0x66cc00FF;
	_sprite_color_palettes_translated[2][3] = 0x4d9900FF;

	_sprite_color_palettes_translated[1][0] = 0xffffe6FF; // Rose
	_sprite_color_palettes_translated[1][1] = 0xffff66FF;
	_sprite_color_palettes_translated[1][2] = 0xcccc00FF;
	_sprite_color_palettes_translated[1][3] = 0x999900FF;

	_sprite_color_palettes_translated[0][0] = 0xfff0e6FF; // Rouge
	_sprite_color_palettes_translated[0][1] = 0xffa366FF;
	_sprite_color_palettes_translated[0][2] = 0xcc5200FF;
	_sprite_color_palettes_translated[0][3] = 0x993d00FF;
}
