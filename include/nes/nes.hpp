#pragma once
#include <string>
#include <cstddef>

namespace nes {

class NES {
public:
  bool loadROM(const std::string& path);

  // eventually: one CPU cycle tick; for now just run some steps
  void reset();
  void runFrames(std::size_t frames);

private:
  // forward-declared in .cpp
  struct Impl;
  Impl* impl_;
};

}
