cmake_minimum_required(VERSION 3.20)
project(nes_emulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(nes
  src/main.cpp
  src/nes/nes.cpp
  src/nes/bus.cpp
  src/nes/cpu/cpu.cpp
  src/nes/ppu/ppu.cpp
  src/nes/apu/apu.cpp
  src/nes/io/controller.cpp
  src/nes/cart/cartridge.cpp
  src/nes/cart/mapper.cpp
  src/nes/cart/mappers/mapper0.cpp
)

target_include_directories(nes PRIVATE include)

# Helpful warnings
if (MSVC)
  target_compile_options(nes PRIVATE /W4 /permissive-)
else()
  target_compile_options(nes PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Optional: make asserts available even in Release if you want
# target_compile_definitions(nes PRIVATE $<$<CONFIG:Release>:NDEBUG=0>)
