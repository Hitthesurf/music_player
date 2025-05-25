#include "uart/uart_driver.h"
#include "hal_handles.h"
#include "stm32h7xx_hal.h"

using namespace ::drivers;

static UartDriver* uart_driver = nullptr;

UartDriver::UartDriver(application::ICharInput& char_input) :
  m_char_input(char_input)
{
  uart_driver = this;
  HAL_UART_Receive_IT(&huart3, &m_rx_byte, 1);
}

void UartDriver::Init() const {}

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

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
  if (huart->Instance == USART3 && uart_driver != nullptr)
  {
    uart_driver->RxIsr();
  }
}
