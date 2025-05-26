#include "uart/uart_driver.h"
#include "hal_handles.h"
#include "stm32h7xx_hal.h"

using namespace ::drivers;

UartDriver::UartDriver(application::ICharInput& char_input) :
  m_char_input(char_input)
{
  HAL_UART_Receive_IT(&huart3, &m_rx_byte, 1);
}

void UartDriver::Init() const
{
  // Empty as init is auto generated
  // Needed for bare metal approach
}

void UartDriver::Output(char text)
{
  const uint8_t data = static_cast<uint8_t>(text);
  HAL_UART_Transmit(&huart3, &data, 1, HAL_MAX_DELAY); // Need to turn into interrupt based.
                                                       // But if low prority can get away with it
}

void UartDriver::RxIsr()
{
  m_char_input.Input(static_cast<char>(m_rx_byte));
  HAL_UART_Receive_IT(&huart3, &m_rx_byte, 1);
}
