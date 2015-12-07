#include "modules/menus/menu_alert.h"
//C standard library
//ASF
//Modules
#include "modules/joystick.h"
#include "modules/menu.h"
#include "modules/timeswitches.h"
#include "modules/menus/editor_integer.h"
#include "modules/config.h"

menu_t* generate_alert_menu(menu_t* parentMenu, timeswitch_config_t* config, const char* menu_title);
menu_item_t* generate_alert_item(menu_t* parentMenu,  timeswitch_config_t* config, void (*on_click)(menu_item_t*), const char* item_title)
{
	menu_item_t* item = menu_add_item(parentMenu,item_title);
	item->on_click = on_click;
	item->user_data = config;
}


void repeat_canceled(menu_t*, editor_integer_data_t*);
void repeat_completed(menu_t*, editor_integer_data_t*);
void target_one(menu_item_t*);
void target_two(menu_item_t*);
void target_three(menu_item_t*);
void target_four(menu_item_t*);
void behavior_on(menu_item_t*);
void behavior_off(menu_item_t*);
void behavior_toggle(menu_item_t*);
void enable_alert(menu_item_t*);
void disable_alert(menu_item_t*);
void clear_settings(menu_item_t*);

const char* titles[] = {
	"Alert 1",
	"Alert 2",
	"Alert 3",
	"Alert 4"	
};

menu_t* generate_alerts_menu(menu_t* parentMenu, config_t* config)
{
	menu_t* alert_list = menu_add_submenu(parentMenu, "Configure alerts");
	for(int i = 0; i < TIMER_CONFIG_COUNT; i++)
	{
		generate_alert_menu(alert_list, (timeswitch_config_t*)&(config->timers[i]), titles[i]);
	}
	
}

menu_t* generate_alert_menu(menu_t* parentMenu, timeswitch_config_t* config, const char* menu_title)
{
	menu_t* alert_menu = menu_add_submenu(parentMenu, menu_title);
	
	menu_t* start_menu = menu_add_submenu(alert_menu, "Start");
	//tijd instellingen hier
	
	menu_t* interval_menu = menu_add_submenu(alert_menu, "Interval");
	//interval instellingen hier
	
	editor_integer_data_t data = {0};
	data.max = 10;
	data.min = 0;
	data.value = 5;
	data.on_cancel = repeat_canceled;
	data.on_completed = repeat_completed;
	data.user_data = config;
	generate_editor_integer(alert_menu, "Repeat", data);
	
	menu_t* target_menu = menu_add_submenu(alert_menu, "Target");
	generate_alert_item(target_menu, config, target_one, "Target one");
	generate_alert_item(target_menu, config, target_two, "Target two");
	generate_alert_item(target_menu, config, target_three, "Target three");
	generate_alert_item(target_menu, config, target_four, "Target four");
	
	menu_t* behavior_menu = menu_add_submenu(alert_menu, "Behavior");
	generate_alert_item(behavior_menu, config, behavior_on, "On");
	generate_alert_item(behavior_menu, config, behavior_off, "Off");
	generate_alert_item(behavior_menu, config, behavior_toggle, "Toggle");
	
	generate_alert_item(alert_menu, config, enable_alert, "Enable");
	generate_alert_item(alert_menu, config, disable_alert, "Disable");
	generate_alert_item(alert_menu, config, clear_settings, "Clear settings");
}


void repeat_canceled(menu_t* menu, editor_integer_data_t* data)
{
	
}

void repeat_completed(menu_t* menu, editor_integer_data_t* data)
{
	timeswitch_config_t* config = data->user_data;
	config->repeat_count = data->value;
}


void target_one(menu_item_t* item)
{
	timeswitch_config_t* config = item->user_data;
	config->output = 0;
}

void target_two(menu_item_t* item)
{
	timeswitch_config_t* config = item->user_data;
	config->output = 1;
}
void target_three(menu_item_t* item)
{
	timeswitch_config_t* config = item->user_data;
	config->output = 2;
}
void target_four(menu_item_t* item)
{
	timeswitch_config_t* config = item->user_data;
	config->output = 3;
}



void behavior_on(menu_item_t* item)
{
	timeswitch_config_t* config = item->user_data;
	config->behaviour = on;
}

void behavior_off(menu_item_t* item)
{
	timeswitch_config_t* config = item->user_data;
	config->behaviour = off;
}

void behavior_toggle(menu_item_t* item)
{
	timeswitch_config_t* config = item->user_data;
	config->behaviour = toggle;
}



void enable_alert(menu_item_t* item)
{
	timeswitch_config_t* config = item->user_data;
	config->enabled = true;
}

void disable_alert(menu_item_t* item)
{
	timeswitch_config_t* config = item->user_data;
	config->enabled = false;
}



void clear_settings(menu_item_t* item)
{
	timeswitch_config_t* config = item->user_data;
	config->behaviour = off;
	config->enabled = false;
	config->output = 0;
	config->repeat_count = 0;
	config->repeat_interval = 0;
	config->timestamp = 0;
}