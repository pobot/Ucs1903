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

#include "Arduino.h"

#include "avr/pgmspace.h"

class Ucs1903 { 
	public:
		// nPin : Pin de connection
		// nLeds : Nombre de led
		Ucs1903(int nPin, int nLeds);
		
		// Charger un nouveau tableau de valeur pour les leds.
		void setRGBData(unsigned char *rgbData);
		
		// Envoi d'une trame avec le nouveau code de couleur de chaque led.
		void show();
		
		// retourne un tableau avec toutes les valeurs des leds.
		unsigned char *getRGBData() { return m_pData; }
	
	private:
		int m_nLeds;
		unsigned char *m_pData;
		unsigned char pin;
		uint8_t **m_pPorts;
};

#endif
