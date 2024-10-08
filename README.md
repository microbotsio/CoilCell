
# CoilCell

<img src="https://microbots.io/cdn/shop/files/Untitled-Copy_2048x.png?v=1720532841" alt="CoilCell" width="300" align="right" style="margin-left: 20px;">
CoilCell is a thin and compact PCB coil with an integrated driver, designed for easy integration with microcontrollers to control magnetic strength and polarity. Ideal for adding motion to magnets in your DIY projects. The CoilCell Library is available for download on both Github and the Arduino Library manager. Basic functions work on all Arduino boards + optimized PWM functions for CodeCell & other ESP32 devices.

## Getting Started with the CoilCell Library

### Setting Up Your CoilCell

To start using CoilCell, create an instance of the `CoilCell` class by specifying the input pins connected to your actuator, and then call the `Init()` function. Here’s a basic setup example:

```cpp
#include "CoilCell.h"

CoilCell myCoilCell(IN1, IN2);  // Replace IN1 and IN2 with your specific pins

void setup() {
    myCoilCell.Init();  // Initializes the CoilCell
}
```

### CoilCell Functions

The `CoilCell` library offers a range of functions to control the coil. Below are detailed descriptions of the available functions:

#### 1. **Init:** `Init()`
   - **Description:** Initializes the CoilCell by setting up the GPIO pins and, if using an ESP32, attaches hardware timers for precise control.
     ```cpp
     myCoilCell.Init();  // Initializes the CoilCell
     ```

#### 2. **Vibrate:** `Vibrate(bool smooth, uint8_t power_percent, uint16_t vib_speed_ms)`
   - **Description for ESP32:** Flips the polarity of the actuator at the specified speed and duty cycle. The `smooth` parameter creates smoother transitions ideal for slow motions.
   - **Examples:**
     ```cpp
     myCoilCell.Vibrate(true, 50, 500);  // Smooth operation at 50% power, flipping every 500 ms
     ```
   - **Description for Other Arduino Devices:** Uses simple GPIO toggling with delay to flip the actuator polarity at 100% duty cycle.
   - **Examples:**
     ```cpp
     myCoilCell.Vibrate(500);  // Flip every 500 milliseconds
     ```

#### 3. **Buzz:** `Buzz(uint16_t us_buzz)`
   - **Description:** Generates a buzzing effect by toggling the actuator state at the specified microsecond intervals, ideal for creating sound or rapid vibrations.
   - **Example:**
     ```cpp
     myCoilCell.Buzz(100);  // Buzz at 100 microseconds
     ```

#### 4. **Drive:** `Drive(bool direction, uint8_t power_percent)`
   - **Description for ESP32:** Controls the speed and polarity of a coil using PWM.
   - **Examples:**
     ```cpp
     myCoilCell.Drive(true, 75);  // Drive forward at 75% power
     ```

#### 5. **Bounce:** `Bounce(bool direction, uint8_t ms_duration)`
   - **Description:** Creates a short bounce motion by quickly reversing polarity for the specified duration.
   - **Example:**
     ```cpp
     myCoilCell.Bounce(true, 10);  // Bounce in one direction for 10 milliseconds
     ```

#### 6. **Tone:** `Tone()`
   - **Description:** Plays a tone by continuously toggling the coil state with varying frequencies, useful for generating audible feedback.
   - **Example:**
     ```cpp
     myCoilCell.Tone();  // Play a tone with varying frequencies
     ```

#### 7. **Toggle:** `Toggle(uint8_t power_percent)`
   - **Description for ESP32:** Toggles the polarity of the coil at the desired duty cycle using PWM.
   - **Examples:**
     ```cpp
     myCoilCell.Toggle(50);  // Toggle direction at 50% power
     ```
     
   - **Description for Other Arduino Devices:** Toggles polarity using simple GPIO toggling.
   - **Examples:**
     ```cpp
     myCoilCell.Toggle();    // Toggle direction or polarity
     ```

