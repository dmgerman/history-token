multiline_comment|/*&n; * sc-rm7k.c: RM7000 cache management functions.&n; *&n; * Copyright (C) 1997, 2001, 2003, 2004 Ralf Baechle (ralf@linux-mips.org)&n; */
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/bcache.h&gt;
macro_line|#include &lt;asm/cacheops.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/* Primary cache parameters. */
DECL|macro|sc_lsize
mdefine_line|#define sc_lsize&t;32
DECL|macro|tc_pagesize
mdefine_line|#define tc_pagesize&t;(32*128)
multiline_comment|/* Secondary cache parameters. */
DECL|macro|scache_size
mdefine_line|#define scache_size&t;(256*1024)&t;/* Fixed to 256KiB on RM7000 */
r_extern
r_int
r_int
id|icache_way_size
comma
id|dcache_way_size
suffix:semicolon
macro_line|#include &lt;asm/r4kcache.h&gt;
DECL|variable|rm7k_tcache_enabled
r_int
id|rm7k_tcache_enabled
suffix:semicolon
multiline_comment|/*&n; * Writeback and invalidate the primary cache dcache before DMA.&n; * (XXX These need to be fixed ...)&n; */
DECL|function|rm7k_sc_wback_inv
r_static
r_void
id|rm7k_sc_wback_inv
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|end
comma
id|a
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;rm7k_sc_wback_inv[%08lx,%08lx]&quot;
comma
id|addr
comma
id|size
)paren
suffix:semicolon
multiline_comment|/* Catch bad driver code */
id|BUG_ON
c_func
(paren
id|size
op_eq
l_int|0
)paren
suffix:semicolon
id|a
op_assign
id|addr
op_amp
op_complement
(paren
id|sc_lsize
op_minus
l_int|1
)paren
suffix:semicolon
id|end
op_assign
(paren
id|addr
op_plus
id|size
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|sc_lsize
op_minus
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|flush_scache_line
c_func
(paren
id|a
)paren
suffix:semicolon
multiline_comment|/* Hit_Writeback_Inv_SD */
r_if
c_cond
(paren
id|a
op_eq
id|end
)paren
r_break
suffix:semicolon
id|a
op_add_assign
id|sc_lsize
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|rm7k_tcache_enabled
)paren
r_return
suffix:semicolon
id|a
op_assign
id|addr
op_amp
op_complement
(paren
id|tc_pagesize
op_minus
l_int|1
)paren
suffix:semicolon
id|end
op_assign
(paren
id|addr
op_plus
id|size
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|tc_pagesize
op_minus
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|invalidate_tcache_page
c_func
(paren
id|a
)paren
suffix:semicolon
multiline_comment|/* Page_Invalidate_T */
r_if
c_cond
(paren
id|a
op_eq
id|end
)paren
r_break
suffix:semicolon
id|a
op_add_assign
id|tc_pagesize
suffix:semicolon
)brace
)brace
DECL|function|rm7k_sc_inv
r_static
r_void
id|rm7k_sc_inv
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|end
comma
id|a
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;rm7k_sc_inv[%08lx,%08lx]&quot;
comma
id|addr
comma
id|size
)paren
suffix:semicolon
multiline_comment|/* Catch bad driver code */
id|BUG_ON
c_func
(paren
id|size
op_eq
l_int|0
)paren
suffix:semicolon
id|a
op_assign
id|addr
op_amp
op_complement
(paren
id|sc_lsize
op_minus
l_int|1
)paren
suffix:semicolon
id|end
op_assign
(paren
id|addr
op_plus
id|size
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|sc_lsize
op_minus
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|invalidate_scache_line
c_func
(paren
id|a
)paren
suffix:semicolon
multiline_comment|/* Hit_Invalidate_SD */
r_if
c_cond
(paren
id|a
op_eq
id|end
)paren
r_break
suffix:semicolon
id|a
op_add_assign
id|sc_lsize
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|rm7k_tcache_enabled
)paren
r_return
suffix:semicolon
id|a
op_assign
id|addr
op_amp
op_complement
(paren
id|tc_pagesize
op_minus
l_int|1
)paren
suffix:semicolon
id|end
op_assign
(paren
id|addr
op_plus
id|size
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|tc_pagesize
op_minus
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|invalidate_tcache_page
c_func
(paren
id|a
)paren
suffix:semicolon
multiline_comment|/* Page_Invalidate_T */
r_if
c_cond
(paren
id|a
op_eq
id|end
)paren
r_break
suffix:semicolon
id|a
op_add_assign
id|tc_pagesize
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * This function is executed in the uncached segment CKSEG1.&n; * It must not touch the stack, because the stack pointer still points&n; * into CKSEG0.&n; *&n; * Three options:&n; *&t;- Write it in assembly and guarantee that we don&squot;t use the stack.&n; *&t;- Disable caching for CKSEG0 before calling it.&n; *&t;- Pray that GCC doesn&squot;t randomly start using the stack.&n; *&n; * This being Linux, we obviously take the least sane of those options -&n; * following DaveM&squot;s lead in c-r4k.c&n; *&n; * It seems we get our kicks from relying on unguaranteed behaviour in GCC&n; */
DECL|function|__rm7k_sc_enable
r_static
id|__init
r_void
id|__rm7k_sc_enable
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|set_c0_config
c_func
(paren
l_int|1
op_lshift
l_int|3
)paren
suffix:semicolon
multiline_comment|/* CONF_SE */
id|write_c0_taglo
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|write_c0_taghi
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|scache_size
suffix:semicolon
id|i
op_add_assign
id|sc_lsize
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;.set noreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set mips3&bslash;n&bslash;t&quot;
l_string|&quot;cache %1, (%0)&bslash;n&bslash;t&quot;
l_string|&quot;.set mips0&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|KSEG0ADDR
c_func
(paren
id|i
)paren
)paren
comma
l_string|&quot;i&quot;
(paren
id|Index_Store_Tag_SD
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|rm7k_sc_enable
r_static
id|__init
r_void
id|rm7k_sc_enable
c_func
(paren
r_void
)paren
(brace
r_void
(paren
op_star
id|func
)paren
(paren
r_void
)paren
op_assign
(paren
r_void
op_star
)paren
id|KSEG1ADDR
c_func
(paren
op_amp
id|__rm7k_sc_enable
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_c0_config
c_func
(paren
)paren
op_amp
l_int|0x08
)paren
multiline_comment|/* CONF_SE */
r_return
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Enabling secondary cache...&quot;
)paren
suffix:semicolon
id|func
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|rm7k_sc_disable
r_static
r_void
id|rm7k_sc_disable
c_func
(paren
r_void
)paren
(brace
id|clear_c0_config
c_func
(paren
l_int|1
op_lshift
l_int|3
)paren
suffix:semicolon
multiline_comment|/* CONF_SE */
)brace
DECL|variable|rm7k_sc_ops
r_struct
id|bcache_ops
id|rm7k_sc_ops
op_assign
(brace
dot
id|bc_enable
op_assign
id|rm7k_sc_enable
comma
dot
id|bc_disable
op_assign
id|rm7k_sc_disable
comma
dot
id|bc_wback_inv
op_assign
id|rm7k_sc_wback_inv
comma
dot
id|bc_inv
op_assign
id|rm7k_sc_inv
)brace
suffix:semicolon
DECL|function|rm7k_sc_init
r_void
id|__init
id|rm7k_sc_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|config
op_assign
id|read_c0_config
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|config
op_rshift
l_int|31
)paren
op_amp
l_int|1
)paren
multiline_comment|/* Bit 31 set -&gt; no S-Cache */
r_return
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Secondary cache size %dK, linesize %d bytes.&bslash;n&quot;
comma
(paren
id|scache_size
op_rshift
l_int|10
)paren
comma
id|sc_lsize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|config
op_rshift
l_int|3
)paren
op_amp
l_int|1
)paren
)paren
multiline_comment|/* CONF_SE */
id|rm7k_sc_enable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * While we&squot;re at it let&squot;s deal with the tertiary cache.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|config
op_rshift
l_int|17
)paren
op_amp
l_int|1
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * We can&squot;t enable the L3 cache yet. There may be board-specific&n;&t;&t; * magic necessary to turn it on, and blindly asking the CPU to&n;&t;&t; * start using it would may give cache errors.&n;&t;&t; *&n;&t;&t; * Also, board-specific knowledge may allow us to use the&n;&t;&t; * CACHE Flash_Invalidate_T instruction if the tag RAM supports&n;&t;&t; * it, and may specify the size of the L3 cache so we don&squot;t have&n;&t;&t; * to probe it.&n;&t;&t; */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Tertiary cache present, %s enabled&bslash;n&quot;
comma
id|config
op_amp
(paren
l_int|1
op_lshift
l_int|12
)paren
ques
c_cond
l_string|&quot;already&quot;
suffix:colon
l_string|&quot;not (yet)&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|config
op_rshift
l_int|12
)paren
op_amp
l_int|1
)paren
id|rm7k_tcache_enabled
op_assign
l_int|1
suffix:semicolon
)brace
id|bcops
op_assign
op_amp
id|rm7k_sc_ops
suffix:semicolon
)brace
eof
