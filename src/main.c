//Standard C
//ASF
#include <asf.h>
//Custom
#include "modules/clock.h"
#include "modules/config.h"
#include "modules/datetime.h"
#include "modules/display.h"
#include "modules/joystick.h"
#include "modules/menu.h"
#include "modules/serial.h"
#include "modules/timeswitches.h"
#include "modules/flash_memory.h"

void init_device(void);
void init_modules(void);
void run_application(void);

int i;

int main (void)
{
	init_device();
	init_modules();
	run_application();
}

void init_device()
{
	INTC_init_interrupts();
	irq_initialize_vectors();
	cpu_irq_enable();
	sleepmgr_init();
	sysclk_init();
	board_init();
}

void init_modules()
{
	config_init();
	serial_init();
	display_init();
	joystick_init();
	clock_init();
	menu_init(); 
	datetime_init();
	timeswitches_init();
	test_func();
}

void run_application()
{
	display_clear();
	display_print("Application started");
	while(true)
	{
		menu_update();
		display_update();
		clock_update();
	}
}