/*
 * MemUtils.h
 *
 *  Created on: 28.01.2015
 *      Author: scan
 */

#ifndef PLAT_MEMUTILS_RAMUTILS_H_
#define PLAT_MEMUTILS_RAMUTILS_H_

class RamUtils
{
public:
  /**
   * Returns the free ram memory space.
   * @return Free Memory space in Bytes
   */
  static int getFreeRam();

private:
  RamUtils() {};
  virtual ~RamUtils() {};

private: // forbidden default functions
  RamUtils& operator = (const RamUtils& src); // assignment operator
  RamUtils(const RamUtils& src);              // copy constructor

};

#endif /* PLAT_MEMUTILS_RAMUTILS_H_ */
