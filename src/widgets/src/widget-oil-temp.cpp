#include "widget-oil-temp.h"

// TODO - Create "static" variables for the test gauge elements so they can be updated in the update_test_gauge function, and remove the "static" keyword from the buffer variable in that function

/*void test_gauge_sweep() {
  //if (GAUGE_TESTING) {
    // back and forth sweep for testing
    lv_anim_t anim_test_gauge_img;
    lv_anim_init(&anim_test_gauge_img);
    lv_anim_set_var(&anim_test_gauge_img, test_gauge);
    lv_anim_set_exec_cb(&anim_test_gauge_img, update_test_gauge);
    lv_anim_set_duration(&anim_test_gauge_img, 10000);
    lv_anim_set_repeat_count(&anim_test_gauge_img, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_playback_duration(&anim_test_gauge_img, 2000);
    lv_anim_set_values(&anim_test_gauge_img, (GAUGE_MIN - 200), (GAUGE_MAX + 200)); // sweep slightly beyond min and max for testing
    lv_anim_start(&anim_test_gauge_img);
  //}
}*/