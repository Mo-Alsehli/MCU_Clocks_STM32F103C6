# This project is based on STM32F103C6 MCU.
## The main objective of this project is to control the clock of the MCU.

### Tools
1. STM32 Cube IDE.
2. Keil Micro-vision Simulator.

## MCU Memory Architecture & Peripherals
![image](https://github.com/Mo-Alsehli/Master_Embedded_Systems/assets/98949843/94c693ec-9988-419c-b726-14250c397b72)

## MCU Clock Tree:
![image](https://github.com/Mo-Alsehli/Master_Embedded_Systems/assets/98949843/24335963-441b-48b2-b081-f11b2ec9c383)

### Toggle GPIOA bit 13 without opening its clock.
https://github.com/Mo-Alsehli/Master_Embedded_Systems/assets/98949843/22303d02-f2cc-4b49-a72b-3139207cff95

### Toggle GPIOA bit 13 and Enable its clock.
https://github.com/Mo-Alsehli/Master_Embedded_Systems/assets/98949843/e57de266-fcda-42d3-bfe9-6a06f5a3af7e

### Configure Board to run with the following rates:
```
1. APB1 Bus frequency 4MHZ
2. APB2 Bus frequency 2MHZ
3. AHB frequency 8 MHZ
4. SysClk 8 MHZ 
5. Use only internal HSI_RC
```
https://github.com/Mo-Alsehli/Master_Embedded_Systems/assets/98949843/a627ada8-2e2b-49ae-8f1d-8422a703a864

### Configure Board to run with the following rates:
```
1. APB1 Bus frequency 16MHZ
2. APB2 Bus frequency 8MHZ
3. AHB frequency 32MHZ
4. SysClk 32 MHZ 
5. Use only internal HSI_RC
```
#### Code 
https://github.com/Mo-Alsehli/Master_Embedded_Systems/assets/98949843/9305556c-7cf4-41d2-ba87-a856ae6b5ebb
#### Simulation
https://github.com/Mo-Alsehli/Master_Embedded_Systems/assets/98949843/43f3852c-dc74-42ee-91f0-f85b3945a2b3
