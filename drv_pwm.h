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

//#ifdef	__cplusplus
//extern "C" {
//#endif

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
    timers_t clockSource; 
    pwms_t pinSel;
    uint16_t dutyCyle;
    uint16_t frequency;
} drv_pwmConfig_t;

drv_pwmHandle_t drv_pwmInit(drv_pwmConfig_t *config);

void drv_pwmSet(drv_pwmHandle_t handle, uint16_t dutyCycle);

uint16_t drv_pwmGet(drv_pwmHandle_t handle);

void drv_pwmDestroy(drv_pwmHandle_t handle);

//#ifdef	__cplusplus
//}
//#endif

#endif	/* DRV_PWM_H */

