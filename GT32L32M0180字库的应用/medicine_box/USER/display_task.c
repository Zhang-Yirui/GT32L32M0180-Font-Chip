/*
 *  Author: Kaka Xie
 *  brief: display operation
 */

#include "delay.h"
#include "sys.h"
#include "display_task.h"
#include "show_ch.h"
#include "show_pic.h"
#include "character_lib.h"
#include "GT32L32M0180.h"
#include <string.h>
#include "fingerprint_task.h"
#include "battery_task.h"
#include "platform.h"

OS_STK DIS_TEST_TASK_STK[DIS_TEST_STK_SIZE];

OS_STK DISPLAY_TASK_STK[DISPLAY_STK_SIZE];


display_info_t display_str_info_ram = {0};
//{
//    .need_update_flag = 1,
//    .content =
//    {
//        [DISPLAY_ID_FP_ID_SUCCESS] =
//        {
//            .start_x = 10,
//            .start_y = 10,
//            .resolution = USER_CH_HIGH_32,
//            .str_color = Blue,
//            .id = DISPLAY_ID_FP_ID_SUCCESS,
//            .need_update_flag = TRUE,
//        },
//
//    },
//};
display_info_t *display_str_info = &display_str_info_ram;


void display_one_chinese(uint16_t start_x, uint16_t start_y, char_resolution_high_e resolution, uint8_t *chinese, uint16_t color)
{
    uint8_t chinese_matrix[128] = {0};   //max 16X16 need 32 bytes
    get_chinese_dot_matrix(chinese, resolution, chinese_matrix);
    switch(resolution)
    {
        case USER_CH_HIGH_32:
            show_32X32_ch_horizontal(start_x, start_y, ' ', 1, color, chinese_matrix);
            break;
        case USER_CH_HIGH_24:
            show_24X24_ch_horizontal(start_x, start_y, ' ', 1, color, chinese_matrix);
            break;
        case USER_CH_HIGH_16:
            show_16X16_ch_horizontal(start_x, start_y, ' ', 1, color, chinese_matrix);
            break;
        default: break;
    }
//    show_16X16_ch_vertical(start_x, start_y, ' ', 1, color, chinese_matrix);
//    show_16X16_ch_horizontal(start_x, start_y, ' ', 1, color, chinese_matrix);
}

void display_many_chinese(uint16_t start_x, uint16_t start_y, char_resolution_high_e resolution, uint8_t *chinese, uint16_t len, uint16_t color)
{
    uint16_t i;
    for(i = 0; i < len; i += 2)
    {
        switch(resolution)
        {
            case USER_CH_HIGH_32:
                display_one_chinese(start_x + (i / 2) * 32, start_y, resolution, &chinese[i], color);
                break;
            case USER_CH_HIGH_24:
                display_one_chinese(start_x + (i / 2) * 24, start_y, resolution, &chinese[i], color);
                break;
            case USER_CH_HIGH_16:
                display_one_chinese(start_x + (i / 2) * 16, start_y, resolution, &chinese[i], color);
                break;
            default: break;
        }
//        display_one_chinese(start_x + (i / 2) * 16, start_y, resolution, &chinese[i], color);
    }
}



void display_one_ascii(uint16_t start_x, uint16_t start_y, char ascii, char_resolution_high_e resolution, uint16_t color)
{
    uint8_t ascii_matrix[64] = {0};    //max 16X32 need 64 bytes
    get_ascii_dot_matrix(ascii, resolution, ascii_matrix);
    switch(resolution)
    {
        case USER_CH_HIGH_32:
            get_ascii_dot_matrix(ascii, resolution, ascii_matrix);
            show_16X32_ch_horizontal(start_x, start_y, ' ', 1, color, ascii_matrix);
            break;
        case USER_CH_HIGH_24:
            get_ascii_dot_matrix(ascii, resolution, ascii_matrix);
            show_12X24_ch_horizontal(start_x, start_y, ' ', 1, color, ascii_matrix);
            break;
        case USER_CH_HIGH_16:
            get_ascii_dot_matrix(ascii, resolution, ascii_matrix);
//            show_8X16_ch_vertical(start_x, start_y, ' ', 1, color, ascii_matrix);
            show_8X16_ch_horizontal(start_x, start_y, ' ', 1, color, ascii_matrix);

            break;
        default: break;
    }
}

