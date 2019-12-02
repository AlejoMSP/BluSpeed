//#if defined(MCU_STM32F103C8) || defined(MCU_STM32F103CB)
//#if defined(PILL_F103XX)
#ifndef BLUE_PILL_H
#define BLUE_PILL_H
/*
***********************************************************************************************************
* General
*/
  #define PORT_TYPE uint32_t
  #define PINMASK_TYPE uint32_t
  #define COMPARE_TYPE uint16_t
  #define COUNTER_TYPE uint16_t
  
  #define micros_safe() micros() //timer5 method is not used on anything but AVR, the micros_safe() macro is simply an alias for the normal micros()

  #ifndef Serial
    #define Serial Serial1
  #endif

  #ifndef CANSerial
    #define CANSerial Serial1
  #endif
  
  #ifndef USE_SERIAL3
    #define USE_SERIAL3
    #define EEPROM_LIB_H <EEPROM.h>
  #endif
  
  void initBoard();
  uint16_t freeRam();
  extern "C" char* sbrk(int incr);

	//.arduino15/packages/STM32/hardware/stm32/1.7.0/variants/PILL_F103XX/variant.cpp
	#define A0 PA0
	#define A1 PA1
	#define A2 PA2
	#define A3 PA3
	#define A4 PA4
	#define A5 PA5
	#define A6 PA6
	#define A7 PA7
	#define A8 PB0
	#define A9 PB1

  //STM32F1 have only 9 12bit adc
  #define A10  PA7
  #define A11  PA6
  #define A12  PA5
  #define A13  PA4
  #define A14  PA3
  #define A15  PA2

	/*  STM32F1/variants/.../board.cpp
	#define A0  PB0
	#define A1  PA7
	#define A2  PA6
	#define A3  PA5
	#define A4  PA4
	#define A5  PA3
	#define A6  PA2
	#define A7  PA1
	#define A8  PA0
	//STM32F1 have only 9 12bit adc
	#define A9  PB0
	#define A10  PA7
	#define A11  PA6
	#define A12  PA5
	#define A13  PA4
	#define A14  PA3
	#define A15  PA2
	*/


/*
***********************************************************************************************************
* Schedules
* Timers Table for STM32F1
*   TIMER1    TIMER2    TIMER3    TIMER4
* 1 -       1 - INJ1  1 - IGN1  1 - oneMSInterval
* 2 - BOOST 2 - INJ2  2 - IGN2  2 -
* 3 - VVT   3 - INJ3  3 - IGN3  3 -
* 4 - IDLE  4 - INJ4  4 - IGN4  4 -
*
*/
  #define MAX_TIMER_PERIOD 65535*2 //The longest period of time (in uS) that the timer can permit (IN this case it is 65535 * 2, as each timer tick is 2uS)
  #define uS_TO_TIMER_COMPARE(uS) (uS >> 1) //Converts a given number of uS into the required number of timer ticks until that time has passed.

	//STM32DUINO
  #define FUEL1_COUNTER (TIM2)->CNT
  #define FUEL2_COUNTER (TIM2)->CNT
  #define FUEL3_COUNTER (TIM2)->CNT
  #define FUEL4_COUNTER (TIM2)->CNT

  #define FUEL1_COMPARE (TIM2)->CCR1
  #define FUEL2_COMPARE (TIM2)->CCR2
  #define FUEL3_COMPARE (TIM2)->CCR3
  #define FUEL4_COMPARE (TIM2)->CCR4

  #define IGN1_COUNTER  (TIM3)->CNT
  #define IGN2_COUNTER  (TIM3)->CNT
  #define IGN3_COUNTER  (TIM3)->CNT
  #define IGN4_COUNTER  (TIM3)->CNT

  #define IGN1_COMPARE (TIM3)->CCR1
  #define IGN2_COMPARE (TIM3)->CCR2
  #define IGN3_COMPARE (TIM3)->CCR3
  #define IGN4_COMPARE (TIM3)->CCR4
  
  #define FUEL1_TIMER_ENABLE() (TIM2)->CCER |= TIM_CCER_CC1E
  #define FUEL2_TIMER_ENABLE() (TIM2)->CCER |= TIM_CCER_CC2E
  #define FUEL3_TIMER_ENABLE() (TIM2)->CCER |= TIM_CCER_CC3E
  #define FUEL4_TIMER_ENABLE() (TIM2)->CCER |= TIM_CCER_CC4E

  #define FUEL1_TIMER_DISABLE() (TIM2)->CCER &= ~TIM_CCER_CC1E
  #define FUEL2_TIMER_DISABLE() (TIM2)->CCER &= ~TIM_CCER_CC2E
  #define FUEL3_TIMER_DISABLE() (TIM2)->CCER &= ~TIM_CCER_CC3E
  #define FUEL4_TIMER_DISABLE() (TIM2)->CCER &= ~TIM_CCER_CC4E

  #define IGN1_TIMER_ENABLE() (TIM3)->CCER |= TIM_CCER_CC1E
  #define IGN2_TIMER_ENABLE() (TIM3)->CCER |= TIM_CCER_CC2E
  #define IGN3_TIMER_ENABLE() (TIM3)->CCER |= TIM_CCER_CC3E
  #define IGN4_TIMER_ENABLE() (TIM3)->CCER |= TIM_CCER_CC4E

  #define IGN1_TIMER_DISABLE() (TIM3)->CCER &= ~TIM_CCER_CC1E
  #define IGN2_TIMER_DISABLE() (TIM3)->CCER &= ~TIM_CCER_CC2E
  #define IGN3_TIMER_DISABLE() (TIM3)->CCER &= ~TIM_CCER_CC3E
  #define IGN4_TIMER_DISABLE() (TIM3)->CCER &= ~TIM_CCER_CC4E
