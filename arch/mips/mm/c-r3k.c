multiline_comment|/*&n; * r2300.c: R2000 and R3000 specific mmu/cache code.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; *&n; * with a lot of changes to make this thing work for R3000s&n; * Tx39XX R4k style caches added. HK&n; * Copyright (C) 1998, 1999, 2000 Harald Koerfgen&n; * Copyright (C) 1998 Gleb Raiko &amp; Vladimir Roganov&n; * Copyright (C) 2001  Maciej W. Rozycki&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/isadep.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
DECL|variable|icache_size
DECL|variable|dcache_size
r_static
r_int
r_int
id|icache_size
comma
id|dcache_size
suffix:semicolon
multiline_comment|/* Size in bytes */
DECL|variable|icache_lsize
DECL|variable|dcache_lsize
r_static
r_int
r_int
id|icache_lsize
comma
id|dcache_lsize
suffix:semicolon
multiline_comment|/* Size in bytes */
DECL|macro|DEBUG_CACHE
macro_line|#undef DEBUG_CACHE
DECL|function|r3k_cache_size
r_int
r_int
id|__init
id|r3k_cache_size
c_func
(paren
r_int
r_int
id|ca_flags
)paren
(brace
r_int
r_int
id|flags
comma
id|status
comma
id|dummy
comma
id|size
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|p
suffix:semicolon
id|p
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|KSEG0
suffix:semicolon
id|flags
op_assign
id|read_c0_status
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* isolate cache space */
id|write_c0_status
c_func
(paren
(paren
id|ca_flags
op_or
id|flags
)paren
op_amp
op_complement
id|ST0_IEC
)paren
suffix:semicolon
op_star
id|p
op_assign
l_int|0xa5a55a5a
suffix:semicolon
id|dummy
op_assign
op_star
id|p
suffix:semicolon
id|status
op_assign
id|read_c0_status
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dummy
op_ne
l_int|0xa5a55a5a
op_logical_or
(paren
id|status
op_amp
id|ST0_CM
)paren
)paren
(brace
id|size
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|size
op_assign
l_int|128
suffix:semicolon
id|size
op_le
l_int|0x40000
suffix:semicolon
id|size
op_lshift_assign
l_int|1
)paren
op_star
(paren
id|p
op_plus
id|size
)paren
op_assign
l_int|0
suffix:semicolon
op_star
id|p
op_assign
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|size
op_assign
l_int|128
suffix:semicolon
(paren
id|size
op_le
l_int|0x40000
)paren
op_logical_and
(paren
op_star
(paren
id|p
op_plus
id|size
)paren
op_eq
l_int|0
)paren
suffix:semicolon
id|size
op_lshift_assign
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
l_int|0x40000
)paren
id|size
op_assign
l_int|0
suffix:semicolon
)brace
id|write_c0_status
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|size
op_star
r_sizeof
(paren
op_star
id|p
)paren
suffix:semicolon
)brace
DECL|function|r3k_cache_lsize
r_int
r_int
id|__init
id|r3k_cache_lsize
c_func
(paren
r_int
r_int
id|ca_flags
)paren
(brace
r_int
r_int
id|flags
comma
id|status
comma
id|lsize
comma
id|i
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|p
suffix:semicolon
id|p
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|KSEG0
suffix:semicolon
id|flags
op_assign
id|read_c0_status
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* isolate cache space */
id|write_c0_status
c_func
(paren
(paren
id|ca_flags
op_or
id|flags
)paren
op_amp
op_complement
id|ST0_IEC
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
l_int|128
suffix:semicolon
id|i
op_increment
)paren
op_star
(paren
id|p
op_plus
id|i
)paren
op_assign
l_int|0
suffix:semicolon
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|p
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|lsize
op_assign
l_int|1
suffix:semicolon
id|lsize
OL
l_int|128
suffix:semicolon
id|lsize
op_lshift_assign
l_int|1
)paren
(brace
op_star
(paren
id|p
op_plus
id|lsize
)paren
suffix:semicolon
id|status
op_assign
id|read_c0_status
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|ST0_CM
)paren
)paren
r_break
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|128
suffix:semicolon
id|i
op_add_assign
id|lsize
)paren
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|p
op_plus
id|i
)paren
op_assign
l_int|0
suffix:semicolon
id|write_c0_status
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|lsize
op_star
r_sizeof
(paren
op_star
id|p
)paren
suffix:semicolon
)brace
DECL|function|r3k_probe_cache
r_static
r_void
id|__init
id|r3k_probe_cache
c_func
(paren
r_void
)paren
(brace
id|dcache_size
op_assign
id|r3k_cache_size
c_func
(paren
id|ST0_ISC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dcache_size
)paren
id|dcache_lsize
op_assign
id|r3k_cache_lsize
c_func
(paren
id|ST0_ISC
)paren
suffix:semicolon
id|icache_size
op_assign
id|r3k_cache_size
c_func
(paren
id|ST0_ISC
op_or
id|ST0_SWC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|icache_size
)paren
id|icache_lsize
op_assign
id|r3k_cache_lsize
c_func
(paren
id|ST0_ISC
op_or
id|ST0_SWC
)paren
suffix:semicolon
)brace
DECL|function|r3k_flush_icache_range
r_static
r_void
id|r3k_flush_icache_range
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
r_int
r_int
id|size
comma
id|i
comma
id|flags
suffix:semicolon
r_volatile
r_int
r_char
op_star
id|p
suffix:semicolon
id|size
op_assign
id|end
op_minus
id|start
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|icache_size
op_logical_or
id|KSEGX
c_func
(paren
id|start
)paren
op_ne
id|KSEG0
)paren
(brace
id|start
op_assign
id|KSEG0
suffix:semicolon
id|size
op_assign
id|icache_size
suffix:semicolon
)brace
id|p
op_assign
(paren
r_char
op_star
)paren
id|start
suffix:semicolon
id|flags
op_assign
id|read_c0_status
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* isolate cache space */
id|write_c0_status
c_func
(paren
(paren
id|ST0_ISC
op_or
id|ST0_SWC
op_or
id|flags
)paren
op_amp
op_complement
id|ST0_IEC
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
id|size
suffix:semicolon
id|i
op_add_assign
l_int|0x080
)paren
(brace
id|asm
(paren
l_string|&quot;sb&bslash;t$0, 0x000(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x004(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x008(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x00c(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x010(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x014(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x018(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x01c(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x020(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x024(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x028(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x02c(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x030(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x034(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x038(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x03c(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x040(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x044(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x048(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x04c(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x050(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x054(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x058(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x05c(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x060(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x064(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x068(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x06c(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x070(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x074(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x078(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x07c(%0)&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|p
)paren
)paren
suffix:semicolon
id|p
op_add_assign
l_int|0x080
suffix:semicolon
)brace
id|write_c0_status
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|r3k_flush_dcache_range
r_static
r_void
id|r3k_flush_dcache_range
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
r_int
r_int
id|size
comma
id|i
comma
id|flags
suffix:semicolon
r_volatile
r_int
r_char
op_star
id|p
suffix:semicolon
id|size
op_assign
id|end
op_minus
id|start
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|dcache_size
op_logical_or
id|KSEGX
c_func
(paren
id|start
)paren
op_ne
id|KSEG0
)paren
(brace
id|start
op_assign
id|KSEG0
suffix:semicolon
id|size
op_assign
id|dcache_size
suffix:semicolon
)brace
id|p
op_assign
(paren
r_char
op_star
)paren
id|start
suffix:semicolon
id|flags
op_assign
id|read_c0_status
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* isolate cache space */
id|write_c0_status
c_func
(paren
(paren
id|ST0_ISC
op_or
id|flags
)paren
op_amp
op_complement
id|ST0_IEC
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
id|size
suffix:semicolon
id|i
op_add_assign
l_int|0x080
)paren
(brace
id|asm
(paren
l_string|&quot;sb&bslash;t$0, 0x000(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x004(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x008(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x00c(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x010(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x014(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x018(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x01c(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x020(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x024(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x028(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x02c(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x030(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x034(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x038(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x03c(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x040(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x044(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x048(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x04c(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x050(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x054(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x058(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x05c(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x060(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x064(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x068(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x06c(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x070(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x074(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x078(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x07c(%0)&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|p
)paren
)paren
suffix:semicolon
id|p
op_add_assign
l_int|0x080
suffix:semicolon
)brace
id|write_c0_status
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|get_phys_page
r_static
r_inline
r_int
r_int
id|get_phys_page
(paren
r_int
r_int
id|addr
comma
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
r_int
id|physpage
suffix:semicolon
id|pgd
op_assign
id|pgd_offset
c_func
(paren
id|mm
comma
id|addr
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|addr
)paren
suffix:semicolon
id|pte
op_assign
id|pte_offset
c_func
(paren
id|pmd
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|physpage
op_assign
id|pte_val
c_func
(paren
op_star
id|pte
)paren
)paren
op_amp
id|_PAGE_VALID
)paren
r_return
id|KSEG0ADDR
c_func
(paren
id|physpage
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|r3k_flush_cache_all
r_static
r_inline
r_void
id|r3k_flush_cache_all
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|r3k___flush_cache_all
r_static
r_inline
r_void
id|r3k___flush_cache_all
c_func
(paren
r_void
)paren
(brace
id|r3k_flush_dcache_range
c_func
(paren
id|KSEG0
comma
id|KSEG0
op_plus
id|dcache_size
)paren
suffix:semicolon
id|r3k_flush_icache_range
c_func
(paren
id|KSEG0
comma
id|KSEG0
op_plus
id|icache_size
)paren
suffix:semicolon
)brace
DECL|function|r3k_flush_cache_mm
r_static
r_void
id|r3k_flush_cache_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
)brace
DECL|function|r3k_flush_cache_range
r_static
r_void
id|r3k_flush_cache_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
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
)brace
DECL|function|r3k_flush_cache_page
r_static
r_void
id|r3k_flush_cache_page
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
)brace
DECL|function|r3k_flush_data_cache_page
r_static
r_void
id|r3k_flush_data_cache_page
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
)brace
DECL|function|r3k_flush_icache_page
r_static
r_void
id|r3k_flush_icache_page
c_func
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
(brace
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
r_if
c_cond
(paren
id|cpu_context
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|mm
)paren
op_eq
l_int|0
)paren
r_return
suffix:semicolon
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
macro_line|#ifdef DEBUG_CACHE
id|printk
c_func
(paren
l_string|&quot;cpage[%d,%08lx]&quot;
comma
id|cpu_context
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|mm
)paren
comma
id|page
)paren
suffix:semicolon
macro_line|#endif
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
id|r3k_flush_icache_range
c_func
(paren
id|physpage
comma
id|physpage
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
)brace
DECL|function|r3k_flush_cache_sigtramp
r_static
r_void
id|r3k_flush_cache_sigtramp
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
macro_line|#ifdef DEBUG_CACHE
id|printk
c_func
(paren
l_string|&quot;csigtramp[%08lx]&quot;
comma
id|addr
)paren
suffix:semicolon
macro_line|#endif
id|flags
op_assign
id|read_c0_status
c_func
(paren
)paren
suffix:semicolon
id|write_c0_status
c_func
(paren
id|flags
op_amp
op_complement
id|ST0_IEC
)paren
suffix:semicolon
multiline_comment|/* Fill the TLB to avoid an exception with caches isolated. */
id|asm
(paren
l_string|&quot;lw&bslash;t$0, 0x000(%0)&bslash;n&bslash;t&quot;
l_string|&quot;lw&bslash;t$0, 0x004(%0)&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
id|write_c0_status
c_func
(paren
(paren
id|ST0_ISC
op_or
id|ST0_SWC
op_or
id|flags
)paren
op_amp
op_complement
id|ST0_IEC
)paren
suffix:semicolon
id|asm
(paren
l_string|&quot;sb&bslash;t$0, 0x000(%0)&bslash;n&bslash;t&quot;
l_string|&quot;sb&bslash;t$0, 0x004(%0)&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
id|write_c0_status
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|r3k_dma_cache_wback_inv
r_static
r_void
id|r3k_dma_cache_wback_inv
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
(brace
multiline_comment|/* Catch bad driver code */
id|BUG_ON
c_func
(paren
id|size
op_eq
l_int|0
)paren
suffix:semicolon
id|iob
c_func
(paren
)paren
suffix:semicolon
id|r3k_flush_dcache_range
c_func
(paren
id|start
comma
id|start
op_plus
id|size
)paren
suffix:semicolon
)brace
DECL|function|ld_mmu_r23000
r_void
id|__init
id|ld_mmu_r23000
c_func
(paren
r_void
)paren
(brace
r_extern
r_void
id|build_clear_page
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|build_copy_page
c_func
(paren
r_void
)paren
suffix:semicolon
id|r3k_probe_cache
c_func
(paren
)paren
suffix:semicolon
id|flush_cache_all
op_assign
id|r3k_flush_cache_all
suffix:semicolon
id|__flush_cache_all
op_assign
id|r3k___flush_cache_all
suffix:semicolon
id|flush_cache_mm
op_assign
id|r3k_flush_cache_mm
suffix:semicolon
id|flush_cache_range
op_assign
id|r3k_flush_cache_range
suffix:semicolon
id|flush_cache_page
op_assign
id|r3k_flush_cache_page
suffix:semicolon
id|flush_icache_page
op_assign
id|r3k_flush_icache_page
suffix:semicolon
id|flush_icache_range
op_assign
id|r3k_flush_icache_range
suffix:semicolon
id|flush_cache_sigtramp
op_assign
id|r3k_flush_cache_sigtramp
suffix:semicolon
id|flush_data_cache_page
op_assign
id|r3k_flush_data_cache_page
suffix:semicolon
id|_dma_cache_wback_inv
op_assign
id|r3k_dma_cache_wback_inv
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Primary instruction cache %ldkB, linesize %ld bytes.&bslash;n&quot;
comma
id|icache_size
op_rshift
l_int|10
comma
id|icache_lsize
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Primary data cache %ldkB, linesize %ld bytes.&bslash;n&quot;
comma
id|dcache_size
op_rshift
l_int|10
comma
id|dcache_lsize
)paren
suffix:semicolon
id|build_clear_page
c_func
(paren
)paren
suffix:semicolon
id|build_copy_page
c_func
(paren
)paren
suffix:semicolon
)brace
eof
