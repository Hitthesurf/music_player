#pragma once

#include "i_song_driver.h"
#include "stm32h7xx_hal.h"
#include <cstdint>

namespace drivers
{

class PWMDriver : public ISongDriver
{
public:
  PWMDriver();
  void Config(size_t sample_rate) override;
  void LoadLeft(uint8_t value) override;
  void LoadRight(uint8_t value) override;
  void Play() override;
  void Stop() override;
  void TimerAuxPwmPeriodElapsedCallback() override;

private:
  TIM_HandleTypeDef* m_timer_aux_pwm;
  TIM_HandleTypeDef* m_timer_load_audio;
  const uint32_t m_left_channel = TIM_CHANNEL_3;
  uint8_t m_sample_left = 0;
  static PWMDriver* s_instance;
};

}
