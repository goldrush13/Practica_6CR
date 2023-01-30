#include "lib/include.h"
uint16_t Result[2];
uint16_t duty[2];

    //Configurar el timer 0 y timer 1 en modo de 32bits para hacer la siguiente rutina:
    // una función que active  el convertidor analógico digital y muestre dos señales de 
    //cierta frecuencia y amplitud definida.
    //y las guarde en dos arreglos  de tamaño 1024 y la envié por el protocolo de 
    //comunicación asíncrono para ser procesadas y regresadas al microcontrolador en 
    //valores binarios las cuales modificaran el ancho de pulso y reconstruirán la señal 
    //enviada a un transistor u opam
void Hilo_1(void)
{
    /*
 //llamada a la conversion por procesador
    PWM0->_1_CMPB = duty[0];
    PWM0->_1_CMPA = duty[1];
    PWM0->_0_CMPA = 1500;    
    */
    GPIOB_AHB->DATA = (1<<0);
    ADC0_InSeq2(Result,duty);
    GPIOB_AHB->DATA = (0<<0);
    

}



int main(void)
{

    Configurar_PLL();  //Confiuracion de velocidad de reloj 20MHZ
    Configurar_GPIO();
    Configura_Reg_ADC0();
    Configurar_UART0();
    Configura_Reg_PWM1(50);//Configuro a 1khz el pwm
    Configurar_Timer0A(&Hilo_1,10000);
    
    while(1)
    {
        ADC0_InSeq2(Result, duty);
    }

}
