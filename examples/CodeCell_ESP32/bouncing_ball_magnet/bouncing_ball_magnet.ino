#include <CoilCell.h>

/*Learn more at microbots.io*/
/*In this example we intialize a CoilCell and make a 5mm diameter ball magnet bounce*/

#define IN1_pin1 5
#define IN1_pin2 6

CoilCell myCoilCell(IN1_pin1, IN1_pin2);

void setup() {
  myCoilCell.Init(); /*Initialize the CoilCell*/
}

void loop() {
  myCoilCell.Bounce(0, 20);/*Bounce the magnet up for 20ms*/
  delay(600);/*Attract the magnet back down for 600ms*/
}
