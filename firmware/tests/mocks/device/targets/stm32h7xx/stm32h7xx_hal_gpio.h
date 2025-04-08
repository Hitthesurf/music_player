#pragma once

#include "stm32h7xx_hal_def.h"

typedef struct
{
  uint32_t Pin; /*!< Specifies the GPIO pins to be configured.
                     This parameter can be any value of @ref GPIO_pins_define */

  uint32_t Mode; /*!< Specifies the operating mode for the selected pins.
                      This parameter can be a value of @ref GPIO_mode_define */

  uint32_t Pull; /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
                      This parameter can be a value of @ref GPIO_pull_define */

  uint32_t Speed; /*!< Specifies the speed for the selected pins.
                       This parameter can be a value of @ref GPIO_speed_define */

  uint32_t Alternate; /*!< Peripheral to be connected to the selected pins.
                           This parameter can be a value of @ref GPIO_Alternate_function_selection */
} GPIO_InitTypeDef;

typedef enum
{
  GPIO_PIN_RESET = 0U,
  GPIO_PIN_SET
} GPIO_PinState;

#define GPIO_PIN_0      ((uint16_t)0x0001) /* Pin 0 selected    */
#define GPIO_PIN_1      ((uint16_t)0x0002) /* Pin 1 selected    */
#define GPIO_PIN_2      ((uint16_t)0x0004) /* Pin 2 selected    */
#define GPIO_PIN_3      ((uint16_t)0x0008) /* Pin 3 selected    */
#define GPIO_PIN_4      ((uint16_t)0x0010) /* Pin 4 selected    */
#define GPIO_PIN_5      ((uint16_t)0x0020) /* Pin 5 selected    */
#define GPIO_PIN_6      ((uint16_t)0x0040) /* Pin 6 selected    */
#define GPIO_PIN_7      ((uint16_t)0x0080) /* Pin 7 selected    */
#define GPIO_PIN_8      ((uint16_t)0x0100) /* Pin 8 selected    */
#define GPIO_PIN_9      ((uint16_t)0x0200) /* Pin 9 selected    */
#define GPIO_PIN_10     ((uint16_t)0x0400) /* Pin 10 selected   */
#define GPIO_PIN_11     ((uint16_t)0x0800) /* Pin 11 selected   */
#define GPIO_PIN_12     ((uint16_t)0x1000) /* Pin 12 selected   */
#define GPIO_PIN_13     ((uint16_t)0x2000) /* Pin 13 selected   */
#define GPIO_PIN_14     ((uint16_t)0x4000) /* Pin 14 selected   */
#define GPIO_PIN_15     ((uint16_t)0x8000) /* Pin 15 selected   */
#define GPIO_PIN_All    ((uint16_t)0xFFFF) /* All pins selected */

#define GPIO_PIN_MASK   (0x0000FFFFU) /* PIN mask for assert test */

#define GPIO_MODE_INPUT MODE_INPUT /*!< Input Floating Mode                                                */
#define GPIO_MODE_OUTPUT_PP                                                                                            \
  (MODE_OUTPUT | OUTPUT_PP) /*!< Output Push Pull Mode                                              */
#define GPIO_MODE_OUTPUT_OD                                                                                            \
  (MODE_OUTPUT | OUTPUT_OD) /*!< Output Open Drain Mode                                             */
#define GPIO_MODE_AF_PP  (MODE_AF | OUTPUT_PP) /*!< Alternate Function Push Pull Mode */
#define GPIO_MODE_AF_OD  (MODE_AF | OUTPUT_OD) /*!< Alternate Function Open Drain Mode */
#define GPIO_MODE_ANALOG MODE_ANALOG /*!< Analog Mode                                                        */
#define GPIO_MODE_IT_RISING                                                                                            \
  (MODE_INPUT | EXTI_IT | TRIGGER_RISING) /*!< External Interrupt Mode with Rising edge trigger detection         */
#define GPIO_MODE_IT_FALLING                                                                                           \
  (MODE_INPUT | EXTI_IT | TRIGGER_FALLING) /*!< External Interrupt Mode with Falling edge trigger detection        */
#define GPIO_MODE_IT_RISING_FALLING                                                                                    \
  (MODE_INPUT | EXTI_IT | TRIGGER_RISING                                                                               \
    | TRIGGER_FALLING) /*!< External Interrupt Mode with Rising/Falling edge trigger detection */

#define GPIO_MODE_EVT_RISING                                                                                           \
  (MODE_INPUT | EXTI_EVT | TRIGGER_RISING) /*!< External Event Mode with Rising edge trigger detection             */
#define GPIO_MODE_EVT_FALLING                                                                                          \
  (MODE_INPUT | EXTI_EVT | TRIGGER_FALLING) /*!< External Event Mode with Falling edge trigger detection            */
