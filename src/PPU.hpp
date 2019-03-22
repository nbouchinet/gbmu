#ifndef PPU_CLASS_H
# define PPU_CLASS_H

# define LCD_WIDTH 160
# define LCD_HEIGHT 144
# define MAX_SPRITE_PER_LINE 10

#include <iostream>
#include <string>
#include <array>
#include "ScreenOutput.hpp"
#include "Fwd.hpp"
#include "IReadWrite.hpp"

/* TODO LIST

	finish the pixel mixing algorythm for CGB
	hdma transfers !!!
*/

typedef struct		s_sprite_info
{
	uint8_t			y_pos; // in screen (0-143)
	uint8_t			x_pos; // in screen (0-159)
	uint8_t			tile_number;
	uint8_t			flags;
	uint8_t			obj_number;
}					t_sprite_info;

typedef struct		s_pixel_segment
{
	uint8_t			value; // Color ID
	bool			is_sprite;
	t_sprite_info	sprite_info;
// need to add stuff related to palette // actually maybe not
}					t_pixel_segment;

class PPU : public IReadWrite
{
public:
	PPU(ComponentsContainer& components);
	~PPU();

	void					reset();

	virtual Byte			read(Word addr) const;
	virtual void			write(Word addr, Byte);

	bool					is_screen_filled();
	bool					test_bit(uint32_t byte, uint8_t bit_number) const;
	void					set_bit(uint8_t & src, uint8_t bit_number);
	void					unset_bit(uint8_t & src, uint8_t bit_number);
	void					update_graphics(Word cycles);

	static constexpr Word	LCDC = 0xFF40;
	static constexpr Word	STAT = 0xFF41;
	static constexpr Word	SCY = 0xFF42;
	static constexpr Word	SCX = 0xFF43;
	static constexpr Word	LY = 0xFF44;
	static constexpr Word	LYC = 0xFF45;
	static constexpr Word	DMA = 0xFF46;
	static constexpr Word	BGP = 0xFF47;
	static constexpr Word	OBP0 = 0xFF48;
	static constexpr Word	OBP1 = 0xFF49;
	static constexpr Word	WY = 0xFF4A;
	static constexpr Word	WX = 0xFF4B;
	static constexpr Word	VBK = 0xFF4F;
	static constexpr Word	HDMA1 = 0xFF51;
	static constexpr Word	HDMA2 = 0xFF52;
	static constexpr Word	HDMA3 = 0xFF53;
	static constexpr Word	HDMA4 = 0xFF54;
	static constexpr Word	HDMA5 = 0xFF55;
	static constexpr Word	BCPS = 0xFF68;
	static constexpr Word	BCPD = 0xFF69;
	static constexpr Word	OCPS = 0xFF6A;
	static constexpr Word	OCPD = 0xFF6B;

	static constexpr Byte	MODE_GB_NOMODE = 0x00;
	static constexpr Byte	MODE_GB_DMG = 0x01;
	static constexpr Byte	MODE_GB_DMGC = 0x02;
	static constexpr Byte	MODE_GB_CGB = 0x03;

	enum MODE_CYCLES
	{
		CYCLES_HBLANK = 204,
		CYCLES_VBLANK = 456,
		CYCLES_OAM_SEARCH = 80,
		CYCLES_DATA_TRANSFER_TO_LCD = 172
	};

