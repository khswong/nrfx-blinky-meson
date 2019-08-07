/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * (C) Copyright 2019
 * Jeremy Grosser <jeremy@synack.me>
 * All Rights Reserved.
 *
 * Example using nrfx to blink an LED on the BBC micro:bit
 */

#include <nrfx_rtc.h>
#include <nrfx_clock.h>
#include <nrf_gpio.h>

/*
 * These pins correspond to the top left LED on the BBC micro:bit
 */
#define ROW1    NRF_GPIO_PIN_MAP(0,13)
#define COL1    NRF_GPIO_PIN_MAP(0,4)

static const nrfx_rtc_t RTC0 = NRFX_RTC_INSTANCE(0);
static const nrfx_rtc_config_t RTC0_CONFIG = NRFX_RTC_DEFAULT_CONFIG;
static volatile uint32_t ticks;

void rtc0_event(nrfx_rtc_int_type_t int_type) {
    if(int_type == NRFX_RTC_INT_TICK) {
        ticks++;
    }
}

int main(int argc, char **argv) {
    nrf_gpio_cfg_output(ROW1);
    nrf_gpio_cfg_output(COL1);

    nrf_gpio_pin_set(ROW1);

    nrfx_clock_lfclk_start();

    if(nrfx_rtc_init(&RTC0, &RTC0_CONFIG, rtc0_event) != NRFX_SUCCESS) {
        return 1;
    }

    nrfx_rtc_tick_enable(&RTC0, true);
    nrfx_rtc_enable(&RTC0);

    while(1) {
        /* Sleep until we get an interrupt */
        __WFI();

        /* 
         * The RTC is configured for 16 Hz operation in
         * ../include/nrfx_config.h. We toggle every 8 Hz, meaning that the LED
         * appears to be blinking at 4 Hz
         */
        if(ticks & 1) {
            nrf_gpio_pin_toggle(COL1);
        }
    }

    return 0;
}
