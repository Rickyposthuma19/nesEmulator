#pragma once

#include "nes/mapper.hpp"
#include "nes/types.hpp"
#include <vector>
#include <cstddef>

namespace nes {

class Mapper0 final : public Mapper {
public:
  Mapper0(std::vector<u8>& prg_, std::vector<u8>& chr_, bool chrIsRam);

  u8  cpuRead(u16 addr) override;
  void cpuWrite(u16 addr, u8 value) override;

  u8  ppuRead(u16 addr) override;
  void ppuWrite(u16 addr, u8 value) override;

private:
  std::vector<u8>& prg_;
  std::vector<u8>& chr_;
  bool chr_is_ram_ = false;
  bool mirror_16k_ = false;
};

} // namespace nes
