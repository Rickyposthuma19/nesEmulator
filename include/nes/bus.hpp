#pragma once
#include "nes/types.hpp"
#include <array>
#include <memory>

namespace nes {
class CPU;
class PPU;
class APU;
class Cartridge;

class Bus {
public:
  void attach(CPU* cpu, PPU* ppu, APU* apu, Cartridge* cart);

  u8  read(u16 addr);
  void write(u16 addr, u8 value);

  // 2KB internal RAM mirrored through $1FFF
  std::array<u8, 2048> ram{};

private:
  CPU* cpu_ = nullptr;
  PPU* ppu_ = nullptr;
  APU* apu_ = nullptr;
  Cartridge* cart_ = nullptr;
};
}
