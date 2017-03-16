/*
 * RamUtils.cpp
 *
 *  Created on: 28.01.2015
 *      Author: scan
 */

#include <Arduino.h>
#include <RamUtils.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

/*!
 * Returns the free ram memory space.
 * @return Free Memory space in Bytes
 */
int RamUtils::getFreeRam()
{
  int free_memory = 0;
#if defined (__arm__) && defined (__SAM3X8E__) // Arduino Due
  struct mallinfo mi=mallinfo();
  extern char* _sbrk(int i);
  char* heapend = _sbrk(0);
  register char * stack_ptr asm("sp");
  free_memory = stack_ptr - heapend + mi.fordblks;
  return free_memory;
#else // AVR
  extern int __bss_end;
  extern int *__brkval;
  if ((int) __brkval == 0)
  {
    free_memory = ((int) &free_memory) - ((int) &__bss_end);
  }
  else
  {
    free_memory = ((int) &free_memory) - ((int) __brkval);
  }
  return free_memory;
#endif
}
