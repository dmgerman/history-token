macro_line|#ifndef _CRIS_BYTEORDER_H
DECL|macro|_CRIS_BYTEORDER_H
mdefine_line|#define _CRIS_BYTEORDER_H
macro_line|#ifdef __GNUC__
macro_line|#include &lt;asm/arch/byteorder.h&gt;
multiline_comment|/* defines are necessary because the other files detect the presence&n; * of a defined __arch_swab32, not an inline&n; */
DECL|macro|__arch__swab32
mdefine_line|#define __arch__swab32(x) ___arch__swab32(x)
DECL|macro|__arch__swab16
mdefine_line|#define __arch__swab16(x) ___arch__swab16(x)
macro_line|#if !defined(__STRICT_ANSI__) || defined(__KERNEL__)
DECL|macro|__BYTEORDER_HAS_U64__
macro_line|#  define __BYTEORDER_HAS_U64__
DECL|macro|__SWAB_64_THRU_32__
macro_line|#  define __SWAB_64_THRU_32__
macro_line|#endif
macro_line|#endif /* __GNUC__ */
macro_line|#include &lt;linux/byteorder/little_endian.h&gt;
macro_line|#endif
eof
