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
macro_line|#include &lt;linux/byteorder/little_endian.h&gt;
macro_line|#endif
eof
