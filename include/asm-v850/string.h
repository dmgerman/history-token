multiline_comment|/*&n; * include/asm-v850/string.h -- Architecture specific string routines&n; *&n; *  Copyright (C) 2001,02  NEC Corporation&n; *  Copyright (C) 2001,02  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_STRING_H__
DECL|macro|__V850_STRING_H__
mdefine_line|#define __V850_STRING_H__
DECL|macro|__HAVE_ARCH_MEMCPY
mdefine_line|#define __HAVE_ARCH_MEMCPY
DECL|macro|__HAVE_ARCH_MEMSET
mdefine_line|#define __HAVE_ARCH_MEMSET
DECL|macro|__HAVE_ARCH_MEMMOVE
mdefine_line|#define __HAVE_ARCH_MEMMOVE
r_extern
r_void
op_star
id|memcpy
(paren
r_void
op_star
comma
r_const
r_void
op_star
comma
id|__kernel_size_t
)paren
suffix:semicolon
r_extern
r_void
op_star
id|memset
(paren
r_void
op_star
comma
r_int
comma
id|__kernel_size_t
)paren
suffix:semicolon
r_extern
r_void
op_star
id|memmove
(paren
r_void
op_star
comma
r_const
r_void
op_star
comma
id|__kernel_size_t
)paren
suffix:semicolon
macro_line|#endif /* __V850_STRING_H__ */
eof
