multiline_comment|/*&n;    NetWinder Floating Point Emulator&n;    (c) Rebel.com, 1998-1999&n;&n;    Direct questions, comments to Scott Bambrough &lt;scottb@netwinder.org&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef __FPSR_H__
DECL|macro|__FPSR_H__
mdefine_line|#define __FPSR_H__
multiline_comment|/*&n;The FPSR is a 32 bit register consisting of 4 parts, each exactly&n;one byte.&n;&n;&t;SYSTEM ID&n;&t;EXCEPTION TRAP ENABLE BYTE&n;&t;SYSTEM CONTROL BYTE&n;&t;CUMULATIVE EXCEPTION FLAGS BYTE&n;&t;&n;The FPCR is a 32 bit register consisting of bit flags.&n;*/
multiline_comment|/* SYSTEM ID&n;------------&n;Note: the system id byte is read only  */
DECL|typedef|FPSR
r_typedef
r_int
r_int
id|FPSR
suffix:semicolon
multiline_comment|/* type for floating point status register */
DECL|typedef|FPCR
r_typedef
r_int
r_int
id|FPCR
suffix:semicolon
multiline_comment|/* type for floating point control register */
DECL|macro|MASK_SYSID
mdefine_line|#define MASK_SYSID&t;&t;0xff000000
DECL|macro|BIT_HARDWARE
mdefine_line|#define BIT_HARDWARE&t;&t;0x80000000
DECL|macro|FP_EMULATOR
mdefine_line|#define FP_EMULATOR&t;&t;0x01000000&t;/* System ID for emulator */ 
DECL|macro|FP_ACCELERATOR
mdefine_line|#define FP_ACCELERATOR&t;&t;0x81000000&t;/* System ID for FPA11 */
multiline_comment|/* EXCEPTION TRAP ENABLE BYTE&n;----------------------------- */
DECL|macro|MASK_TRAP_ENABLE
mdefine_line|#define MASK_TRAP_ENABLE&t;0x00ff0000
DECL|macro|MASK_TRAP_ENABLE_STRICT
mdefine_line|#define MASK_TRAP_ENABLE_STRICT&t;0x001f0000
DECL|macro|BIT_IXE
mdefine_line|#define BIT_IXE&t;&t;0x00100000   /* inexact exception enable */
DECL|macro|BIT_UFE
mdefine_line|#define BIT_UFE&t;&t;0x00080000   /* underflow exception enable */
DECL|macro|BIT_OFE
mdefine_line|#define BIT_OFE&t;&t;0x00040000   /* overflow exception enable */
DECL|macro|BIT_DZE
mdefine_line|#define BIT_DZE&t;&t;0x00020000   /* divide by zero exception enable */
DECL|macro|BIT_IOE
mdefine_line|#define BIT_IOE&t;&t;0x00010000   /* invalid operation exception enable */
multiline_comment|/* SYSTEM CONTROL BYTE&n;---------------------- */
DECL|macro|MASK_SYSTEM_CONTROL
mdefine_line|#define MASK_SYSTEM_CONTROL&t;0x0000ff00
DECL|macro|MASK_TRAP_STRICT
mdefine_line|#define MASK_TRAP_STRICT&t;0x00001f00
DECL|macro|BIT_AC
mdefine_line|#define BIT_AC&t;0x00001000&t;/* use alternative C-flag definition&n;&t;&t;&t;&t;   for compares */
DECL|macro|BIT_EP
mdefine_line|#define BIT_EP&t;0x00000800&t;/* use expanded packed decimal format */
DECL|macro|BIT_SO
mdefine_line|#define BIT_SO&t;0x00000400&t;/* select synchronous operation of FPA */
DECL|macro|BIT_NE
mdefine_line|#define BIT_NE&t;0x00000200&t;/* NaN exception bit */
DECL|macro|BIT_ND
mdefine_line|#define BIT_ND&t;0x00000100&t;/* no denormalized numbers bit */
multiline_comment|/* CUMULATIVE EXCEPTION FLAGS BYTE&n;---------------------------------- */
DECL|macro|MASK_EXCEPTION_FLAGS
mdefine_line|#define MASK_EXCEPTION_FLAGS&t;&t;0x000000ff
DECL|macro|MASK_EXCEPTION_FLAGS_STRICT
mdefine_line|#define MASK_EXCEPTION_FLAGS_STRICT&t;0x0000001f
DECL|macro|BIT_IXC
mdefine_line|#define BIT_IXC&t;&t;0x00000010&t;/* inexact exception flag */
DECL|macro|BIT_UFC
mdefine_line|#define BIT_UFC&t;&t;0x00000008&t;/* underflow exception flag */
DECL|macro|BIT_OFC
mdefine_line|#define BIT_OFC&t;&t;0x00000004&t;/* overfloat exception flag */
DECL|macro|BIT_DZC
mdefine_line|#define BIT_DZC&t;&t;0x00000002&t;/* divide by zero exception flag */
DECL|macro|BIT_IOC
mdefine_line|#define BIT_IOC&t;&t;0x00000001&t;/* invalid operation exception flag */
multiline_comment|/* Floating Point Control Register&n;----------------------------------*/
DECL|macro|BIT_RU
mdefine_line|#define BIT_RU&t;&t;0x80000000&t;/* rounded up bit */
DECL|macro|BIT_IE
mdefine_line|#define BIT_IE&t;&t;0x10000000&t;/* inexact bit */
DECL|macro|BIT_MO
mdefine_line|#define BIT_MO&t;&t;0x08000000&t;/* mantissa overflow bit */
DECL|macro|BIT_EO
mdefine_line|#define BIT_EO&t;&t;0x04000000&t;/* exponent overflow bit */
DECL|macro|BIT_SB
mdefine_line|#define BIT_SB&t;&t;0x00000800&t;/* store bounce */
DECL|macro|BIT_AB
mdefine_line|#define BIT_AB&t;&t;0x00000400&t;/* arithmetic bounce */
DECL|macro|BIT_RE
mdefine_line|#define BIT_RE&t;&t;0x00000200&t;/* rounding exception */
DECL|macro|BIT_DA
mdefine_line|#define BIT_DA&t;&t;0x00000100&t;/* disable FPA */
DECL|macro|MASK_OP
mdefine_line|#define MASK_OP&t;&t;0x00f08010&t;/* AU operation code */
DECL|macro|MASK_PR
mdefine_line|#define MASK_PR&t;&t;0x00080080&t;/* AU precision */
DECL|macro|MASK_S1
mdefine_line|#define MASK_S1&t;&t;0x00070000&t;/* AU source register 1 */
DECL|macro|MASK_S2
mdefine_line|#define MASK_S2&t;&t;0x00000007&t;/* AU source register 2 */
DECL|macro|MASK_DS
mdefine_line|#define MASK_DS&t;&t;0x00007000&t;/* AU destination register */
DECL|macro|MASK_RM
mdefine_line|#define MASK_RM&t;&t;0x00000060&t;/* AU rounding mode */
DECL|macro|MASK_ALU
mdefine_line|#define MASK_ALU&t;0x9cfff2ff&t;/* only ALU can write these bits */
DECL|macro|MASK_RESET
mdefine_line|#define MASK_RESET&t;0x00000d00&t;/* bits set on reset, all others cleared */
DECL|macro|MASK_WFC
mdefine_line|#define MASK_WFC&t;MASK_RESET
DECL|macro|MASK_RFC
mdefine_line|#define MASK_RFC&t;~MASK_RESET
macro_line|#endif
eof
