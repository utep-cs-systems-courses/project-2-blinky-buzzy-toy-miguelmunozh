#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

/*
char toggle_red()		// always toggle! 
{
  static char state = 0;

  switch (state) {
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;		        //always changes an led/
}


char toggle_green()	//only toggle green if red is on!  
{
  char changed = 0;
  if (red_on) {
    green_on ^= 1;
    changed = 1;
  }
  return changed;
}

//makes the light dim, (dim demo)
void state_advance()		/* alternate between toggling red & green 
{
  char changed = 0;  

  static enum {R=0, G=1} color = G;
  switch (color) {
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }

  led_changed = changed;
  led_update();
}
*/

/*state machine for button 2,*/
char toggle(){
  static char state =0;
  switch(state){
  case 0:
    red_on = 0;
    green_on = 0;
    state = 1;
    break;
  case 1:
    green_on = 1;
    state = 2;
    break;
  case 2:
    red_on = 1;
    green_on = 0;
    state = 3;
    break;
  case 3:
    red_on = 1;
    green_on = 1;
    state = 0;
    break;
  }
  return 1;
}


/*state machine that counts to 3,
 this state machine goes through 4 stages
 which are cases 0 - 3*/
char state_dim(){
  static char state =0;
  switch(state){
  case 0:
    //change leds
    red_on = 1;
    green_on =0;
    state =1;
    break;
  case 1:
    red_on = 0;
    green_on = 1;
    state = 0;
    break;
  }
  return 1;
}
void turn_leds_off(){
    red_on = 0;
    green_on =0;  
}

/*toggle_song turns off and on the leds at the rythim of the ''music''*/
char toggle_rithm(){
  static char state =0;
  switch(state){
  case 0:
    //change leds
    red_on = 1;
    green_on =0;
    //play a tone
    buzzer_set_period(100);
    state =1;
    break;
  case 1:
    red_on = 0;
    green_on = 1;
    buzzer_set_period(200);
    state = 2;
    break;
  case 2:
    red_on = 1;
    green_on=0;
    buzzer_set_period(300);
    state =3;
    break;
  case 3:
    red_on =0;
    green_on =1;
    buzzer_set_period(400);
    state = 4;
    break;
  case 4:
    red_on = 1;
    green_on = 0;
    buzzer_set_period(500);
    state = 5;
    break;
  case 5:
    red_on =0;
    green_on =1;
    buzzer_set_period(600);
    state = 6;
    break;
  case 6:
    red_on = 1;
    green_on = 0;
    buzzer_set_period(700);
    state = 7;
    break;
  case 7:
    red_on =0;
    green_on =1;
    buzzer_set_period(800);
    state = 8;
    break;
  case 8:
    red_on = 1;
    green_on = 0;
    buzzer_set_period(900);
    state = 9;
    break;
  case 9:
    red_on =0;
    green_on =1;
    buzzer_set_period(1000);
    state = 10;
    break;
  case 10:
    red_on = 1;
    green_on = 1;
    buzzer_set_period(900);
    state = 11;
    break;
  case 11:
    red_on =1;
    green_on =1;
    buzzer_set_period(800);
    state = 12;
    break;
  case 12:
    red_on = 1;
    green_on = 0;
    buzzer_set_period(700);
    state = 13;
    break;
  case 13:
    red_on =0;
    green_on =1;
    buzzer_set_period(700);
    state = 14;
    break;
  case 14:
    red_on = 0;
    green_on = 1;
    buzzer_set_period(600);
    state = 15;
    break;
  case 15:
    buzzer_set_period(500);
    state = 0;
    break;
  }
return 1;
  
}
/*this state machine plays a song*/
void state_advance_song(){
 static char stat =0;
  switch(stat){
  case 0:
    buzzer_set_period(2039);
    stat =1;
    break;
  case 1:
    buzzer_set_period(2039);
    stat = 2;
    break;
    case 2:
    buzzer_set_period(1396);
    stat = 3;
    break;
    case 3:
    buzzer_set_period(1396);
    stat =4;
    break;
  case 4:
    buzzer_set_period(1318);
    stat = 5;
    break;
    case 5:
    buzzer_set_period(1318);
    stat = 6;
    break;
  case 6:
    buzzer_set_period(1396);
   stat = 7;
    break;
    case 7:
    buzzer_set_period(1567);
    stat = 8;
    break;
     case 8:
    buzzer_set_period(1567);
    stat = 9;
    break;
    case 9:
    buzzer_set_period(1760);
    stat = 10;
    break;
    case 10:
    buzzer_set_period(1760);
    stat = 11;
    break;
    case 11:
    buzzer_set_period(1975);
    stat = 12;
    break;
    case 12:
    buzzer_set_period(1975);
    stat = 13;
    break;
  case 13:
    buzzer_set_period(2093);
    stat = 0;
    break;
  }
}

void state_advance_binary(){
  led_changed = toggle();
  led_update();
}
void state_advance_rithm(){
  led_changed = toggle_rithm();
  led_update();
}
void state_advance(){
  led_changed = state_dim();
  led_update();
}
