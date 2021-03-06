#include "LPC407x_8x_177x_8x.h"

#include "Library/GPIO.h"
#include "Library/Joystick.h"
#include "Library/PWM.h"
int speed = 100;
void init() {
	Joystick_Init();
	
	PWM_Init();
	PCONP |= (1<<6);
	PORT1->DIR |= (1<<24)|(1<<23);
	
}

// When code start, LED should be turned off.
// When you press the UP button of the Joystick, LED will be turned on (use 100% Duty Cycle)
// When you press the CENTER button of the Joystick, LED will be turned on (use 50% Duty Cycle)
// When you press the DOWN button of the Joystick, LED will be turned off.
// When you press the LEFT button of the Joystick, LED will blink (2 times in a second).
// When you press the RIGHT button of the Joystick, LED will blink (10 times in a second).
void update() {
	
	if(Joystick_Up_Pressed()){
		uint32_t value = PORT1->PIN;
	value &= ~(1<<24);
	value |= (1<<23);
	PORT1->PIN = value;
		PWM_Write(100);
	}else if(Joystick_Center_Pressed()){
		
	}else if(Joystick_Down_Pressed()){
		 uint32_t value = PORT1->PIN;
	value |= (1<<24);
	value |= (1<<23);
		
	PORT1->PIN = value;
		PWM_Write(0);
	}else if(Joystick_Left_Pressed()){
		int i = 0;
		int j = 0;
		for(i;i<100000000;i++){
		}
		speed = speed - 10;
		PWM_Write(speed);
		
	}else if(Joystick_Right_Pressed()){
		uint32_t value = PORT1->PIN;
	value |= (1<<24);
	value &= ~(1<<23);
	PORT1->PIN = value;
		PWM_Write(100);
   	
	}
}

int main() {
	init();
	
	while(1) {
		update();
	}
}

