#include "app_led.h"

void LedInit(void)
{
	GPIO_ClockEnable(GPIO_GROUPB, TRUE);
	GPIO_ClockEnable(GPIO_GROUPE, TRUE);
	
	GPIO_Config_t config = {0};
	config.group = GPIO_GROUPB;
	config.pinMask |= (1<<GPIO_PIN5);
	config.mode = GPIO_Mode_PUSH_PULL;
	config.directionSpeed = GPIO_OUTPUT_MODE_SPEED50MHZ;
	config.defaultLevel = GPIO_PIN_LEVEL_HIGH;
	GPIO_Config(&config);
	
	config.group = GPIO_GROUPE;
	GPIO_Config(&config);
}




