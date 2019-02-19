#ifndef SOUNDCHANNEL_HPP
#define SOUNDCHANNEL_HPP

#include "src/Fwd.hpp"
#include "src/IReadWrite.hpp"

#include <vector>

namespace sound {

class IModulationUnit;

class SoundChannel : public IReadWrite {
 private:
  using ModUnitPtr = IModulationUnit*;
  std::vector<ModUnitPtr> _modulation_units;

  virtual void do_trigger() = 0;

 protected:
  int p_output_volume = 0;
  bool p_muted = false;
  bool p_enabled = true;

  void bind_module(ModUnitPtr module) { _modulation_units.push_back(module); }
  SoundChannel() = default;

 public:
  virtual ~SoundChannel() = default;

  void update(unsigned int modulation_unit_step);
  void trigger();

  int get_output() const {
    return (p_muted or not p_enabled) ? 0 : p_output_volume;
  }
  bool is_enabled() const { return p_enabled; }
  void enable(bool v) { p_enabled = v; }
};

}  // namespace sound

#endif  // SOUNDCHANNEL_HPP
