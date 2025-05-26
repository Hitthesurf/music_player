#include "pwm/pwm_driver.h"
#include "hal_handles.h"

using namespace ::drivers;

PWMDriver::PWMDriver() :
  m_timer_aux_pwm(&htim4),
  m_timer_load_audio(&htim17)
{
}

void PWMDriver::Config(size_t sample_rate)
{
  // ... prescaler configured in .ioc to give micro second timer ticks
  const size_t timer_ticks_per_second = 1000000;
  const size_t micro_seconds_per_sample = timer_ticks_per_second / sample_rate;

  constexpr size_t prescaler_value = 4;
  constexpr size_t audio_resolution_8_bit = 256;
  __HAL_TIM_SET_PRESCALER(m_timer_aux_pwm, prescaler_value - 1);
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
  __HAL_TIM_SET_AUTORELOAD(m_timer_aux_pwm, audio_resolution_8_bit - 1);

  // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
  __HAL_TIM_SET_AUTORELOAD(m_timer_load_audio, micro_seconds_per_sample - 1);
}

void PWMDriver::LoadLeft(uint8_t value)
{
  // Save value to static var
  m_sample_left = value;
}

void PWMDriver::LoadRight(uint8_t value) {}

void PWMDriver::Play()
{
  HAL_TIM_Base_Start_IT(m_timer_aux_pwm);
  HAL_TIM_PWM_Start(m_timer_aux_pwm, m_left_channel);
  // HAL_TIM_PWM_Start(timerAuxPWM, RIGHT_CHANNEL);
  //  HAL_TIM_PWM_Start(timerBuzzerPWM, TIM_CHANNEL_1);
  HAL_TIM_Base_Start_IT(m_timer_load_audio);
}

void PWMDriver::Stop()
{
  HAL_TIM_Base_Stop_IT(m_timer_aux_pwm);
  HAL_TIM_PWM_Stop(m_timer_aux_pwm, m_left_channel);
  // HAL_TIM_PWM_Stop(timerAuxPWM, RIGHT_CHANNEL);
  // HAL_TIM_PWM_Stop(timerBuzzerPWM, TIM_CHANNEL_1);
  HAL_TIM_Base_Stop_IT(m_timer_load_audio);
}

void PWMDriver::TimerAuxPwmPeriodElapsedCallback()
{
  __HAL_TIM_SET_COMPARE(m_timer_aux_pwm, m_left_channel, m_sample_left);
}
