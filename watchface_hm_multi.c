/*
 * =====================================================================================
 * 
 *    Corporation:  dscao(大胜). All Rights Reserved.
 *       Filename:  Multi_watchface.c
 *         Author:  dscao , dscao.com@gmail.com
 *        Created:  2016年1月8日 01时20分30秒
 * 
 *    Description:  
 *
 * =====================================================================================
 *
 * =====================================================================================
 * 
 *   MODIFICATION HISTORY :
 *    
 *		     DATE :
 *		     DESC :
 * =====================================================================================
 */	
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "maibu_sdk.h"
#include "maibu_res.h"




/*窗口ID, 通过该窗口ID获取窗口句柄*/
static int32_t g_app_mwd_window_id = -1;

/*小时分钟图层ID，通过该图层ID获取图层句柄*/
static int16_t g_app_mwd_hm_layer_id = -1;
static int16_t g_app_mwd_week_layer_id = -1;
static int16_t g_app_mwd_day_layer_id = -1;
static int16_t g_app_mwd_ble_layer_id = -1;
static int16_t g_app_mwd_pressure_layer_id = -1;
static int8_t g_app_mwd_battery_layer_id = -1;
static int16_t g_app_mwd_weeks_layer_id = -1;
static int16_t g_app_mwd_days_layer_id = -1;
static int8_t g_app_mwd_steps_layer_id = -1;
static int8_t g_app_mwd_climb_layer_id = -1;
static int8_t g_app_mwd_temperature_layer_id = -1;

static uint8_t app_timer_change_id = -1;

/*定时器状态static int accel_event = 0;*/
static	int accel_event = 0;
static	int accel_show = 0;

/*背景图片图层位置*/

#define MWD_BG_ORIGIN_X		0
#define MWD_BG_ORIGIN_Y		0	
#define MWD_BG_SIZE_H		128
#define MWD_BG_SIZE_W		128



/*显示小时分钟文本图层*/
#define MWD_HM_ORIGIN_X 		2
#define MWD_HM_ORIGIN_Y		20
#define MWD_HM_SIZE_H   		28		
#define MWD_HM_SIZE_W  		84

/*显示星期文本图层*/
#define MWD_WEEK_ORIGIN_X		2
#define MWD_WEEK_ORIGIN_Y		52	
#define MWD_WEEK_SIZE_H		18
#define MWD_WEEK_SIZE_W		124

/*蓝牙图层位置*/
#define MWD_BLE_ORIGIN_X		4
#define MWD_BLE_ORIGIN_Y		4	
#define MWD_BLE_SIZE_H		9
#define MWD_BLE_SIZE_W		9

/*气压图层位置*/
#define MWD_PRESSURE_ORIGIN_X		22
#define MWD_PRESSURE_ORIGIN_Y		2	
#define MWD_PRESSURE_SIZE_H		15
#define MWD_PRESSURE_SIZE_W		66

/*电量图层位置*/
#define MWD_BATTERY_ORIGIN_X		96
#define MWD_BATTERY_ORIGIN_Y		3	
#define MWD_BATTERY_SIZE_H		12
#define MWD_BATTERY_SIZE_W		26

/*周图层位置*/
#define MWD_WEEKS_ORIGIN_X		88
#define MWD_WEEKS_ORIGIN_Y		20	
#define MWD_WEEKS_SIZE_H		14
#define MWD_WEEKS_SIZE_W		38

/*天图层位置*/
#define MWD_DAYS_ORIGIN_X		88
#define MWD_DAYS_ORIGIN_Y		34	
#define MWD_DAYS_SIZE_H		14
#define MWD_DAYS_SIZE_W		38

/*步数图层位置*/
#define MWD_STEPS_ORIGIN_X		20
#define MWD_STEPS_ORIGIN_Y		116	
#define MWD_STEPS_SIZE_H		10
#define MWD_STEPS_SIZE_W		50

