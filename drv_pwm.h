/*
 * Copyright 2016 Bart Monhemius.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef DRV_PWM_H
#define	DRV_PWM_H

#include "pinDefs.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef	__cplusplus
extern "C" {
#endif

/** Available PWM units*/
typedef enum {
    PWM_1 = 0,
    PWM_2,
    PWM_3,
    PWM_4,
    PWM_5,
    NUM_OF_PWM
} pwms_t;

typedef struct pwmHandle *drv_pwmHandle_t;

typedef struct {
    timers_t clockSource;   /**< The timer to use for PWM, note timer 1 is reserved by FreeRTOS*/
    pwms_t pinSel;          /**< The OC module to output the PWM on*/
    uint16_t dutyCyle;      /**< The initial PWM duty cycle*/
    uint16_t frequency;     /**< The PWM frequency*/
} drv_pwmConfig_t;

/**
 * @brief Initialize a PWM driver.
 * @param config Configuration structure to configure the PWM driver.
 * @return Handle object to the PWM driver.
 */
drv_pwmHandle_t drv_pwmInit(drv_pwmConfig_t *config);

/**
 * @brief Set the PWM duty cycle with 16-bits accuracy
 * @details Configures the OCxRS register of the OC unit.
 *
 * @param handle Handle to the PWM driver.
 * @param dutyCycle Duty cycle to set.
 */
void drv_pwmSet(drv_pwmHandle_t handle, uint16_t dutyCycle);

/**
 * @brief Get the last set duty cycle.
 * @details Does not return the value of the OC register.
 * @param handle Handle to the PWM driver.
 * @return Duty cycle.
 */
uint16_t drv_pwmGet(drv_pwmHandle_t handle);

/**
 * @brief Uninitialized the PWM driver and free the memory of the handle object.
 * @details Disables timer and OC unit.
 * @param handle Handle to the PWM driver to disable.
 */
void drv_pwmDestroy(drv_pwmHandle_t handle);

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_PWM_H */

