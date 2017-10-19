#include "LPC407x_8x_177x_8x.h"

#include "Library/GPIO.h"
#include "Library/Joystick.h"
#include "Library/PWM.h"

void init() {
	Joystick_Init();
	
	PWM_Init();
	PWM_Write(0);
}

// When code start, LED should be turned off.
// When you press the UP button of the Joystick, LED will be turned on (use 100% Duty Cycle)
// When you press the CENTER button of the Joystick, LED will be turned on (use 50% Duty Cycle)
// When you press the DOWN button of the Joystick, LED will be turned off.
// When you press the LEFT button of the Joystick, LED will blink (2 times in a second).
// When you press the RIGHT button of the Joystick, LED will blink (10 times in a second).
void update() {
	if(Joystick_Up_Pressed()){
		PWM_Cycle_Rate(10);
		PWM_Write(100);
	}else if(Joystick_Center_Pressed()){
		PWM_Cycle_Rate(10);
		PWM_Write(50);
	}else if(Joystick_Down_Pressed()){
		PWM_Cycle_Rate(10);
		PWM_Write(0);
	}else if(Joystick_Left_Pressed()){
		PWM_Cycle_Rate(500);
	}else if(Joystick_Right_Pressed()){
   	PWM_Cycle_Rate(100);
	}
}

int main() {
	init();
	
	while(1) {
		update();
	}
}