#define GPIO_MODE_EVT_RISING_FALLING                                                                                   \
  (MODE_INPUT | EXTI_EVT | TRIGGER_RISING                                                                              \
    | TRIGGER_FALLING) /*!< External Event Mode with Rising/Falling edge trigger detection     */

#define GPIO_SPEED_FREQ_LOW       (0x00000000U) /*!< Low speed     */
#define GPIO_SPEED_FREQ_MEDIUM    (0x00000001U) /*!< Medium speed  */
#define GPIO_SPEED_FREQ_HIGH      (0x00000002U) /*!< Fast speed    */
#define GPIO_SPEED_FREQ_VERY_HIGH (0x00000003U) /*!< High speed    */

#define GPIO_NOPULL               (0x00000000U) /*!< No Pull-up or Pull-down activation  */
#define GPIO_PULLUP               (0x00000001U) /*!< Pull-up activation                  */
#define GPIO_PULLDOWN             (0x00000002U) /*!< Pull-down activation                */

void HAL_GPIO_Init(GPIO_TypeDef* GPIOx, const GPIO_InitTypeDef* GPIO_Init);
void HAL_GPIO_DeInit(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);

GPIO_PinState HAL_GPIO_ReadPin(const GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
HAL_StatusTypeDef HAL_GPIO_LockPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#define GPIO_MODE_Pos              0u
#define GPIO_MODE                  (0x3uL << GPIO_MODE_Pos)
#define MODE_INPUT                 (0x0uL << GPIO_MODE_Pos)
#define MODE_OUTPUT                (0x1uL << GPIO_MODE_Pos)
#define MODE_AF                    (0x2uL << GPIO_MODE_Pos)
#define MODE_ANALOG                (0x3uL << GPIO_MODE_Pos)
#define OUTPUT_TYPE_Pos            4u
#define OUTPUT_TYPE                (0x1uL << OUTPUT_TYPE_Pos)
#define OUTPUT_PP                  (0x0uL << OUTPUT_TYPE_Pos)
#define OUTPUT_OD                  (0x1uL << OUTPUT_TYPE_Pos)
#define EXTI_MODE_Pos              16u
#define EXTI_MODE                  (0x3uL << EXTI_MODE_Pos)
#define EXTI_IT                    (0x1uL << EXTI_MODE_Pos)
#define EXTI_EVT                   (0x2uL << EXTI_MODE_Pos)
#define TRIGGER_MODE_Pos           20u
#define TRIGGER_MODE               (0x7uL << TRIGGER_MODE_Pos)
#define TRIGGER_RISING             (0x1uL << TRIGGER_MODE_Pos)
#define TRIGGER_FALLING            (0x2uL << TRIGGER_MODE_Pos)
#define TRIGGER_LEVEL              (0x4uL << TRIGGER_MODE_Pos)

#define IS_GPIO_PIN_ACTION(ACTION) (((ACTION) == GPIO_PIN_RESET) || ((ACTION) == GPIO_PIN_SET))
#define IS_GPIO_PIN(__PIN__)                                                                                           \
  ((((uint32_t)(__PIN__) & GPIO_PIN_MASK) != 0x00U) && (((uint32_t)(__PIN__) & ~GPIO_PIN_MASK) == 0x00U))
#define IS_GPIO_MODE(MODE)                                                                                             \
  (((MODE) == GPIO_MODE_INPUT) || ((MODE) == GPIO_MODE_OUTPUT_PP) || ((MODE) == GPIO_MODE_OUTPUT_OD)                   \
    || ((MODE) == GPIO_MODE_AF_PP) || ((MODE) == GPIO_MODE_AF_OD) || ((MODE) == GPIO_MODE_IT_RISING)                   \
    || ((MODE) == GPIO_MODE_IT_FALLING) || ((MODE) == GPIO_MODE_IT_RISING_FALLING) || ((MODE) == GPIO_MODE_EVT_RISING) \
    || ((MODE) == GPIO_MODE_EVT_FALLING) || ((MODE) == GPIO_MODE_EVT_RISING_FALLING) || ((MODE) == GPIO_MODE_ANALOG))
#define IS_GPIO_SPEED(SPEED)                                                                                           \
  (((SPEED) == GPIO_SPEED_FREQ_LOW) || ((SPEED) == GPIO_SPEED_FREQ_MEDIUM) || ((SPEED) == GPIO_SPEED_FREQ_HIGH)        \
    || ((SPEED) == GPIO_SPEED_FREQ_VERY_HIGH))

#define IS_GPIO_PULL(PULL) (((PULL) == GPIO_NOPULL) || ((PULL) == GPIO_PULLUP) || ((PULL) == GPIO_PULLDOWN))
