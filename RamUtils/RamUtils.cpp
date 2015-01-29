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
  extern int  __bss_end;
  extern int  *__brkval;
  int free_memory;
  if((int)__brkval == 0) {
    free_memory = ((int)&free_memory) - ((int)&__bss_end);
  }
  else {
    free_memory = ((int)&free_memory) - ((int)__brkval);
  }

  return free_memory;
}
