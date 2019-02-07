#ifndef IREADWRITE_HPP
#define IREADWRITE_HPP

#include "src/Fwd.hpp"

class IReadWrite {
  public:
    virtual ~IReadWrite() = default;
    virtual Byte read(Word addr) const = 0;
    virtual void write(Word addr, Byte) = 0;
};

#endif // IREADWRITE_HPP
