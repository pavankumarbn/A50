/** @file DJI_Memory.cpp
 *  @version 3.1.7
 *  @date July 1st, 2016
 *
 *  @brief
 *  Implement memory management for Core API of DJI onboardSDK library
 *
 *  @copyright 2016 DJI. All right reserved.
 *
 *
 *  @attention
 *  It is not necessary to include DJI_Memory.h in any custom code file.
 *  The functions in this file are not API functions.
 *  Do not modify this file if you are unsure about it.
 *
 */

#include "DJI_Memory.h"
#include <stdio.h>
#include <string.h>
#include "DJI_API.h"

using namespace DJI::onboardSDK;

void CoreAPI::MMU::setupMMU() {
  unsigned int i;
  memoryTable[0].tabIndex = 0;
  memoryTable[0].usageFlag = 1;
  memoryTable[0].pmem = memory;
  memoryTable[0].memSize = 0;
  for (i = 1; i < (MMU_TABLE_NUM - 1); i++) {
    memoryTable[i].tabIndex = i;
    memoryTable[i].usageFlag = 0;
  }
  memoryTable[MMU_TABLE_NUM - 1].tabIndex = MMU_TABLE_NUM - 1;
  memoryTable[MMU_TABLE_NUM - 1].usageFlag = 1;
  memoryTable[MMU_TABLE_NUM - 1].pmem = memory + MEMORY_SIZE;
  memoryTable[MMU_TABLE_NUM - 1].memSize = 0;
}

void CoreAPI::MMU::freeMemory(MMU_Tab *mmu_tab) {
  if (mmu_tab == (MMU_Tab *)0) return;
  if (mmu_tab->tabIndex == 0 || mmu_tab->tabIndex == (MMU_TABLE_NUM - 1))
    return;
  mmu_tab->usageFlag = 0;
}

MMU_Tab *CoreAPI::MMU::allocMemory(unsigned short size) {
  unsigned int mem_used = 0;
  unsigned char i;
  unsigned char j = 0;
  unsigned char mmu_tab_used_num = 0;
  unsigned char mmu_tab_used_index[MMU_TABLE_NUM];

  unsigned int temp32;
  unsigned int temp_area[2] = {0xFFFFFFFF, 0xFFFFFFFF};

  unsigned int record_temp32 = 0;
  unsigned char magic_flag = 0;

  if (size > PRO_PURE_DATA_MAX_SIZE || size > MEMORY_SIZE) return (MMU_Tab *)0;

  for (i = 0; i < MMU_TABLE_NUM; i++)
    if (memoryTable[i].usageFlag == 1) {
      mem_used += memoryTable[i].memSize;
      mmu_tab_used_index[mmu_tab_used_num++] = memoryTable[i].tabIndex;
    }

  if (MEMORY_SIZE < (mem_used + size)) return (MMU_Tab *)0;

  if (mem_used == 0) {
    memoryTable[1].pmem = memoryTable[0].pmem;
    memoryTable[1].memSize = size;
    memoryTable[1].usageFlag = 1;
    return &memoryTable[1];
  }

  for (i = 0; i < (mmu_tab_used_num - 1); i++)
    for (j = 0; j < (mmu_tab_used_num - i - 1); j++)
      if (memoryTable[mmu_tab_used_index[j]].pmem >
          memoryTable[mmu_tab_used_index[j + 1]].pmem) {
        mmu_tab_used_index[j + 1] ^= mmu_tab_used_index[j];
        mmu_tab_used_index[j] ^= mmu_tab_used_index[j + 1];
        mmu_tab_used_index[j + 1] ^= mmu_tab_used_index[j];
      }

  for (i = 0; i < (mmu_tab_used_num - 1); i++) {
    temp32 = (unsigned int)(memoryTable[mmu_tab_used_index[i + 1]].pmem -
                            memoryTable[mmu_tab_used_index[i]].pmem);

    if ((temp32 - memoryTable[mmu_tab_used_index[i]].memSize) >= size) {
      if (temp_area[1] >
          (temp32 - memoryTable[mmu_tab_used_index[i]].memSize)) {
        temp_area[0] = memoryTable[mmu_tab_used_index[i]].tabIndex;
        temp_area[1] = temp32 - memoryTable[mmu_tab_used_index[i]].memSize;
      }
    }

    record_temp32 += temp32 - memoryTable[mmu_tab_used_index[i]].memSize;
    if (record_temp32 >= size && magic_flag == 0) {
      j = i;
      magic_flag = 1;
    }
  }

  if (temp_area[0] == 0xFFFFFFFF && temp_area[1] == 0xFFFFFFFF) {
    for (i = 0; i < j; i++) {
      if (memoryTable[mmu_tab_used_index[i + 1]].pmem >
          (memoryTable[mmu_tab_used_index[i]].pmem +
           memoryTable[mmu_tab_used_index[i]].memSize)) {
        memmove(memoryTable[mmu_tab_used_index[i]].pmem +
                    memoryTable[mmu_tab_used_index[i]].memSize,
                memoryTable[mmu_tab_used_index[i + 1]].pmem,
                memoryTable[mmu_tab_used_index[i + 1]].memSize);
        memoryTable[mmu_tab_used_index[i + 1]].pmem =
            memoryTable[mmu_tab_used_index[i]].pmem +
            memoryTable[mmu_tab_used_index[i]].memSize;
      }
    }

    for (i = 1; i < (MMU_TABLE_NUM - 1); i++) {
      if (memoryTable[i].usageFlag == 0) {
        memoryTable[i].pmem = memoryTable[mmu_tab_used_index[j]].pmem +
                              memoryTable[mmu_tab_used_index[j]].memSize;

        memoryTable[i].memSize = size;
        memoryTable[i].usageFlag = 1;
        return &memoryTable[i];
      }
    }
    return (MMU_Tab *)0;
  }

  for (i = 1; i < (MMU_TABLE_NUM - 1); i++) {
    if (memoryTable[i].usageFlag == 0) {
      memoryTable[i].pmem =
          memoryTable[temp_area[0]].pmem + memoryTable[temp_area[0]].memSize;

      memoryTable[i].memSize = size;
      memoryTable[i].usageFlag = 1;
      return &memoryTable[i];
    }
  }

  return (MMU_Tab *)0;
}

