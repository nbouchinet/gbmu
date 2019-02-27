#ifndef SOUNDCHANNEL_HPP
#define SOUNDCHANNEL_HPP

#include "src/Fwd.hpp"
#include "src/IReadWrite.hpp"

#include <vector>
#include <cassert>

namespace sound {

class IModulationUnit;

class SoundChannel : public IReadWrite {
 private:
  using ModUnitPtr = IModulationUnit*;
  std::vector<ModUnitPtr> _modulation_units;

  virtual void do_trigger() = 0;
  virtual void do_update() = 0;

 protected:
  Byte p_output_volume = 0;
  bool p_enabled = true;

  void bind_module(ModUnitPtr module) { _modulation_units.push_back(module); }
  SoundChannel() = default;

 public:
  static constexpr Byte MaxVolume = 0xf;
  virtual ~SoundChannel() = default;

  void update_modules(unsigned int modulation_unit_step);
  void update();
  void trigger();

  float get_output() const {
    if (not p_enabled)
      return 0.f;
    assert(p_output_volume <= MaxVolume);
    return p_output_volume / (static_cast<float>(MaxVolume) / 2.f) - 1.f;
  }
  bool is_enabled() const { return p_enabled; }
  void enable(bool v) { p_enabled = v; }
};

}  // namespace sound

#endif  // SOUNDCHANNEL_HPP
