/*
 * Paulo Pedreiras, 2022/02
 * Simple Digital I/O, PWM and External Interrupt example
 * 
 * Button 1 generates an Int and cycles among 4 different Duty-Cycles
 * PWMis  applied to LED1 to allow visual feedback
 *
 *    ****** NOTE: must add "CONFIG_PWM=y" to prj.conf to enable the PWM module****
 *
 *
 *      HW info
 *          https://infocenter.nordicsemi.com/topic/struct_nrf52/struct/nrf52840.html
 *          Section: nRF52840 Product Specification -> Peripherals -> GPIO / GPIOTE and PWM
 * 
 *          Board specific HW info can be found in the nRF52840_DK_User_Guide_20201203. I/O pins available at pg 27
 *
 *
 *      Peripheral Libs: 
 *              https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/reference/peripherals/index.html
 *              GPIO and PWM
 * 
 * 
 */

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <drivers/pwm.h>
#include <sys/printk.h>
#include <sys/__assert.h>
#include <string.h>
#include <stdio.h>


/* Refer to dts file */
#define GPIO0_NID DT_NODELABEL(gpio0) 
#define PWM0_NID DT_NODELABEL(pwm0) 
#define BOARDLED1 0x0d
                /* Pin at which LED is connected. Addressing is direct (i.e., pin number)                  */
                /* Note 1: The PMW channel must be associted with the SAME pin in the DTS file             */
                /*         See the overlay file in this project to see how to change the assignment        */
                /*         *** Note: RUN CMAKE (Project -> Run Cmake) after editing the overlay file***    */
                /* Note 2: the pin can (and should) be obtained automatically from the DTS file.           */
                /*         I'm doing it manually to avoid entering in (cryptic) DT macros.                 */ 
                      

#define BOARDBUT1 0xb /* Pin at which BUT1 is connected. Addressing is direct (i.e., pin number) */

/* Int related declarations */
static struct gpio_callback but1_cb_data; /* Callback structure */

/* Callback function and variables*/
volatile int dcToggleFlag = 0; /* Flag to signal a BUT1 press */

void but1press_cbfunction(const struct device *dev, struct gpio_callback *cb, uint32_t pins){
    
    /* Inform that button was hit*/
    printk("But1 pressed at %d\n\r", k_cycle_get_32());
    
    /* Update Flag*/
    dcToggleFlag = 1;
}

/* Main function */
void main(void) {

    /* Local vars */
    const struct device *gpio0_dev;         /* Pointer to GPIO device structure */
    const struct device *pwm0_dev;          /* Pointer to PWM device structure */
    int ret=0;                              /* Generic return value variable */
    
    unsigned int pwmPeriod_us = 1000;       /* PWM priod in us */
    unsigned int dcValue[]={0,33,66,100};   /* Duty-cycle in % */
    unsigned int dcIndex=0;                 /* DC Index */
    
    /* Task init code */
    printk("pwmDemo\n\r"); 
    printk("Hit But1 to cycle among intensities ...\n\r ");

    /* Bind to GPIO 0 and PWM0 */
    gpio0_dev = device_get_binding(DT_LABEL(GPIO0_NID));
    if (gpio0_dev == NULL) {
        printk("Error: Failed to bind to GPIO0\n\r");        
	return;
    }
    else {
        printk("Bind to GPIO0 successfull \n\r");        
    }
    
    pwm0_dev = device_get_binding(DT_LABEL(PWM0_NID));
    if (pwm0_dev == NULL) {
	printk("Error: Failed to bind to PWM0\n r");
	return;
    }
    else  {
        printk("Bind to PWM0 successful\n\r");            
    }

    
    /* Configure PINS */    
    
    /* Note that PCB does not include pull-up resistors */
    /* See nRF52840v1.0.0 DK Users Guide V 1.0.0, pg 29 */
    ret = gpio_pin_configure(gpio0_dev, BOARDBUT1, GPIO_INPUT | GPIO_PULL_UP);
    if (ret < 0) {
        printk("Error %d: Failed to configure BUT 1 \n\r", ret);
	return;
    }

    /* Set interrupt HW - which pin and event generate interrupt */
    ret = gpio_pin_interrupt_configure(gpio0_dev, BOARDBUT1, GPIO_INT_EDGE_TO_ACTIVE);
    if (ret != 0) {
	printk("Error %d: failed to configure interrupt on BUT1 pin \n\r", ret);
	return;
    }
    
    /* Set callback */
    gpio_init_callback(&but1_cb_data, but1press_cbfunction, BIT(BOARDBUT1));
    gpio_add_callback(gpio0_dev, &but1_cb_data);
    
    
    /* main loop */
    while(1) {        
               
        if(dcToggleFlag) {
            dcIndex++;
            if(dcIndex == 4) 
                dcIndex = 0;
            dcToggleFlag = 0;
            printk("PWM DC value set to %u %%\n\r",dcValue[dcIndex]);

            ret = pwm_pin_set_usec(pwm0_dev, BOARDLED1,
		      pwmPeriod_us,(unsigned int)((pwmPeriod_us*dcValue[dcIndex])/100), PWM_POLARITY_NORMAL);
            if (ret) {
                printk("Error %d: failed to set pulse width\n", ret);
		return;
            }
        }            
           
    }

    return;
}

