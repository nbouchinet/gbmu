#include <cstdint>
#include <string>

using Byte = uint8_t;
using Word = uint16_t;

union Register {
  Word word;
  struct {
    Byte low, high;
  };
};

Byte read_byte(Word addr);
void write_byte(Word addr, Byte v);
bool test_bit(uint8_t bit, Byte b);
void set_bit(uint8_t bit, Byte& b);
void reset_bit(uint8_t bit, Byte& b);

class Core {
 public:
  enum Flags { CY = 4, H, N, Z };
  static constexpr uint8_t Z_FLAG = 0x80;
  static constexpr uint8_t N_FLAG = 0x40;
  static constexpr uint8_t H_FLAG = 0x20;
  static constexpr uint8_t CY_FLAG = 0x10;

 private:
  Register _pc;
  Register _sp;
  Register _af;
  Register _bc;
  Register _de;
  Register _hl;
  Byte _flags;
  Word _clock;

  template <typename T>
  void instr_ld(T& a, T b) {
    a = b;
  }
  void instr_ldd(Byte&, Byte);
  void instr_ldi(Byte&, Byte);
  void instr_ldhl(Byte a);
  void instr_push(Word v);
  void instr_pop(Word& dest);

  template <typename T>
  void instr_add(T& a, T b) {
    _flags = 0u;
    if (test_bit())
    a += b;
    if (a == 0u) set_bit(Z, _flags);
  }
  void instr_adc(Byte&, Byte);
  void instr_sub(Byte&, Byte);
  void instr_sbc(Byte&, Byte);
  void instr_and(Byte&, Byte);
  void instr_or(Byte&, Byte);
  void instr_xor(Byte&, Byte);

  template <typename T>
  void instr_inc(T& t) {
    ++t;
  }
  template <typename T>
  void instr_dec(T& t) {
    --t;
  }

  void instr_daa();
  void instr_cpl();
  void instr_ccf();
  void instr_scf();
  void instr_nop();
  void instr_halt();
  void instr_stop();
  void instr_di();
  void instr_ei();
  void instr_rlca();
  void instr_rla();
  void instr_rrca();
  void instr_rra();

  enum class JumpCondition { None, NonZero, Zero, NonCarry, Carry };
  void instr_jp(JumpCondition, Word);
  void instr_jr(JumpCondition, Word);
  void instr_call(JumpCondition, Word);
  void instr_ret(JumpCondition);
  void instr_reti();

  void instr_rst(Byte);

  void instr_rlc(Byte&);
  void instr_rl(Byte&);
  void instr_rrc(Byte&);
  void instr_rr(Byte&);
  void instr_sla(Byte&);
  void instr_sra(Byte&);
  void instr_swap(Byte&);
  void instr_srl(Byte&);
  void instr_bit(Byte&, Byte);
  void instr_set(Byte&, Byte);
  void instr_res(Byte&, Byte);

  void exec_instruction(std::function<void(void)> instr, Byte clock_cycles) {
    instr();
    _clock += clock_cycles;
  }

  void exec_instruction(std::function<void(Byte&)> instr, Word addr,
                        Byte clock_cycles) {
    Byte b = read_byte(addr);
    instr(b);
    write_byte(addr, b);
    _clock += clock_cycles;
  }

 public:
  using Iterator = std::string::iterator;
  void execute(Iterator& it) {
    Iterator original_it = it;
    switch (*it++) {
#include "instructions.inc"
      default:
        assert(false);
        break;
    }
    _pc.word += it - original_it;
  }
};
