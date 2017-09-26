//evshield_sumoeyes
#include <Wire.h>
#include <EVShield.h>
#include <EVs_SumoEyes.h>
#include <USART.h>


EVShield    evshield(0x34,0x36);
EVs_SumoEyes    seyes1;

void setup()    {
  
  initUSART();
  printString("starting program\r\n");
  evshield.init( SH_HardwareI2C );
  seyes1.init( &evshield, SH_BAS1 );
  
}

void  loop()   {
      uint16_t raw;
      
      seyes1.setLongRange();
      raw = seyes1.readRaw();
      printWord(raw);
      printString("\r\n");
      if ((raw > 450) && (raw < 500))  {
        Serial.println("object centre\r\n");
      }
      if ((raw > 800) && (raw < 850))  {
        Serial.println("object left\r\n");
      }
      if ((raw > 550) && (raw < 600))  {
        Serial.println("object right\r\n");
      }
      delay (1000);
}

