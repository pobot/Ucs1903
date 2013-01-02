#include <Ucs1903.h>

#define NUM_LEDS 6
#define PIN 13

// Sometimes chipsets wire in a backwards sort of way
struct CRGB { unsigned char b; unsigned char r; unsigned char g; };
// struct CRGB { unsigned char r; unsigned char g; unsigned char b; };
struct CRGB *leds;

Ucs1903 girlande(PIN, NUM_LEDS);

void setup()
{
  leds = (struct CRGB*)girlande.getRGBData(); 
}

void loop() { 
  // one at a time
  for(int j = 0; j < 4; j++) { 
    for(int i = 0 ; i < NUM_LEDS; i++ ) {
      memset(leds, 0, NUM_LEDS * 3);
      switch(j) { 
        case 0: leds[i].r = 255; break;
        case 1: leds[i].g = 255; break;
        case 2: leds[i].b = 255; break;
        case 3: leds[i].r = leds[i].g = leds[i].b = 255; break;
      }
      girlande.show();
      delay(100);
    }
  }

  // growing/receeding bars
  for(int j = 0; j < 3; j++) { 
    memset(leds, 0, NUM_LEDS * 3);
    for(int i = 0 ; i < NUM_LEDS; i++ ) {
      switch(j) { 
        case 0: leds[i].r = 255; break;
        case 1: leds[i].g = 255; break;
        case 2: leds[i].b = 255; break;
      }
      girlande.show();
      delay(100);
    }
    for(int i = NUM_LEDS-1 ; i >= 0; i-- ) {
      switch(j) { 
        case 0: leds[i].r = 0; break;
        case 1: leds[i].g = 0; break;
        case 2: leds[i].b = 0; break;
      }
      girlande.show();
      delay(100);
    }
  }
  
  // Fade in/fade out
  for(int j = 0; j < 4; j++ ) { 
    memset(leds, 0, NUM_LEDS * 3);
    for(int k = 0; k < 256; k++) { 
      for(int i = 0; i < NUM_LEDS; i++ ) {
        switch(j) { 
          case 0: leds[i].r = k; break;
          case 1: leds[i].g = k; break;
          case 2: leds[i].b = k; break;
          case 3: leds[i].r = leds[i].g = leds[i].b = k; break;
        }
      }
      girlande.show();
      delay(3);
    }
    for(int k = 255; k >= 0; k--) { 
      for(int i = 0; i < NUM_LEDS; i++ ) {
        switch(j) { 
          case 0: leds[i].r = k; break;
          case 1: leds[i].g = k; break;
          case 2: leds[i].b = k; break;
          case 3: leds[i].r = leds[i].g = leds[i].b = k; break;
        }
      }
      girlande.show();
      delay(3);
    }
  }
}

