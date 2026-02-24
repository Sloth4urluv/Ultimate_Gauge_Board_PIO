#include "widget-oil-pressure.h"

// TODO - Create "static" variables for the test gauge elements so they can be updated in the update_test_gauge function, and remove the "static" keyword from the buffer variable in that function
//static int GAUGE_TICK_COUNT   = 18; // ROSS - number of ticks on the gauge, adjust as needed
const int GAUGE_TICK_COUNT   = 18; // ROSS - number of ticks on the gauge, adjust as needed
static int GAUGE_MIN           = 200; // ROSS - minimum value for the gauge, adjust as needed
static int GAUGE_MAX           = 10000; // ROSS - maximum value for the gauge, adjust as needed

static bool GAUGE_PREV[GAUGE_TICK_COUNT] = {false}; // ROSS - array to track previous state of each tick for the test gauge
//static bool GAUGE_PREV[18] = {false}; // ROSS - array to track previous state of each tick for the test gauge

lv_obj_t *test_gauge[GAUGE_TICK_COUNT];
lv_obj_t * gauge_label;

void make_oilP_gauge(uint8_t tick_count, lv_obj_t *parent, const void *start_tick_image, const void *middle_tick_image, const void *end_tick_image) {
  //test_gauge[0] = (lv_obj_t*)malloc(tick_count * sizeof(lv_obj_t*)); // allocate memory for the test gauge ticks
  gauge_label = lv_label_create(parent);
  for (int i = 0; i < tick_count; i++) {
    test_gauge[i] = lv_image_create(parent);
    
    // Assign the appropriate image based on whether it's the start tick, an intermediate tick, or the end tick
    if ((i == 0)) // Start tick
    {
      lv_image_set_src(test_gauge[i], start_tick_image);
    }
    else if (i == (tick_count - 1)) // End tick
    {
      lv_image_set_src(test_gauge[i], end_tick_image);
    }
    else // Middle ticks
    {
      lv_image_set_src(test_gauge[i], middle_tick_image);
    }
    
    // Align relative to the previous tick
    if (i == 0) {
      lv_obj_align(test_gauge[i], LV_ALIGN_CENTER, 25, 50); // ROSS - adjust alignment for new tick image
    } else {
      lv_obj_align_to(test_gauge[i], test_gauge[i-1], LV_ALIGN_CENTER, 10, 0); // TODO - Create a structure to hold the tick spacing values for different gauge configurations and use that here instead of hardcoding the spacing
    }

    // Set recolor and opacity, opacity can be set later to dim the test gauge ticks when real data is displayed
    lv_obj_set_style_image_recolor(test_gauge[i], lv_color_make(0,0,0), 0); // Set recolor to black
    lv_obj_set_style_image_recolor_opa(test_gauge[i], 128, 0); // Start with ticks dimmed (partially transparent) until real data is displayed
  }
  lv_obj_align_to(gauge_label, test_gauge[tick_count >> 1], LV_ALIGN_CENTER, 0, 20); // Position label above the first tick
  lv_label_set_text(gauge_label, "Oil Temp"); // ROSS - set initial label text
  lv_obj_set_style_text_color(gauge_label, lv_color_make(255,255,255), 0); // ROSS - set label text color to white
}

// TODO - Create a structure to pass in start, stop, play, and playback duration values for the animation
void oilP_gauge_sweep() {
  //if (GAUGE_TESTING) {
    // back and forth sweep for testing
    lv_anim_t anim_test_gauge_img;
    lv_anim_init(&anim_test_gauge_img);
    lv_anim_set_var(&anim_test_gauge_img, test_gauge);
    lv_anim_set_exec_cb(&anim_test_gauge_img, update_oilP_gauge);
    lv_anim_set_duration(&anim_test_gauge_img, 10000);
    lv_anim_set_repeat_count(&anim_test_gauge_img, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_playback_duration(&anim_test_gauge_img, 2000);
    lv_anim_set_values(&anim_test_gauge_img, (GAUGE_MIN - 200), (GAUGE_MAX + 200)); // sweep slightly beyond min and max for testing
    lv_anim_start(&anim_test_gauge_img);
  //}
}
// TODO - Create a function for animation callback that scales the animation value for the gauge
// ROSS - update Test Gauge UI with the latest value
static void update_oilP_gauge(void *obj, int32_t v) {
  static char buffer[16];
  static int32_t previous_value;
  if (abs(v - previous_value) >= 100) {
    previous_value = v;
    snprintf(buffer, sizeof(buffer), "%.1f", (v/100.0f));
    lv_label_set_text_static(gauge_label, buffer);
  }
  
  //lv_label_set_text(label_oilTemp, "Oil Temp");
  bool state = false;
  for (int i = 0; i < GAUGE_TICK_COUNT; i++) {
    bool state = (v >= (GAUGE_MIN + ((GAUGE_MAX - GAUGE_MIN) / (GAUGE_TICK_COUNT - 1)) * i));
    if (state != GAUGE_PREV[i]) { // only update if the state has changed
      if (state) {
        lv_obj_set_style_image_recolor_opa(test_gauge[i], 0, 0); // fully opaque for ticks below the current value
      } else {
        lv_obj_set_style_image_recolor_opa(test_gauge[i], 128, 0); // fully transparent for ticks above the current value
      }
      GAUGE_PREV[i] = state; // update previous state
    }
  }
}