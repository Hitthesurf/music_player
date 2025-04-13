#include "led/led_two_driver.h"
#include "mock_cmsis.h"
#include <gmock/gmock.h>

using namespace ::drivers;

class LedTwoDriverTests : public testing::Test
{
public:
  LedTwoDriverTests() :
    m_led_driver(m_led_driver)
  {
    ResetCMSIS();
  }

protected:
  LedTwoDriver m_led_driver;
};

// TODO: Add tests for bare metal init
// Need to add some for of queuing

// PB0

TEST_F(LedTwoDriverTests, led_driver_reads_correct_pin)
{
  // Given
  // When
  m_led_driver.Toggle();

  // Then
  ASSERT_EQ(1, state_READ_BIT.call_count);
  ASSERT_EQ(GPIOB->ODR, state_READ_BIT.reg);
  ASSERT_EQ(GPIO_ODR_OD0, state_READ_BIT.bit);
}

TEST_F(LedTwoDriverTests, led_driver_turns_pin_on_when_off)
{
  // Given
  state_READ_BIT.return_value = 0;

  // When
  m_led_driver.Toggle();

  // Then
  ASSERT_EQ(1, state_SET_BIT.call_count);
  ASSERT_EQ(GPIOB->BSRR, state_SET_BIT.reg);
  ASSERT_EQ(GPIO_BSRR_BS0, state_SET_BIT.bit);
}

TEST_F(LedTwoDriverTests, led_driver_turns_pin_off_when_on)
{
  // Given
  state_READ_BIT.return_value = GPIO_ODR_OD0;

  // When
  m_led_driver.Toggle();

  // Then
  ASSERT_EQ(1, state_SET_BIT.call_count);
  ASSERT_EQ(GPIOB->BSRR, state_SET_BIT.reg);
  ASSERT_EQ(GPIO_BSRR_BR0, state_SET_BIT.bit);
}
