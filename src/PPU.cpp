#include "Gameboy.hpp"
#include "MemoryBus.hpp"
#include "PPU.hpp"
#include "cpu/InterruptController.hpp"

#include <bitset>
#include <unistd.h>

//------------------------------------------------------------------------------
PPU::PPU(ComponentsContainer &components) : _components(components) {
  reset();
  return;
}

//------------------------------------------------------------------------------
PPU::~PPU() { return; }

//------------------------------------------------------------------------------
void PPU::reset() {
  for (int i = 0; i < 8192; i++) {
    _lcd_memory_bank_0[i] = 0;
    _lcd_memory_bank_1[i] = 0;
  }

  for (int i = 0; i < LCD_WIDTH; i++) {
    _lcd_oam_ram[i] = 0;

    _pixel_pipeline[i].value = false;
    _pixel_pipeline[i].is_sprite = false;
    _pixel_pipeline[i].sprite_info.y_pos = 0;
    _pixel_pipeline[i].sprite_info.x_pos = 0;
    _pixel_pipeline[i].sprite_info.tile_number = 0;
    _pixel_pipeline[i].sprite_info.flags = 0;
    _pixel_pipeline[i].sprite_info.obj_number = 0;
  }

  for (int i = 0; i < MAX_SPRITE_PER_LINE; i++) {
    _sprites_line[i].y_pos = 0;
    _sprites_line[i].x_pos = 0;
    _sprites_line[i].tile_number = 0;
    _sprites_line[i].flags = 0;
    _sprites_line[i].obj_number = 0;
  }

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 4; j++) {
      _background_color_palettes_translated[i][j] = 0;
      _sprite_color_palettes_translated[i][j] = 0;
      _background_color_palettes[i][j] = 0;
      _sprite_color_palettes[i][j] = 0;
    }
  }

  for (int i = 0; i < 4; i++) {
    _background_dmg_palette_translated[i] = 0;
    _sprites_dmg_palettes_translated[0][i] = 0;
    _sprites_dmg_palettes_translated[1][i] = 0;
  }

  translate_dmg_palettes();

  _lcdc = 0x91;
  _stat = 0x80;
  _scy = 0;
  _scx = 0;
  _ly = 0;
  _lyc = 0;
  _dma = 0xFF;
  _bgp = 0xFC;
  _obp0 = 0xFF;
  _obp1 = 0xFF;
  _wy = 0;
  _wx = 0;
  _vbk = 0;
  _hdma1 = 0xFF;
  _hdma2 = 0xFF;
  _hdma3 = 0xFF;
  _hdma4 = 0xFF;
  _hdma5 = 0xFF;
  _bcps = 0xC0;
  _ocps = 0xC1;
  _bcpd = 0xFF;
  _ocpd = 0x00;

  _lcd_cycles = 0;
  _background_data_start = 0;
  _background_chr_attr_start = 0;
  _sprite_data_start = 0;
  _window_chr_attr_start = 0;
  _sprite_size = 0;
  _unsigned_tile_numbers = false;
  _windowing_on = false;
  _nb_sprites = 0;
  _gb_mode = 0;

  _h_blank_hdma_src_addr = 0;
  _h_blank_hdma_dst_addr = 0;

  _nb_frames_rendered = 0;
  _wait_frames_turn_on = 0;
}

//==============================================================================
bool PPU::test_bit(uint32_t byte, uint8_t bit_number) const {
  if ((byte) & (1 << (bit_number)))
    return (true);
  return (false);
}

//------------------------------------------------------------------------------
void PPU::set_bit(uint8_t &src, uint8_t bit_number) {
  src |= 1UL << bit_number;
}

//------------------------------------------------------------------------------
void PPU::unset_bit(uint8_t &src, uint8_t bit_number) {
  src &= ~(1UL << bit_number);
}

//------------------------------------------------------------------------------
bool PPU::is_hdma_active() {
  return (test_bit(_hdma5, 7) == true ? false : true);
}

