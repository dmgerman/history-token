multiline_comment|/* $Id: byteorder.h,v 1.15 1997/12/16 19:20:44 davem Exp $ */
macro_line|#ifndef _SPARC_BYTEORDER_H
DECL|macro|_SPARC_BYTEORDER_H
mdefine_line|#define _SPARC_BYTEORDER_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#if defined(__GNUC__) &amp;&amp; !defined(__STRICT_ANSI__) || defined(__KERNEL__)
DECL|macro|__BYTEORDER_HAS_U64__
macro_line|#  define __BYTEORDER_HAS_U64__
DECL|macro|__SWAB_64_THRU_32__
macro_line|#  define __SWAB_64_THRU_32__
macro_line|#endif
macro_line|#include &lt;linux/byteorder/big_endian.h&gt;
macro_line|#endif /* _SPARC_BYTEORDER_H */
eof
