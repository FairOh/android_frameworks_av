/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*------------------------------------------------------------------------------

    Table of contents

    1. Include headers
    2. Module defines
    3. Data types
    4. Function prototypes

------------------------------------------------------------------------------*/

#ifndef H264SWDEC_CAVLC_H
#define H264SWDEC_CAVLC_H

/*------------------------------------------------------------------------------
    1. Include headers
------------------------------------------------------------------------------*/

#include "basetype.h"
#include "h264bsd_stream.h"

/*------------------------------------------------------------------------------
    2. Module defines
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
    3. Data types
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    4. Function prototypes
------------------------------------------------------------------------------*/

u32 h264bsdDecodeResidualBlockCavlc(
  strmData_t *pStrmData,
#if MIPS_DSP_R2_LE
/*-----------------------------------------------------------------------------
    coeffLevel type changed from i32 to i16 . This allows compiler to generate
    more efficient code for MIPS platform. All necessary changes are done in the
    h264bsd_macroblock_layer.c and h264bsd_transform.c files.
 -----------------------------------------------------------------------------*/

  i16 *coeffLevel,
#else /* #if MIPS_DSP_R2_LE */
  i32 *coeffLevel,
#endif /* #if MIPS_DSP_R2_LE */
  i32 nc,
  u32 maxNumCoeff);

#endif /* #ifdef H264SWDEC_CAVLC_H */

