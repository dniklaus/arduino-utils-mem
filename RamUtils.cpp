/*
 * RamUtils.cpp
 *
 *  Created on: 28.01.2015
 *      Author: scan
 */

#include <Arduino.h>
#include <RamUtils.h>

#if defined (__arm__) && defined (__SAM3X8E__) // Arduino Due
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
extern char* _sbrk(int i);
#endif

#if defined (ARDUINO_ARCH_SAMD) && defined (__SAMD21G18A__) // Adafruit Feather M0
extern "C" char *sbrk(int i);
#endif

#if defined (__AVR__) // AVR
extern "C" int __bss_end;
extern "C" int *__brkval;
#endif

/**
 * Returns the free ram memory space.
 * @return Free Memory space in Bytes
 */
int RamUtils::getFreeRam()
{
  int free_memory = 0;
#if defined (__arm__) && defined (__SAM3X8E__) // Arduino Due
  struct mallinfo mi=mallinfo();
  char* heapend = _sbrk(0);
  register char * stack_ptr asm("sp");
  free_memory = stack_ptr - heapend + mi.fordblks;
#elif defined (ARDUINO_ARCH_SAMD) && defined (__SAMD21G18A__) // Adafruit Feather M0
  char stack_dummy = 0;
  free_memory = &stack_dummy - sbrk(0);
#elif defined (__AVR__) // AVR
  if ((int) __brkval == 0)
  {
    free_memory = ((int) &free_memory) - ((int) &__bss_end);
  }
  else
  {
    free_memory = ((int) &free_memory) - ((int) __brkval);
  }
#endif
  return free_memory;
}