void DJI::onboardSDK::CoreAPI::setupSession() {
  unsigned int i;
  for (i = 0; i < SESSION_TABLE_NUM; i++) {
    CMDSessionTab[i].sessionID = i;
    CMDSessionTab[i].usageFlag = 0;
    CMDSessionTab[i].mmu = (MMU_Tab *)NULL;
  }

  for (i = 0; i < (SESSION_TABLE_NUM - 1); i++) {
    ACKSessionTab[i].sessionID = i + 1;
    ACKSessionTab[i].sessionStatus = ACK_SESSION_IDLE;
    ACKSessionTab[i].mmu = (MMU_Tab *)NULL;
  }
}

/*! @note Alloc a cmd session for sending cmd data
 *  when arg session_id = 0/1, it means select session 0/1 to send cmd
 *  otherwise set arg session_id = CMD_SESSION_AUTO (32), which means auto
 *  select a idle session id is between 2~31.
 */

CMDSession *DJI::onboardSDK::CoreAPI::allocSession(unsigned short session_id,
                                                   unsigned short size) {
  unsigned int i;
  API_LOG(serialDevice, DEBUG_LOG, "Allocation size %d", size);
  MMU_Tab *memoryTab = NULL;

  if (session_id == 0 || session_id == 1) {
    if (this->CMDSessionTab[session_id].usageFlag == 0)
      i = session_id;
    else {
      /* session is busy */
      API_LOG(serialDevice, ERROR_LOG, "session %d is busy\n", session_id);
      return NULL;
    }
  } else {
    for (i = 2; i < SESSION_TABLE_NUM; i++)
      if (CMDSessionTab[i].usageFlag == 0) break;
  }
  if (i < 32 && CMDSessionTab[i].usageFlag == 0) {
    CMDSessionTab[i].usageFlag = 1;
    memoryTab = mmu.allocMemory(size);
    if (memoryTab == NULL)
      CMDSessionTab[i].usageFlag = 0;
    else {
      CMDSessionTab[i].mmu = memoryTab;
      return &CMDSessionTab[i];
    }
  }
  return NULL;
}

void DJI::onboardSDK::CoreAPI::freeSession(CMDSession *session) {
  if (session->usageFlag == 1) {
    API_LOG(serialDevice, DEBUG_LOG, "session id %d\n", session->sessionID);
    mmu.freeMemory(session->mmu);
    session->usageFlag = 0;
  }
}

ACKSession *DJI::onboardSDK::CoreAPI::allocACK(unsigned short session_id,
                                               unsigned short size) {
  MMU_Tab *memoryTab = NULL;
  if (session_id > 0 && session_id < 32) {
    if (ACKSessionTab[session_id - 1].mmu)
      freeACK(&ACKSessionTab[session_id - 1]);
    memoryTab = mmu.allocMemory(size);
    if (memoryTab == NULL) {
      API_LOG(serialDevice, ERROR_LOG, "there is not enough memory\n");
      return NULL;
    } else {
      ACKSessionTab[session_id - 1].mmu = memoryTab;
      return &ACKSessionTab[session_id - 1];
    }
  }
  API_LOG(serialDevice, ERROR_LOG, "wrong Ack session ID: 0x%X\n", session_id);
  return NULL;
}

void DJI::onboardSDK::CoreAPI::freeACK(ACKSession *session) {
  mmu.freeMemory(session->mmu);
}
