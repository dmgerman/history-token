multiline_comment|/*&n; * arch/sh/mm/cache-sh2.c&n; *&n; * Copyright (C) 2002 Paul Mundt&n; *&n; * Released under the terms of the GNU GPL v2.0.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n; * Calculate the OC address and set the way bit on the SH-2.&n; *&n; * We must have already jump_to_P2()&squot;ed prior to calling this&n; * function, since we rely on CCR manipulation to do the&n; * Right Thing(tm).&n; */
DECL|function|__get_oc_addr
r_int
r_int
id|__get_oc_addr
c_func
(paren
r_int
r_int
id|set
comma
r_int
r_int
id|way
)paren
(brace
r_int
r_int
id|ccr
suffix:semicolon
multiline_comment|/*&n;&t; * On SH-2 the way bit isn&squot;t tracked in the address field&n;&t; * if we&squot;re doing address array access .. instead, we need&n;&t; * to manually switch out the way in the CCR.&n;&t; */
id|ccr
op_assign
id|ctrl_inl
c_func
(paren
id|CCR
)paren
suffix:semicolon
id|ccr
op_and_assign
op_complement
l_int|0x00c0
suffix:semicolon
id|ccr
op_or_assign
id|way
op_lshift
id|cpu_data-&gt;dcache.way_shift
suffix:semicolon
multiline_comment|/*&n;&t; * Despite the number of sets being halved, we end up losing&n;&t; * the first 2 ways to OCRAM instead of the last 2 (if we&squot;re&n;&t; * 4-way). As a result, forcibly setting the W1 bit handily&n;&t; * bumps us up 2 ways.&n;&t; */
r_if
c_cond
(paren
id|ccr
op_amp
id|CCR_CACHE_ORA
)paren
id|ccr
op_or_assign
l_int|1
op_lshift
(paren
id|cpu_data-&gt;dcache.way_shift
op_plus
l_int|1
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|ccr
comma
id|CCR
)paren
suffix:semicolon
r_return
id|CACHE_OC_ADDRESS_ARRAY
op_or
(paren
id|set
op_lshift
id|cpu_data-&gt;dcache.entry_shift
)paren
suffix:semicolon
)brace
DECL|function|detect_cpu_and_cache_system
r_int
id|__init
id|detect_cpu_and_cache_system
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * For now, assume SH7604 .. fix this later.&n;&t; */
id|cpu_data-&gt;type
op_assign
id|CPU_SH7604
suffix:semicolon
id|cpu_data-&gt;dcache.ways
op_assign
l_int|4
suffix:semicolon
id|cpu_data-&gt;dcache.way_shift
op_assign
l_int|6
suffix:semicolon
id|cpu_data-&gt;dcache.sets
op_assign
l_int|64
suffix:semicolon
id|cpu_data-&gt;dcache.entry_shift
op_assign
l_int|4
suffix:semicolon
id|cpu_data-&gt;dcache.linesz
op_assign
id|L1_CACHE_BYTES
suffix:semicolon
id|cpu_data-&gt;dcache.flags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * SH-2 doesn&squot;t have separate caches&n;&t; */
id|cpu_data-&gt;dcache.flags
op_or_assign
id|SH_CACHE_COMBINED
suffix:semicolon
id|cpu_data-&gt;icache
op_assign
id|cpu_data-&gt;dcache
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
