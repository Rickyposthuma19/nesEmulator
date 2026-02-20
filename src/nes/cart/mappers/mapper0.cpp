#include "nes/mapper0.hpp"

namespace nes {

Mapper0::Mapper0(std::vector<u8>& prg_, std::vector<u8>& chr_, bool chrIsRam)
  : prg_(prg_), chr_(chr_) {

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
    index = (addr - 0x8000) & 0x3FFF;
  } else {
    index = (addr - 0x8000);
  }

  // bounds safety
  if (index >= prg_.size()) return 0;

  return prg_[index];
}

void Mapper0::cpuWrite(u16 addr, u8 value) {
  (void)addr;
  (void)value;
  // NROM PRG is ROM; usually ignore writes
}

u8 Mapper0::ppuRead(u16 addr) {
// range check
if (addr >= 0x2000) return 0;

std::size_t index = addr;

// sanity check
if (index < chr_.size())
    return chr_[index];
else
    return 0;
}

void Mapper0::ppuWrite(u16 addr, u8 value){
// range check
if (addr >= 0x2000) return;

std::size_t index = addr;

// only allow writes when cartridge uses CHR RAM
if (chr_is_ram_ == false) 
  return;

chr_[index] = value;
}


}
