#ifndef FADEEFFECT_HPP
#define FADEEFFECT_HPP

class FadeEffect {
 public:
  enum class Type { Ascending, Descending };

 private:
  static constexpr unsigned max_divider = 100;

  unsigned _divider = 1;
  unsigned _total_steps = 0;
  unsigned _steps_left = 0;
  Type _way = Type::Ascending;
  bool _done = true;

 public:
  FadeEffect() = default;
  FadeEffect(unsigned steps, Type way = Type::Ascending)
      : _total_steps(steps),
        _steps_left(steps / max_divider),
        _way(way),
        _done(false) {
    if (way == Type::Ascending)
      _divider = max_divider;
    else
      _divider = 1.;
  }

  void step() {
    if (done()) return;
    if (_steps_left-- == 0) {
      _steps_left = _total_steps / max_divider;
      if (_way == Type::Ascending) {
        --_divider;
        if (_divider <= 1) _done = true;
      } else {
        ++_divider;
        if (_divider >= max_divider) _done = true;
      }
    }
  }

  float apply(float target) const { return target / _divider; }
  bool done() const { return _done; }
};

#endif  // FADEEFFECT_HPP
