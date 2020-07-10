#include <msp430.h>
#include "led.h"

unsigned char red_on = 0, green_on = 0;
unsigned char led_changed = 0;

static char redVal[] = {0, LED_RED}, greenVal[] = {0, LED_GREEN};


void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  led_changed = 1;
  //  led_update();         the call was here since leed init is called in main, when it starts but                            now it is changed to when i press a button
}

void led_update()
{
  if (led_changed) {
      
    char ledFlags = redVal[red_on] | greenVal[green_on];
    // switch_init();
    P1OUT &= (0xff^LEDS) | ledFlags; // clear bit for off leds
    P1OUT |= ledFlags;		     // set bit for on leds
    led_changed = 0;
  }
 }

