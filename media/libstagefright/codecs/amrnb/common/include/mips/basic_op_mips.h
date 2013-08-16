/* ------------------------------------------------------------------
 * Copyright (C) 1998-2009 PacketVideo
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 * -------------------------------------------------------------------
 */
/****************************************************************************************
Portions of this file are derived from the following 3GPP standard:

    3GPP TS 26.073
    ANSI-C code for the Adaptive Multi-Rate (AMR) speech codec
    Available from http://www.3gpp.org

(C) 2004, 3GPP Organizational Partners (ARIB, ATIS, CCSA, ETSI, TTA, TTC)
Permission to distribute, modify and use this file under the standard license
terms listed above has been obtained from the copyright holder.
****************************************************************************************/
/*

 Pathname: ./include/basic_op.h

------------------------------------------------------------------------------
 REVISION HISTORY

 Description: Revised basic_op.h since the basicop2.c functions were split
          up into separate source and header files. This function was
          retained because there are legacy GSM AMR C functions that still
          include this file. This file now includes the various basicop2
          functions' header files instead of defining the function
          prototypes.

 Description: Including header files with platform specific inline assembly
              instructions.

 Who:                       Date:
 Description:

------------------------------------------------------------------------------
 INCLUDE DESCRIPTION

 This file includes all the basicop2.c functions' header files.

------------------------------------------------------------------------------
*/