//------------------------------------------------------------------------------
void PPU::hdma_h_blank_step() {
  // if destination address overflows, stop the transfer
  if (_h_blank_hdma_dst_addr + 16 < _h_blank_hdma_dst_addr) {
    set_bit(_hdma5, 7);
    return;
  }

  for (int i = 0; i < 16; i++) {
    _components.mem_bus->write(
        _h_blank_hdma_dst_addr + 0x8000,
        _components.mem_bus->read<Byte>(_h_blank_hdma_src_addr));
    _h_blank_hdma_src_addr++;
    _h_blank_hdma_dst_addr++;
  }

  _hdma1 = _h_blank_hdma_src_addr >> 8;
  _hdma2 = _h_blank_hdma_src_addr & 0xFF;
  _hdma3 = _h_blank_hdma_dst_addr >> 8;
  _hdma4 = _h_blank_hdma_dst_addr & 0xFF;

  _hdma5--;
}

//------------------------------------------------------------------------------
void PPU::general_purpose_hdma(uint8_t hdma5_arg) {
  uint16_t addr_source = 0;
  uint16_t addr_dest = 0;
  uint16_t lines_to_transfer = 0;

  addr_source = ((_hdma1 << 8) | _hdma2) & 0xFFF0;
  addr_dest = ((_hdma3 << 8) | _hdma4) & 0x1FF0;
  lines_to_transfer = ((hdma5_arg & 0x7F) + 1) * 16;

  for (int i = 0; i < lines_to_transfer; i++) {
    _components.mem_bus->write(
        0x8000 + addr_dest + i,
        _components.mem_bus->read<Byte>(addr_source + i));
  }

  addr_source += lines_to_transfer;
  addr_dest += lines_to_transfer;

  _hdma1 = addr_source >> 8;
  _hdma2 = addr_source & 0xFF;
  _hdma3 = addr_dest >> 8;
  _hdma4 = addr_dest & 0xFF;
  _hdma5 = 0xFF;
}

//------------------------------------------------------------------------------
void PPU::initiate_h_blank_hdma_transfer(uint8_t hdma5_arg) {
  unset_bit(hdma5_arg, 7);
  _hdma5 = hdma5_arg;
  _h_blank_hdma_src_addr = ((_hdma1 << 8) + _hdma2) & 0xFFF0;
  _h_blank_hdma_dst_addr = ((_hdma3 << 8) | _hdma4) & 0x1FF0;
}

//------------------------------------------------------------------------------
void PPU::initiate_hdma_transfer(uint8_t hdma5_arg) {
  if (test_bit(hdma5_arg, 7) == true) {
    initiate_h_blank_hdma_transfer(hdma5_arg);
  } else {
    general_purpose_hdma(hdma5_arg);
  }
}

//------------------------------------------------------------------------------
void PPU::handle_hdma_transfer(uint8_t hdma5_arg) {
  if (is_hdma_active() == false) {
    initiate_hdma_transfer(hdma5_arg);
  } else if (is_hdma_active()) {
    if (test_bit(hdma5_arg, 7) == false)
      set_bit(_hdma5, 7);
    //		else
    //			initiate_hdma_transfer(hdma5_arg);
  }
}

//------------------------------------------------------------------------------
void PPU::dma_transfer(uint16_t address) {
  uint16_t dma_addr;

  dma_addr = address << 8;
  for (int i = 0; i < 0xA0; i++) {
    _lcd_oam_ram[i] = _components.mem_bus->read<Byte>(
        dma_addr + i); // dma's are always written into OAM ram
  }
}

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
void PPU::handle_lcdc_write(uint8_t value) {
  if (test_bit(_lcdc, 7) == true && test_bit(value, 7) == false) {
    _ly = 0;
    for (int y = 0; y < LCD_HEIGHT; y++) {
      for (int x = 0; x < LCD_WIDTH; x++) {
        set_pixel(y, x, 0xFFFFFFFF);
      }
    }
    _components.driver_screen->transfer_dirty_to_clean();
  } else if (test_bit(_lcdc, 7) == false && test_bit(value, 7) == true) {
    _wait_frames_turn_on = 2;
    lyc_check();
  }
  _lcdc = value;
  setup_window();
  setup_background_data();
  setup_sprite_data();
}

