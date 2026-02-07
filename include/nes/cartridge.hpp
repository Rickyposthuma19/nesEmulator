#pragma once
#include "nes/types.hpp"
#include "nes/mapper.hpp"
#include <string>
#include <vector>
#include <memory>

namespace nes {

class Mapper;

class Cartridge {
public:
  Cartridge() = default;
  ~Cartridge(); 

  bool load(const std::string& path);

  u8  cpuRead(u16 addr);
  void cpuWrite(u16 addr, u8 value);

private:
  std::vector<u8> prg_;
  std::vector<u8> chr_;

  u8 mapper_id_ = 0;
  std::unique_ptr<Mapper> mapper_;
};

}
