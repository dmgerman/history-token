multiline_comment|/*&n; * include/asm-v850/tlb.h&n; *&n; *  Copyright (C) 2002  NEC Corporation&n; *  Copyright (C) 2002  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_TLB_H__
DECL|macro|__V850_TLB_H__
mdefine_line|#define __V850_TLB_H__
DECL|macro|tlb_flush
mdefine_line|#define tlb_flush(tlb)&t;((void)0)
macro_line|#include &lt;asm-generic/tlb.h&gt;
macro_line|#endif /* __V850_TLB_H__ */
eof
