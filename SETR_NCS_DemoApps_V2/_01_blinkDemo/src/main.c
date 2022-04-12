/*
 * Paulo Pedreiras, 2022/02
 * Simple Digital Output example
 * 
 * Toggles periodically LED1, which is internally connected to P0.13 
 *
 * Base documentation:
 *        
 *      HW info:
 *          https://infocenter.nordicsemi.com/topic/struct_nrf52/struct/nrf52840.html
 *          Section: nRF52840 Product Specification -> Peripherals -> GPIO / GPIOTE
 * 
 *          Board specific HW info can be found in the nRF52840_DK_User_Guide_20201203. I/O pins available at pg 27
 *
 *          Note that Leds are active-low. I.e., they turn on when a logic zero is output at the corresponding port, and vice-versa.
 *
 *      Peripherals:
 *          https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/reference/peripherals/gpio.html 
 * 
 * 
 */

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <sys/printk.h>
#include <sys/__assert.h>
#include <string.h>
#include <timing/timing.h>
#include <stdio.h>


/* Refer to dts file */
#define GPIO0_NID DT_NODELABEL(gpio0) 
#define BOARDLED1 0xd /* Pin at which LED is connected. Addressing is direct (i.e., pin number) */

#define BLINKPERIOD_MS 100 /* Blink period in ms*/ 

/* Main function */
void main(void) {

    /* Local vars */    
    const struct device *gpio0_dev;         /* Pointer to GPIO device structure */
    int ret=0;                              /* Generic return value variable */
    int ledstate=0;                         /* Led state var */

    /* Task init code */
    printk("LED1 blink demo \n");

    /* Bind to GPIO 0 */
    gpio0_dev = device_get_binding(DT_LABEL(GPIO0_NID));
    if (gpio0_dev == NULL) {
        printk("Failed to bind to GPIO0\n\r");        
	return;
    }
    else {
        printk("Bind to GPIO0 successfull \n\r");        
    }
    
    /* Configure PIN */
    ret = gpio_pin_configure(gpio0_dev, BOARDLED1, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("gpio_pin_configure() failed with error %d\n\r", ret);        
	return;
    }    

    /* Blink loop */
    while(1) {                
                
        /* Toggle led status */
        if(ledstate == 0)
            ledstate = 1;
        else
            ledstate = 0;
        gpio_pin_set(gpio0_dev, BOARDLED1, ledstate);
       
        /* Pause  */ 
        k_msleep(BLINKPERIOD_MS);        

    }
    
    return;
} 