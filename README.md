# PlatformIO Config

For Esp32-Vroom-32s use Denky32 board config:

```
[env:denky32]
platform = espressif32
board = denky32
framework = arduino
monitor_speed = 9600
```

# Serial Monitor

The serial monitor is intensely frustrating on this board.  

PlatformIO's serial monitor defaults to 9600, requiring a corresponding Serial.begin(9600) in code.
This works, but a random number of garbage characters are printed initially, then serial output starts as expected.
Attempting to increase the baud to 115200 (by adding `monitor_speed = 115200` to platformio.ini, and Serial.begin(115200) in code) results in PSRAM id read error warnings, but otherwise works.

# Dependencies

Adafruit SSD1306
    Required for display support.
    Install by adding `adafruit/Adafruit SSD1306@^2.5.7` to `lib_deps` property in platformio.ini, then `#include <Adafruit_SSD1306.h>`.
    NB: attempting to compile before including the header in code will result in compilation failures within Adafruit SSD1306/Adafruit_SSD1306.h.

# Display

The Adafruit_SSD1306 lib includes a splash screen logo, which consumes a significant amount of flash even if never displayed.
The lib offers SSD1306_NO_SPLASH to avoid this, but just #define'ing it prior to including the lib doesn't work. Instead define it as a build_flag in platformio.ini:

```
build_flags = -D SSD1306_NO_SPLASH
```

Font size 1 is 6px wide, giving 21 chars across + 2px.

# uC Pinout

```
                                                         +------------+
                       VCC <---------------- VIN 3.3V 19 |            | 38 GND -------------------------->
                     (xxx) <---------------- RESET EN 18 | +--------+ | 37 GPIO23 -----------------------> Button 3
      (in only, no pullup) <------------- ADC0 GPIO36 17 | |        | | 36 GPIO22 I2C SCL ---------------> Screen SCL
      (in only, no pullup) <------------- ADC3 GPIO39 16 | |        | | 35 GPIO1 TX0 --------------------> (xxx serial)
      (in only, no pullup) <------------- ADC6 GPIO34 15 | |        | | 34 GPIO3 RX0 --------------------> (xxx serial)
      (in only, no pullup) <------------- ADC7 GPIO35 14 | +--------+ | 33 GPIO21 I2C SDA ---------------> Screen SDA
                  Button 4 <------ TOUCH9 ADC4 GPIO32 13 |            | 32 GND --------------------------> 
                           <------ TOUCH8 ADC5 GPIO33 12 |            | 31 GPIO19 VSPI MISO -------------> Button 2
                (xxx wifi) <------------ ADC18 GPIO25 11 |            | 30 GPIO18 VSPI SCK --------------> Button 1
                (xxx wifi) <------------ ADC19 GPIO26 10 |            | 29 GPIO5  VSPI SS ---------------> (xxx strapping)
                (xxx wifi) <----- TOUCH7 ADC17 GPIO27  9 |    TOP     | 28 GPIO17 -----------------------> (xxx flash)
           (xxx jtag/wifi) <----- TOUCH6 ADC16 GPIO14  8 |            | 27 GPIO16 -----------------------> (xxx flash) 
 (xxx strapping/jtag/wifi) <----- TOUCH5 ADC15 GPIO12  7 |            | 26 GPIO4 ADC10 TOUCH0 -----------> (xxx wifi)
                       GND <--------------------- GND  6 |            | 25 GPIO0 ADC11 TOUCH1 -----------> (xxx strapping/wifi) 
           (xxx jtag/wifi) <----- TOUCH4 ADC14 GPIO13  5 |            | 24 GPIO2 ADC12 TOUCH2 -----------> (xxx strapping/wifi)
               (xxx flash) <---------- FLASH D2 GPIO9  4 |            | 23 GPIO15 ADC13 TOUCH3 ----------> (xxx strapping/jtag/wifi) 
               (xxx flash) <--------- FLASH D3 GPIO10  3 |            | 22 GPIO8 FLASH D1 ---------------> (xxx flash)
               (xxx flash) <-------- FLASH CMD GPIO11  2 |            | 21 GPIO7 FLASH D0 ---------------> (xxx flash)
                                               VIN 5V  1 | o +----+ o | 20 GPIO6 FLASH SCK --------------> (xxX flash)
                                                         +---|    |---+ 
                                                             +----+
```