void display_many_ascii(uint16_t start_x, uint16_t start_y, char* ascii, uint16_t len, char_resolution_high_e resolution, uint16_t color)
{
    uint8_t i;
    uint8_t space = 16;
    switch(resolution)
    {
        case USER_CH_HIGH_32:
            space = 16;
            break;
        case USER_CH_HIGH_16:
            space = 8;
            break;
        default: return;
    }
    for(i = 0; i < len; i++)
    {
        display_one_ascii(start_x + i * space, start_y, ascii[i], resolution, color);
    }
}


void display_many_chinese_middle(uint16_t start_y, uint8_t* chinese, uint16_t len, char_resolution_high_e resolution, uint16_t color)
{
    if(len <= (LCD_X_MAX / 16) * 2)
    {
        display_many_chinese((LCD_X_MAX - ((len * 16) / 2)) / 2, start_y, resolution, chinese, len, color);
    }

}


void display_many_ascii_middle(uint16_t start_y, char* ascii, uint16_t len, char_resolution_high_e resolution, uint16_t color)
{
    uint16_t start_x = 0;
    switch(resolution)
    {
        case USER_CH_HIGH_32:
            start_x = (LCD_X_MAX - (len * 16)) / 2;
            break;
        case USER_CH_HIGH_16:
            start_x = (LCD_X_MAX - (len * 8)) / 2;
            break;
        default: return;
    }
    display_many_ascii(start_x, start_y, ascii, len, resolution, color);
}


void display_string(uint16_t start_x, uint16_t start_y, uint8_t* str, uint16_t len, char_resolution_high_e resolution, uint16_t color)
{
    uint16_t i;
    uint8_t space_x = 8;
    switch(resolution)
    {
        case USER_CH_HIGH_32:
            space_x = 16;
            break;
        case USER_CH_HIGH_24:
            space_x = 12;
            break;
        case USER_CH_HIGH_16:
            space_x = 8;
            break;
        default: return;
    }
    for(i = 0; i < len; i++)
    {
        if(str[i] >= 0x80)
        {
            display_one_chinese(start_x + i * space_x, start_y, resolution, &str[i], color);
            i++;
        }
        else
        {
//            display_one_ascii(start_x + i * space_x, start_y, str[i], USER_CH_HIGH_16, color);
            display_one_ascii(start_x + i * space_x, start_y, str[i], resolution, color);
        }
    }
}


void show_rectangle(uint8_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y, const uint16_t color)
{
    if((end_x > start_x) && (end_y > start_y))
    {
        lcd_color_box(start_x, start_y, end_x - start_x, end_y - start_y, color);
    }
}

void notify_string(uint16_t start_x, uint16_t start_y, uint8_t* str, uint16_t len, char_resolution_high_e resolution, uint16_t str_color, uint16_t rectangle_color)
{
    uint16_t rec_start_x, rec_start_y, rec_end_x, rec_end_y;
    uint8_t space_x = 8;
    uint8_t space_y = 16;
#define RECTANGLE_DELTA_X   10
#define RECTANGLE_DELTA_Y   20
    if((start_x > RECTANGLE_DELTA_X / 2) && (start_y > RECTANGLE_DELTA_Y / 2))
    {
        rec_start_x = start_x - RECTANGLE_DELTA_X / 2;
        rec_start_y = start_y - RECTANGLE_DELTA_Y / 2;

        rec_end_x = start_x + space_x * len + RECTANGLE_DELTA_X / 2;
        rec_end_y = start_y + space_y + RECTANGLE_DELTA_Y / 2;
        show_rectangle(rec_start_x, rec_start_y, rec_end_x, rec_end_y, rectangle_color);
        lcd_color_box(rec_start_x, rec_start_y, rec_end_x - rec_start_x, rec_end_y - rec_start_y, rectangle_color);
//        for(i = 1; i < 320; i++)
//        {
//            lcd_color_box(0, 0, i, i, Green);
//            delay_ms(30);
//        }

//        for(i = 1; i < 320; i++)
//        {
//            lcd_color_box(50, 0, 160, i, Green);
//            delay_ms(10);
//        }
//        lcd_color_box(100, 200, 379, 10, Green);
        display_string(start_x, start_y, str, len, resolution, str_color);
    }
}

