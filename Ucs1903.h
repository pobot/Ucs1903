/**
  Ucs1903.h - Librarie pour gestion de led HTD-12IC.

  @author :     Grégory Fromain, < gregoryfromain@gmail.com >
  @since : 	    21/12/2012
  @license :    http://creativecommons.org/licenses/by-nc/3.0/
  @link :       https://github.com/greg06/Ucs1903
*/

// Original source : https://github.com/PartYTech/fastspi

#ifndef __INC_SPIRGB_H
#define __INC_SPIRGB_H
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include <pins_arduino.h>
#endif

#include "avr/pgmspace.h"

class CFastSPI_LED { 
	public:  
		int m_nLeds;
		unsigned char *m_pData;
		unsigned char *m_pDataEnd;

		uint8_t **m_pPorts;
		unsigned int m_nDDR;
		unsigned pinLed;
	public:
		
		// initialize the engine - note this will also be re-called if one of the auto-calibration values
		// (e.g. percentage, refresh rate, brightness levels) is changed
		void init(int nPin, int nLeds);
		
		// call this method whenever you want to output a block of rgb data.  It is assumed that 
		// rgbData is nNumLeds * 3 bytes long.
		void setRGBData(unsigned char *rgbData);
		
		// call this method to get a pointer to the raw rgb data
		unsigned char *getRGBData() { return m_pData; }
		
		// 'show' or push the current led data (note, with some chipsets, data shows up in the
		// leds as soon as it is written to the array returned by getRGBData.
		void show();

};

extern CFastSPI_LED FastSPI_LED;
#endif
