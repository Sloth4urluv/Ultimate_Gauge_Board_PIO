#pragma once

#include <Arduino.h>
#include <lvgl.h>

// TODO = Create functions to set the static variables
// TODO - Create function to reallocate the test gauge ticks if the tick count changes, and update the make_test_gauge function to use that function instead of malloc

/**
 * @brief Creates an oil pressure gauge with the specified number of ticks and tick images
 * @param tick_count The number of ticks to create for the gauge
 * @param parent The parent LVGL object to which the gauge will be added
 * @param start_tick_image The image to use for the start tick (minimum value)
 * @param middle_tick_image The image to use for the middle ticks (intermediate values)
 * @param end_tick_image The image to use for the end tick (maximum value)
 */
void make_oilP_gauge(uint8_t tick_count, lv_obj_t *parent, const void *start_tick_image, const void *middle_tick_image, const void *end_tick_image);

/**
 * @brief Animates the oil pressure gauge with a back and forth sweep for testing purposes
 * This function creates an animation that sweeps the gauge needle back and forth across the range of
 */
void oilP_gauge_sweep();

/**
 * @brief Animation callback function to update the oil pressure gauge UI with the latest value
 * This function is called by the LVGL animation system and updates the visibility of the gauge ticks based on the current value of the gauge.
 * It uses a static buffer to store the previous value and only updates the UI if the value has changed by a certain threshold to reduce unnecessary updates.
 * @param obj The LVGL object being animated (in this case, the array of gauge ticks)
 * @param v The current value of the animation, which should correspond to the current value of the gauge being displayed
 */
static void update_oilP_gauge(void *obj, int32_t v);