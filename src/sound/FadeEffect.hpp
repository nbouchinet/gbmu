#ifndef FADEEFFECT_HPP
#define FADEEFFECT_HPP

class FadeEffect {
 public:
  enum class Type { Ascending, Descending };

 private:
  static constexpr float max_divider = 10.;

  float _divider = 1.;
  float _divider_step = 0.;
  Type _way = Type::Ascending;
  bool _done = true;

 public:
  FadeEffect() = default;
  FadeEffect(unsigned steps, Type way = Type::Ascending)
      : _divider_step(1. / (steps / max_divider)), _way(way), _done(false) {
    if (way == Type::Ascending)
      _divider = max_divider;
    else
      _divider = 1.;
  }

  void step() {
    if (done()) return;
    if (_way == Type::Ascending) {
      _divider -= _divider_step;
      if (_divider <= 1.) _done = true;
    } else {
      _divider += _divider_step;
      if (_divider >= max_divider) _done = true;
    }
  }

  float apply(float target) const { return target / _divider; }
  bool done() const { return _done; }
};

#endif  // FADEEFFECT_HPP
