/**
  Ucs1903.h - Librarie pour gestion de led HTD-12IC.

  @author :     Grégory Fromain, < gregoryfromain@gmail.com >
  @since : 	    21/12/2012
  @license :    http://creativecommons.org/licenses/by-nc/3.0/
  @link :       https://github.com/greg06/Ucs1903
*/

// Original source : https://github.com/PartYTech/fastspi

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include <pins_arduino.h>
  #include "wiring.h"
#endif
#include "avr/interrupt.h"
#include "avr/io.h"
#include "Ucs1903.h"


#define MASK_HI(R, P) (R) |= (P)
#define MASK_LO(R, P) (R) &= ~(P)

// Some ASM defines
#define NOP __asm__ __volatile__ ("cp r0,r0\n");
#define NOP2 NOP NOP
#define NOP1 NOP
#define NOP3 NOP NOP2
#define NOP4 NOP NOP3
#define NOP5 NOP NOP4
#define NOP6 NOP NOP5
#define NOP7 NOP NOP6
#define NOP8 NOP NOP7
#define NOP9 NOP NOP8
#define NOP10 NOP NOP9
#define NOP11 NOP NOP10
#define NOP12 NOP NOP11
#define NOP13 NOP NOP12
#define NOP14 NOP NOP13
#define NOP15 NOP10 NOP5
#define NOP16 NOP14 NOP2
#define NOP20 NOP10 NOP10
#define NOP22 NOP20 NOP2

#define NOP_SHORT NOP2
#define NOP_LONG NOP5

#define NOP_SHORT_1903 NOP2
#define NOP_LONG_1903 NOP15

#define UCS1903_BIT_SET(X,N,_PORT) if( X & (1<<N) ) { MASK_HI(_PORT,PIN); NOP_LONG_1903; MASK_LO(_PORT,PIN); NOP_SHORT_1903; } else { MASK_HI(_PORT,PIN); NOP_SHORT_1903; MASK_LO(_PORT,PIN); NOP_LONG_1903; }

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

CFastSPI_LED FastSPI_LED;


// local variables used for state tracking and pre-computed values
// TODO: move these into the class as necessary
static unsigned char *pData;

// nPin : Pin de connection
// nLeds : Nombre de led
void CFastSPI_LED::init(int nPin, int nLeds)
{ 
	//Configuration du nombre de led
	m_nLeds = nLeds * 3;
	m_pData = (unsigned char*)malloc(m_nLeds);
	memset(m_pData,0,m_nLeds);
	m_pDataEnd = m_pData + m_nLeds;
	
	//Selection de la pin de sortie
  m_pPorts = (uint8_t**)malloc(sizeof(uint8_t*));

  m_pPorts[0] = NULL;

  pinLed = nPin;
  m_pPorts[0] = (uint8_t*)portOutputRegister(digitalPinToPort(nPin));

  // store some static locals (makes lookup faster)
	pData = m_pDataEnd;
}

void CFastSPI_LED::setRGBData(unsigned char *rgbData)
{
	memcpy(m_pData,rgbData,m_nLeds);
}

void CFastSPI_LED::show() 
{ 
  cli();
  register byte *pData = m_pData;
  register byte *pEnd = pData + m_nLeds;
  register unsigned char PIN = digitalPinToBitMask(FastSPI_LED.pinLed); 
  register volatile uint8_t *pPort = m_pPorts[0];

	if(pPort != NOT_A_PIN)
		UCS1903_ALL(*pPort, pData, pEnd);

  sei();
}
