#include "uart/uart_driver.h"
#include "hal_handles.h"
#include "stm32h7xx_hal.h"

using namespace ::drivers;

UartDriver::UartDriver() = default;

void UartDriver::Init() const {}

void UartDriver::Output(char text)
{
  const uint8_t data = static_cast<uint8_t>(text);
  HAL_UART_Transmit(&huart3, &data, 1, HAL_MAX_DELAY); // Need to turn into interrupt based.
                                                       // But if low prority can get away with it
}
