#pragma once
#include "nes/types.hpp"

namespace nes {

class Controller {
public:
  void write(u8 value);
  u8 read();

  void setButtonState(int button, bool pressed);

private:
  u8 shift_ = 0;
  u8 buttons_ = 0;
};

}