void clear_rectangle(uint8_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y)
{
    if((end_x > start_x) && (end_y > start_y))
    {
        lcd_color_box(start_x, start_y, end_x - start_x, end_y - start_y, BACKGROUD_COLOR);
    }
}


#if DISPLAY_FUNCTION_1

display_info_t display_info_ram = {0};
display_info_t *display_info = &display_info_ram;

void display_add_one_content(show_content_t content)
{
    if(display_info->content_len < DISPLAY_CONTENT_NUM_MAX)
    {
        display_info->need_update_flag = 1;
        display_info->content[display_info->content_len] = content;
        display_info->content_len++;
    }
}

void display_remove_one_content(uint16_t cnt)       //cnt start from 0
{
    uint16_t i;
    show_content_t content_tmp = {0};
    if(display_info->content_len > 0)
    {
        if(cnt <= display_info->content_len - 1)
        {
            display_info->need_update_flag = 1;
//            memset((void *)(&display_info->content[cnt - 1]), 1, sizeof(show_content_t));
            display_info->content[cnt] = content_tmp;
            for(i = cnt; i < display_info->content_len - 1; i++)
            {
                display_info->content[i] = display_info->content[i + 1];
            }
            display_info->content_len--;
        }
    }
}

void display_main_func(void)
{
    uint16_t i;
    if(display_info->need_update_flag == 1)
    {
        display_info->need_update_flag = 0;
        display_background(BACKGROUD_COLOR);
        for(i = 0; i < display_info->content_len; i++)
        {
            if(display_info->content[i].need_rectangle_flag == 1)
            {
                notify_string(display_info->content[i].start_x, display_info->content[i].start_y,display_info->content[i].str,\
                display_info->content[i].str_len, display_info->content[i].resolution, display_info->content[i].str_color, display_info->content[i].rec_color);
            }
            else
            {
                display_string(display_info->content[i].start_x, display_info->content[i].start_y,display_info->content[i].str, \
                display_info->content[i].str_len, display_info->content[i].resolution, display_info->content[i].str_color);
            }
            if(display_info->content[i].period_ms > 0)
            {
                delay_ms(display_info->content[i].period_ms);
                display_remove_one_content(i);
            }
        }
    }
}
#endif

void display_background(uint16_t color)
{
    lcd_color_box(0, 0, LCD_X_MAX, LCD_Y_MAX, color);
}

