multiline_comment|/*&n; *  linux/include/asm-arm/byteorder.h&n; *&n; * ARM Endian-ness.  In little endian mode, the data bus is connected such&n; * that byte accesses appear as:&n; *  0 = d0...d7, 1 = d8...d15, 2 = d16...d23, 3 = d24...d31&n; * and word accesses (data or instruction) appear as:&n; *  d0...d31&n; *&n; * When in big endian mode, byte accesses appear as:&n; *  0 = d24...d31, 1 = d16...d23, 2 = d8...d15, 3 = d0...d7&n; * and word accesses (data or instruction) appear as:&n; *  d0...d31&n; */
macro_line|#ifndef __ASM_ARM_BYTEORDER_H
DECL|macro|__ASM_ARM_BYTEORDER_H
mdefine_line|#define __ASM_ARM_BYTEORDER_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#if !defined(__STRICT_ANSI__) || defined(__KERNEL__)
DECL|macro|__BYTEORDER_HAS_U64__
macro_line|#  define __BYTEORDER_HAS_U64__
DECL|macro|__SWAB_64_THRU_32__
macro_line|#  define __SWAB_64_THRU_32__
macro_line|#endif
macro_line|#ifdef __ARMEB__
macro_line|#include &lt;linux/byteorder/big_endian.h&gt;
macro_line|#else
macro_line|#include &lt;linux/byteorder/little_endian.h&gt;
macro_line|#endif
macro_line|#endif
eof