/*爬升高度图层位置*/
#define MWD_CLIMB_ORIGIN_X		88
#define MWD_CLIMB_ORIGIN_Y		116	
#define MWD_CLIMB_SIZE_H		10
#define MWD_CLIMB_SIZE_W		40

/*天气图标图层位置*/
#define MWD_TQTB_ORIGIN_X		10
#define MWD_TQTB_ORIGIN_Y		76	
#define MWD_TQTB_SIZE_H		30
#define MWD_TQTB_SIZE_W		30

/*天气温度图层位置*/
#define MWD_TQWD_ORIGIN_X		70
#define MWD_TQWD_ORIGIN_Y		76	
#define MWD_TQWD_SIZE_H		30
#define MWD_TQWD_SIZE_W		40

/*实测手表温度图层位置*/
#define MWD_TEMPERATURE_ORIGIN_X		2
#define MWD_TEMPERATURE_ORIGIN_Y		78	
#define MWD_TEMPERATURE_SIZE_H		34
#define MWD_TEMPERATURE_SIZE_W		124

/*声明自定义函数*/

int diday(int year, int month, int day);
int diweek(int didays,int weekday) ;


/*年*/
int16_t g_official_year = -1;
/*月*/
int8_t g_official_month = -1;
/*日*/
int8_t g_official_day = -1;

/*蓝牙是否已断开*/
int8_t g_official_bledis = -1;

void app_mwd_watch_update()
{
	/*根据窗口ID获取窗口句柄*/
		P_Window p_window = app_window_stack_get_window_by_id(g_app_mwd_window_id);	
		if (NULL == p_window)
		{
			return ;
		}
		/*根据图层ID获取图层句柄*/
		P_Layer p_hm_layer = app_window_get_layer_by_id(p_window, g_app_mwd_hm_layer_id);
		if (NULL == p_hm_layer)
		{
			return;
		}
		
		P_Layer p_week_layer = app_window_get_layer_by_id(p_window, g_app_mwd_week_layer_id);
		if (NULL == p_week_layer)
		{
			return;
		}
		
		
		P_Layer p_ble_layer = app_window_get_layer_by_id(p_window, g_app_mwd_ble_layer_id);
		if (NULL == p_ble_layer)
		{
			return;
		}
		
				
		P_Layer p_battery_layer = app_window_get_layer_by_id(p_window, g_app_mwd_battery_layer_id);
		if (NULL == p_battery_layer)
		{
			return;
		}
		
		P_Layer p_weeks_layer = app_window_get_layer_by_id(p_window, g_app_mwd_weeks_layer_id);
		if (NULL == p_weeks_layer)
		{
			return;
		}
		
		P_Layer p_days_layer = app_window_get_layer_by_id(p_window, g_app_mwd_days_layer_id);
		if (NULL == p_days_layer)
		{
			return;
		}
		
		P_Layer p_steps_layer = app_window_get_layer_by_id(p_window, g_app_mwd_steps_layer_id);
		if (NULL == p_steps_layer)
		{
			return;
		}
		
		P_Layer p_climb_layer = app_window_get_layer_by_id(p_window, g_app_mwd_climb_layer_id);
		if (NULL == p_climb_layer)
		{
			return;
		}
		
		P_Layer p_pressure_layer = app_window_get_layer_by_id(p_window, g_app_mwd_pressure_layer_id);
		if (NULL == p_pressure_layer)
		{
			return;
		}
		
		P_Layer p_temperature_layer = app_window_get_layer_by_id(p_window, g_app_mwd_temperature_layer_id);
		if (NULL == p_temperature_layer)
		{
			return;
		}
		
		
		char str[20] ="", buf[]="内部温度：25.5度", buf2[]="海拔：8888m";
		struct date_time datetime;
		app_service_get_datetime(&datetime);
		sprintf(str, "%02d:%02d", datetime.hour, datetime.min);
		app_layer_set_text_text(p_hm_layer, str);	
	
	/*每天凌晨更新日期*/	
	if ( (datetime.mday != g_official_day) || (datetime.year != g_official_year) || (datetime.mon != g_official_month))
	{
		memset(str, 0, sizeof(str));
		char wday[7][8]={"周日","周一","周二","周三","周四","周五","周六"}; 
		sprintf(str, "%s  %d/%d/%d", wday[datetime.wday], datetime.year, datetime.mon, datetime.mday);
		app_layer_set_text_text(p_week_layer, str);
		
		sprintf(str, "%d天", diday(datetime.year,datetime.mon,datetime.mday));
		app_layer_set_text_text(p_days_layer, str);
		sprintf(str, "%d周", diweek(diday(datetime.year,datetime.mon,datetime.mday),datetime.wday));
		app_layer_set_text_text(p_weeks_layer, str);
		
		g_official_year = datetime.year;
		g_official_month = datetime.mon;
		g_official_day = datetime.mday;
	}			
		
						
		
		
		
		/*电量状态*/
		int8_t percent;
		maibu_get_battery_percent(&percent);
		sprintf(str, "%d", percent);
		app_layer_set_text_text(p_battery_layer, str);
				
		/*更新运动步数*/
		SportData data;
		if (0 == maibu_get_sport_data(&data, 0))
		{
			sprintf(str, "%d", data.step);	
			app_layer_set_text_text(p_steps_layer, str);
			sprintf(str, "%dm", data.floor*3);	
			app_layer_set_text_text(p_climb_layer, str);	
		}
		
		/*更新气压*/
		float pressure;
		if (0 == maibu_get_pressure(&pressure))
		{
			sprintf(str, "%0.1f hPa", pressure);
			app_layer_set_text_text(p_pressure_layer, str);	
		}
		/*更新温度*/
		float temp;
		if (0 == maibu_get_temperature(&temp))
		{sprintf(buf, "内部温度：%0.1f 度", temp);

			app_layer_set_text_text(p_temperature_layer, buf);	
		}
		
		
		
	
		
	app_window_update(p_window);
	
}

