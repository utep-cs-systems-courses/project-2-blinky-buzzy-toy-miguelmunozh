#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"
#include "buzzer.h"
//#include "toggle.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  static char another_count =0;

  switch_interrupt_handler();          /*single handler for all the switches*/

  //handle what to do when a button is pressed  
  switch(state){
  case 1:
     if(++blink_count == 50){
        state_advance_song();
        blink_count = 0;
      }
     break; 
  case 2:
     if (++another_count ==250) {
	buzzer_set_period(0);
	state_advance_binary();
	  another_count = 0;
	}
     break; 
  case 3:
     if(++blink_count == 30){
        state_advance_rithm();
        blink_count = 0;
      }
     break;
  case 4:
      if(++blink_count == 40){
	buzzer_set_period(0); //stop the beep
        state_advance();
        blink_count = 0;
      }
  }
  }
