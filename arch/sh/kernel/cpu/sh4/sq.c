multiline_comment|/*&n; * arch/sh/kernel/cpu/sq.c&n; *&n; * General management API for SH-4 integrated Store Queues&n; *&n; * Copyright (C) 2001, 2002, 2003, 2004  Paul Mundt&n; * Copyright (C) 2001, 2002  M. R. Brown&n; *&n; * Some of this code has been adopted directly from the old arch/sh/mm/sq.c&n; * hack that was part of the LinuxDC project. For all intents and purposes,&n; * this is a completely new interface that really doesn&squot;t have much in common&n; * with the old zone-based approach at all. In fact, it&squot;s only listed here for&n; * general completeness.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/cpu/sq.h&gt;
r_static
id|LIST_HEAD
c_func
(paren
id|sq_mapping_list
)paren
suffix:semicolon
DECL|variable|sq_mapping_lock
r_static
id|spinlock_t
id|sq_mapping_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_extern
r_struct
id|vm_struct
op_star
id|__get_vm_area
c_func
(paren
r_int
r_int
id|size
comma
r_int
r_int
id|flags
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
multiline_comment|/**&n; * sq_flush - Flush (prefetch) the store queue cache&n; *&n; * @addr: the store queue address to flush&n; *&n; * Executes a prefetch instruction on the specified store queue cache,&n; * so that the cached data is written to physical memory.&n; */
DECL|function|sq_flush
r_inline
r_void
id|sq_flush
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;pref @%0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * sq_flush_range - Flush (prefetch) a specific SQ range&n; *&n; * @start: the store queue address to start flushing from&n; * @len: the length to flush&n; *&n; * Flushes the store queue cache from @start to @start + @len in a&n; * linear fashion.&n; */
DECL|function|sq_flush_range
r_void
id|sq_flush_range
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|len
)paren
(brace
r_volatile
r_int
r_int
op_star
id|sq
op_assign
(paren
r_int
r_int
op_star
)paren
id|start
suffix:semicolon
r_int
r_int
id|dummy
suffix:semicolon
multiline_comment|/* Flush the queues */
r_for
c_loop
(paren
id|len
op_rshift_assign
l_int|5
suffix:semicolon
id|len
op_decrement
suffix:semicolon
id|sq
op_add_assign
l_int|8
)paren
id|sq_flush
c_func
(paren
(paren
r_void
op_star
)paren
id|sq
)paren
suffix:semicolon
multiline_comment|/* Wait for completion */
id|dummy
op_assign
id|ctrl_inl
c_func
(paren
id|P4SEG_STORE_QUE
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
l_int|0
comma
id|P4SEG_STORE_QUE
op_plus
l_int|0
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
l_int|0
comma
id|P4SEG_STORE_QUE
op_plus
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|__sq_alloc_mapping
r_static
r_struct
id|sq_mapping
op_star
id|__sq_alloc_mapping
c_func
(paren
r_int
r_int
id|virt
comma
r_int
r_int
id|phys
comma
r_int
r_int
id|size
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|sq_mapping
op_star
id|map
suffix:semicolon
r_if
c_cond
(paren
id|virt
op_plus
id|size
OG
id|SQ_ADDRMAX
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOSPC
)paren
suffix:semicolon
id|map
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sq_mapping
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|map
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|map-&gt;list
)paren
suffix:semicolon
id|map-&gt;sq_addr
op_assign
id|virt
suffix:semicolon
id|map-&gt;addr
op_assign
id|phys
suffix:semicolon
id|map-&gt;size
op_assign
id|size
op_plus
l_int|1
suffix:semicolon
id|map-&gt;name
op_assign
id|name
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|map-&gt;list
comma
op_amp
id|sq_mapping_list
)paren
suffix:semicolon
r_return
id|map
suffix:semicolon
)brace
DECL|function|__sq_get_next_addr
r_static
r_int
r_int
id|__sq_get_next_addr
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|sq_mapping_list
)paren
)paren
(brace
r_struct
id|list_head
op_star
id|pos
comma
op_star
id|tmp
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Read one off the list head, as it will have the highest&n;&t;&t; * mapped allocation. Set the next one up right above it.&n;&t;&t; *&n;&t;&t; * This is somewhat sub-optimal, as we don&squot;t look at&n;&t;&t; * gaps between allocations or anything lower then the&n;&t;&t; * highest-level allocation.&n;&t;&t; *&n;&t;&t; * However, in the interest of performance and the general&n;&t;&t; * lack of desire to do constant list rebalancing, we don&squot;t&n;&t;&t; * worry about it.&n;&t;&t; */
id|list_for_each_safe
c_func
(paren
id|pos
comma
id|tmp
comma
op_amp
id|sq_mapping_list
)paren
(brace
r_struct
id|sq_mapping
op_star
id|entry
suffix:semicolon
id|entry
op_assign
id|list_entry
c_func
(paren
id|pos
comma
id|typeof
c_func
(paren
op_star
id|entry
)paren
comma
id|list
)paren
suffix:semicolon
r_return
id|entry-&gt;sq_addr
op_plus
id|entry-&gt;size
suffix:semicolon
)brace
)brace
r_return
id|P4SEG_STORE_QUE
suffix:semicolon
)brace
multiline_comment|/**&n; * __sq_remap - Perform a translation from the SQ to a phys addr&n; *&n; * @phys: Physical address to map store queues too.&n; * @virt: Associated store queue address.&n; *&n; * Maps the store queue address @virt to the physical address @phys.&n; */
DECL|function|__sq_remap
r_static
r_struct
id|sq_mapping
op_star
id|__sq_remap
c_func
(paren
r_struct
id|sq_mapping
op_star
id|map
)paren
(brace
r_int
r_int
id|flags
comma
id|pteh
comma
id|ptel
suffix:semicolon
r_struct
id|vm_struct
op_star
id|vma
suffix:semicolon
id|pgprot_t
id|pgprot
suffix:semicolon
multiline_comment|/*&n;&t; * Without an MMU (or with it turned off), this is much more&n;&t; * straightforward, as we can just load up each queue&squot;s QACR with&n;&t; * the physical address appropriately masked.&n;&t; */
id|ctrl_outl
c_func
(paren
(paren
(paren
id|map-&gt;addr
op_rshift
l_int|26
)paren
op_lshift
l_int|2
)paren
op_amp
l_int|0x1c
comma
id|SQ_QACR0
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
(paren
(paren
id|map-&gt;addr
op_rshift
l_int|26
)paren
op_lshift
l_int|2
)paren
op_amp
l_int|0x1c
comma
id|SQ_QACR1
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MMU
multiline_comment|/*&n;&t; * With an MMU on the other hand, things are slightly more involved.&n;&t; * Namely, we have to have a direct mapping between the SQ addr and&n;&t; * the associated physical address in the UTLB by way of setting up&n;&t; * a virt&lt;-&gt;phys translation by hand. We do this by simply specifying&n;&t; * the SQ addr in UTLB.VPN and the associated physical address in&n;&t; * UTLB.PPN.&n;&t; *&n;&t; * Notably, even though this is a special case translation, and some&n;&t; * of the configuration bits are meaningless, we&squot;re still required&n;&t; * to have a valid ASID context in PTEH.&n;&t; *&n;&t; * We could also probably get by without explicitly setting PTEA, but&n;&t; * we do it here just for good measure.&n;&t; */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sq_mapping_lock
comma
id|flags
)paren
suffix:semicolon
id|pteh
op_assign
id|map-&gt;sq_addr
suffix:semicolon
id|ctrl_outl
c_func
(paren
(paren
id|pteh
op_amp
id|MMU_VPN_MASK
)paren
op_or
id|get_asid
c_func
(paren
)paren
comma
id|MMU_PTEH
)paren
suffix:semicolon
id|ptel
op_assign
id|map-&gt;addr
op_amp
id|PAGE_MASK
suffix:semicolon
id|ctrl_outl
c_func
(paren
(paren
(paren
id|ptel
op_rshift
l_int|28
)paren
op_amp
l_int|0xe
)paren
op_or
(paren
id|ptel
op_amp
l_int|0x1
)paren
comma
id|MMU_PTEA
)paren
suffix:semicolon
id|pgprot
op_assign
id|pgprot_noncached
c_func
(paren
id|PAGE_KERNEL
)paren
suffix:semicolon
id|ptel
op_and_assign
id|_PAGE_FLAGS_HARDWARE_MASK
suffix:semicolon
id|ptel
op_or_assign
id|pgprot_val
c_func
(paren
id|pgprot
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|ptel
comma
id|MMU_PTEL
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;ldtlb&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sq_mapping_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Next, we need to map ourselves in the kernel page table, so that&n;&t; * future accesses after a TLB flush will be handled when we take a&n;&t; * page fault.&n;&t; *&n;&t; * Theoretically we could just do this directly and not worry about&n;&t; * setting up the translation by hand ahead of time, but for the&n;&t; * cases where we want a one-shot SQ mapping followed by a quick&n;&t; * writeout before we hit the TLB flush, we do it anyways. This way&n;&t; * we at least save ourselves the initial page fault overhead.&n;&t; */
id|vma
op_assign
id|__get_vm_area
c_func
(paren
id|map-&gt;size
comma
id|VM_ALLOC
comma
id|map-&gt;sq_addr
comma
id|SQ_ADDRMAX
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|vma-&gt;phys_addr
op_assign
id|map-&gt;addr
suffix:semicolon
r_if
c_cond
(paren
id|remap_area_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|vma-&gt;addr
comma
id|vma-&gt;phys_addr
comma
id|map-&gt;size
comma
id|pgprot_val
c_func
(paren
id|pgprot
)paren
)paren
)paren
(brace
id|vunmap
c_func
(paren
id|vma-&gt;addr
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_MMU */
r_return
id|map
suffix:semicolon
)brace
multiline_comment|/**&n; * sq_remap - Map a physical address through the Store Queues&n; *&n; * @phys: Physical address of mapping.&n; * @size: Length of mapping.&n; * @name: User invoking mapping.&n; *&n; * Remaps the physical address @phys through the next available store queue&n; * address of @size length. @name is logged at boot time as well as through&n; * the procfs interface.&n; *&n; * A pre-allocated and filled sq_mapping pointer is returned, and must be&n; * cleaned up with a call to sq_unmap() when the user is done with the&n; * mapping.&n; */
DECL|function|sq_remap
r_struct
id|sq_mapping
op_star
id|sq_remap
c_func
(paren
r_int
r_int
id|phys
comma
r_int
r_int
id|size
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|sq_mapping
op_star
id|map
suffix:semicolon
r_int
r_int
id|virt
comma
id|end
suffix:semicolon
r_int
r_int
id|psz
suffix:semicolon
multiline_comment|/* Don&squot;t allow wraparound or zero size */
id|end
op_assign
id|phys
op_plus
id|size
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
op_logical_or
id|end
OL
id|phys
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* Don&squot;t allow anyone to remap normal memory.. */
r_if
c_cond
(paren
id|phys
OL
id|virt_to_phys
c_func
(paren
id|high_memory
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|phys
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|end
op_plus
l_int|1
)paren
op_minus
id|phys
suffix:semicolon
id|virt
op_assign
id|__sq_get_next_addr
c_func
(paren
)paren
suffix:semicolon
id|psz
op_assign
(paren
id|size
op_plus
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_div
id|PAGE_SIZE
suffix:semicolon
id|map
op_assign
id|__sq_alloc_mapping
c_func
(paren
id|virt
comma
id|phys
comma
id|size
comma
id|name
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sqremap: %15s  [%4d page%s]  va 0x%08lx   pa 0x%08lx&bslash;n&quot;
comma
id|map-&gt;name
ques
c_cond
id|map-&gt;name
suffix:colon
l_string|&quot;???&quot;
comma
id|psz
comma
id|psz
op_eq
l_int|1
ques
c_cond
l_string|&quot; &quot;
suffix:colon
l_string|&quot;s&quot;
comma
id|map-&gt;sq_addr
comma
id|map-&gt;addr
)paren
suffix:semicolon
r_return
id|__sq_remap
c_func
(paren
id|map
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * sq_unmap - Unmap a Store Queue allocation&n; *&n; * @map: Pre-allocated Store Queue mapping.&n; *&n; * Unmaps the store queue allocation @map that was previously created by&n; * sq_remap(). Also frees up the pte that was previously inserted into&n; * the kernel page table and discards the UTLB translation.&n; */
DECL|function|sq_unmap
r_void
id|sq_unmap
c_func
(paren
r_struct
id|sq_mapping
op_star
id|map
)paren
(brace
r_if
c_cond
(paren
id|map-&gt;sq_addr
OG
(paren
r_int
r_int
)paren
id|high_memory
)paren
id|vfree
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|map-&gt;sq_addr
op_amp
id|PAGE_MASK
)paren
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|map-&gt;list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|map
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * sq_clear - Clear a store queue range&n; *&n; * @addr: Address to start clearing from.&n; * @len: Length to clear.&n; *&n; * A quick zero-fill implementation for clearing out memory that has been&n; * remapped through the store queues.&n; */
DECL|function|sq_clear
r_void
id|sq_clear
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|len
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Clear out both queues linearly */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ctrl_outl
c_func
(paren
l_int|0
comma
id|addr
op_plus
id|i
op_plus
l_int|0
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
l_int|0
comma
id|addr
op_plus
id|i
op_plus
l_int|8
)paren
suffix:semicolon
)brace
id|sq_flush_range
c_func
(paren
id|addr
comma
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * sq_vma_unmap - Unmap a VMA range&n; *&n; * @area: VMA containing range.&n; * @addr: Start of range.&n; * @len: Length of range.&n; *&n; * Searches the sq_mapping_list for a mapping matching the sq addr @addr,&n; * and subsequently frees up the entry. Further cleanup is done by generic&n; * code.&n; */
DECL|function|sq_vma_unmap
r_static
r_void
id|sq_vma_unmap
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|area
comma
r_int
r_int
id|addr
comma
r_int
id|len
)paren
(brace
r_struct
id|list_head
op_star
id|pos
comma
op_star
id|tmp
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|pos
comma
id|tmp
comma
op_amp
id|sq_mapping_list
)paren
(brace
r_struct
id|sq_mapping
op_star
id|entry
suffix:semicolon
id|entry
op_assign
id|list_entry
c_func
(paren
id|pos
comma
id|typeof
c_func
(paren
op_star
id|entry
)paren
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;sq_addr
op_eq
id|addr
)paren
(brace
multiline_comment|/* &n;&t;&t;&t; * We could probably get away without doing the tlb flush&n;&t;&t;&t; * here, as generic code should take care of most of this&n;&t;&t;&t; * when unmapping the rest of the VMA range for us. Leave&n;&t;&t;&t; * it in for added sanity for the time being..&n;&t;&t;&t; */
id|__flush_tlb_page
c_func
(paren
id|get_asid
c_func
(paren
)paren
comma
id|entry-&gt;sq_addr
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|entry-&gt;list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|entry
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/**&n; * sq_vma_sync - Sync a VMA range&n; *&n; * @area: VMA containing range.&n; * @start: Start of range.&n; * @len: Length of range.&n; * @flags: Additional flags.&n; *&n; * Synchronizes an sq mapped range by flushing the store queue cache for&n; * the duration of the mapping.&n; *&n; * Used internally for user mappings, which must use msync() to prefetch&n; * the store queue cache.&n; */
DECL|function|sq_vma_sync
r_static
r_int
id|sq_vma_sync
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|area
comma
r_int
r_int
id|start
comma
r_int
id|len
comma
r_int
r_int
id|flags
)paren
(brace
id|sq_flush_range
c_func
(paren
id|start
comma
id|len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sq_vma_ops
r_static
r_struct
id|vm_operations_struct
id|sq_vma_ops
op_assign
(brace
dot
id|unmap
op_assign
id|sq_vma_unmap
comma
dot
id|sync
op_assign
id|sq_vma_sync
comma
)brace
suffix:semicolon
multiline_comment|/**&n; * sq_mmap - mmap() for /dev/cpu/sq&n; *&n; * @file: unused.&n; * @vma: VMA to remap.&n; *&n; * Remap the specified vma @vma through the store queues, and setup associated&n; * information for the new mapping. Also build up the page tables for the new&n; * area.&n; */
DECL|function|sq_mmap
r_static
r_int
id|sq_mmap
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_int
r_int
id|offset
op_assign
id|vma-&gt;vm_pgoff
op_lshift
id|PAGE_SHIFT
suffix:semicolon
r_int
r_int
id|size
op_assign
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
suffix:semicolon
r_struct
id|sq_mapping
op_star
id|map
suffix:semicolon
multiline_comment|/* &n;&t; * We&squot;re not interested in any arbitrary virtual address that has&n;&t; * been stuck in the VMA, as we already know what addresses we&n;&t; * want. Save off the size, and reposition the VMA to begin at&n;&t; * the next available sq address.&n;&t; */
id|vma-&gt;vm_start
op_assign
id|__sq_get_next_addr
c_func
(paren
)paren
suffix:semicolon
id|vma-&gt;vm_end
op_assign
id|vma-&gt;vm_start
op_plus
id|size
suffix:semicolon
id|vma-&gt;vm_page_prot
op_assign
id|pgprot_noncached
c_func
(paren
id|vma-&gt;vm_page_prot
)paren
suffix:semicolon
id|vma-&gt;vm_flags
op_or_assign
id|VM_IO
op_or
id|VM_RESERVED
suffix:semicolon
id|map
op_assign
id|__sq_alloc_mapping
c_func
(paren
id|vma-&gt;vm_start
comma
id|offset
comma
id|size
comma
l_string|&quot;Userspace&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|io_remap_page_range
c_func
(paren
id|vma
comma
id|map-&gt;sq_addr
comma
id|map-&gt;addr
comma
id|size
comma
id|vma-&gt;vm_page_prot
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|vma-&gt;vm_ops
op_assign
op_amp
id|sq_vma_ops
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_FS
DECL|function|sq_mapping_read_proc
r_static
r_int
id|sq_mapping_read_proc
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|len
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
r_char
op_star
id|p
op_assign
id|buf
suffix:semicolon
id|list_for_each_prev
c_func
(paren
id|pos
comma
op_amp
id|sq_mapping_list
)paren
(brace
r_struct
id|sq_mapping
op_star
id|entry
suffix:semicolon
id|entry
op_assign
id|list_entry
c_func
(paren
id|pos
comma
id|typeof
c_func
(paren
op_star
id|entry
)paren
comma
id|list
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;%08lx-%08lx [%08lx]: %s&bslash;n&quot;
comma
id|entry-&gt;sq_addr
comma
id|entry-&gt;sq_addr
op_plus
id|entry-&gt;size
op_minus
l_int|1
comma
id|entry-&gt;addr
comma
id|entry-&gt;name
)paren
suffix:semicolon
)brace
r_return
id|p
op_minus
id|buf
suffix:semicolon
)brace
macro_line|#endif
DECL|variable|sq_fops
r_static
r_struct
id|file_operations
id|sq_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|mmap
op_assign
id|sq_mmap
comma
)brace
suffix:semicolon
DECL|variable|sq_dev
r_static
r_struct
id|miscdevice
id|sq_dev
op_assign
(brace
dot
id|minor
op_assign
id|STORE_QUEUE_MINOR
comma
dot
id|name
op_assign
l_string|&quot;sq&quot;
comma
dot
id|devfs_name
op_assign
l_string|&quot;cpu/sq&quot;
comma
dot
id|fops
op_assign
op_amp
id|sq_fops
comma
)brace
suffix:semicolon
DECL|function|sq_api_init
r_static
r_int
id|__init
id|sq_api_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;sq: Registering store queue API.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
id|create_proc_read_entry
c_func
(paren
l_string|&quot;sq_mapping&quot;
comma
l_int|0
comma
l_int|0
comma
id|sq_mapping_read_proc
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
r_return
id|misc_register
c_func
(paren
op_amp
id|sq_dev
)paren
suffix:semicolon
)brace
DECL|function|sq_api_exit
r_static
r_void
id|__exit
id|sq_api_exit
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|sq_dev
)paren
suffix:semicolon
)brace
DECL|variable|sq_api_init
id|module_init
c_func
(paren
id|sq_api_init
)paren
suffix:semicolon
DECL|variable|sq_api_exit
id|module_exit
c_func
(paren
id|sq_api_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Paul Mundt &lt;lethal@linux-sh.org&gt;, M. R. Brown &lt;mrbrown@0xd6.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Simple API for SH-4 integrated Store Queues&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|STORE_QUEUE_MINOR
id|MODULE_ALIAS_MISCDEV
c_func
(paren
id|STORE_QUEUE_MINOR
)paren
suffix:semicolon
DECL|variable|sq_remap
id|EXPORT_SYMBOL
c_func
(paren
id|sq_remap
)paren
suffix:semicolon
DECL|variable|sq_unmap
id|EXPORT_SYMBOL
c_func
(paren
id|sq_unmap
)paren
suffix:semicolon
DECL|variable|sq_clear
id|EXPORT_SYMBOL
c_func
(paren
id|sq_clear
)paren
suffix:semicolon
DECL|variable|sq_flush
id|EXPORT_SYMBOL
c_func
(paren
id|sq_flush
)paren
suffix:semicolon
DECL|variable|sq_flush_range
id|EXPORT_SYMBOL
c_func
(paren
id|sq_flush_range
)paren
suffix:semicolon
eof
