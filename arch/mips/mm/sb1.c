multiline_comment|/*&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; * Copyright (C) 1997, 2001 Ralf Baechle (ralf@gnu.org)&n; * Copyright (C) 2000 Sibyte&n; * &n; * Written by Justin Carlson (carlson@sibyte.com)&n; *&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
multiline_comment|/*&n; * In this entire file, I&squot;m not sure what the role of the L2 on the sb1250 &n; * is.  Since it is coherent to the system, we should never need to flush&n; * it...right?...right???  -JDC&n; */
macro_line|#include &lt;asm/mmu_context.h&gt;
multiline_comment|/* These are probed at ld_mmu time */
DECL|variable|icache_size
r_static
r_int
r_int
id|icache_size
suffix:semicolon
DECL|variable|dcache_size
r_static
r_int
r_int
id|dcache_size
suffix:semicolon
DECL|variable|icache_line_size
r_static
r_int
r_int
id|icache_line_size
suffix:semicolon
DECL|variable|dcache_line_size
r_static
r_int
r_int
id|dcache_line_size
suffix:semicolon
DECL|variable|icache_assoc
r_static
r_int
r_int
id|icache_assoc
suffix:semicolon
DECL|variable|dcache_assoc
r_static
r_int
r_int
id|dcache_assoc
suffix:semicolon
DECL|variable|icache_sets
r_static
r_int
r_int
id|icache_sets
suffix:semicolon
DECL|variable|dcache_sets
r_static
r_int
r_int
id|dcache_sets
suffix:semicolon
DECL|variable|tlb_entries
r_static
r_int
r_int
id|tlb_entries
suffix:semicolon
DECL|function|pgd_init
r_void
id|pgd_init
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_int
r_int
op_star
id|p
op_assign
(paren
r_int
r_int
op_star
)paren
id|page
suffix:semicolon
r_int
id|i
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
id|USER_PTRS_PER_PGD
suffix:semicolon
id|i
op_add_assign
l_int|8
)paren
(brace
id|p
(braket
id|i
op_plus
l_int|0
)braket
op_assign
(paren
r_int
r_int
)paren
id|invalid_pte_table
suffix:semicolon
id|p
(braket
id|i
op_plus
l_int|1
)braket
op_assign
(paren
r_int
r_int
)paren
id|invalid_pte_table
suffix:semicolon
id|p
(braket
id|i
op_plus
l_int|2
)braket
op_assign
(paren
r_int
r_int
)paren
id|invalid_pte_table
suffix:semicolon
id|p
(braket
id|i
op_plus
l_int|3
)braket
op_assign
(paren
r_int
r_int
)paren
id|invalid_pte_table
suffix:semicolon
id|p
(braket
id|i
op_plus
l_int|4
)braket
op_assign
(paren
r_int
r_int
)paren
id|invalid_pte_table
suffix:semicolon
id|p
(braket
id|i
op_plus
l_int|5
)braket
op_assign
(paren
r_int
r_int
)paren
id|invalid_pte_table
suffix:semicolon
id|p
(braket
id|i
op_plus
l_int|6
)braket
op_assign
(paren
r_int
r_int
)paren
id|invalid_pte_table
suffix:semicolon
id|p
(braket
id|i
op_plus
l_int|7
)braket
op_assign
(paren
r_int
r_int
)paren
id|invalid_pte_table
suffix:semicolon
)brace
)brace
DECL|function|flush_tlb_all
r_void
id|flush_tlb_all
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|old_ctx
suffix:semicolon
r_int
id|entry
suffix:semicolon
id|__save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* Save old context and create impossible VPN2 value */
id|old_ctx
op_assign
(paren
id|get_entryhi
c_func
(paren
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|set_entrylo0
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|set_entrylo1
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|entry
op_assign
l_int|0
suffix:semicolon
id|entry
OL
id|tlb_entries
suffix:semicolon
id|entry
op_increment
)paren
(brace
id|set_entryhi
c_func
(paren
id|KSEG0
op_plus
(paren
id|PAGE_SIZE
op_lshift
l_int|1
)paren
op_star
id|entry
)paren
suffix:semicolon
id|set_index
c_func
(paren
id|entry
)paren
suffix:semicolon
id|tlb_write_indexed
c_func
(paren
)paren
suffix:semicolon
)brace
id|set_entryhi
c_func
(paren
id|old_ctx
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* These are the functions hooked by the memory management function pointers */
DECL|function|sb1_clear_page
r_static
r_void
id|sb1_clear_page
c_func
(paren
r_void
op_star
id|page
)paren
(brace
multiline_comment|/* JDCXXX - This should be bottlenecked by the write buffer, but these&n;&t;   things tend to be mildly unpredictable...should check this on the&n;&t;   performance model */
multiline_comment|/* We prefetch 4 lines ahead.  We&squot;re also &quot;cheating&quot; slightly here...&n;&t;   since we know we&squot;re on an SB1, we force the assembler to take &n;&t;   64-bit operands to speed things up */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push                  &bslash;n&quot;
l_string|&quot;.set noreorder             &bslash;n&quot;
l_string|&quot;.set noat                  &bslash;n&quot;
l_string|&quot;.set mips4                 &bslash;n&quot;
l_string|&quot;     addiu     $1, %0, %2  &bslash;n&quot;
multiline_comment|/* Calculate the end of the page to clear */
l_string|&quot;     pref       5,  0(%0)  &bslash;n&quot;
multiline_comment|/* Prefetch the first 4 lines */
l_string|&quot;     pref       5, 32(%0)  &bslash;n&quot;
l_string|&quot;     pref       5, 64(%0)  &bslash;n&quot;
l_string|&quot;     pref       5, 96(%0)  &bslash;n&quot;
l_string|&quot;1:   sd        $0,  0(%0)  &bslash;n&quot;
multiline_comment|/* Throw out a cacheline of 0&squot;s */
l_string|&quot;     sd        $0,  8(%0)  &bslash;n&quot;
l_string|&quot;     sd        $0, 16(%0)  &bslash;n&quot;
l_string|&quot;     sd        $0, 24(%0)  &bslash;n&quot;
l_string|&quot;     pref       5,128(%0)  &bslash;n&quot;
multiline_comment|/* Prefetch 4 lines ahead     */
l_string|&quot;     bne       $1, %0, 1b  &bslash;n&quot;
l_string|&quot;     addiu     %0, %0, 32  &bslash;n&quot;
multiline_comment|/* Next cacheline (This instruction better be short piped!) */
l_string|&quot;.set pop                   &bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|page
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|page
)paren
comma
l_string|&quot;I&quot;
(paren
id|PAGE_SIZE
op_minus
l_int|32
)paren
suffix:colon
l_string|&quot;$1&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|sb1_copy_page
r_static
r_void
id|sb1_copy_page
c_func
(paren
r_void
op_star
id|to
comma
r_void
op_star
id|from
)paren
(brace
multiline_comment|/* This should be optimized in assembly...can&squot;t use ld/sd, though,&n;&t; * because the top 32 bits could be nuked if we took an interrupt&n;&t; * during the routine.  And this is not a good place to be cli()&squot;ing&n;&t; */
multiline_comment|/* The pref&squot;s used here are using &quot;streaming&quot; hints, which cause the&n;&t; * copied data to be kicked out of the cache sooner.  A page copy often&n;&t; * ends up copying a lot more data than is commonly used, so this seems&n;&t; * to make sense in terms of reducing cache pollution, but I&squot;ve no real&n;&t; * performance data to back this up&n;&t; */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push                  &bslash;n&quot;
l_string|&quot;.set noreorder             &bslash;n&quot;
l_string|&quot;.set noat                  &bslash;n&quot;
l_string|&quot;.set mips4                 &bslash;n&quot;
l_string|&quot;     addiu     $1, %0, %4  &bslash;n&quot;
multiline_comment|/* Calculate the end of the page to copy */
l_string|&quot;     pref       4,  0(%0)  &bslash;n&quot;
multiline_comment|/* Prefetch the first 3 lines to be read and copied */
l_string|&quot;     pref       5,  0(%1)  &bslash;n&quot;
l_string|&quot;     pref       4, 32(%0)  &bslash;n&quot;
l_string|&quot;     pref       5, 32(%1)  &bslash;n&quot;
l_string|&quot;     pref       4, 64(%0)  &bslash;n&quot;
l_string|&quot;     pref       5, 64(%1)  &bslash;n&quot;
l_string|&quot;1:   lw        $2,  0(%0)  &bslash;n&quot;
multiline_comment|/* Block copy a cacheline */
l_string|&quot;     lw        $3,  4(%0)  &bslash;n&quot;
l_string|&quot;     lw        $4,  8(%0)  &bslash;n&quot;
l_string|&quot;     lw        $5, 12(%0)  &bslash;n&quot;
l_string|&quot;     lw        $6, 16(%0)  &bslash;n&quot;
l_string|&quot;     lw        $7, 20(%0)  &bslash;n&quot;
l_string|&quot;     lw        $8, 24(%0)  &bslash;n&quot;
l_string|&quot;     lw        $9, 28(%0)  &bslash;n&quot;
l_string|&quot;     pref       4, 96(%0)  &bslash;n&quot;
multiline_comment|/* Prefetch ahead         */
l_string|&quot;     pref       5, 96(%1)  &bslash;n&quot;
l_string|&quot;     sw        $2,  0(%1)  &bslash;n&quot;
l_string|&quot;     sw        $3,  4(%1)  &bslash;n&quot;
l_string|&quot;     sw        $4,  8(%1)  &bslash;n&quot;
l_string|&quot;     sw        $5, 12(%1)  &bslash;n&quot;
l_string|&quot;     sw        $6, 16(%1)  &bslash;n&quot;
l_string|&quot;     sw        $7, 20(%1)  &bslash;n&quot;
l_string|&quot;     sw        $8, 24(%1)  &bslash;n&quot;
l_string|&quot;     sw        $9, 28(%1)  &bslash;n&quot;
l_string|&quot;     addiu     %1, %1, 32  &bslash;n&quot;
multiline_comment|/* Next cacheline */
l_string|&quot;     nop                   &bslash;n&quot;
multiline_comment|/* Force next add to short pipe */
l_string|&quot;     nop                   &bslash;n&quot;
multiline_comment|/* Force next add to short pipe */
l_string|&quot;     bne       $1, %0, 1b  &bslash;n&quot;
l_string|&quot;     addiu     %0, %0, 32  &bslash;n&quot;
multiline_comment|/* Next cacheline */
l_string|&quot;.set pop                   &bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|to
)paren
comma
l_string|&quot;=r&quot;
(paren
id|from
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|from
)paren
comma
l_string|&quot;1&quot;
(paren
id|to
)paren
comma
l_string|&quot;I&quot;
(paren
id|PAGE_SIZE
op_minus
l_int|32
)paren
suffix:colon
l_string|&quot;$1&quot;
comma
l_string|&quot;$2&quot;
comma
l_string|&quot;$3&quot;
comma
l_string|&quot;$4&quot;
comma
l_string|&quot;$5&quot;
comma
l_string|&quot;$6&quot;
comma
l_string|&quot;$7&quot;
comma
l_string|&quot;$8&quot;
comma
l_string|&quot;$9&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t;unsigned long *src = from;&n;&t;unsigned long *dest = to;&n;&t;unsigned long *target = (unsigned long *) (((unsigned long)src) + PAGE_SIZE);&n;&t;while (src != target) {&n;&t;&t;*dest++ = *src++;&n;&t;}&n;*/
)brace
multiline_comment|/*&n; * The dcache is fully coherent to the system, with one&n; * big caveat:  the instruction stream.  In other words,&n; * if we miss in the icache, and have dirty data in the&n; * L1 dcache, then we&squot;ll go out to memory (or the L2) and&n; * get the not-as-recent data.&n; * &n; * So the only time we have to flush the dcache is when&n; * we&squot;re flushing the icache.  Since the L2 is fully&n; * coherent to everything, including I/O, we never have&n; * to flush it&n; */
DECL|function|sb1_flush_cache_all
r_static
r_void
id|sb1_flush_cache_all
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Haven&squot;t worried too much about speed here; given that we&squot;re flushing&n;&t; * the icache, the time to invalidate is dwarfed by the time it&squot;s going&n;&t; * to take to refill it.  Register usage:&n;&t; * &n;&t; * $1 - moving cache index&n;&t; * $2 - set count&n;&t; */
r_if
c_cond
(paren
id|icache_sets
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;.set push                  &bslash;n&quot;
l_string|&quot;.set noreorder             &bslash;n&quot;
l_string|&quot;.set noat                  &bslash;n&quot;
l_string|&quot;.set mips4                 &bslash;n&quot;
l_string|&quot;     move   $1, %2         &bslash;n&quot;
multiline_comment|/* Start at index 0 */
l_string|&quot;1:   cache  0, 0($1)       &bslash;n&quot;
multiline_comment|/* Invalidate this index */
l_string|&quot;     addiu  %1, %1, -1     &bslash;n&quot;
multiline_comment|/* Decrement loop count */
l_string|&quot;     bnez   %1, 1b         &bslash;n&quot;
multiline_comment|/* loop test */
l_string|&quot;     addu   $1, $1, %0     &bslash;n&quot;
multiline_comment|/* Next address JDCXXX - Should be short piped */
l_string|&quot;.set pop                   &bslash;n&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|icache_line_size
)paren
comma
l_string|&quot;r&quot;
(paren
id|icache_sets
op_star
id|icache_assoc
)paren
comma
l_string|&quot;r&quot;
(paren
id|KSEG0
)paren
suffix:colon
l_string|&quot;$1&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dcache_sets
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;.set push                  &bslash;n&quot;
l_string|&quot;.set noreorder             &bslash;n&quot;
l_string|&quot;.set noat                  &bslash;n&quot;
l_string|&quot;.set mips4                 &bslash;n&quot;
l_string|&quot;     move   $1, %2         &bslash;n&quot;
multiline_comment|/* Start at index 0 */
l_string|&quot;1:   cache  0x1, 0($1)     &bslash;n&quot;
multiline_comment|/* WB/Invalidate this index */
l_string|&quot;     addiu  %1, %1, -1     &bslash;n&quot;
multiline_comment|/* Decrement loop count */
l_string|&quot;     bnez   %1, 1b         &bslash;n&quot;
multiline_comment|/* loop test */
l_string|&quot;     addu   $1, $1, %0     &bslash;n&quot;
multiline_comment|/* Next address JDCXXX - Should be short piped */
l_string|&quot;.set pop                   &bslash;n&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|dcache_line_size
)paren
comma
l_string|&quot;r&quot;
(paren
id|dcache_sets
op_star
id|dcache_assoc
)paren
comma
l_string|&quot;r&quot;
(paren
id|KSEG0
)paren
suffix:colon
l_string|&quot;$1&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * When flushing a range in the icache, we have to first writeback&n; * the dcache for the same range, so new ifetches will see any&n; * data that was dirty in the dcache&n; */
DECL|function|sb1_flush_icache_range
r_static
r_void
id|sb1_flush_icache_range
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
multiline_comment|/* JDCXXX - Implement me! */
id|sb1_flush_cache_all
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|sb1_flush_cache_mm
r_static
r_void
id|sb1_flush_cache_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
multiline_comment|/* Don&squot;t need to do this, as the dcache is physically tagged */
)brace
DECL|function|sb1_flush_cache_range
r_static
r_void
id|sb1_flush_cache_range
c_func
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
(brace
multiline_comment|/* Don&squot;t need to do this, as the dcache is physically tagged */
)brace
DECL|function|sb1_flush_cache_sigtramp
r_static
r_void
id|sb1_flush_cache_sigtramp
c_func
(paren
r_int
r_int
id|page
)paren
(brace
multiline_comment|/* JDCXXX - Implement me! */
id|sb1_flush_cache_all
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This only needs to make sure stores done up to this&n; * point are visible to other agents outside the CPU.  Given &n; * the coherent nature of the ZBus, all that&squot;s required here is &n; * a sync to make sure the data gets out to the caches and is&n; * visible to an arbitrary A Phase from an external agent &n; *   &n; * Actually, I&squot;m not even sure that&squot;s necessary; the semantics&n; * of this function aren&squot;t clear.  If it&squot;s supposed to serve as&n; * a memory barrier, this is needed.  If it&squot;s only meant to &n; * prevent data from being invisible to non-cpu memory accessors&n; * for some indefinite period of time (e.g. in a non-coherent &n; * dcache) then this function would be a complete nop.&n; */
DECL|function|sb1_flush_page_to_ram
r_static
r_void
id|sb1_flush_page_to_ram
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;     sync  &bslash;n&quot;
multiline_comment|/* Short pipe */
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Cribbed from the r2300 code */
DECL|function|sb1_flush_cache_page
r_static
r_void
id|sb1_flush_cache_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|page
)paren
(brace
id|sb1_flush_cache_all
c_func
(paren
)paren
suffix:semicolon
macro_line|#if 0
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|vma-&gt;vm_mm
suffix:semicolon
r_int
r_int
id|physpage
suffix:semicolon
multiline_comment|/* No icache flush needed without context; */
r_if
c_cond
(paren
id|mm-&gt;context
op_eq
l_int|0
)paren
r_return
suffix:semicolon
multiline_comment|/* No icache flush needed if the page isn&squot;t executable */
r_if
c_cond
(paren
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXEC
)paren
)paren
r_return
suffix:semicolon
id|physpage
op_assign
(paren
r_int
r_int
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|physpage
)paren
id|sb1_flush_icache_range
c_func
(paren
id|physpage
comma
id|physpage
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; *  Cache set values (from the mips64 spec)&n; * 0 - 64&n; * 1 - 128&n; * 2 - 256&n; * 3 - 512&n; * 4 - 1024&n; * 5 - 2048&n; * 6 - 4096&n; * 7 - Reserved&n; */
DECL|function|decode_cache_sets
r_static
r_int
r_int
id|decode_cache_sets
c_func
(paren
r_int
r_int
id|config_field
)paren
(brace
r_if
c_cond
(paren
id|config_field
op_eq
l_int|7
)paren
(brace
multiline_comment|/* JDCXXX - Find a graceful way to abort. */
r_return
l_int|0
suffix:semicolon
)brace
r_return
(paren
l_int|1
op_lshift
(paren
id|config_field
op_plus
l_int|6
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Cache line size values (from the mips64 spec)&n; * 0 - No cache present.&n; * 1 - 4 bytes&n; * 2 - 8 bytes&n; * 3 - 16 bytes&n; * 4 - 32 bytes&n; * 5 - 64 bytes&n; * 6 - 128 bytes&n; * 7 - Reserved&n; */
DECL|function|decode_cache_line_size
r_static
r_int
r_int
id|decode_cache_line_size
c_func
(paren
r_int
r_int
id|config_field
)paren
(brace
r_if
c_cond
(paren
id|config_field
op_eq
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|config_field
op_eq
l_int|7
)paren
(brace
multiline_comment|/* JDCXXX - Find a graceful way to abort. */
r_return
l_int|0
suffix:semicolon
)brace
r_return
(paren
l_int|1
op_lshift
(paren
id|config_field
op_plus
l_int|1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Relevant bits of the config1 register format (from the MIPS32/MIPS64 specs)&n; *&n; * 24:22 Icache sets per way&n; * 21:19 Icache line size&n; * 18:16 Icache Associativity&n; * 15:13 Dcache sets per way&n; * 12:10 Dcache line size&n; * 9:7   Dcache Associativity&n; */
DECL|function|probe_cache_sizes
r_static
r_void
id|probe_cache_sizes
c_func
(paren
r_void
)paren
(brace
id|u32
id|config1
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push                  &bslash;n&quot;
l_string|&quot;.set mips64                &bslash;n&quot;
l_string|&quot;     mfc0    %0, $16, 1    &bslash;n&quot;
multiline_comment|/* Get config1 register */
l_string|&quot;.set pop                   &bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|config1
)paren
)paren
suffix:semicolon
id|icache_line_size
op_assign
id|decode_cache_line_size
c_func
(paren
(paren
id|config1
op_rshift
l_int|19
)paren
op_amp
l_int|0x7
)paren
suffix:semicolon
id|dcache_line_size
op_assign
id|decode_cache_line_size
c_func
(paren
(paren
id|config1
op_rshift
l_int|10
)paren
op_amp
l_int|0x7
)paren
suffix:semicolon
id|icache_sets
op_assign
id|decode_cache_sets
c_func
(paren
(paren
id|config1
op_rshift
l_int|22
)paren
op_amp
l_int|0x7
)paren
suffix:semicolon
id|dcache_sets
op_assign
id|decode_cache_sets
c_func
(paren
(paren
id|config1
op_rshift
l_int|13
)paren
op_amp
l_int|0x7
)paren
suffix:semicolon
id|icache_assoc
op_assign
(paren
(paren
id|config1
op_rshift
l_int|16
)paren
op_amp
l_int|0x7
)paren
op_plus
l_int|1
suffix:semicolon
id|dcache_assoc
op_assign
(paren
(paren
id|config1
op_rshift
l_int|7
)paren
op_amp
l_int|0x7
)paren
op_plus
l_int|1
suffix:semicolon
id|icache_size
op_assign
id|icache_line_size
op_star
id|icache_sets
op_star
id|icache_assoc
suffix:semicolon
id|dcache_size
op_assign
id|dcache_line_size
op_star
id|dcache_sets
op_star
id|dcache_assoc
suffix:semicolon
id|tlb_entries
op_assign
(paren
(paren
id|config1
op_rshift
l_int|25
)paren
op_amp
l_int|0x3f
)paren
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* This is called from loadmmu.c.  We have to set up all the&n;   memory management function pointers, as well as initialize&n;   the caches and tlbs */
DECL|function|ld_mmu_sb1
r_void
id|ld_mmu_sb1
c_func
(paren
r_void
)paren
(brace
id|probe_cache_sizes
c_func
(paren
)paren
suffix:semicolon
id|_clear_page
op_assign
id|sb1_clear_page
suffix:semicolon
id|_copy_page
op_assign
id|sb1_copy_page
suffix:semicolon
id|_flush_cache_all
op_assign
id|sb1_flush_cache_all
suffix:semicolon
id|_flush_cache_mm
op_assign
id|sb1_flush_cache_mm
suffix:semicolon
id|_flush_cache_range
op_assign
id|sb1_flush_cache_range
suffix:semicolon
id|_flush_cache_page
op_assign
id|sb1_flush_cache_page
suffix:semicolon
id|_flush_cache_sigtramp
op_assign
id|sb1_flush_cache_sigtramp
suffix:semicolon
id|_flush_page_to_ram
op_assign
id|sb1_flush_page_to_ram
suffix:semicolon
id|_flush_icache_page
op_assign
id|sb1_flush_cache_page
suffix:semicolon
id|_flush_icache_range
op_assign
id|sb1_flush_icache_range
suffix:semicolon
multiline_comment|/*&n;&t; * JDCXXX I&squot;m not sure whether these are necessary: is this the right &n;&t; * place to initialize the tlb?  If it is, why is it done &n;&t; * at this level instead of as common code in loadmmu()?&n;&t; */
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Turn on caching in kseg0 */
id|set_cp0_config
c_func
(paren
id|CONF_CM_CMASK
comma
l_int|0
)paren
suffix:semicolon
)brace
eof
