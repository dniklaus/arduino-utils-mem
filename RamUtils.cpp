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
#elif defined (__arm__) && defined (STM32F411xE) // STM32F4xx
#include <sys/types.h>
#include <errno.h>

// Deklaration des Heap-Endes aus dem Linker-Skript
extern uint8_t _end; 

caddr_t _sbrk(int incr) {
    static uint8_t *heap_end = NULL;
    uint8_t *prev_heap_end;

    // Beim ersten Aufruf den Heap-Start setzen
    if (heap_end == NULL) {
        heap_end = &_end;
    }

    prev_heap_end = heap_end;

    // optional: Hier könnte ein Check gegen das Stack-Ende stehen (Stack-Overflow-Schutz)

    heap_end += incr;
    return (caddr_t) prev_heap_end;
}
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
#elif defined (__arm__) && defined (STM32F411xE) // STM32F4xx
  char stack_dummy = 0;
  free_memory = &stack_dummy - _sbrk(0);
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
