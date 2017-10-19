#include "PWM.h"

void PWM_Init() {
	//Change the function of the pin in here:
uint32_t value = IOCON_LED;
	value &= ~(1<<2);
	value |= (1<<1)|(1<<0);
	IOCON_LED = value;
	//Turn on PWM
	PCONP |= (1<<5);
	//Enable PWM output for corresponding pin.
	PWMX->PCR |= (1<<9);
	//Reset The PWM Timer Counter and The PWM Prescale Counter on the Next Positive Edge of PCLK
	PWMX->TCR |= (1<<1);
	//Configure MR0 register for giving pulse every 20 ms.
	PWMX->MR0 = (PERIPHERAL_CLOCK_FREQUENCY / 1000000) * 20 * 1000;
	//Reset TC, when MR0 matches TC.
	PWMX->MCR |= (1<<1);
	//Enable PWM Match 0 Latch.
	PWMX->LER |= (1<<0);
	//Enable Counter and PWM and Clear Reset on the PWM
	PWMX->TCR &= ~(1<<1);
	PWMX->TCR |= (1<<0);
	PWMX->TCR |= (1<<3);
	//PWM_Write(100);
}

void PWM_Cycle_Rate(uint32_t period_In_Cycles) {
	//Write a formula that changes the MR0 register value for a given parameter.
	PWMX->MR0 =(PERIPHERAL_CLOCK_FREQUENCY / 1000000) *period_In_Cycles * 1000;
	//Enable PWM Match Register Latch for MR0.
	PWMX->LER |= (1<<0);
}

void PWM_Write(uint32_t T_ON) {	
	if(T_ON > 100) {
		T_ON = 100;
	}
	
	//Write a formula to calculate the match register for P30 (P1_2) pin.
		PWMX->MR1 = T_ON/100.0 * PWMX->MR0;	
	
	
	//If T_ON equal to MR0, there will be 1 Cycle Dropout. In order to prevent this, we increase the T_ON value.
	if (PWMX->MR1 == PWMX->MR0) {
		PWMX->MR1++;
	}
	
	//Enable PWM Match Register Latch.
	PWMX->LER |= (1<<1);
		
}
