#include "nes/cartridge.hpp"
#include <iostream>

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Usage: nes <rom.nes>\n";
    return 1;
  }

  nes::Cartridge cart;
  if (!cart.load(argv[1])) {
    std::cerr << "Failed to load ROM.\n";
    return 1;
  }

  // TODO: read reset vector (0xFFFC low, 0xFFFD high) and print
  std::cout << "ROM loaded.\n";
  std::size_t prgSizeBytes() const;
  std::size_t chrSizeBytes() const;
  u8 mapperId() const;
  return 0;
}
