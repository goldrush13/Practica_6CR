
#include "lib/include.h"

extern void Configura_Reg_PWM1(uint16_t freq)
{
    SYSCTL->RCGCPWM |= (1<<0); /*Enable reloj de modulo PWM1 pag 354*/
   
    SYSCTL->RCGCGPIO |= (1<<1)|(1<<4);; /*Enable reloj de GPIO Puerto F pag 340 pin 5*/
   // GPIOF->AFSEL |= (1<<3)|(1<<2)|(1<<1); /*Control de registros ya sea por GPIO o Otros Pag 672*/
    
    GPIOB_AHB->AFSEL |= (1<<4) | (1<<7);
    GPIOE_AHB->AFSEL |= (1<<4);
    
    GPIOB_AHB->PCTL |= (GPIOB_AHB->PCTL&0xFFF0FFFF) | 0x00040000; 
    GPIOB_AHB->PCTL |= (GPIOB_AHB->PCTL&0x0FFFFFFF) | 0x40000000; 
    GPIOE_AHB->PCTL |= (GPIOE_AHB->PCTL&0xFFF0FFFF) | 0x00040000;

    GPIOB->DEN |= (1<<4);
    GPIOB->DEN |= (1<<7);
    GPIOE->DEN |= (1<<4);

    PWM0->CC = (1<<8) | (0x2<<0);  /*Enable o Disable Divisor  Pag 1747*/
   
    PWM0->_0_CTL = (0<<0);
    PWM0->_1_CTL = (0<<0); /*Bloqueo y desbloqueo*/
   
    PWM0->_1_GENB = 0x0000080C; /*Registro de las acciones del pwm Pag 1285*/
    PWM0->_1_GENA = 0x0000008C; /*Registro de las acciones del pwm Pag 1282*/
    PWM0->_0_GENB = 0x0000008C;//PWM5
    
    PWM0->_1_LOAD = 50000; /*cuentas=fclk/fpwm  para 1khz cuentas = (20,000,000/1000)*/
    PWM0->_0_LOAD = 50000;
    PWM0->_2_LOAD = 50000;

    PWM0->_1_CMPB = 35000;
    PWM0->_1_CMPA = 35000;
    PWM0->_0_CMPA = 35000;

    PWM0->_1_CTL = (1<<0);// Se activa el generador 3
    PWM0->_0_CTL = (1<<0);// Se activa el generador 2
    
    PWM0->ENABLE = (1<<3) | (1<<2) | (1<<1); /*habilitar el bloque pa que pase Pag 1247*/
}
