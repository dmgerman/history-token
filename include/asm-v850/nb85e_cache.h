multiline_comment|/*&n; * include/asm-v850/nb85e_cache_cache.h -- Cache control for NB85E_CACHE212 and&n; * &t;NB85E_CACHE213 cache memories&n; *&n; *  Copyright (C) 2001  NEC Corporation&n; *  Copyright (C) 2001  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_NB85E_CACHE_H__
DECL|macro|__V850_NB85E_CACHE_H__
mdefine_line|#define __V850_NB85E_CACHE_H__
multiline_comment|/* Cache control registers.  */
DECL|macro|NB85E_CACHE_ICC_ADDR
mdefine_line|#define NB85E_CACHE_ICC_ADDR&t;&t;0xFFFFF070
DECL|macro|NB85E_CACHE_DCC_ADDR
mdefine_line|#define NB85E_CACHE_DCC_ADDR&t;&t;0xFFFFF078
multiline_comment|/* Size of a cache line in bytes.  */
DECL|macro|NB85E_CACHE_LINE_SIZE
mdefine_line|#define NB85E_CACHE_LINE_SIZE&t;&t;16
macro_line|#ifndef __ASSEMBLY__
DECL|function|nb85e_cache_flush_cache
r_extern
r_inline
r_void
id|nb85e_cache_flush_cache
(paren
r_int
r_int
id|cache_control_addr
)paren
(brace
multiline_comment|/*&n;&t;   From the NB85E Instruction/Data Cache manual, how to flush&n;&t;   the instruction cache (ICC is the `Instruction Cache Control&n;&t;   Register&squot;):&n;&n;&t;&t;mov&t;0x3, r2&n;&t;  LOP0:&n;&t;&t;ld.h&t;ICC[r0], r1&n;&t;&t;cmp&t;r0, r1&n;&t;&t;bnz&t;LOP0&n;&t;&t;st.h&t;r2, ICC[r0]&n;&t;  LOP1:&t;&t;&t;&t;- First TAG clear&n;&t;&t;ld.h&t;ICC[r0], r1&n;&t;&t;cmp&t;r0, r1&n;&t;&t;bnz&t;LOP1&n;&t;&t;st.h&t;r2, ICC[r0]&n;&t;  LOP2:&t;&t;&t;&t;- Second TAG clear&n;&t;&t;ld.h&t;ICC[r0], r1&n;&t;&t;cmp&t;r0, r1&n;&t;&t;bnz&t;LOP2&n;&t;*/
r_int
id|cache_flush_bits
comma
id|ccr_contents
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;&t;mov&t;0x3, %1;&quot;
l_string|&quot;1:&t;ld.h&t;0[%2], %0;&quot;
l_string|&quot;&t;cmp&t;r0, %0;&quot;
l_string|&quot;&t;bnz&t;1b;&quot;
l_string|&quot;&t;st.h&t;%1, 0[%2];&quot;
l_string|&quot;2:&t;ld.h&t;0[%2], %0;&quot;
l_string|&quot;&t;cmp&t;r0, %0;&quot;
l_string|&quot;&t;bnz&t;2b;&quot;
l_string|&quot;&t;st.h&t;%1, 0[%2];&quot;
l_string|&quot;3:&t;ld.h&t;0[%2], %0;&quot;
l_string|&quot;&t;cmp&t;r0, %0;&quot;
l_string|&quot;&t;bnz&t;3b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|ccr_contents
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|cache_flush_bits
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|cache_control_addr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|nb85e_cache_flush_icache
r_extern
r_inline
r_void
id|nb85e_cache_flush_icache
(paren
r_void
)paren
(brace
id|nb85e_cache_flush_cache
(paren
id|NB85E_CACHE_ICC_ADDR
)paren
suffix:semicolon
)brace
DECL|function|nb85e_cache_flush_dcache
r_extern
r_inline
r_void
id|nb85e_cache_flush_dcache
(paren
r_void
)paren
(brace
id|nb85e_cache_flush_cache
(paren
id|NB85E_CACHE_DCC_ADDR
)paren
suffix:semicolon
)brace
DECL|function|nb85e_cache_flush
r_extern
r_inline
r_void
id|nb85e_cache_flush
(paren
r_void
)paren
(brace
id|nb85e_cache_flush_icache
(paren
)paren
suffix:semicolon
id|nb85e_cache_flush_dcache
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* !__ASSEMBLY__ */
"&f;"
multiline_comment|/* Define standard definitions in terms of processor-specific ones.  */
multiline_comment|/* For &lt;asm/cache.h&gt; */
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define L1_CACHE_BYTES&t;&t;&t;&t;NB85E_CACHE_LINE_SIZE
multiline_comment|/* For &lt;asm/pgalloc.h&gt; */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;&t;&t;nb85e_cache_flush ()
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(mm)&t;&t;&t;nb85e_cache_flush ()
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(mm, start, end)&t;nb85e_cache_flush ()
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(vma, vmaddr)&t;&t;nb85e_cache_flush ()
DECL|macro|flush_page_to_ram
mdefine_line|#define flush_page_to_ram(page)&t;&t;&t;nb85e_cache_flush ()
DECL|macro|flush_dcache_page
mdefine_line|#define flush_dcache_page(page)&t;&t;&t;nb85e_cache_flush_dcache ()
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(start, end)&t;&t;nb85e_cache_flush_icache ()
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma,pg)&t;&t;nb85e_cache_flush_icache ()
DECL|macro|flush_icache
mdefine_line|#define flush_icache()&t;&t;&t;&t;nb85e_cache_flush_icache ()
DECL|macro|flush_cache_sigtramp
mdefine_line|#define flush_cache_sigtramp(vaddr)&t;&t;nb85e_cache_flush_icache ()
macro_line|#endif /* __V850_NB85E_CACHE_H__ */
eof