void app_ble_change()
{	
	
	P_Window p_window = app_window_stack_get_window_by_id(g_app_mwd_window_id);	
	if (NULL == p_window)
	{
		return ;
	}
	P_Layer p_ble_layer = app_window_get_layer_by_id(p_window, g_app_mwd_ble_layer_id);
	if (NULL == p_ble_layer)
	{
		return;
	}

	
	/*蓝牙状态更改*/
	GBitmap bitmap_ble_con;
	GBitmap bitmap_ble_discon;
	GRect frame_ble = {{MWD_BLE_ORIGIN_X, MWD_BLE_ORIGIN_Y}, {MWD_BLE_SIZE_H, MWD_BLE_SIZE_W}};
	res_get_user_bitmap(RES_BITMAP_BLE_CONNECTED, &bitmap_ble_con);
	res_get_user_bitmap(RES_BITMAP_BLE_DISCONNECTED, &bitmap_ble_discon);
	LayerBitmap layer_bitmap_ble_con = { bitmap_ble_con,frame_ble,GAlignCenter };
	LayerBitmap layer_bitmap_ble_discon = { bitmap_ble_discon,frame_ble,GAlignCenter };
	enum BleStatus ble_sta;
	ble_sta = maibu_get_ble_status();
	if (ble_sta != BLE_STATUS_CONNECTED && ble_sta != BLE_STATUS_USING) {
		if (g_official_bledis == 0)
		{
		P_Layer layer_ble_new = app_layer_create_bitmap(&layer_bitmap_ble_discon);
		app_layer_set_bg_color(layer_ble_new, GColorBlack);
		g_app_mwd_ble_layer_id = app_window_replace_layer(p_window, p_ble_layer, layer_ble_new);
		app_window_update(p_window);
		g_official_bledis = 1;
		maibu_service_vibes_pulse(VibesPulseTypeShort,1);
		}
	}
	else if (ble_sta = BLE_STATUS_CONNECTED) {
		if (g_official_bledis == 1)
		{
		P_Layer layer_ble_new = app_layer_create_bitmap(&layer_bitmap_ble_con);
		app_layer_set_bg_color(layer_ble_new, GColorBlack);
		g_app_mwd_ble_layer_id = app_window_replace_layer(p_window, p_ble_layer, layer_ble_new);
		app_window_update(p_window);
		g_official_bledis = 0;
		}
	}
	
}


