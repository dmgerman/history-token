multiline_comment|/* &n; * Copyright (C) 2000 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/config.h&quot;
macro_line|#include &quot;linux/types.h&quot;
macro_line|#include &quot;linux/mm.h&quot;
macro_line|#include &quot;linux/fs.h&quot;
macro_line|#include &quot;linux/init.h&quot;
macro_line|#include &quot;linux/bootmem.h&quot;
macro_line|#include &quot;linux/swap.h&quot;
macro_line|#include &quot;linux/slab.h&quot;
macro_line|#include &quot;linux/vmalloc.h&quot;
macro_line|#include &quot;linux/highmem.h&quot;
macro_line|#include &quot;asm/page.h&quot;
macro_line|#include &quot;asm/pgtable.h&quot;
macro_line|#include &quot;asm/pgalloc.h&quot;
macro_line|#include &quot;asm/bitops.h&quot;
macro_line|#include &quot;asm/uaccess.h&quot;
macro_line|#include &quot;asm/tlb.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;mem_user.h&quot;
macro_line|#include &quot;mem.h&quot;
macro_line|#include &quot;kern.h&quot;
macro_line|#include &quot;init.h&quot;
DECL|variable|high_physmem
r_int
r_int
id|high_physmem
suffix:semicolon
DECL|variable|low_physmem
r_int
r_int
id|low_physmem
suffix:semicolon
DECL|variable|vm_start
r_int
r_int
id|vm_start
suffix:semicolon
DECL|variable|vm_end
r_int
r_int
id|vm_end
suffix:semicolon
DECL|variable|swapper_pg_dir
id|pgd_t
id|swapper_pg_dir
(braket
l_int|1024
)braket
suffix:semicolon
DECL|variable|empty_zero_page
r_int
r_int
op_star
id|empty_zero_page
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|empty_bad_page
r_int
r_int
op_star
id|empty_bad_page
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|bad_pmd_string
r_const
r_char
id|bad_pmd_string
(braket
)braket
op_assign
l_string|&quot;Bad pmd in pte_alloc: %08lx&bslash;n&quot;
suffix:semicolon
r_extern
r_char
id|__init_begin
comma
id|__init_end
suffix:semicolon
r_extern
r_int
id|physmem_size
suffix:semicolon
DECL|variable|mmu_gathers
id|mmu_gather_t
id|mmu_gathers
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|kmalloc_ok
r_int
id|kmalloc_ok
op_assign
l_int|0
suffix:semicolon
DECL|macro|NREGIONS
mdefine_line|#define NREGIONS (phys_region_index(0xffffffff) - phys_region_index(0x0))
DECL|variable|regions
r_struct
id|mem_region
op_star
id|regions
(braket
id|NREGIONS
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
id|NREGIONS
op_minus
l_int|1
)braket
op_assign
l_int|NULL
)brace
suffix:semicolon
DECL|macro|REGION_SIZE
mdefine_line|#define REGION_SIZE ((0xffffffff &amp; ~REGION_MASK) + 1)
DECL|variable|brk_end
r_static
r_int
r_int
id|brk_end
suffix:semicolon
DECL|function|map_cb
r_static
r_void
id|map_cb
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
id|map
c_func
(paren
id|brk_end
comma
id|__pa
c_func
(paren
id|brk_end
)paren
comma
id|uml_reserved
op_minus
id|brk_end
comma
l_int|1
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|unmap_physmem
r_void
id|unmap_physmem
c_func
(paren
r_void
)paren
(brace
id|unmap
c_func
(paren
(paren
r_void
op_star
)paren
id|brk_end
comma
id|uml_reserved
op_minus
id|brk_end
)paren
suffix:semicolon
)brace
r_extern
r_char
id|__binary_start
suffix:semicolon
DECL|function|mem_init
r_void
id|mem_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|start
suffix:semicolon
id|max_mapnr
op_assign
id|num_physpages
op_assign
id|max_low_pfn
suffix:semicolon
multiline_comment|/* clear the zero-page */
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|empty_zero_page
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
multiline_comment|/* Map in the area just after the brk now that kmalloc is about&n;&t; * to be turned on.&n;&t; */
id|brk_end
op_assign
(paren
r_int
r_int
)paren
id|ROUND_UP
c_func
(paren
id|sbrk
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|map_cb
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|tracing_cb
c_func
(paren
id|map_cb
comma
l_int|NULL
)paren
suffix:semicolon
id|free_bootmem
c_func
(paren
id|__pa
c_func
(paren
id|brk_end
)paren
comma
id|uml_reserved
op_minus
id|brk_end
)paren
suffix:semicolon
id|uml_reserved
op_assign
id|brk_end
suffix:semicolon
multiline_comment|/* Fill in any hole at the start of the binary */
id|start
op_assign
(paren
r_int
r_int
)paren
op_amp
id|__binary_start
suffix:semicolon
r_if
c_cond
(paren
id|uml_physmem
op_ne
id|start
)paren
(brace
id|map
c_func
(paren
id|uml_physmem
comma
id|__pa
c_func
(paren
id|uml_physmem
)paren
comma
id|start
op_minus
id|uml_physmem
comma
l_int|1
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* this will put all low memory onto the freelists */
id|totalram_pages
op_add_assign
id|free_all_bootmem
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Memory: %luk available&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|nr_free_pages
c_func
(paren
)paren
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
)paren
suffix:semicolon
id|kmalloc_ok
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|paging_init
r_void
id|paging_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|mem_region
op_star
id|region
suffix:semicolon
r_int
r_int
id|zones_size
(braket
id|MAX_NR_ZONES
)braket
comma
id|start
comma
id|end
suffix:semicolon
r_int
id|i
comma
id|index
suffix:semicolon
id|empty_zero_page
op_assign
(paren
r_int
r_int
op_star
)paren
id|alloc_bootmem_low_pages
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
id|empty_bad_page
op_assign
(paren
r_int
r_int
op_star
)paren
id|alloc_bootmem_low_pages
c_func
(paren
id|PAGE_SIZE
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
r_sizeof
(paren
id|zones_size
)paren
op_div
r_sizeof
(paren
id|zones_size
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|zones_size
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|zones_size
(braket
l_int|0
)braket
op_assign
(paren
id|high_physmem
op_rshift
id|PAGE_SHIFT
)paren
op_minus
(paren
id|uml_physmem
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|free_area_init
c_func
(paren
id|zones_size
)paren
suffix:semicolon
id|start
op_assign
id|phys_region_index
c_func
(paren
id|__pa
c_func
(paren
id|uml_physmem
)paren
)paren
suffix:semicolon
id|end
op_assign
id|phys_region_index
c_func
(paren
id|__pa
c_func
(paren
id|high_physmem
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|start
suffix:semicolon
id|i
op_le
id|end
suffix:semicolon
id|i
op_increment
)paren
(brace
id|region
op_assign
id|regions
(braket
id|i
)braket
suffix:semicolon
id|index
op_assign
(paren
id|region-&gt;start
op_minus
id|uml_physmem
)paren
op_div
id|PAGE_SIZE
suffix:semicolon
id|region-&gt;mem_map
op_assign
op_amp
id|mem_map
(braket
id|index
)braket
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
id|start
)paren
(brace
id|free_bootmem
c_func
(paren
id|__pa
c_func
(paren
id|region-&gt;start
)paren
comma
id|region-&gt;len
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|__bad_page
id|pte_t
id|__bad_page
c_func
(paren
r_void
)paren
(brace
id|clear_page
c_func
(paren
id|empty_bad_page
)paren
suffix:semicolon
r_return
id|pte_mkdirty
c_func
(paren
id|mk_pte
c_func
(paren
(paren
r_struct
id|page
op_star
)paren
id|empty_bad_page
comma
id|PAGE_SHARED
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* This can&squot;t do anything because nothing in the kernel image can be freed&n; * since it&squot;s not in kernel physical memory.&n; */
DECL|function|free_initmem
r_void
id|free_initmem
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
DECL|function|free_initrd_mem
r_void
id|free_initrd_mem
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
r_if
c_cond
(paren
id|start
OL
id|end
)paren
id|printk
(paren
l_string|&quot;Freeing initrd memory: %ldk freed&bslash;n&quot;
comma
(paren
id|end
op_minus
id|start
)paren
op_rshift
l_int|10
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|start
OL
id|end
suffix:semicolon
id|start
op_add_assign
id|PAGE_SIZE
)paren
(brace
id|ClearPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|start
)paren
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|virt_to_page
c_func
(paren
id|start
)paren
comma
l_int|1
)paren
suffix:semicolon
id|free_page
c_func
(paren
id|start
)paren
suffix:semicolon
id|totalram_pages
op_increment
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|function|show_mem
r_void
id|show_mem
c_func
(paren
r_void
)paren
(brace
r_int
id|pfn
comma
id|total
op_assign
l_int|0
comma
id|reserved
op_assign
l_int|0
suffix:semicolon
r_int
id|shared
op_assign
l_int|0
comma
id|cached
op_assign
l_int|0
suffix:semicolon
r_int
id|highmem
op_assign
l_int|0
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Mem-info:&bslash;n&quot;
)paren
suffix:semicolon
id|show_free_areas
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Free swap:       %6dkB&bslash;n&quot;
comma
id|nr_swap_pages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
)paren
suffix:semicolon
id|pfn
op_assign
id|max_mapnr
suffix:semicolon
r_while
c_loop
(paren
id|pfn
op_decrement
OG
l_int|0
)paren
(brace
id|page
op_assign
id|pfn_to_page
c_func
(paren
id|pfn
)paren
suffix:semicolon
id|total
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|PageHighMem
c_func
(paren
id|page
)paren
)paren
(brace
id|highmem
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|page
)paren
)paren
(brace
id|reserved
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|PageSwapCache
c_func
(paren
id|page
)paren
)paren
(brace
id|cached
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|page_count
c_func
(paren
id|page
)paren
)paren
(brace
id|shared
op_add_assign
id|page_count
c_func
(paren
id|page
)paren
op_minus
l_int|1
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;%d pages of RAM&bslash;n&quot;
comma
id|total
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d pages of HIGHMEM&bslash;n&quot;
comma
id|highmem
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d reserved pages&bslash;n&quot;
comma
id|reserved
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d pages shared&bslash;n&quot;
comma
id|shared
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d pages swap cached&bslash;n&quot;
comma
id|cached
)paren
suffix:semicolon
)brace
DECL|variable|kmem_top
r_int
r_int
id|kmem_top
op_assign
l_int|0
suffix:semicolon
DECL|function|get_kmem_end
r_int
r_int
id|get_kmem_end
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|kmem_top
op_eq
l_int|0
)paren
(brace
id|kmem_top
op_assign
id|host_task_size
op_minus
id|ABOVE_KMEM
suffix:semicolon
)brace
r_return
id|kmem_top
suffix:semicolon
)brace
DECL|function|set_kmem_end
r_void
id|set_kmem_end
c_func
(paren
r_int
r_int
r_new
)paren
(brace
id|kmem_top
op_assign
r_new
suffix:semicolon
)brace
DECL|function|uml_mem_setup
r_static
r_int
id|__init
id|uml_mem_setup
c_func
(paren
r_char
op_star
id|line
comma
r_int
op_star
id|add
)paren
(brace
r_char
op_star
id|retptr
suffix:semicolon
id|physmem_size
op_assign
id|memparse
c_func
(paren
id|line
comma
op_amp
id|retptr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|__uml_setup
c_func
(paren
l_string|&quot;mem=&quot;
comma
id|uml_mem_setup
comma
l_string|&quot;mem=&lt;Amount of desired ram&gt;&bslash;n&quot;
l_string|&quot;    This controls how much &bslash;&quot;physical&bslash;&quot; memory the kernel allocates&bslash;n&quot;
l_string|&quot;    for the system. The size is specified as a number followed by&bslash;n&quot;
l_string|&quot;    one of &squot;k&squot;, &squot;K&squot;, &squot;m&squot;, &squot;M&squot;, which have the obvious meanings.&bslash;n&quot;
l_string|&quot;    This is not related to the amount of memory in the physical&bslash;n&quot;
l_string|&quot;    machine. It can be more, and the excess, if it&squot;s ever used, will&bslash;n&quot;
l_string|&quot;    just be swapped out.&bslash;n        Example: mem=64M&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
DECL|function|arch_validate
r_struct
id|page
op_star
id|arch_validate
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|mask
comma
r_int
id|order
)paren
(brace
r_int
r_int
id|addr
comma
id|zero
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|again
suffix:colon
r_if
c_cond
(paren
id|page
op_eq
l_int|NULL
)paren
(brace
r_return
id|page
suffix:semicolon
)brace
id|addr
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
l_int|1
op_lshift
id|order
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|current-&gt;thread.fault_addr
op_assign
(paren
r_void
op_star
)paren
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|__do_copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|addr
comma
op_amp
id|zero
comma
r_sizeof
(paren
id|zero
)paren
comma
op_amp
id|current-&gt;thread.fault_addr
comma
op_amp
id|current-&gt;thread.fault_catcher
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|mask
op_amp
id|__GFP_WAIT
)paren
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
)brace
id|addr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
(paren
l_int|1
op_lshift
id|order
)paren
)paren
(brace
r_return
id|page
suffix:semicolon
)brace
id|page
op_assign
id|_alloc_pages
c_func
(paren
id|mask
comma
id|order
)paren
suffix:semicolon
r_goto
id|again
suffix:semicolon
)brace
DECL|variable|vm_reserved
r_static
r_struct
id|list_head
id|vm_reserved
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|vm_reserved
)paren
suffix:semicolon
DECL|variable|head
r_static
r_struct
id|vm_reserved
id|head
op_assign
(brace
id|list
suffix:colon
id|LIST_HEAD_INIT
c_func
(paren
id|head.list
)paren
comma
id|start
suffix:colon
l_int|0
comma
id|end
suffix:colon
l_int|0xffffffff
)brace
suffix:semicolon
DECL|variable|tail
r_static
r_struct
id|vm_reserved
id|tail
op_assign
(brace
id|list
suffix:colon
id|LIST_HEAD_INIT
c_func
(paren
id|tail.list
)paren
comma
id|start
suffix:colon
l_int|0
comma
id|end
suffix:colon
l_int|0xffffffff
)brace
suffix:semicolon
DECL|function|set_usable_vm
r_void
id|set_usable_vm
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
id|list_add
c_func
(paren
op_amp
id|head.list
comma
op_amp
id|vm_reserved
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|tail.list
comma
op_amp
id|head.list
)paren
suffix:semicolon
id|head.end
op_assign
id|start
suffix:semicolon
id|tail.start
op_assign
id|end
suffix:semicolon
)brace
DECL|function|reserve_vm
r_int
id|reserve_vm
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_void
op_star
id|e
)paren
(brace
r_struct
id|vm_reserved
op_star
id|entry
op_assign
id|e
comma
op_star
id|reserved
comma
op_star
id|prev
suffix:semicolon
r_struct
id|list_head
op_star
id|ele
suffix:semicolon
(def_block
id|list_for_each
c_func
(paren
id|ele
comma
op_amp
id|vm_reserved
)paren
(brace
id|reserved
op_assign
id|list_entry
c_func
(paren
id|ele
comma
r_struct
id|vm_reserved
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reserved-&gt;start
op_ge
id|end
)paren
(brace
r_goto
id|found
suffix:semicolon
)brace
)brace
)def_block
id|panic
c_func
(paren
l_string|&quot;Reserved vm out of range&quot;
)paren
suffix:semicolon
id|found
suffix:colon
id|prev
op_assign
id|list_entry
c_func
(paren
id|ele-&gt;prev
comma
r_struct
id|vm_reserved
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prev-&gt;end
OG
id|start
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Can&squot;t reserve vm&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|entry
op_eq
l_int|NULL
)paren
(brace
id|entry
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|entry
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|entry
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;reserve_vm : Failed to allocate entry&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
op_star
id|entry
op_assign
(paren
(paren
r_struct
id|vm_reserved
)paren
(brace
id|list
suffix:colon
id|LIST_HEAD_INIT
c_func
(paren
id|entry-&gt;list
)paren
comma
id|start
suffix:colon
id|start
comma
id|end
suffix:colon
id|end
)brace
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|entry-&gt;list
comma
op_amp
id|prev-&gt;list
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_vm
r_int
r_int
id|get_vm
c_func
(paren
r_int
r_int
id|len
)paren
(brace
r_struct
id|vm_reserved
op_star
id|this
comma
op_star
id|next
suffix:semicolon
r_struct
id|list_head
op_star
id|ele
suffix:semicolon
r_int
r_int
id|start
suffix:semicolon
r_int
id|err
suffix:semicolon
(def_block
id|list_for_each
c_func
(paren
id|ele
comma
op_amp
id|vm_reserved
)paren
(brace
id|this
op_assign
id|list_entry
c_func
(paren
id|ele
comma
r_struct
id|vm_reserved
comma
id|list
)paren
suffix:semicolon
id|next
op_assign
id|list_entry
c_func
(paren
id|ele-&gt;next
comma
r_struct
id|vm_reserved
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|this-&gt;start
OL
id|next-&gt;start
)paren
op_logical_and
(paren
id|this-&gt;end
op_plus
id|len
op_plus
id|PAGE_SIZE
op_le
id|next-&gt;start
)paren
)paren
(brace
r_goto
id|found
suffix:semicolon
)brace
)brace
)def_block
r_return
l_int|0
suffix:semicolon
id|found
suffix:colon
id|start
op_assign
(paren
r_int
r_int
)paren
id|ROUND_UP
c_func
(paren
id|this-&gt;end
)paren
op_plus
id|PAGE_SIZE
suffix:semicolon
id|err
op_assign
id|reserve_vm
c_func
(paren
id|start
comma
id|start
op_plus
id|len
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|start
suffix:semicolon
)brace
DECL|function|nregions
r_int
id|nregions
c_func
(paren
r_void
)paren
(brace
r_return
id|NREGIONS
suffix:semicolon
)brace
DECL|function|init_maps
r_int
id|init_maps
c_func
(paren
r_struct
id|mem_region
op_star
id|region
)paren
(brace
r_struct
id|page
op_star
id|p
comma
op_star
id|map
suffix:semicolon
r_int
id|i
comma
id|n
suffix:semicolon
r_if
c_cond
(paren
id|region
op_eq
op_amp
id|physmem_region
)paren
(brace
id|region-&gt;mem_map
op_assign
id|mem_map
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|region-&gt;mem_map
op_ne
l_int|NULL
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|n
op_assign
id|region-&gt;len
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|map
op_assign
id|kmalloc
c_func
(paren
id|n
op_star
r_sizeof
(paren
r_struct
id|page
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map
op_eq
l_int|NULL
)paren
(brace
id|map
op_assign
id|vmalloc
c_func
(paren
id|n
op_star
r_sizeof
(paren
r_struct
id|page
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|map
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
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
id|n
suffix:semicolon
id|i
op_increment
)paren
(brace
id|p
op_assign
op_amp
id|map
(braket
id|i
)braket
suffix:semicolon
id|set_page_count
c_func
(paren
id|p
comma
l_int|0
)paren
suffix:semicolon
id|SetPageReserved
c_func
(paren
id|p
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|p-&gt;list
)paren
suffix:semicolon
)brace
id|region-&gt;mem_map
op_assign
id|map
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|setup_range
r_void
id|setup_range
c_func
(paren
r_int
id|fd
comma
r_char
op_star
id|driver
comma
r_int
r_int
id|start
comma
r_int
r_int
id|len
comma
r_struct
id|mem_region
op_star
id|region
comma
r_void
op_star
id|reserved
)paren
(brace
r_int
id|i
comma
id|incr
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
id|NREGIONS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|regions
(braket
id|i
)braket
op_eq
l_int|NULL
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|i
op_eq
id|NREGIONS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;setup_range : no free regions&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|setup_one_range
c_func
(paren
id|i
comma
id|fd
comma
id|driver
comma
id|start
comma
id|len
comma
id|region
)paren
suffix:semicolon
id|region
op_assign
id|regions
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|setup_region
c_func
(paren
id|region
comma
id|reserved
)paren
)paren
(brace
id|kfree
c_func
(paren
id|region
)paren
suffix:semicolon
id|regions
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
suffix:semicolon
)brace
id|incr
op_assign
id|min
c_func
(paren
id|len
comma
(paren
r_int
r_int
)paren
id|REGION_SIZE
)paren
suffix:semicolon
id|start
op_add_assign
id|incr
suffix:semicolon
id|len
op_sub_assign
id|incr
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
suffix:semicolon
)brace
)brace
DECL|struct|iomem
r_struct
id|iomem
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|fd
r_int
id|fd
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|iomem_regions
r_struct
id|iomem
id|iomem_regions
(braket
id|NREGIONS
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
id|NREGIONS
op_minus
l_int|1
)braket
op_assign
(brace
id|name
suffix:colon
l_int|NULL
comma
id|fd
suffix:colon
op_minus
l_int|1
comma
id|size
suffix:colon
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|num_iomem_regions
r_int
id|num_iomem_regions
op_assign
l_int|0
suffix:semicolon
DECL|function|add_iomem
r_void
id|add_iomem
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|fd
comma
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|num_iomem_regions
op_eq
r_sizeof
(paren
id|iomem_regions
)paren
op_div
r_sizeof
(paren
id|iomem_regions
(braket
l_int|0
)braket
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
id|size
op_assign
(paren
id|size
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_amp
id|PAGE_MASK
suffix:semicolon
id|iomem_regions
(braket
id|num_iomem_regions
op_increment
)braket
op_assign
(paren
(paren
r_struct
id|iomem
)paren
(brace
id|name
suffix:colon
id|name
comma
id|fd
suffix:colon
id|fd
comma
id|size
suffix:colon
id|size
)brace
)paren
suffix:semicolon
)brace
DECL|function|setup_iomem
r_int
id|setup_iomem
c_func
(paren
r_void
)paren
(brace
r_struct
id|iomem
op_star
id|iomem
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
id|num_iomem_regions
suffix:semicolon
id|i
op_increment
)paren
(brace
id|iomem
op_assign
op_amp
id|iomem_regions
(braket
id|i
)braket
suffix:semicolon
id|setup_range
c_func
(paren
id|iomem-&gt;fd
comma
id|iomem-&gt;name
comma
op_minus
l_int|1
comma
id|iomem-&gt;size
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|setup_iomem
id|__initcall
c_func
(paren
id|setup_iomem
)paren
suffix:semicolon
DECL|macro|PFN_UP
mdefine_line|#define PFN_UP(x)&t;(((x) + PAGE_SIZE-1) &gt;&gt; PAGE_SHIFT)
DECL|macro|PFN_DOWN
mdefine_line|#define PFN_DOWN(x)&t;((x) &gt;&gt; PAGE_SHIFT)
DECL|variable|physmem_region
r_static
r_struct
id|mem_region
id|physmem_region
suffix:semicolon
DECL|variable|physmem_reserved
r_static
r_struct
id|vm_reserved
id|physmem_reserved
suffix:semicolon
DECL|function|setup_physmem
r_void
id|setup_physmem
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|reserve_end
comma
r_int
r_int
id|len
)paren
(brace
r_struct
id|mem_region
op_star
id|region
op_assign
op_amp
id|physmem_region
suffix:semicolon
r_struct
id|vm_reserved
op_star
id|reserved
op_assign
op_amp
id|physmem_reserved
suffix:semicolon
r_int
r_int
id|cur
suffix:semicolon
r_int
id|do_free
op_assign
l_int|1
comma
id|bootmap_size
suffix:semicolon
r_do
(brace
id|cur
op_assign
id|min
c_func
(paren
id|len
comma
(paren
r_int
r_int
)paren
id|REGION_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|region
op_eq
l_int|NULL
)paren
(brace
id|region
op_assign
id|alloc_bootmem_low_pages
c_func
(paren
r_sizeof
(paren
op_star
id|region
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|reserved
op_eq
l_int|NULL
)paren
(brace
id|reserved
op_assign
id|alloc_bootmem_low_pages
c_func
(paren
r_sizeof
(paren
op_star
id|reserved
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|region
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|reserved
op_eq
l_int|NULL
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Couldn&squot;t allocate physmem region or vm &quot;
l_string|&quot;reservation&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|setup_range
c_func
(paren
op_minus
l_int|1
comma
l_int|NULL
comma
id|start
comma
id|cur
comma
id|region
comma
id|reserved
)paren
suffix:semicolon
r_if
c_cond
(paren
id|do_free
)paren
(brace
r_int
r_int
id|reserve
op_assign
id|reserve_end
op_minus
id|start
suffix:semicolon
r_int
id|pfn
op_assign
id|PFN_UP
c_func
(paren
id|__pa
c_func
(paren
id|reserve_end
)paren
)paren
suffix:semicolon
r_int
id|delta
op_assign
(paren
id|len
op_minus
id|reserve
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|bootmap_size
op_assign
id|init_bootmem
c_func
(paren
id|pfn
comma
id|pfn
op_plus
id|delta
)paren
suffix:semicolon
id|free_bootmem
c_func
(paren
id|__pa
c_func
(paren
id|reserve_end
)paren
op_plus
id|bootmap_size
comma
id|cur
op_minus
id|bootmap_size
op_minus
id|reserve
)paren
suffix:semicolon
id|do_free
op_assign
l_int|0
suffix:semicolon
)brace
id|start
op_add_assign
id|cur
suffix:semicolon
id|len
op_sub_assign
id|cur
suffix:semicolon
id|region
op_assign
l_int|NULL
suffix:semicolon
id|reserved
op_assign
l_int|NULL
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
suffix:semicolon
)brace
)brace
DECL|function|phys_region
r_struct
id|mem_region
op_star
id|phys_region
c_func
(paren
r_int
r_int
id|phys
)paren
(brace
r_int
r_int
id|n
op_assign
id|phys_region_index
c_func
(paren
id|phys
)paren
suffix:semicolon
r_if
c_cond
(paren
id|regions
(braket
id|n
)braket
op_eq
l_int|NULL
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Physical address in uninitialized region&quot;
)paren
suffix:semicolon
)brace
r_return
id|regions
(braket
id|n
)braket
suffix:semicolon
)brace
DECL|function|phys_offset
r_int
r_int
id|phys_offset
c_func
(paren
r_int
r_int
id|phys
)paren
(brace
r_return
id|phys_addr
c_func
(paren
id|phys
)paren
suffix:semicolon
)brace
DECL|function|phys_mem_map
r_struct
id|page
op_star
id|phys_mem_map
c_func
(paren
r_int
r_int
id|phys
)paren
(brace
r_return
(paren
r_struct
id|page
op_star
)paren
id|phys_region
c_func
(paren
id|phys
)paren
op_member_access_from_pointer
id|mem_map
suffix:semicolon
)brace
DECL|function|pte_mem_map
r_struct
id|page
op_star
id|pte_mem_map
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|phys_mem_map
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
)paren
suffix:semicolon
)brace
DECL|function|page_region
r_struct
id|mem_region
op_star
id|page_region
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
op_star
id|index_out
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|mem_region
op_star
id|region
suffix:semicolon
r_struct
id|page
op_star
id|map
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
id|NREGIONS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|region
op_assign
id|regions
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|region
op_eq
l_int|NULL
)paren
(brace
r_continue
suffix:semicolon
)brace
id|map
op_assign
id|region-&gt;mem_map
suffix:semicolon
r_if
c_cond
(paren
(paren
id|page
op_ge
id|map
)paren
op_logical_and
(paren
id|page
OL
op_amp
id|map
(braket
id|region-&gt;len
op_rshift
id|PAGE_SHIFT
)braket
)paren
)paren
(brace
r_if
c_cond
(paren
id|index_out
op_ne
l_int|NULL
)paren
(brace
op_star
id|index_out
op_assign
id|i
suffix:semicolon
)brace
r_return
id|region
suffix:semicolon
)brace
)brace
id|panic
c_func
(paren
l_string|&quot;No region found for page&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|page_mem_map
r_struct
id|page
op_star
id|page_mem_map
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_return
(paren
r_struct
id|page
op_star
)paren
id|page_region
c_func
(paren
id|page
comma
l_int|NULL
)paren
op_member_access_from_pointer
id|mem_map
suffix:semicolon
)brace
DECL|function|region_pa
r_extern
r_int
r_int
id|region_pa
c_func
(paren
r_void
op_star
id|virt
)paren
(brace
r_struct
id|mem_region
op_star
id|region
suffix:semicolon
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|virt
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
id|NREGIONS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|region
op_assign
id|regions
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|region
op_eq
l_int|NULL
)paren
(brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|region-&gt;start
op_le
id|addr
)paren
op_logical_and
(paren
id|addr
op_le
id|region-&gt;start
op_plus
id|region-&gt;len
)paren
)paren
(brace
r_return
id|mk_phys
c_func
(paren
id|addr
op_minus
id|region-&gt;start
comma
id|i
)paren
suffix:semicolon
)brace
)brace
id|panic
c_func
(paren
l_string|&quot;region_pa : no region for virtual address&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|region_va
r_extern
r_void
op_star
id|region_va
c_func
(paren
r_int
r_int
id|phys
)paren
(brace
r_return
(paren
r_void
op_star
)paren
(paren
id|phys_region
c_func
(paren
id|phys
)paren
op_member_access_from_pointer
id|start
op_plus
id|phys_addr
c_func
(paren
id|phys
)paren
)paren
suffix:semicolon
)brace
DECL|function|page_to_phys
r_int
r_int
id|page_to_phys
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_int
id|n
suffix:semicolon
r_struct
id|mem_region
op_star
id|region
op_assign
id|page_region
c_func
(paren
id|page
comma
op_amp
id|n
)paren
suffix:semicolon
r_struct
id|page
op_star
id|map
op_assign
id|region-&gt;mem_map
suffix:semicolon
r_return
id|mk_phys
c_func
(paren
(paren
id|page
op_minus
id|map
)paren
op_lshift
id|PAGE_SHIFT
comma
id|n
)paren
suffix:semicolon
)brace
DECL|function|phys_to_page
r_struct
id|page
op_star
id|phys_to_page
c_func
(paren
r_int
r_int
id|phys
)paren
(brace
r_struct
id|page
op_star
id|mem_map
suffix:semicolon
id|mem_map
op_assign
id|phys_mem_map
c_func
(paren
id|phys
)paren
suffix:semicolon
r_return
id|mem_map
op_plus
(paren
id|phys_offset
c_func
(paren
id|phys
)paren
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
)brace
DECL|function|setup_mem_maps
r_int
id|setup_mem_maps
c_func
(paren
r_void
)paren
(brace
r_struct
id|mem_region
op_star
id|region
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
id|NREGIONS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|region
op_assign
id|regions
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|region
op_ne
l_int|NULL
)paren
op_logical_and
(paren
id|region-&gt;fd
OG
l_int|0
)paren
)paren
(brace
id|init_maps
c_func
(paren
id|region
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|setup_mem_maps
id|__initcall
c_func
(paren
id|setup_mem_maps
)paren
suffix:semicolon
multiline_comment|/*&n; * Allocate and free page tables.&n; */
DECL|function|pgd_alloc
id|pgd_t
op_star
id|pgd_alloc
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|pgd_t
op_star
id|pgd
op_assign
(paren
id|pgd_t
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd
)paren
(brace
id|memset
c_func
(paren
id|pgd
comma
l_int|0
comma
id|USER_PTRS_PER_PGD
op_star
r_sizeof
(paren
id|pgd_t
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|pgd
op_plus
id|USER_PTRS_PER_PGD
comma
id|swapper_pg_dir
op_plus
id|USER_PTRS_PER_PGD
comma
(paren
id|PTRS_PER_PGD
op_minus
id|USER_PTRS_PER_PGD
)paren
op_star
r_sizeof
(paren
id|pgd_t
)paren
)paren
suffix:semicolon
)brace
r_return
id|pgd
suffix:semicolon
)brace
DECL|function|pgd_free
r_void
id|pgd_free
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|pgd
)paren
suffix:semicolon
)brace
DECL|function|pte_alloc_one_kernel
id|pte_t
op_star
id|pte_alloc_one_kernel
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
(brace
r_int
id|count
op_assign
l_int|0
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
r_do
(brace
id|pte
op_assign
(paren
id|pte_t
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte
)paren
id|clear_page
c_func
(paren
id|pte
)paren
suffix:semicolon
r_else
(brace
id|current-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|HZ
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_logical_neg
id|pte
op_logical_and
(paren
id|count
op_increment
OL
l_int|10
)paren
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_alloc_one
r_struct
id|page
op_star
id|pte_alloc_one
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
(brace
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_struct
id|page
op_star
id|pte
suffix:semicolon
r_do
(brace
id|pte
op_assign
id|alloc_pages
c_func
(paren
id|GFP_KERNEL
op_or
id|__GFP_HIGHMEM
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte
)paren
id|clear_highpage
c_func
(paren
id|pte
)paren
suffix:semicolon
r_else
(brace
id|current-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|HZ
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_logical_neg
id|pte
op_logical_and
(paren
id|count
op_increment
OL
l_int|10
)paren
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof