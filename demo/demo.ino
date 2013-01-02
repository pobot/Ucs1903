#include <Ucs1903.h>

#define NUM_LEDS 6
#define PIN 13

Ucs1903 girlande(PIN, NUM_LEDS);

void setup()
{

}

void loop() { 
  for(int j = 0; j < 4; j++) { 
    for(int i = 0 ; i < NUM_LEDS; i++ ) {
      girlande.setOff();
      switch(j) { 
        case 0: girlande.setLed(i, 255, 0, 0); break;
        case 1: girlande.setLed(i, 0, 255, 0); break;
        case 2: girlande.setLed(i, 0, 0, 255); break;
        case 3: girlande.setLed(i, 255, 255, 255); break;
      }
      girlande.show();
      delay(100);
    }
  }

  // growing/receeding bars
  for(int j = 0; j < 3; j++) {
    girlande.setOff();
    for(int i = 0 ; i < NUM_LEDS; i++ ) {
      switch(j) { 
        case 0: girlande.setLed(i, 255, 0, 0); break;
        case 1: girlande.setLed(i, 0, 255, 0); break;
        case 2: girlande.setLed(i, 0, 0, 255); break;
      }
      girlande.show();
      delay(100);
    }
    for(int i = NUM_LEDS-1 ; i >= 0; i-- ) {
      switch(j) { 
        case 0: girlande.setLed(i, 0, 0, 0); break;
        case 1: girlande.setLed(i, 0, 0, 0); break;
        case 2: girlande.setLed(i, 0, 0, 0); break;
      }
      girlande.show();
      delay(100);
    }
  }
  
  // Fade in/fade out
  for(int j = 0; j < 4; j++ ) {
    girlande.setOff();
    for(int k = 0; k < 256; k++) { 
      for(int i = 0; i < NUM_LEDS; i++ ) {
        switch(j) { 
          case 0: girlande.setLed(i, k, 0, 0); break;
          case 1: girlande.setLed(i, 0, k, 0); break;
          case 2: girlande.setLed(i, 0, 0, k); break;
          case 3: girlande.setLed(i, k, k, k); break;
        }
      }
      girlande.show();
      delay(3);
    }
    for(int k = 255; k >= 0; k--) { 
      for(int i = 0; i < NUM_LEDS; i++ ) {
        switch(j) { 
          case 0: girlande.setLed(i, k, 0, 0); break;
          case 1: girlande.setLed(i, 0, k, 0); break;
          case 2: girlande.setLed(i, 0, 0, k); break;
          case 3: girlande.setLed(i, k, k, k); break;
        }
      }
      girlande.show();
      delay(3);
    }
  }
}

