/*
 * Paulo Pedreiras, 2022/02
 * 
 * Simple SW module example
 * 
 * Ilustrates how SW modules can be created in NCS
 *      Note that CMakesLists.txt must be updated as follows (lines with ->)    
 *           cmake_minimum_required(VERSION 3.20.0)
 *
 *           find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
 *           project(modularSWDemo)
 *
 *      ->   zephyr_include_directories(MyMath) #Add this line - SW module folder
 *
 *           target_sources(app PRIVATE src/main.c)
 *
 *      ->   target_sources(app PRIVATE src/MyMath/MyMath.c)  #Add this line - track MyMath.c
 *
 * 
 * 
 */

#include <zephyr.h>
#include <sys/printk.h>
#include "MyMath/MyMath.h"

#define STEPTIME_MS 500 /* Time between calls to MyAdd (in ms) */ 

/* Main function */
void main(void) {

    /* Variables */
    int x=0,y=10,res=0;

    /* Task init code */
    printk("Example if the use of SW modules  \n");
    printk("Call to MyAdd(x,y) in MyMath module\n\r"); 

    /* Blink loop */
    while(1) {  
        res=MyAdd(x++,y++);
        printk("MyAdd(%d,%d)=%d \n\r",x,y,res);

        /* Pause  */ 
        k_msleep(STEPTIME_MS);      
   }
    
    return;
} 