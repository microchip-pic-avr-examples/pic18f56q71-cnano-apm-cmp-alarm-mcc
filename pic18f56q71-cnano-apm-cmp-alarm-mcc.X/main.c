 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2023] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"

/*
    Main application
*/

void CMP1_InterruptHandler(void)
{
    if(CMP1_GetOutputStatus() == true)      /* make sure positive edge interrupt occurred */ 
    {
        PWM2_16BIT_Enable();
        LED_SetLow();                       /* turn LED on when speaker is driven*/
    }
}

void PWM2_InterruptHandler(void)
{
    if(CMP1_GetOutputStatus() == false)     /* check if Comparator outputs '0' */
    {    
        PWM2_16BIT_Disable();
        LED_SetHigh();                      /* turn LED off when speaker is not driven */
    }
}

int main(void)
{
    SYSTEM_Initialize();
    
    CMP1_InterruptCallbackRegister(CMP1_InterruptHandler);
    PWM2_16BIT_Period_SetInterruptHandler(PWM2_InterruptHandler);

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts 
    // Use the following macros to: 

    // Enable the Global High Interrupts 
    INTERRUPT_GlobalInterruptHighEnable(); 

    // Disable the Global High Interrupts 
    //INTERRUPT_GlobalInterruptHighDisable(); 

    // Enable the Global Low Interrupts 
    INTERRUPT_GlobalInterruptLowEnable(); 

    // Disable the Global Low Interrupts 
    //INTERRUPT_GlobalInterruptLowDisable();
    
    while(1)
    {
        if(APM_StatusGet() != 0)            /* check if any analog module is enabled by the APM */
        {
            APMStatus_SetHigh();            /* GPIO outputs logic high if any analog module is enabled */
        }
        else
        {
            APMStatus_SetLow();             /* GPIO outputs logic low if all analog modules are disabled */
        }
    }    
}