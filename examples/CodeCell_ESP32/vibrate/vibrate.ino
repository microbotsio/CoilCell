#include <CoilCell.h>

/*Learn more at microbots.io*/
/*In this example we intialize a CoilCell and make it vibrate at 5Hz*/

#define IN1_pin1 5
#define IN1_pin2 6

CoilCell myCoilCell(IN1_pin1, IN1_pin2);

void setup() {
  myCoilCell.Init();
  myCoilCell.Tone();
}

void loop() {
  myCoilCell.Vibrate(0,100,100);/*Vibrate the magnet at 5Hz - Set to to your desired frequency with this formula (time = 0.5/Frequency)*/
}
