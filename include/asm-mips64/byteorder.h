multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 1999 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_BYTEORDER_H
DECL|macro|_ASM_BYTEORDER_H
mdefine_line|#define _ASM_BYTEORDER_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#ifdef __GNUC__
macro_line|#if !defined(__STRICT_ANSI__) || defined(__KERNEL__)
DECL|macro|__BYTEORDER_HAS_U64__
macro_line|#  define __BYTEORDER_HAS_U64__
macro_line|#endif
macro_line|#endif /* __GNUC__ */
macro_line|#if defined (__MIPSEB__)
macro_line|#  include &lt;linux/byteorder/big_endian.h&gt;
macro_line|#elif defined (__MIPSEL__)
macro_line|#  include &lt;linux/byteorder/little_endian.h&gt;
macro_line|#else
macro_line|#  error &quot;MIPS, but neither __MIPSEB__, nor __MIPSEL__???&quot;
macro_line|#endif
macro_line|#endif /* _ASM_BYTEORDER_H */
eof
