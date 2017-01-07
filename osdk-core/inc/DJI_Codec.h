/** @file DJI_Codec.h
 *  @version 3.1.7
 *  @date July 1st, 2016
 *
 *  @brief
 *  Encoding/Message parsing features for DJI onboardSDK library
 *
 *  @copyright 2016 DJI. All rights reserved.
 *
 */

#ifndef DJI_CODEC_H
#define DJI_CODEC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory>
#include "DJI_Type.h"

#define _SDK_U32_SET(_addr, _val) (*((unsigned int *)(_addr)) = (_val))
#define _SDK_U16_SET(_addr, _val) (*((unsigned short *)(_addr)) = (_val))

#define _SDK_CALC_CRC_HEAD(_msg, _len) \
  sdk_stream_crc16_calc((const unsigned char *)(_msg), _len)
#define _SDK_CALC_CRC_TAIL(_msg, _len) \
  sdk_stream_crc32_calc((const unsigned char *)(_msg), _len)

void transformTwoByte(const char *pstr, unsigned char *pdata);

#endif  // DJI_CODEC_H
