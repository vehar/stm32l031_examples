/* initialization for the STM32L011 */
int main();
void init(void);
void Default_Handler(void);
void Systick_Handler(void);
extern void isr_usart2(void);
// The following are 'declared' in the linker script
extern unsigned char  INIT_DATA_VALUES;
extern unsigned char  INIT_DATA_START;
extern unsigned char  INIT_DATA_END;
extern unsigned char  BSS_START;
extern unsigned char  BSS_END;
extern "C" { void STACK_TOP(void);} // This is defined in the linker script
typedef void (*fptr)(void);
// the section "vectors" is placed at the beginning of flash 
// by the linker script
#pragma GCC push_options
#pragma GCC optimize ("O0")
// the section "vectors" is placed at the beginning of flash 
// by the linker script
const fptr Vectors[] __attribute__((section(".vectors"))) ={
	(fptr)(STACK_TOP), 	/* Top of stack */ 
	init,   		     /* Reset Handler */
	Default_Handler,	/* NMI */
	Default_Handler,	/* Hard Fault */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Reserved  */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Reserved */ 
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* SVC Call */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* Reserved */
	Default_Handler,	/* PendSV */
	Systick_Handler,	/* SysTick */	
/* External interrupt handlers follow */
	Default_Handler, 	/* 0: WWDG */
	Default_Handler, 	/* 1: PVD */
	Default_Handler, 	/* 2: RTC */
	Default_Handler, 	/* 3: FLASH */
	Default_Handler, 	/* 4: RCC */
	Default_Handler, 	/* 5: EXTI0_1 */
	Default_Handler, 	/* 6: EXTI2_3 */
	Default_Handler, 	/* 7: EXTI4_15 */
	Default_Handler, 	/* 8: */
	Default_Handler, 	/* 9:  DMA_CH1 */
	Default_Handler, 	/* 10: DMA_CH_3, DMA_CH_2 */
	Default_Handler, 	/* 11: DMA_CH4_5_6_7 */
	Default_Handler, 	/* 12: ADC_COMP */
	Default_Handler, 	/* 13: LPTIM */
	Default_Handler, 	/* 14: USART4_5 */
	Default_Handler, 	/* 15: TIM2 */
	Default_Handler, 	/* 16: TIM3 */
	Default_Handler, 	/* 17: TIM6 */
	Default_Handler, 	/* 18: TIM7 */
	Default_Handler, 	/* 19: */
	Default_Handler, 	/* 20: TIM21 */
	Default_Handler, 	/* 21: I2C3 */
	Default_Handler, 	/* 22: TIM22 */
	Default_Handler, 	/* 23: I2C1 */
	Default_Handler, 	/* 24: I2C2 */
	Default_Handler, 	/* 25: SPI1 */
	Default_Handler, 	/* 26: SPI2 */
	Default_Handler, 	/* 27: USART1 */
	Default_Handler, 	/* 28: USART2 */
	Default_Handler 	/* 29: LPUART + AES */
	
};
void init()
{
// do global/static data initialization
	unsigned char *src;
	unsigned char *dest;
	unsigned len;
	src= &INIT_DATA_VALUES;
	dest= &INIT_DATA_START;
	len= &INIT_DATA_END-&INIT_DATA_START;
	while (len--)
		*dest++ = *src++;
// zero out the uninitialized global/static variables
	dest = &BSS_START;
	len = &BSS_END - &BSS_START;
	while (len--)
		*dest++=0;
	main();
}


void Default_Handler()
{	
	while(1);
}
#pragma GCC pop_options