void dis_str_info_init(void)
{
    display_str_info->need_update_flag = TRUE;
    display_str_info->content_len = DISPLAY_ID_MAX;

//    display_str_info->content[DISPLAY_ID_FP_ID_SUCCESS].id = DISPLAY_ID_FP_ID_SUCCESS;
//    display_str_info->content[DISPLAY_ID_FP_ID_SUCCESS].need_update_flag = TRUE;
//    display_str_info->content[DISPLAY_ID_FP_ID_SUCCESS].start_x = 10;
//    display_str_info->content[DISPLAY_ID_FP_ID_SUCCESS].start_y = 10;
//    display_str_info->content[DISPLAY_ID_FP_ID_SUCCESS].str_color = Blue;
//    display_str_info->content[DISPLAY_ID_FP_ID_SUCCESS].resolution = USER_CH_HIGH_32;
//    display_str_info->content[DISPLAY_ID_FP_ID_SUCCESS].str_len = sizeof("??????");
//    memcpy(display_str_info->content[DISPLAY_ID_FP_ID_SUCCESS].str, "??????", display_str_info->content[DISPLAY_ID_FP_ID_SUCCESS].str_len);

//    display_str_info->content[DISPLAY_ID_LOCK_STATUS].id = DISPLAY_ID_LOCK_STATUS;
//    display_str_info->content[DISPLAY_ID_LOCK_STATUS].need_update_flag = TRUE;
//    display_str_info->content[DISPLAY_ID_LOCK_STATUS].start_x = 10;
//    display_str_info->content[DISPLAY_ID_LOCK_STATUS].start_y = 50;
//    display_str_info->content[DISPLAY_ID_LOCK_STATUS].resolution = USER_CH_HIGH_24;
//    display_str_info->content[DISPLAY_ID_LOCK_STATUS].str_color = Blue;
//    display_str_info->content[DISPLAY_ID_LOCK_STATUS].str_len = sizeof("lock status: ??????????????????????");
//    memcpy(display_str_info->content[DISPLAY_ID_LOCK_STATUS].str, "lock status: ??????????????????????", display_str_info->content[DISPLAY_ID_LOCK_STATUS].str_len);


//    display_str_info->content[DISPLAY_ID_TO_DESTINATION].id = DISPLAY_ID_TO_DESTINATION;
//    display_str_info->content[DISPLAY_ID_TO_DESTINATION].need_update_flag = TRUE;
//    display_str_info->content[DISPLAY_ID_TO_DESTINATION].start_x = 10;
//    display_str_info->content[DISPLAY_ID_TO_DESTINATION].start_y = 90;
//    display_str_info->content[DISPLAY_ID_TO_DESTINATION].resolution = USER_CH_HIGH_32;
//    display_str_info->content[DISPLAY_ID_TO_DESTINATION].str_color = Blue;
//    display_str_info->content[DISPLAY_ID_TO_DESTINATION].str_len = sizeof("??????:??????, 10????????");
//    memcpy(display_str_info->content[DISPLAY_ID_TO_DESTINATION].str, "??????:??????, 10????????", display_str_info->content[DISPLAY_ID_TO_DESTINATION].str_len);
}



void show_fp_id_result(uint8_t result, uint16_t fp_id)
{
    display_str_info->content[DISPLAY_ID_FP_ID_STATUS].need_update_flag = TRUE;

    display_str_info->content[DISPLAY_ID_FP_ID_STATUS].id = DISPLAY_ID_FP_ID_STATUS;
    display_str_info->content[DISPLAY_ID_FP_ID_STATUS].start_x = 0;
    display_str_info->content[DISPLAY_ID_FP_ID_STATUS].start_y = 10;
    display_str_info->content[DISPLAY_ID_FP_ID_STATUS].str_color = Blue;
    display_str_info->content[DISPLAY_ID_FP_ID_STATUS].resolution = USER_CH_HIGH_32;

    if(result == TRUE)
    {
        display_str_info->content[DISPLAY_ID_FP_ID_STATUS].str_len = sizeof("??????");
        memcpy(display_str_info->content[DISPLAY_ID_FP_ID_STATUS].str, "??????", display_str_info->content[DISPLAY_ID_FP_ID_STATUS].str_len);
    }
    else
    {
        display_str_info->content[DISPLAY_ID_FP_ID_STATUS].str_color = Red;
        display_str_info->content[DISPLAY_ID_FP_ID_STATUS].str_len = sizeof("??????????,????????????????????");
        memcpy(display_str_info->content[DISPLAY_ID_FP_ID_STATUS].str, "??????????,????????????????????", display_str_info->content[DISPLAY_ID_FP_ID_STATUS].str_len);
    }

    display_str_info->content[DISPLAY_ID_FP_ID_STATUS].occupied_zone.start_x = display_str_info->content[DISPLAY_ID_FP_ID_STATUS].start_x;
    display_str_info->content[DISPLAY_ID_FP_ID_STATUS].occupied_zone.start_y = display_str_info->content[DISPLAY_ID_FP_ID_STATUS].start_y;
    display_str_info->content[DISPLAY_ID_FP_ID_STATUS].occupied_zone.end_x = LCD_X_MAX;
//    display_str_info->content[DISPLAY_ID_TO_DESTINATION].occupied_zone.end_x = display_str_info->content[DISPLAY_ID_TO_DESTINATION].start_x + \
    display_str_info->content[DISPLAY_ID_TO_DESTINATION].str_len * 16;
    display_str_info->content[DISPLAY_ID_FP_ID_STATUS].occupied_zone.end_y = display_str_info->content[DISPLAY_ID_FP_ID_STATUS].start_y + 42;
}

