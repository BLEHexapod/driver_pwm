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

#include "drv_pwm.h"

static volatile uint32_t *dutyCycleRegs[NUM_OF_PWM] = {
    &OC1RS,
    &OC2RS,
    &OC3RS,
    &OC4RS,
    &OC5RS
};

static volatile uint32_t *pwmRegs[NUM_OF_PWM] = {
    &OC1CON,
    &OC2CON,
    &OC3CON,
    &OC4CON,
    &OC5CON
};

struct pwmHandle {
    uint16_t dutyCycle;
    timers_t clockSource;
    pwms_t pinSel;
};

drv_pwmHandle_t drv_pwmInit(drv_pwmConfig_t *config)
{
    drv_pwmHandle_t handle = calloc(1, sizeof(struct pwmHandle));
    handle->dutyCycle = config->dutyCyle;
    handle->clockSource = config->clockSource;
    handle->pinSel = config->pinSel;
    *periodRegs[config->clockSource] = 1 / ((1 / CPUCLK) * config->frequency * 16) - 1;
    *dutyCycleRegs[config->pinSel] = config->dutyCyle;
    *pwmRegs[config->pinSel] = (1<< OC_ON) | (1<<OC_OCM1) | (1<<OC_OCM2);
    *timerRegs[config->clockSource] = (1<<TMRB_PS2) | (1<<TMRB_ON);
    return handle;
}

void drv_pwmSet(drv_pwmHandle_t handle, uint16_t dutyCycle)
{
    *dutyCycleRegs[handle->pinSel] = dutyCycle;
    handle->dutyCycle = dutyCycle;
}

uint16_t drv_pwmGet(drv_pwmHandle_t handle)
{
    return handle->dutyCycle;
}

void drv_pwmDestroy(drv_pwmHandle_t handle)
{
    *pwmRegs[handle->pinSel] &= ~((1<< OC_ON) | (1<<OC_OCM1) | (1<<OC_OCM2));
    *timerRegs[handle->clockSource] &= ~((1<<TMRB_PS2) | (1<<TMRB_ON));
    free(handle);
}
