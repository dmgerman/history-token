multiline_comment|/*&n; *  linux/arch/m68k/mm/kmap.c&n; *&n; *  Copyright (C) 1997 Roman Hodek&n; *&n; *  10/01/99 cleaned up the code and changing to the same interface&n; *&t;     used by other architectures&t;&t;/Roman Zippel&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|DEBUG
macro_line|#undef DEBUG
DECL|macro|PTRTREESIZE
mdefine_line|#define PTRTREESIZE&t;(256*1024)
multiline_comment|/*&n; * For 040/060 we can use the virtual memory area like other architectures,&n; * but for 020/030 we want to use early termination page descriptor and we&n; * can&squot;t mix this with normal page descriptors, so we have to copy that code&n; * (mm/vmalloc.c) and return appriorate aligned addresses.&n; */
macro_line|#ifdef CPU_M68040_OR_M68060_ONLY
DECL|macro|IO_SIZE
mdefine_line|#define IO_SIZE&t;&t;PAGE_SIZE
DECL|function|get_io_area
r_static
r_inline
r_struct
id|vm_struct
op_star
id|get_io_area
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_return
id|get_vm_area
c_func
(paren
id|size
comma
id|VM_IOREMAP
)paren
suffix:semicolon
)brace
DECL|function|free_io_area
r_static
r_inline
r_void
id|free_io_area
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
r_return
id|vfree
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|PAGE_MASK
op_amp
(paren
r_int
r_int
)paren
id|addr
)paren
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|IO_SIZE
mdefine_line|#define IO_SIZE&t;&t;(256*1024)
DECL|variable|iolist
r_static
r_struct
id|vm_struct
op_star
id|iolist
suffix:semicolon
DECL|function|get_io_area
r_static
r_struct
id|vm_struct
op_star
id|get_io_area
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_struct
id|vm_struct
op_star
op_star
id|p
comma
op_star
id|tmp
comma
op_star
id|area
suffix:semicolon
id|area
op_assign
(paren
r_struct
id|vm_struct
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|area
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|area
)paren
r_return
l_int|NULL
suffix:semicolon
id|addr
op_assign
id|KMAP_START
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|iolist
suffix:semicolon
(paren
id|tmp
op_assign
op_star
id|p
)paren
suffix:semicolon
id|p
op_assign
op_amp
id|tmp-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|size
op_plus
id|addr
OL
(paren
r_int
r_int
)paren
id|tmp-&gt;addr
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|addr
OG
id|KMAP_END
op_minus
id|size
)paren
r_return
l_int|NULL
suffix:semicolon
id|addr
op_assign
id|tmp-&gt;size
op_plus
(paren
r_int
r_int
)paren
id|tmp-&gt;addr
suffix:semicolon
)brace
id|area-&gt;addr
op_assign
(paren
r_void
op_star
)paren
id|addr
suffix:semicolon
id|area-&gt;size
op_assign
id|size
op_plus
id|IO_SIZE
suffix:semicolon
id|area-&gt;next
op_assign
op_star
id|p
suffix:semicolon
op_star
id|p
op_assign
id|area
suffix:semicolon
r_return
id|area
suffix:semicolon
)brace
DECL|function|free_io_area
r_static
r_inline
r_void
id|free_io_area
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
r_struct
id|vm_struct
op_star
op_star
id|p
comma
op_star
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|addr
)paren
r_return
suffix:semicolon
id|addr
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|addr
op_amp
op_minus
id|IO_SIZE
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|iolist
suffix:semicolon
(paren
id|tmp
op_assign
op_star
id|p
)paren
suffix:semicolon
id|p
op_assign
op_amp
id|tmp-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|tmp-&gt;addr
op_eq
id|addr
)paren
(brace
op_star
id|p
op_assign
id|tmp-&gt;next
suffix:semicolon
id|__iounmap
c_func
(paren
id|tmp-&gt;addr
comma
id|tmp-&gt;size
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif
multiline_comment|/*&n; * Map some physical address range into the kernel address space. The&n; * code is copied and adapted from map_chunk().&n; */
multiline_comment|/* Rewritten by Andreas Schwab to remove all races. */
DECL|function|__ioremap
r_void
op_star
id|__ioremap
c_func
(paren
r_int
r_int
id|physaddr
comma
r_int
r_int
id|size
comma
r_int
id|cacheflag
)paren
(brace
r_struct
id|vm_struct
op_star
id|area
suffix:semicolon
r_int
r_int
id|virtaddr
comma
id|retaddr
suffix:semicolon
r_int
id|offset
suffix:semicolon
id|pgd_t
op_star
id|pgd_dir
suffix:semicolon
id|pmd_t
op_star
id|pmd_dir
suffix:semicolon
id|pte_t
op_star
id|pte_dir
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t allow mappings that wrap..&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|size
op_logical_or
id|size
OG
id|physaddr
op_plus
id|size
)paren
r_return
l_int|NULL
suffix:semicolon
macro_line|#ifdef CONFIG_AMIGA
r_if
c_cond
(paren
id|MACH_IS_AMIGA
)paren
(brace
r_if
c_cond
(paren
(paren
id|physaddr
op_ge
l_int|0x40000000
)paren
op_logical_and
(paren
id|physaddr
op_plus
id|size
OL
l_int|0x60000000
)paren
op_logical_and
(paren
id|cacheflag
op_eq
id|IOMAP_NOCACHE_SER
)paren
)paren
r_return
(paren
r_void
op_star
)paren
id|physaddr
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;ioremap: 0x%lx,0x%lx(%d) - &quot;
comma
id|physaddr
comma
id|size
comma
id|cacheflag
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Mappings have to be aligned&n;&t; */
id|offset
op_assign
id|physaddr
op_amp
(paren
id|IO_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|physaddr
op_and_assign
op_minus
id|IO_SIZE
suffix:semicolon
id|size
op_assign
(paren
id|size
op_plus
id|offset
op_plus
id|IO_SIZE
op_minus
l_int|1
)paren
op_amp
op_minus
id|IO_SIZE
suffix:semicolon
multiline_comment|/*&n;&t; * Ok, go for it..&n;&t; */
id|area
op_assign
id|get_io_area
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|area
)paren
r_return
l_int|NULL
suffix:semicolon
id|virtaddr
op_assign
(paren
r_int
r_int
)paren
id|area-&gt;addr
suffix:semicolon
id|retaddr
op_assign
id|virtaddr
op_plus
id|offset
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;0x%lx,0x%lx,0x%lx&quot;
comma
id|physaddr
comma
id|virtaddr
comma
id|retaddr
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * add cache and table flags to physical address&n;&t; */
r_if
c_cond
(paren
id|CPU_IS_040_OR_060
)paren
(brace
id|physaddr
op_or_assign
(paren
id|_PAGE_PRESENT
op_or
id|_PAGE_GLOBAL040
op_or
id|_PAGE_ACCESSED
op_or
id|_PAGE_DIRTY
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cacheflag
)paren
(brace
r_case
id|IOMAP_FULL_CACHING
suffix:colon
id|physaddr
op_or_assign
id|_PAGE_CACHE040
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IOMAP_NOCACHE_SER
suffix:colon
r_default
suffix:colon
id|physaddr
op_or_assign
id|_PAGE_NOCACHE_S
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IOMAP_NOCACHE_NONSER
suffix:colon
id|physaddr
op_or_assign
id|_PAGE_NOCACHE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IOMAP_WRITETHROUGH
suffix:colon
id|physaddr
op_or_assign
id|_PAGE_CACHE040W
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
id|physaddr
op_or_assign
(paren
id|_PAGE_PRESENT
op_or
id|_PAGE_ACCESSED
op_or
id|_PAGE_DIRTY
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cacheflag
)paren
(brace
r_case
id|IOMAP_NOCACHE_SER
suffix:colon
r_case
id|IOMAP_NOCACHE_NONSER
suffix:colon
r_default
suffix:colon
id|physaddr
op_or_assign
id|_PAGE_NOCACHE030
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IOMAP_FULL_CACHING
suffix:colon
r_case
id|IOMAP_WRITETHROUGH
suffix:colon
r_break
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
(paren
r_int
)paren
id|size
OG
l_int|0
)paren
(brace
macro_line|#ifdef DEBUG
r_if
c_cond
(paren
op_logical_neg
(paren
id|virtaddr
op_amp
(paren
id|PTRTREESIZE
op_minus
l_int|1
)paren
)paren
)paren
id|printk
(paren
l_string|&quot;&bslash;npa=%#lx va=%#lx &quot;
comma
id|physaddr
comma
id|virtaddr
)paren
suffix:semicolon
macro_line|#endif
id|pgd_dir
op_assign
id|pgd_offset_k
c_func
(paren
id|virtaddr
)paren
suffix:semicolon
id|pmd_dir
op_assign
id|pmd_alloc
c_func
(paren
op_amp
id|init_mm
comma
id|pgd_dir
comma
id|virtaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd_dir
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ioremap: no mem for pmd_dir&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|CPU_IS_020_OR_030
)paren
(brace
id|pmd_dir-&gt;pmd
(braket
(paren
id|virtaddr
op_div
id|PTRTREESIZE
)paren
op_amp
l_int|15
)braket
op_assign
id|physaddr
suffix:semicolon
id|physaddr
op_add_assign
id|PTRTREESIZE
suffix:semicolon
id|virtaddr
op_add_assign
id|PTRTREESIZE
suffix:semicolon
id|size
op_sub_assign
id|PTRTREESIZE
suffix:semicolon
)brace
r_else
(brace
id|pte_dir
op_assign
id|pte_alloc_kernel
c_func
(paren
op_amp
id|init_mm
comma
id|pmd_dir
comma
id|virtaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_dir
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ioremap: no mem for pte_dir&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|pte_val
c_func
(paren
op_star
id|pte_dir
)paren
op_assign
id|physaddr
suffix:semicolon
id|virtaddr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|physaddr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|size
op_sub_assign
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|retaddr
suffix:semicolon
)brace
multiline_comment|/*&n; * Unmap a ioremap()ed region again&n; */
DECL|function|iounmap
r_void
id|iounmap
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
macro_line|#ifdef CONFIG_AMIGA
r_if
c_cond
(paren
(paren
op_logical_neg
id|MACH_IS_AMIGA
)paren
op_logical_or
(paren
(paren
(paren
r_int
r_int
)paren
id|addr
OL
l_int|0x40000000
)paren
op_logical_or
(paren
(paren
r_int
r_int
)paren
id|addr
OG
l_int|0x60000000
)paren
)paren
)paren
id|free_io_area
c_func
(paren
id|addr
)paren
suffix:semicolon
macro_line|#else
id|free_io_area
c_func
(paren
id|addr
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * __iounmap unmaps nearly everything, so be careful&n; * it doesn&squot;t free currently pointer/page tables anymore but it&n; * wans&squot;t used anyway and might be added later.&n; */
DECL|function|__iounmap
r_void
id|__iounmap
c_func
(paren
r_void
op_star
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|virtaddr
op_assign
(paren
r_int
r_int
)paren
id|addr
suffix:semicolon
id|pgd_t
op_star
id|pgd_dir
suffix:semicolon
id|pmd_t
op_star
id|pmd_dir
suffix:semicolon
id|pte_t
op_star
id|pte_dir
suffix:semicolon
r_while
c_loop
(paren
(paren
r_int
)paren
id|size
OG
l_int|0
)paren
(brace
id|pgd_dir
op_assign
id|pgd_offset_k
c_func
(paren
id|virtaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd_bad
c_func
(paren
op_star
id|pgd_dir
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;iounmap: bad pgd(%08lx)&bslash;n&quot;
comma
id|pgd_val
c_func
(paren
op_star
id|pgd_dir
)paren
)paren
suffix:semicolon
id|pgd_clear
c_func
(paren
id|pgd_dir
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pmd_dir
op_assign
id|pmd_offset
c_func
(paren
id|pgd_dir
comma
id|virtaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|CPU_IS_020_OR_030
)paren
(brace
r_int
id|pmd_off
op_assign
(paren
id|virtaddr
op_div
id|PTRTREESIZE
)paren
op_amp
l_int|15
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pmd_dir-&gt;pmd
(braket
id|pmd_off
)braket
op_amp
id|_DESCTYPE_MASK
)paren
op_eq
id|_PAGE_PRESENT
)paren
(brace
id|pmd_dir-&gt;pmd
(braket
id|pmd_off
)braket
op_assign
l_int|0
suffix:semicolon
id|virtaddr
op_add_assign
id|PTRTREESIZE
suffix:semicolon
id|size
op_sub_assign
id|PTRTREESIZE
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|pmd_bad
c_func
(paren
op_star
id|pmd_dir
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;iounmap: bad pmd (%08lx)&bslash;n&quot;
comma
id|pmd_val
c_func
(paren
op_star
id|pmd_dir
)paren
)paren
suffix:semicolon
id|pmd_clear
c_func
(paren
id|pmd_dir
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pte_dir
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmd_dir
comma
id|virtaddr
)paren
suffix:semicolon
id|pte_val
c_func
(paren
op_star
id|pte_dir
)paren
op_assign
l_int|0
suffix:semicolon
id|virtaddr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|size
op_sub_assign
id|PAGE_SIZE
suffix:semicolon
)brace
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set new cache mode for some kernel address space.&n; * The caller must push data for that range itself, if such data may already&n; * be in the cache.&n; */
DECL|function|kernel_set_cachemode
r_void
id|kernel_set_cachemode
c_func
(paren
r_void
op_star
id|addr
comma
r_int
r_int
id|size
comma
r_int
id|cmode
)paren
(brace
r_int
r_int
id|virtaddr
op_assign
(paren
r_int
r_int
)paren
id|addr
suffix:semicolon
id|pgd_t
op_star
id|pgd_dir
suffix:semicolon
id|pmd_t
op_star
id|pmd_dir
suffix:semicolon
id|pte_t
op_star
id|pte_dir
suffix:semicolon
r_if
c_cond
(paren
id|CPU_IS_040_OR_060
)paren
(brace
r_switch
c_cond
(paren
id|cmode
)paren
(brace
r_case
id|IOMAP_FULL_CACHING
suffix:colon
id|cmode
op_assign
id|_PAGE_CACHE040
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IOMAP_NOCACHE_SER
suffix:colon
r_default
suffix:colon
id|cmode
op_assign
id|_PAGE_NOCACHE_S
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IOMAP_NOCACHE_NONSER
suffix:colon
id|cmode
op_assign
id|_PAGE_NOCACHE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IOMAP_WRITETHROUGH
suffix:colon
id|cmode
op_assign
id|_PAGE_CACHE040W
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
r_switch
c_cond
(paren
id|cmode
)paren
(brace
r_case
id|IOMAP_NOCACHE_SER
suffix:colon
r_case
id|IOMAP_NOCACHE_NONSER
suffix:colon
r_default
suffix:colon
id|cmode
op_assign
id|_PAGE_NOCACHE030
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IOMAP_FULL_CACHING
suffix:colon
r_case
id|IOMAP_WRITETHROUGH
suffix:colon
id|cmode
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
(paren
r_int
)paren
id|size
OG
l_int|0
)paren
(brace
id|pgd_dir
op_assign
id|pgd_offset_k
c_func
(paren
id|virtaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd_bad
c_func
(paren
op_star
id|pgd_dir
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;iocachemode: bad pgd(%08lx)&bslash;n&quot;
comma
id|pgd_val
c_func
(paren
op_star
id|pgd_dir
)paren
)paren
suffix:semicolon
id|pgd_clear
c_func
(paren
id|pgd_dir
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pmd_dir
op_assign
id|pmd_offset
c_func
(paren
id|pgd_dir
comma
id|virtaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|CPU_IS_020_OR_030
)paren
(brace
r_int
id|pmd_off
op_assign
(paren
id|virtaddr
op_div
id|PTRTREESIZE
)paren
op_amp
l_int|15
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pmd_dir-&gt;pmd
(braket
id|pmd_off
)braket
op_amp
id|_DESCTYPE_MASK
)paren
op_eq
id|_PAGE_PRESENT
)paren
(brace
id|pmd_dir-&gt;pmd
(braket
id|pmd_off
)braket
op_assign
(paren
id|pmd_dir-&gt;pmd
(braket
id|pmd_off
)braket
op_amp
id|_CACHEMASK040
)paren
op_or
id|cmode
suffix:semicolon
id|virtaddr
op_add_assign
id|PTRTREESIZE
suffix:semicolon
id|size
op_sub_assign
id|PTRTREESIZE
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|pmd_bad
c_func
(paren
op_star
id|pmd_dir
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;iocachemode: bad pmd (%08lx)&bslash;n&quot;
comma
id|pmd_val
c_func
(paren
op_star
id|pmd_dir
)paren
)paren
suffix:semicolon
id|pmd_clear
c_func
(paren
id|pmd_dir
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pte_dir
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmd_dir
comma
id|virtaddr
)paren
suffix:semicolon
id|pte_val
c_func
(paren
op_star
id|pte_dir
)paren
op_assign
(paren
id|pte_val
c_func
(paren
op_star
id|pte_dir
)paren
op_amp
id|_CACHEMASK040
)paren
op_or
id|cmode
suffix:semicolon
id|virtaddr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|size
op_sub_assign
id|PAGE_SIZE
suffix:semicolon
)brace
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
)brace
eof