void clear_fp_id_result(void)
{
    display_str_info->content[DISPLAY_ID_FP_ID_STATUS].need_update_flag = TRUE;

    display_str_info->content[DISPLAY_ID_FP_ID_STATUS].id = DISPLAY_ID_FP_ID_STATUS;
    display_str_info->content[DISPLAY_ID_FP_ID_STATUS].start_x = 0;
    display_str_info->content[DISPLAY_ID_FP_ID_STATUS].start_y = 10;
    display_str_info->content[DISPLAY_ID_FP_ID_STATUS].str_color = Blue;
    display_str_info->content[DISPLAY_ID_FP_ID_STATUS].resolution = USER_CH_HIGH_32;

    display_str_info->content[DISPLAY_ID_FP_ID_STATUS].str_color = Red;
    memset(display_str_info->content[DISPLAY_ID_FP_ID_STATUS].str, 0, display_str_info->content[DISPLAY_ID_FP_ID_STATUS].str_len);
    display_str_info->content[DISPLAY_ID_FP_ID_STATUS].str_len =0;

    display_str_info->content[DISPLAY_ID_FP_ID_STATUS].occupied_zone.start_x = display_str_info->content[DISPLAY_ID_FP_ID_STATUS].start_x;
    display_str_info->content[DISPLAY_ID_FP_ID_STATUS].occupied_zone.start_y = display_str_info->content[DISPLAY_ID_FP_ID_STATUS].start_y;
    display_str_info->content[DISPLAY_ID_FP_ID_STATUS].occupied_zone.end_x = LCD_X_MAX;
//    display_str_info->content[DISPLAY_ID_TO_DESTINATION].occupied_zone.end_x = display_str_info->content[DISPLAY_ID_TO_DESTINATION].start_x + \
    display_str_info->content[DISPLAY_ID_TO_DESTINATION].str_len * 16;
    display_str_info->content[DISPLAY_ID_FP_ID_STATUS].occupied_zone.end_y = display_str_info->content[DISPLAY_ID_FP_ID_STATUS].start_y + 42;
}


void show_power_status(uint16_t power)
{
    display_str_info->content[DISPLAY_ID_POWER_STATUS].need_update_flag = TRUE;

    display_str_info->content[DISPLAY_ID_POWER_STATUS].id = DISPLAY_ID_POWER_STATUS;
    display_str_info->content[DISPLAY_ID_POWER_STATUS].start_x = 10;
    display_str_info->content[DISPLAY_ID_POWER_STATUS].start_y = 300;
    display_str_info->content[DISPLAY_ID_POWER_STATUS].str_color = Blue;
    display_str_info->content[DISPLAY_ID_POWER_STATUS].resolution = USER_CH_HIGH_16;

    display_str_info->content[DISPLAY_ID_POWER_STATUS].str_len = 7;
    sprintf((char *)display_str_info->content[DISPLAY_ID_POWER_STATUS].str, "%dmv", power);

    display_str_info->content[DISPLAY_ID_POWER_STATUS].occupied_zone.start_x = display_str_info->content[DISPLAY_ID_POWER_STATUS].start_x;
    display_str_info->content[DISPLAY_ID_POWER_STATUS].occupied_zone.start_y = display_str_info->content[DISPLAY_ID_POWER_STATUS].start_y;
    display_str_info->content[DISPLAY_ID_POWER_STATUS].occupied_zone.end_x = display_str_info->content[DISPLAY_ID_POWER_STATUS].start_x + 56;
//    display_str_info->content[DISPLAY_ID_TO_DESTINATION].occupied_zone.end_x = display_str_info->content[DISPLAY_ID_TO_DESTINATION].start_x + \
    display_str_info->content[DISPLAY_ID_TO_DESTINATION].str_len * 16;
    display_str_info->content[DISPLAY_ID_POWER_STATUS].occupied_zone.end_y = display_str_info->content[DISPLAY_ID_POWER_STATUS].start_y + 525;

    //        lcd_color_box(10, 300, 56, 525, color);
}

