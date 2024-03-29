/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mohamed Magdi
 * @brief          : Main program body
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include <stdint.h>

#define GPIOA_BASE 0x40010800
#define RCC_BASE 0x40021000

#define GPIOA_CRH *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR *(volatile uint32_t *)(GPIOA_BASE + 0x0C)

// RCC APB Enable Register
#define RCC_APB2ENR *(volatile uint32_t *)(RCC_BASE + 0x18)
// Clock Configuration Register
#define RCC_CFGR *(volatile uint32_t *)(RCC_BASE + 0x04)
// Clock Control Register
#define RCC_CR *(volatile uint32_t *)(RCC_BASE + 0x0)

void configureBoardWithFreqs1() {
	// Configure Board to run with the Following rates:
	// APB1 Bus frequency 4MHZ
	// APB2 Bus frequency 2MHZ
	// AHB frequency 8 MHZ
	// SysClk 8 MHZ
	// Use only internal HSI_RC

	// Input By Default Is HSI  = 8MHZ
	// In Clock Configuration Register:
	/* Bits 13:11  PPRE2[2:0]: APB high-speed prescaler (APB2)
	Set and cleared by software to control the division factor of the APB High speed clock (PCLK2).
	0xx: HCLK not divided
	100: HCLK divided by 2
	101: HCLK divided by 4
	110: HCLK divided by 8
	111: HCLK divided by 16 */

	RCC_CFGR |= (0b101 << 11);

	/* Bits 10:8  PPRE1[2:0]: APB Low-speed prescaler (APB1)
	Set and cleared by software to control the division factor of the APB Low speed clock (PCLK1).
	0xx: HCLK not divided
	100: HCLK divided by 2
	101: HCLK divided by 4
	110: HCLK divided by 8
	111: HCLK divided by 16 */

	RCC_CFGR |= (0b100 << 8);

	// BY DEFAULT From Clock Tree:
	// AHB frequency 8 MHZ
	// SysClk 8 MHZ
	// Uses only internal HSI_RC

}

void configureBoardWithFreqs2() {
	// Configure Board to run with the Following rates:
	// APB1 Bus frequency 16MHZ
	// APB2 Bus frequency 8MHZ
	// AHB frequency 32 MHZ
	// SysClk 32 MHZ
	// Use only internal HSI_RC

	// Choose The PLL As the System Clock.
	/* Bits 1:0  SW[1:0]: System clock Switch
	Set and cleared by software to select SYSCLK source.
	Set by hardware to force HSI selection when leaving Stop and Standby mode or in case of failure of
	the HSE oscillator used directly or indirectly as system clock (if the Clock Security System is
	enabled).
	00: HSI selected as system clock
	01: HSE selected as system clock
	10: PLL selected as system clock
	11: Not allowed */
	RCC_CFGR |= (0b10 << 0);

	// Set PLLMUL to *8 Prescaller to get 32MHZ as a system clock.
	// In Clock Configuration Register
	/* Bits 21:18  PLLMUL[3:0]: PLL multiplication factor
	These bits are written by software to define the PLL multiplication factor. They can be written only
	when PLL is disabled.
	000x: Reserved
	0010: PLL input clock x 4
	0011: PLL input clock x 5
	0100: PLL input clock x 6
	0101: PLL input clock x 7
	0110: PLL input clock x 8 */
	RCC_CFGR |= (0b0110 << 18);

	// From clock tree we have to enable pll and pllMull to prescale the input freq 8mhz to 32mhz
    // Enable PLL:
	// In clock control register bit 24
	/* Bit 24  PLLON: PLL enable
	Set and cleared by software to enable PLL.
	0: PLL OFF
	1: PLL ON */
	RCC_CR |= 1 << 24;

	// Input By Default Is HSI  = 32MHZ
	// In Clock Configuration Register:
	/* Bits 13:11  PPRE2[2:0]: APB high-speed prescaler (APB2)
	Set and cleared by software to control the division factor of the APB High speed clock (PCLK2).
	0xx: HCLK not divided
	100: HCLK divided by 2
	101: HCLK divided by 4
	110: HCLK divided by 8
	111: HCLK divided by 16 */
	RCC_CFGR |= (0b101 << 11);

	/* Bits 10:8  PPRE1[2:0]: APB Low-speed prescaler (APB1)
	Set and cleared by software to control the division factor of the APB Low speed clock (PCLK1).
	0xx: HCLK not divided
	100: HCLK divided by 2
	101: HCLK divided by 4
	110: HCLK divided by 8
	111: HCLK divided by 16 */
	RCC_CFGR |= (0b100 << 8);
}


int main(void)
{
	// Enabling Clock For GPOA.
	// GPOA Is connected to APB2 bus.
	// Bit 2  IOPAEN: I/O port A clock enable
	// Set and cleared by software.
	// 0: I/O port A clock disabled
	// 1:I/O port A clock enabled
	RCC_APB2ENR |= 1 << 2;

	configureBoardWithFreqs2();


	// INIT GPIOA
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;

	while(1){
		GPIOA_ODR |= 1<<13;
		for(int i = 0; i < 10000; i++); // Delay
		GPIOA_ODR &= ~(1<<13);
		for(int i = 0; i < 10000; i++); // Delay
	}
}
