multiline_comment|/*&n; * include/asm-v850/v850e_cache.h -- Cache control for V850E cache memories&n; *&n; *  Copyright (C) 2001,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
multiline_comment|/* This file implements cache control for the rather simple cache used on&n;   some V850E CPUs, specifically the NB85E/TEG CPU-core and the V850E/ME2&n;   CPU.  V850E2 processors have their own (better) cache&n;   implementation.  */
macro_line|#ifndef __V850_V850E_CACHE_H__
DECL|macro|__V850_V850E_CACHE_H__
mdefine_line|#define __V850_V850E_CACHE_H__
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/* Cache control registers.  */
DECL|macro|V850E_CACHE_BHC_ADDR
mdefine_line|#define V850E_CACHE_BHC_ADDR&t;0xFFFFF06A
DECL|macro|V850E_CACHE_BHC
mdefine_line|#define V850E_CACHE_BHC&t;&t;(*(volatile u16 *)V850E_CACHE_BHC_ADDR)
DECL|macro|V850E_CACHE_ICC_ADDR
mdefine_line|#define V850E_CACHE_ICC_ADDR&t;0xFFFFF070
DECL|macro|V850E_CACHE_ICC
mdefine_line|#define V850E_CACHE_ICC&t;&t;(*(volatile u16 *)V850E_CACHE_ICC_ADDR)
DECL|macro|V850E_CACHE_ISI_ADDR
mdefine_line|#define V850E_CACHE_ISI_ADDR&t;0xFFFFF072
DECL|macro|V850E_CACHE_ISI
mdefine_line|#define V850E_CACHE_ISI&t;&t;(*(volatile u16 *)V850E_CACHE_ISI_ADDR)
DECL|macro|V850E_CACHE_DCC_ADDR
mdefine_line|#define V850E_CACHE_DCC_ADDR&t;0xFFFFF078
DECL|macro|V850E_CACHE_DCC
mdefine_line|#define V850E_CACHE_DCC&t;&t;(*(volatile u16 *)V850E_CACHE_DCC_ADDR)
multiline_comment|/* Size of a cache line in bytes.  */
DECL|macro|V850E_CACHE_LINE_SIZE
mdefine_line|#define V850E_CACHE_LINE_SIZE&t;16
multiline_comment|/* For &lt;asm/cache.h&gt; */
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define L1_CACHE_BYTES&t;&t;V850E_CACHE_LINE_SIZE
macro_line|#if defined(__KERNEL__) &amp;&amp; !defined(__ASSEMBLY__)
multiline_comment|/* Set caching params via the BHC, ICC, and DCC registers.  */
r_void
id|v850e_cache_enable
(paren
id|u16
id|bhc
comma
id|u16
id|icc
comma
id|u16
id|dcc
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ &amp;&amp; !__ASSEMBLY__ */
macro_line|#endif /* __V850_V850E_CACHE_H__ */
eof