void clear_zone(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y, uint16_t color)
{
    if((end_x > start_x) && (end_y > start_y))
    {
        lcd_color_box(start_x, start_y,end_x - start_x , end_y - start_y, color);
//        lcd_color_box(10, 202, 60, 310, color);
//        lcd_color_box(10, 300, 56, 525, color);
//        lcd_color_box(10, 512, 40, 310, color);
    }

}
void show_destination_info(void)
{
    uint8_t space;
    display_str_info->content[DISPLAY_ID_TO_DESTINATION].id = DISPLAY_ID_TO_DESTINATION;
    display_str_info->content[DISPLAY_ID_TO_DESTINATION].need_update_flag = TRUE;
    display_str_info->content[DISPLAY_ID_TO_DESTINATION].start_x = 10;
    display_str_info->content[DISPLAY_ID_TO_DESTINATION].start_y = 90;
    display_str_info->content[DISPLAY_ID_TO_DESTINATION].resolution = USER_CH_HIGH_32;
    display_str_info->content[DISPLAY_ID_TO_DESTINATION].str_color = Blue;
    display_str_info->content[DISPLAY_ID_TO_DESTINATION].str_len = sizeof("??????:??????, 10????????");
    memcpy(display_str_info->content[DISPLAY_ID_TO_DESTINATION].str, "??????:??????, 10????????", display_str_info->content[DISPLAY_ID_TO_DESTINATION].str_len);
    display_str_info->content[DISPLAY_ID_TO_DESTINATION].occupied_zone.start_x = display_str_info->content[DISPLAY_ID_TO_DESTINATION].start_x;
    display_str_info->content[DISPLAY_ID_TO_DESTINATION].occupied_zone.start_y = display_str_info->content[DISPLAY_ID_TO_DESTINATION].start_y;
    display_str_info->content[DISPLAY_ID_TO_DESTINATION].occupied_zone.end_x = display_str_info->content[DISPLAY_ID_TO_DESTINATION].start_x + \
    display_str_info->content[DISPLAY_ID_TO_DESTINATION].str_len * 16;
//    display_str_info->content[DISPLAY_ID_TO_DESTINATION].occupied_zone.end_x = LCD_X_MAX;
    display_str_info->content[DISPLAY_ID_TO_DESTINATION].occupied_zone.end_y = display_str_info->content[DISPLAY_ID_TO_DESTINATION].start_y + 115;
}

void clear_destination_info(void)
{
    lcd_color_box(display_str_info->content[DISPLAY_ID_TO_DESTINATION].start_x, display_str_info->content[DISPLAY_ID_TO_DESTINATION].start_y, \
                    LCD_X_MAX, 50, Yellow);
}

void dis_main_str_func(void)
{
    for(uint16_t i = 0; i < DISPLAY_ID_MAX; i++)
    {
        if(display_str_info->content[i].need_update_flag == TRUE)
        {
            clear_zone(display_str_info->content[i].occupied_zone.start_x, display_str_info->content[i].occupied_zone.start_y, \
                    display_str_info->content[i].occupied_zone.end_x, display_str_info->content[i].occupied_zone.end_y, Green);
            display_string(display_str_info->content[i].start_x, display_str_info->content[i].start_y, display_str_info->content[i].str, \
                display_str_info->content[i].str_len, display_str_info->content[i].resolution, display_str_info->content[i].str_color);
            display_str_info->content[i].need_update_flag = FALSE;
        }
    }
}

#define FP_ID_EXIST_TIME    5 * OS_TICKS_PER_SEC
void display_main_prepare(void)
{
    /* fingerprint id result */
    if(fp_id_result.trigger == TRUE)
    {
        if(get_tick() - fp_id_result.start_tick <= FP_ID_EXIST_TIME)
        {
            if(get_tick() - fp_id_result.start_tick <= OS_TICKS_PER_SEC / 3)
            {
                show_fp_id_result(fp_id_result.result, fp_id_result.fp_id);
            }
        }
        else
        {
            fp_id_result.trigger = FALSE;
        }
    }
    else
    {
        clear_fp_id_result();
    }



    /* DISPLAY_ID_LOW_POWER: low power */
    show_power_status(battery_voltage);

}


