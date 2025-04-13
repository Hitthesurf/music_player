#include "led/led_one_driver.h"
#include "mock_hal.h"
#include <gmock/gmock.h>

using namespace ::drivers;

class LedOneDriverTests : public testing::Test
{
public:
  LedOneDriverTests()
  {
    ResetHAL();
  }

protected:
  LedOneDriver m_led_driver{};
};

// HAL Init is done by auto generated code.
TEST_F(LedOneDriverTests, led_driver_toggles_correct_pin)
{
  // Given
  // When
  m_led_driver.Toggle();

  // Then
  ASSERT_EQ(1, state_HAL_GPIO_TogglePin.call_count);
  ASSERT_EQ(GPIOB, state_HAL_GPIO_TogglePin.GPIOx);
  ASSERT_EQ(GPIO_PIN_14, state_HAL_GPIO_TogglePin.GPIO_Pin);
}
