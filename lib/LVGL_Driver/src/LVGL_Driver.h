#pragma once

#include <lvgl.h>
#include <esp_heap_caps.h>
#include "Display_ST7701.h"

#define LCD_WIDTH                     ESP_PANEL_LCD_WIDTH
#define LCD_HEIGHT                    ESP_PANEL_LCD_HEIGHT
#define BUFFER_FACTOR                 6                       // what fraction of the screen for buffer size
#define LVGL_USE_TRIPPLE_BUFFERING    1                       // set to 1 to use tripple buffering

void lvgl_flush_callback(lv_display_t *disp, const lv_area_t *area, uint8_t *color_p);
void lvgl_init(void);
