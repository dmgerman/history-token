multiline_comment|/*&n; * Procedures for interfacing to Open Firmware.&n; *&n; * Peter Bergner, IBM Corp.&t;June 2001.&n; * Copyright (C) 2001 Peter Bergner.&n; * &n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/lmb.h&gt;
macro_line|#include &lt;asm/abs_addr.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
DECL|variable|__initdata
r_struct
id|lmb
id|lmb
id|__initdata
suffix:semicolon
r_static
r_int
r_int
id|__init
DECL|function|lmb_addrs_overlap
id|lmb_addrs_overlap
c_func
(paren
r_int
r_int
id|base1
comma
r_int
r_int
id|size1
comma
r_int
r_int
id|base2
comma
r_int
r_int
id|size2
)paren
(brace
r_return
(paren
(paren
id|base1
OL
(paren
id|base2
op_plus
id|size2
)paren
)paren
op_logical_and
(paren
id|base2
OL
(paren
id|base1
op_plus
id|size1
)paren
)paren
)paren
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|lmb_addrs_adjacent
id|lmb_addrs_adjacent
c_func
(paren
r_int
r_int
id|base1
comma
r_int
r_int
id|size1
comma
r_int
r_int
id|base2
comma
r_int
r_int
id|size2
)paren
(brace
r_if
c_cond
(paren
id|base2
op_eq
id|base1
op_plus
id|size1
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|base1
op_eq
id|base2
op_plus
id|size2
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|lmb_regions_adjacent
id|lmb_regions_adjacent
c_func
(paren
r_struct
id|lmb_region
op_star
id|rgn
comma
r_int
r_int
id|r1
comma
r_int
r_int
id|r2
)paren
(brace
r_int
r_int
id|base1
op_assign
id|rgn-&gt;region
(braket
id|r1
)braket
dot
id|base
suffix:semicolon
r_int
r_int
id|size1
op_assign
id|rgn-&gt;region
(braket
id|r1
)braket
dot
id|size
suffix:semicolon
r_int
r_int
id|base2
op_assign
id|rgn-&gt;region
(braket
id|r2
)braket
dot
id|base
suffix:semicolon
r_int
r_int
id|size2
op_assign
id|rgn-&gt;region
(braket
id|r2
)braket
dot
id|size
suffix:semicolon
r_return
id|lmb_addrs_adjacent
c_func
(paren
id|base1
comma
id|size1
comma
id|base2
comma
id|size2
)paren
suffix:semicolon
)brace
multiline_comment|/* Assumption: base addr of region 1 &lt; base addr of region 2 */
r_static
r_void
id|__init
DECL|function|lmb_coalesce_regions
id|lmb_coalesce_regions
c_func
(paren
r_struct
id|lmb_region
op_star
id|rgn
comma
r_int
r_int
id|r1
comma
r_int
r_int
id|r2
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
id|rgn-&gt;region
(braket
id|r1
)braket
dot
id|size
op_add_assign
id|rgn-&gt;region
(braket
id|r2
)braket
dot
id|size
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|r2
suffix:semicolon
id|i
OL
id|rgn-&gt;cnt
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rgn-&gt;region
(braket
id|i
)braket
dot
id|base
op_assign
id|rgn-&gt;region
(braket
id|i
op_plus
l_int|1
)braket
dot
id|base
suffix:semicolon
id|rgn-&gt;region
(braket
id|i
)braket
dot
id|physbase
op_assign
id|rgn-&gt;region
(braket
id|i
op_plus
l_int|1
)braket
dot
id|physbase
suffix:semicolon
id|rgn-&gt;region
(braket
id|i
)braket
dot
id|size
op_assign
id|rgn-&gt;region
(braket
id|i
op_plus
l_int|1
)braket
dot
id|size
suffix:semicolon
)brace
id|rgn-&gt;cnt
op_decrement
suffix:semicolon
)brace
multiline_comment|/* This routine called with relocation disabled. */
r_void
id|__init
DECL|function|lmb_init
id|lmb_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|offset
op_assign
id|reloc_offset
c_func
(paren
)paren
suffix:semicolon
r_struct
id|lmb
op_star
id|_lmb
op_assign
id|PTRRELOC
c_func
(paren
op_amp
id|lmb
)paren
suffix:semicolon
multiline_comment|/* Create a dummy zero size LMB which will get coalesced away later.&n;&t; * This simplifies the lmb_add() code below...&n;&t; */
id|_lmb-&gt;memory.region
(braket
l_int|0
)braket
dot
id|base
op_assign
l_int|0
suffix:semicolon
id|_lmb-&gt;memory.region
(braket
l_int|0
)braket
dot
id|size
op_assign
l_int|0
suffix:semicolon
id|_lmb-&gt;memory.cnt
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Ditto. */
id|_lmb-&gt;reserved.region
(braket
l_int|0
)braket
dot
id|base
op_assign
l_int|0
suffix:semicolon
id|_lmb-&gt;reserved.region
(braket
l_int|0
)braket
dot
id|size
op_assign
l_int|0
suffix:semicolon
id|_lmb-&gt;reserved.cnt
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* This routine called with relocation disabled. */
r_void
id|__init
DECL|function|lmb_analyze
id|lmb_analyze
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
id|mem_size
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|size_mask
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|offset
op_assign
id|reloc_offset
c_func
(paren
)paren
suffix:semicolon
r_struct
id|lmb
op_star
id|_lmb
op_assign
id|PTRRELOC
c_func
(paren
op_amp
id|lmb
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MSCHUNKS
r_int
r_int
id|physbase
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|_lmb-&gt;memory.cnt
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|lmb_size
suffix:semicolon
id|lmb_size
op_assign
id|_lmb-&gt;memory.region
(braket
id|i
)braket
dot
id|size
suffix:semicolon
macro_line|#ifdef CONFIG_MSCHUNKS
id|_lmb-&gt;memory.region
(braket
id|i
)braket
dot
id|physbase
op_assign
id|physbase
suffix:semicolon
id|physbase
op_add_assign
id|lmb_size
suffix:semicolon
macro_line|#else
id|_lmb-&gt;memory.region
(braket
id|i
)braket
dot
id|physbase
op_assign
id|_lmb-&gt;memory.region
(braket
id|i
)braket
dot
id|base
suffix:semicolon
macro_line|#endif
id|mem_size
op_add_assign
id|lmb_size
suffix:semicolon
id|size_mask
op_or_assign
id|lmb_size
suffix:semicolon
)brace
id|_lmb-&gt;memory.size
op_assign
id|mem_size
suffix:semicolon
)brace
multiline_comment|/* This routine called with relocation disabled. */
r_static
r_int
id|__init
DECL|function|lmb_add_region
id|lmb_add_region
c_func
(paren
r_struct
id|lmb_region
op_star
id|rgn
comma
r_int
r_int
id|base
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|i
comma
id|coalesced
op_assign
l_int|0
suffix:semicolon
r_int
id|adjacent
suffix:semicolon
multiline_comment|/* First try and coalesce this LMB with another. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|rgn-&gt;cnt
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|rgnbase
op_assign
id|rgn-&gt;region
(braket
id|i
)braket
dot
id|base
suffix:semicolon
r_int
r_int
id|rgnsize
op_assign
id|rgn-&gt;region
(braket
id|i
)braket
dot
id|size
suffix:semicolon
id|adjacent
op_assign
id|lmb_addrs_adjacent
c_func
(paren
id|base
comma
id|size
comma
id|rgnbase
comma
id|rgnsize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|adjacent
OG
l_int|0
)paren
(brace
id|rgn-&gt;region
(braket
id|i
)braket
dot
id|base
op_sub_assign
id|size
suffix:semicolon
id|rgn-&gt;region
(braket
id|i
)braket
dot
id|physbase
op_sub_assign
id|size
suffix:semicolon
id|rgn-&gt;region
(braket
id|i
)braket
dot
id|size
op_add_assign
id|size
suffix:semicolon
id|coalesced
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|adjacent
OL
l_int|0
)paren
(brace
id|rgn-&gt;region
(braket
id|i
)braket
dot
id|size
op_add_assign
id|size
suffix:semicolon
id|coalesced
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|i
OL
id|rgn-&gt;cnt
op_minus
l_int|1
)paren
op_logical_and
id|lmb_regions_adjacent
c_func
(paren
id|rgn
comma
id|i
comma
id|i
op_plus
l_int|1
)paren
)paren
(brace
id|lmb_coalesce_regions
c_func
(paren
id|rgn
comma
id|i
comma
id|i
op_plus
l_int|1
)paren
suffix:semicolon
id|coalesced
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|coalesced
)paren
(brace
r_return
id|coalesced
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|rgn-&gt;cnt
op_ge
id|MAX_LMB_REGIONS
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Couldn&squot;t coalesce the LMB, so add it to the sorted table. */
r_for
c_loop
(paren
id|i
op_assign
id|rgn-&gt;cnt
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|base
OL
id|rgn-&gt;region
(braket
id|i
)braket
dot
id|base
)paren
(brace
id|rgn-&gt;region
(braket
id|i
op_plus
l_int|1
)braket
dot
id|base
op_assign
id|rgn-&gt;region
(braket
id|i
)braket
dot
id|base
suffix:semicolon
id|rgn-&gt;region
(braket
id|i
op_plus
l_int|1
)braket
dot
id|physbase
op_assign
id|rgn-&gt;region
(braket
id|i
)braket
dot
id|physbase
suffix:semicolon
id|rgn-&gt;region
(braket
id|i
op_plus
l_int|1
)braket
dot
id|size
op_assign
id|rgn-&gt;region
(braket
id|i
)braket
dot
id|size
suffix:semicolon
)brace
r_else
(brace
id|rgn-&gt;region
(braket
id|i
op_plus
l_int|1
)braket
dot
id|base
op_assign
id|base
suffix:semicolon
id|rgn-&gt;region
(braket
id|i
op_plus
l_int|1
)braket
dot
id|physbase
op_assign
id|lmb_abs_to_phys
c_func
(paren
id|base
)paren
suffix:semicolon
id|rgn-&gt;region
(braket
id|i
op_plus
l_int|1
)braket
dot
id|size
op_assign
id|size
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|rgn-&gt;cnt
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* This routine called with relocation disabled. */
r_int
id|__init
DECL|function|lmb_add
id|lmb_add
c_func
(paren
r_int
r_int
id|base
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|offset
op_assign
id|reloc_offset
c_func
(paren
)paren
suffix:semicolon
r_struct
id|lmb
op_star
id|_lmb
op_assign
id|PTRRELOC
c_func
(paren
op_amp
id|lmb
)paren
suffix:semicolon
r_struct
id|lmb_region
op_star
id|_rgn
op_assign
op_amp
(paren
id|_lmb-&gt;memory
)paren
suffix:semicolon
multiline_comment|/* On pSeries LPAR systems, the first LMB is our RMO region. */
r_if
c_cond
(paren
id|base
op_eq
l_int|0
)paren
id|_lmb-&gt;rmo_size
op_assign
id|size
suffix:semicolon
r_return
id|lmb_add_region
c_func
(paren
id|_rgn
comma
id|base
comma
id|size
)paren
suffix:semicolon
)brace
r_int
id|__init
DECL|function|lmb_reserve
id|lmb_reserve
c_func
(paren
r_int
r_int
id|base
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|offset
op_assign
id|reloc_offset
c_func
(paren
)paren
suffix:semicolon
r_struct
id|lmb
op_star
id|_lmb
op_assign
id|PTRRELOC
c_func
(paren
op_amp
id|lmb
)paren
suffix:semicolon
r_struct
id|lmb_region
op_star
id|_rgn
op_assign
op_amp
(paren
id|_lmb-&gt;reserved
)paren
suffix:semicolon
r_return
id|lmb_add_region
c_func
(paren
id|_rgn
comma
id|base
comma
id|size
)paren
suffix:semicolon
)brace
r_int
id|__init
DECL|function|lmb_overlaps_region
id|lmb_overlaps_region
c_func
(paren
r_struct
id|lmb_region
op_star
id|rgn
comma
r_int
r_int
id|base
comma
r_int
r_int
id|size
)paren
(brace
r_int
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
id|rgn-&gt;cnt
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|rgnbase
op_assign
id|rgn-&gt;region
(braket
id|i
)braket
dot
id|base
suffix:semicolon
r_int
r_int
id|rgnsize
op_assign
id|rgn-&gt;region
(braket
id|i
)braket
dot
id|size
suffix:semicolon
r_if
c_cond
(paren
id|lmb_addrs_overlap
c_func
(paren
id|base
comma
id|size
comma
id|rgnbase
comma
id|rgnsize
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
r_return
(paren
id|i
OL
id|rgn-&gt;cnt
)paren
ques
c_cond
id|i
suffix:colon
op_minus
l_int|1
suffix:semicolon
)brace
r_int
r_int
id|__init
DECL|function|lmb_alloc
id|lmb_alloc
c_func
(paren
r_int
r_int
id|size
comma
r_int
r_int
id|align
)paren
(brace
r_return
id|lmb_alloc_base
c_func
(paren
id|size
comma
id|align
comma
id|LMB_ALLOC_ANYWHERE
)paren
suffix:semicolon
)brace
r_int
r_int
id|__init
DECL|function|lmb_alloc_base
id|lmb_alloc_base
c_func
(paren
r_int
r_int
id|size
comma
r_int
r_int
id|align
comma
r_int
r_int
id|max_addr
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_int
r_int
id|base
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|offset
op_assign
id|reloc_offset
c_func
(paren
)paren
suffix:semicolon
r_struct
id|lmb
op_star
id|_lmb
op_assign
id|PTRRELOC
c_func
(paren
op_amp
id|lmb
)paren
suffix:semicolon
r_struct
id|lmb_region
op_star
id|_mem
op_assign
op_amp
(paren
id|_lmb-&gt;memory
)paren
suffix:semicolon
r_struct
id|lmb_region
op_star
id|_rsv
op_assign
op_amp
(paren
id|_lmb-&gt;reserved
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|_mem-&gt;cnt
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_int
r_int
id|lmbbase
op_assign
id|_mem-&gt;region
(braket
id|i
)braket
dot
id|base
suffix:semicolon
r_int
r_int
id|lmbsize
op_assign
id|_mem-&gt;region
(braket
id|i
)braket
dot
id|size
suffix:semicolon
r_if
c_cond
(paren
id|max_addr
op_eq
id|LMB_ALLOC_ANYWHERE
)paren
id|base
op_assign
id|_ALIGN_DOWN
c_func
(paren
id|lmbbase
op_plus
id|lmbsize
op_minus
id|size
comma
id|align
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|lmbbase
OL
id|max_addr
)paren
id|base
op_assign
id|_ALIGN_DOWN
c_func
(paren
id|min
c_func
(paren
id|lmbbase
op_plus
id|lmbsize
comma
id|max_addr
)paren
op_minus
id|size
comma
id|align
)paren
suffix:semicolon
r_else
r_continue
suffix:semicolon
r_while
c_loop
(paren
(paren
id|lmbbase
op_le
id|base
)paren
op_logical_and
(paren
(paren
id|j
op_assign
id|lmb_overlaps_region
c_func
(paren
id|_rsv
comma
id|base
comma
id|size
)paren
)paren
op_ge
l_int|0
)paren
)paren
(brace
id|base
op_assign
id|_ALIGN_DOWN
c_func
(paren
id|_rsv-&gt;region
(braket
id|j
)braket
dot
id|base
op_minus
id|size
comma
id|align
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|base
op_ne
l_int|0
)paren
op_logical_and
(paren
id|lmbbase
op_le
id|base
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|lmb_add_region
c_func
(paren
id|_rsv
comma
id|base
comma
id|size
)paren
suffix:semicolon
r_return
id|base
suffix:semicolon
)brace
r_int
r_int
id|__init
DECL|function|lmb_phys_mem_size
id|lmb_phys_mem_size
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|offset
op_assign
id|reloc_offset
c_func
(paren
)paren
suffix:semicolon
r_struct
id|lmb
op_star
id|_lmb
op_assign
id|PTRRELOC
c_func
(paren
op_amp
id|lmb
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MSCHUNKS
r_return
id|_lmb-&gt;memory.size
suffix:semicolon
macro_line|#else
r_struct
id|lmb_region
op_star
id|_mem
op_assign
op_amp
(paren
id|_lmb-&gt;memory
)paren
suffix:semicolon
r_int
r_int
id|total
op_assign
l_int|0
suffix:semicolon
r_int
id|i
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
id|_mem-&gt;cnt
suffix:semicolon
id|i
op_increment
)paren
id|total
op_add_assign
id|_mem-&gt;region
(braket
id|i
)braket
dot
id|size
suffix:semicolon
r_return
id|total
suffix:semicolon
macro_line|#endif /* CONFIG_MSCHUNKS */
)brace
r_int
r_int
id|__init
DECL|function|lmb_end_of_DRAM
id|lmb_end_of_DRAM
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|offset
op_assign
id|reloc_offset
c_func
(paren
)paren
suffix:semicolon
r_struct
id|lmb
op_star
id|_lmb
op_assign
id|PTRRELOC
c_func
(paren
op_amp
id|lmb
)paren
suffix:semicolon
r_struct
id|lmb_region
op_star
id|_mem
op_assign
op_amp
(paren
id|_lmb-&gt;memory
)paren
suffix:semicolon
r_int
id|idx
op_assign
id|_mem-&gt;cnt
op_minus
l_int|1
suffix:semicolon
macro_line|#ifdef CONFIG_MSCHUNKS
r_return
(paren
id|_mem-&gt;region
(braket
id|idx
)braket
dot
id|physbase
op_plus
id|_mem-&gt;region
(braket
id|idx
)braket
dot
id|size
)paren
suffix:semicolon
macro_line|#else
r_return
(paren
id|_mem-&gt;region
(braket
id|idx
)braket
dot
id|base
op_plus
id|_mem-&gt;region
(braket
id|idx
)braket
dot
id|size
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_MSCHUNKS */
r_return
l_int|0
suffix:semicolon
)brace
r_int
r_int
id|__init
DECL|function|lmb_abs_to_phys
id|lmb_abs_to_phys
c_func
(paren
r_int
r_int
id|aa
)paren
(brace
r_int
r_int
id|i
comma
id|pa
op_assign
id|aa
suffix:semicolon
r_int
r_int
id|offset
op_assign
id|reloc_offset
c_func
(paren
)paren
suffix:semicolon
r_struct
id|lmb
op_star
id|_lmb
op_assign
id|PTRRELOC
c_func
(paren
op_amp
id|lmb
)paren
suffix:semicolon
r_struct
id|lmb_region
op_star
id|_mem
op_assign
op_amp
(paren
id|_lmb-&gt;memory
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
id|_mem-&gt;cnt
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|lmbbase
op_assign
id|_mem-&gt;region
(braket
id|i
)braket
dot
id|base
suffix:semicolon
r_int
r_int
id|lmbsize
op_assign
id|_mem-&gt;region
(braket
id|i
)braket
dot
id|size
suffix:semicolon
r_if
c_cond
(paren
id|lmb_addrs_overlap
c_func
(paren
id|aa
comma
l_int|1
comma
id|lmbbase
comma
id|lmbsize
)paren
)paren
(brace
id|pa
op_assign
id|_mem-&gt;region
(braket
id|i
)braket
dot
id|physbase
op_plus
(paren
id|aa
op_minus
id|lmbbase
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|pa
suffix:semicolon
)brace
eof
