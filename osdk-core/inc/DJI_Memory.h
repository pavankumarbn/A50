/** @file DJI_Memory.h
 *  @version 3.1.7
 *  @date July 1st, 2016
 *
 *  @brief
 *  Implement memory management for Core API of DJI onboardSDK library. See
 * DJI_Memory.cpp for more.
 *
 *  @copyright 2016 DJI. All right reserved.
 *
 */

#ifndef DJI_MEMORY_H
#define DJI_MEMORY_H

#include "DJI_Type.h"

namespace DJI {
namespace onboardSDK {

class MMU {
 public:
  MMU() {}
  void setupMMU(void);
  void freeMemory(MMU_Tab *mmu_tab);
  MMU_Tab *allocMemory(unsigned short size);

 private:
  MMU_Tab memoryTable[MMU_TABLE_NUM];
  unsigned char memory[MEMORY_SIZE];
};

}  // onboardSDK
}  // DJI
#endif  // DJI_MEMORY_H
