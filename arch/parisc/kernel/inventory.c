multiline_comment|/*&n; * inventory.c&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; * Copyright (c) 1999 The Puffin Group (David Kennedy and Alex deVries)&n; * Copyright (c) 2001 Matthew Wilcox for Hewlett-Packard&n; *&n; * These are the routines to discover what hardware exists in this box.&n; * This task is complicated by there being 3 different ways of&n; * performing an inventory, depending largely on the age of the box.&n; * The recommended way to do this is to check to see whether the machine&n; * is a `Snake&squot; first, then try System Map, then try PAT.  We try System&n; * Map before checking for a Snake -- this probably doesn&squot;t cause any&n; * problems, but...&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pdc.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/*&n;** Debug options&n;** DEBUG_PAT Dump details which PDC PAT provides about ranges/devices.&n;*/
DECL|macro|DEBUG_PAT
macro_line|#undef DEBUG_PAT
DECL|variable|pdc_type
r_int
id|pdc_type
op_assign
id|PDC_TYPE_ILLEGAL
suffix:semicolon
DECL|function|setup_pdc
r_void
id|__init
id|setup_pdc
c_func
(paren
r_void
)paren
(brace
r_int
id|status
suffix:semicolon
r_int
r_int
id|bus_id
suffix:semicolon
r_struct
id|pdc_system_map_mod_info
id|module_result
suffix:semicolon
r_struct
id|pdc_module_path
id|module_path
suffix:semicolon
r_struct
id|pdc_model
id|model
suffix:semicolon
macro_line|#ifdef __LP64__
r_struct
id|pdc_pat_cell_num
id|cell_info
suffix:semicolon
macro_line|#endif
multiline_comment|/* Determine the pdc &quot;type&quot; used on this machine */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Determining PDC firmware type: &quot;
)paren
suffix:semicolon
id|status
op_assign
id|pdc_system_map_find_mods
c_func
(paren
op_amp
id|module_result
comma
op_amp
id|module_path
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
id|PDC_OK
)paren
(brace
id|pdc_type
op_assign
id|PDC_TYPE_SYSTEM_MAP
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;System Map.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If the machine doesn&squot;t support PDC_SYSTEM_MAP then either it&n;&t; * is a pdc pat box, or it is an older box. All 64 bit capable&n;&t; * machines are either pdc pat boxes or they support PDC_SYSTEM_MAP.&n;&t; */
multiline_comment|/*&n;&t; * TODO: We should test for 64 bit capability and give a&n;&t; * clearer message.&n;&t; */
macro_line|#ifdef __LP64__
id|status
op_assign
id|pdc_pat_cell_get_number
c_func
(paren
op_amp
id|cell_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
id|PDC_OK
)paren
(brace
id|pdc_type
op_assign
id|PDC_TYPE_PAT
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;64 bit PAT.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Check the CPU&squot;s bus ID.  There&squot;s probably a better test.  */
id|status
op_assign
id|pdc_model_info
c_func
(paren
op_amp
id|model
)paren
suffix:semicolon
id|bus_id
op_assign
(paren
id|model.hversion
op_rshift
(paren
l_int|4
op_plus
l_int|7
)paren
)paren
op_amp
l_int|0x1f
suffix:semicolon
r_switch
c_cond
(paren
id|bus_id
)paren
(brace
r_case
l_int|0x4
suffix:colon
multiline_comment|/* 720, 730, 750, 735, 755 */
r_case
l_int|0x6
suffix:colon
multiline_comment|/* 705, 710 */
r_case
l_int|0x7
suffix:colon
multiline_comment|/* 715, 725 */
r_case
l_int|0x8
suffix:colon
multiline_comment|/* 745, 747, 742 */
r_case
l_int|0xA
suffix:colon
multiline_comment|/* 712 and similiar */
r_case
l_int|0xC
suffix:colon
multiline_comment|/* 715/64, at least */
id|pdc_type
op_assign
id|PDC_TYPE_SNAKE
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Snake.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Everything else */
id|printk
c_func
(paren
l_string|&quot;Unsupported.&bslash;n&quot;
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;If this is a 64-bit machine, please try a 64-bit kernel.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|macro|PDC_PAGE_ADJ_SHIFT
mdefine_line|#define PDC_PAGE_ADJ_SHIFT (PAGE_SHIFT - 12) /* pdc pages are always 4k */
r_static
r_void
id|__init
DECL|function|set_pmem_entry
id|set_pmem_entry
c_func
(paren
id|physmem_range_t
op_star
id|pmem_ptr
comma
r_int
r_int
id|start
comma
r_int
r_int
id|pages4k
)paren
(brace
multiline_comment|/* Rather than aligning and potentially throwing away&n;&t; * memory, we&squot;ll assume that any ranges are already&n;&t; * nicely aligned with any reasonable page size, and&n;&t; * panic if they are not (it&squot;s more likely that the&n;&t; * pdc info is bad in this case).&n;&t; */
r_if
c_cond
(paren
(paren
(paren
id|start
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_ne
l_int|0
)paren
op_logical_or
(paren
(paren
id|pages4k
op_amp
(paren
(paren
l_int|1UL
op_lshift
id|PDC_PAGE_ADJ_SHIFT
)paren
op_minus
l_int|1
)paren
)paren
op_ne
l_int|0
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Memory range doesn&squot;t align with page size!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|pmem_ptr-&gt;start_pfn
op_assign
(paren
id|start
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|pmem_ptr-&gt;pages
op_assign
(paren
id|pages4k
op_rshift
id|PDC_PAGE_ADJ_SHIFT
)paren
suffix:semicolon
)brace
DECL|function|pagezero_memconfig
r_static
r_void
id|__init
id|pagezero_memconfig
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|npages
suffix:semicolon
multiline_comment|/* Use the 32 bit information from page zero to create a single&n;&t; * entry in the pmem_ranges[] table.&n;&t; *&n;&t; * We currently don&squot;t support machines with contiguous memory&n;&t; * &gt;= 4 Gb, who report that memory using 64 bit only fields&n;&t; * on page zero. It&squot;s not worth doing until it can be tested,&n;&t; * and it is not clear we can support those machines for other&n;&t; * reasons.&n;&t; *&n;&t; * If that support is done in the future, this is where it&n;&t; * should be done.&n;&t; */
id|npages
op_assign
(paren
id|PAGE_ALIGN
c_func
(paren
id|PAGE0-&gt;imm_max_mem
)paren
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|set_pmem_entry
c_func
(paren
id|pmem_ranges
comma
l_int|0UL
comma
id|npages
)paren
suffix:semicolon
id|npmem_ranges
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#ifdef __LP64__
multiline_comment|/* All of the PDC PAT specific code is 64-bit only */
multiline_comment|/*&n;**  The module object is filled via PDC_PAT_CELL[Return Cell Module].&n;**  If a module is found, register module will get the IODC bytes via&n;**  pdc_iodc_read() using the PA view of conf_base_addr for the hpa parameter.&n;**&n;**  The IO view can be used by PDC_PAT_CELL[Return Cell Module]&n;**  only for SBAs and LBAs.  This view will cause an invalid&n;**  argument error for all other cell module types.&n;**&n;*/
r_static
r_int
id|__init
DECL|function|pat_query_module
id|pat_query_module
c_func
(paren
id|ulong
id|pcell_loc
comma
id|ulong
id|mod_index
)paren
(brace
id|pdc_pat_cell_mod_maddr_block_t
id|pa_pdc_cell
suffix:semicolon
r_int
r_int
id|bytecnt
suffix:semicolon
r_int
r_int
id|temp
suffix:semicolon
multiline_comment|/* 64-bit scratch value */
r_int
id|status
suffix:semicolon
multiline_comment|/* PDC return value status */
r_struct
id|parisc_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* return cell module (PA or Processor view) */
id|status
op_assign
id|pdc_pat_cell_module
c_func
(paren
op_amp
id|bytecnt
comma
id|pcell_loc
comma
id|mod_index
comma
id|PA_VIEW
comma
op_amp
id|pa_pdc_cell
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
id|PDC_OK
)paren
(brace
multiline_comment|/* no more cell modules or error */
r_return
id|status
suffix:semicolon
)brace
id|temp
op_assign
id|pa_pdc_cell.cba
suffix:semicolon
id|dev
op_assign
id|alloc_pa_dev
c_func
(paren
id|PAT_GET_CBA
c_func
(paren
id|temp
)paren
comma
op_amp
id|pa_pdc_cell.mod_path
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
r_return
id|PDC_NE_MOD
suffix:semicolon
)brace
multiline_comment|/* alloc_pa_dev sets dev-&gt;hpa */
multiline_comment|/*&n;&t;** save parameters in the parisc_device&n;&t;** (The idea being the device driver will call pdc_pat_cell_module()&n;&t;** and store the results in its own data structure.)&n;&t;*/
id|dev-&gt;pcell_loc
op_assign
id|pcell_loc
suffix:semicolon
id|dev-&gt;mod_index
op_assign
id|mod_index
suffix:semicolon
multiline_comment|/* save generic info returned from the call */
multiline_comment|/* REVISIT: who is the consumer of this? not sure yet... */
id|dev-&gt;mod_info
op_assign
id|pa_pdc_cell.mod_info
suffix:semicolon
multiline_comment|/* pass to PAT_GET_ENTITY() */
id|dev-&gt;pmod_loc
op_assign
id|pa_pdc_cell.mod_location
suffix:semicolon
id|register_parisc_device
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* advertise device */
macro_line|#ifdef DEBUG_PAT
id|pdc_pat_cell_mod_maddr_block_t
id|io_pdc_cell
suffix:semicolon
multiline_comment|/* dump what we see so far... */
r_switch
c_cond
(paren
id|PAT_GET_ENTITY
c_func
(paren
id|dev-&gt;mod_info
)paren
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_case
id|PAT_ENTITY_PROC
suffix:colon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;PAT_ENTITY_PROC: id_eid 0x%lx&bslash;n&quot;
comma
id|pa_pdc_cell.mod
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PAT_ENTITY_MEM
suffix:colon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;PAT_ENTITY_MEM: amount 0x%lx min_gni_base 0x%lx min_gni_len 0x%lx&bslash;n&quot;
comma
id|pa_pdc_cell.mod
(braket
l_int|0
)braket
comma
id|pa_pdc_cell.mod
(braket
l_int|1
)braket
comma
id|pa_pdc_cell.mod
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PAT_ENTITY_CA
suffix:colon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;PAT_ENTITY_CA: %ld&bslash;n&quot;
comma
id|pcell_loc
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PAT_ENTITY_PBC
suffix:colon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;PAT_ENTITY_PBC: &quot;
)paren
suffix:semicolon
r_goto
id|print_ranges
suffix:semicolon
r_case
id|PAT_ENTITY_SBA
suffix:colon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;PAT_ENTITY_SBA: &quot;
)paren
suffix:semicolon
r_goto
id|print_ranges
suffix:semicolon
r_case
id|PAT_ENTITY_LBA
suffix:colon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;PAT_ENTITY_LBA: &quot;
)paren
suffix:semicolon
id|print_ranges
suffix:colon
id|pdc_pat_cell_module
c_func
(paren
op_amp
id|bytecnt
comma
id|pcell_loc
comma
id|mod_index
comma
id|IO_VIEW
comma
op_amp
id|io_pdc_cell
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ranges %ld&bslash;n&quot;
comma
id|pa_pdc_cell.mod
(braket
l_int|1
)braket
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
id|pa_pdc_cell.mod
(braket
l_int|1
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;  PA_VIEW %ld: 0x%016lx 0x%016lx 0x%016lx&bslash;n&quot;
comma
id|i
comma
id|pa_pdc_cell.mod
(braket
l_int|2
op_plus
id|i
op_star
l_int|3
)braket
comma
multiline_comment|/* type */
id|pa_pdc_cell.mod
(braket
l_int|3
op_plus
id|i
op_star
l_int|3
)braket
comma
multiline_comment|/* start */
id|pa_pdc_cell.mod
(braket
l_int|4
op_plus
id|i
op_star
l_int|3
)braket
)paren
suffix:semicolon
multiline_comment|/* finish (ie end) */
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;  IO_VIEW %ld: 0x%016lx 0x%016lx 0x%016lx&bslash;n&quot;
comma
id|i
comma
id|io_pdc_cell.mod
(braket
l_int|2
op_plus
id|i
op_star
l_int|3
)braket
comma
multiline_comment|/* type */
id|io_pdc_cell.mod
(braket
l_int|3
op_plus
id|i
op_star
l_int|3
)braket
comma
multiline_comment|/* start */
id|io_pdc_cell.mod
(braket
l_int|4
op_plus
id|i
op_star
l_int|3
)braket
)paren
suffix:semicolon
multiline_comment|/* finish (ie end) */
)brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#endif /* DEBUG_PAT */
r_return
id|PDC_OK
suffix:semicolon
)brace
multiline_comment|/* pat pdc can return information about a variety of different&n; * types of memory (e.g. firmware,i/o, etc) but we only care about&n; * the usable physical ram right now. Since the firmware specific&n; * information is allocated on the stack, we&squot;ll be generous, in&n; * case there is a lot of other information we don&squot;t care about.&n; */
DECL|macro|PAT_MAX_RANGES
mdefine_line|#define PAT_MAX_RANGES (4 * MAX_PHYSMEM_RANGES)
DECL|function|pat_memconfig
r_static
r_void
id|__init
id|pat_memconfig
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|actual_len
suffix:semicolon
r_struct
id|pdc_pat_pd_addr_map_entry
id|mem_table
(braket
id|PAT_MAX_RANGES
op_plus
l_int|1
)braket
suffix:semicolon
r_struct
id|pdc_pat_pd_addr_map_entry
op_star
id|mtbl_ptr
suffix:semicolon
id|physmem_range_t
op_star
id|pmem_ptr
suffix:semicolon
r_int
id|status
suffix:semicolon
r_int
id|entries
suffix:semicolon
r_int
r_int
id|length
suffix:semicolon
r_int
id|i
suffix:semicolon
id|length
op_assign
(paren
id|PAT_MAX_RANGES
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_struct
id|pdc_pat_pd_addr_map_entry
)paren
suffix:semicolon
id|status
op_assign
id|pdc_pat_pd_get_addr_map
c_func
(paren
op_amp
id|actual_len
comma
id|mem_table
comma
id|length
comma
l_int|0L
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_ne
id|PDC_OK
)paren
op_logical_or
(paren
(paren
id|actual_len
op_mod
r_sizeof
(paren
r_struct
id|pdc_pat_pd_addr_map_entry
)paren
)paren
op_ne
l_int|0
)paren
)paren
(brace
multiline_comment|/* The above pdc call shouldn&squot;t fail, but, just in&n;&t;&t; * case, just use the PAGE0 info.&n;&t;&t; */
id|printk
c_func
(paren
l_string|&quot;&bslash;n&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;WARNING! Could not get full memory configuration. &quot;
l_string|&quot;All memory may not be used!&bslash;n&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|pagezero_memconfig
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|entries
op_assign
id|actual_len
op_div
r_sizeof
(paren
r_struct
id|pdc_pat_pd_addr_map_entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entries
OG
id|PAT_MAX_RANGES
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;This Machine has more memory ranges than we support!&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Some memory may not be used!&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Copy information into the firmware independent pmem_ranges&n;&t; * array, skipping types we don&squot;t care about. Notice we said&n;&t; * &quot;may&quot; above. We&squot;ll use all the entries that were returned.&n;&t; */
id|npmem_ranges
op_assign
l_int|0
suffix:semicolon
id|mtbl_ptr
op_assign
id|mem_table
suffix:semicolon
id|pmem_ptr
op_assign
id|pmem_ranges
suffix:semicolon
multiline_comment|/* Global firmware independent table */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|entries
suffix:semicolon
id|i
op_increment
comma
id|mtbl_ptr
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|mtbl_ptr-&gt;entry_type
op_ne
id|PAT_MEMORY_DESCRIPTOR
)paren
op_logical_or
(paren
id|mtbl_ptr-&gt;memory_type
op_ne
id|PAT_MEMTYPE_MEMORY
)paren
op_logical_or
(paren
id|mtbl_ptr-&gt;pages
op_eq
l_int|0
)paren
op_logical_or
(paren
(paren
id|mtbl_ptr-&gt;memory_usage
op_ne
id|PAT_MEMUSE_GENERAL
)paren
op_logical_and
(paren
id|mtbl_ptr-&gt;memory_usage
op_ne
id|PAT_MEMUSE_GI
)paren
op_logical_and
(paren
id|mtbl_ptr-&gt;memory_usage
op_ne
id|PAT_MEMUSE_GNI
)paren
)paren
)paren
(brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|npmem_ranges
op_eq
id|MAX_PHYSMEM_RANGES
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;This Machine has more memory ranges than we support!&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Some memory will not be used!&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|set_pmem_entry
c_func
(paren
id|pmem_ptr
op_increment
comma
id|mtbl_ptr-&gt;paddr
comma
id|mtbl_ptr-&gt;pages
)paren
suffix:semicolon
id|npmem_ranges
op_increment
suffix:semicolon
)brace
)brace
DECL|function|pat_inventory
r_static
r_int
id|__init
id|pat_inventory
c_func
(paren
r_void
)paren
(brace
r_int
id|status
suffix:semicolon
id|ulong
id|mod_index
op_assign
l_int|0
suffix:semicolon
r_struct
id|pdc_pat_cell_num
id|cell_info
suffix:semicolon
multiline_comment|/*&n;&t;** Note:  Prelude (and it&squot;s successors: Lclass, A400/500) only&n;&t;**        implement PDC_PAT_CELL sub-options 0 and 2.&n;&t;*/
id|status
op_assign
id|pdc_pat_cell_get_number
c_func
(paren
op_amp
id|cell_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
id|PDC_OK
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_PAT
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;CELL_GET_NUMBER: 0x%lx 0x%lx&bslash;n&quot;
comma
id|cell_info.cell_num
comma
id|cell_info.cell_loc
)paren
suffix:semicolon
macro_line|#endif
r_while
c_loop
(paren
id|PDC_OK
op_eq
id|pat_query_module
c_func
(paren
id|cell_info.cell_loc
comma
id|mod_index
)paren
)paren
(brace
id|mod_index
op_increment
suffix:semicolon
)brace
r_return
id|mod_index
suffix:semicolon
)brace
multiline_comment|/* We only look for extended memory ranges on a 64 bit capable box */
DECL|function|sprockets_memconfig
r_static
r_void
id|__init
id|sprockets_memconfig
c_func
(paren
r_void
)paren
(brace
r_struct
id|pdc_memory_table_raddr
id|r_addr
suffix:semicolon
r_struct
id|pdc_memory_table
id|mem_table
(braket
id|MAX_PHYSMEM_RANGES
)braket
suffix:semicolon
r_struct
id|pdc_memory_table
op_star
id|mtbl_ptr
suffix:semicolon
id|physmem_range_t
op_star
id|pmem_ptr
suffix:semicolon
r_int
id|status
suffix:semicolon
r_int
id|entries
suffix:semicolon
r_int
id|i
suffix:semicolon
id|status
op_assign
id|pdc_mem_mem_table
c_func
(paren
op_amp
id|r_addr
comma
id|mem_table
comma
(paren
r_int
r_int
)paren
id|MAX_PHYSMEM_RANGES
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
id|PDC_OK
)paren
(brace
multiline_comment|/* The above pdc call only works on boxes with sprockets&n;&t;&t; * firmware (newer B,C,J class). Other non PAT PDC machines&n;&t;&t; * do support more than 3.75 Gb of memory, but we don&squot;t&n;&t;&t; * support them yet.&n;&t;&t; */
id|pagezero_memconfig
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|r_addr.entries_total
OG
id|MAX_PHYSMEM_RANGES
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;This Machine has more memory ranges than we support!&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Some memory will not be used!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|entries
op_assign
(paren
r_int
)paren
id|r_addr.entries_returned
suffix:semicolon
id|npmem_ranges
op_assign
l_int|0
suffix:semicolon
id|mtbl_ptr
op_assign
id|mem_table
suffix:semicolon
id|pmem_ptr
op_assign
id|pmem_ranges
suffix:semicolon
multiline_comment|/* Global firmware independent table */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|entries
suffix:semicolon
id|i
op_increment
comma
id|mtbl_ptr
op_increment
)paren
(brace
id|set_pmem_entry
c_func
(paren
id|pmem_ptr
op_increment
comma
id|mtbl_ptr-&gt;paddr
comma
id|mtbl_ptr-&gt;pages
)paren
suffix:semicolon
id|npmem_ranges
op_increment
suffix:semicolon
)brace
)brace
macro_line|#else   /* !__LP64__ */
DECL|macro|pat_inventory
mdefine_line|#define pat_inventory() do { } while (0)
DECL|macro|pat_memconfig
mdefine_line|#define pat_memconfig() do { } while (0)
DECL|macro|sprockets_memconfig
mdefine_line|#define sprockets_memconfig() pagezero_memconfig()
macro_line|#endif&t;/* !__LP64__ */
macro_line|#ifndef CONFIG_PA20
multiline_comment|/* Code to support Snake machines (7[2350], 7[235]5, 715/Scorpio) */
r_static
r_struct
id|parisc_device
op_star
id|__init
DECL|function|legacy_create_device
id|legacy_create_device
c_func
(paren
r_struct
id|pdc_memory_map
op_star
id|r_addr
comma
r_struct
id|pdc_module_path
op_star
id|module_path
)paren
(brace
r_struct
id|parisc_device
op_star
id|dev
suffix:semicolon
r_int
id|status
op_assign
id|pdc_mem_map_hpa
c_func
(paren
id|r_addr
comma
id|module_path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
id|PDC_OK
)paren
r_return
l_int|NULL
suffix:semicolon
id|dev
op_assign
id|alloc_pa_dev
c_func
(paren
id|r_addr-&gt;hpa
comma
op_amp
id|module_path-&gt;path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|register_parisc_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
multiline_comment|/**&n; * snake_inventory&n; *&n; * Before PDC_SYSTEM_MAP was invented, the PDC_MEM_MAP call was used.&n; * To use it, we initialise the mod_path.bc to 0xff and try all values of&n; * mod to get the HPA for the top-level devices.  Bus adapters may have&n; * sub-devices which are discovered by setting bc[5] to 0 and bc[4] to the&n; * module, then trying all possible functions.&n; */
DECL|function|snake_inventory
r_static
r_void
id|__init
id|snake_inventory
c_func
(paren
r_void
)paren
(brace
r_int
id|mod
suffix:semicolon
r_for
c_loop
(paren
id|mod
op_assign
l_int|0
suffix:semicolon
id|mod
OL
l_int|16
suffix:semicolon
id|mod
op_increment
)paren
(brace
r_struct
id|parisc_device
op_star
id|dev
suffix:semicolon
r_struct
id|pdc_module_path
id|module_path
suffix:semicolon
r_struct
id|pdc_memory_map
id|r_addr
suffix:semicolon
r_int
r_int
id|func
suffix:semicolon
id|memset
c_func
(paren
id|module_path.path.bc
comma
l_int|0xff
comma
l_int|6
)paren
suffix:semicolon
id|module_path.path.mod
op_assign
id|mod
suffix:semicolon
id|dev
op_assign
id|legacy_create_device
c_func
(paren
op_amp
id|r_addr
comma
op_amp
id|module_path
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|dev
)paren
op_logical_or
(paren
id|dev-&gt;id.hw_type
op_ne
id|HPHW_BA
)paren
)paren
r_continue
suffix:semicolon
id|memset
c_func
(paren
id|module_path.path.bc
comma
l_int|0xff
comma
l_int|4
)paren
suffix:semicolon
id|module_path.path.bc
(braket
l_int|4
)braket
op_assign
id|mod
suffix:semicolon
r_for
c_loop
(paren
id|func
op_assign
l_int|0
suffix:semicolon
id|func
OL
l_int|16
suffix:semicolon
id|func
op_increment
)paren
(brace
id|module_path.path.bc
(braket
l_int|5
)braket
op_assign
l_int|0
suffix:semicolon
id|module_path.path.mod
op_assign
id|func
suffix:semicolon
id|legacy_create_device
c_func
(paren
op_amp
id|r_addr
comma
op_amp
id|module_path
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#else /* CONFIG_PA20 */
DECL|macro|snake_inventory
mdefine_line|#define snake_inventory() do { } while (0)
macro_line|#endif  /* CONFIG_PA20 */
multiline_comment|/* Common 32/64 bit based code goes here */
multiline_comment|/**&n; * add_system_map_addresses - Add additional addresses to the parisc device.&n; * @dev: The parisc device.&n; * @num_addrs: Then number of addresses to add;&n; * @module_instance: The system_map module instance.&n; *&n; * This function adds any additional addresses reported by the system_map&n; * firmware to the parisc device.&n; */
r_static
r_void
id|__init
DECL|function|add_system_map_addresses
id|add_system_map_addresses
c_func
(paren
r_struct
id|parisc_device
op_star
id|dev
comma
r_int
id|num_addrs
comma
r_int
id|module_instance
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|status
suffix:semicolon
r_struct
id|pdc_system_map_addr_info
id|addr_result
suffix:semicolon
id|dev-&gt;addr
op_assign
id|kmalloc
c_func
(paren
id|num_addrs
op_star
r_sizeof
(paren
r_int
r_int
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;addr
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s %s(): memory allocation failure&bslash;n&quot;
comma
id|__FILE__
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|num_addrs
suffix:semicolon
op_increment
id|i
)paren
(brace
id|status
op_assign
id|pdc_system_map_find_addrs
c_func
(paren
op_amp
id|addr_result
comma
id|module_instance
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PDC_OK
op_eq
id|status
)paren
(brace
id|dev-&gt;addr
(braket
id|dev-&gt;num_addrs
)braket
op_assign
(paren
r_int
r_int
)paren
id|addr_result.mod_addr
suffix:semicolon
id|dev-&gt;num_addrs
op_increment
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Bad PDC_FIND_ADDRESS status return (%ld) for index %d&bslash;n&quot;
comma
id|status
comma
id|i
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/**&n; * do_system_map_inventory - Retrieve firmware devices via SYSTEM_MAP.&n; *&n; * This function attempts to retrieve and register all the devices firmware&n; * knows about via the SYSTEM_MAP PDC call.&n; */
DECL|function|system_map_inventory
r_static
r_void
id|__init
id|system_map_inventory
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|status
op_assign
id|PDC_OK
suffix:semicolon
multiline_comment|/*&n;&t; * first stop the usb controller, otherwise the machine&n;&t; * might crash during iommu setup&n;&t; */
id|pdc_suspend_usb
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|status
op_ne
id|PDC_BAD_PROC
op_logical_and
id|status
op_ne
id|PDC_NE_MOD
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|parisc_device
op_star
id|dev
suffix:semicolon
r_struct
id|pdc_system_map_mod_info
id|module_result
suffix:semicolon
r_struct
id|pdc_module_path
id|module_path
suffix:semicolon
id|status
op_assign
id|pdc_system_map_find_mods
c_func
(paren
op_amp
id|module_result
comma
op_amp
id|module_path
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
id|PDC_OK
)paren
r_continue
suffix:semicolon
id|dev
op_assign
id|alloc_pa_dev
c_func
(paren
id|module_result.mod_addr
comma
op_amp
id|module_path.path
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_continue
suffix:semicolon
id|register_parisc_device
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* if available, get the additional addresses for a module */
r_if
c_cond
(paren
op_logical_neg
id|module_result.add_addrs
)paren
r_continue
suffix:semicolon
id|add_system_map_addresses
c_func
(paren
id|dev
comma
id|module_result.add_addrs
comma
id|i
)paren
suffix:semicolon
)brace
id|walk_central_bus
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|do_memory_inventory
r_void
id|__init
id|do_memory_inventory
c_func
(paren
r_void
)paren
(brace
r_switch
c_cond
(paren
id|pdc_type
)paren
(brace
r_case
id|PDC_TYPE_PAT
suffix:colon
id|pat_memconfig
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PDC_TYPE_SYSTEM_MAP
suffix:colon
id|sprockets_memconfig
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PDC_TYPE_SNAKE
suffix:colon
id|pagezero_memconfig
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;Unknown PDC type!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|npmem_ranges
op_eq
l_int|0
op_logical_or
id|pmem_ranges
(braket
l_int|0
)braket
dot
id|start_pfn
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Bad memory configuration returned!&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Some memory may not be used!&bslash;n&quot;
)paren
suffix:semicolon
id|pagezero_memconfig
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|do_device_inventory
r_void
id|__init
id|do_device_inventory
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Searching for devices...&bslash;n&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|pdc_type
)paren
(brace
r_case
id|PDC_TYPE_PAT
suffix:colon
id|pat_inventory
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PDC_TYPE_SYSTEM_MAP
suffix:colon
id|system_map_inventory
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PDC_TYPE_SNAKE
suffix:colon
id|snake_inventory
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;Unknown PDC type!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Found devices:&bslash;n&quot;
)paren
suffix:semicolon
id|print_parisc_devices
c_func
(paren
)paren
suffix:semicolon
)brace
eof