extern uint8_t flash_read_test_buf[100];

void display_task(void *pdata)
{
    uint8_t init_flag = 0;
    show_content_t content = {0};
    dis_str_info_init();
    while(1)
    {
        if(init_flag == 0)
        {
            init_flag = 1;
            display_background(White);
            show_destination_info();
//            show_fp_id_result(FALSE);
#if DISPLAY_FUNCTION_1
            content.start_x = 10;
            content.start_y = 20;
            content.str_len = sizeof("1.???????? ???? A");
            memcpy(content.str, "1.???????? ???? A", content.str_len);
            content.str_color = Blue;
            content.period_ms = 0;
            content.resolution = USER_CH_HIGH_16;
            content.need_rectangle_flag = 0;
            display_add_one_content(content);

            content.start_x = 10;
            content.start_y = 40;
            content.str_len = sizeof("2.???????? ???? ??????");
            memcpy(content.str, "2.???????? ???? ??????", content.str_len);
            content.resolution = USER_CH_HIGH_16;
            content.need_rectangle_flag = 0;

            display_add_one_content(content);

            content.start_x = 10;
            content.start_y = 60;
            content.str_len = sizeof("3.???????? ???? ???? ! !");
            memcpy(content.str, "3.???????? ???? ???? ?? ??", content.str_len);
            content.str_color = Blue;
            content.period_ms = 1000;
            content.resolution = USER_CH_HIGH_16;
            content.need_rectangle_flag = 0;
            display_add_one_content(content);

            content.start_x = 10;
            content.start_y = 80;
            content.str_len = sizeof("??????????  Mrobot");
            memcpy(content.str, "??????????  Mrobot", content.str_len);
            content.str_color = Blue;
            content.period_ms = 0;
            content.resolution = USER_CH_HIGH_32;
            content.need_rectangle_flag = 0;
            display_add_one_content(content);

            content.start_x = 10;
            content.start_y = 120;
            content.str_len = sizeof("2.???????? ???? ??????");
            memcpy(content.str, "2.???????? ???? ??????", content.str_len);
            content.resolution = USER_CH_HIGH_24;
            content.need_rectangle_flag = 0;

            display_add_one_content(content);

            content.start_x = 10;
            content.start_y = 160;
            content.str_len = sizeof("3.???????? ???? ????");
            memcpy(content.str, "3.???????? ???? ????", content.str_len);
            content.str_color = Blue;
            content.period_ms = 1000;
            content.resolution = USER_CH_HIGH_32;
            content.need_rectangle_flag = 0;
            display_add_one_content(content);

            content.start_x = 10;
            content.start_y = 160;
            content.str_len = sizeof("????!@#$%^&-??< >?? ??/??");
            memcpy(content.str, "????!@#$%^&-??< >?? ??/??", content.str_len);
            content.str_color = Blue;
            content.period_ms = 0;
            content.resolution = USER_CH_HIGH_32;
            content.need_rectangle_flag = 0;
            display_add_one_content(content);
#endif

        }
////        display_one_chinese(10, 10, "??", Blue);
//        display_many_chinese_middle(120, "??????????????", 14,0, Blue);
//        display_many_chinese(10, 30, "??????????????", 14, Black);
//        display_many_ascii(10, 50, "hello world", sizeof("hello world"), ASCII_16X32_NORMAL, Blue);
//        display_many_ascii(10, 80, "hello world", sizeof("hello world"), ASCII_8X16_NORMAL, Blue);
//        display_many_ascii_middle(140, "Mrobot", sizeof("Mrobot"), ASCII_16X32_NORMAL, Blue);
//        display_one_ascii(10, 100, 'A', ASCII_16X32_NORMAL, Blue);
//        display_string(10, 180, "ABCDE??????????FG", sizeof("ABCDE??????????FG"), 0, Blue);
//
//        notify_string(200, 280, "????????????", sizeof("????????????"), 0, Blue, Red);
#if DISPLAY_FUNCTION_1
        display_main_func();
#endif
        display_main_prepare();
        dis_main_str_func();
        delay_ms(100);
    }
}



