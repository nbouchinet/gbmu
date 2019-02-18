#ifndef APU_HPP
#define APU_HPP

#include "src/Fwd.hpp"
#include "src/IReadWrite.hpp"

#include <vector>
#include <memory>

#define CPU_FREQ (4194304)

namespace sound {

class SoundChannel;

class APU : public IReadWrite {
 private:
  struct MemoryRangedChannel {
    Word begin, end;
    std::unique_ptr<SoundChannel> channel;
  };
  std::vector<MemoryRangedChannel> _channels;
  int _cpu_cycles = CPU_FREQ / 512;
  unsigned int _modulation_units_steps = 0;

 public:
  APU();

  void update_clock();
  Byte read(Word addr) const override;
  void write(Word addr, Byte) override;
};
}  // namespace sound

#endif  // APU_HPP
