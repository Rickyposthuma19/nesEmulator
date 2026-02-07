#pragma once
#include "nes/types.hpp"

namespace nes {

class Mapper {
public:
  virtual ~Mapper() = default;

  virtual u8  cpuRead(u16 addr) = 0;
  virtual void cpuWrite(u16 addr, u8 value) = 0;
};

}
