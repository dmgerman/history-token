multiline_comment|/*&n; *  PowerPC version&n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *&n; *  Modifications by Paul Mackerras (PowerMac) (paulus@cs.anu.edu.au)&n; *  and Cort Dougan (PReP) (cort@cs.nmt.edu)&n; *    Copyright (C) 1996 Paul Mackerras&n; *  Amiga/APUS changes by Jesper Skov (jskov@cygnus.co.uk).&n; *  PPC44x/36-bit changes by Matt Porter (mporter@mvista.com)&n; *&n; *  Derived from &quot;arch/i386/mm/init.c&quot;&n; *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/btext.h&gt;
macro_line|#include &lt;asm/tlb.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &quot;mem_pieces.h&quot;
macro_line|#include &quot;mmu_decl.h&quot;
macro_line|#if defined(CONFIG_KERNEL_START_BOOL) || defined(CONFIG_LOWMEM_SIZE_BOOL)
multiline_comment|/* The ammount of lowmem must be within 0xF0000000 - KERNELBASE. */
macro_line|#if (CONFIG_LOWMEM_SIZE &gt; (0xF0000000 - KERNELBASE))
macro_line|#error &quot;You must adjust CONFIG_LOWMEM_SIZE or CONFIG_START_KERNEL&quot;
macro_line|#endif
macro_line|#endif
DECL|macro|MAX_LOW_MEM
mdefine_line|#define MAX_LOW_MEM&t;CONFIG_LOWMEM_SIZE
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|mmu_gather
comma
id|mmu_gathers
)paren
suffix:semicolon
DECL|variable|total_memory
r_int
r_int
id|total_memory
suffix:semicolon
DECL|variable|total_lowmem
r_int
r_int
id|total_lowmem
suffix:semicolon
DECL|variable|ppc_memstart
r_int
r_int
id|ppc_memstart
suffix:semicolon
DECL|variable|ppc_memoffset
r_int
r_int
id|ppc_memoffset
op_assign
id|PAGE_OFFSET
suffix:semicolon
DECL|variable|mem_init_done
r_int
id|mem_init_done
suffix:semicolon
DECL|variable|init_bootmem_done
r_int
id|init_bootmem_done
suffix:semicolon
DECL|variable|boot_mapsize
r_int
id|boot_mapsize
suffix:semicolon
macro_line|#ifdef CONFIG_PPC_PMAC
DECL|variable|agp_special_page
r_int
r_int
id|agp_special_page
suffix:semicolon
macro_line|#endif
r_extern
r_char
id|_end
(braket
)braket
suffix:semicolon
r_extern
r_char
id|etext
(braket
)braket
comma
id|_stext
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
id|__prep_begin
comma
id|__prep_end
suffix:semicolon
r_extern
r_char
id|__chrp_begin
comma
id|__chrp_end
suffix:semicolon
r_extern
r_char
id|__pmac_begin
comma
id|__pmac_end
suffix:semicolon
r_extern
r_char
id|__openfirmware_begin
comma
id|__openfirmware_end
suffix:semicolon
macro_line|#ifdef CONFIG_HIGHMEM
DECL|variable|kmap_pte
id|pte_t
op_star
id|kmap_pte
suffix:semicolon
DECL|variable|kmap_prot
id|pgprot_t
id|kmap_prot
suffix:semicolon
DECL|variable|kmap_prot
id|EXPORT_SYMBOL
c_func
(paren
id|kmap_prot
)paren
suffix:semicolon
DECL|variable|kmap_pte
id|EXPORT_SYMBOL
c_func
(paren
id|kmap_pte
)paren
suffix:semicolon
macro_line|#endif
r_void
id|MMU_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|set_phys_avail
c_func
(paren
r_int
r_int
id|total_ram
)paren
suffix:semicolon
multiline_comment|/* XXX should be in current.h  -- paulus */
r_extern
r_struct
id|task_struct
op_star
id|current_set
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|klimit
r_char
op_star
id|klimit
op_assign
id|_end
suffix:semicolon
DECL|variable|phys_avail
r_struct
id|mem_pieces
id|phys_avail
suffix:semicolon
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
multiline_comment|/*&n; * this tells the system to map all of ram with the segregs&n; * (i.e. page tables) instead of the bats.&n; * -- Cort&n; */
DECL|variable|__map_without_bats
r_int
id|__map_without_bats
suffix:semicolon
DECL|variable|__map_without_ltlbs
r_int
id|__map_without_ltlbs
suffix:semicolon
multiline_comment|/* max amount of RAM to use */
DECL|variable|__max_memory
r_int
r_int
id|__max_memory
suffix:semicolon
multiline_comment|/* max amount of low RAM to map in */
DECL|variable|__max_low_memory
r_int
r_int
id|__max_low_memory
op_assign
id|MAX_LOW_MEM
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
r_int
id|highmem
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
l_string|&quot;Free swap:       %6ldkB&bslash;n&quot;
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
id|PageHighMem
c_func
(paren
id|mem_map
op_plus
id|i
)paren
)paren
id|highmem
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
id|page_count
c_func
(paren
id|mem_map
op_plus
id|i
)paren
)paren
id|free
op_increment
suffix:semicolon
r_else
id|shared
op_add_assign
id|page_count
c_func
(paren
id|mem_map
op_plus
id|i
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
l_string|&quot;%d pages of HIGHMEM&bslash;n&quot;
comma
id|highmem
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
)brace
multiline_comment|/* Free up now-unused memory */
DECL|function|free_sec
r_static
r_void
id|free_sec
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
r_const
r_char
op_star
id|name
)paren
(brace
r_int
r_int
id|cnt
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
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
id|cnt
op_increment
suffix:semicolon
id|start
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cnt
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; %ldk %s&quot;
comma
id|cnt
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|name
)paren
suffix:semicolon
id|totalram_pages
op_add_assign
id|cnt
suffix:semicolon
)brace
)brace
DECL|function|free_initmem
r_void
id|free_initmem
c_func
(paren
r_void
)paren
(brace
DECL|macro|FREESEC
mdefine_line|#define FREESEC(TYPE) &bslash;&n;&t;free_sec((unsigned long)(&amp;__ ## TYPE ## _begin), &bslash;&n;&t;&t; (unsigned long)(&amp;__ ## TYPE ## _end), &bslash;&n;&t;&t; #TYPE);
id|printk
(paren
l_string|&quot;Freeing unused kernel memory:&quot;
)paren
suffix:semicolon
id|FREESEC
c_func
(paren
id|init
)paren
suffix:semicolon
r_if
c_cond
(paren
id|_machine
op_ne
id|_MACH_Pmac
)paren
id|FREESEC
c_func
(paren
id|pmac
)paren
suffix:semicolon
r_if
c_cond
(paren
id|_machine
op_ne
id|_MACH_chrp
)paren
id|FREESEC
c_func
(paren
id|chrp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|_machine
op_ne
id|_MACH_prep
)paren
id|FREESEC
c_func
(paren
id|prep
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|have_of
)paren
id|FREESEC
c_func
(paren
id|openfirmware
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
DECL|macro|FREESEC
macro_line|#undef FREESEC
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
multiline_comment|/*&n; * Check for command-line options that affect what MMU_init will do.&n; */
DECL|function|MMU_setup
r_void
id|MMU_setup
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Check for nobats option (used in mapin_ram). */
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|cmd_line
comma
l_string|&quot;nobats&quot;
)paren
)paren
(brace
id|__map_without_bats
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|cmd_line
comma
l_string|&quot;noltlbs&quot;
)paren
)paren
(brace
id|__map_without_ltlbs
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Look for mem= option on command line */
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|cmd_line
comma
l_string|&quot;mem=&quot;
)paren
)paren
(brace
r_char
op_star
id|p
comma
op_star
id|q
suffix:semicolon
r_int
r_int
id|maxmem
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|q
op_assign
id|cmd_line
suffix:semicolon
(paren
id|p
op_assign
id|strstr
c_func
(paren
id|q
comma
l_string|&quot;mem=&quot;
)paren
)paren
op_ne
l_int|0
suffix:semicolon
)paren
(brace
id|q
op_assign
id|p
op_plus
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|p
OG
id|cmd_line
op_logical_and
id|p
(braket
op_minus
l_int|1
)braket
op_ne
l_char|&squot; &squot;
)paren
r_continue
suffix:semicolon
id|maxmem
op_assign
id|simple_strtoul
c_func
(paren
id|q
comma
op_amp
id|q
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|q
op_eq
l_char|&squot;k&squot;
op_logical_or
op_star
id|q
op_eq
l_char|&squot;K&squot;
)paren
(brace
id|maxmem
op_lshift_assign
l_int|10
suffix:semicolon
op_increment
id|q
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|q
op_eq
l_char|&squot;m&squot;
op_logical_or
op_star
id|q
op_eq
l_char|&squot;M&squot;
)paren
(brace
id|maxmem
op_lshift_assign
l_int|20
suffix:semicolon
op_increment
id|q
suffix:semicolon
)brace
)brace
id|__max_memory
op_assign
id|maxmem
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * MMU_init sets up the basic memory mappings for the kernel,&n; * including both RAM and possibly some I/O regions,&n; * and sets up the page tables and the MMU hardware ready to go.&n; */
DECL|function|MMU_init
r_void
id|__init
id|MMU_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;MMU:enter&quot;
comma
l_int|0x111
)paren
suffix:semicolon
multiline_comment|/* parse args from command line */
id|MMU_setup
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Figure out how much memory we have, how much&n;&t; * is lowmem, and how much is highmem.  If we were&n;&t; * passed the total memory size from the bootloader,&n;&t; * just use it.&n;&t; */
r_if
c_cond
(paren
id|boot_mem_size
)paren
id|total_memory
op_assign
id|boot_mem_size
suffix:semicolon
r_else
id|total_memory
op_assign
id|ppc_md
dot
id|find_end_of_memory
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|__max_memory
op_logical_and
id|total_memory
OG
id|__max_memory
)paren
id|total_memory
op_assign
id|__max_memory
suffix:semicolon
id|total_lowmem
op_assign
id|total_memory
suffix:semicolon
macro_line|#ifdef CONFIG_FSL_BOOKE
multiline_comment|/* Freescale Book-E parts expect lowmem to be mapped by fixed TLB&n;&t; * entries, so we need to adjust lowmem to match the amount we can map&n;&t; * in the fixed entries */
id|adjust_total_lowmem
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_FSL_BOOKE */
r_if
c_cond
(paren
id|total_lowmem
OG
id|__max_low_memory
)paren
(brace
id|total_lowmem
op_assign
id|__max_low_memory
suffix:semicolon
macro_line|#ifndef CONFIG_HIGHMEM
id|total_memory
op_assign
id|total_lowmem
suffix:semicolon
macro_line|#endif /* CONFIG_HIGHMEM */
)brace
id|set_phys_avail
c_func
(paren
id|total_lowmem
)paren
suffix:semicolon
multiline_comment|/* Initialize the MMU hardware */
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;MMU:hw init&quot;
comma
l_int|0x300
)paren
suffix:semicolon
id|MMU_init_hw
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Map in all of RAM starting at KERNELBASE */
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;MMU:mapin&quot;
comma
l_int|0x301
)paren
suffix:semicolon
id|mapin_ram
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HIGHMEM
id|ioremap_base
op_assign
id|PKMAP_BASE
suffix:semicolon
macro_line|#else
id|ioremap_base
op_assign
l_int|0xfe000000UL
suffix:semicolon
multiline_comment|/* for now, could be 0xfffff000 */
macro_line|#endif /* CONFIG_HIGHMEM */
id|ioremap_bot
op_assign
id|ioremap_base
suffix:semicolon
multiline_comment|/* Map in I/O resources */
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;MMU:setio&quot;
comma
l_int|0x302
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.setup_io_mappings
)paren
id|ppc_md
dot
id|setup_io_mappings
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Initialize the context management stuff */
id|mmu_context_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;MMU:exit&quot;
comma
l_int|0x211
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BOOTX_TEXT
multiline_comment|/* By default, we are no longer mapped */
id|boot_text_mapped
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Must be done last, or ppc_md.progress will die. */
id|map_boot_text
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* This is only called until mem_init is done. */
DECL|function|early_get_page
r_void
id|__init
op_star
id|early_get_page
c_func
(paren
r_void
)paren
(brace
r_void
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|init_bootmem_done
)paren
(brace
id|p
op_assign
id|alloc_bootmem_pages
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
)brace
r_else
(brace
id|p
op_assign
id|mem_pieces_find
c_func
(paren
id|PAGE_SIZE
comma
id|PAGE_SIZE
)paren
suffix:semicolon
)brace
r_return
id|p
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
id|start
comma
id|size
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * Find an area to use for the bootmem bitmap.&n;&t; * We look for the first area which is at least&n;&t; * 128kB in length (128kB is enough for a bitmap&n;&t; * for 4GB of memory, using 4kB pages), plus 1 page&n;&t; * (in case the address isn&squot;t page-aligned).&n;&t; */
id|start
op_assign
l_int|0
suffix:semicolon
id|size
op_assign
l_int|0
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
id|phys_avail.n_regions
suffix:semicolon
op_increment
id|i
)paren
(brace
r_int
r_int
id|a
op_assign
id|phys_avail.regions
(braket
id|i
)braket
dot
id|address
suffix:semicolon
r_int
r_int
id|s
op_assign
id|phys_avail.regions
(braket
id|i
)braket
dot
id|size
suffix:semicolon
r_if
c_cond
(paren
id|s
op_le
id|size
)paren
r_continue
suffix:semicolon
id|start
op_assign
id|a
suffix:semicolon
id|size
op_assign
id|s
suffix:semicolon
r_if
c_cond
(paren
id|s
op_ge
l_int|33
op_star
id|PAGE_SIZE
)paren
r_break
suffix:semicolon
)brace
id|start
op_assign
id|PAGE_ALIGN
c_func
(paren
id|start
)paren
suffix:semicolon
id|min_low_pfn
op_assign
id|start
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|max_low_pfn
op_assign
(paren
id|PPC_MEMSTART
op_plus
id|total_lowmem
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|max_pfn
op_assign
(paren
id|PPC_MEMSTART
op_plus
id|total_memory
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|boot_mapsize
op_assign
id|init_bootmem_node
c_func
(paren
op_amp
id|contig_page_data
comma
id|min_low_pfn
comma
id|PPC_MEMSTART
op_rshift
id|PAGE_SHIFT
comma
id|max_low_pfn
)paren
suffix:semicolon
multiline_comment|/* remove the bootmem bitmap from the available memory */
id|mem_pieces_remove
c_func
(paren
op_amp
id|phys_avail
comma
id|start
comma
id|boot_mapsize
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* add everything in phys_avail into the bootmem map */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|phys_avail.n_regions
suffix:semicolon
op_increment
id|i
)paren
id|free_bootmem
c_func
(paren
id|phys_avail.regions
(braket
id|i
)braket
dot
id|address
comma
id|phys_avail.regions
(braket
id|i
)braket
dot
id|size
)paren
suffix:semicolon
id|init_bootmem_done
op_assign
l_int|1
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
macro_line|#ifdef CONFIG_HIGHMEM
id|map_page
c_func
(paren
id|PKMAP_BASE
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* XXX gross */
id|pkmap_page_table
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmd_offset
c_func
(paren
id|pgd_offset_k
(paren
id|PKMAP_BASE
)paren
comma
id|PKMAP_BASE
)paren
comma
id|PKMAP_BASE
)paren
suffix:semicolon
id|map_page
c_func
(paren
id|KMAP_FIX_BEGIN
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* XXX gross */
id|kmap_pte
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmd_offset
c_func
(paren
id|pgd_offset_k
(paren
id|KMAP_FIX_BEGIN
)paren
comma
id|KMAP_FIX_BEGIN
)paren
comma
id|KMAP_FIX_BEGIN
)paren
suffix:semicolon
id|kmap_prot
op_assign
id|PAGE_KERNEL
suffix:semicolon
macro_line|#endif /* CONFIG_HIGHMEM */
multiline_comment|/*&n;&t; * All pages are DMA-able so we put them all in the DMA zone.&n;&t; */
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
id|total_lowmem
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
macro_line|#ifdef CONFIG_HIGHMEM
id|zones_size
(braket
id|ZONE_HIGHMEM
)braket
op_assign
(paren
id|total_memory
op_minus
id|total_lowmem
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
macro_line|#endif /* CONFIG_HIGHMEM */
id|free_area_init
c_func
(paren
id|zones_size
)paren
suffix:semicolon
)brace
DECL|function|mem_init
r_void
id|__init
id|mem_init
c_func
(paren
r_void
)paren
(brace
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
macro_line|#ifdef CONFIG_HIGHMEM
r_int
r_int
id|highmem_mapnr
suffix:semicolon
id|highmem_mapnr
op_assign
id|total_lowmem
op_rshift
id|PAGE_SHIFT
suffix:semicolon
macro_line|#endif /* CONFIG_HIGHMEM */
id|max_mapnr
op_assign
id|total_memory
op_rshift
id|PAGE_SHIFT
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
id|PPC_MEMSTART
op_plus
id|total_lowmem
)paren
suffix:semicolon
id|num_physpages
op_assign
id|max_mapnr
suffix:semicolon
multiline_comment|/* RAM is assumed contiguous */
id|totalram_pages
op_add_assign
id|free_all_bootmem
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
multiline_comment|/* if we are booted from BootX with an initial ramdisk,&n;&t;   make sure the ramdisk pages aren&squot;t reserved. */
r_if
c_cond
(paren
id|initrd_start
)paren
(brace
r_for
c_loop
(paren
id|addr
op_assign
id|initrd_start
suffix:semicolon
id|addr
OL
id|initrd_end
suffix:semicolon
id|addr
op_add_assign
id|PAGE_SIZE
)paren
id|ClearPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_BLK_DEV_INITRD */
macro_line|#ifdef CONFIG_PPC_OF
multiline_comment|/* mark the RTAS pages as reserved */
r_if
c_cond
(paren
id|rtas_data
)paren
r_for
c_loop
(paren
id|addr
op_assign
(paren
id|ulong
)paren
id|__va
c_func
(paren
id|rtas_data
)paren
suffix:semicolon
id|addr
OL
id|PAGE_ALIGN
c_func
(paren
(paren
id|ulong
)paren
id|__va
c_func
(paren
id|rtas_data
)paren
op_plus
id|rtas_size
)paren
suffix:semicolon
id|addr
op_add_assign
id|PAGE_SIZE
)paren
id|SetPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PPC_PMAC
r_if
c_cond
(paren
id|agp_special_page
)paren
id|SetPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|agp_special_page
)paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|sysmap
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
id|virt_to_page
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
id|PAGE_OFFSET
suffix:semicolon
id|addr
OL
(paren
r_int
r_int
)paren
id|high_memory
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
id|virt_to_page
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
(paren
id|ulong
)paren
id|klimit
)paren
id|datapages
op_increment
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_HIGHMEM
(brace
r_int
r_int
id|pfn
suffix:semicolon
r_for
c_loop
(paren
id|pfn
op_assign
id|highmem_mapnr
suffix:semicolon
id|pfn
OL
id|max_mapnr
suffix:semicolon
op_increment
id|pfn
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|mem_map
op_plus
id|pfn
suffix:semicolon
id|ClearPageReserved
c_func
(paren
id|page
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|PG_highmem
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
id|set_page_count
c_func
(paren
id|page
comma
l_int|1
)paren
suffix:semicolon
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|totalhigh_pages
op_increment
suffix:semicolon
)brace
id|totalram_pages
op_add_assign
id|totalhigh_pages
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_HIGHMEM */
id|printk
c_func
(paren
l_string|&quot;Memory: %luk available (%dk kernel code, %dk data, %dk init, %ldk highmem)&bslash;n&quot;
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
(paren
r_int
r_int
)paren
(paren
id|totalhigh_pages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sysmap
)paren
id|printk
c_func
(paren
l_string|&quot;System.map loaded at 0x%08x for debugger, size: %ld bytes&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|sysmap
comma
id|sysmap_size
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PPC_PMAC
r_if
c_cond
(paren
id|agp_special_page
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;AGP special page: 0x%08lx&bslash;n&quot;
comma
id|agp_special_page
)paren
suffix:semicolon
macro_line|#endif
id|mem_init_done
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Set phys_avail to the amount of physical memory,&n; * less the kernel text/data/bss.&n; */
r_void
id|__init
DECL|function|set_phys_avail
id|set_phys_avail
c_func
(paren
r_int
r_int
id|total_memory
)paren
(brace
r_int
r_int
id|kstart
comma
id|ksize
suffix:semicolon
multiline_comment|/*&n;&t; * Initially, available physical memory is equivalent to all&n;&t; * physical memory.&n;&t; */
id|phys_avail.regions
(braket
l_int|0
)braket
dot
id|address
op_assign
id|PPC_MEMSTART
suffix:semicolon
id|phys_avail.regions
(braket
l_int|0
)braket
dot
id|size
op_assign
id|total_memory
suffix:semicolon
id|phys_avail.n_regions
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Map out the kernel text/data/bss from the available physical&n;&t; * memory.&n;&t; */
id|kstart
op_assign
id|__pa
c_func
(paren
id|_stext
)paren
suffix:semicolon
multiline_comment|/* should be 0 */
id|ksize
op_assign
id|PAGE_ALIGN
c_func
(paren
id|klimit
op_minus
id|_stext
)paren
suffix:semicolon
id|mem_pieces_remove
c_func
(paren
op_amp
id|phys_avail
comma
id|kstart
comma
id|ksize
comma
l_int|0
)paren
suffix:semicolon
id|mem_pieces_remove
c_func
(paren
op_amp
id|phys_avail
comma
l_int|0
comma
l_int|0x4000
comma
l_int|0
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_BLK_DEV_INITRD)
multiline_comment|/* Remove the init RAM disk from the available memory. */
r_if
c_cond
(paren
id|initrd_start
)paren
(brace
id|mem_pieces_remove
c_func
(paren
op_amp
id|phys_avail
comma
id|__pa
c_func
(paren
id|initrd_start
)paren
comma
id|initrd_end
op_minus
id|initrd_start
comma
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_BLK_DEV_INITRD */
macro_line|#ifdef CONFIG_PPC_OF
multiline_comment|/* remove the RTAS pages from the available memory */
r_if
c_cond
(paren
id|rtas_data
)paren
id|mem_pieces_remove
c_func
(paren
op_amp
id|phys_avail
comma
id|rtas_data
comma
id|rtas_size
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* remove the sysmap pages from the available memory */
r_if
c_cond
(paren
id|sysmap
)paren
id|mem_pieces_remove
c_func
(paren
op_amp
id|phys_avail
comma
id|__pa
c_func
(paren
id|sysmap
)paren
comma
id|sysmap_size
comma
l_int|1
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PPC_PMAC
multiline_comment|/* Because of some uninorth weirdness, we need a page of&n;&t; * memory as high as possible (it must be outside of the&n;&t; * bus address seen as the AGP aperture). It will be used&n;&t; * by the r128 DRM driver&n;&t; *&n;&t; * FIXME: We need to make sure that page doesn&squot;t overlap any of the&bslash;&n;&t; * above. This could be done by improving mem_pieces_find to be able&n;&t; * to do a backward search from the end of the list.&n;&t; */
r_if
c_cond
(paren
id|_machine
op_eq
id|_MACH_Pmac
op_logical_and
id|find_devices
c_func
(paren
l_string|&quot;uni-north-agp&quot;
)paren
)paren
(brace
id|agp_special_page
op_assign
(paren
id|total_memory
op_minus
id|PAGE_SIZE
)paren
suffix:semicolon
id|mem_pieces_remove
c_func
(paren
op_amp
id|phys_avail
comma
id|agp_special_page
comma
id|PAGE_SIZE
comma
l_int|0
)paren
suffix:semicolon
id|agp_special_page
op_assign
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|agp_special_page
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PPC_PMAC */
)brace
multiline_comment|/* Mark some memory as reserved by removing it from phys_avail. */
DECL|function|reserve_phys_mem
r_void
id|__init
id|reserve_phys_mem
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
id|mem_pieces_remove
c_func
(paren
op_amp
id|phys_avail
comma
id|start
comma
id|size
comma
l_int|1
)paren
suffix:semicolon
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
DECL|function|flush_dcache_icache_page
r_void
id|flush_dcache_icache_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
macro_line|#ifdef CONFIG_BOOKE
id|__flush_dcache_icache
c_func
(paren
id|kmap
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
macro_line|#else
id|__flush_dcache_icache_phys
c_func
(paren
id|page_to_pfn
c_func
(paren
id|page
)paren
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
macro_line|#endif
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
comma
r_struct
id|page
op_star
id|pg
)paren
(brace
id|clear_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|PG_arch_1
comma
op_amp
id|pg-&gt;flags
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
comma
r_struct
id|page
op_star
id|pg
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
id|clear_bit
c_func
(paren
id|PG_arch_1
comma
op_amp
id|pg-&gt;flags
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
id|kmap
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
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
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
id|address
comma
id|pte_t
id|pte
)paren
(brace
multiline_comment|/* handle i-cache coherency */
r_int
r_int
id|pfn
op_assign
id|pte_pfn
c_func
(paren
id|pte
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pfn_valid
c_func
(paren
id|pfn
)paren
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|pfn_to_page
c_func
(paren
id|pfn
)paren
suffix:semicolon
r_if
c_cond
(paren
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
r_if
c_cond
(paren
id|vma-&gt;vm_mm
op_eq
id|current-&gt;active_mm
)paren
id|__flush_dcache_icache
c_func
(paren
(paren
r_void
op_star
)paren
id|address
)paren
suffix:semicolon
r_else
id|flush_dcache_icache_page
c_func
(paren
id|page
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
macro_line|#ifdef CONFIG_PPC_STD_MMU
multiline_comment|/* We only want HPTEs for linux PTEs that have _PAGE_ACCESSED set */
r_if
c_cond
(paren
id|Hash
op_ne
l_int|0
op_logical_and
id|pte_young
c_func
(paren
id|pte
)paren
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|mm
op_assign
(paren
id|address
OL
id|TASK_SIZE
)paren
ques
c_cond
id|vma-&gt;vm_mm
suffix:colon
op_amp
id|init_mm
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd_offset
c_func
(paren
id|mm
comma
id|address
)paren
comma
id|address
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
id|add_hash_page
c_func
(paren
id|mm-&gt;context
comma
id|address
comma
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
eof
