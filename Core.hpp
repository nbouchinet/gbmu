#include <cstdint>
#include <string>

using Byte = uint8_t;
using Word = uint16_t;
using Flags = Byte;

union Register {
  Word word;
  struct {
    Byte low, high;
  };
};

Byte read_byte(Word addr);
void write_byte(Word addr, Byte v);

class Core {
 private:
  Register _pc;
  Register _sp;
  Register _af;
  Register _bc;
  Register _de;
  Register _hl;
  Flags _flags;
  Word _clock;

  void instr_ld(Byte& a, Byte b);
  void instr_ld(Word& a, Word b);
  void instr_ldd(Word a, Byte b);
  void instr_ldd(Byte a, Word b);
  void instr_ldi(Byte a, Word b);
  void instr_ldhl(Byte a);
  void instr_push(Word v);
  void instr_pop(Word& dest);

  void instr_add(Byte&, Byte);
  void instr_adc(Byte&, Byte);
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
    Iterator original_i = it;
    switch (*it++) {
#include "instructions.inc"
    }
    _pc.word += i - original_i;
  }
};
