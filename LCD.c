#include "LCD.h"



void delay_ms(unsigned int ms) {
	unsigned int i, j;
	for (i = 0; i < ms; i++)
	{
		for (j = 0; j < 800; j++)
		{
		}
	}
	
}



void LCD_WriteCom(unsigned char com) {
		
	
	 
	GPIOB->ODR &= 0xFFFFFFFD;									//set RS to 0
	
	unsigned char com1, com2;
	com1= (com&0xf0)>>1;
	com2= (com&0x0f)<<3;
	GPIOB->ODR &= 0xFFFFFFFB;									// set E = 0;
	
	// send upper command data (com1)
	GPIOB->ODR &= 0xFFFFFF87;
	GPIOB->ODR |= com1;
	
	GPIOB->ODR |= 0x00000004;									//set E=1;
	delay_ms(10);
	GPIOB->ODR &= 0xFFFFFFFB;									// set E = 0;
	
	// send lower command data (com2)
	GPIOB->ODR &= 0xFFFFFF87;
	GPIOB->ODR |= com2;
	
	GPIOB->ODR |= 0x00000004;									//set E=1
	delay_ms(10);
	GPIOB->ODR &= 0xFFFFFFFB;									// set E = 0
	
	
	
		GPIOB->ODR |= 0x00000002;								//Set RS back to 1
}
void LCD_WriteData(unsigned char dat) {
	unsigned char dat1, dat2;
	dat1= (dat&0xf0)>>1;
	dat2= (dat&0x0f)<<3;
	GPIOB->ODR &= 0xFFFFFFFB;									// set E = 0;
	
	
	// send upper info data (dat1)
	GPIOB->ODR &= 0xFFFFFF87;
	GPIOB->ODR |= dat1;
	
	
	GPIOB->ODR |= 0x00000004;									//set E=1;
	delay_ms(10);
	GPIOB->ODR &= 0xFFFFFFFB;									// set E = 0;
	
	
	// send lower info data (dat2)
	GPIOB->ODR &= 0xFFFFFF87;
	GPIOB->ODR |= dat2;
	
	
	GPIOB->ODR |= 0x00000004;									//set E=1;
	delay_ms(10);
	GPIOB->ODR &= 0xFFFFFFFB;									// set E = 0;
}
void LCD_Init(void){
	//set GPIOB clock on
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	
	// Enable the HSI clock
	
	// find out what CR is?
	//RCC->CR |= RCC_CR_CSSON_HSION;
	RCC ->CR  |=RCC_CR_HSION;
	
	//Set    PB1 to PB6 as outputs
	GPIOB->MODER &= 0xFFFFC553;
	GPIOB->MODER |= 0x00001554;	
	
	// Display initialization
	LCD_WriteCom(0x38); // features set up
	LCD_WriteCom(0x0c); //display switch
	LCD_WriteCom(0x06); // input mode Style setting
	LCD_WriteCom(0x01); //clear
	delay_ms(5);
	
	
	//Set RS to 1
	GPIOB->ODR |= 0x00000002;

}void LCD_Clear(void){
	LCD_WriteCom(0x01); //clear
}





void LCD_DisplayString(unsigned int line, unsigned char *ptr) {
	unsigned char i;
	LCD_WriteCom(0x40 + (0x40 * line));
	
	for (i=0; ptr[i]!= '\0'; i++)
	{
		LCD_WriteData(ptr[i]);
	}
}


	
	/*
uint32_t getPin(GPIO_TypeDef * port, uint32_t pin){
	uint32_t temp >> pin;					//Shift the value over by the value of that pin
	temp &= 0x00000001;						//mask to only read that pin
	return temp;									//return the value of that pin
	
}



void setPin(GPIO_TypeDef * port, uint32_t pin, uint32_t value){
	uint32_t temp = port->ODR;
	uint32_t mask = 1 << pin;
	if (value){										//if we're setting it too high
		temp 1 = mask;
	}
	else{													//if we're setting to to low
		temp &= ~mask;
	}
	port->ODR = temp;
}
*/
