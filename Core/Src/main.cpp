#include "main.h"

#include "ST-LIB.hpp"
#include "ErrorHandler/ErrorHandler.hpp"

#include "simulator.h"

constexpr auto led_req = ST_LIB::DigitalOutputDomain::DigitalOutput(ST_LIB::PB0);

using MainBoard = ST_LIB::Board<ST_LIB::DefaultFaultPolicy, led_req>;
auto& led_instance = MainBoard::instance_of<led_req>();

#ifdef SIMULATOR
extern "C" void Board_init(void *mem)
#else
extern "C" void BoardInit()
#endif
{
#ifdef SIMULATOR
  Simulator_InitMemory(mem);
#endif

  MainBoard::init();
  // Any other init stuff you might want here...
}

extern "C" void Board_update(void)
{
  led_instance.toggle();
}

#ifndef SIMULATOR
int main(void) {
  while (1) {
    Board_update();
  }
}
#endif

extern "C" void Error_Handler(void) {
    PANIC("HAL error handler triggered");
    while (1) {
    }
}
