multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Inline assembly cache operations.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; * Copyright (C) 1997 - 2002 Ralf Baechle (ralf@gnu.org)&n; * Copyright (C) 2004 Ralf Baechle (ralf@linux-mips.org)&n; */
macro_line|#ifndef _ASM_R4KCACHE_H
DECL|macro|_ASM_R4KCACHE_H
mdefine_line|#define _ASM_R4KCACHE_H
macro_line|#include &lt;asm/asm.h&gt;
macro_line|#include &lt;asm/cacheops.h&gt;
multiline_comment|/*&n; * This macro return a properly sign-extended address suitable as base address&n; * for indexed cache operations.  Two issues here:&n; *&n; *  - The MIPS32 and MIPS64 specs permit an implementation to directly derive&n; *    the index bits from the virtual address.  This breaks with tradition&n; *    set by the R4000.  To keep unpleassant surprises from happening we pick&n; *    an address in KSEG0 / CKSEG0.&n; *  - We need a properly sign extended address for 64-bit code.  To get away&n; *    without ifdefs we let the compiler do it by a type cast.&n; */
DECL|macro|INDEX_BASE
mdefine_line|#define INDEX_BASE&t;CKSEG0
DECL|macro|cache_op
mdefine_line|#define cache_op(op,addr)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.set&t;noreorder&t;&t;&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;.set&t;mips3&bslash;n&bslash;t&t;&t;&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache&t;%0, %1&t;&t;&t;&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;.set&t;mips0&t;&t;&t;&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;.set&t;reorder&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;i&quot; (op), &quot;m&quot; (*(unsigned char *)(addr)))
DECL|function|flush_icache_line_indexed
r_static
r_inline
r_void
id|flush_icache_line_indexed
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|cache_op
c_func
(paren
id|Index_Invalidate_I
comma
id|addr
)paren
suffix:semicolon
)brace
DECL|function|flush_dcache_line_indexed
r_static
r_inline
r_void
id|flush_dcache_line_indexed
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|cache_op
c_func
(paren
id|Index_Writeback_Inv_D
comma
id|addr
)paren
suffix:semicolon
)brace
DECL|function|flush_scache_line_indexed
r_static
r_inline
r_void
id|flush_scache_line_indexed
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|cache_op
c_func
(paren
id|Index_Writeback_Inv_SD
comma
id|addr
)paren
suffix:semicolon
)brace
DECL|function|flush_icache_line
r_static
r_inline
r_void
id|flush_icache_line
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|cache_op
c_func
(paren
id|Hit_Invalidate_I
comma
id|addr
)paren
suffix:semicolon
)brace
DECL|function|flush_dcache_line
r_static
r_inline
r_void
id|flush_dcache_line
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|cache_op
c_func
(paren
id|Hit_Writeback_Inv_D
comma
id|addr
)paren
suffix:semicolon
)brace
DECL|function|invalidate_dcache_line
r_static
r_inline
r_void
id|invalidate_dcache_line
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|cache_op
c_func
(paren
id|Hit_Invalidate_D
comma
id|addr
)paren
suffix:semicolon
)brace
DECL|function|invalidate_scache_line
r_static
r_inline
r_void
id|invalidate_scache_line
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|cache_op
c_func
(paren
id|Hit_Invalidate_SD
comma
id|addr
)paren
suffix:semicolon
)brace
DECL|function|flush_scache_line
r_static
r_inline
r_void
id|flush_scache_line
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|cache_op
c_func
(paren
id|Hit_Writeback_Inv_SD
comma
id|addr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The next two are for badland addresses like signal trampolines.&n; */
DECL|function|protected_flush_icache_line
r_static
r_inline
r_void
id|protected_flush_icache_line
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set noreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set mips3&bslash;n&quot;
l_string|&quot;1:&bslash;tcache %0,(%1)&bslash;n&quot;
l_string|&quot;2:&bslash;t.set mips0&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;.section&bslash;t__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;
id|STR
c_func
(paren
id|PTR
)paren
l_string|&quot;&bslash;t1b,2b&bslash;n&bslash;t&quot;
l_string|&quot;.previous&quot;
suffix:colon
suffix:colon
l_string|&quot;i&quot;
(paren
id|Hit_Invalidate_I
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * R10000 / R12000 hazard - these processors don&squot;t support the Hit_Writeback_D&n; * cacheop so we use Hit_Writeback_Inv_D which is supported by all R4000-style&n; * caches.  We&squot;re talking about one cacheline unnecessarily getting invalidated&n; * here so the penaltiy isn&squot;t overly hard.&n; */
DECL|function|protected_writeback_dcache_line
r_static
r_inline
r_void
id|protected_writeback_dcache_line
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set noreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set mips3&bslash;n&quot;
l_string|&quot;1:&bslash;tcache %0,(%1)&bslash;n&quot;
l_string|&quot;2:&bslash;t.set mips0&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;.section&bslash;t__ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;
id|STR
c_func
(paren
id|PTR
)paren
l_string|&quot;&bslash;t1b,2b&bslash;n&bslash;t&quot;
l_string|&quot;.previous&quot;
suffix:colon
suffix:colon
l_string|&quot;i&quot;
(paren
id|Hit_Writeback_Inv_D
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This one is RM7000-specific&n; */
DECL|function|invalidate_tcache_page
r_static
r_inline
r_void
id|invalidate_tcache_page
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|cache_op
c_func
(paren
id|Page_Invalidate_T
comma
id|addr
)paren
suffix:semicolon
)brace
DECL|macro|cache16_unroll32
mdefine_line|#define cache16_unroll32(base,op)&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.set noreorder&t;&t;&t;&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;.set mips3&t;&t;&t;&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x000(%0); cache %1, 0x010(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x020(%0); cache %1, 0x030(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x040(%0); cache %1, 0x050(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x060(%0); cache %1, 0x070(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x080(%0); cache %1, 0x090(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x0a0(%0); cache %1, 0x0b0(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x0c0(%0); cache %1, 0x0d0(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x0e0(%0); cache %1, 0x0f0(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x100(%0); cache %1, 0x110(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x120(%0); cache %1, 0x130(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x140(%0); cache %1, 0x150(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x160(%0); cache %1, 0x170(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x180(%0); cache %1, 0x190(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x1a0(%0); cache %1, 0x1b0(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x1c0(%0); cache %1, 0x1d0(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x1e0(%0); cache %1, 0x1f0(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;.set mips0&t;&t;&t;&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;.set reorder&t;&t;&t;&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&t;:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot; (base),&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;  &quot;i&quot; (op));
DECL|function|blast_dcache16
r_static
r_inline
r_void
id|blast_dcache16
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start
op_assign
id|INDEX_BASE
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|current_cpu_data.dcache.waysize
suffix:semicolon
r_int
r_int
id|ws_inc
op_assign
l_int|1UL
op_lshift
id|current_cpu_data.dcache.waybit
suffix:semicolon
r_int
r_int
id|ws_end
op_assign
id|current_cpu_data.dcache.ways
op_lshift
id|current_cpu_data.dcache.waybit
suffix:semicolon
r_int
r_int
id|ws
comma
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|ws
op_assign
l_int|0
suffix:semicolon
id|ws
OL
id|ws_end
suffix:semicolon
id|ws
op_add_assign
id|ws_inc
)paren
r_for
c_loop
(paren
id|addr
op_assign
id|start
suffix:semicolon
id|addr
OL
id|end
suffix:semicolon
id|addr
op_add_assign
l_int|0x200
)paren
id|cache16_unroll32
c_func
(paren
id|addr
op_or
id|ws
comma
id|Index_Writeback_Inv_D
)paren
suffix:semicolon
)brace
DECL|function|blast_dcache16_page
r_static
r_inline
r_void
id|blast_dcache16_page
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|PAGE_SIZE
suffix:semicolon
r_do
(brace
id|cache16_unroll32
c_func
(paren
id|start
comma
id|Hit_Writeback_Inv_D
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x200
suffix:semicolon
)brace
r_while
c_loop
(paren
id|start
OL
id|end
)paren
suffix:semicolon
)brace
DECL|function|blast_dcache16_page_indexed
r_static
r_inline
r_void
id|blast_dcache16_page_indexed
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|PAGE_SIZE
suffix:semicolon
r_int
r_int
id|ws_inc
op_assign
l_int|1UL
op_lshift
id|current_cpu_data.dcache.waybit
suffix:semicolon
r_int
r_int
id|ws_end
op_assign
id|current_cpu_data.dcache.ways
op_lshift
id|current_cpu_data.dcache.waybit
suffix:semicolon
r_int
r_int
id|ws
comma
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|ws
op_assign
l_int|0
suffix:semicolon
id|ws
OL
id|ws_end
suffix:semicolon
id|ws
op_add_assign
id|ws_inc
)paren
r_for
c_loop
(paren
id|addr
op_assign
id|start
suffix:semicolon
id|addr
OL
id|end
suffix:semicolon
id|addr
op_add_assign
l_int|0x200
)paren
id|cache16_unroll32
c_func
(paren
id|addr
op_or
id|ws
comma
id|Index_Writeback_Inv_D
)paren
suffix:semicolon
)brace
DECL|function|blast_icache16
r_static
r_inline
r_void
id|blast_icache16
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start
op_assign
id|INDEX_BASE
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|current_cpu_data.icache.waysize
suffix:semicolon
r_int
r_int
id|ws_inc
op_assign
l_int|1UL
op_lshift
id|current_cpu_data.icache.waybit
suffix:semicolon
r_int
r_int
id|ws_end
op_assign
id|current_cpu_data.icache.ways
op_lshift
id|current_cpu_data.icache.waybit
suffix:semicolon
r_int
r_int
id|ws
comma
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|ws
op_assign
l_int|0
suffix:semicolon
id|ws
OL
id|ws_end
suffix:semicolon
id|ws
op_add_assign
id|ws_inc
)paren
r_for
c_loop
(paren
id|addr
op_assign
id|start
suffix:semicolon
id|addr
OL
id|end
suffix:semicolon
id|addr
op_add_assign
l_int|0x200
)paren
id|cache16_unroll32
c_func
(paren
id|addr
op_or
id|ws
comma
id|Index_Invalidate_I
)paren
suffix:semicolon
)brace
DECL|function|blast_icache16_page
r_static
r_inline
r_void
id|blast_icache16_page
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|PAGE_SIZE
suffix:semicolon
r_do
(brace
id|cache16_unroll32
c_func
(paren
id|start
comma
id|Hit_Invalidate_I
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x200
suffix:semicolon
)brace
r_while
c_loop
(paren
id|start
OL
id|end
)paren
suffix:semicolon
)brace
DECL|function|blast_icache16_page_indexed
r_static
r_inline
r_void
id|blast_icache16_page_indexed
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|PAGE_SIZE
suffix:semicolon
r_int
r_int
id|ws_inc
op_assign
l_int|1UL
op_lshift
id|current_cpu_data.icache.waybit
suffix:semicolon
r_int
r_int
id|ws_end
op_assign
id|current_cpu_data.icache.ways
op_lshift
id|current_cpu_data.icache.waybit
suffix:semicolon
r_int
r_int
id|ws
comma
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|ws
op_assign
l_int|0
suffix:semicolon
id|ws
OL
id|ws_end
suffix:semicolon
id|ws
op_add_assign
id|ws_inc
)paren
r_for
c_loop
(paren
id|addr
op_assign
id|start
suffix:semicolon
id|addr
OL
id|end
suffix:semicolon
id|addr
op_add_assign
l_int|0x200
)paren
id|cache16_unroll32
c_func
(paren
id|addr
op_or
id|ws
comma
id|Index_Invalidate_I
)paren
suffix:semicolon
)brace
DECL|function|blast_scache16
r_static
r_inline
r_void
id|blast_scache16
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start
op_assign
id|INDEX_BASE
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|current_cpu_data.scache.waysize
suffix:semicolon
r_int
r_int
id|ws_inc
op_assign
l_int|1UL
op_lshift
id|current_cpu_data.scache.waybit
suffix:semicolon
r_int
r_int
id|ws_end
op_assign
id|current_cpu_data.scache.ways
op_lshift
id|current_cpu_data.scache.waybit
suffix:semicolon
r_int
r_int
id|ws
comma
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|ws
op_assign
l_int|0
suffix:semicolon
id|ws
OL
id|ws_end
suffix:semicolon
id|ws
op_add_assign
id|ws_inc
)paren
r_for
c_loop
(paren
id|addr
op_assign
id|start
suffix:semicolon
id|addr
OL
id|end
suffix:semicolon
id|addr
op_add_assign
l_int|0x200
)paren
id|cache16_unroll32
c_func
(paren
id|addr
op_or
id|ws
comma
id|Index_Writeback_Inv_SD
)paren
suffix:semicolon
)brace
DECL|function|blast_scache16_page
r_static
r_inline
r_void
id|blast_scache16_page
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
id|page
op_plus
id|PAGE_SIZE
suffix:semicolon
r_do
(brace
id|cache16_unroll32
c_func
(paren
id|start
comma
id|Hit_Writeback_Inv_SD
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x200
suffix:semicolon
)brace
r_while
c_loop
(paren
id|start
OL
id|end
)paren
suffix:semicolon
)brace
DECL|function|blast_scache16_page_indexed
r_static
r_inline
r_void
id|blast_scache16_page_indexed
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|PAGE_SIZE
suffix:semicolon
r_int
r_int
id|ws_inc
op_assign
l_int|1UL
op_lshift
id|current_cpu_data.scache.waybit
suffix:semicolon
r_int
r_int
id|ws_end
op_assign
id|current_cpu_data.scache.ways
op_lshift
id|current_cpu_data.scache.waybit
suffix:semicolon
r_int
r_int
id|ws
comma
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|ws
op_assign
l_int|0
suffix:semicolon
id|ws
OL
id|ws_end
suffix:semicolon
id|ws
op_add_assign
id|ws_inc
)paren
r_for
c_loop
(paren
id|addr
op_assign
id|start
suffix:semicolon
id|addr
OL
id|end
suffix:semicolon
id|addr
op_add_assign
l_int|0x200
)paren
id|cache16_unroll32
c_func
(paren
id|addr
op_or
id|ws
comma
id|Index_Writeback_Inv_SD
)paren
suffix:semicolon
)brace
DECL|macro|cache32_unroll32
mdefine_line|#define cache32_unroll32(base,op)&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.set noreorder&t;&t;&t;&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;.set mips3&t;&t;&t;&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x000(%0); cache %1, 0x020(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x040(%0); cache %1, 0x060(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x080(%0); cache %1, 0x0a0(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x0c0(%0); cache %1, 0x0e0(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x100(%0); cache %1, 0x120(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x140(%0); cache %1, 0x160(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x180(%0); cache %1, 0x1a0(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x1c0(%0); cache %1, 0x1e0(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x200(%0); cache %1, 0x220(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x240(%0); cache %1, 0x260(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x280(%0); cache %1, 0x2a0(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x2c0(%0); cache %1, 0x2e0(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x300(%0); cache %1, 0x320(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x340(%0); cache %1, 0x360(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x380(%0); cache %1, 0x3a0(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x3c0(%0); cache %1, 0x3e0(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;.set mips0&t;&t;&t;&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;.set reorder&t;&t;&t;&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&t;:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot; (base),&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;  &quot;i&quot; (op));
DECL|function|blast_dcache32
r_static
r_inline
r_void
id|blast_dcache32
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start
op_assign
id|INDEX_BASE
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|current_cpu_data.dcache.waysize
suffix:semicolon
r_int
r_int
id|ws_inc
op_assign
l_int|1UL
op_lshift
id|current_cpu_data.dcache.waybit
suffix:semicolon
r_int
r_int
id|ws_end
op_assign
id|current_cpu_data.dcache.ways
op_lshift
id|current_cpu_data.dcache.waybit
suffix:semicolon
r_int
r_int
id|ws
comma
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|ws
op_assign
l_int|0
suffix:semicolon
id|ws
OL
id|ws_end
suffix:semicolon
id|ws
op_add_assign
id|ws_inc
)paren
r_for
c_loop
(paren
id|addr
op_assign
id|start
suffix:semicolon
id|addr
OL
id|end
suffix:semicolon
id|addr
op_add_assign
l_int|0x400
)paren
id|cache32_unroll32
c_func
(paren
id|addr
op_or
id|ws
comma
id|Index_Writeback_Inv_D
)paren
suffix:semicolon
)brace
DECL|function|blast_dcache32_page
r_static
r_inline
r_void
id|blast_dcache32_page
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|PAGE_SIZE
suffix:semicolon
r_do
(brace
id|cache32_unroll32
c_func
(paren
id|start
comma
id|Hit_Writeback_Inv_D
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x400
suffix:semicolon
)brace
r_while
c_loop
(paren
id|start
OL
id|end
)paren
suffix:semicolon
)brace
DECL|function|blast_dcache32_page_indexed
r_static
r_inline
r_void
id|blast_dcache32_page_indexed
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|PAGE_SIZE
suffix:semicolon
r_int
r_int
id|ws_inc
op_assign
l_int|1UL
op_lshift
id|current_cpu_data.dcache.waybit
suffix:semicolon
r_int
r_int
id|ws_end
op_assign
id|current_cpu_data.dcache.ways
op_lshift
id|current_cpu_data.dcache.waybit
suffix:semicolon
r_int
r_int
id|ws
comma
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|ws
op_assign
l_int|0
suffix:semicolon
id|ws
OL
id|ws_end
suffix:semicolon
id|ws
op_add_assign
id|ws_inc
)paren
r_for
c_loop
(paren
id|addr
op_assign
id|start
suffix:semicolon
id|addr
OL
id|end
suffix:semicolon
id|addr
op_add_assign
l_int|0x400
)paren
id|cache32_unroll32
c_func
(paren
id|addr
op_or
id|ws
comma
id|Index_Writeback_Inv_D
)paren
suffix:semicolon
)brace
DECL|function|blast_icache32
r_static
r_inline
r_void
id|blast_icache32
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start
op_assign
id|INDEX_BASE
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|current_cpu_data.icache.waysize
suffix:semicolon
r_int
r_int
id|ws_inc
op_assign
l_int|1UL
op_lshift
id|current_cpu_data.icache.waybit
suffix:semicolon
r_int
r_int
id|ws_end
op_assign
id|current_cpu_data.icache.ways
op_lshift
id|current_cpu_data.icache.waybit
suffix:semicolon
r_int
r_int
id|ws
comma
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|ws
op_assign
l_int|0
suffix:semicolon
id|ws
OL
id|ws_end
suffix:semicolon
id|ws
op_add_assign
id|ws_inc
)paren
r_for
c_loop
(paren
id|addr
op_assign
id|start
suffix:semicolon
id|addr
OL
id|end
suffix:semicolon
id|addr
op_add_assign
l_int|0x400
)paren
id|cache32_unroll32
c_func
(paren
id|addr
op_or
id|ws
comma
id|Index_Invalidate_I
)paren
suffix:semicolon
)brace
DECL|function|blast_icache32_page
r_static
r_inline
r_void
id|blast_icache32_page
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|PAGE_SIZE
suffix:semicolon
r_do
(brace
id|cache32_unroll32
c_func
(paren
id|start
comma
id|Hit_Invalidate_I
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x400
suffix:semicolon
)brace
r_while
c_loop
(paren
id|start
OL
id|end
)paren
suffix:semicolon
)brace
DECL|function|blast_icache32_page_indexed
r_static
r_inline
r_void
id|blast_icache32_page_indexed
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|PAGE_SIZE
suffix:semicolon
r_int
r_int
id|ws_inc
op_assign
l_int|1UL
op_lshift
id|current_cpu_data.icache.waybit
suffix:semicolon
r_int
r_int
id|ws_end
op_assign
id|current_cpu_data.icache.ways
op_lshift
id|current_cpu_data.icache.waybit
suffix:semicolon
r_int
r_int
id|ws
comma
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|ws
op_assign
l_int|0
suffix:semicolon
id|ws
OL
id|ws_end
suffix:semicolon
id|ws
op_add_assign
id|ws_inc
)paren
r_for
c_loop
(paren
id|addr
op_assign
id|start
suffix:semicolon
id|addr
OL
id|end
suffix:semicolon
id|addr
op_add_assign
l_int|0x400
)paren
id|cache32_unroll32
c_func
(paren
id|addr
op_or
id|ws
comma
id|Index_Invalidate_I
)paren
suffix:semicolon
)brace
DECL|function|blast_scache32
r_static
r_inline
r_void
id|blast_scache32
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start
op_assign
id|INDEX_BASE
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|current_cpu_data.scache.waysize
suffix:semicolon
r_int
r_int
id|ws_inc
op_assign
l_int|1UL
op_lshift
id|current_cpu_data.scache.waybit
suffix:semicolon
r_int
r_int
id|ws_end
op_assign
id|current_cpu_data.scache.ways
op_lshift
id|current_cpu_data.scache.waybit
suffix:semicolon
r_int
r_int
id|ws
comma
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|ws
op_assign
l_int|0
suffix:semicolon
id|ws
OL
id|ws_end
suffix:semicolon
id|ws
op_add_assign
id|ws_inc
)paren
r_for
c_loop
(paren
id|addr
op_assign
id|start
suffix:semicolon
id|addr
OL
id|end
suffix:semicolon
id|addr
op_add_assign
l_int|0x400
)paren
id|cache32_unroll32
c_func
(paren
id|addr
op_or
id|ws
comma
id|Index_Writeback_Inv_SD
)paren
suffix:semicolon
)brace
DECL|function|blast_scache32_page
r_static
r_inline
r_void
id|blast_scache32_page
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
id|page
op_plus
id|PAGE_SIZE
suffix:semicolon
r_do
(brace
id|cache32_unroll32
c_func
(paren
id|start
comma
id|Hit_Writeback_Inv_SD
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x400
suffix:semicolon
)brace
r_while
c_loop
(paren
id|start
OL
id|end
)paren
suffix:semicolon
)brace
DECL|function|blast_scache32_page_indexed
r_static
r_inline
r_void
id|blast_scache32_page_indexed
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|PAGE_SIZE
suffix:semicolon
r_int
r_int
id|ws_inc
op_assign
l_int|1UL
op_lshift
id|current_cpu_data.scache.waybit
suffix:semicolon
r_int
r_int
id|ws_end
op_assign
id|current_cpu_data.scache.ways
op_lshift
id|current_cpu_data.scache.waybit
suffix:semicolon
r_int
r_int
id|ws
comma
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|ws
op_assign
l_int|0
suffix:semicolon
id|ws
OL
id|ws_end
suffix:semicolon
id|ws
op_add_assign
id|ws_inc
)paren
r_for
c_loop
(paren
id|addr
op_assign
id|start
suffix:semicolon
id|addr
OL
id|end
suffix:semicolon
id|addr
op_add_assign
l_int|0x400
)paren
id|cache32_unroll32
c_func
(paren
id|addr
op_or
id|ws
comma
id|Index_Writeback_Inv_SD
)paren
suffix:semicolon
)brace
DECL|macro|cache64_unroll32
mdefine_line|#define cache64_unroll32(base,op)&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.set noreorder&t;&t;&t;&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;.set mips3&t;&t;&t;&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x000(%0); cache %1, 0x040(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x080(%0); cache %1, 0x0c0(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x100(%0); cache %1, 0x140(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x180(%0); cache %1, 0x1c0(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x200(%0); cache %1, 0x240(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x280(%0); cache %1, 0x2c0(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x300(%0); cache %1, 0x340(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x380(%0); cache %1, 0x3c0(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x400(%0); cache %1, 0x440(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x480(%0); cache %1, 0x4c0(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x500(%0); cache %1, 0x540(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x580(%0); cache %1, 0x5c0(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x600(%0); cache %1, 0x640(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x680(%0); cache %1, 0x6c0(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x700(%0); cache %1, 0x740(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x780(%0); cache %1, 0x7c0(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;.set mips0&t;&t;&t;&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;.set reorder&t;&t;&t;&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&t;:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot; (base),&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;  &quot;i&quot; (op));
DECL|function|blast_icache64
r_static
r_inline
r_void
id|blast_icache64
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start
op_assign
id|INDEX_BASE
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|current_cpu_data.icache.waysize
suffix:semicolon
r_int
r_int
id|ws_inc
op_assign
l_int|1UL
op_lshift
id|current_cpu_data.icache.waybit
suffix:semicolon
r_int
r_int
id|ws_end
op_assign
id|current_cpu_data.icache.ways
op_lshift
id|current_cpu_data.icache.waybit
suffix:semicolon
r_int
r_int
id|ws
comma
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|ws
op_assign
l_int|0
suffix:semicolon
id|ws
OL
id|ws_end
suffix:semicolon
id|ws
op_add_assign
id|ws_inc
)paren
r_for
c_loop
(paren
id|addr
op_assign
id|start
suffix:semicolon
id|addr
OL
id|end
suffix:semicolon
id|addr
op_add_assign
l_int|0x800
)paren
id|cache64_unroll32
c_func
(paren
id|addr
op_or
id|ws
comma
id|Index_Invalidate_I
)paren
suffix:semicolon
)brace
DECL|function|blast_icache64_page
r_static
r_inline
r_void
id|blast_icache64_page
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|PAGE_SIZE
suffix:semicolon
r_do
(brace
id|cache64_unroll32
c_func
(paren
id|start
comma
id|Hit_Invalidate_I
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x800
suffix:semicolon
)brace
r_while
c_loop
(paren
id|start
OL
id|end
)paren
suffix:semicolon
)brace
DECL|function|blast_icache64_page_indexed
r_static
r_inline
r_void
id|blast_icache64_page_indexed
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|PAGE_SIZE
suffix:semicolon
r_int
r_int
id|ws_inc
op_assign
l_int|1UL
op_lshift
id|current_cpu_data.icache.waybit
suffix:semicolon
r_int
r_int
id|ws_end
op_assign
id|current_cpu_data.icache.ways
op_lshift
id|current_cpu_data.icache.waybit
suffix:semicolon
r_int
r_int
id|ws
comma
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|ws
op_assign
l_int|0
suffix:semicolon
id|ws
OL
id|ws_end
suffix:semicolon
id|ws
op_add_assign
id|ws_inc
)paren
r_for
c_loop
(paren
id|addr
op_assign
id|start
suffix:semicolon
id|addr
OL
id|end
suffix:semicolon
id|addr
op_add_assign
l_int|0x800
)paren
id|cache64_unroll32
c_func
(paren
id|addr
op_or
id|ws
comma
id|Index_Invalidate_I
)paren
suffix:semicolon
)brace
DECL|function|blast_scache64
r_static
r_inline
r_void
id|blast_scache64
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start
op_assign
id|INDEX_BASE
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|current_cpu_data.scache.waysize
suffix:semicolon
r_int
r_int
id|ws_inc
op_assign
l_int|1UL
op_lshift
id|current_cpu_data.scache.waybit
suffix:semicolon
r_int
r_int
id|ws_end
op_assign
id|current_cpu_data.scache.ways
op_lshift
id|current_cpu_data.scache.waybit
suffix:semicolon
r_int
r_int
id|ws
comma
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|ws
op_assign
l_int|0
suffix:semicolon
id|ws
OL
id|ws_end
suffix:semicolon
id|ws
op_add_assign
id|ws_inc
)paren
r_for
c_loop
(paren
id|addr
op_assign
id|start
suffix:semicolon
id|addr
OL
id|end
suffix:semicolon
id|addr
op_add_assign
l_int|0x800
)paren
id|cache64_unroll32
c_func
(paren
id|addr
op_or
id|ws
comma
id|Index_Writeback_Inv_SD
)paren
suffix:semicolon
)brace
DECL|function|blast_scache64_page
r_static
r_inline
r_void
id|blast_scache64_page
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
id|page
op_plus
id|PAGE_SIZE
suffix:semicolon
r_do
(brace
id|cache64_unroll32
c_func
(paren
id|start
comma
id|Hit_Writeback_Inv_SD
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x800
suffix:semicolon
)brace
r_while
c_loop
(paren
id|start
OL
id|end
)paren
suffix:semicolon
)brace
DECL|function|blast_scache64_page_indexed
r_static
r_inline
r_void
id|blast_scache64_page_indexed
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|PAGE_SIZE
suffix:semicolon
r_int
r_int
id|ws_inc
op_assign
l_int|1UL
op_lshift
id|current_cpu_data.scache.waybit
suffix:semicolon
r_int
r_int
id|ws_end
op_assign
id|current_cpu_data.scache.ways
op_lshift
id|current_cpu_data.scache.waybit
suffix:semicolon
r_int
r_int
id|ws
comma
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|ws
op_assign
l_int|0
suffix:semicolon
id|ws
OL
id|ws_end
suffix:semicolon
id|ws
op_add_assign
id|ws_inc
)paren
r_for
c_loop
(paren
id|addr
op_assign
id|start
suffix:semicolon
id|addr
OL
id|end
suffix:semicolon
id|addr
op_add_assign
l_int|0x800
)paren
id|cache64_unroll32
c_func
(paren
id|addr
op_or
id|ws
comma
id|Index_Writeback_Inv_SD
)paren
suffix:semicolon
)brace
DECL|macro|cache128_unroll32
mdefine_line|#define cache128_unroll32(base,op)&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.set noreorder&t;&t;&t;&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;.set mips3&t;&t;&t;&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x000(%0); cache %1, 0x080(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x100(%0); cache %1, 0x180(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x200(%0); cache %1, 0x280(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x300(%0); cache %1, 0x380(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x400(%0); cache %1, 0x480(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x500(%0); cache %1, 0x580(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x600(%0); cache %1, 0x680(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x700(%0); cache %1, 0x780(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x800(%0); cache %1, 0x880(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0x900(%0); cache %1, 0x980(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0xa00(%0); cache %1, 0xa80(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0xb00(%0); cache %1, 0xb80(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0xc00(%0); cache %1, 0xc80(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0xd00(%0); cache %1, 0xd80(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0xe00(%0); cache %1, 0xe80(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;cache %1, 0xf00(%0); cache %1, 0xf80(%0)&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;.set mips0&t;&t;&t;&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&quot;&t;.set reorder&t;&t;&t;&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&t;:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot; (base),&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;  &quot;i&quot; (op));
DECL|function|blast_scache128
r_static
r_inline
r_void
id|blast_scache128
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start
op_assign
id|INDEX_BASE
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|current_cpu_data.scache.waysize
suffix:semicolon
r_int
r_int
id|ws_inc
op_assign
l_int|1UL
op_lshift
id|current_cpu_data.scache.waybit
suffix:semicolon
r_int
r_int
id|ws_end
op_assign
id|current_cpu_data.scache.ways
op_lshift
id|current_cpu_data.scache.waybit
suffix:semicolon
r_int
r_int
id|ws
comma
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|ws
op_assign
l_int|0
suffix:semicolon
id|ws
OL
id|ws_end
suffix:semicolon
id|ws
op_add_assign
id|ws_inc
)paren
r_for
c_loop
(paren
id|addr
op_assign
id|start
suffix:semicolon
id|addr
OL
id|end
suffix:semicolon
id|addr
op_add_assign
l_int|0x1000
)paren
id|cache128_unroll32
c_func
(paren
id|addr
op_or
id|ws
comma
id|Index_Writeback_Inv_SD
)paren
suffix:semicolon
)brace
DECL|function|blast_scache128_page
r_static
r_inline
r_void
id|blast_scache128_page
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
id|page
op_plus
id|PAGE_SIZE
suffix:semicolon
r_do
(brace
id|cache128_unroll32
c_func
(paren
id|start
comma
id|Hit_Writeback_Inv_SD
)paren
suffix:semicolon
id|start
op_add_assign
l_int|0x1000
suffix:semicolon
)brace
r_while
c_loop
(paren
id|start
OL
id|end
)paren
suffix:semicolon
)brace
DECL|function|blast_scache128_page_indexed
r_static
r_inline
r_void
id|blast_scache128_page_indexed
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|page
suffix:semicolon
r_int
r_int
id|end
op_assign
id|start
op_plus
id|PAGE_SIZE
suffix:semicolon
r_int
r_int
id|ws_inc
op_assign
l_int|1UL
op_lshift
id|current_cpu_data.scache.waybit
suffix:semicolon
r_int
r_int
id|ws_end
op_assign
id|current_cpu_data.scache.ways
op_lshift
id|current_cpu_data.scache.waybit
suffix:semicolon
r_int
r_int
id|ws
comma
id|addr
suffix:semicolon
r_for
c_loop
(paren
id|ws
op_assign
l_int|0
suffix:semicolon
id|ws
OL
id|ws_end
suffix:semicolon
id|ws
op_add_assign
id|ws_inc
)paren
r_for
c_loop
(paren
id|addr
op_assign
id|start
suffix:semicolon
id|addr
OL
id|end
suffix:semicolon
id|addr
op_add_assign
l_int|0x1000
)paren
id|cache128_unroll32
c_func
(paren
id|addr
op_or
id|ws
comma
id|Index_Writeback_Inv_SD
)paren
suffix:semicolon
)brace
macro_line|#endif /* _ASM_R4KCACHE_H */
eof
