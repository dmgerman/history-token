multiline_comment|/*&n; * include/asm-v850/nb85e_cache_cache.h -- Cache control for NB85E_CACHE212 and&n; * &t;NB85E_CACHE213 cache memories&n; *&n; *  Copyright (C) 2001,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_NB85E_CACHE_H__
DECL|macro|__V850_NB85E_CACHE_H__
mdefine_line|#define __V850_NB85E_CACHE_H__
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/* Cache control registers.  */
DECL|macro|NB85E_CACHE_BHC_ADDR
mdefine_line|#define NB85E_CACHE_BHC_ADDR&t;0xFFFFF06A
DECL|macro|NB85E_CACHE_BHC
mdefine_line|#define NB85E_CACHE_BHC&t;&t;(*(volatile u16 *)NB85E_CACHE_BHC_ADDR)
DECL|macro|NB85E_CACHE_ICC_ADDR
mdefine_line|#define NB85E_CACHE_ICC_ADDR&t;0xFFFFF070
DECL|macro|NB85E_CACHE_ICC
mdefine_line|#define NB85E_CACHE_ICC&t;&t;(*(volatile u16 *)NB85E_CACHE_ICC_ADDR)
DECL|macro|NB85E_CACHE_ISI_ADDR
mdefine_line|#define NB85E_CACHE_ISI_ADDR&t;0xFFFFF072
DECL|macro|NB85E_CACHE_ISI
mdefine_line|#define NB85E_CACHE_ISI&t;&t;(*(volatile u16 *)NB85E_CACHE_ISI_ADDR)
DECL|macro|NB85E_CACHE_DCC_ADDR
mdefine_line|#define NB85E_CACHE_DCC_ADDR&t;0xFFFFF078
DECL|macro|NB85E_CACHE_DCC
mdefine_line|#define NB85E_CACHE_DCC&t;&t;(*(volatile u16 *)NB85E_CACHE_DCC_ADDR)
multiline_comment|/* Size of a cache line in bytes.  */
DECL|macro|NB85E_CACHE_LINE_SIZE
mdefine_line|#define NB85E_CACHE_LINE_SIZE&t;16
multiline_comment|/* For &lt;asm/cache.h&gt; */
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define L1_CACHE_BYTES&t;&t;&t;&t;NB85E_CACHE_LINE_SIZE
macro_line|#if defined(__KERNEL__) &amp;&amp; !defined(__ASSEMBLY__)
multiline_comment|/* Set caching params via the BHC and DCC registers.  */
r_void
id|nb85e_cache_enable
(paren
id|u16
id|bhc
comma
id|u16
id|dcc
)paren
suffix:semicolon
r_struct
id|page
suffix:semicolon
r_struct
id|mm_struct
suffix:semicolon
r_struct
id|vm_area_struct
suffix:semicolon
r_extern
r_void
id|nb85e_cache_flush_all
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|nb85e_cache_flush_mm
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
r_extern
r_void
id|nb85e_cache_flush_range
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
r_extern
r_void
id|nb85e_cache_flush_page
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|page_addr
)paren
suffix:semicolon
r_extern
r_void
id|nb85e_cache_flush_dcache_page
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
r_extern
r_void
id|nb85e_cache_flush_icache
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|nb85e_cache_flush_icache_range
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
r_extern
r_void
id|nb85e_cache_flush_icache_page
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
r_extern
r_void
id|nb85e_cache_flush_icache_user_range
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|adr
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_void
id|nb85e_cache_flush_sigtramp
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all&t;&t;nb85e_cache_flush_all
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm&t;&t;nb85e_cache_flush_mm
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range&t;nb85e_cache_flush_range
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page&t;nb85e_cache_flush_page
DECL|macro|flush_dcache_page
mdefine_line|#define flush_dcache_page&t;nb85e_cache_flush_dcache_page
DECL|macro|flush_icache
mdefine_line|#define flush_icache&t;&t;nb85e_cache_flush_icache
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range&t;nb85e_cache_flush_icache_range
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page&t;nb85e_cache_flush_icache_page
DECL|macro|flush_icache_user_range
mdefine_line|#define flush_icache_user_range&t;nb85e_cache_flush_icache_user_range
DECL|macro|flush_cache_sigtramp
mdefine_line|#define flush_cache_sigtramp&t;nb85e_cache_flush_sigtramp
macro_line|#endif /* __KERNEL__ &amp;&amp; !__ASSEMBLY__ */
macro_line|#endif /* __V850_NB85E_CACHE_H__ */
eof
