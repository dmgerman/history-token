multiline_comment|/*&n; *  &n; *&n; *  PowerPC version &n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *&n; *  Modifications by Paul Mackerras (PowerMac) (paulus@cs.anu.edu.au)&n; *  and Cort Dougan (PReP) (cort@cs.nmt.edu)&n; *    Copyright (C) 1996 Paul Mackerras&n; *  Amiga/APUS changes by Jesper Skov (jskov@cygnus.co.uk).&n; *&n; *  Derived from &quot;arch/i386/mm/init.c&quot;&n; *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *&n; *  Dave Engebretsen &lt;engebret@us.ibm.com&gt;&n; *      Rework for PPC64 port.&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
macro_line|#include &lt;linux/blk.h&gt;&t;&t;/* for initrd_* */
macro_line|#endif
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/abs_addr.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/lmb.h&gt;
macro_line|#include &lt;asm/rtas.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/tlb.h&gt;
macro_line|#include &lt;asm/naca.h&gt;
macro_line|#include &lt;asm/eeh.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
DECL|macro|PGTOKB
mdefine_line|#define&t;PGTOKB(pages)&t;(((pages) * PAGE_SIZE) &gt;&gt; 10)
macro_line|#ifdef CONFIG_PPC_ISERIES
macro_line|#include &lt;asm/iSeries/iSeries_dma.h&gt;
macro_line|#endif
DECL|variable|mmu_context_queue
r_struct
id|mmu_context_queue_t
id|mmu_context_queue
suffix:semicolon
DECL|variable|mem_init_done
r_int
id|mem_init_done
suffix:semicolon
DECL|variable|ioremap_bot
r_int
r_int
id|ioremap_bot
op_assign
id|IMALLOC_BASE
suffix:semicolon
DECL|variable|boot_mapsize
r_static
r_int
id|boot_mapsize
suffix:semicolon
DECL|variable|totalram_pages
r_static
r_int
r_int
id|totalram_pages
suffix:semicolon
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
)braket
suffix:semicolon
r_extern
r_char
id|__init_begin
comma
id|__init_end
suffix:semicolon
r_extern
r_char
id|__chrp_begin
comma
id|__chrp_end
suffix:semicolon
r_extern
r_char
id|__openfirmware_begin
comma
id|__openfirmware_end
suffix:semicolon
r_extern
r_struct
id|_of_tce_table
id|of_tce_table
(braket
)braket
suffix:semicolon
r_extern
r_char
id|_start
(braket
)braket
comma
id|_end
(braket
)braket
suffix:semicolon
r_extern
r_char
id|_stext
(braket
)braket
comma
id|etext
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|task_struct
op_star
id|current_set
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_void
id|mm_init_ppc64
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
r_int
op_star
id|pmac_find_end_of_memory
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
op_star
id|find_end_of_memory
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|pgd_t
id|ioremap_dir
(braket
)braket
suffix:semicolon
DECL|variable|ioremap_pgd
id|pgd_t
op_star
id|ioremap_pgd
op_assign
(paren
id|pgd_t
op_star
)paren
op_amp
id|ioremap_dir
suffix:semicolon
r_static
r_void
id|map_io_page
c_func
(paren
r_int
r_int
id|va
comma
r_int
r_int
id|pa
comma
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_void
id|die_if_kernel
c_func
(paren
r_char
op_star
comma
r_struct
id|pt_regs
op_star
comma
r_int
)paren
suffix:semicolon
DECL|variable|klimit
r_int
r_int
id|klimit
op_assign
(paren
r_int
r_int
)paren
id|_end
suffix:semicolon
DECL|variable|Hash
id|HPTE
op_star
id|Hash
op_assign
l_int|0
suffix:semicolon
DECL|variable|Hash_size
r_int
r_int
id|Hash_size
op_assign
l_int|0
suffix:semicolon
DECL|variable|_SDR1
r_int
r_int
id|_SDR1
op_assign
l_int|0
suffix:semicolon
DECL|variable|_ASR
r_int
r_int
id|_ASR
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* max amount of RAM to use */
DECL|variable|__max_memory
r_int
r_int
id|__max_memory
suffix:semicolon
multiline_comment|/* This is declared as we are using the more or less generic &n; * include/asm-ppc64/tlb.h file -- tgall&n; */
DECL|variable|mmu_gathers
id|mmu_gather_t
id|mmu_gathers
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|function|show_mem
r_void
id|show_mem
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|free
op_assign
l_int|0
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
id|i
op_assign
id|max_mapnr
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
OG
l_int|0
)paren
(brace
id|total
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|mem_map
op_plus
id|i
)paren
)paren
id|reserved
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|PageSwapCache
c_func
(paren
id|mem_map
op_plus
id|i
)paren
)paren
id|cached
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|mem_map
(braket
id|i
)braket
dot
id|count
)paren
)paren
id|free
op_increment
suffix:semicolon
r_else
id|shared
op_add_assign
id|atomic_read
c_func
(paren
op_amp
id|mem_map
(braket
id|i
)braket
dot
id|count
)paren
op_minus
l_int|1
suffix:semicolon
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
l_string|&quot;%d free pages&bslash;n&quot;
comma
id|free
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
id|show_buffers
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|si_meminfo
r_void
id|si_meminfo
c_func
(paren
r_struct
id|sysinfo
op_star
id|val
)paren
(brace
id|val-&gt;totalram
op_assign
id|totalram_pages
suffix:semicolon
id|val-&gt;sharedram
op_assign
l_int|0
suffix:semicolon
id|val-&gt;freeram
op_assign
id|nr_free_pages
c_func
(paren
)paren
suffix:semicolon
id|val-&gt;bufferram
op_assign
id|atomic_read
c_func
(paren
op_amp
id|buffermem_pages
)paren
suffix:semicolon
id|val-&gt;totalhigh
op_assign
l_int|0
suffix:semicolon
id|val-&gt;freehigh
op_assign
l_int|0
suffix:semicolon
id|val-&gt;mem_unit
op_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_void
op_star
DECL|function|ioremap
id|ioremap
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
macro_line|#ifdef CONFIG_PPC_ISERIES
r_return
(paren
r_void
op_star
)paren
id|addr
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|mem_init_done
op_logical_and
(paren
id|addr
op_rshift
l_int|60UL
)paren
)paren
(brace
r_if
c_cond
(paren
id|IS_EEH_TOKEN_DISABLED
c_func
(paren
id|addr
)paren
)paren
r_return
(paren
r_void
op_star
)paren
id|IO_TOKEN_TO_ADDR
c_func
(paren
id|addr
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|addr
suffix:semicolon
multiline_comment|/* already mapped address or EEH token. */
)brace
r_return
id|__ioremap
c_func
(paren
id|addr
comma
id|size
comma
id|_PAGE_NO_CACHE
)paren
suffix:semicolon
macro_line|#endif
)brace
r_extern
r_struct
id|vm_struct
op_star
id|get_im_area
c_func
(paren
r_int
r_int
id|size
)paren
suffix:semicolon
r_void
op_star
DECL|function|__ioremap
id|__ioremap
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
comma
r_int
r_int
id|flags
)paren
(brace
r_int
r_int
id|pa
comma
id|ea
comma
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * Choose an address to map it to.&n;&t; * Once the imalloc system is running, we use it.&n;&t; * Before that, we map using addresses going&n;&t; * up from ioremap_bot.  imalloc will use&n;&t; * the addresses from ioremap_bot through&n;&t; * IMALLOC_END (0xE000001fffffffff)&n;&t; * &n;&t; */
id|pa
op_assign
id|addr
op_amp
id|PAGE_MASK
suffix:semicolon
id|size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|addr
op_plus
id|size
)paren
op_minus
id|pa
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|mem_init_done
)paren
(brace
r_struct
id|vm_struct
op_star
id|area
suffix:semicolon
id|area
op_assign
id|get_im_area
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|area
op_eq
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
id|ea
op_assign
(paren
r_int
r_int
)paren
(paren
id|area-&gt;addr
)paren
suffix:semicolon
)brace
r_else
(brace
id|ea
op_assign
id|ioremap_bot
suffix:semicolon
id|ioremap_bot
op_add_assign
id|size
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|_PAGE_PRESENT
)paren
op_eq
l_int|0
)paren
id|flags
op_or_assign
id|pgprot_val
c_func
(paren
id|PAGE_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
(paren
id|_PAGE_NO_CACHE
op_or
id|_PAGE_WRITETHRU
)paren
)paren
id|flags
op_or_assign
id|_PAGE_GUARDED
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
id|PAGE_SIZE
)paren
(brace
id|map_io_page
c_func
(paren
id|ea
op_plus
id|i
comma
id|pa
op_plus
id|i
comma
id|flags
)paren
suffix:semicolon
)brace
r_return
(paren
r_void
op_star
)paren
(paren
id|ea
op_plus
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
)paren
suffix:semicolon
)brace
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
macro_line|#ifdef CONFIG_PPC_ISERIES
multiline_comment|/* iSeries I/O Remap is a noop              */
r_return
suffix:semicolon
macro_line|#else 
multiline_comment|/* DRENG / PPPBBB todo */
r_return
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * map_io_page currently only called by __ioremap&n; * map_io_page adds an entry to the ioremap page table&n; * and adds an entry to the HPT, possibly bolting it&n; */
DECL|function|map_io_page
r_static
r_void
id|map_io_page
c_func
(paren
r_int
r_int
id|ea
comma
r_int
r_int
id|pa
comma
r_int
id|flags
)paren
(brace
id|pgd_t
op_star
id|pgdp
suffix:semicolon
id|pmd_t
op_star
id|pmdp
suffix:semicolon
id|pte_t
op_star
id|ptep
suffix:semicolon
r_int
r_int
id|vsid
suffix:semicolon
r_if
c_cond
(paren
id|mem_init_done
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|ioremap_mm.page_table_lock
)paren
suffix:semicolon
id|pgdp
op_assign
id|pgd_offset_i
c_func
(paren
id|ea
)paren
suffix:semicolon
id|pmdp
op_assign
id|pmd_alloc
c_func
(paren
op_amp
id|ioremap_mm
comma
id|pgdp
comma
id|ea
)paren
suffix:semicolon
id|ptep
op_assign
id|pte_alloc_kernel
c_func
(paren
op_amp
id|ioremap_mm
comma
id|pmdp
comma
id|ea
)paren
suffix:semicolon
id|pa
op_assign
id|absolute_to_phys
c_func
(paren
id|pa
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|ptep
comma
id|mk_pte_phys
c_func
(paren
id|pa
op_amp
id|PAGE_MASK
comma
id|__pgprot
c_func
(paren
id|flags
)paren
)paren
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|ioremap_mm.page_table_lock
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* If the mm subsystem is not fully up, we cannot create a&n;&t;&t; * linux page table entry for this mapping.  Simply bolt an&n;&t;&t; * entry in the hardware page table. &n; &t;&t; */
id|vsid
op_assign
id|get_kernel_vsid
c_func
(paren
id|ea
)paren
suffix:semicolon
id|ppc_md
dot
id|make_pte
c_func
(paren
id|htab_data.htab
comma
(paren
id|vsid
op_lshift
l_int|28
)paren
op_or
(paren
id|ea
op_amp
l_int|0xFFFFFFF
)paren
comma
singleline_comment|// va (NOT the ea)
id|pa
comma
id|_PAGE_NO_CACHE
op_or
id|_PAGE_GUARDED
op_or
id|PP_RWXX
comma
id|htab_data.htab_hash_mask
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|flush_tlb_mm
id|flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_if
c_cond
(paren
id|mm-&gt;map_count
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|mp
suffix:semicolon
r_for
c_loop
(paren
id|mp
op_assign
id|mm-&gt;mmap
suffix:semicolon
id|mp
op_ne
l_int|NULL
suffix:semicolon
id|mp
op_assign
id|mp-&gt;vm_next
)paren
id|__flush_tlb_range
c_func
(paren
id|mm
comma
id|mp-&gt;vm_start
comma
id|mp-&gt;vm_end
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* MIKEC: It is not clear why this is needed */
multiline_comment|/* paulus: it is needed to clear out stale HPTEs&n;&t;&t; * when an address space (represented by an mm_struct)&n;&t;&t; * is being destroyed. */
id|__flush_tlb_range
c_func
(paren
id|mm
comma
id|USER_START
comma
id|USER_END
)paren
suffix:semicolon
)brace
multiline_comment|/* XXX are there races with checking cpu_vm_mask? - Anton */
id|mm-&gt;cpu_vm_mask
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Callers should hold the mm-&gt;page_table_lock&n; */
r_void
DECL|function|flush_tlb_page
id|flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|vmaddr
)paren
(brace
r_int
r_int
id|context
op_assign
l_int|0
suffix:semicolon
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
id|ptep
suffix:semicolon
id|pte_t
id|pte
suffix:semicolon
r_int
id|local
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|REGION_ID
c_func
(paren
id|vmaddr
)paren
)paren
(brace
r_case
id|VMALLOC_REGION_ID
suffix:colon
id|pgd
op_assign
id|pgd_offset_k
c_func
(paren
id|vmaddr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IO_REGION_ID
suffix:colon
id|pgd
op_assign
id|pgd_offset_i
c_func
(paren
id|vmaddr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USER_REGION_ID
suffix:colon
id|pgd
op_assign
id|pgd_offset
c_func
(paren
id|vma-&gt;vm_mm
comma
id|vmaddr
)paren
suffix:semicolon
id|context
op_assign
id|vma-&gt;vm_mm-&gt;context
suffix:semicolon
multiline_comment|/* XXX are there races with checking cpu_vm_mask? - Anton */
r_if
c_cond
(paren
id|vma-&gt;vm_mm-&gt;cpu_vm_mask
op_eq
(paren
l_int|1
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
id|local
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;flush_tlb_page: invalid region 0x%016lx&quot;
comma
id|vmaddr
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pgd_none
c_func
(paren
op_star
id|pgd
)paren
)paren
(brace
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|vmaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|ptep
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmd
comma
id|vmaddr
)paren
suffix:semicolon
multiline_comment|/* Check if HPTE might exist and flush it if so */
id|pte
op_assign
id|__pte
c_func
(paren
id|pte_update
c_func
(paren
id|ptep
comma
id|_PAGE_HPTEFLAGS
comma
l_int|0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_HASHPTE
)paren
(brace
id|flush_hash_page
c_func
(paren
id|context
comma
id|vmaddr
comma
id|pte
comma
id|local
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|variable|tlb_batch_array
r_struct
id|tlb_batch_data
id|tlb_batch_array
(braket
id|NR_CPUS
)braket
(braket
id|MAX_BATCH_FLUSH
)braket
suffix:semicolon
r_void
DECL|function|__flush_tlb_range
id|__flush_tlb_range
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
id|ptep
suffix:semicolon
id|pte_t
id|pte
suffix:semicolon
r_int
r_int
id|pgd_end
comma
id|pmd_end
suffix:semicolon
r_int
r_int
id|context
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_struct
id|tlb_batch_data
op_star
id|ptes
op_assign
op_amp
id|tlb_batch_array
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
(braket
l_int|0
)braket
suffix:semicolon
r_int
id|local
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|start
op_ge
id|end
)paren
id|panic
c_func
(paren
l_string|&quot;flush_tlb_range: start (%016lx) greater than end (%016lx)&bslash;n&quot;
comma
id|start
comma
id|end
)paren
suffix:semicolon
r_if
c_cond
(paren
id|REGION_ID
c_func
(paren
id|start
)paren
op_ne
id|REGION_ID
c_func
(paren
id|end
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;flush_tlb_range: start (%016lx) and end (%016lx) not in same region&bslash;n&quot;
comma
id|start
comma
id|end
)paren
suffix:semicolon
id|context
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|REGION_ID
c_func
(paren
id|start
)paren
)paren
(brace
r_case
id|VMALLOC_REGION_ID
suffix:colon
id|pgd
op_assign
id|pgd_offset_k
c_func
(paren
id|start
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IO_REGION_ID
suffix:colon
id|pgd
op_assign
id|pgd_offset_i
c_func
(paren
id|start
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|USER_REGION_ID
suffix:colon
id|pgd
op_assign
id|pgd_offset
c_func
(paren
id|mm
comma
id|start
)paren
suffix:semicolon
id|context
op_assign
id|mm-&gt;context
suffix:semicolon
multiline_comment|/* XXX are there races with checking cpu_vm_mask? - Anton */
r_if
c_cond
(paren
id|mm-&gt;cpu_vm_mask
op_eq
(paren
l_int|1
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
(brace
id|local
op_assign
l_int|1
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;flush_tlb_range: invalid region for start (%016lx) and end (%016lx)&bslash;n&quot;
comma
id|start
comma
id|end
)paren
suffix:semicolon
)brace
r_do
(brace
id|pgd_end
op_assign
(paren
id|start
op_plus
id|PGDIR_SIZE
)paren
op_amp
id|PGDIR_MASK
suffix:semicolon
r_if
c_cond
(paren
id|pgd_end
OG
id|end
)paren
id|pgd_end
op_assign
id|end
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pgd_none
c_func
(paren
op_star
id|pgd
)paren
)paren
(brace
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|start
)paren
suffix:semicolon
r_do
(brace
id|pmd_end
op_assign
(paren
id|start
op_plus
id|PMD_SIZE
)paren
op_amp
id|PMD_MASK
suffix:semicolon
r_if
c_cond
(paren
id|pmd_end
OG
id|end
)paren
id|pmd_end
op_assign
id|end
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|ptep
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmd
comma
id|start
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
op_amp
id|_PAGE_HASHPTE
)paren
(brace
id|pte
op_assign
id|__pte
c_func
(paren
id|pte_update
c_func
(paren
id|ptep
comma
id|_PAGE_HPTEFLAGS
comma
l_int|0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_HASHPTE
)paren
(brace
id|ptes-&gt;pte
op_assign
id|pte
suffix:semicolon
id|ptes-&gt;addr
op_assign
id|start
suffix:semicolon
id|ptes
op_increment
suffix:semicolon
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|MAX_BATCH_FLUSH
)paren
(brace
id|flush_hash_range
c_func
(paren
id|context
comma
id|MAX_BATCH_FLUSH
comma
id|local
)paren
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
id|ptes
op_assign
op_amp
id|tlb_batch_array
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
(braket
l_int|0
)braket
suffix:semicolon
)brace
)brace
)brace
id|start
op_add_assign
id|PAGE_SIZE
suffix:semicolon
op_increment
id|ptep
suffix:semicolon
)brace
r_while
c_loop
(paren
id|start
OL
id|pmd_end
)paren
suffix:semicolon
)brace
r_else
id|start
op_assign
id|pmd_end
suffix:semicolon
op_increment
id|pmd
suffix:semicolon
)brace
r_while
c_loop
(paren
id|start
OL
id|pgd_end
)paren
suffix:semicolon
)brace
r_else
id|start
op_assign
id|pgd_end
suffix:semicolon
op_increment
id|pgd
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
r_if
c_cond
(paren
id|i
)paren
id|flush_hash_range
c_func
(paren
id|context
comma
id|i
comma
id|local
)paren
suffix:semicolon
)brace
DECL|function|free_initmem
r_void
id|__init
id|free_initmem
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|a
suffix:semicolon
r_int
r_int
id|num_freed_pages
op_assign
l_int|0
suffix:semicolon
DECL|macro|FREESEC
mdefine_line|#define FREESEC(START,END,CNT) do { &bslash;&n;&t;a = (unsigned long)(&amp;START); &bslash;&n;&t;for (; a &lt; (unsigned long)(&amp;END); a += PAGE_SIZE) { &bslash;&n;&t;  &t;clear_bit(PG_reserved, &amp;mem_map[MAP_NR(a)].flags); &bslash;&n;&t;&t;set_page_count(mem_map+MAP_NR(a), 1); &bslash;&n;&t;&t;free_page(a); &bslash;&n;&t;&t;CNT++; &bslash;&n;&t;} &bslash;&n;} while (0)
id|FREESEC
c_func
(paren
id|__init_begin
comma
id|__init_end
comma
id|num_freed_pages
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;Freeing unused kernel memory: %ldk init&bslash;n&quot;
comma
id|PGTOKB
c_func
(paren
id|num_freed_pages
)paren
)paren
suffix:semicolon
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
r_int
r_int
id|xstart
op_assign
id|start
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
id|mem_map
op_plus
id|MAP_NR
c_func
(paren
id|start
)paren
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|mem_map
op_plus
id|MAP_NR
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
id|printk
(paren
l_string|&quot;Freeing initrd memory: %ldk freed&bslash;n&quot;
comma
(paren
id|end
op_minus
id|xstart
)paren
op_rshift
l_int|10
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Do very early mm setup.&n; */
DECL|function|mm_init_ppc64
r_void
id|__init
id|mm_init_ppc64
c_func
(paren
r_void
)paren
(brace
r_struct
id|paca_struct
op_star
id|lpaca
suffix:semicolon
r_int
r_int
id|guard_page
comma
id|index
suffix:semicolon
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;MM:init&quot;
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Reserve all contexts &lt; FIRST_USER_CONTEXT for kernel use.&n;&t; * The range of contexts [FIRST_USER_CONTEXT, NUM_USER_CONTEXT)&n;&t; * are stored on a stack/queue for easy allocation and deallocation.&n;&t; */
id|mmu_context_queue.lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|mmu_context_queue.head
op_assign
l_int|0
suffix:semicolon
id|mmu_context_queue.tail
op_assign
id|NUM_USER_CONTEXT
op_minus
l_int|1
suffix:semicolon
id|mmu_context_queue.size
op_assign
id|NUM_USER_CONTEXT
suffix:semicolon
r_for
c_loop
(paren
id|index
op_assign
l_int|0
suffix:semicolon
id|index
OL
id|NUM_USER_CONTEXT
suffix:semicolon
id|index
op_increment
)paren
(brace
id|mmu_context_queue.elements
(braket
id|index
)braket
op_assign
id|index
op_plus
id|FIRST_USER_CONTEXT
suffix:semicolon
)brace
multiline_comment|/* Setup guard pages for the Paca&squot;s */
r_for
c_loop
(paren
id|index
op_assign
l_int|0
suffix:semicolon
id|index
OL
id|NR_CPUS
suffix:semicolon
id|index
op_increment
)paren
(brace
id|lpaca
op_assign
op_amp
id|paca
(braket
id|index
)braket
suffix:semicolon
id|guard_page
op_assign
(paren
(paren
r_int
r_int
)paren
id|lpaca
)paren
op_plus
l_int|0x1000
suffix:semicolon
id|ppc_md
dot
id|hpte_updateboltedpp
c_func
(paren
id|PP_RXRX
comma
id|guard_page
)paren
suffix:semicolon
)brace
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;MM:exit&quot;
comma
l_int|0x211
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize the bootmem system and give it all the memory we&n; * have available.&n; */
DECL|function|do_init_bootmem
r_void
id|__init
id|do_init_bootmem
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_int
r_int
id|start
comma
id|bootmap_pages
suffix:semicolon
r_int
r_int
id|total_pages
op_assign
id|lmb_end_of_DRAM
c_func
(paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_MMINIT
comma
l_string|&quot;do_init_bootmem: start&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Find an area to use for the bootmem bitmap.  Calculate the size of&n;&t; * bitmap required as (Total Memory) / PAGE_SIZE / BITS_PER_BYTE.&n;&t; * Add 1 additional page in case the address isn&squot;t page-aligned.&n;&t; */
id|bootmap_pages
op_assign
id|bootmem_bootmap_pages
c_func
(paren
id|total_pages
)paren
suffix:semicolon
id|start
op_assign
(paren
r_int
r_int
)paren
id|__a2p
c_func
(paren
id|lmb_alloc
c_func
(paren
id|bootmap_pages
op_lshift
id|PAGE_SHIFT
comma
id|PAGE_SIZE
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|start
op_eq
l_int|0
)paren
(brace
id|udbg_printf
c_func
(paren
l_string|&quot;do_init_bootmem: failed to allocate a bitmap.&bslash;n&quot;
)paren
suffix:semicolon
id|udbg_printf
c_func
(paren
l_string|&quot;&bslash;tbootmap_pages = 0x%lx.&bslash;n&quot;
comma
id|bootmap_pages
)paren
suffix:semicolon
id|PPCDBG_ENTER_DEBUGGER
c_func
(paren
)paren
suffix:semicolon
)brace
id|PPCDBG
c_func
(paren
id|PPCDBG_MMINIT
comma
l_string|&quot;&bslash;tstart               = 0x%lx&bslash;n&quot;
comma
id|start
)paren
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_MMINIT
comma
l_string|&quot;&bslash;tbootmap_pages       = 0x%lx&bslash;n&quot;
comma
id|bootmap_pages
)paren
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_MMINIT
comma
l_string|&quot;&bslash;tphysicalMemorySize  = 0x%lx&bslash;n&quot;
comma
id|naca-&gt;physicalMemorySize
)paren
suffix:semicolon
id|boot_mapsize
op_assign
id|init_bootmem
c_func
(paren
id|start
op_rshift
id|PAGE_SHIFT
comma
id|total_pages
)paren
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_MMINIT
comma
l_string|&quot;&bslash;tboot_mapsize        = 0x%lx&bslash;n&quot;
comma
id|boot_mapsize
)paren
suffix:semicolon
multiline_comment|/* add all physical memory to the bootmem map */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|lmb.memory.cnt
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|physbase
comma
id|size
suffix:semicolon
r_int
r_int
id|type
op_assign
id|lmb.memory.region
(braket
id|i
)braket
dot
id|type
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
id|LMB_MEMORY_AREA
)paren
r_continue
suffix:semicolon
id|physbase
op_assign
id|lmb.memory.region
(braket
id|i
)braket
dot
id|physbase
suffix:semicolon
id|size
op_assign
id|lmb.memory.region
(braket
id|i
)braket
dot
id|size
suffix:semicolon
id|free_bootmem
c_func
(paren
id|physbase
comma
id|size
)paren
suffix:semicolon
)brace
multiline_comment|/* reserve the sections we&squot;re already using */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|lmb.reserved.cnt
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|physbase
op_assign
id|lmb.reserved.region
(braket
id|i
)braket
dot
id|physbase
suffix:semicolon
r_int
r_int
id|size
op_assign
id|lmb.reserved.region
(braket
id|i
)braket
dot
id|size
suffix:semicolon
macro_line|#if 0 /* PPPBBB */
r_if
c_cond
(paren
(paren
id|physbase
op_eq
l_int|0
)paren
op_logical_and
(paren
id|size
OL
(paren
l_int|16
op_lshift
l_int|20
)paren
)paren
)paren
(brace
id|size
op_assign
l_int|16
op_lshift
l_int|20
suffix:semicolon
)brace
macro_line|#endif
id|reserve_bootmem
c_func
(paren
id|physbase
comma
id|size
)paren
suffix:semicolon
)brace
id|PPCDBG
c_func
(paren
id|PPCDBG_MMINIT
comma
l_string|&quot;do_init_bootmem: end&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * paging_init() sets up the page tables - in fact we&squot;ve already done this.&n; */
DECL|function|paging_init
r_void
id|__init
id|paging_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|zones_size
(braket
id|MAX_NR_ZONES
)braket
comma
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * All pages are DMA-able so we put them all in the DMA zone.&n;&t; */
id|zones_size
(braket
l_int|0
)braket
op_assign
id|lmb_end_of_DRAM
c_func
(paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|MAX_NR_ZONES
suffix:semicolon
id|i
op_increment
)paren
id|zones_size
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|free_area_init
c_func
(paren
id|zones_size
)paren
suffix:semicolon
)brace
r_extern
r_int
r_int
id|prof_shift
suffix:semicolon
r_extern
r_int
r_int
id|prof_len
suffix:semicolon
r_extern
r_int
r_int
op_star
id|prof_buffer
suffix:semicolon
r_extern
r_int
r_int
id|dprof_shift
suffix:semicolon
r_extern
r_int
r_int
id|dprof_len
suffix:semicolon
r_extern
r_int
r_int
op_star
id|dprof_buffer
suffix:semicolon
r_void
id|initialize_paca_hardware_interrupt_stack
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|mem_init
r_void
id|__init
id|mem_init
c_func
(paren
r_void
)paren
(brace
r_extern
r_char
op_star
id|sysmap
suffix:semicolon
r_extern
r_int
r_int
id|sysmap_size
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_int
id|codepages
op_assign
l_int|0
suffix:semicolon
r_int
id|datapages
op_assign
l_int|0
suffix:semicolon
r_int
id|initpages
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|va_rtas_base
op_assign
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|rtas.base
)paren
suffix:semicolon
id|max_mapnr
op_assign
id|max_low_pfn
suffix:semicolon
id|high_memory
op_assign
(paren
r_void
op_star
)paren
id|__va
c_func
(paren
id|max_low_pfn
op_star
id|PAGE_SIZE
)paren
suffix:semicolon
id|num_physpages
op_assign
id|max_mapnr
suffix:semicolon
multiline_comment|/* RAM is assumed contiguous */
id|max_pfn
op_assign
id|max_low_pfn
suffix:semicolon
id|totalram_pages
op_add_assign
id|free_all_bootmem
c_func
(paren
)paren
suffix:semicolon
id|ifppcdebug
c_func
(paren
id|PPCDBG_MMINIT
)paren
(brace
id|udbg_printf
c_func
(paren
l_string|&quot;mem_init: totalram_pages = 0x%lx&bslash;n&quot;
comma
id|totalram_pages
)paren
suffix:semicolon
id|udbg_printf
c_func
(paren
l_string|&quot;mem_init: va_rtas_base   = 0x%lx&bslash;n&quot;
comma
id|va_rtas_base
)paren
suffix:semicolon
id|udbg_printf
c_func
(paren
l_string|&quot;mem_init: va_rtas_end    = 0x%lx&bslash;n&quot;
comma
id|PAGE_ALIGN
c_func
(paren
id|va_rtas_base
op_plus
id|rtas.size
)paren
)paren
suffix:semicolon
id|udbg_printf
c_func
(paren
l_string|&quot;mem_init: pinned start   = 0x%lx&bslash;n&quot;
comma
id|__va
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|udbg_printf
c_func
(paren
l_string|&quot;mem_init: pinned end     = 0x%lx&bslash;n&quot;
comma
id|PAGE_ALIGN
c_func
(paren
id|klimit
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sysmap_size
)paren
r_for
c_loop
(paren
id|addr
op_assign
(paren
r_int
r_int
)paren
id|sysmap
suffix:semicolon
id|addr
OL
id|PAGE_ALIGN
c_func
(paren
(paren
r_int
r_int
)paren
id|sysmap
op_plus
id|sysmap_size
)paren
suffix:semicolon
id|addr
op_add_assign
id|PAGE_SIZE
)paren
id|SetPageReserved
c_func
(paren
id|mem_map
op_plus
id|MAP_NR
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
id|KERNELBASE
suffix:semicolon
id|addr
op_le
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|lmb_end_of_DRAM
c_func
(paren
)paren
)paren
suffix:semicolon
id|addr
op_add_assign
id|PAGE_SIZE
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|PageReserved
c_func
(paren
id|mem_map
op_plus
id|MAP_NR
c_func
(paren
id|addr
)paren
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|addr
OL
(paren
id|ulong
)paren
id|etext
)paren
id|codepages
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|addr
op_ge
(paren
r_int
r_int
)paren
op_amp
id|__init_begin
op_logical_and
id|addr
OL
(paren
r_int
r_int
)paren
op_amp
id|__init_end
)paren
id|initpages
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
id|addr
OL
id|klimit
)paren
id|datapages
op_increment
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Memory: %luk available (%dk kernel code, %dk data, %dk init) [%08lx,%08lx]&bslash;n&quot;
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
comma
id|codepages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|datapages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|initpages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|PAGE_OFFSET
comma
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|lmb_end_of_DRAM
c_func
(paren
)paren
)paren
)paren
suffix:semicolon
id|mem_init_done
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* set the last page of each hardware interrupt stack to be protected */
id|initialize_paca_hardware_interrupt_stack
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PPC_ISERIES
id|create_virtual_bus_tce_table
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* HACK HACK This allows the iSeries profiling to use /proc/profile */
id|prof_shift
op_assign
id|dprof_shift
suffix:semicolon
id|prof_len
op_assign
id|dprof_len
suffix:semicolon
id|prof_buffer
op_assign
id|dprof_buffer
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * This is called when a page has been modified by the kernel.&n; * It just marks the page as not i-cache clean.  We do the i-cache&n; * flush later when the page is given to a user process, if necessary.&n; */
DECL|function|flush_dcache_page
r_void
id|flush_dcache_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|clear_bit
c_func
(paren
id|PG_arch_1
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
)brace
DECL|function|flush_icache_page
r_void
id|flush_icache_page
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
r_if
c_cond
(paren
id|page-&gt;mapping
op_logical_and
op_logical_neg
id|PageReserved
c_func
(paren
id|page
)paren
op_logical_and
op_logical_neg
id|test_bit
c_func
(paren
id|PG_arch_1
comma
op_amp
id|page-&gt;flags
)paren
)paren
(brace
id|__flush_dcache_icache
c_func
(paren
id|page_address
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|PG_arch_1
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
)brace
)brace
DECL|function|clear_user_page
r_void
id|clear_user_page
c_func
(paren
r_void
op_star
id|page
comma
r_int
r_int
id|vaddr
)paren
(brace
id|clear_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
DECL|function|copy_user_page
r_void
id|copy_user_page
c_func
(paren
r_void
op_star
id|vto
comma
r_void
op_star
id|vfrom
comma
r_int
r_int
id|vaddr
)paren
(brace
id|copy_page
c_func
(paren
id|vto
comma
id|vfrom
)paren
suffix:semicolon
id|__flush_dcache_icache
c_func
(paren
id|vto
)paren
suffix:semicolon
)brace
DECL|function|flush_icache_user_range
r_void
id|flush_icache_user_range
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
comma
r_int
r_int
id|addr
comma
r_int
id|len
)paren
(brace
r_int
r_int
id|maddr
suffix:semicolon
id|maddr
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
op_plus
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
id|flush_icache_range
c_func
(paren
id|maddr
comma
id|maddr
op_plus
id|len
)paren
suffix:semicolon
)brace
r_extern
id|pte_t
op_star
id|find_linux_pte
c_func
(paren
id|pgd_t
op_star
id|pgdir
comma
r_int
r_int
id|ea
)paren
suffix:semicolon
r_int
id|__hash_page
c_func
(paren
r_int
r_int
id|ea
comma
r_int
r_int
id|access
comma
r_int
r_int
id|vsid
comma
id|pte_t
op_star
id|ptep
)paren
suffix:semicolon
multiline_comment|/*&n; * This is called at the end of handling a user page fault, when the&n; * fault has been handled by updating a PTE in the linux page tables.&n; * We use it to preload an HPTE into the hash table corresponding to&n; * the updated linux PTE.&n; */
DECL|function|update_mmu_cache
r_void
id|update_mmu_cache
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|ea
comma
id|pte_t
id|pte
)paren
(brace
r_int
r_int
id|vsid
suffix:semicolon
r_void
op_star
id|pgdir
suffix:semicolon
id|pte_t
op_star
id|ptep
suffix:semicolon
multiline_comment|/* We only want HPTEs for linux PTEs that have _PAGE_ACCESSED set */
r_if
c_cond
(paren
op_logical_neg
id|pte_young
c_func
(paren
id|pte
)paren
)paren
r_return
suffix:semicolon
id|pgdir
op_assign
id|vma-&gt;vm_mm-&gt;pgd
suffix:semicolon
r_if
c_cond
(paren
id|pgdir
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|ptep
op_assign
id|find_linux_pte
c_func
(paren
id|pgdir
comma
id|ea
)paren
suffix:semicolon
id|vsid
op_assign
id|get_vsid
c_func
(paren
id|vma-&gt;vm_mm-&gt;context
comma
id|ea
)paren
suffix:semicolon
id|__hash_page
c_func
(paren
id|ea
comma
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
(paren
id|_PAGE_USER
op_or
id|_PAGE_RW
)paren
comma
id|vsid
comma
id|ptep
)paren
suffix:semicolon
)brace
eof