/*
***********************************************************************************************************
* Auxilliaries
*/
	//STM32DUINO
  #define ENABLE_BOOST_TIMER()  (TIM1)->CCER |= TIM_CCER_CC2E
  #define DISABLE_BOOST_TIMER() (TIM1)->CCER &= ~TIM_CCER_CC2E

  #define ENABLE_VVT_TIMER()    (TIM1)->CCER |= TIM_CCER_CC3E
  #define DISABLE_VVT_TIMER()   (TIM1)->CCER &= ~TIM_CCER_CC3E

  #define BOOST_TIMER_COMPARE   (TIM1)->CCR2
  #define BOOST_TIMER_COUNTER   (TIM1)->CNT
  #define VVT_TIMER_COMPARE     (TIM1)->CCR3
  #define VVT_TIMER_COUNTER     (TIM1)->CNT

/*
***********************************************************************************************************
* Idle
*/
	//STM32DUINO
  #define IDLE_COUNTER   (TIM1)->CNT
  #define IDLE_COMPARE   (TIM1)->CCR4

  #define IDLE_TIMER_ENABLE()  (TIM1)->CCER |= TIM_CCER_CC4E
  #define IDLE_TIMER_DISABLE() (TIM1)->CCER &= ~TIM_CCER_CC4E

/*
***********************************************************************************************************
* Timers
*/
HardwareTimer Timer1(TIM1);
HardwareTimer Timer2(TIM2);
HardwareTimer Timer3(TIM3);
HardwareTimer Timer4(TIM4);


void oneMSInterval(HardwareTimer*);
void boostInterrupt(HardwareTimer*);
void fuelSchedule1Interrupt(HardwareTimer*);
void fuelSchedule2Interrupt(HardwareTimer*);
void fuelSchedule3Interrupt(HardwareTimer*);
void fuelSchedule4Interrupt(HardwareTimer*);
void idleInterrupt(HardwareTimer*);
void vvtInterrupt(HardwareTimer*);
void ignitionSchedule1Interrupt(HardwareTimer*);
void ignitionSchedule2Interrupt(HardwareTimer*);
void ignitionSchedule3Interrupt(HardwareTimer*);
void ignitionSchedule4Interrupt(HardwareTimer*);
void ignitionSchedule5Interrupt(HardwareTimer*);

/*
***********************************************************************************************************
* CAN / Second serial
*/

#endif
//#endif //CORE_STM32