void app_mwd_watch_time_change(enum SysEventType type, void *context)
{

	/*时间更改*/
	if (type == SysEventTypeTimeChange)
	{
		app_mwd_watch_update();
	}
}




P_Window init_mwd_window()
{
	P_Window p_window = app_window_create();
	if (NULL == p_window)
	{
		return NULL;
	}

	char str[20] = "", buf[]="温度：25.5C", buf2[]="海拔：1111m";;

	
	/*添加背景图层*/
	GRect frame = {{MWD_BG_ORIGIN_X, MWD_BG_ORIGIN_Y}, {MWD_BG_SIZE_H, MWD_BG_SIZE_W}};
	GBitmap bitmap;		
	res_get_user_bitmap(RES_BITMAP_BG, &bitmap);
	LayerBitmap layer_bitmap = {bitmap, frame, GAlignCenter};
	P_Layer layer = app_layer_create_bitmap(&layer_bitmap);
	app_layer_set_bg_color(layer, GColorBlack);
	app_window_add_layer(p_window, layer);

	/*添加小时分钟图层*/
	GRect frame_hm = {{MWD_HM_ORIGIN_X, MWD_HM_ORIGIN_Y}, {MWD_HM_SIZE_H, MWD_HM_SIZE_W}};
	struct date_time t;
	app_service_get_datetime(&t);
	char time_str[20] = "";
	sprintf(time_str, "%02d:%02d", t.hour, t.min);
	LayerText lt_hm = {time_str, frame_hm, GAlignLeft, U_ASCII_ARIALBD_30, 0};
	P_Layer layer_text_hm = app_layer_create_text(&lt_hm);
	if(layer_text_hm != NULL)
	{	app_layer_set_bg_color(layer_text_hm, GColorBlack);	
		g_app_mwd_hm_layer_id = app_window_add_layer(p_window, layer_text_hm);
	}
	
	/*添加日期星期状态图层*/
	GRect frame_week = {{MWD_WEEK_ORIGIN_X, MWD_WEEK_ORIGIN_Y}, {MWD_WEEK_SIZE_H, MWD_WEEK_SIZE_W}};
	char week_str[20] = "";
	memset(week_str, 0, sizeof(week_str));
	char wday[7][8]={"周日","周一","周二","周三","周四","周五","周六"}; 
	sprintf(week_str, "%s  %d/%d/%d", wday[t.wday], t.year, t.mon, t.mday);
	LayerText lt_week = {week_str, frame_week, GAlignCenter, U_GBK_SIMSUN_14, 0};
	P_Layer layer_text_week = app_layer_create_text(&lt_week);
	if(layer_text_week != NULL)
	{
		app_layer_set_bg_color(layer_text_week, GColorBlack);	
		g_app_mwd_week_layer_id = app_window_add_layer(p_window, layer_text_week);
	}
	/*添加周图层*/
	GRect frame_weeks = {{MWD_WEEKS_ORIGIN_X, MWD_WEEKS_ORIGIN_Y}, {MWD_WEEKS_SIZE_H, MWD_WEEKS_SIZE_W}};
	char weeks_str[6] = "";
	sprintf(weeks_str, "%d周", diweek(diday(t.year,t.mon,t.mday),t.wday));
	LayerText lt_weeks = {weeks_str, frame_weeks, GAlignRight, U_GBK_SIMSUN_12, 0};
	P_Layer layer_text_weeks = app_layer_create_text(&lt_weeks);	
	if(layer_text_weeks != NULL)
	{
		app_layer_set_bg_color(layer_text_weeks, GColorBlack);	
		g_app_mwd_weeks_layer_id = app_window_add_layer(p_window, layer_text_weeks);
	}
	/*添加天图层*/
	GRect frame_days = {{MWD_DAYS_ORIGIN_X, MWD_DAYS_ORIGIN_Y}, {MWD_DAYS_SIZE_H, MWD_DAYS_SIZE_W}};
	char days_str[8] = "";
	sprintf(days_str, "%d天", diday(t.year,t.mon,t.mday));
	LayerText lt_days = {days_str, frame_days, GAlignRight, U_GBK_SIMSUN_12, 0};
	P_Layer layer_text_days = app_layer_create_text(&lt_days);
		if(layer_text_days != NULL)
	{
		app_layer_set_bg_color(layer_text_days, GColorBlack);
		g_app_mwd_days_layer_id = app_window_add_layer(p_window, layer_text_days);
	}	
	
	
	/*添加电量数据图层显示电量百分比*/
	GRect frame_battery = {{MWD_BATTERY_ORIGIN_X, MWD_BATTERY_ORIGIN_Y}, {MWD_BATTERY_SIZE_H, MWD_BATTERY_SIZE_W}};
	int8_t percent;
	maibu_get_battery_percent(&percent);
	sprintf(str, "%d", percent);
	LayerText lt_battery = {str, frame_battery, GAlignCenter, U_ASCII_ARIAL_12, 0};
	P_Layer layer_battery = app_layer_create_text(&lt_battery);
	app_layer_set_bg_color(layer_battery, GColorBlack);
	if(layer_battery != NULL)
	{
		g_app_mwd_battery_layer_id = app_window_add_layer(p_window, layer_battery);
	}
	
		
	/*添加运动数据图层*/
	GRect frame_steps =  {{MWD_STEPS_ORIGIN_X, MWD_STEPS_ORIGIN_Y}, {MWD_STEPS_SIZE_H, MWD_STEPS_SIZE_W}};
	GRect frame_climb =  {{MWD_CLIMB_ORIGIN_X, MWD_CLIMB_ORIGIN_Y}, {MWD_CLIMB_SIZE_H, MWD_CLIMB_SIZE_W}};
	SportData data;
	if (0 == maibu_get_sport_data(&data, 0))
	{
		sprintf(str, "%d", data.step);
		LayerText lt_steps = {str, frame_steps, GAlignCenter, U_ASCII_ARIAL_12, 0};
		P_Layer layer_steps = app_layer_create_text(&lt_steps);
		app_layer_set_bg_color(layer_steps, GColorBlack);
		sprintf(str, "%dm", data.floor*3);
		LayerText lt_climb = {str, frame_climb, GAlignCenter, U_ASCII_ARIAL_12, 0};
		P_Layer layer_climb = app_layer_create_text(&lt_climb);
		app_layer_set_bg_color(layer_climb, GColorBlack);
		if(layer_steps != NULL)
		{
			g_app_mwd_steps_layer_id = app_window_add_layer(p_window, layer_steps);
		}
		if(layer_climb != NULL)
		{
			g_app_mwd_climb_layer_id = app_window_add_layer(p_window, layer_climb);
		}
			
	}
	
	
	/*添加气压数据图层*/
	GRect frame_pressure = {{MWD_PRESSURE_ORIGIN_X, MWD_PRESSURE_ORIGIN_Y}, {MWD_PRESSURE_SIZE_H, MWD_PRESSURE_SIZE_W}};
	sprintf(str, "checking");
	LayerText lt_pressure = {str, frame_pressure, GAlignCenter, U_ASCII_ARIAL_12, 0};
	P_Layer layer_pressure = app_layer_create_text(&lt_pressure);
	app_layer_set_bg_color(layer_pressure, GColorBlack);
	if(layer_pressure != NULL)
	{
		g_app_mwd_pressure_layer_id = app_window_add_layer(p_window, layer_pressure);
	}
			
	/*添加手表实测温度图层*/
	GRect frame_temperature = {{MWD_TEMPERATURE_ORIGIN_X, MWD_TEMPERATURE_ORIGIN_Y}, {MWD_TEMPERATURE_SIZE_H, MWD_TEMPERATURE_SIZE_W}};
	float temp;
	if (0 == maibu_get_temperature(&temp))
	{
	sprintf(buf, "内部温度：检测中.", temp);
	LayerText layer_text_temperature = {buf, frame_temperature, GAlignCenter,  U_GBK_SIMSUN_12, 0};
	P_Layer layer_temperature = app_layer_create_text(&layer_text_temperature);
	if(layer_temperature != NULL)
	{
		app_layer_set_bg_color(layer_temperature, GColorBlack);
		g_app_mwd_temperature_layer_id = app_window_add_layer(p_window, layer_temperature);
	}
	}

	/*添加蓝牙图层,有接口后要加入判断是否显示哪一个图*/
	GRect frame_ble = {{MWD_BLE_ORIGIN_X, MWD_BLE_ORIGIN_Y}, {MWD_BLE_SIZE_H, MWD_BLE_SIZE_W}};
	GBitmap bitmap_ble;	
	res_get_user_bitmap(RES_BITMAP_BLE_CONNECTED, &bitmap_ble);
	LayerBitmap layer_bitmap_ble = {bitmap_ble, frame_ble, GAlignCenter};
	P_Layer layer_ble = app_layer_create_bitmap(&layer_bitmap_ble);
	if(layer_ble != NULL)
	{
		app_layer_set_bg_color(layer_ble, GColorBlack);
		g_app_mwd_ble_layer_id = app_window_add_layer(p_window, layer_ble);
	}	
	g_official_bledis = 0;
	
	
	
	/*注册一个事件通知回调，当有时间改变时，立即更新时间*/
	maibu_service_sys_event_subscribe(app_mwd_watch_time_change);

	return p_window;

}