//extern const unsigned char pic_background[307200];
void dis_test_task(void *pdata)
{
    int i = 0;

    while(1)
    {
//        for(i = 0; i < 100; i++)
//        {
//            lcd_color_box(0, 0, 320, 480, (0x00f1 << 5) + (0x00f2 << 10) + i);
//            //delay_ms(10);
//        }

//        lcd_color_box(0,0,320,480,Red);delay_ms(1000);
//        lcd_color_box(0,0,320,480,Blue);delay_ms(1000);
        delay_ms(1000);
        lcd_color_box(0, 0, LCD_X_MAX, LCD_Y_MAX, Red);delay_ms(1000);
        lcd_color_box(0, 0, LCD_X_MAX, LCD_Y_MAX, White);delay_ms(1000);
//        lcd_color_box_ex(0, 0, LCD_X_MAX, LCD_Y_MAX, pic_background);delay_ms(1000);
        lcd_color_box(100, 100, 60, 90, Green);delay_ms(1000);
//        lcd_color_box_ex(0, 0, LCD_X_MAX, LCD_Y_MAX, pic_background);delay_ms(1000);
//        lcd_color_box(0,0,20,80,Green);delay_ms(1000);
//        lcd_color_box(100,100,20,80,Green);delay_ms(1000);
//        lcd_color_box(200,260,20,80,Green);delay_ms(1000);
//
//        for(i = 0; i < 320; i++)
//        {
//            lcd_draw_pixel(i, i, Red);
//        }
//        delay_ms(1000);
//        for(i = 0; i < 320; i++)
//        {
//            lcd_draw_pixel(320 - i, i, Red);
//        }
//        delay_ms(1000);
//        for(i = 0; i < 320; i++)
//        {
//            lcd_draw_pixel(180, i, Red);
//        }
//        delay_ms(1000);
//        for(i = 0; i < 320; i++)
//        {
//            lcd_draw_pixel(i, 180, Red);
//        }


//        show_ch(100, 100, "??", 1, Red);
//        delay_ms(1000);
//        show_ch(120, 120, "??", 1, Red);
//        delay_ms(1000);
//        show_ch(140, 140, "??", 1, Red);
//        delay_ms(1000);
//        show_ch(160, 160, "??", 1, Red);
//        delay_ms(1000);
//        for(i = 0; i < 480; i += 32)
//        {
//            //show_16x16_ch(0, i, "??????????????????????????????????????????????????????????????????????????????????????", 20, Red);
//            //show_ch(0, 320, "??????????????????????????????????????????????????????????????????????????????????????", 20, Red);
//            show_32x32_ch(0, i, "??????????????????????????????????????????????????????????????????????????????????????????????????", 15, Blue);
////            show_32x32_ch_vertical(0, i, "????????", 4, Red);
////            show_32x32_ch(0, i, "????????", 4, Red);
//        }
        delay_ms(1000);
//        for(i = 0; i < 480; i++)
//        {
//            lcd_draw_pixel(i, 470, Red);
//        }
//        delay_ms(1000);
//        for(i = 0; i < 480; i++)
//        {
//            lcd_draw_pixel(310, i, Red);
//        }
//        delay_ms(1000);
        //lcd_color_box(300,200,20,80,Green);delay_ms(1000);
        //lcd_color_box(300,400,20,80,Green);delay_ms(1000);
        //lcd_fill_pic(0, 0, 320, 480, gImage_MM_T035);delay_ms(1000);



//        for(i = 0; i < 480; i += 10)
//        {
//            lcd_color_box_ex(0, i, 320, 480 - i, gImage_MM_T035);
//        }

//        lcd_color_box_ex(0, 0, 320, 480, gImage_MM_T035);
        delay_ms(1000);
    }

}

