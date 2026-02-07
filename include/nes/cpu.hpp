#pragma once
#include "nes/types.hpp"

namespace nes {

class Bus;

class CPU {
public:
  CPU() = default;

  void connect(Bus* bus);
  void reset();

  // Phase 1: instruction-based
  void stepInstruction();

  // Phase 2+: cycle-based
  void tick();

  // Interrupts
  void nmi();
  void irq();

  // Debug
  u16 pc() const { return pc_; }

private:
  Bus* bus_ = nullptr;

  // Registers
  u8  a_ = 0;
  u8  x_ = 0;
  u8  y_ = 0;
  u8  sp_ = 0xFD;
  u8  p_  = 0x24;   // default NES power-on-ish
  u16 pc_ = 0;

  // Cycle engine
  u8  opcode_ = 0;
  u8  cycles_left_ = 0;

  // Helpers (you implement)
  u8  read(u16 addr);
  void write(u16 addr, u8 value);
};

}
