multiline_comment|/*&n; * This file contains the routines for handling the MMU on those&n; * PowerPC implementations where the MMU substantially follows the&n; * architecture specification.  This includes the 6xx, 7xx, 7xxx,&n; * 8260, and POWER3 implementations but excludes the 8xx and 4xx.&n; * Although the iSeries hardware does comply with the architecture&n; * specification, the need to work through the hypervisor makes&n; * things sufficiently different that it is handled elsewhere.&n; *  -- paulus&n; * &n; *  Derived from arch/ppc/mm/init.c:&n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *&n; *  Modifications by Paul Mackerras (PowerMac) (paulus@cs.anu.edu.au)&n; *  and Cort Dougan (PReP) (cort@cs.nmt.edu)&n; *    Copyright (C) 1996 Paul Mackerras&n; *  Amiga/APUS changes by Jesper Skov (jskov@cygnus.co.uk).&n; *&n; *  Derived from &quot;arch/i386/mm/init.c&quot;&n; *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &quot;mmu_decl.h&quot;
macro_line|#include &quot;mem_pieces.h&quot;
DECL|variable|Hash
DECL|variable|Hash_end
id|PTE
op_star
id|Hash
comma
op_star
id|Hash_end
suffix:semicolon
DECL|variable|Hash_size
DECL|variable|Hash_mask
r_int
r_int
id|Hash_size
comma
id|Hash_mask
suffix:semicolon
DECL|variable|_SDR1
r_int
r_int
id|_SDR1
suffix:semicolon
DECL|union|ubat
r_union
id|ubat
(brace
multiline_comment|/* BAT register values to be loaded */
DECL|member|bat
id|BAT
id|bat
suffix:semicolon
macro_line|#ifdef CONFIG_PPC64BRIDGE
DECL|member|word
id|u64
id|word
(braket
l_int|2
)braket
suffix:semicolon
macro_line|#else
DECL|member|word
id|u32
id|word
(braket
l_int|2
)braket
suffix:semicolon
macro_line|#endif
DECL|variable|BATS
)brace
id|BATS
(braket
l_int|4
)braket
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 4 pairs of IBAT, DBAT */
DECL|struct|batrange
r_struct
id|batrange
(brace
multiline_comment|/* stores address ranges mapped by BATs */
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
DECL|member|limit
r_int
r_int
id|limit
suffix:semicolon
DECL|member|phys
r_int
r_int
id|phys
suffix:semicolon
DECL|variable|bat_addrs
)brace
id|bat_addrs
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/*&n; * Return PA for this VA if it is mapped by a BAT, or 0&n; */
DECL|function|v_mapped_by_bats
r_int
r_int
id|v_mapped_by_bats
c_func
(paren
r_int
r_int
id|va
)paren
(brace
r_int
id|b
suffix:semicolon
r_for
c_loop
(paren
id|b
op_assign
l_int|0
suffix:semicolon
id|b
OL
l_int|4
suffix:semicolon
op_increment
id|b
)paren
r_if
c_cond
(paren
id|va
op_ge
id|bat_addrs
(braket
id|b
)braket
dot
id|start
op_logical_and
id|va
OL
id|bat_addrs
(braket
id|b
)braket
dot
id|limit
)paren
r_return
id|bat_addrs
(braket
id|b
)braket
dot
id|phys
op_plus
(paren
id|va
op_minus
id|bat_addrs
(braket
id|b
)braket
dot
id|start
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Return VA for a given PA or 0 if not mapped&n; */
DECL|function|p_mapped_by_bats
r_int
r_int
id|p_mapped_by_bats
c_func
(paren
r_int
r_int
id|pa
)paren
(brace
r_int
id|b
suffix:semicolon
r_for
c_loop
(paren
id|b
op_assign
l_int|0
suffix:semicolon
id|b
OL
l_int|4
suffix:semicolon
op_increment
id|b
)paren
r_if
c_cond
(paren
id|pa
op_ge
id|bat_addrs
(braket
id|b
)braket
dot
id|phys
op_logical_and
id|pa
OL
(paren
id|bat_addrs
(braket
id|b
)braket
dot
id|limit
op_minus
id|bat_addrs
(braket
id|b
)braket
dot
id|start
)paren
op_plus
id|bat_addrs
(braket
id|b
)braket
dot
id|phys
)paren
r_return
id|bat_addrs
(braket
id|b
)braket
dot
id|start
op_plus
(paren
id|pa
op_minus
id|bat_addrs
(braket
id|b
)braket
dot
id|phys
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mmu_mapin_ram
r_int
r_int
id|__init
id|mmu_mapin_ram
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|tot
comma
id|bl
comma
id|done
suffix:semicolon
r_int
r_int
id|max_size
op_assign
(paren
l_int|256
op_lshift
l_int|20
)paren
suffix:semicolon
r_int
r_int
id|align
suffix:semicolon
r_if
c_cond
(paren
id|__map_without_bats
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Set up BAT2 and if necessary BAT3 to cover RAM. */
multiline_comment|/* Make sure we don&squot;t map a block larger than the&n;&t;   smallest alignment of the physical address. */
multiline_comment|/* alignment of PPC_MEMSTART */
id|align
op_assign
op_complement
(paren
id|PPC_MEMSTART
op_minus
l_int|1
)paren
op_amp
id|PPC_MEMSTART
suffix:semicolon
multiline_comment|/* set BAT block size to MIN(max_size, align) */
r_if
c_cond
(paren
id|align
op_logical_and
id|align
OL
id|max_size
)paren
id|max_size
op_assign
id|align
suffix:semicolon
id|tot
op_assign
id|total_lowmem
suffix:semicolon
r_for
c_loop
(paren
id|bl
op_assign
l_int|128
op_lshift
l_int|10
suffix:semicolon
id|bl
OL
id|max_size
suffix:semicolon
id|bl
op_lshift_assign
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|bl
op_star
l_int|2
OG
id|tot
)paren
r_break
suffix:semicolon
)brace
id|setbat
c_func
(paren
l_int|2
comma
id|KERNELBASE
comma
id|PPC_MEMSTART
comma
id|bl
comma
id|_PAGE_KERNEL
)paren
suffix:semicolon
id|done
op_assign
(paren
r_int
r_int
)paren
id|bat_addrs
(braket
l_int|2
)braket
dot
id|limit
op_minus
id|KERNELBASE
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|done
OL
id|tot
)paren
op_logical_and
op_logical_neg
id|bat_addrs
(braket
l_int|3
)braket
dot
id|limit
)paren
(brace
multiline_comment|/* use BAT3 to cover a bit more */
id|tot
op_sub_assign
id|done
suffix:semicolon
r_for
c_loop
(paren
id|bl
op_assign
l_int|128
op_lshift
l_int|10
suffix:semicolon
id|bl
OL
id|max_size
suffix:semicolon
id|bl
op_lshift_assign
l_int|1
)paren
r_if
c_cond
(paren
id|bl
op_star
l_int|2
OG
id|tot
)paren
r_break
suffix:semicolon
id|setbat
c_func
(paren
l_int|3
comma
id|KERNELBASE
op_plus
id|done
comma
id|PPC_MEMSTART
op_plus
id|done
comma
id|bl
comma
id|_PAGE_KERNEL
)paren
suffix:semicolon
id|done
op_assign
(paren
r_int
r_int
)paren
id|bat_addrs
(braket
l_int|3
)braket
dot
id|limit
op_minus
id|KERNELBASE
op_plus
l_int|1
suffix:semicolon
)brace
r_return
id|done
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up one of the I/D BAT (block address translation) register pairs.&n; * The parameters are not checked; in particular size must be a power&n; * of 2 between 128k and 256M.&n; */
DECL|function|setbat
r_void
id|__init
id|setbat
c_func
(paren
r_int
id|index
comma
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
r_int
id|flags
)paren
(brace
r_int
r_int
id|bl
suffix:semicolon
r_int
id|wimgxpp
suffix:semicolon
r_union
id|ubat
op_star
id|bat
op_assign
id|BATS
(braket
id|index
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|_PAGE_NO_CACHE
)paren
op_eq
l_int|0
)paren
id|flags
op_or_assign
id|_PAGE_COHERENT
suffix:semicolon
macro_line|#endif
id|bl
op_assign
(paren
id|size
op_rshift
l_int|17
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|PVR_VER
c_func
(paren
id|mfspr
c_func
(paren
id|PVR
)paren
)paren
op_ne
l_int|1
)paren
(brace
multiline_comment|/* 603, 604, etc. */
multiline_comment|/* Do DBAT first */
id|wimgxpp
op_assign
id|flags
op_amp
(paren
id|_PAGE_WRITETHRU
op_or
id|_PAGE_NO_CACHE
op_or
id|_PAGE_COHERENT
op_or
id|_PAGE_GUARDED
)paren
suffix:semicolon
id|wimgxpp
op_or_assign
(paren
id|flags
op_amp
id|_PAGE_RW
)paren
ques
c_cond
id|BPP_RW
suffix:colon
id|BPP_RX
suffix:semicolon
id|bat
(braket
l_int|1
)braket
dot
id|word
(braket
l_int|0
)braket
op_assign
id|virt
op_or
(paren
id|bl
op_lshift
l_int|2
)paren
op_or
l_int|2
suffix:semicolon
multiline_comment|/* Vs=1, Vp=0 */
id|bat
(braket
l_int|1
)braket
dot
id|word
(braket
l_int|1
)braket
op_assign
id|phys
op_or
id|wimgxpp
suffix:semicolon
macro_line|#ifndef CONFIG_KGDB /* want user access for breakpoints */
r_if
c_cond
(paren
id|flags
op_amp
id|_PAGE_USER
)paren
macro_line|#endif
id|bat
(braket
l_int|1
)braket
dot
id|bat.batu.vp
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|_PAGE_GUARDED
)paren
(brace
multiline_comment|/* G bit must be zero in IBATs */
id|bat
(braket
l_int|0
)braket
dot
id|word
(braket
l_int|0
)braket
op_assign
id|bat
(braket
l_int|0
)braket
dot
id|word
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* make IBAT same as DBAT */
id|bat
(braket
l_int|0
)braket
op_assign
id|bat
(braket
l_int|1
)braket
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* 601 cpu */
r_if
c_cond
(paren
id|bl
OG
id|BL_8M
)paren
id|bl
op_assign
id|BL_8M
suffix:semicolon
id|wimgxpp
op_assign
id|flags
op_amp
(paren
id|_PAGE_WRITETHRU
op_or
id|_PAGE_NO_CACHE
op_or
id|_PAGE_COHERENT
)paren
suffix:semicolon
id|wimgxpp
op_or_assign
(paren
id|flags
op_amp
id|_PAGE_RW
)paren
ques
c_cond
(paren
(paren
id|flags
op_amp
id|_PAGE_USER
)paren
ques
c_cond
id|PP_RWRW
suffix:colon
id|PP_RWXX
)paren
suffix:colon
id|PP_RXRX
suffix:semicolon
id|bat-&gt;word
(braket
l_int|0
)braket
op_assign
id|virt
op_or
id|wimgxpp
op_or
l_int|4
suffix:semicolon
multiline_comment|/* Ks=0, Ku=1 */
id|bat-&gt;word
(braket
l_int|1
)braket
op_assign
id|phys
op_or
id|bl
op_or
l_int|0x40
suffix:semicolon
multiline_comment|/* V=1 */
)brace
id|bat_addrs
(braket
id|index
)braket
dot
id|start
op_assign
id|virt
suffix:semicolon
id|bat_addrs
(braket
id|index
)braket
dot
id|limit
op_assign
id|virt
op_plus
(paren
(paren
id|bl
op_plus
l_int|1
)paren
op_lshift
l_int|17
)paren
op_minus
l_int|1
suffix:semicolon
id|bat_addrs
(braket
id|index
)braket
dot
id|phys
op_assign
id|phys
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize the hash table and patch the instructions in hashtable.S.&n; */
DECL|function|MMU_init_hw
r_void
id|__init
id|MMU_init_hw
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|hmask
comma
id|mb
comma
id|mb2
suffix:semicolon
r_int
r_int
id|n_hpteg
comma
id|lg_n_hpteg
suffix:semicolon
r_extern
r_int
r_int
id|hash_page_patch_A
(braket
)braket
suffix:semicolon
r_extern
r_int
r_int
id|hash_page_patch_B
(braket
)braket
comma
id|hash_page_patch_C
(braket
)braket
suffix:semicolon
r_extern
r_int
r_int
id|hash_page
(braket
)braket
suffix:semicolon
r_extern
r_int
r_int
id|flush_hash_patch_A
(braket
)braket
comma
id|flush_hash_patch_B
(braket
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cur_cpu_spec
(braket
l_int|0
)braket
op_member_access_from_pointer
id|cpu_features
op_amp
id|CPU_FTR_HPTE_TABLE
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * Put a blr (procedure return) instruction at the&n;&t;&t; * start of hash_page, since we can still get DSI&n;&t;&t; * exceptions on a 603.&n;&t;&t; */
id|hash_page
(braket
l_int|0
)braket
op_assign
l_int|0x4e800020
suffix:semicolon
id|flush_icache_range
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|hash_page
(braket
l_int|0
)braket
comma
(paren
r_int
r_int
)paren
op_amp
id|hash_page
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
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
l_string|&quot;hash:enter&quot;
comma
l_int|0x105
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PPC64BRIDGE
DECL|macro|LG_HPTEG_SIZE
mdefine_line|#define LG_HPTEG_SIZE&t;7&t;&t;/* 128 bytes per HPTEG */
DECL|macro|SDR1_LOW_BITS
mdefine_line|#define SDR1_LOW_BITS&t;(lg_n_hpteg - 11)
DECL|macro|MIN_N_HPTEG
mdefine_line|#define MIN_N_HPTEG&t;2048&t;&t;/* min 256kB hash table */
macro_line|#else
mdefine_line|#define LG_HPTEG_SIZE&t;6&t;&t;/* 64 bytes per HPTEG */
mdefine_line|#define SDR1_LOW_BITS&t;((n_hpteg - 1) &gt;&gt; 10)
mdefine_line|#define MIN_N_HPTEG&t;1024&t;&t;/* min 64kB hash table */
macro_line|#endif
multiline_comment|/*&n;&t; * Allow 1 HPTE (1/8 HPTEG) for each page of memory.&n;&t; * This is less than the recommended amount, but then&n;&t; * Linux ain&squot;t AIX.&n;&t; */
id|n_hpteg
op_assign
id|total_memory
op_div
(paren
id|PAGE_SIZE
op_star
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n_hpteg
OL
id|MIN_N_HPTEG
)paren
id|n_hpteg
op_assign
id|MIN_N_HPTEG
suffix:semicolon
id|lg_n_hpteg
op_assign
id|__ilog2
c_func
(paren
id|n_hpteg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n_hpteg
op_amp
(paren
id|n_hpteg
op_minus
l_int|1
)paren
)paren
(brace
op_increment
id|lg_n_hpteg
suffix:semicolon
multiline_comment|/* round up if not power of 2 */
id|n_hpteg
op_assign
l_int|1
op_lshift
id|lg_n_hpteg
suffix:semicolon
)brace
id|Hash_size
op_assign
id|n_hpteg
op_lshift
id|LG_HPTEG_SIZE
suffix:semicolon
id|Hash_mask
op_assign
id|n_hpteg
op_minus
l_int|1
suffix:semicolon
id|hmask
op_assign
id|Hash_mask
op_rshift
(paren
l_int|16
op_minus
id|LG_HPTEG_SIZE
)paren
suffix:semicolon
id|mb2
op_assign
id|mb
op_assign
l_int|32
op_minus
id|LG_HPTEG_SIZE
op_minus
id|lg_n_hpteg
suffix:semicolon
r_if
c_cond
(paren
id|lg_n_hpteg
OG
l_int|16
)paren
id|mb2
op_assign
l_int|16
op_minus
id|LG_HPTEG_SIZE
suffix:semicolon
multiline_comment|/*&n;&t; * Find some memory for the hash table.&n;&t; */
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
l_string|&quot;hash:find piece&quot;
comma
l_int|0x322
)paren
suffix:semicolon
id|Hash
op_assign
id|mem_pieces_find
c_func
(paren
id|Hash_size
comma
id|Hash_size
)paren
suffix:semicolon
id|cacheable_memzero
c_func
(paren
id|Hash
comma
id|Hash_size
)paren
suffix:semicolon
id|_SDR1
op_assign
id|__pa
c_func
(paren
id|Hash
)paren
op_or
id|SDR1_LOW_BITS
suffix:semicolon
id|Hash_end
op_assign
(paren
id|PTE
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|Hash
op_plus
id|Hash_size
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Total memory = %ldMB; using %ldkB for hash table (at %p)&bslash;n&quot;
comma
id|total_memory
op_rshift
l_int|20
comma
id|Hash_size
op_rshift
l_int|10
comma
id|Hash
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Patch up the instructions in hashtable.S:create_hpte&n;&t; */
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
l_string|&quot;hash:patch&quot;
comma
l_int|0x345
)paren
suffix:semicolon
id|hash_page_patch_A
(braket
l_int|0
)braket
op_assign
(paren
id|hash_page_patch_A
(braket
l_int|0
)braket
op_amp
op_complement
l_int|0xffff
)paren
op_or
(paren
(paren
r_int
r_int
)paren
(paren
id|Hash
)paren
op_rshift
l_int|16
)paren
suffix:semicolon
id|hash_page_patch_A
(braket
l_int|1
)braket
op_assign
(paren
id|hash_page_patch_A
(braket
l_int|1
)braket
op_amp
op_complement
l_int|0x7c0
)paren
op_or
(paren
id|mb
op_lshift
l_int|6
)paren
suffix:semicolon
id|hash_page_patch_A
(braket
l_int|2
)braket
op_assign
(paren
id|hash_page_patch_A
(braket
l_int|2
)braket
op_amp
op_complement
l_int|0x7c0
)paren
op_or
(paren
id|mb2
op_lshift
l_int|6
)paren
suffix:semicolon
id|hash_page_patch_B
(braket
l_int|0
)braket
op_assign
(paren
id|hash_page_patch_B
(braket
l_int|0
)braket
op_amp
op_complement
l_int|0xffff
)paren
op_or
id|hmask
suffix:semicolon
id|hash_page_patch_C
(braket
l_int|0
)braket
op_assign
(paren
id|hash_page_patch_C
(braket
l_int|0
)braket
op_amp
op_complement
l_int|0xffff
)paren
op_or
id|hmask
suffix:semicolon
multiline_comment|/*&n;&t; * Ensure that the locations we&squot;ve patched have been written&n;&t; * out from the data cache and invalidated in the instruction&n;&t; * cache, on those machines with split caches.&n;&t; */
id|flush_icache_range
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|hash_page_patch_A
(braket
l_int|0
)braket
comma
(paren
r_int
r_int
)paren
op_amp
id|hash_page_patch_C
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Patch up the instructions in hashtable.S:flush_hash_page&n;&t; */
id|flush_hash_patch_A
(braket
l_int|0
)braket
op_assign
(paren
id|flush_hash_patch_A
(braket
l_int|0
)braket
op_amp
op_complement
l_int|0xffff
)paren
op_or
(paren
(paren
r_int
r_int
)paren
(paren
id|Hash
)paren
op_rshift
l_int|16
)paren
suffix:semicolon
id|flush_hash_patch_A
(braket
l_int|1
)braket
op_assign
(paren
id|flush_hash_patch_A
(braket
l_int|1
)braket
op_amp
op_complement
l_int|0x7c0
)paren
op_or
(paren
id|mb
op_lshift
l_int|6
)paren
suffix:semicolon
id|flush_hash_patch_A
(braket
l_int|2
)braket
op_assign
(paren
id|flush_hash_patch_A
(braket
l_int|2
)braket
op_amp
op_complement
l_int|0x7c0
)paren
op_or
(paren
id|mb2
op_lshift
l_int|6
)paren
suffix:semicolon
id|flush_hash_patch_B
(braket
l_int|0
)braket
op_assign
(paren
id|flush_hash_patch_B
(braket
l_int|0
)braket
op_amp
op_complement
l_int|0xffff
)paren
op_or
id|hmask
suffix:semicolon
id|flush_icache_range
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|flush_hash_patch_A
(braket
l_int|0
)braket
comma
(paren
r_int
r_int
)paren
op_amp
id|flush_hash_patch_B
(braket
l_int|1
)braket
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
l_string|&quot;hash:done&quot;
comma
l_int|0x205
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
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
r_static
r_int
id|nopreload
suffix:semicolon
r_if
c_cond
(paren
id|Hash
op_eq
l_int|0
op_logical_or
id|nopreload
)paren
r_return
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
eof