//------------------------------------------------------------------------------
void PPU::lyc_check() {
  if (_ly == _lyc) {
    set_bit(_stat, 2);
    if (test_bit(_stat, 6))
      _components.interrupt_controller->request_interrupt( // valid
          _components.interrupt_controller->LCDCSI);
  } else {
    unset_bit(_stat, 2);
  }
}

//------------------------------------------------------------------------------
void PPU::write(Word address, Byte value) {
  if (address >= 0x8000 && address < 0xA000) {
    if (test_bit(_vbk, 0) == false) {
      _lcd_memory_bank_0[address - 0x8000] = value;
      return;
    } else if (test_bit(_vbk, 0) == true) {
      _lcd_memory_bank_1[address - 0x8000] = value;
      return;
    }
  }
  if (address >= 0xFE00 && address < 0xFEA0) {
    _lcd_oam_ram[address - 0xFE00] = value;
    return;
  }

  switch (address) {
  case 0xFF40:
    handle_lcdc_write(value);
    break;
  case 0xFF41:
    _stat = value; // need to set interrupt TODO

    if (test_bit(_stat, 5) == true) {
      _components.interrupt_controller->request_interrupt(
          _components.interrupt_controller->LCDCSI);
    }

    if (test_bit(_stat, 4) == true) {
      _components.interrupt_controller->request_interrupt(
          _components.interrupt_controller->LCDCSI);
    }

    if (test_bit(_stat, 3) == true) {
      _components.interrupt_controller->request_interrupt(
          _components.interrupt_controller->LCDCSI);
    }

    lyc_check();
    break;
  case 0xFF42:
    _scy = value;
    break;
  case 0xFF43:
    _scx = value;
    break;
  case 0xFF44:
    _ly = 0;
    lyc_check();
    break;
  case 0xFF45:
    _lyc = value;
    lyc_check();
    break;
  case 0xFF46:
    dma_transfer(value);
    break;
  case 0xFF47:
    _bgp = value;
    translate_dmg_palettes();
    break;
  case 0xFF48:
    _obp0 = value;
    translate_dmg_palettes();
    break;
  case 0xFF49:
    _obp1 = value;
    translate_dmg_palettes();
    break;
  case 0xFF4A:
    _wy = value;
    break;
  case 0xFF4B:
    _wx = value;
    break;
  case 0xFF4F:
    if (test_bit(_hdma5, 7) == false && _vbk != value)
      std::cerr << "changing vbk during a transfer, BAD!" << std::endl;
    _vbk = value;
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
    handle_hdma_transfer(value);
    break;
  case 0xFF68:
    _bcps = value;
    break;
  case 0xFF69:
    // std::endl;
    handle_cgb_bg_palette_write(value);
    break;
  case 0xFF6A:
    _ocps = value;
    break;
  case 0xFF6B:
    // std::endl;
    handle_cgb_obj_palette_write(value);
    break;
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
Byte PPU::read(Word address) const {
  Byte ret = 0;

  if (address >= 0x8000 && address < 0xA000) {
    if (test_bit(_vbk, 0) == false) {
      ret = _lcd_memory_bank_0[address - 0x8000];
      return (ret);
    } else if (test_bit(_vbk, 0) == true) {
      ret = _lcd_memory_bank_1[address - 0x8000];
      return (ret);
    }
  }
  if (address >= 0xFE00 && address < 0xFEA0) {
    ret = _lcd_oam_ram[address - 0xFE00];
    return (ret);
  }

  switch (address) {
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
  case 0xFF4F:
    ret = _vbk;
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
    ret = handle_cgb_bg_palette_read();
    break;
  case 0xFF6A:
    ret = _ocps;
    break;
  case 0xFF6B:
    ret = handle_cgb_obj_palette_read();
    break;
  }
  return (ret);
}

//------------------------------------------------------------------------------
uint8_t PPU::read_mem_bank(uint8_t bank, uint16_t address) {
  if (address >= 0x8000 && address <= 0x9FFF) {
    if (bank == 0)
      return (_lcd_memory_bank_0[address - 0x8000]);
    else if (bank == 1)
      return (_lcd_memory_bank_1[address - 0x8000]);
  } else {
    //		std::cerr << "WARNING : read_mem_bank called with an address not
    // included in v_bank ranges (0x8000-0x9FFF) - returning 0" << std::endl;
  }
  return (0);
}

//------------------------------------------------------------------------------
bool PPU::is_lcd_enabled() {
  if (test_bit(_lcdc, 7))
    return (true);
  return (false);
}

//------------------------------------------------------------------------------
bool PPU::is_screen_filled() {
  if (_ly == 144)
    return (true);
  return (false);
}

//------------------------------------------------------------------------------
void PPU::setup_sprite_data() {
  _sprite_data_start = 0x8000;
  _sprite_size = 8;
  if (test_bit(_lcdc, 2) == true)
    _sprite_size = 16;
}

//------------------------------------------------------------------------------
void PPU::setup_window() {
  if (test_bit(_lcdc, 5) == true)
    _windowing_on = true;
  else
    _windowing_on = false;

  if (test_bit(_lcdc, 6) == true)
    _window_chr_attr_start = 0x9C00;
  else
    _window_chr_attr_start = 0x9800;
}

//------------------------------------------------------------------------------
void PPU::setup_background_data() {
  if (test_bit(_lcdc, 4) == true) {
    _background_data_start = 0x8000;
    _unsigned_tile_numbers = true;
  } else {
    _background_data_start = 0x8800;
    _unsigned_tile_numbers = false;
  }

  if (test_bit(_lcdc, 3) == true)
    _background_chr_attr_start = 0x9C00;
  else
    _background_chr_attr_start = 0x9800;
}

//------------------------------------------------------------------------------
void PPU::setup_gb_mode() {
  uint8_t mode_flag = 0;

  if (_gb_mode == 0) {
    mode_flag = _components.mem_bus->read<Byte>(0x0143);
    if (mode_flag == 0xC0) {
      _gb_mode = MODE_GB_CGB;
    } else if (mode_flag == 0x80) {
      _gb_mode = MODE_GB_CGB; // Need to set custom palettes
    } else {
      _gb_mode = MODE_GB_DMG;
    }
  }
}

//------------------------------------------------------------------------------
void PPU::set_pixel(uint8_t y, uint8_t x, uint32_t value) {
  _components.driver_screen->set_rgba(y, x, value);
}

//------------------------------------------------------------------------------
void PPU::get_sprites_for_line() // takes up to MAX_SPRITE_PER_LINE sprites and
                                 // loads attributes in _sprites_line tab for
                                 // use later in render_sprites()
{
  uint16_t
      sprite_attributes_offset; // offset from the start of the Table in bytes
  uint16_t sprite_attributes_table_start =
      0xFE00; // start of OAM ram for sprites
  uint8_t y_pos_tmp;
  uint8_t x_pos_tmp;

  _nb_sprites = 0;

  for (int sprite = 0; sprite < 40; sprite++) {
    sprite_attributes_offset =
        sprite * 4; // 4 bytes of attributes data per sprite;
    y_pos_tmp =
        read(sprite_attributes_table_start + sprite_attributes_offset); //
    x_pos_tmp =
        read(sprite_attributes_table_start + sprite_attributes_offset + 1); //
    if (_ly + 16 >= y_pos_tmp && _ly + (16 - _sprite_size) < y_pos_tmp) {
      _sprites_line[_nb_sprites].y_pos = y_pos_tmp; // -16 !!!!
      _sprites_line[_nb_sprites].x_pos = x_pos_tmp; // -8 !!!!
      _sprites_line[_nb_sprites].tile_number = read(
          sprite_attributes_table_start + sprite_attributes_offset +
          2); // the number of the tile data we have to read for pixel values
      _sprites_line[_nb_sprites].flags =
          read(sprite_attributes_table_start + sprite_attributes_offset +
               3); // for flips and other datas
      _sprites_line[_nb_sprites].obj_number = sprite;
      if (_sprite_size == 16)
        unset_bit(_sprites_line[_nb_sprites].tile_number, 0);
      _nb_sprites++;
    }
    if (_nb_sprites >= MAX_SPRITE_PER_LINE) // this allows to only take up to 10
      // sprites by default
      return;
  }
}

//------------------------------------------------------------------------------
void PPU::replace_pixel_segment(t_pixel_segment &holder,
                                t_pixel_segment &contender) {
  holder.value = contender.value;
  holder.is_sprite = contender.is_sprite;
  holder.sprite_info = contender.sprite_info;
}

//------------------------------------------------------------------------------
void PPU::blend_pixels(t_pixel_segment &holder, t_pixel_segment &contender) {
  // note : we can assume that contender is always a sprite because we first
  // render all tiles (which cannot intersect)

  if (_gb_mode == MODE_GB_DMG) // is DMG
  {
    if (holder.is_sprite == false) // sprite VS background
    {
      if (test_bit(contender.sprite_info.flags, 7) ==
              false               // contender sprite has priority to BG
          && contender.value > 0) // == not transparent pixel | value 0 is
                                  // always transparent for sprites
      {
        replace_pixel_segment(holder, contender);
      } else if (test_bit(contender.sprite_info.flags, 7) ==
                     true // contender sprite does not have priority to BG
                 && holder.value == 0) // background is transparent;
      {
        replace_pixel_segment(holder, contender);
      }
    } else if (holder.is_sprite == true) // sprite VS sprite
    {
      if (holder.value == 0 &&
          contender.value != 0) // transparent pixel vs not transparent
        replace_pixel_segment(holder, contender);
      else if (holder.value != 0 &&
               contender.value != 0) // neither sprites pixels are transparent
      {
        if (contender.sprite_info.x_pos <
                holder.sprite_info.x_pos // comparing x_pos
            ||
            (contender.sprite_info.x_pos ==
                 holder.sprite_info
                     .x_pos // if still can't determine, use obj number instead
             && contender.sprite_info.obj_number <
                    holder.sprite_info.obj_number)) {
          replace_pixel_segment(holder, contender);
        }
      }
    }
  }

  else if (_gb_mode == MODE_GB_CGB) // is CGB
  {
    if (holder.is_sprite == false) // holder is a tile
    {
      // tiles also have priority flag in CGB
      if (test_bit(holder.sprite_info.flags, 7) ==
          false) // priority according to sprite flag
      {
        if (test_bit(contender.sprite_info.flags, 7) ==
                false               // contender sprite has priority to BG
            && contender.value > 0) // == not transparent pixel | value 0 is
                                    // always transparent for sprites
        {
          replace_pixel_segment(holder, contender);
        } else if (test_bit(contender.sprite_info.flags, 7) == true &&
                   holder.value == 0 &&
                   contender.value >
                       0) // contender sprite does not have priority to BG
        {
          replace_pixel_segment(holder, contender);
        }
      }
    } else if (holder.is_sprite == true) // same as DMG
    {
      if (holder.value == 0 &&
          contender.value != 0) // transparent pixel vs not transparent
        replace_pixel_segment(holder, contender);
      else if (holder.sprite_info.obj_number >
                   contender.sprite_info.obj_number &&
               contender.value > 0) {
        replace_pixel_segment(holder, contender);
      }
    }
  }
}

//------------------------------------------------------------------------------
void PPU::render_sprites() {
  for (int sprite = _nb_sprites - 1; sprite >= 0;
       sprite--) // up to 10 sprites on the line
  {
    uint8_t data1;
    uint8_t data2;
    bool x_flip =
        test_bit(_sprites_line[sprite].flags, 5) == true ? false : true;
    bool y_flip =
        test_bit(_sprites_line[sprite].flags, 6) == true ? false : true;

    int sprite_line =
        ((_sprites_line[sprite].y_pos) - (_ly + (16 - _sprite_size)) -
         1); // which line of the sprite does the scanline go through ?
    if (y_flip == true)
      sprite_line = (sprite_line - (_sprite_size - 1)) * (-1);
    uint16_t tile_line_data_address =
        (_sprite_data_start + (_sprites_line[sprite].tile_number * 16)) +
        (sprite_line * 2);

    if (test_bit(_sprites_line[sprite].flags, 3) == true) {
      data1 = read_mem_bank(1, tile_line_data_address);
      data2 = read_mem_bank(1, tile_line_data_address + 1);
    } else {
      data1 = read_mem_bank(0, tile_line_data_address);
      data2 = read_mem_bank(0, tile_line_data_address + 1);
    }

    for (int pixel = 0; pixel < 8; pixel++) {
      uint8_t line_pixel = pixel;
      uint8_t color_id = 0;
      t_pixel_segment contender;

      if (x_flip == true)
        line_pixel = (line_pixel - 7) * (-1);
      if (test_bit(data1, line_pixel) == true)
        color_id += 1;
      if (test_bit(data2, line_pixel) == true)
        color_id += 2;

      if (_sprites_line[sprite].x_pos + pixel - 8u < LCD_WIDTH) {
        contender.value = color_id;
        contender.is_sprite = true;
        contender.sprite_info = _sprites_line[sprite];
        blend_pixels(_pixel_pipeline[contender.sprite_info.x_pos + pixel - 8u],
                     contender);
      }
    }
  }
}

//------------------------------------------------------------------------------
uint16_t PPU::get_tile_data_address(uint8_t tileIdentifier) {
  uint8_t tile_memory_size = 16; // 2 bytes per line of pixels
  uint16_t tile_data_address;

  if (_unsigned_tile_numbers == true)
    tile_data_address = 0x8000 + (tileIdentifier * tile_memory_size);
  else {
    if (tileIdentifier <= 127)
      tile_data_address = 0x9000 + (tileIdentifier * tile_memory_size);
    else
      tile_data_address = 0x8800 + ((tileIdentifier - 128) * tile_memory_size);
  }
  return (tile_data_address);
}

//------------------------------------------------------------------------------
uint16_t PPU::determine_tile_number_address(uint8_t y_pos, uint8_t x_pos,
                                            bool in_window) {
  uint16_t tile_row;            // 32 Tiles per line
  uint16_t tile_col;            // add to Row
  uint16_t tile_number_address; // where's the tile CHR number ?

  tile_row =
      (((uint16_t)(y_pos / 8)) * 32); // (0-992) 32 tiles per 8 vertical pixels
  tile_col = x_pos / 8;               // (0-32) 1 tile per 8 horizontal pixel

  if (in_window == true)
    tile_number_address =
        _window_chr_attr_start + tile_row +
        tile_col; // 1 byte per tile number (uint8_t), just the tile number
  else
    tile_number_address = _background_chr_attr_start + tile_row + tile_col;

  return (tile_number_address);
}

//------------------------------------------------------------------------------
void PPU::render_tiles() {
  uint8_t x_pos;
  uint8_t y_pos;
  bool in_window = false;
  uint16_t tile_number_address; // from tile_number_address we get the
  // tile_number (CHR code)
  uint8_t tile_number;    // from BG display data we get tile_number
  uint16_t tile_location; // from tile_number we deduce where the data for each
  // pixel of the tile starts
  uint8_t tile_attr; // needed for CGB, same location as tile_number_address in
  // the BG display Data except in the Bank 1

  for (uint8_t i = 0; i < 160; i++) {
    if (_windowing_on == true && i + 7 >= _wx &&
        _ly >= _wy) // are we in the window and is it enabled ?
      in_window = true;

    if (in_window == true) {
      x_pos = (i + 7) - _wx;
      y_pos = _ly - _wy;
    } else {
      x_pos = _scx + i;
      y_pos = _scy + _ly;
    }

    tile_number_address =
        determine_tile_number_address(y_pos, x_pos, in_window);

    tile_number = read_mem_bank(0, tile_number_address);
    tile_attr = 0;
    if (_gb_mode == MODE_GB_CGB)
      tile_attr = read_mem_bank(1, tile_number_address);
    tile_location = get_tile_data_address(tile_number);

    uint8_t pixel_line_in_tile = y_pos % 8;
    uint8_t pixel_in_tile_line = x_pos % 8;

    if (test_bit(tile_attr, 6) ==
        true) // we check the vertical flip flag, only in CGB
      pixel_line_in_tile = 7 - pixel_line_in_tile;
    if (test_bit(tile_attr, 5) ==
        false) // we check horizontal flip flag, only in CGB
      pixel_in_tile_line = 7 - pixel_in_tile_line;

    uint16_t tile_line =
        (pixel_line_in_tile * 2); // 16 bits (2 bytes) per 8 pixels, get the
    // right horizontal line of pixels
    uint8_t first_byte = 0;
    uint8_t second_byte = 0;

    if (test_bit(tile_attr, 3) == true) {
      first_byte = read_mem_bank(1, tile_location + tile_line);
      second_byte = read_mem_bank(1, tile_location + tile_line + 1);
    } else {
      first_byte = read_mem_bank(0, tile_location + tile_line);
      second_byte = read_mem_bank(0, tile_location + tile_line + 1);
    }

    // extract the color value from each byte's corresponding bit
    uint8_t color_id = 0;
    if (test_bit(first_byte, pixel_in_tile_line) == true)
      color_id += 1;
    if (test_bit(second_byte, pixel_in_tile_line) == true)
      color_id += 2;

    // put in pipeline
    _pixel_pipeline[i].value = color_id;
    _pixel_pipeline[i].is_sprite = false;
    _pixel_pipeline[i].sprite_info.tile_number = tile_number;
    _pixel_pipeline[i].sprite_info.flags = tile_attr;
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

//------------------------------------------------------------------------------
void PPU::send_pixel_pipeline() {
  for (int i = 0; i < LCD_WIDTH; i++) {
    if (_gb_mode == MODE_GB_DMG) {
      if (_pixel_pipeline[i].is_sprite == false) {
        set_pixel(_ly, i,
                  _background_dmg_palette_translated[_pixel_pipeline[i].value]);
      } else if (_pixel_pipeline[i].is_sprite == true) {
        if (test_bit(_pixel_pipeline[i].sprite_info.flags, 4) == true)
          set_pixel(
              _ly, i,
              _sprites_dmg_palettes_translated[1][_pixel_pipeline[i].value]);
        else
          set_pixel(
              _ly, i,
              _sprites_dmg_palettes_translated[0][_pixel_pipeline[i].value]);
      }
    } else if (_gb_mode == MODE_GB_CGB) {
      // enforce_debug_palettes();

      uint8_t palette_number = 0;
      if (_pixel_pipeline[i].is_sprite == false) {
        palette_number =
            extract_value(_pixel_pipeline[i].sprite_info.flags, 0, 2);
        set_pixel(
            _ly, i,
            _background_color_palettes_translated[palette_number]
                                                 [_pixel_pipeline[i].value]);
      } else if (_pixel_pipeline[i].is_sprite == true) {
        palette_number =
            extract_value(_pixel_pipeline[i].sprite_info.flags, 0, 2);
        set_pixel(_ly, i,
                  _sprite_color_palettes_translated[palette_number]
                                                   [_pixel_pipeline[i].value]);
      }
    }
  }
  set_pixel(0, 0, 0xFF0000FF);
  set_pixel(0, 159, 0xFF0000FF);
  set_pixel(143, 159, 0xFF0000FF);
  set_pixel(143, 0, 0xFF0000FF);
}

//------------------------------------------------------------------------------
void PPU::render_scanline() {
  if (_gb_mode == MODE_GB_CGB ||
      (_gb_mode == MODE_GB_DMG && test_bit(_lcdc, 0) == true))
    render_tiles();
  if (test_bit(_lcdc, 1) == true)
    render_sprites();
  send_pixel_pipeline();
}

//------------------------------------------------------------------------------
uint8_t PPU::extract_value(uint32_t val, uint8_t bit_start,
                           uint8_t bit_end) const {
  uint8_t weight = 1;
  uint8_t ret = 0;

  while (bit_start <= bit_end) {
    if (test_bit(val, bit_start) == true)
      ret += weight;
    bit_start++;
    weight *= 2;
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
    return (0xE0F8D0FF);
  case 1:
    return (0x88C070FF);
  case 2:
    return (0x346856FF);
  case 3:
    return (0x081820FF);
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
void PPU::update_data_transfer_to_lcd_status() {
  if (_lcd_cycles >= CYCLES_DATA_TRANSFER_TO_LCD * _speed) {
    _lcd_cycles -= CYCLES_DATA_TRANSFER_TO_LCD * _speed;
    set_stat_mode(MODE_HBLANK);
    if (_wait_frames_turn_on == 0) {
      if (test_bit(_stat, 3) == true) {
        _components.interrupt_controller->request_interrupt( // valid
            _components.interrupt_controller->LCDCSI);
      }
      render_scanline();
    }
  }
}

//------------------------------------------------------------------------------
void PPU::update_oam_search_status() {
  if (_lcd_cycles >= CYCLES_OAM_SEARCH * _speed) {
    _lcd_cycles -= CYCLES_OAM_SEARCH * _speed;
    get_sprites_for_line();
    set_stat_mode(MODE_DATA_TRANSFER_TO_LCD);
  }
}

//------------------------------------------------------------------------------
void PPU::update_v_blank_status() {
  if (_lcd_cycles >= CYCLES_VBLANK * _speed) {
    _lcd_cycles -= CYCLES_VBLANK * _speed;
    if (_ly >= 153) {
      _ly = 0;
      set_stat_mode(MODE_OAM_SEARCH);
      if (test_bit(_stat, 5) == true)
        _components.interrupt_controller->request_interrupt( // valid
            _components.interrupt_controller->LCDCSI);
    } else
      _ly++;
    lyc_check();
  }
}

//------------------------------------------------------------------------------
void PPU::update_h_blank_status() {
  if (_lcd_cycles >= CYCLES_HBLANK * _speed) {
    _lcd_cycles -= CYCLES_HBLANK * _speed;
    _ly++;
    lyc_check();
    if (_ly >= 144) {
      if (_wait_frames_turn_on > 0)
        _wait_frames_turn_on--;
      _nb_frames_rendered++;
      if (_wait_frames_turn_on > 0) {
        for (uint32_t y = 0; y < LCD_HEIGHT; y++) {
          for (uint32_t x = 0; x < LCD_WIDTH; x++) {
            set_pixel(y, x, 0xFFFFFFFF);
          }
        }
      }
      _components.driver_screen->transfer_dirty_to_clean();
      set_stat_mode(MODE_VBLANK);
      _components.interrupt_controller->request_interrupt( // valid
          _components.interrupt_controller->VBI);
      if (test_bit(_stat, 4) == true)
        _components.interrupt_controller->request_interrupt( // valid
            _components.interrupt_controller->LCDCSI);
    } else {
      if (is_hdma_active() == true)
        hdma_h_blank_step(); // TODO: know when this have to happend
      set_stat_mode(MODE_OAM_SEARCH);
      if (test_bit(_stat, 5) == true)
        _components.interrupt_controller->request_interrupt( // valid

            _components.interrupt_controller->LCDCSI);
    }
  }
}

//------------------------------------------------------------------------------
void PPU::update_lcd_status() {
  //	std::cerr << "update_lcd_status called, _stat = " <<
  // std::bitset<8>(_stat)  << std::endl;
  if (get_stat_mode() == MODE_HBLANK)
    update_h_blank_status();
  else if (get_stat_mode() == MODE_VBLANK)
    update_v_blank_status();
  else if (get_stat_mode() == MODE_OAM_SEARCH)
    update_oam_search_status();
  else if (get_stat_mode() == MODE_DATA_TRANSFER_TO_LCD)
    update_data_transfer_to_lcd_status();
}

//------------------------------------------------------------------------------
void PPU::update_graphics(Word cycles) {
  setup_gb_mode();
  _lcd_cycles += cycles;
  if (is_lcd_enabled()) {
    update_lcd_status();
  } else {
    if (_lcd_cycles >= 70224 * _speed)
      _lcd_cycles -= 70224 * _speed;
  }
}