	enum STAT_MODE
	{
		MODE_HBLANK = 0,
		MODE_VBLANK = 1,
		MODE_OAM_SEARCH = 2,
		MODE_DATA_TRANSFER_TO_LCD = 3
	};

private:
	uint16_t				get_tile_data_address(uint8_t tile_identifier);
	uint16_t				determine_tile_number_address(uint8_t y_pos, uint8_t x_pos, bool boi_its_a_window);
	uint8_t					read_mem_bank(uint8_t bank, uint16_t address);
	uint8_t					extract_value(uint32_t val, uint8_t bit_start, uint8_t bit_end) const;
	void					setup_window();
	void					setup_background_data();
	void					setup_sprite_data();
	void					handle_lcdc_write(uint8_t value);
	Byte					handle_cgb_bg_palette_read() const;
	Byte					handle_cgb_obj_palette_read() const;
	void					handle_cgb_bg_palette_write(uint8_t bcpd_arg);
	void					handle_cgb_obj_palette_write(uint8_t ocpd_arg);
	void					handle_hdma_transfer(uint8_t hdma5_arg);
	void					lyc_check();
	bool					is_hdma_active();
	void					hdma_h_blank_step();
	void					initiate_hdma_transfer(uint8_t hdma5_arg);
	void					dma_transfer(uint16_t address);
	bool					is_lcd_enabled();
	void					render_scanline();
	void					set_pixel(uint8_t y, uint8_t x, uint32_t value);
	void					render_tiles(); // put pixels in the pipeline from Tiles
	void					render_sprites(); // does the same with sprites, handle some merging too
	void					get_sprites_for_line();
	void					send_pixel_pipeline();
	void					blend_pixels(t_pixel_segment &holder, t_pixel_segment &contender);
	void					translate_dmg_palettes();
	uint32_t				translate_cgb_color_value(uint16_t value);
	uint32_t				translate_dmg_color_value(uint8_t value);
	uint16_t				color_palette_array_case_wrapper(uint8_t specifier) const;
	void					update_data_transfer_to_lcd_status();
	void					update_oam_search_status();
	void					update_v_blank_status();
	void					update_h_blank_status();
	bool					test_interrupt_enablers();
	void					set_stat_mode(STAT_MODE mode) { unset_bit(_stat, 0); unset_bit(_stat, 1); _stat += mode; }
	uint8_t					get_stat_mode() { return (extract_value(_stat, 0, 1)); }
	void					update_lcd_status();
	void					replace_pixel_segment(t_pixel_segment &holder, t_pixel_segment &contender);
	void					setup_gb_mode();

	ComponentsContainer&	_components;

	uint8_t					_lcdc;					// (0xFF40) lcd controller register
	uint8_t					_stat;					// (0xFF41) PPU status register (flags)
	uint8_t					_scy;					// (0xFF42) Same as above (0-255)
	uint8_t					_scx;					// (0xFF43) Scroll of the screen in the memory (0-255)
	uint8_t					_ly;					// (0xFF44) the line we're rendering, is a register (== Current Scanline)
	uint8_t					_lyc;					// (0xFF45) Scanline comparator
	uint8_t					_dma;					// (0xFF46) 
	uint8_t					_bgp;					// (0xFF47) 
	uint8_t					_obp0;					// (0xFF48) 
	uint8_t					_obp1;					// (0xFF49) 
	uint8_t					_wy;					// (0xFF4A) windowY Same as above (0-143)
	uint8_t					_wx;					// (0xFF4B) windowX Coordinates of the start of the window IN the screen (7-166)
	uint8_t					_vbk;					// (0xFF4F)
	uint8_t					_hdma1;					// (0xFF51) hdma1-5 are probably unused in the emulator // maybe not
	uint8_t					_hdma2;					// (0xFF52)
	uint8_t					_hdma3;					// (0xFF53)
	uint8_t					_hdma4;					// (0xFF54)
	uint8_t					_hdma5;					// (0xFF55)
	uint8_t					_bcps;					// (0xFF68)
	uint8_t					_bcpd;					// (0xFF69)
	uint8_t					_ocps;					// (0xFF6A)
	uint8_t					_ocpd;					// (0xFF6B)

	uint64_t				_lcd_cycles;
	uint16_t				_background_data_start;
	uint16_t				_background_chr_attr_start;
	uint16_t				_sprite_data_start;
	uint16_t				_window_chr_attr_start;
	uint8_t					_sprite_size;
	bool					_unsigned_tile_numbers;
	bool					_windowing_on;
	uint8_t					_gb_mode;

	uint16_t				_h_blank_hdma_src_addr;
	uint16_t				_h_blank_hdma_dst_addr;
	bool					_h_blank_hdma_step_done;

	uint32_t				_background_color_palettes_translated[8][4];
	uint32_t				_sprite_color_palettes_translated[8][4];
	uint16_t				_background_color_palettes[8][4];
	uint16_t				_sprite_color_palettes[8][4];

	uint32_t				_background_dmg_palette_translated[4];
	uint32_t				_sprites_dmg_palettes_translated[2][4];

	uint8_t					_background_dmg_palette[4];
	uint8_t					_sprites_dmg_palettes[2][4];

	t_pixel_segment			_pixel_pipeline[LCD_WIDTH];
	t_sprite_info			_sprites_line[MAX_SPRITE_PER_LINE];	// by default 10 sprites per line
	uint8_t					_nb_sprites;

	std::array<Byte, 8192>		_lcd_memory_bank_1;
	std::array<Byte, 8192>		_lcd_memory_bank_0; // (0x8000-0x9FFF) Tiles RAM bank 0
	std::array<Byte, 160>		_lcd_oam_ram; // (0xFE00 - 0xFE9F) Sprite attr RAM

};

#endif
