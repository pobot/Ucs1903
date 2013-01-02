/**
  Ucs1903.h - Librarie pour gestion de led HTD-12IC.

  @author :     Grégory Fromain, < gregoryfromain@gmail.com >
  @since : 	    21/12/2012
  @license :    http://creativecommons.org/licenses/by-nc/3.0/
  @link :       https://github.com/greg06/Ucs1903
*/

// Original source : https://github.com/PartYTech/fastspi

#include "Arduino.h"

#include "avr/interrupt.h"
#include "avr/io.h"
#include "Ucs1903.h"


#define MASK_HI(R, P) (R) |= (P)
#define MASK_LO(R, P) (R) &= ~(P)

// Some ASM defines
#define NOP __asm__ __volatile__ ("cp r0,r0\n");
#define NOP_SHORT_1903 NOP NOP
#define NOP_LONG_1903 NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP

#define UCS1903_BIT_SET(X,N,_PORT) if( X & (1<<N) ) { \
MASK_HI(_PORT,PIN); NOP_LONG_1903; MASK_LO(_PORT,PIN); NOP_SHORT_1903; } \
else { MASK_HI(_PORT,PIN); NOP_SHORT_1903; MASK_LO(_PORT,PIN); NOP_LONG_1903; }

#define UCS1903_BIT_ALL(_PORT)   \
 UCS1903_BIT_SET(x,7,_PORT); \
 UCS1903_BIT_SET(x,6,_PORT); \
 UCS1903_BIT_SET(x,5,_PORT); \
 UCS1903_BIT_SET(x,4,_PORT); \
 UCS1903_BIT_SET(x,3,_PORT); \
 UCS1903_BIT_SET(x,2,_PORT); \
 UCS1903_BIT_SET(x,1,_PORT); \
 UCS1903_BIT_SET(x,0,_PORT);

#define UCS1903_ALL(_PORT,PTR, END) \
 while(PTR != END) { register unsigned char x = *PTR++;  UCS1903_BIT_ALL(_PORT); \
   x = *PTR++; UCS1903_BIT_ALL(_PORT); \
   x = *PTR++; UCS1903_BIT_ALL(_PORT); }

// local variables used for state tracking and pre-computed values
// TODO: move these into the class as necessary
static unsigned char *pData;


Ucs1903::Ucs1903(int nPin, int nLeds)
{
	//Configuration du nombre de led
	m_nLeds = nLeds * 3;
	//Réservation d'espace mémoire
	m_pData = (unsigned char*)malloc(m_nLeds);
	//Reset des valeurs de toute les leds
	memset(m_pData,0,m_nLeds);
	
	//Selection de la pin de sortie
	m_pPorts = (uint8_t**)malloc(sizeof(uint8_t*));
	m_pPorts[0] = NULL;
	m_pPorts[0] = (uint8_t*)portOutputRegister(digitalPinToPort(nPin));
	pin = digitalPinToBitMask(nPin); 
}

void Ucs1903::show() 
{ 
  cli();
  register byte *pData = m_pData;
  register byte *pEnd = pData + m_nLeds;
  register unsigned char PIN = pin;
  register volatile uint8_t *pPort = m_pPorts[0];

  if(pPort != NOT_A_PIN)
	UCS1903_ALL(*pPort, pData, pEnd);

  sei();
}

void Ucs1903::setRGBData(unsigned char *rgbData)
{
	memcpy(m_pData,rgbData,m_nLeds);
}

void Ucs1903::setOff()
{
	memset(m_pData,0,m_nLeds);
}

void Ucs1903::setLed(int pos, unsigned char r, unsigned char g, unsigned char b)
{
	m_pData[(pos*3)+0] = r;
	m_pData[(pos*3)+1] = g;
	m_pData[(pos*3)+2] = b;
}


