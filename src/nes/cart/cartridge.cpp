#include "nes/cartridge.hpp"
#include "nes/mapper0.hpp"
#include "nes/mapper.hpp"

#include <fstream>
#include <iostream>   // optional for debug prints
#include <stdexcept>  // optional
#include <cstddef>    // size_t

namespace nes {

Cartridge::~Cartridge() = default;

static bool readFileToBuffer(const std::string& path, std::vector<u8>& out) {
  std::ifstream file(path, std::ios::binary);
  if (!file) return false;

  file.seekg(0, std::ios::end);
  const std::streamoff size = file.tellg();
  if (size <= 0) return false;

  out.resize(static_cast<std::size_t>(size));

  file.seekg(0, std::ios::beg);
  file.read(reinterpret_cast<char*>(out.data()), size);
  return file.good();
}

bool Cartridge::load(const std::string& path) {
  std::vector<u8> file;
  if (!readFileToBuffer(path, file)) {
    return false;
  }

  // --- 1) Basic iNES sanity checks ---
  if (file.size() < 16) return false;

  // verify "NES\x1A"
  if (!((file[0]=='N') && (file[1]=='E') && (file[2]=='S') && (file[3]==0x1A))){
    std::cerr << "Not a vaid iNES ROM\n";
    return false;
  }

  const u8 prgBanks = file[4];
  const u8 chrBanks = file[5];
  const u8 flags6   = file[6];
  const u8 flags7   = file[7];

  const bool isINES2 = ((flags7 & 0x0C) == 0x08);
  if (isINES2) {
    std::cerr << "iNES 2.0 not supported yet\n";
    return false;
  }

  // flag to check CHR ROM or CHR RAM
  chr_is_ram_ = (chrBanks == 0);

  // trainer flag (bit 2 of flags6)
  const bool hasTrainer = (flags6 & 0x04) != 0;

  const u8 mapperLow  = (flags6 >> 4) & 0x0F;
  const u8 mapperHigh = (flags7 >> 4) & 0x0F;
  mapper_id_ = (mapperHigh << 4) | mapperLow;


  // --- 2) Compute offsets and sizes ---
  std::size_t offset = 16;
  if (hasTrainer) offset += 512;

  const std::size_t prgSize = static_cast<std::size_t>(prgBanks) * 16384;
  const std::size_t chrSize = static_cast<std::size_t>(chrBanks) * 8192;

  if (offset > file.size() ||
    prgSize > file.size() - offset ||
    chrSize > file.size() - offset - prgSize) {
  std::cerr << "ROM file too small for PRG/CHR data\n";
  return false;
  }


  // --- 3) Copy PRG/CHR into vectors ---
  prg_.assign(file.begin() + offset, file.begin() + offset + prgSize);
  offset += prgSize;

  if (chrSize > 0) {
    chr_.assign(file.begin() + offset, file.begin() + offset + chrSize);
  } else {
    // CHR RAM case: allocate 8KB (common default)
    chr_.assign(8192, 0);
  }

  // --- 4) Instantiate mapper ---
  // For now only Mapper0
  if (mapper_id_ != 0) {
    // unsupported mapper
    mapper_.reset();
    return false;
  }

  mapper_ = std::make_unique<Mapper0>(prg_, chr_, chr_is_ram_);

  return true;
}

u8 Cartridge::cpuRead(u16 addr) {
  if (!mapper_) return 0;
  if (addr < 0x4020) return 0;     // cartridge region only
  return mapper_->cpuRead(addr);
}

void Cartridge::cpuWrite(u16 addr, u8 value) {
  if (!mapper_) return;
  mapper_->cpuWrite(addr, value);
}

u8 Cartridge::ppuRead(u16 addr) {
  if (!mapper_) return 0;
  addr &= 0x3FFF;                 // PPU bus is 14-bit
  if (addr > 0x1FFF) return 0;     // cart CHR region only
  return mapper_->ppuRead(addr);
}

void Cartridge::ppuWrite(u16 addr, u8 value) {
  if (!mapper_) return;
  mapper_->ppuWrite(addr, value);
}

}
