#pragma once
#include "nes/mapper.hpp"
#include <vector>

namespace nes {

class Mapper0 : public Mapper {
public:
  Mapper0(const std::vector<u8>& prg, const std::vector<u8>& chr);

  u8  cpuRead(u16 addr) override;
  void cpuWrite(u16 addr, u8 value) override;

private:
  const std::vector<u8>& prg_;
  const std::vector<u8>& chr_;
  bool mirror_16k_ = false;
};

}
