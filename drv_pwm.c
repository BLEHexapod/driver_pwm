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

struct pwmHandle {
    uint16_t dutyCycle;
    volatile uint32_t *pwmReg;
    volatile uint32_t *dutyCycleReg;
    volatile uint32_t *timerReg;
};

static void pwmGetTimer(drv_pwmHandle_t handle, drv_pwmConfig_t *config)
{
    switch(config->clockSource) {
        case TIMER_2:
            PR2 = PB_CLK / (config->frequency * PWM_TIMER_PS);
            T2CON = (1<<TMRB_ON) | (1<<TMRB_PS2);
            handle->timerReg = &T2CON;
            break;
        case TIMER_3:
            PR3 = PB_CLK / (config->frequency * PWM_TIMER_PS);
            T3CON = (1<<TMRB_ON) | (1<<TMRB_PS2);
            handle->timerReg = &T3CON;
            break;
        case TIMER_4:
            PR3 = PB_CLK / (config->frequency * PWM_TIMER_PS);
            T4CON = (1<<TMRB_ON) | (1<<TMRB_PS2);
            handle->timerReg = &T4CON;
            break;
        case TIMER_5:
            PR3 = PB_CLK / (config->frequency * PWM_TIMER_PS);
            T5CON = (1<<TMRB_ON) | (1<<TMRB_PS2);
            handle->timerReg = &T5CON;
            break;
        default:
            break;
    }
}

static void pwmGetOc(drv_pwmHandle_t handle, drv_pwmConfig_t *config)
{
    switch(config->pinSel) {
        case PWM_1:
            OC1RS = handle->dutyCycle;
            OC1CONSET = OC_ON | (1<<OC_OCM1) | (1<<OC_OCM2);
            handle->pwmReg = &OC1CON;
            handle->dutyCycleReg = &OC1RS;
            break;
        case PWM_2:
            OC2RS = handle->dutyCycle;
            OC2CONSET = (1<<15) | (1<<OC_OCM1) | (1<<OC_OCM2);
            handle->pwmReg = &OC2CON;
            handle->dutyCycleReg = &OC2RS;
            break;
        case PWM_3:
            OC3RS = handle->dutyCycle;
            OC3CONSET = (1<<15)  | (1<<OC_OCM1) | (1<<OC_OCM2);
            handle->pwmReg = &OC3CON;
            handle->dutyCycleReg = &OC3RS;
            break;
        case PWM_4:
            OC4RS = handle->dutyCycle;
            OC4CONSET = (1<<15) | (1<<OC_OCM1) | (1<<OC_OCM2);
            handle->pwmReg = &OC4CON;
            handle->dutyCycleReg = &OC4RS;
            break;
        case PWM_5:
            OC5RS = handle->dutyCycle;
            OC5CONSET = OC_ON | (1<<OC_OCM1) | (1<<OC_OCM2);
            handle->pwmReg = &OC5CON;
            handle->dutyCycleReg = &OC5RS;
            break;
        default:
            break;
    }
}

drv_pwmHandle_t drv_pwmNew(drv_pwmConfig_t *config)
{
    drv_pwmHandle_t handle = calloc(1, sizeof(struct pwmHandle));
    handle->dutyCycle = config->dutyCycle * (PR2 / 255);
    pwmGetTimer(handle, config);
    pwmGetOc(handle, config);
    return handle;
}

void drv_pwmSet(drv_pwmHandle_t handle, uint8_t dutyCycle)
{
    dutyCycle *= (PR2 / PWM_DC_MAX);
    *(handle->dutyCycleReg) = dutyCycle;
    handle->dutyCycle = dutyCycle;
}

uint8_t drv_pwmGet(drv_pwmHandle_t handle)
{
    return handle->dutyCycle;
}

void drv_pwmDestroy(drv_pwmHandle_t handle)
{
    *(handle->pwmReg) &= ~((1<< OC_ON) | (1<<OC_OCM1) | (1<<OC_OCM2));
    *(handle->timerReg) = (1<<TMRB_PS2) | (1<<TMRB_ON);
    free(handle);
}
