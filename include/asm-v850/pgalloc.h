multiline_comment|/*&n; * include/asm-v850/pgalloc.h&n; *&n; *  Copyright (C) 2001,02  NEC Corporation&n; *  Copyright (C) 2001,02  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_PGALLOC_H__
DECL|macro|__V850_PGALLOC_H__
mdefine_line|#define __V850_PGALLOC_H__
macro_line|#include &lt;linux/mm.h&gt;  /* some crap code expects this */
multiline_comment|/* ... and then, there was one.  */
DECL|macro|check_pgt_cache
mdefine_line|#define check_pgt_cache()&t;((void)0)
macro_line|#endif /* __V850_PGALLOC_H__ */
eof
