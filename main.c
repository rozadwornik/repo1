#include <LPC21xx.H>

#define LED0_bm (1<<16)
#define LED1_bm (1<<17)
#define LED2_bm (1<<18)
#define LED3_bm (1<<19)
#define LED_ALL_bm 0x00010000 | 0x00020000 | 0x00040000 | 0x00080000
#define Butt0_bm (1<<4)
#define Butt1_bm (1<<5)
#define Butt2_bm (1<<6)
#define Butt3_bm (1<<7)
#define Buttons Butt0_bm | Butt1_bm | Butt2_bm | Butt3_bm

enum ButtonState {RELEASED, PRESSED};

enum KeyboardState {RELEASED_2, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};

enum Direction {LEFT, RIGHT};


void Delay(int DelayTime){
	int TimeScale=2400; 
	int i;
	int Iterations = TimeScale*DelayTime;
	for(i=0; i<Iterations; i++){
	}
}

void LedInit(){
	IO1DIR |= LED_ALL_bm;
	IO1SET |= LED0_bm;
}

void LedOn(unsigned char ucLedIndeks){
	switch(ucLedIndeks){
		case 0:
			IO1CLR = LED_ALL_bm;
			IO1SET = LED0_bm;
				break;
		case 1:
			IO1CLR = LED_ALL_bm;
			IO1SET = LED1_bm;
				break;
		case 2:
			IO1CLR = LED_ALL_bm;
			IO1SET = LED2_bm;
				break;
		case 3:
			IO1CLR = LED_ALL_bm;
			IO1SET = LED3_bm;
				break;
	}
}

enum ButtonState eReadButton1(){
	unsigned char ucButton1State = IO0PIN&Butt1_bm;
	if(ucButton1State == 0){
		return PRESSED;
	}
	return RELEASED;
}

void KeyboardInit(){
	IO0DIR |= Buttons;
	IO0SET |= Buttons;
}

enum KeyboardState eKeyboardRead(){
	if((IO0PIN & Butt0_bm) == 0){
		return BUTTON_0;
	}
	if((IO0PIN & Butt1_bm) == 0){
		return BUTTON_1;
	}
	if((IO0PIN & Butt2_bm) == 0){
		return BUTTON_2;
	}
	if((IO0PIN & Butt3_bm) == 0){
		return BUTTON_3;
	}
		return RELEASED_2;
}

unsigned int uiDiodeNumber=0;

void StepLeft(){
	LedOn(uiDiodeNumber++%4);
}

void StepRight(){
	LedOn(uiDiodeNumber--%4);
}

void LedStep(enum Direction eDir){
	static unsigned int uiDiodeNumber=0;
	if(eDir == LEFT){
		uiDiodeNumber++;
	}
	else {
		uiDiodeNumber--;
	}
	LedOn(uiDiodeNumber%4);
}
	
void LedStepLeft(){
	LedStep(LEFT);
}

void LedStepRight(){
	LedStep(RIGHT);
}

int main(){
	LedInit();
	LedOn(2);
	Delay(1000);
	LedStepRight();
	Delay(1000);
	LedStepLeft();
	Delay(1000);
}
