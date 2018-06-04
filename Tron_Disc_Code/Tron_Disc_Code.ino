// This is a demonstration on how to use an input device to trigger changes on your neo pixels.
// You should wire a momentary push button to connect from ground to a digital IO pin.  When you
// press the button it will change to a new pixel animation.  Note that you need to press the
// button once to start the first animation!

#include <Adafruit_NeoPixel.h>

#define BUTTON_PIN   2    // Digital IO pin connected to the button.  This will be
                          // driven with a pull-up resistor so the switch should
                          // pull the pin to ground momentarily.  On a high -> low
                          // transition the button press logic will execute.

#define PIXEL_PIN    4    // Digital IO pin connected to the NeoPixels.

#define PIXEL_PIN2   6 

#define INPUT_PIN    5    //Pin to detect base connection

#define PIXEL_COUNT 11    //LED strip light count
#define PIXEL_COUNT2 11    //LED strip light count


const int tosecondarduino = 7;  // Sending signal to base from disc to change base led once connection is established between both 

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(PIXEL_COUNT2, PIXEL_PIN2, NEO_GRB + NEO_KHZ800);

bool oldState = HIGH;
int showType = 0;
int bridgeconnection=0;


void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(INPUT_PIN, INPUT_PULLUP);
  pinMode (tosecondarduino, OUTPUT);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {

  digitalWrite (tosecondarduino,LOW);

  // Enters as soon base loses its connection to tray
  if(bridgeconnection==1)
  {
    //Turn off disc lights and rest bridgeconnection variable
    startShow(0); 
    bridgeconnection--;
  }
  
  //Check if the Base is Connected to Tray
  while(digitalRead(INPUT_PIN) != HIGH) 
  { 
    //Flag to see if connection is broken
    if(bridgeconnection==0)
    {
      bridgeconnection++;
    }
    //Reset Tray and Show charging lights
    showType=0;
    startShow(4);
  }
//  test--;
  

 
  // Get current button state.
  bool newState = digitalRead(BUTTON_PIN);

  // Check if state changed from high to low (button press).
  if (newState == LOW && oldState == HIGH) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);
    if (newState == LOW) {
      showType++;
      if (showType > 3)
        showType=0;
      startShow(showType);
      
 
    }
  }

  // Set the last button state to the old state.
  oldState = newState;
  
}



void startShow(int i) {
  switch(i){
    case 0: colorWipe(strip.Color(0, 0, 0), 50);    // Black/off
            colorWipe(strip2.Color(0, 0, 0), 50);    // Black/off
            break;
    case 1: colorWipe(strip.Color(255, 0, 0), 50);  // Red
            colorWipe(strip2.Color(255, 0, 0), 50);  // Red
            break;
    case 2: colorWipe(strip.Color(0, 255, 0), 50);  // Green
            colorWipe(strip2.Color(0, 255, 0), 50);  // Green
            break;
    case 3: colorWipe(strip.Color(0, 0, 255), 50);  // Blue
            colorWipe(strip2.Color(0, 0, 255), 50);  // Blue
            break;
    case 4: colorWipe(strip.Color(100, 100, 100), 25);  // Blue
            colorWipe(strip2.Color(100, 100, 100), 25);  // Blue
            break;
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
   
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
 
}
