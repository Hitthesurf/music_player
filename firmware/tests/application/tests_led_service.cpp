#include "led/led_service.h"
#include "led/mock_led_driver.h"
#include <gmock/gmock.h>

using namespace ::application;
using namespace ::tests;

class LedServiceTests : public testing::Test
{
public:
  LedServiceTests() :
    m_led_service(m_led_one_driver, m_led_two_driver)
  {
  }

protected:
  MockLedDriver m_led_one_driver{};
  MockLedDriver m_led_two_driver{};
  LedService m_led_service;
};

TEST_F(LedServiceTests, init_calls_the_init_driver)
{
  // Given
  // When
  m_led_service.Init();

  // Then
  ASSERT_EQ(1, m_led_one_driver.state.init_call_count);
  ASSERT_EQ(1, m_led_two_driver.state.init_call_count);
}

TEST_F(LedServiceTests, run_task_calls_the_toggle_driver)
{
  // Given
  // When
  m_led_service.RunTask();

  // Then
  ASSERT_EQ(1, m_led_one_driver.state.toggle_call_count);
  ASSERT_EQ(1, m_led_two_driver.state.toggle_call_count);
}
