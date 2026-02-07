#pragma once
#include "nes/types.hpp"

namespace nes {

class Bus;

class PPU {
public:
  void connect(Bus* bus);
  void reset();

  // CPU-facing registers ($2000-$2007)
  u8  cpuRead(u16 addr);
  void cpuWrite(u16 addr, u8 value);

  // Called once per PPU cycle
  void tick();

  bool nmiRequested() const;

private:
  Bus* bus_ = nullptr;

  // Registers
  u8 ctrl_   = 0;
  u8 mask_   = 0;
  u8 status_ = 0;
  u8 oam_addr_ = 0;

  // VRAM addressing
  u16 v_ = 0;   // current VRAM address
  u16 t_ = 0;   // temporary VRAM address
  u8  fine_x_ = 0;
  bool write_latch_ = false;

  // Timing
  int scanline_ = 0;
  int dot_ = 0;
};

}
