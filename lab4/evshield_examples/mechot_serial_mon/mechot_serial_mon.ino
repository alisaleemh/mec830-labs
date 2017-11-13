#include <mechbotShield.h>

#include <USART.h>






int main(void)  {

  uint8_t i;
  i=56;
  
  //set up serial prot
  initUSART();
  printString("Hello Vincent\r\n");
  printDecByte(i);
  printString("\r\n");
  printBinaryByte(i);
  




  
}

