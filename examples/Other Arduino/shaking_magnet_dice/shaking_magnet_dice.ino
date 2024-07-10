#include <CoilCell.h>

/*Learn more at microbots.io*/
/*In this example we intialize a CoilCell and make a 5mm square magnet act as a dice, shaking, set it to 1, shaking again and set it to 6*/

#define IN1_pin1 7
#define IN1_pin2 6

CoilCell myCoilCell(IN1_pin1, IN1_pin2);

bool polarity_flag = 0;
int16_t shake_counter = 0;

void setup() {
  myCoilCell.Init();
}

void loop() {
  myCoilCell.Vibrate(50); /*Shaking the magnet at 10Hz for a few seconds*/
  shake_counter++;
  if (shake_counter >= 50) {
    shake_counter = 0;
    polarity_flag = !polarity_flag;
    if (polarity_flag) {
      myCoilCell.Toggle(); /*Set the north facing number for 1sec*/
    } else {
      myCoilCell.Toggle(); /*Set the south facing number for 1sec*/
    }
    delay(1000);
  }
}
