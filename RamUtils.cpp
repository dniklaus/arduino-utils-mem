/*
 * RamUtils.cpp
 *
 *  Created on: 28.01.2015
 *      Author: scan
 */

#include <Arduino.h>
#include <RamUtils.h>

/*!
 * Returns the free ram memory space.
 * @return Free Memory space in Bytes
 */
int RamUtils::getFreeRam()
{
#if defined (__arm__) && defined (__SAM3X8E__) // Arduino Due
// should use uinstd.h to define sbrk but on Arduino Due this causes a conflict
  extern "C" char* sbrk(int incr);
  int getFreeRam(void)
  {
    char top;
    return &top - reinterpret_cast<char*>(sbrk(0));
  }
#else // AVR
  extern int __bss_end;
  extern int *__brkval;
  int free_memory;
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
