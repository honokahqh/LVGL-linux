// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.3
// LVGL version: 8.3.4
// Project name: SquareLine_Project

#include "../ui.h"

void ui_ScreenConfirm_screen_init(void)
{
ui_ScreenConfirm = lv_obj_create(NULL);
lv_obj_clear_flag( ui_ScreenConfirm, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_ScreenConfirm, lv_color_hex(0x201E1C), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ScreenConfirm, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_grad_color(ui_ScreenConfirm, lv_color_hex(0x1E1B0E), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_grad_dir(ui_ScreenConfirm, LV_GRAD_DIR_HOR, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmPanelTtitle = lv_obj_create(ui_ScreenConfirm);
lv_obj_set_width( ui_ConfirmPanelTtitle, 1024);
lv_obj_set_height( ui_ConfirmPanelTtitle, 60);
lv_obj_clear_flag( ui_ConfirmPanelTtitle, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_ConfirmPanelTtitle, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_ConfirmPanelTtitle, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ConfirmPanelTtitle, 200, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_grad_color(ui_ConfirmPanelTtitle, lv_color_hex(0x1C190C), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_grad_dir(ui_ConfirmPanelTtitle, LV_GRAD_DIR_HOR, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_ConfirmPanelTtitle, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_ConfirmPanelTtitle, 50, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_ConfirmPanelTtitle, 1, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmBtnBack = lv_btn_create(ui_ConfirmPanelTtitle);
lv_obj_set_width( ui_ConfirmBtnBack, 100);
lv_obj_set_height( ui_ConfirmBtnBack, 60);
lv_obj_set_x( ui_ConfirmBtnBack, -20 );
lv_obj_set_y( ui_ConfirmBtnBack, 0 );
lv_obj_set_align( ui_ConfirmBtnBack, LV_ALIGN_LEFT_MID );
lv_obj_add_flag( ui_ConfirmBtnBack, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ConfirmBtnBack, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_ConfirmBtnBack, 100, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_ConfirmBtnBack, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ConfirmBtnBack, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_img_src( ui_ConfirmBtnBack, &ui_img_1611405318, LV_PART_MAIN | LV_STATE_DEFAULT );

ui_ConfirmLabelTime = lv_label_create(ui_ConfirmPanelTtitle);
lv_obj_set_width( ui_ConfirmLabelTime, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ConfirmLabelTime, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_ConfirmLabelTime, LV_ALIGN_RIGHT_MID );
lv_label_set_text(ui_ConfirmLabelTime,"09:37");
lv_obj_set_style_text_font(ui_ConfirmLabelTime, &ui_font_CN24, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmPanelKey = lv_obj_create(ui_ScreenConfirm);
lv_obj_set_width( ui_ConfirmPanelKey, 400);
lv_obj_set_height( ui_ConfirmPanelKey, 400);
lv_obj_set_x( ui_ConfirmPanelKey, 0 );
lv_obj_set_y( ui_ConfirmPanelKey, -31 );
lv_obj_set_align( ui_ConfirmPanelKey, LV_ALIGN_BOTTOM_MID );
lv_obj_clear_flag( ui_ConfirmPanelKey, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_ConfirmPanelKey, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_ConfirmPanelKey, lv_color_hex(0x181612), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ConfirmPanelKey, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_ConfirmPanelKey, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmBtn2 = lv_btn_create(ui_ConfirmPanelKey);
lv_obj_set_width( ui_ConfirmBtn2, 110);
lv_obj_set_height( ui_ConfirmBtn2, 80);
lv_obj_set_align( ui_ConfirmBtn2, LV_ALIGN_TOP_MID );
lv_obj_add_flag( ui_ConfirmBtn2, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ConfirmBtn2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_ConfirmBtn2, lv_color_hex(0x2D2B29), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ConfirmBtn2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmLabel2 = lv_label_create(ui_ConfirmBtn2);
lv_obj_set_width( ui_ConfirmLabel2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ConfirmLabel2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_ConfirmLabel2, LV_ALIGN_CENTER );
lv_label_set_text(ui_ConfirmLabel2,"2");
lv_obj_set_style_text_font(ui_ConfirmLabel2, &ui_font_CN32, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmBtn1 = lv_btn_create(ui_ConfirmPanelKey);
lv_obj_set_width( ui_ConfirmBtn1, 110);
lv_obj_set_height( ui_ConfirmBtn1, 80);
lv_obj_set_x( ui_ConfirmBtn1, -125 );
lv_obj_set_y( ui_ConfirmBtn1, 0 );
lv_obj_set_align( ui_ConfirmBtn1, LV_ALIGN_TOP_MID );
lv_obj_add_flag( ui_ConfirmBtn1, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ConfirmBtn1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_ConfirmBtn1, lv_color_hex(0x2D2B29), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ConfirmBtn1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmLabel1 = lv_label_create(ui_ConfirmBtn1);
lv_obj_set_width( ui_ConfirmLabel1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ConfirmLabel1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_ConfirmLabel1, LV_ALIGN_CENTER );
lv_label_set_text(ui_ConfirmLabel1,"1");
lv_obj_set_style_text_font(ui_ConfirmLabel1, &ui_font_CN32, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmBtn3 = lv_btn_create(ui_ConfirmPanelKey);
lv_obj_set_width( ui_ConfirmBtn3, 110);
lv_obj_set_height( ui_ConfirmBtn3, 80);
lv_obj_set_x( ui_ConfirmBtn3, 125 );
lv_obj_set_y( ui_ConfirmBtn3, 0 );
lv_obj_set_align( ui_ConfirmBtn3, LV_ALIGN_TOP_MID );
lv_obj_add_flag( ui_ConfirmBtn3, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ConfirmBtn3, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_ConfirmBtn3, lv_color_hex(0x2D2B29), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ConfirmBtn3, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmLabel3 = lv_label_create(ui_ConfirmBtn3);
lv_obj_set_width( ui_ConfirmLabel3, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ConfirmLabel3, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_ConfirmLabel3, LV_ALIGN_CENTER );
lv_label_set_text(ui_ConfirmLabel3,"3");
lv_obj_set_style_text_font(ui_ConfirmLabel3, &ui_font_CN32, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmBtn4 = lv_btn_create(ui_ConfirmPanelKey);
lv_obj_set_width( ui_ConfirmBtn4, 110);
lv_obj_set_height( ui_ConfirmBtn4, 80);
lv_obj_set_x( ui_ConfirmBtn4, -125 );
lv_obj_set_y( ui_ConfirmBtn4, 95 );
lv_obj_set_align( ui_ConfirmBtn4, LV_ALIGN_TOP_MID );
lv_obj_add_flag( ui_ConfirmBtn4, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ConfirmBtn4, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_ConfirmBtn4, lv_color_hex(0x2D2B29), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ConfirmBtn4, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmLabel4 = lv_label_create(ui_ConfirmBtn4);
lv_obj_set_width( ui_ConfirmLabel4, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ConfirmLabel4, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_ConfirmLabel4, LV_ALIGN_CENTER );
lv_label_set_text(ui_ConfirmLabel4,"4");
lv_obj_set_style_text_font(ui_ConfirmLabel4, &ui_font_CN32, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmBtn5 = lv_btn_create(ui_ConfirmPanelKey);
lv_obj_set_width( ui_ConfirmBtn5, 110);
lv_obj_set_height( ui_ConfirmBtn5, 80);
lv_obj_set_x( ui_ConfirmBtn5, 0 );
lv_obj_set_y( ui_ConfirmBtn5, 95 );
lv_obj_set_align( ui_ConfirmBtn5, LV_ALIGN_TOP_MID );
lv_obj_add_flag( ui_ConfirmBtn5, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ConfirmBtn5, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_ConfirmBtn5, lv_color_hex(0x2D2B29), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ConfirmBtn5, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmLabel5 = lv_label_create(ui_ConfirmBtn5);
lv_obj_set_width( ui_ConfirmLabel5, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ConfirmLabel5, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_ConfirmLabel5, LV_ALIGN_CENTER );
lv_label_set_text(ui_ConfirmLabel5,"5");
lv_obj_set_style_text_font(ui_ConfirmLabel5, &ui_font_CN32, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmBtn6 = lv_btn_create(ui_ConfirmPanelKey);
lv_obj_set_width( ui_ConfirmBtn6, 110);
lv_obj_set_height( ui_ConfirmBtn6, 80);
lv_obj_set_x( ui_ConfirmBtn6, 125 );
lv_obj_set_y( ui_ConfirmBtn6, 95 );
lv_obj_set_align( ui_ConfirmBtn6, LV_ALIGN_TOP_MID );
lv_obj_add_flag( ui_ConfirmBtn6, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ConfirmBtn6, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_ConfirmBtn6, lv_color_hex(0x2D2B29), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ConfirmBtn6, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmLabel6 = lv_label_create(ui_ConfirmBtn6);
lv_obj_set_width( ui_ConfirmLabel6, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ConfirmLabel6, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_ConfirmLabel6, LV_ALIGN_CENTER );
lv_label_set_text(ui_ConfirmLabel6,"2");
lv_obj_set_style_text_font(ui_ConfirmLabel6, &ui_font_CN32, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmBtn7 = lv_btn_create(ui_ConfirmPanelKey);
lv_obj_set_width( ui_ConfirmBtn7, 110);
lv_obj_set_height( ui_ConfirmBtn7, 80);
lv_obj_set_x( ui_ConfirmBtn7, -125 );
lv_obj_set_y( ui_ConfirmBtn7, 190 );
lv_obj_set_align( ui_ConfirmBtn7, LV_ALIGN_TOP_MID );
lv_obj_add_flag( ui_ConfirmBtn7, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ConfirmBtn7, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_ConfirmBtn7, lv_color_hex(0x2D2B29), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ConfirmBtn7, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmLabel7 = lv_label_create(ui_ConfirmBtn7);
lv_obj_set_width( ui_ConfirmLabel7, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ConfirmLabel7, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_ConfirmLabel7, LV_ALIGN_CENTER );
lv_label_set_text(ui_ConfirmLabel7,"7");
lv_obj_set_style_text_font(ui_ConfirmLabel7, &ui_font_CN32, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmBtn8 = lv_btn_create(ui_ConfirmPanelKey);
lv_obj_set_width( ui_ConfirmBtn8, 110);
lv_obj_set_height( ui_ConfirmBtn8, 80);
lv_obj_set_x( ui_ConfirmBtn8, 0 );
lv_obj_set_y( ui_ConfirmBtn8, 190 );
lv_obj_set_align( ui_ConfirmBtn8, LV_ALIGN_TOP_MID );
lv_obj_add_flag( ui_ConfirmBtn8, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ConfirmBtn8, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_ConfirmBtn8, lv_color_hex(0x2D2B29), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ConfirmBtn8, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmLabel8 = lv_label_create(ui_ConfirmBtn8);
lv_obj_set_width( ui_ConfirmLabel8, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ConfirmLabel8, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_ConfirmLabel8, LV_ALIGN_CENTER );
lv_label_set_text(ui_ConfirmLabel8,"8");
lv_obj_set_style_text_font(ui_ConfirmLabel8, &ui_font_CN32, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmBtn9 = lv_btn_create(ui_ConfirmPanelKey);
lv_obj_set_width( ui_ConfirmBtn9, 110);
lv_obj_set_height( ui_ConfirmBtn9, 80);
lv_obj_set_x( ui_ConfirmBtn9, 125 );
lv_obj_set_y( ui_ConfirmBtn9, 190 );
lv_obj_set_align( ui_ConfirmBtn9, LV_ALIGN_TOP_MID );
lv_obj_add_flag( ui_ConfirmBtn9, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ConfirmBtn9, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_ConfirmBtn9, lv_color_hex(0x2D2B29), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ConfirmBtn9, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmLabel9 = lv_label_create(ui_ConfirmBtn9);
lv_obj_set_width( ui_ConfirmLabel9, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ConfirmLabel9, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_ConfirmLabel9, LV_ALIGN_CENTER );
lv_label_set_text(ui_ConfirmLabel9,"9");
lv_obj_set_style_text_font(ui_ConfirmLabel9, &ui_font_CN32, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmBtn0 = lv_btn_create(ui_ConfirmPanelKey);
lv_obj_set_width( ui_ConfirmBtn0, 110);
lv_obj_set_height( ui_ConfirmBtn0, 80);
lv_obj_set_x( ui_ConfirmBtn0, 0 );
lv_obj_set_y( ui_ConfirmBtn0, 285 );
lv_obj_set_align( ui_ConfirmBtn0, LV_ALIGN_TOP_MID );
lv_obj_add_flag( ui_ConfirmBtn0, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ConfirmBtn0, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_ConfirmBtn0, lv_color_hex(0x2D2B29), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ConfirmBtn0, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmLabel0 = lv_label_create(ui_ConfirmBtn0);
lv_obj_set_width( ui_ConfirmLabel0, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ConfirmLabel0, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_ConfirmLabel0, LV_ALIGN_CENTER );
lv_label_set_text(ui_ConfirmLabel0,"0");
lv_obj_set_style_text_font(ui_ConfirmLabel0, &ui_font_CN32, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmBtnCancel = lv_btn_create(ui_ConfirmPanelKey);
lv_obj_set_width( ui_ConfirmBtnCancel, 110);
lv_obj_set_height( ui_ConfirmBtnCancel, 80);
lv_obj_set_x( ui_ConfirmBtnCancel, -125 );
lv_obj_set_y( ui_ConfirmBtnCancel, 285 );
lv_obj_set_align( ui_ConfirmBtnCancel, LV_ALIGN_TOP_MID );
lv_obj_add_flag( ui_ConfirmBtnCancel, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ConfirmBtnCancel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_ConfirmBtnCancel, lv_color_hex(0x2D2B29), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ConfirmBtnCancel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmLabelCancel = lv_label_create(ui_ConfirmBtnCancel);
lv_obj_set_width( ui_ConfirmLabelCancel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ConfirmLabelCancel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_ConfirmLabelCancel, LV_ALIGN_CENTER );
lv_label_set_text(ui_ConfirmLabelCancel,"取消");
lv_obj_set_style_text_font(ui_ConfirmLabelCancel, &ui_font_CN32, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmBtnConfirm = lv_btn_create(ui_ConfirmPanelKey);
lv_obj_set_width( ui_ConfirmBtnConfirm, 110);
lv_obj_set_height( ui_ConfirmBtnConfirm, 80);
lv_obj_set_x( ui_ConfirmBtnConfirm, 125 );
lv_obj_set_y( ui_ConfirmBtnConfirm, 285 );
lv_obj_set_align( ui_ConfirmBtnConfirm, LV_ALIGN_TOP_MID );
lv_obj_add_flag( ui_ConfirmBtnConfirm, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ConfirmBtnConfirm, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_ConfirmBtnConfirm, lv_color_hex(0x2D2B29), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ConfirmBtnConfirm, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmLabelConfirm = lv_label_create(ui_ConfirmBtnConfirm);
lv_obj_set_width( ui_ConfirmLabelConfirm, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ConfirmLabelConfirm, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_ConfirmLabelConfirm, LV_ALIGN_CENTER );
lv_label_set_text(ui_ConfirmLabelConfirm,"确定");
lv_obj_set_style_text_font(ui_ConfirmLabelConfirm, &ui_font_CN32, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmPanelInput = lv_obj_create(ui_ScreenConfirm);
lv_obj_set_width( ui_ConfirmPanelInput, 400);
lv_obj_set_height( ui_ConfirmPanelInput, 70);
lv_obj_set_x( ui_ConfirmPanelInput, 0 );
lv_obj_set_y( ui_ConfirmPanelInput, -430 );
lv_obj_set_align( ui_ConfirmPanelInput, LV_ALIGN_BOTTOM_MID );
lv_obj_clear_flag( ui_ConfirmPanelInput, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_ConfirmPanelInput, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_ConfirmPanelInput, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ConfirmPanelInput, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_ConfirmPanelInput, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmLabelInput = lv_label_create(ui_ConfirmPanelInput);
lv_obj_set_width( ui_ConfirmLabelInput, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ConfirmLabelInput, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_ConfirmLabelInput, LV_ALIGN_LEFT_MID );
lv_label_set_text(ui_ConfirmLabelInput,"请输入管理密码");
lv_obj_set_style_text_color(ui_ConfirmLabelInput, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_ConfirmLabelInput, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_ConfirmLabelInput, &ui_font_CN32, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmBtnReset = lv_btn_create(ui_ScreenConfirm);
lv_obj_set_width( ui_ConfirmBtnReset, 150);
lv_obj_set_height( ui_ConfirmBtnReset, 60);
lv_obj_set_x( ui_ConfirmBtnReset, 370 );
lv_obj_set_y( ui_ConfirmBtnReset, 100 );
lv_obj_set_align( ui_ConfirmBtnReset, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_ConfirmBtnReset, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ConfirmBtnReset, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_ConfirmBtnReset, lv_color_hex(0xF9E6C6), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ConfirmBtnReset, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_grad_color(ui_ConfirmBtnReset, lv_color_hex(0xE2AE6C), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_grad_dir(ui_ConfirmBtnReset, LV_GRAD_DIR_VER, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmLabelReset = lv_label_create(ui_ConfirmBtnReset);
lv_obj_set_width( ui_ConfirmLabelReset, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ConfirmLabelReset, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_ConfirmLabelReset, 30 );
lv_obj_set_y( ui_ConfirmLabelReset, 0 );
lv_obj_set_align( ui_ConfirmLabelReset, LV_ALIGN_LEFT_MID );
lv_label_set_text(ui_ConfirmLabelReset,"设备重启");
lv_obj_set_style_text_color(ui_ConfirmLabelReset, lv_color_hex(0x492B06), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_ConfirmLabelReset, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_ConfirmLabelReset, &ui_font_CN24, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmImgReset = lv_btn_create(ui_ConfirmBtnReset);
lv_obj_set_width( ui_ConfirmImgReset, 40);
lv_obj_set_height( ui_ConfirmImgReset, 40);
lv_obj_set_x( ui_ConfirmImgReset, -15 );
lv_obj_set_y( ui_ConfirmImgReset, 0 );
lv_obj_set_align( ui_ConfirmImgReset, LV_ALIGN_LEFT_MID );
lv_obj_add_flag( ui_ConfirmImgReset, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ConfirmImgReset, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_ConfirmImgReset, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ConfirmImgReset, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_img_src( ui_ConfirmImgReset, &ui_img_1215410760, LV_PART_MAIN | LV_STATE_DEFAULT );

ui_ConfirmBtnInit = lv_btn_create(ui_ScreenConfirm);
lv_obj_set_width( ui_ConfirmBtnInit, 150);
lv_obj_set_height( ui_ConfirmBtnInit, 60);
lv_obj_set_x( ui_ConfirmBtnInit, 370 );
lv_obj_set_y( ui_ConfirmBtnInit, 185 );
lv_obj_set_align( ui_ConfirmBtnInit, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_ConfirmBtnInit, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ConfirmBtnInit, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_ConfirmBtnInit, lv_color_hex(0xF9E6C6), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ConfirmBtnInit, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_grad_color(ui_ConfirmBtnInit, lv_color_hex(0xE2AE6C), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_grad_dir(ui_ConfirmBtnInit, LV_GRAD_DIR_VER, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmLabelinit = lv_label_create(ui_ConfirmBtnInit);
lv_obj_set_width( ui_ConfirmLabelinit, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ConfirmLabelinit, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_ConfirmLabelinit, 30 );
lv_obj_set_y( ui_ConfirmLabelinit, 0 );
lv_obj_set_align( ui_ConfirmLabelinit, LV_ALIGN_LEFT_MID );
lv_label_set_text(ui_ConfirmLabelinit,"初始化");
lv_obj_set_style_text_color(ui_ConfirmLabelinit, lv_color_hex(0x492B06), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_ConfirmLabelinit, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_ConfirmLabelinit, &ui_font_CN24, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConfirmImgReinit = lv_btn_create(ui_ConfirmBtnInit);
lv_obj_set_width( ui_ConfirmImgReinit, 40);
lv_obj_set_height( ui_ConfirmImgReinit, 40);
lv_obj_set_x( ui_ConfirmImgReinit, -15 );
lv_obj_set_y( ui_ConfirmImgReinit, 0 );
lv_obj_set_align( ui_ConfirmImgReinit, LV_ALIGN_LEFT_MID );
lv_obj_add_flag( ui_ConfirmImgReinit, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ConfirmImgReinit, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_ConfirmImgReinit, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ConfirmImgReinit, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_img_src( ui_ConfirmImgReinit, &ui_img_1839223040, LV_PART_MAIN | LV_STATE_DEFAULT );

}