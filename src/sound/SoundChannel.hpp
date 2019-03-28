#ifndef SOUNDCHANNEL_HPP
#define SOUNDCHANNEL_HPP

#include "src/Fwd.hpp"
#include "src/IReadWrite.hpp"
#include "src/sound/AudioInterface.hpp"

#include <cassert>
#include <vector>

namespace sound {

class IModulationUnit;

class SoundChannel : public IReadWrite {
 private:
  using ModUnitPtr = IModulationUnit*;
  std::vector<ModUnitPtr> _modulation_units;
  unsigned _summed_volumes = 0;
  unsigned _summed_volumes_nb = 0;

  virtual void do_trigger() = 0;
  virtual void do_update() = 0;
  virtual void do_clear() = 0;

 protected:
  Byte p_output_volume = 0;
  bool p_enabled = false;
  Byte p_speed = 1;

  SoundChannel() = default;
  void bind_module(ModUnitPtr module) { _modulation_units.push_back(module); }

 public:
  static constexpr Byte MaxVolume = 0xf;
  virtual ~SoundChannel() = default;

  void update_modules(unsigned int modulation_unit_step);
  void update();
  void trigger();
  void clear();

  void downsample() {
    if (_summed_volumes_nb == 0)
      p_output_volume = 0;
    else
      p_output_volume = _summed_volumes / _summed_volumes_nb;
    _summed_volumes = 0;
    _summed_volumes_nb = 0;
  }

  void set_speed(Byte value) { p_speed = value; }

  AudioInterface::Sample get_output(Byte volume) const {
    if (not p_enabled) return 0.f;
    assert(volume);
    Byte out = p_output_volume * volume;
    AudioInterface::Sample ret =
        out / (static_cast<AudioInterface::Sample>(MaxVolume * volume) / 2.f) -
        1.f;
    assert(ret <= 1.f and ret >= -1.f);
    return ret;
  }

  Byte get_raw_volume() const { return p_output_volume; }

  bool is_enabled() const { return p_enabled; }
  void enable(bool v) { p_enabled = v; }
};

}  // namespace sound

#endif  // SOUNDCHANNEL_HPP
