multiline_comment|/*&n; * include/asm-v850/cache.h -- Cache operations&n; *&n; *  Copyright (C) 2001  NEC Corporation&n; *  Copyright (C) 2001  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_CACHE_H__
DECL|macro|__V850_CACHE_H__
mdefine_line|#define __V850_CACHE_H__
multiline_comment|/* All cache operations are machine-dependent.  */
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#ifndef L1_CACHE_BYTES
multiline_comment|/* This processor has no cache, so just choose an arbitrary value.  */
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define L1_CACHE_BYTES&t;&t;16
macro_line|#endif
macro_line|#endif /* __V850_CACHE_H__ */
eof