int diday(int year, int month, int day) 
{
	int sum,leap;
	if (month== 1){
	sum=0;
	}
	if (month== 2){
	sum=33;
	}
	if (month== 3){
	sum=59;
	}
	if (month== 4){
	sum=90;
	}
	if (month== 5){
	sum=120;
	}
	if (month== 6){
	sum=151;
	}
	if (month== 7){
	sum=181;
	}
	if (month== 8){
	sum=212;
	}
	if (month== 9){
	sum=243;
	}
	if (month== 10){
	sum=273;
	}
	if (month== 11){
	sum=304;
	}
	if (month== 12){
	sum=334;
	}
	sum=sum+day; /*再加上某天的天数*/
	if(year%400==0||(year%4==0&&year%100!=0)) {/*判断是不是闰年*/
	leap=1;
	}
	else{
	leap=0;
	}
	if(leap==1&&month>2){/*如果是闰年且月份大于2,总天数应该加一天*/
	sum=sum+1;
	}
	
	return sum;
}

int diweek(int didays,int weekday) 
{
	int dizous;	
	int base;
	if (didays<weekday)
		base=weekday + 1-didays;
	else
		base=7 - (didays - ( weekday + 1)) % 7;
	int weekadd = (didays % 7 + base -1 ) > 7 ? 1 : 0; 
    dizous = didays / 7 + weekadd + 1; 
	return dizous;
}


int main()
{
/*simulator_init();*/
	/*创建显示时间窗口*/
	P_Window p_window = init_mwd_window();
	if (p_window != NULL)
	{
		/*放入窗口栈显示*/
		g_app_mwd_window_id = app_window_stack_push(p_window);
		app_mwd_watch_update();
	}	
	/*每2秒刷新*/
	app_timer_change_id = app_service_timer_subscribe(1000*2, app_ble_change, NULL);
/*simulator_wait();*/

}
