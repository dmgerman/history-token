multiline_comment|/******************************************************************************&n; *&n; * Name: acmacros.h - C macros for the entire subsystem.&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#ifndef __ACMACROS_H__
DECL|macro|__ACMACROS_H__
mdefine_line|#define __ACMACROS_H__
multiline_comment|/*&n; * Data manipulation macros&n; */
DECL|macro|ACPI_LOWORD
mdefine_line|#define ACPI_LOWORD(l)                  ((u16)(u32)(l))
DECL|macro|ACPI_HIWORD
mdefine_line|#define ACPI_HIWORD(l)                  ((u16)((((u32)(l)) &gt;&gt; 16) &amp; 0xFFFF))
DECL|macro|ACPI_LOBYTE
mdefine_line|#define ACPI_LOBYTE(l)                  ((u8)(u16)(l))
DECL|macro|ACPI_HIBYTE
mdefine_line|#define ACPI_HIBYTE(l)                  ((u8)((((u16)(l)) &gt;&gt; 8) &amp; 0xFF))
macro_line|#if ACPI_MACHINE_WIDTH == 16
multiline_comment|/*&n; * For 16-bit addresses, we have to assume that the upper 32 bits&n; * are zero.&n; */
DECL|macro|ACPI_LODWORD
mdefine_line|#define ACPI_LODWORD(l)                 ((u32)(l))
DECL|macro|ACPI_HIDWORD
mdefine_line|#define ACPI_HIDWORD(l)                 ((u32)(0))
DECL|macro|ACPI_GET_ADDRESS
mdefine_line|#define ACPI_GET_ADDRESS(a)             ((a).lo)
DECL|macro|ACPI_STORE_ADDRESS
mdefine_line|#define ACPI_STORE_ADDRESS(a,b)         {(a).hi=0;(a).lo=(u32)(b);}
DECL|macro|ACPI_VALID_ADDRESS
mdefine_line|#define ACPI_VALID_ADDRESS(a)           ((a).hi | (a).lo)
macro_line|#else
macro_line|#ifdef ACPI_NO_INTEGER64_SUPPORT
multiline_comment|/*&n; * acpi_integer is 32-bits, no 64-bit support on this platform&n; */
DECL|macro|ACPI_LODWORD
mdefine_line|#define ACPI_LODWORD(l)                 ((u32)(l))
DECL|macro|ACPI_HIDWORD
mdefine_line|#define ACPI_HIDWORD(l)                 ((u32)(0))
DECL|macro|ACPI_GET_ADDRESS
mdefine_line|#define ACPI_GET_ADDRESS(a)             (a)
DECL|macro|ACPI_STORE_ADDRESS
mdefine_line|#define ACPI_STORE_ADDRESS(a,b)         ((a)=(b))
DECL|macro|ACPI_VALID_ADDRESS
mdefine_line|#define ACPI_VALID_ADDRESS(a)           (a)
macro_line|#else
multiline_comment|/*&n; * Full 64-bit address/integer on both 32-bit and 64-bit platforms&n; */
DECL|macro|ACPI_LODWORD
mdefine_line|#define ACPI_LODWORD(l)                 ((u32)(u64)(l))
DECL|macro|ACPI_HIDWORD
mdefine_line|#define ACPI_HIDWORD(l)                 ((u32)(((*(struct uint64_struct *)(void *)(&amp;l))).hi))
DECL|macro|ACPI_GET_ADDRESS
mdefine_line|#define ACPI_GET_ADDRESS(a)             (a)
DECL|macro|ACPI_STORE_ADDRESS
mdefine_line|#define ACPI_STORE_ADDRESS(a,b)         ((a)=(acpi_physical_address)(b))
DECL|macro|ACPI_VALID_ADDRESS
mdefine_line|#define ACPI_VALID_ADDRESS(a)           (a)
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * printf() format helpers&n; */
multiline_comment|/* Split 64-bit integer into two 32-bit values. use with %8,8_x%8.8X */
DECL|macro|ACPI_FORMAT_UINT64
mdefine_line|#define ACPI_FORMAT_UINT64(i)           ACPI_HIDWORD(i),ACPI_LODWORD(i)
multiline_comment|/*&n; * Extract a byte of data using a pointer.  Any more than a byte and we&n; * get into potential aligment issues -- see the STORE macros below&n; */
DECL|macro|ACPI_GET8
mdefine_line|#define ACPI_GET8(addr)                 (*(u8*)(addr))
multiline_comment|/* Pointer arithmetic */
DECL|macro|ACPI_PTR_ADD
mdefine_line|#define ACPI_PTR_ADD(t,a,b)             (t *) (void *)((char *)(a) + (acpi_native_uint)(b))
DECL|macro|ACPI_PTR_DIFF
mdefine_line|#define ACPI_PTR_DIFF(a,b)              (acpi_native_uint) ((char *)(a) - (char *)(b))
multiline_comment|/* Pointer/Integer type conversions */
DECL|macro|ACPI_TO_POINTER
mdefine_line|#define ACPI_TO_POINTER(i)              ACPI_PTR_ADD (void, (void *) NULL,(acpi_native_uint)i)
DECL|macro|ACPI_TO_INTEGER
mdefine_line|#define ACPI_TO_INTEGER(p)              ACPI_PTR_DIFF (p,(void *) NULL)
DECL|macro|ACPI_OFFSET
mdefine_line|#define ACPI_OFFSET(d,f)                (acpi_size) ACPI_PTR_DIFF (&amp;(((d *)0)-&gt;f),(void *) NULL)
DECL|macro|ACPI_FADT_OFFSET
mdefine_line|#define ACPI_FADT_OFFSET(f)             ACPI_OFFSET (FADT_DESCRIPTOR, f)
DECL|macro|ACPI_CAST_PTR
mdefine_line|#define ACPI_CAST_PTR(t, p)             ((t *)(void *)(p))
DECL|macro|ACPI_CAST_INDIRECT_PTR
mdefine_line|#define ACPI_CAST_INDIRECT_PTR(t, p)    ((t **)(void *)(p))
macro_line|#if ACPI_MACHINE_WIDTH == 16
DECL|macro|ACPI_STORE_POINTER
mdefine_line|#define ACPI_STORE_POINTER(d,s)         ACPI_MOVE_32_TO_32(d,s)
DECL|macro|ACPI_PHYSADDR_TO_PTR
mdefine_line|#define ACPI_PHYSADDR_TO_PTR(i)         (void *)(i)
DECL|macro|ACPI_PTR_TO_PHYSADDR
mdefine_line|#define ACPI_PTR_TO_PHYSADDR(i)         (u32) (char *)(i)
macro_line|#else
DECL|macro|ACPI_PHYSADDR_TO_PTR
mdefine_line|#define ACPI_PHYSADDR_TO_PTR(i)         ACPI_TO_POINTER(i)
DECL|macro|ACPI_PTR_TO_PHYSADDR
mdefine_line|#define ACPI_PTR_TO_PHYSADDR(i)         ACPI_TO_INTEGER(i)
macro_line|#endif
multiline_comment|/*&n; * Macros for moving data around to/from buffers that are possibly unaligned.&n; * If the hardware supports the transfer of unaligned data, just do the store.&n; * Otherwise, we have to move one byte at a time.&n; */
macro_line|#ifdef ACPI_BIG_ENDIAN
multiline_comment|/*&n; * Macros for big-endian machines&n; */
multiline_comment|/* This macro sets a buffer index, starting from the end of the buffer */
DECL|macro|ACPI_BUFFER_INDEX
mdefine_line|#define ACPI_BUFFER_INDEX(buf_len,buf_offset,byte_gran) ((buf_len) - (((buf_offset)+1) * (byte_gran)))
multiline_comment|/* These macros reverse the bytes during the move, converting little-endian to big endian */
multiline_comment|/* Big Endian      &lt;==        Little Endian */
multiline_comment|/*  Hi...Lo                     Lo...Hi     */
multiline_comment|/* 16-bit source, 16/32/64 destination */
DECL|macro|ACPI_MOVE_16_TO_16
mdefine_line|#define ACPI_MOVE_16_TO_16(d,s)         {((  u8 *)(void *)(d))[0] = ((u8 *)(void *)(s))[1];&bslash;&n;&t;&t;&t;  ((  u8 *)(void *)(d))[1] = ((u8 *)(void *)(s))[0];}
DECL|macro|ACPI_MOVE_16_TO_32
mdefine_line|#define ACPI_MOVE_16_TO_32(d,s)         {(*(u32 *)(void *)(d))=0;&bslash;&n;&t;&t;&t;&t;&t;  ((u8 *)(void *)(d))[2] = ((u8 *)(void *)(s))[1];&bslash;&n;&t;&t;&t;&t;&t;  ((u8 *)(void *)(d))[3] = ((u8 *)(void *)(s))[0];}
DECL|macro|ACPI_MOVE_16_TO_64
mdefine_line|#define ACPI_MOVE_16_TO_64(d,s)         {(*(u64 *)(void *)(d))=0;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;   ((u8 *)(void *)(d))[6] = ((u8 *)(void *)(s))[1];&bslash;&n;&t;&t;&t;&t;&t;&t;&t;   ((u8 *)(void *)(d))[7] = ((u8 *)(void *)(s))[0];}
multiline_comment|/* 32-bit source, 16/32/64 destination */
DECL|macro|ACPI_MOVE_32_TO_16
mdefine_line|#define ACPI_MOVE_32_TO_16(d,s)         ACPI_MOVE_16_TO_16(d,s)    /* Truncate to 16 */
DECL|macro|ACPI_MOVE_32_TO_32
mdefine_line|#define ACPI_MOVE_32_TO_32(d,s)         {((  u8 *)(void *)(d))[0] = ((u8 *)(void *)(s))[3];&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;  ((  u8 *)(void *)(d))[1] = ((u8 *)(void *)(s))[2];&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;  ((  u8 *)(void *)(d))[2] = ((u8 *)(void *)(s))[1];&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;  ((  u8 *)(void *)(d))[3] = ((u8 *)(void *)(s))[0];}
DECL|macro|ACPI_MOVE_32_TO_64
mdefine_line|#define ACPI_MOVE_32_TO_64(d,s)         {(*(u64 *)(void *)(d))=0;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;   ((u8 *)(void *)(d))[4] = ((u8 *)(void *)(s))[3];&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;   ((u8 *)(void *)(d))[5] = ((u8 *)(void *)(s))[2];&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;   ((u8 *)(void *)(d))[6] = ((u8 *)(void *)(s))[1];&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;   ((u8 *)(void *)(d))[7] = ((u8 *)(void *)(s))[0];}
multiline_comment|/* 64-bit source, 16/32/64 destination */
DECL|macro|ACPI_MOVE_64_TO_16
mdefine_line|#define ACPI_MOVE_64_TO_16(d,s)         ACPI_MOVE_16_TO_16(d,s)    /* Truncate to 16 */
DECL|macro|ACPI_MOVE_64_TO_32
mdefine_line|#define ACPI_MOVE_64_TO_32(d,s)         ACPI_MOVE_32_TO_32(d,s)    /* Truncate to 32 */
DECL|macro|ACPI_MOVE_64_TO_64
mdefine_line|#define ACPI_MOVE_64_TO_64(d,s)         {((  u8 *)(void *)(d))[0] = ((u8 *)(void *)(s))[7];&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; ((  u8 *)(void *)(d))[1] = ((u8 *)(void *)(s))[6];&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; ((  u8 *)(void *)(d))[2] = ((u8 *)(void *)(s))[5];&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; ((  u8 *)(void *)(d))[3] = ((u8 *)(void *)(s))[4];&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; ((  u8 *)(void *)(d))[4] = ((u8 *)(void *)(s))[3];&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; ((  u8 *)(void *)(d))[5] = ((u8 *)(void *)(s))[2];&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; ((  u8 *)(void *)(d))[6] = ((u8 *)(void *)(s))[1];&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; ((  u8 *)(void *)(d))[7] = ((u8 *)(void *)(s))[0];}
macro_line|#else
multiline_comment|/*&n; * Macros for little-endian machines&n; */
multiline_comment|/* This macro sets a buffer index, starting from the beginning of the buffer */
DECL|macro|ACPI_BUFFER_INDEX
mdefine_line|#define ACPI_BUFFER_INDEX(buf_len,buf_offset,byte_gran) (buf_offset)
macro_line|#ifdef ACPI_MISALIGNED_TRANSFERS
multiline_comment|/* The hardware supports unaligned transfers, just do the little-endian move */
macro_line|#if ACPI_MACHINE_WIDTH == 16
multiline_comment|/* No 64-bit integers */
multiline_comment|/* 16-bit source, 16/32/64 destination */
DECL|macro|ACPI_MOVE_16_TO_16
mdefine_line|#define ACPI_MOVE_16_TO_16(d,s)         *(u16 *)(void *)(d) = *(u16 *)(void *)(s)
DECL|macro|ACPI_MOVE_16_TO_32
mdefine_line|#define ACPI_MOVE_16_TO_32(d,s)         *(u32 *)(void *)(d) = *(u16 *)(void *)(s)
DECL|macro|ACPI_MOVE_16_TO_64
mdefine_line|#define ACPI_MOVE_16_TO_64(d,s)         ACPI_MOVE_16_TO_32(d,s)
multiline_comment|/* 32-bit source, 16/32/64 destination */
DECL|macro|ACPI_MOVE_32_TO_16
mdefine_line|#define ACPI_MOVE_32_TO_16(d,s)         ACPI_MOVE_16_TO_16(d,s)    /* Truncate to 16 */
DECL|macro|ACPI_MOVE_32_TO_32
mdefine_line|#define ACPI_MOVE_32_TO_32(d,s)         *(u32 *)(void *)(d) = *(u32 *)(void *)(s)
DECL|macro|ACPI_MOVE_32_TO_64
mdefine_line|#define ACPI_MOVE_32_TO_64(d,s)         ACPI_MOVE_32_TO_32(d,s)
multiline_comment|/* 64-bit source, 16/32/64 destination */
DECL|macro|ACPI_MOVE_64_TO_16
mdefine_line|#define ACPI_MOVE_64_TO_16(d,s)         ACPI_MOVE_16_TO_16(d,s)    /* Truncate to 16 */
DECL|macro|ACPI_MOVE_64_TO_32
mdefine_line|#define ACPI_MOVE_64_TO_32(d,s)         ACPI_MOVE_32_TO_32(d,s)    /* Truncate to 32 */
DECL|macro|ACPI_MOVE_64_TO_64
mdefine_line|#define ACPI_MOVE_64_TO_64(d,s)         ACPI_MOVE_32_TO_32(d,s)
macro_line|#else
multiline_comment|/* 16-bit source, 16/32/64 destination */
DECL|macro|ACPI_MOVE_16_TO_16
mdefine_line|#define ACPI_MOVE_16_TO_16(d,s)         *(u16 *)(void *)(d) = *(u16 *)(void *)(s)
DECL|macro|ACPI_MOVE_16_TO_32
mdefine_line|#define ACPI_MOVE_16_TO_32(d,s)         *(u32 *)(void *)(d) = *(u16 *)(void *)(s)
DECL|macro|ACPI_MOVE_16_TO_64
mdefine_line|#define ACPI_MOVE_16_TO_64(d,s)         *(u64 *)(void *)(d) = *(u16 *)(void *)(s)
multiline_comment|/* 32-bit source, 16/32/64 destination */
DECL|macro|ACPI_MOVE_32_TO_16
mdefine_line|#define ACPI_MOVE_32_TO_16(d,s)         ACPI_MOVE_16_TO_16(d,s)    /* Truncate to 16 */
DECL|macro|ACPI_MOVE_32_TO_32
mdefine_line|#define ACPI_MOVE_32_TO_32(d,s)         *(u32 *)(void *)(d) = *(u32 *)(void *)(s)
DECL|macro|ACPI_MOVE_32_TO_64
mdefine_line|#define ACPI_MOVE_32_TO_64(d,s)         *(u64 *)(void *)(d) = *(u32 *)(void *)(s)
multiline_comment|/* 64-bit source, 16/32/64 destination */
DECL|macro|ACPI_MOVE_64_TO_16
mdefine_line|#define ACPI_MOVE_64_TO_16(d,s)         ACPI_MOVE_16_TO_16(d,s)    /* Truncate to 16 */
DECL|macro|ACPI_MOVE_64_TO_32
mdefine_line|#define ACPI_MOVE_64_TO_32(d,s)         ACPI_MOVE_32_TO_32(d,s)    /* Truncate to 32 */
DECL|macro|ACPI_MOVE_64_TO_64
mdefine_line|#define ACPI_MOVE_64_TO_64(d,s)         *(u64 *)(void *)(d) = *(u64 *)(void *)(s)
macro_line|#endif
macro_line|#else
multiline_comment|/*&n; * The hardware does not support unaligned transfers.  We must move the&n; * data one byte at a time.  These macros work whether the source or&n; * the destination (or both) is/are unaligned.  (Little-endian move)&n; */
multiline_comment|/* 16-bit source, 16/32/64 destination */
DECL|macro|ACPI_MOVE_16_TO_16
mdefine_line|#define ACPI_MOVE_16_TO_16(d,s)         {((  u8 *)(void *)(d))[0] = ((u8 *)(void *)(s))[0];&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; ((  u8 *)(void *)(d))[1] = ((u8 *)(void *)(s))[1];}
DECL|macro|ACPI_MOVE_16_TO_32
mdefine_line|#define ACPI_MOVE_16_TO_32(d,s)         {(*(u32 *)(void *)(d)) = 0; ACPI_MOVE_16_TO_16(d,s);}
DECL|macro|ACPI_MOVE_16_TO_64
mdefine_line|#define ACPI_MOVE_16_TO_64(d,s)         {(*(u64 *)(void *)(d)) = 0; ACPI_MOVE_16_TO_16(d,s);}
multiline_comment|/* 32-bit source, 16/32/64 destination */
DECL|macro|ACPI_MOVE_32_TO_16
mdefine_line|#define ACPI_MOVE_32_TO_16(d,s)         ACPI_MOVE_16_TO_16(d,s)    /* Truncate to 16 */
DECL|macro|ACPI_MOVE_32_TO_32
mdefine_line|#define ACPI_MOVE_32_TO_32(d,s)         {((  u8 *)(void *)(d))[0] = ((u8 *)(void *)(s))[0];&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; ((  u8 *)(void *)(d))[1] = ((u8 *)(void *)(s))[1];&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; ((  u8 *)(void *)(d))[2] = ((u8 *)(void *)(s))[2];&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; ((  u8 *)(void *)(d))[3] = ((u8 *)(void *)(s))[3];}
DECL|macro|ACPI_MOVE_32_TO_64
mdefine_line|#define ACPI_MOVE_32_TO_64(d,s)         {(*(u64 *)(void *)(d)) = 0; ACPI_MOVE_32_TO_32(d,s);}
multiline_comment|/* 64-bit source, 16/32/64 destination */
DECL|macro|ACPI_MOVE_64_TO_16
mdefine_line|#define ACPI_MOVE_64_TO_16(d,s)         ACPI_MOVE_16_TO_16(d,s)    /* Truncate to 16 */
DECL|macro|ACPI_MOVE_64_TO_32
mdefine_line|#define ACPI_MOVE_64_TO_32(d,s)         ACPI_MOVE_32_TO_32(d,s)    /* Truncate to 32 */
DECL|macro|ACPI_MOVE_64_TO_64
mdefine_line|#define ACPI_MOVE_64_TO_64(d,s)         {((  u8 *)(void *)(d))[0] = ((u8 *)(void *)(s))[0];&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; ((  u8 *)(void *)(d))[1] = ((u8 *)(void *)(s))[1];&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; ((  u8 *)(void *)(d))[2] = ((u8 *)(void *)(s))[2];&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; ((  u8 *)(void *)(d))[3] = ((u8 *)(void *)(s))[3];&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; ((  u8 *)(void *)(d))[4] = ((u8 *)(void *)(s))[4];&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; ((  u8 *)(void *)(d))[5] = ((u8 *)(void *)(s))[5];&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; ((  u8 *)(void *)(d))[6] = ((u8 *)(void *)(s))[6];&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; ((  u8 *)(void *)(d))[7] = ((u8 *)(void *)(s))[7];}
macro_line|#endif
macro_line|#endif
multiline_comment|/* Macros based on machine integer width */
macro_line|#if ACPI_MACHINE_WIDTH == 16
DECL|macro|ACPI_MOVE_SIZE_TO_16
mdefine_line|#define ACPI_MOVE_SIZE_TO_16(d,s)       ACPI_MOVE_16_TO_16(d,s)
macro_line|#elif ACPI_MACHINE_WIDTH == 32
DECL|macro|ACPI_MOVE_SIZE_TO_16
mdefine_line|#define ACPI_MOVE_SIZE_TO_16(d,s)       ACPI_MOVE_32_TO_16(d,s)
macro_line|#elif ACPI_MACHINE_WIDTH == 64
DECL|macro|ACPI_MOVE_SIZE_TO_16
mdefine_line|#define ACPI_MOVE_SIZE_TO_16(d,s)       ACPI_MOVE_64_TO_16(d,s)
macro_line|#else
macro_line|#error unknown ACPI_MACHINE_WIDTH
macro_line|#endif
multiline_comment|/*&n; * Fast power-of-two math macros for non-optimized compilers&n; */
DECL|macro|_ACPI_DIV
mdefine_line|#define _ACPI_DIV(value,power_of2)      ((u32) ((value) &gt;&gt; (power_of2)))
DECL|macro|_ACPI_MUL
mdefine_line|#define _ACPI_MUL(value,power_of2)      ((u32) ((value) &lt;&lt; (power_of2)))
DECL|macro|_ACPI_MOD
mdefine_line|#define _ACPI_MOD(value,divisor)        ((u32) ((value) &amp; ((divisor) -1)))
DECL|macro|ACPI_DIV_2
mdefine_line|#define ACPI_DIV_2(a)                   _ACPI_DIV(a,1)
DECL|macro|ACPI_MUL_2
mdefine_line|#define ACPI_MUL_2(a)                   _ACPI_MUL(a,1)
DECL|macro|ACPI_MOD_2
mdefine_line|#define ACPI_MOD_2(a)                   _ACPI_MOD(a,2)
DECL|macro|ACPI_DIV_4
mdefine_line|#define ACPI_DIV_4(a)                   _ACPI_DIV(a,2)
DECL|macro|ACPI_MUL_4
mdefine_line|#define ACPI_MUL_4(a)                   _ACPI_MUL(a,2)
DECL|macro|ACPI_MOD_4
mdefine_line|#define ACPI_MOD_4(a)                   _ACPI_MOD(a,4)
DECL|macro|ACPI_DIV_8
mdefine_line|#define ACPI_DIV_8(a)                   _ACPI_DIV(a,3)
DECL|macro|ACPI_MUL_8
mdefine_line|#define ACPI_MUL_8(a)                   _ACPI_MUL(a,3)
DECL|macro|ACPI_MOD_8
mdefine_line|#define ACPI_MOD_8(a)                   _ACPI_MOD(a,8)
DECL|macro|ACPI_DIV_16
mdefine_line|#define ACPI_DIV_16(a)                  _ACPI_DIV(a,4)
DECL|macro|ACPI_MUL_16
mdefine_line|#define ACPI_MUL_16(a)                  _ACPI_MUL(a,4)
DECL|macro|ACPI_MOD_16
mdefine_line|#define ACPI_MOD_16(a)                  _ACPI_MOD(a,16)
multiline_comment|/*&n; * Rounding macros (Power of two boundaries only)&n; */
DECL|macro|ACPI_ROUND_DOWN
mdefine_line|#define ACPI_ROUND_DOWN(value,boundary)      (((acpi_native_uint)(value)) &amp; (~(((acpi_native_uint) boundary)-1)))
DECL|macro|ACPI_ROUND_UP
mdefine_line|#define ACPI_ROUND_UP(value,boundary)        ((((acpi_native_uint)(value)) + (((acpi_native_uint) boundary)-1)) &amp; (~(((acpi_native_uint) boundary)-1)))
DECL|macro|ACPI_ROUND_DOWN_TO_32_BITS
mdefine_line|#define ACPI_ROUND_DOWN_TO_32_BITS(a)        ACPI_ROUND_DOWN(a,4)
DECL|macro|ACPI_ROUND_DOWN_TO_64_BITS
mdefine_line|#define ACPI_ROUND_DOWN_TO_64_BITS(a)        ACPI_ROUND_DOWN(a,8)
DECL|macro|ACPI_ROUND_DOWN_TO_NATIVE_WORD
mdefine_line|#define ACPI_ROUND_DOWN_TO_NATIVE_WORD(a)    ACPI_ROUND_DOWN(a,ALIGNED_ADDRESS_BOUNDARY)
DECL|macro|ACPI_ROUND_UP_to_32_bITS
mdefine_line|#define ACPI_ROUND_UP_to_32_bITS(a)          ACPI_ROUND_UP(a,4)
DECL|macro|ACPI_ROUND_UP_to_64_bITS
mdefine_line|#define ACPI_ROUND_UP_to_64_bITS(a)          ACPI_ROUND_UP(a,8)
DECL|macro|ACPI_ROUND_UP_TO_NATIVE_WORD
mdefine_line|#define ACPI_ROUND_UP_TO_NATIVE_WORD(a)      ACPI_ROUND_UP(a,ALIGNED_ADDRESS_BOUNDARY)
DECL|macro|ACPI_ROUND_BITS_UP_TO_BYTES
mdefine_line|#define ACPI_ROUND_BITS_UP_TO_BYTES(a)       ACPI_DIV_8((a) + 7)
DECL|macro|ACPI_ROUND_BITS_DOWN_TO_BYTES
mdefine_line|#define ACPI_ROUND_BITS_DOWN_TO_BYTES(a)     ACPI_DIV_8((a))
DECL|macro|ACPI_ROUND_UP_TO_1K
mdefine_line|#define ACPI_ROUND_UP_TO_1K(a)               (((a) + 1023) &gt;&gt; 10)
multiline_comment|/* Generic (non-power-of-two) rounding */
DECL|macro|ACPI_ROUND_UP_TO
mdefine_line|#define ACPI_ROUND_UP_TO(value,boundary)     (((value) + ((boundary)-1)) / (boundary))
multiline_comment|/*&n; * Bitmask creation&n; * Bit positions start at zero.&n; * MASK_BITS_ABOVE creates a mask starting AT the position and above&n; * MASK_BITS_BELOW creates a mask starting one bit BELOW the position&n; */
DECL|macro|ACPI_MASK_BITS_ABOVE
mdefine_line|#define ACPI_MASK_BITS_ABOVE(position)       (~((ACPI_INTEGER_MAX) &lt;&lt; ((u32) (position))))
DECL|macro|ACPI_MASK_BITS_BELOW
mdefine_line|#define ACPI_MASK_BITS_BELOW(position)       ((ACPI_INTEGER_MAX) &lt;&lt; ((u32) (position)))
DECL|macro|ACPI_IS_OCTAL_DIGIT
mdefine_line|#define ACPI_IS_OCTAL_DIGIT(d)               (((char)(d) &gt;= &squot;0&squot;) &amp;&amp; ((char)(d) &lt;= &squot;7&squot;))
multiline_comment|/* Macros for GAS addressing */
macro_line|#if ACPI_MACHINE_WIDTH != 16
DECL|macro|ACPI_PCI_DEVICE
mdefine_line|#define ACPI_PCI_DEVICE(a)              (u16) ((ACPI_HIDWORD ((a))) &amp; 0x0000FFFF)
DECL|macro|ACPI_PCI_FUNCTION
mdefine_line|#define ACPI_PCI_FUNCTION(a)            (u16) ((ACPI_LODWORD ((a))) &gt;&gt; 16)
DECL|macro|ACPI_PCI_REGISTER
mdefine_line|#define ACPI_PCI_REGISTER(a)            (u16) ((ACPI_LODWORD ((a))) &amp; 0x0000FFFF)
macro_line|#else
multiline_comment|/* No support for GAS and PCI IDs in 16-bit mode  */
DECL|macro|ACPI_PCI_FUNCTION
mdefine_line|#define ACPI_PCI_FUNCTION(a)            (u16) ((a) &amp; 0xFFFF0000)
DECL|macro|ACPI_PCI_DEVICE
mdefine_line|#define ACPI_PCI_DEVICE(a)              (u16) ((a) &amp; 0x0000FFFF)
DECL|macro|ACPI_PCI_REGISTER
mdefine_line|#define ACPI_PCI_REGISTER(a)            (u16) ((a) &amp; 0x0000FFFF)
macro_line|#endif
multiline_comment|/* Bitfields within ACPI registers */
DECL|macro|ACPI_REGISTER_PREPARE_BITS
mdefine_line|#define ACPI_REGISTER_PREPARE_BITS(val, pos, mask)      ((val &lt;&lt; pos) &amp; mask)
DECL|macro|ACPI_REGISTER_INSERT_VALUE
mdefine_line|#define ACPI_REGISTER_INSERT_VALUE(reg, pos, mask, val)  reg = (reg &amp; (~(mask))) | ACPI_REGISTER_PREPARE_BITS(val, pos, mask)
multiline_comment|/*&n; * An struct acpi_namespace_node * can appear in some contexts,&n; * where a pointer to an union acpi_operand_object    can also&n; * appear.  This macro is used to distinguish them.&n; *&n; * The &quot;Descriptor&quot; field is the first field in both structures.&n; */
DECL|macro|ACPI_GET_DESCRIPTOR_TYPE
mdefine_line|#define ACPI_GET_DESCRIPTOR_TYPE(d)     (((union acpi_descriptor *)(void *)(d))-&gt;descriptor_id)
DECL|macro|ACPI_SET_DESCRIPTOR_TYPE
mdefine_line|#define ACPI_SET_DESCRIPTOR_TYPE(d,t)   (((union acpi_descriptor *)(void *)(d))-&gt;descriptor_id = t)
multiline_comment|/* Macro to test the object type */
DECL|macro|ACPI_GET_OBJECT_TYPE
mdefine_line|#define ACPI_GET_OBJECT_TYPE(d)         (((union acpi_operand_object *)(void *)(d))-&gt;common.type)
multiline_comment|/* Macro to check the table flags for SINGLE or MULTIPLE tables are allowed */
DECL|macro|ACPI_IS_SINGLE_TABLE
mdefine_line|#define ACPI_IS_SINGLE_TABLE(x)         (((x) &amp; 0x01) == ACPI_TABLE_SINGLE ? 1 : 0)
multiline_comment|/*&n; * Macros for the master AML opcode table&n; */
macro_line|#if defined(ACPI_DISASSEMBLER) || defined (ACPI_DEBUG_OUTPUT)
DECL|macro|ACPI_OP
mdefine_line|#define ACPI_OP(name,Pargs,Iargs,obj_type,class,type,flags)    {name,(u32)(Pargs),(u32)(Iargs),(u32)(flags),obj_type,class,type}
macro_line|#else
DECL|macro|ACPI_OP
mdefine_line|#define ACPI_OP(name,Pargs,Iargs,obj_type,class,type,flags)    {(u32)(Pargs),(u32)(Iargs),(u32)(flags),obj_type,class,type}
macro_line|#endif
macro_line|#ifdef ACPI_DISASSEMBLER
DECL|macro|ACPI_DISASM_ONLY_MEMBERS
mdefine_line|#define ACPI_DISASM_ONLY_MEMBERS(a)     a;
macro_line|#else
DECL|macro|ACPI_DISASM_ONLY_MEMBERS
mdefine_line|#define ACPI_DISASM_ONLY_MEMBERS(a)
macro_line|#endif
DECL|macro|ARG_TYPE_WIDTH
mdefine_line|#define ARG_TYPE_WIDTH                  5
DECL|macro|ARG_1
mdefine_line|#define ARG_1(x)                        ((u32)(x))
DECL|macro|ARG_2
mdefine_line|#define ARG_2(x)                        ((u32)(x) &lt;&lt; (1 * ARG_TYPE_WIDTH))
DECL|macro|ARG_3
mdefine_line|#define ARG_3(x)                        ((u32)(x) &lt;&lt; (2 * ARG_TYPE_WIDTH))
DECL|macro|ARG_4
mdefine_line|#define ARG_4(x)                        ((u32)(x) &lt;&lt; (3 * ARG_TYPE_WIDTH))
DECL|macro|ARG_5
mdefine_line|#define ARG_5(x)                        ((u32)(x) &lt;&lt; (4 * ARG_TYPE_WIDTH))
DECL|macro|ARG_6
mdefine_line|#define ARG_6(x)                        ((u32)(x) &lt;&lt; (5 * ARG_TYPE_WIDTH))
DECL|macro|ARGI_LIST1
mdefine_line|#define ARGI_LIST1(a)                   (ARG_1(a))
DECL|macro|ARGI_LIST2
mdefine_line|#define ARGI_LIST2(a,b)                 (ARG_1(b)|ARG_2(a))
DECL|macro|ARGI_LIST3
mdefine_line|#define ARGI_LIST3(a,b,c)               (ARG_1(c)|ARG_2(b)|ARG_3(a))
DECL|macro|ARGI_LIST4
mdefine_line|#define ARGI_LIST4(a,b,c,d)             (ARG_1(d)|ARG_2(c)|ARG_3(b)|ARG_4(a))
DECL|macro|ARGI_LIST5
mdefine_line|#define ARGI_LIST5(a,b,c,d,e)           (ARG_1(e)|ARG_2(d)|ARG_3(c)|ARG_4(b)|ARG_5(a))
DECL|macro|ARGI_LIST6
mdefine_line|#define ARGI_LIST6(a,b,c,d,e,f)         (ARG_1(f)|ARG_2(e)|ARG_3(d)|ARG_4(c)|ARG_5(b)|ARG_6(a))
DECL|macro|ARGP_LIST1
mdefine_line|#define ARGP_LIST1(a)                   (ARG_1(a))
DECL|macro|ARGP_LIST2
mdefine_line|#define ARGP_LIST2(a,b)                 (ARG_1(a)|ARG_2(b))
DECL|macro|ARGP_LIST3
mdefine_line|#define ARGP_LIST3(a,b,c)               (ARG_1(a)|ARG_2(b)|ARG_3(c))
DECL|macro|ARGP_LIST4
mdefine_line|#define ARGP_LIST4(a,b,c,d)             (ARG_1(a)|ARG_2(b)|ARG_3(c)|ARG_4(d))
DECL|macro|ARGP_LIST5
mdefine_line|#define ARGP_LIST5(a,b,c,d,e)           (ARG_1(a)|ARG_2(b)|ARG_3(c)|ARG_4(d)|ARG_5(e))
DECL|macro|ARGP_LIST6
mdefine_line|#define ARGP_LIST6(a,b,c,d,e,f)         (ARG_1(a)|ARG_2(b)|ARG_3(c)|ARG_4(d)|ARG_5(e)|ARG_6(f))
DECL|macro|GET_CURRENT_ARG_TYPE
mdefine_line|#define GET_CURRENT_ARG_TYPE(list)      (list &amp; ((u32) 0x1F))
DECL|macro|INCREMENT_ARG_LIST
mdefine_line|#define INCREMENT_ARG_LIST(list)        (list &gt;&gt;= ((u32) ARG_TYPE_WIDTH))
multiline_comment|/*&n; * Reporting macros that are never compiled out&n; */
DECL|macro|ACPI_PARAM_LIST
mdefine_line|#define ACPI_PARAM_LIST(pl)                 pl
multiline_comment|/*&n; * Error reporting.  These versions add callers module and line#.  Since&n; * _THIS_MODULE gets compiled out when ACPI_DEBUG_OUTPUT isn&squot;t defined, only&n; * use it in debug mode.&n; */
macro_line|#ifdef ACPI_DEBUG_OUTPUT
DECL|macro|ACPI_REPORT_INFO
mdefine_line|#define ACPI_REPORT_INFO(fp)                {acpi_ut_report_info(_THIS_MODULE,__LINE__,_COMPONENT); &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;acpi_os_printf ACPI_PARAM_LIST(fp);}
DECL|macro|ACPI_REPORT_ERROR
mdefine_line|#define ACPI_REPORT_ERROR(fp)               {acpi_ut_report_error(_THIS_MODULE,__LINE__,_COMPONENT); &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;acpi_os_printf ACPI_PARAM_LIST(fp);}
DECL|macro|ACPI_REPORT_WARNING
mdefine_line|#define ACPI_REPORT_WARNING(fp)             {acpi_ut_report_warning(_THIS_MODULE,__LINE__,_COMPONENT); &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;acpi_os_printf ACPI_PARAM_LIST(fp);}
DECL|macro|ACPI_REPORT_NSERROR
mdefine_line|#define ACPI_REPORT_NSERROR(s,e)            acpi_ns_report_error(_THIS_MODULE,__LINE__,_COMPONENT, s, e);
DECL|macro|ACPI_REPORT_METHOD_ERROR
mdefine_line|#define ACPI_REPORT_METHOD_ERROR(s,n,p,e)   acpi_ns_report_method_error(_THIS_MODULE,__LINE__,_COMPONENT, s, n, p, e);
macro_line|#else
DECL|macro|ACPI_REPORT_INFO
mdefine_line|#define ACPI_REPORT_INFO(fp)                {acpi_ut_report_info(&quot;ACPI&quot;,__LINE__,_COMPONENT); &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;acpi_os_printf ACPI_PARAM_LIST(fp);}
DECL|macro|ACPI_REPORT_ERROR
mdefine_line|#define ACPI_REPORT_ERROR(fp)               {acpi_ut_report_error(&quot;ACPI&quot;,__LINE__,_COMPONENT); &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;acpi_os_printf ACPI_PARAM_LIST(fp);}
DECL|macro|ACPI_REPORT_WARNING
mdefine_line|#define ACPI_REPORT_WARNING(fp)             {acpi_ut_report_warning(&quot;ACPI&quot;,__LINE__,_COMPONENT); &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;acpi_os_printf ACPI_PARAM_LIST(fp);}
DECL|macro|ACPI_REPORT_NSERROR
mdefine_line|#define ACPI_REPORT_NSERROR(s,e)            acpi_ns_report_error(&quot;ACPI&quot;,__LINE__,_COMPONENT, s, e);
DECL|macro|ACPI_REPORT_METHOD_ERROR
mdefine_line|#define ACPI_REPORT_METHOD_ERROR(s,n,p,e)   acpi_ns_report_method_error(&quot;ACPI&quot;,__LINE__,_COMPONENT, s, n, p, e);
macro_line|#endif
multiline_comment|/* Error reporting.  These versions pass thru the module and line# */
DECL|macro|_ACPI_REPORT_INFO
mdefine_line|#define _ACPI_REPORT_INFO(a,b,c,fp)         {acpi_ut_report_info(a,b,c); &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;acpi_os_printf ACPI_PARAM_LIST(fp);}
DECL|macro|_ACPI_REPORT_ERROR
mdefine_line|#define _ACPI_REPORT_ERROR(a,b,c,fp)        {acpi_ut_report_error(a,b,c); &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;acpi_os_printf ACPI_PARAM_LIST(fp);}
DECL|macro|_ACPI_REPORT_WARNING
mdefine_line|#define _ACPI_REPORT_WARNING(a,b,c,fp)      {acpi_ut_report_warning(a,b,c); &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;acpi_os_printf ACPI_PARAM_LIST(fp);}
multiline_comment|/*&n; * Debug macros that are conditionally compiled&n; */
macro_line|#ifdef ACPI_DEBUG_OUTPUT
DECL|macro|ACPI_MODULE_NAME
mdefine_line|#define ACPI_MODULE_NAME(name)               static char ACPI_UNUSED_VAR *_THIS_MODULE = name;
multiline_comment|/*&n; * Function entry tracing.&n; * The first parameter should be the procedure name as a quoted string.  This is declared&n; * as a local string (&quot;_proc_name) so that it can be also used by the function exit macros below.&n; */
DECL|macro|ACPI_FUNCTION_NAME
mdefine_line|#define ACPI_FUNCTION_NAME(a)               struct acpi_debug_print_info _dbg; &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;_dbg.component_id = _COMPONENT; &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;_dbg.proc_name   = a; &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;_dbg.module_name = _THIS_MODULE;
DECL|macro|ACPI_FUNCTION_TRACE
mdefine_line|#define ACPI_FUNCTION_TRACE(a)              ACPI_FUNCTION_NAME(a) &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;acpi_ut_trace(__LINE__,&amp;_dbg)
DECL|macro|ACPI_FUNCTION_TRACE_PTR
mdefine_line|#define ACPI_FUNCTION_TRACE_PTR(a,b)        ACPI_FUNCTION_NAME(a) &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;acpi_ut_trace_ptr(__LINE__,&amp;_dbg,(void *)b)
DECL|macro|ACPI_FUNCTION_TRACE_U32
mdefine_line|#define ACPI_FUNCTION_TRACE_U32(a,b)        ACPI_FUNCTION_NAME(a) &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;acpi_ut_trace_u32(__LINE__,&amp;_dbg,(u32)b)
DECL|macro|ACPI_FUNCTION_TRACE_STR
mdefine_line|#define ACPI_FUNCTION_TRACE_STR(a,b)        ACPI_FUNCTION_NAME(a) &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;acpi_ut_trace_str(__LINE__,&amp;_dbg,(char *)b)
DECL|macro|ACPI_FUNCTION_ENTRY
mdefine_line|#define ACPI_FUNCTION_ENTRY()               acpi_ut_track_stack_ptr()
multiline_comment|/*&n; * Function exit tracing.&n; * WARNING: These macros include a return statement.  This is usually considered&n; * bad form, but having a separate exit macro is very ugly and difficult to maintain.&n; * One of the FUNCTION_TRACE macros above must be used in conjunction with these macros&n; * so that &quot;_proc_name&quot; is defined.&n; */
macro_line|#ifdef ACPI_USE_DO_WHILE_0
DECL|macro|ACPI_DO_WHILE0
mdefine_line|#define ACPI_DO_WHILE0(a)               do a while(0)
macro_line|#else
DECL|macro|ACPI_DO_WHILE0
mdefine_line|#define ACPI_DO_WHILE0(a)               a
macro_line|#endif
DECL|macro|return_VOID
mdefine_line|#define return_VOID                     ACPI_DO_WHILE0 ({acpi_ut_exit(__LINE__,&amp;_dbg);return;})
DECL|macro|return_ACPI_STATUS
mdefine_line|#define return_ACPI_STATUS(s)           ACPI_DO_WHILE0 ({acpi_ut_status_exit(__LINE__,&amp;_dbg,(s));return((s));})
DECL|macro|return_VALUE
mdefine_line|#define return_VALUE(s)                 ACPI_DO_WHILE0 ({acpi_ut_value_exit(__LINE__,&amp;_dbg,(acpi_integer)(s));return((s));})
DECL|macro|return_PTR
mdefine_line|#define return_PTR(s)                   ACPI_DO_WHILE0 ({acpi_ut_ptr_exit(__LINE__,&amp;_dbg,(u8 *)(s));return((s));})
multiline_comment|/* Conditional execution */
DECL|macro|ACPI_DEBUG_EXEC
mdefine_line|#define ACPI_DEBUG_EXEC(a)              a
DECL|macro|ACPI_NORMAL_EXEC
mdefine_line|#define ACPI_NORMAL_EXEC(a)
DECL|macro|ACPI_DEBUG_DEFINE
mdefine_line|#define ACPI_DEBUG_DEFINE(a)            a;
DECL|macro|ACPI_DEBUG_ONLY_MEMBERS
mdefine_line|#define ACPI_DEBUG_ONLY_MEMBERS(a)      a;
DECL|macro|_VERBOSE_STRUCTURES
mdefine_line|#define _VERBOSE_STRUCTURES
multiline_comment|/* Stack and buffer dumping */
DECL|macro|ACPI_DUMP_STACK_ENTRY
mdefine_line|#define ACPI_DUMP_STACK_ENTRY(a)        acpi_ex_dump_operand(a)
DECL|macro|ACPI_DUMP_OPERANDS
mdefine_line|#define ACPI_DUMP_OPERANDS(a,b,c,d,e)   acpi_ex_dump_operands(a,b,c,d,e,_THIS_MODULE,__LINE__)
DECL|macro|ACPI_DUMP_ENTRY
mdefine_line|#define ACPI_DUMP_ENTRY(a,b)            acpi_ns_dump_entry (a,b)
DECL|macro|ACPI_DUMP_TABLES
mdefine_line|#define ACPI_DUMP_TABLES(a,b)           acpi_ns_dump_tables(a,b)
DECL|macro|ACPI_DUMP_PATHNAME
mdefine_line|#define ACPI_DUMP_PATHNAME(a,b,c,d)     acpi_ns_dump_pathname(a,b,c,d)
DECL|macro|ACPI_DUMP_RESOURCE_LIST
mdefine_line|#define ACPI_DUMP_RESOURCE_LIST(a)      acpi_rs_dump_resource_list(a)
DECL|macro|ACPI_DUMP_BUFFER
mdefine_line|#define ACPI_DUMP_BUFFER(a,b)           acpi_ut_dump_buffer((u8 *)a,b,DB_BYTE_DISPLAY,_COMPONENT)
DECL|macro|ACPI_BREAK_MSG
mdefine_line|#define ACPI_BREAK_MSG(a)               acpi_os_signal (ACPI_SIGNAL_BREAKPOINT,(a))
multiline_comment|/*&n; * Generate INT3 on ACPI_ERROR (Debug only!)&n; */
DECL|macro|ACPI_ERROR_BREAK
mdefine_line|#define ACPI_ERROR_BREAK
macro_line|#ifdef  ACPI_ERROR_BREAK
DECL|macro|ACPI_BREAK_ON_ERROR
mdefine_line|#define ACPI_BREAK_ON_ERROR(lvl)        if ((lvl)&amp;ACPI_ERROR) &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;acpi_os_signal(ACPI_SIGNAL_BREAKPOINT,&quot;Fatal error encountered&bslash;n&quot;)
macro_line|#else
DECL|macro|ACPI_BREAK_ON_ERROR
mdefine_line|#define ACPI_BREAK_ON_ERROR(lvl)
macro_line|#endif
multiline_comment|/*&n; * Master debug print macros&n; * Print iff:&n; *    1) Debug print for the current component is enabled&n; *    2) Debug error level or trace level for the print statement is enabled&n; */
DECL|macro|ACPI_DEBUG_PRINT
mdefine_line|#define ACPI_DEBUG_PRINT(pl)            acpi_ut_debug_print ACPI_PARAM_LIST(pl)
DECL|macro|ACPI_DEBUG_PRINT_RAW
mdefine_line|#define ACPI_DEBUG_PRINT_RAW(pl)        acpi_ut_debug_print_raw ACPI_PARAM_LIST(pl)
macro_line|#else
multiline_comment|/*&n; * This is the non-debug case -- make everything go away,&n; * leaving no executable debug code!&n; */
DECL|macro|ACPI_MODULE_NAME
mdefine_line|#define ACPI_MODULE_NAME(name)
DECL|macro|_THIS_MODULE
mdefine_line|#define _THIS_MODULE &quot;&quot;
DECL|macro|ACPI_DEBUG_EXEC
mdefine_line|#define ACPI_DEBUG_EXEC(a)
DECL|macro|ACPI_NORMAL_EXEC
mdefine_line|#define ACPI_NORMAL_EXEC(a)             a;
DECL|macro|ACPI_DEBUG_DEFINE
mdefine_line|#define ACPI_DEBUG_DEFINE(a)
DECL|macro|ACPI_DEBUG_ONLY_MEMBERS
mdefine_line|#define ACPI_DEBUG_ONLY_MEMBERS(a)
DECL|macro|ACPI_FUNCTION_NAME
mdefine_line|#define ACPI_FUNCTION_NAME(a)
DECL|macro|ACPI_FUNCTION_TRACE
mdefine_line|#define ACPI_FUNCTION_TRACE(a)
DECL|macro|ACPI_FUNCTION_TRACE_PTR
mdefine_line|#define ACPI_FUNCTION_TRACE_PTR(a,b)
DECL|macro|ACPI_FUNCTION_TRACE_U32
mdefine_line|#define ACPI_FUNCTION_TRACE_U32(a,b)
DECL|macro|ACPI_FUNCTION_TRACE_STR
mdefine_line|#define ACPI_FUNCTION_TRACE_STR(a,b)
DECL|macro|ACPI_FUNCTION_EXIT
mdefine_line|#define ACPI_FUNCTION_EXIT
DECL|macro|ACPI_FUNCTION_STATUS_EXIT
mdefine_line|#define ACPI_FUNCTION_STATUS_EXIT(s)
DECL|macro|ACPI_FUNCTION_VALUE_EXIT
mdefine_line|#define ACPI_FUNCTION_VALUE_EXIT(s)
DECL|macro|ACPI_FUNCTION_ENTRY
mdefine_line|#define ACPI_FUNCTION_ENTRY()
DECL|macro|ACPI_DUMP_STACK_ENTRY
mdefine_line|#define ACPI_DUMP_STACK_ENTRY(a)
DECL|macro|ACPI_DUMP_OPERANDS
mdefine_line|#define ACPI_DUMP_OPERANDS(a,b,c,d,e)
DECL|macro|ACPI_DUMP_ENTRY
mdefine_line|#define ACPI_DUMP_ENTRY(a,b)
DECL|macro|ACPI_DUMP_TABLES
mdefine_line|#define ACPI_DUMP_TABLES(a,b)
DECL|macro|ACPI_DUMP_PATHNAME
mdefine_line|#define ACPI_DUMP_PATHNAME(a,b,c,d)
DECL|macro|ACPI_DUMP_RESOURCE_LIST
mdefine_line|#define ACPI_DUMP_RESOURCE_LIST(a)
DECL|macro|ACPI_DUMP_BUFFER
mdefine_line|#define ACPI_DUMP_BUFFER(a,b)
DECL|macro|ACPI_DEBUG_PRINT
mdefine_line|#define ACPI_DEBUG_PRINT(pl)
DECL|macro|ACPI_DEBUG_PRINT_RAW
mdefine_line|#define ACPI_DEBUG_PRINT_RAW(pl)
DECL|macro|ACPI_BREAK_MSG
mdefine_line|#define ACPI_BREAK_MSG(a)
DECL|macro|return_VOID
mdefine_line|#define return_VOID                     return
DECL|macro|return_ACPI_STATUS
mdefine_line|#define return_ACPI_STATUS(s)           return(s)
DECL|macro|return_VALUE
mdefine_line|#define return_VALUE(s)                 return(s)
DECL|macro|return_PTR
mdefine_line|#define return_PTR(s)                   return(s)
macro_line|#endif
multiline_comment|/*&n; * Some code only gets executed when the debugger is built in.&n; * Note that this is entirely independent of whether the&n; * DEBUG_PRINT stuff (set by ACPI_DEBUG_OUTPUT) is on, or not.&n; */
macro_line|#ifdef ACPI_DEBUGGER
DECL|macro|ACPI_DEBUGGER_EXEC
mdefine_line|#define ACPI_DEBUGGER_EXEC(a)           a
macro_line|#else
DECL|macro|ACPI_DEBUGGER_EXEC
mdefine_line|#define ACPI_DEBUGGER_EXEC(a)
macro_line|#endif
multiline_comment|/*&n; * For 16-bit code, we want to shrink some things even though&n; * we are using ACPI_DEBUG_OUTPUT to get the debug output&n; */
macro_line|#if ACPI_MACHINE_WIDTH == 16
DECL|macro|ACPI_DEBUG_ONLY_MEMBERS
macro_line|#undef ACPI_DEBUG_ONLY_MEMBERS
DECL|macro|_VERBOSE_STRUCTURES
macro_line|#undef _VERBOSE_STRUCTURES
DECL|macro|ACPI_DEBUG_ONLY_MEMBERS
mdefine_line|#define ACPI_DEBUG_ONLY_MEMBERS(a)
macro_line|#endif
macro_line|#ifdef ACPI_DEBUG_OUTPUT
multiline_comment|/*&n; * 1) Set name to blanks&n; * 2) Copy the object name&n; */
DECL|macro|ACPI_ADD_OBJECT_NAME
mdefine_line|#define ACPI_ADD_OBJECT_NAME(a,b)       ACPI_MEMSET (a-&gt;common.name, &squot; &squot;, sizeof (a-&gt;common.name));&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;ACPI_STRNCPY (a-&gt;common.name, acpi_gbl_ns_type_names[b], sizeof (a-&gt;common.name))
macro_line|#else
DECL|macro|ACPI_ADD_OBJECT_NAME
mdefine_line|#define ACPI_ADD_OBJECT_NAME(a,b)
macro_line|#endif
multiline_comment|/*&n; * Memory allocation tracking (DEBUG ONLY)&n; */
macro_line|#ifndef ACPI_DBG_TRACK_ALLOCATIONS
multiline_comment|/* Memory allocation */
DECL|macro|ACPI_MEM_ALLOCATE
mdefine_line|#define ACPI_MEM_ALLOCATE(a)            acpi_ut_allocate((acpi_size)(a),_COMPONENT,_THIS_MODULE,__LINE__)
DECL|macro|ACPI_MEM_CALLOCATE
mdefine_line|#define ACPI_MEM_CALLOCATE(a)           acpi_ut_callocate((acpi_size)(a), _COMPONENT,_THIS_MODULE,__LINE__)
DECL|macro|ACPI_MEM_FREE
mdefine_line|#define ACPI_MEM_FREE(a)                acpi_os_free(a)
DECL|macro|ACPI_MEM_TRACKING
mdefine_line|#define ACPI_MEM_TRACKING(a)
macro_line|#else
multiline_comment|/* Memory allocation */
DECL|macro|ACPI_MEM_ALLOCATE
mdefine_line|#define ACPI_MEM_ALLOCATE(a)            acpi_ut_allocate_and_track((acpi_size)(a),_COMPONENT,_THIS_MODULE,__LINE__)
DECL|macro|ACPI_MEM_CALLOCATE
mdefine_line|#define ACPI_MEM_CALLOCATE(a)           acpi_ut_callocate_and_track((acpi_size)(a), _COMPONENT,_THIS_MODULE,__LINE__)
DECL|macro|ACPI_MEM_FREE
mdefine_line|#define ACPI_MEM_FREE(a)                acpi_ut_free_and_track(a,_COMPONENT,_THIS_MODULE,__LINE__)
DECL|macro|ACPI_MEM_TRACKING
mdefine_line|#define ACPI_MEM_TRACKING(a)            a
macro_line|#endif /* ACPI_DBG_TRACK_ALLOCATIONS */
macro_line|#endif /* ACMACROS_H */
eof
