#include "nes/mappers/mapper0.hpp"

namespace nes {

Mapper0::Mapper0(const std::vector<u8>& prg, const std::vector<u8>& chr)
  : prg_(prg), chr_(chr) {

  // Mapper0 PRG is either 16KB or 32KB
  mirror_16k_ = (prg_.size() == 16384);
}

u8 Mapper0::cpuRead(u16 addr) {
  // CPU sees PRG at $8000-$FFFF
  if (addr < 0x8000) {
    return 0;
  }

  std::size_t index = 0;

  if (mirror_16k_) {
    // TODO: map $8000-$FFFF onto 0x0000-0x3FFF
    // index = (addr - 0x8000) & 0x3FFF;
  } else {
    // TODO: map $8000-$FFFF onto 0x0000-0x7FFF
    // index = (addr - 0x8000);
  }

  // TODO: bounds safety (optional)
  return prg_[index];
}

void Mapper0::cpuWrite(u16 addr, u8 value) {
  (void)addr;
  (void)value;
  // NROM PRG is ROM; usually ignore writes
}

}
