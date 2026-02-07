#pragma once
#include "nes/types.hpp"

namespace nes {

class Bus;

class APU {
public:
  void connect(Bus* bus);
  void reset();

  u8  cpuRead(u16 addr);
  void cpuWrite(u16 addr, u8 value);

  // Called once per CPU cycle
  void tick();

  bool irqRequested() const;

private:
  Bus* bus_ = nullptr;

  bool irq_ = false;
};

}
