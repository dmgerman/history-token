multiline_comment|/*&n; * arch/sh/kernel/cpu/sh2/probe.c&n; *&n; * CPU Subtype Probing for SH-2.&n; *&n; * Copyright (C) 2002 Paul Mundt&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
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