/*----------------------------------------------------------------------------
; CONTINUE ONLY IF NOT ALREADY DEFINED
----------------------------------------------------------------------------*/
#ifndef BASIC_OP_MIPS_H
#define BASIC_OP_MIPS_H


    /*----------------------------------------------------------------------------
    ; MACROS
    ; Define module specific macros here
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; DEFINES
    ; Include all pre-processor statements here.
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; EXTERNAL VARIABLES REFERENCES
    ; Declare variables used in this module but defined elsewhere
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; SIMPLE TYPEDEF'S
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; ENUMERATED TYPEDEF'S
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; STRUCTURES TYPEDEF'S
    ----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------
    ; GLOBAL FUNCTION DEFINITIONS
    ; Function Prototype declaration
    ----------------------------------------------------------------------------*/
    /*
    ------------------------------------------------------------------------------
     FUNCTION NAME: mac_32
    ------------------------------------------------------------------------------
     INPUT AND OUTPUT DEFINITIONS

     Inputs:
        L_var3 = 32 bit long signed integer (Word32) whose value falls
                 in the range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.
        L_var1_hi = 16 bit short signed integer (Word16) whose value falls in
               the range : 0xffff 8000 <= var1 <= 0x0000 7fff.
        L_var1_lo = 16 bit short signed integer (Word16) whose value falls in
               the range : 0xffff 8000 <= var2 <= 0x0000 7fff.
        L_var2_hi = 16 bit short signed integer (Word16) whose value falls in
               the range : 0xffff 8000 <= var1 <= 0x0000 7fff.
        L_var2_lo = 16 bit short signed integer (Word16) whose value falls in
               the range : 0xffff 8000 <= var2 <= 0x0000 7fff.

        pOverflow = pointer to overflow (Flag)

     Outputs:
        pOverflow -> 1 if the 32 bit mac operation resulted in overflow

     Returns:
        L_var3 = 32-bit result of L_var3 + (L_var1 * L_var2)(Word32)

    */
    static inline Word32 Mac_32(Word32 L_var3,
                                Word16 L_var1_hi,
                                Word16 L_var1_lo,
                                Word16 L_var2_hi,
                                Word16 L_var2_lo,
                                Flag *pOverflow)
    {
        Word16  product;
        Word32  result;

        OSCL_UNUSED_ARG(pOverflow);

        __asm__ volatile (
            "muleq_s.w.phr  %[result],  %[L_var1_hi],   %[L_var2_hi]     \n\t"
            "muleq_s.w.phr  %[product], %[L_var1_hi],   %[L_var2_lo]     \n\t"
            "addq_s.w       %[L_var3],  %[L_var3],      %[result]        \n\t"
            "sra            %[product], %[product],     16               \n\t"
            "sll            %[product], %[product],     1                \n\t"
            "addq_s.w       %[L_var3],  %[L_var3],      %[product]       \n\t"
            "muleq_s.w.phr  %[product], %[L_var1_lo],   %[L_var2_hi]     \n\t"
            "sra            %[product], %[product],     16               \n\t"
            "sll            %[product], %[product],     1                \n\t"
            "addq_s.w       %[L_var3],  %[L_var3],      %[product]       \n\t"

            : [product] "=&r" (product), [L_var3] "+r" (L_var3),
              [result] "=&r" (result)
            : [L_var1_hi] "r" (L_var1_hi), [L_var1_lo] "r" (L_var1_lo),
              [L_var2_hi] "r" (L_var2_hi), [L_var2_lo] "r" (L_var2_lo)
            : "hi", "lo"
        );

        return (L_var3);
    }

    /*
    ------------------------------------------------------------------------------
     FUNCTION NAME: mac_32_16
    ------------------------------------------------------------------------------
     INPUT AND OUTPUT DEFINITIONS

     Inputs:
        L_var3 = 32 bit long signed integer (Word32) whose value falls
                 in the range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.
        L_var1_hi = 16 bit short signed integer (Word16) whose value falls in
               the range : 0xffff 8000 <= var1 <= 0x0000 7fff.
        L_var1_lo = 16 bit short signed integer (Word16) whose value falls in
               the range : 0xffff 8000 <= var2 <= 0x0000 7fff.
        var2= 16 bit short signed integer (Word16) whose value falls in
               the range : 0xffff 8000 <= var1 <= 0x0000 7fff.
        pOverflow = pointer to overflow (Flag)

     Outputs:
        pOverflow -> 1 if the 32 bit mac operation resulted in overflow

     Returns:
        L_var3 = 32-bit result of L_var3 + (L_var1 * var2)(Word32)
    */

    static inline Word32 Mac_32_16(Word32 L_var3,
                                   Word16 L_var1_hi,
                                   Word16 L_var1_lo,
                                   Word16 var2,
                                   Flag  *pOverflow)
    {
        Word16  product;
        Word32  result;

        OSCL_UNUSED_ARG(pOverflow);

        __asm__ volatile (
            "muleq_s.w.phr  %[result],  %[L_var1_hi],   %[var2]     \n\t"
            "muleq_s.w.phr  %[product], %[L_var1_lo],   %[var2]     \n\t"
            "addq_s.w       %[result],  %[L_var3],      %[result]   \n\t"
            "sra            %[product], %[product],     16          \n\t"
            "sll            %[product], %[product],     1           \n\t"
            "addq_s.w       %[result],  %[result],      %[product]  \n\t"
            : [product] "=&r" (product),  [result] "=&r" (result)
            : [L_var1_hi] "r" (L_var1_hi), [L_var1_lo] "r" (L_var1_lo),
              [var2] "r" (var2), [L_var3] "r" (L_var3)
            : "hi", "lo"
        );

        return (result);
    }


    /*----------------------------------------------------------------------------
         Function Name : negate

         Negate var1 with saturation, saturate in the case where input is -32768:
                      negate(var1) = sub(0,var1).

         Inputs :
          var1
                   16 bit short signed integer (Word16) whose value falls in the
                   range : 0x8000 <= var1 <= 0x7fff.

         Outputs :
          none

         Return Value :
                   16 bit short signed integer (Word16) whose value falls in the
                   range : 0x8000 <= var_out <= 0x7fff.
     ----------------------------------------------------------------------------*/

    static inline Word16 negate(Word16 var1)
    {

        Word16 var_out;

        __asm__ volatile (
            "subq_s.ph %[var_out], $0, %[var1]  \n\t"
            : [var_out] "=r" (var_out)
            : [var1] "r" (var1)
        );

        return (var_out);
    }

    /*----------------------------------------------------------------------------

         Function Name : shl

         Arithmetically shift the 16 bit input var1 left var2 positions.Zero fill
         the var2 LSB of the result. If var2 is negative, arithmetically shift
         var1 right by -var2 with sign extension. Saturate the result in case of
         underflows or overflows.

         Inputs :
          var1
                   16 bit short signed integer (Word16) whose value falls in the
                   range : 0x8000 <= var1 <= 0x7fff.

          var2
                   16 bit short signed integer (Word16) whose value falls in the
                   range : 0x8000 <= var1 <= 0x7fff.

          pOverflow : pointer to overflow (Flag)

         Return Value :
          var_out
                   16 bit short signed integer (Word16) whose value falls in the
                   range : 0x8000 <= var_out <= 0x7fff.
     ----------------------------------------------------------------------------*/

    static inline Word16 shl(Word16 var1, Word16 var2, Flag *pOverflow)
    {
        Word16 var_out = 0;

        OSCL_UNUSED_ARG(pOverflow);

        if (var2 < 0)
        {
            var2 = -var2;
            if (var2 < 15)
            {
                var_out = var1 >> var2;
            }
        }
        else
        {
            __asm__ volatile (
                "shllv_s.ph %[var_out], %[var1], %[var2]    \n\t"
                : [var_out] "=r" (var_out)
                : [var1] "r" (var1), [var2] "r" (var2)
            );
        }
        return (var_out);
    }


    /*----------------------------------------------------------------------------

         Function Name : L_shl

         Arithmetically shift the 32 bit input L_var1 left var2 positions. Zero
         fill the var2 LSB of the result. If var2 is negative, arithmetically
         shift L_var1 right by -var2 with sign extension. Saturate the result in
         case of underflows or overflows.

         Inputs :
          L_var1   32 bit long signed integer (Word32) whose value falls in the
                   range : 0x8000 0000 <= L_var1 <= 0x7fff ffff.

          var2
                   16 bit short signed integer (Word16) whose value falls in the
                   range :  8000 <= var2 <= 7fff.

          pOverflow : pointer to overflow (Flag)

         Return Value :
                   32 bit long signed integer (Word32) whose value falls in the
                   range : 0x8000 0000 <= L_var_out <= 0x7fff ffff.

     ----------------------------------------------------------------------------*/

    static inline Word32 L_shl(Word32 L_var1, Word16 var2, Flag *pOverflow)
    {
        Word32 L_var_out = 0;

        OSCL_UNUSED_ARG(pOverflow);

        if (var2 > 0)
        {
            __asm__ volatile (
                "shllv_s.w %[L_var_out], %[L_var1], %[var2] \n\t"
                : [L_var_out] "=r" (L_var_out)
                : [L_var1] "r" (L_var1), [var2] "r" (var2)
            );
        }
        else
        {
            var2 = -var2;
            if (var2 < 31)
            {
                L_var_out = L_var1 >> var2;
            }
        }

        return (L_var_out);
    }


    /*----------------------------------------------------------------------------

         Function Name : L_shr

         Arithmetically shift the 32 bit input L_var1 right var2 positions with
         sign extension. If var2 is negative, arithmetically shift L_var1 left
         by -var2 and zero fill the -var2 LSB of the result. Saturate the result
         in case of underflows or overflows.

         Inputs :
          L_var1   32 bit long signed integer (Word32) whose value falls in the
                   range : 0x8000 0000 <= L_var1 <= 0x7fff ffff.

          var2
                   16 bit short signed integer (Word16) whose value falls in the
                   range :  8000 <= var2 <= 7fff.

          pOverflow : pointer to overflow (Flag)

         Return Value :
                   32 bit long signed integer (Word32) whose value falls in the
                   range : 0x8000 0000 <= L_var_out <= 0x7fff ffff.

     ----------------------------------------------------------------------------*/

    static inline Word32 L_shr(Word32 L_var1, Word16 var2, Flag *pOverflow)
    {
        Word32 L_var_out = 0;

        OSCL_UNUSED_ARG(pOverflow);

        if (var2 > 0)
        {
            if (var2 < 31)
            {
                L_var_out = L_var1 >> var2;
            }
        }
        else
        {
            var2 = -var2;

            L_var_out = L_var1 << (var2) ;
            if ((L_var_out >> (var2)) != L_var1)
            {
                L_var_out = (L_var1 >> 31) ^ MAX_32;
            }

        }

        return (L_var_out);
    }

    /*----------------------------------------------------------------------------

         Function Name : abs_s

          Absolute value of var1; abs_s(-32768) = 32767.

         Inputs :
          var1
                   16 bit short signed integer (Word16) whose value falls in the
                   range : 0x8000 <= var1 <= 0x7fff.

          pOverflow : pointer to overflow (Flag)

         Outputs :
          none

         Return Value :
                   16 bit short signed integer (Word16) whose value falls in the
                   range : 0x0000 <= var_out <= 0x7fff.

     ----------------------------------------------------------------------------*/

    static inline Word16 abs_s(Word16 var1)
    {

        Word16 y;

        __asm__ volatile (
            "absq_s.ph  %[y],    %[var1]  \n\t"
            "seh        %[y],    %[y]     \n\t"
            : [y] "=&r" (y)
            : [var1] "r" (var1)
        );

        return (y);
    }
    /*----------------------------------------------------------------------------
    ; END
    ----------------------------------------------------------------------------*/

#endif /* BASIC_OP_MIPS_H */


