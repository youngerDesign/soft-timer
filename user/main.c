#include "sys.h"
#include "usart.h"
#include "delay.h"

#include "app_key.h"
#include "app_led.h"
#include "app_timer.h"
#include "app_softTimer.h"

uint8_t g_timer1ThreadMessageQueue = 0;
uint8_t g_timer2ThreadMessageQueue = 0;
uint8_t g_timer3ThreadMessageQueue = 0;
void Timer1Callback(void);
void Timer2Callback(void);
void Timer3Callback(void);

void APP_TestThreadEntry(void);

int main(void)
{

	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72); //延时初始化
	uart_init(72,115200); //串口初始化为 115200

	SoftTimerInit();

	DDA_Timer_t* timer1 = DDA_TimerCreate(Timer1Callback, 1, 2000);
	DDA_TimerStart(timer1);

	DDA_Timer_t* timer2 = DDA_TimerCreate(Timer2Callback, 1, 3000);
	DDA_TimerStart(timer2);
	
	DDA_Timer_t* timer3 = DDA_TimerCreate(Timer3Callback, 1, 800);
	DDA_TimerStart(timer3);

	printf("timer init completed:%d\r\n", GetTick());
	uint8_t flag = 0;
	while(1)
	{
		APP_TestThreadEntry();
	}
}

void Timer1Callback(void)
{
	g_timer1ThreadMessageQueue++; //模拟消息队列
}

void Timer2Callback(void)
{
	g_timer2ThreadMessageQueue++;
}

void Timer3Callback(void)
{
	g_timer3ThreadMessageQueue++;
}

void APP_TestThreadEntry(void)
{
	if (g_timer1ThreadMessageQueue != 0) { // A线程收到timer线程发来的timeout消息
		g_timer1ThreadMessageQueue--;
		printf("timer1 timeout tick:%d\r\n", GetTick());
	}
	
	if (g_timer2ThreadMessageQueue != 0) { // B线程收到timer线程发来的timeout消息
		g_timer2ThreadMessageQueue--;
		printf("timer2 timeout tick:%d\r\n", GetTick());
	}
	
	if (g_timer3ThreadMessageQueue != 0) { // C线程收到timer线程发来的timeout消息
		g_timer3ThreadMessageQueue--;
		printf("timer3 timeout tick:%d\r\n", GetTick());
	}
}
