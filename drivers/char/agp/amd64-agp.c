multiline_comment|/* &n; * Copyright 2001-2003 SuSE Labs.&n; * Distributed under the GNU public license, v2.&n; * &n; * This is a GART driver for the AMD Opteron/Athlon64 on-CPU northbridge.&n; * It also includes support for the AMD 8151 AGP bridge,&n; * although it doesn&squot;t actually do much, as all the real&n; * work is done in the northbridge(s).&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/agp_backend.h&gt;
macro_line|#include &quot;agp.h&quot;
multiline_comment|/* Will need to be increased if AMD64 ever goes &gt;8-way. */
macro_line|#ifdef CONFIG_SMP
DECL|macro|MAX_HAMMER_GARTS
mdefine_line|#define MAX_HAMMER_GARTS   8
macro_line|#else
DECL|macro|MAX_HAMMER_GARTS
mdefine_line|#define MAX_HAMMER_GARTS   1
macro_line|#endif
multiline_comment|/* PTE bits. */
DECL|macro|GPTE_VALID
mdefine_line|#define GPTE_VALID&t;1
DECL|macro|GPTE_COHERENT
mdefine_line|#define GPTE_COHERENT&t;2
multiline_comment|/* Aperture control register bits. */
DECL|macro|GARTEN
mdefine_line|#define GARTEN&t;&t;(1&lt;&lt;0)
DECL|macro|DISGARTCPU
mdefine_line|#define DISGARTCPU&t;(1&lt;&lt;4)
DECL|macro|DISGARTIO
mdefine_line|#define DISGARTIO&t;(1&lt;&lt;5)
multiline_comment|/* GART cache control register bits. */
DECL|macro|INVGART
mdefine_line|#define INVGART&t;&t;(1&lt;&lt;0)
DECL|macro|GARTPTEERR
mdefine_line|#define GARTPTEERR&t;(1&lt;&lt;1)
DECL|variable|nr_garts
r_static
r_int
id|nr_garts
suffix:semicolon
DECL|variable|hammers
r_static
r_struct
id|pci_dev
op_star
id|hammers
(braket
id|MAX_HAMMER_GARTS
)braket
suffix:semicolon
DECL|variable|agp_try_unsupported
r_static
r_int
id|__initdata
id|agp_try_unsupported
suffix:semicolon
DECL|variable|gart_iterator
r_static
r_int
id|gart_iterator
suffix:semicolon
DECL|macro|for_each_nb
mdefine_line|#define for_each_nb() for(gart_iterator=0;gart_iterator&lt;nr_garts;gart_iterator++)
DECL|function|flush_amd64_tlb
r_static
r_void
id|flush_amd64_tlb
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u32
id|tmp
suffix:semicolon
id|pci_read_config_dword
(paren
id|dev
comma
id|AMD64_GARTCACHECTL
comma
op_amp
id|tmp
)paren
suffix:semicolon
id|tmp
op_or_assign
id|INVGART
suffix:semicolon
id|pci_write_config_dword
(paren
id|dev
comma
id|AMD64_GARTCACHECTL
comma
id|tmp
)paren
suffix:semicolon
)brace
DECL|function|amd64_tlbflush
r_static
r_void
id|amd64_tlbflush
c_func
(paren
r_struct
id|agp_memory
op_star
id|temp
)paren
(brace
id|for_each_nb
c_func
(paren
)paren
id|flush_amd64_tlb
c_func
(paren
id|hammers
(braket
id|gart_iterator
)braket
)paren
suffix:semicolon
)brace
DECL|function|amd64_insert_memory
r_static
r_int
id|amd64_insert_memory
c_func
(paren
r_struct
id|agp_memory
op_star
id|mem
comma
id|off_t
id|pg_start
comma
r_int
id|type
)paren
(brace
r_int
id|i
comma
id|j
comma
id|num_entries
suffix:semicolon
r_int
id|tmp
suffix:semicolon
id|u32
id|pte
suffix:semicolon
id|num_entries
op_assign
id|agp_num_entries
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
l_int|0
op_logical_or
id|mem-&gt;type
op_ne
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Make sure we can fit the range in the gatt table. */
multiline_comment|/* FIXME: could wrap */
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
)paren
id|pg_start
op_plus
id|mem-&gt;page_count
)paren
OG
id|num_entries
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|j
op_assign
id|pg_start
suffix:semicolon
multiline_comment|/* gatt table should be empty. */
r_while
c_loop
(paren
id|j
OL
(paren
id|pg_start
op_plus
id|mem-&gt;page_count
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|PGE_EMPTY
c_func
(paren
id|agp_bridge
comma
id|agp_bridge-&gt;gatt_table
(braket
id|j
)braket
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|j
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mem-&gt;is_flushed
op_eq
id|FALSE
)paren
(brace
id|global_cache_flush
c_func
(paren
)paren
suffix:semicolon
id|mem-&gt;is_flushed
op_assign
id|TRUE
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|j
op_assign
id|pg_start
suffix:semicolon
id|i
OL
id|mem-&gt;page_count
suffix:semicolon
id|i
op_increment
comma
id|j
op_increment
)paren
(brace
id|tmp
op_assign
id|agp_bridge-&gt;driver
op_member_access_from_pointer
id|mask_memory
c_func
(paren
id|mem-&gt;memory
(braket
id|i
)braket
comma
id|mem-&gt;type
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|tmp
op_amp
l_int|0xffffff0000000ffc
)paren
suffix:semicolon
id|pte
op_assign
(paren
id|tmp
op_amp
l_int|0x000000ff00000000
)paren
op_rshift
l_int|28
suffix:semicolon
id|pte
op_or_assign
(paren
id|tmp
op_amp
l_int|0x00000000fffff000
)paren
suffix:semicolon
id|pte
op_or_assign
id|GPTE_VALID
op_or
id|GPTE_COHERENT
suffix:semicolon
id|agp_bridge-&gt;gatt_table
(braket
id|j
)braket
op_assign
id|pte
suffix:semicolon
)brace
id|amd64_tlbflush
c_func
(paren
id|mem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This hack alters the order element according&n; * to the size of a long. It sucks. I totally disown this, even&n; * though it does appear to work for the most part.&n; */
DECL|variable|amd64_aperture_sizes
r_static
r_struct
id|aper_size_info_32
id|amd64_aperture_sizes
(braket
l_int|7
)braket
op_assign
(brace
(brace
l_int|32
comma
l_int|8192
comma
l_int|3
op_plus
(paren
r_sizeof
(paren
r_int
)paren
op_div
l_int|8
)paren
comma
l_int|0
)brace
comma
(brace
l_int|64
comma
l_int|16384
comma
l_int|4
op_plus
(paren
r_sizeof
(paren
r_int
)paren
op_div
l_int|8
)paren
comma
l_int|1
op_lshift
l_int|1
)brace
comma
(brace
l_int|128
comma
l_int|32768
comma
l_int|5
op_plus
(paren
r_sizeof
(paren
r_int
)paren
op_div
l_int|8
)paren
comma
l_int|1
op_lshift
l_int|2
)brace
comma
(brace
l_int|256
comma
l_int|65536
comma
l_int|6
op_plus
(paren
r_sizeof
(paren
r_int
)paren
op_div
l_int|8
)paren
comma
l_int|1
op_lshift
l_int|1
op_or
l_int|1
op_lshift
l_int|2
)brace
comma
(brace
l_int|512
comma
l_int|131072
comma
l_int|7
op_plus
(paren
r_sizeof
(paren
r_int
)paren
op_div
l_int|8
)paren
comma
l_int|1
op_lshift
l_int|3
)brace
comma
(brace
l_int|1024
comma
l_int|262144
comma
l_int|8
op_plus
(paren
r_sizeof
(paren
r_int
)paren
op_div
l_int|8
)paren
comma
l_int|1
op_lshift
l_int|1
op_or
l_int|1
op_lshift
l_int|3
)brace
comma
(brace
l_int|2048
comma
l_int|524288
comma
l_int|9
op_plus
(paren
r_sizeof
(paren
r_int
)paren
op_div
l_int|8
)paren
comma
l_int|1
op_lshift
l_int|2
op_or
l_int|1
op_lshift
l_int|3
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * Get the current Aperture size from the x86-64.&n; * Note, that there may be multiple x86-64&squot;s, but we just return&n; * the value from the first one we find. The set_size functions&n; * keep the rest coherent anyway. Or at least should do.&n; */
DECL|function|amd64_fetch_size
r_static
r_int
id|amd64_fetch_size
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_int
id|i
suffix:semicolon
id|u32
id|temp
suffix:semicolon
r_struct
id|aper_size_info_32
op_star
id|values
suffix:semicolon
id|dev
op_assign
id|hammers
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|AMD64_GARTAPERTURECTL
comma
op_amp
id|temp
)paren
suffix:semicolon
id|temp
op_assign
(paren
id|temp
op_amp
l_int|0xe
)paren
suffix:semicolon
id|values
op_assign
id|A_SIZE_32
c_func
(paren
id|amd64_aperture_sizes
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
id|agp_bridge-&gt;driver-&gt;num_aperture_sizes
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|temp
op_eq
id|values
(braket
id|i
)braket
dot
id|size_value
)paren
(brace
id|agp_bridge-&gt;previous_size
op_assign
id|agp_bridge-&gt;current_size
op_assign
(paren
r_void
op_star
)paren
(paren
id|values
op_plus
id|i
)paren
suffix:semicolon
id|agp_bridge-&gt;aperture_size_idx
op_assign
id|i
suffix:semicolon
r_return
id|values
(braket
id|i
)braket
dot
id|size
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * In a multiprocessor x86-64 system, this function gets&n; * called once for each CPU.&n; */
DECL|function|amd64_configure
r_static
id|u64
id|amd64_configure
(paren
r_struct
id|pci_dev
op_star
id|hammer
comma
id|u64
id|gatt_table
)paren
(brace
id|u64
id|aperturebase
suffix:semicolon
id|u32
id|tmp
suffix:semicolon
id|u64
id|addr
comma
id|aper_base
suffix:semicolon
multiline_comment|/* Address to map to */
id|pci_read_config_dword
(paren
id|hammer
comma
id|AMD64_GARTAPERTUREBASE
comma
op_amp
id|tmp
)paren
suffix:semicolon
id|aperturebase
op_assign
id|tmp
op_lshift
l_int|25
suffix:semicolon
id|aper_base
op_assign
(paren
id|aperturebase
op_amp
id|PCI_BASE_ADDRESS_MEM_MASK
)paren
suffix:semicolon
multiline_comment|/* address of the mappings table */
id|addr
op_assign
(paren
id|u64
)paren
id|gatt_table
suffix:semicolon
id|addr
op_rshift_assign
l_int|12
suffix:semicolon
id|tmp
op_assign
(paren
id|u32
)paren
id|addr
op_lshift
l_int|4
suffix:semicolon
id|tmp
op_and_assign
op_complement
l_int|0xf
suffix:semicolon
id|pci_write_config_dword
(paren
id|hammer
comma
id|AMD64_GARTTABLEBASE
comma
id|tmp
)paren
suffix:semicolon
multiline_comment|/* Enable GART translation for this hammer. */
id|pci_read_config_dword
c_func
(paren
id|hammer
comma
id|AMD64_GARTAPERTURECTL
comma
op_amp
id|tmp
)paren
suffix:semicolon
id|tmp
op_or_assign
id|GARTEN
suffix:semicolon
id|tmp
op_and_assign
op_complement
(paren
id|DISGARTCPU
op_or
id|DISGARTIO
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|hammer
comma
id|AMD64_GARTAPERTURECTL
comma
id|tmp
)paren
suffix:semicolon
multiline_comment|/* keep CPU&squot;s coherent. */
id|flush_amd64_tlb
(paren
id|hammer
)paren
suffix:semicolon
r_return
id|aper_base
suffix:semicolon
)brace
DECL|variable|amd_8151_sizes
r_static
r_struct
id|aper_size_info_32
id|amd_8151_sizes
(braket
l_int|7
)braket
op_assign
(brace
(brace
l_int|2048
comma
l_int|524288
comma
l_int|9
comma
l_int|0x00000000
)brace
comma
multiline_comment|/* 0 0 0 0 0 0 */
(brace
l_int|1024
comma
l_int|262144
comma
l_int|8
comma
l_int|0x00000400
)brace
comma
multiline_comment|/* 1 0 0 0 0 0 */
(brace
l_int|512
comma
l_int|131072
comma
l_int|7
comma
l_int|0x00000600
)brace
comma
multiline_comment|/* 1 1 0 0 0 0 */
(brace
l_int|256
comma
l_int|65536
comma
l_int|6
comma
l_int|0x00000700
)brace
comma
multiline_comment|/* 1 1 1 0 0 0 */
(brace
l_int|128
comma
l_int|32768
comma
l_int|5
comma
l_int|0x00000720
)brace
comma
multiline_comment|/* 1 1 1 1 0 0 */
(brace
l_int|64
comma
l_int|16384
comma
l_int|4
comma
l_int|0x00000730
)brace
comma
multiline_comment|/* 1 1 1 1 1 0 */
(brace
l_int|32
comma
l_int|8192
comma
l_int|3
comma
l_int|0x00000738
)brace
multiline_comment|/* 1 1 1 1 1 1 */
)brace
suffix:semicolon
DECL|function|amd_8151_configure
r_static
r_int
id|amd_8151_configure
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|gatt_bus
op_assign
id|virt_to_phys
c_func
(paren
id|agp_bridge-&gt;gatt_table_real
)paren
suffix:semicolon
multiline_comment|/* Configure AGP regs in each x86-64 host bridge. */
id|for_each_nb
c_func
(paren
)paren
(brace
id|agp_bridge-&gt;gart_bus_addr
op_assign
id|amd64_configure
c_func
(paren
id|hammers
(braket
id|gart_iterator
)braket
comma
id|gatt_bus
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|amd64_cleanup
r_static
r_void
id|amd64_cleanup
c_func
(paren
r_void
)paren
(brace
id|u32
id|tmp
suffix:semicolon
id|for_each_nb
c_func
(paren
)paren
(brace
multiline_comment|/* disable gart translation */
id|pci_read_config_dword
(paren
id|hammers
(braket
id|gart_iterator
)braket
comma
id|AMD64_GARTAPERTURECTL
comma
op_amp
id|tmp
)paren
suffix:semicolon
id|tmp
op_and_assign
op_complement
id|AMD64_GARTEN
suffix:semicolon
id|pci_write_config_dword
(paren
id|hammers
(braket
id|gart_iterator
)braket
comma
id|AMD64_GARTAPERTURECTL
comma
id|tmp
)paren
suffix:semicolon
)brace
)brace
DECL|variable|amd_8151_driver
r_struct
id|agp_bridge_driver
id|amd_8151_driver
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|aperture_sizes
op_assign
id|amd_8151_sizes
comma
dot
id|size_type
op_assign
id|U32_APER_SIZE
comma
dot
id|num_aperture_sizes
op_assign
l_int|7
comma
dot
id|configure
op_assign
id|amd_8151_configure
comma
dot
id|fetch_size
op_assign
id|amd64_fetch_size
comma
dot
id|cleanup
op_assign
id|amd64_cleanup
comma
dot
id|tlb_flush
op_assign
id|amd64_tlbflush
comma
dot
id|mask_memory
op_assign
id|agp_generic_mask_memory
comma
dot
id|masks
op_assign
l_int|NULL
comma
dot
id|agp_enable
op_assign
id|agp_generic_enable
comma
dot
id|cache_flush
op_assign
id|global_cache_flush
comma
dot
id|create_gatt_table
op_assign
id|agp_generic_create_gatt_table
comma
dot
id|free_gatt_table
op_assign
id|agp_generic_free_gatt_table
comma
dot
id|insert_memory
op_assign
id|amd64_insert_memory
comma
dot
id|remove_memory
op_assign
id|agp_generic_remove_memory
comma
dot
id|alloc_by_type
op_assign
id|agp_generic_alloc_by_type
comma
dot
id|free_by_type
op_assign
id|agp_generic_free_by_type
comma
dot
id|agp_alloc_page
op_assign
id|agp_generic_alloc_page
comma
dot
id|agp_destroy_page
op_assign
id|agp_generic_destroy_page
comma
)brace
suffix:semicolon
multiline_comment|/* Some basic sanity checks for the aperture. */
DECL|function|aperture_valid
r_static
r_int
id|__init
id|aperture_valid
c_func
(paren
id|u64
id|aper
comma
id|u32
id|size
)paren
(brace
r_static
r_int
id|not_first_call
suffix:semicolon
id|u32
id|pfn
comma
id|c
suffix:semicolon
r_if
c_cond
(paren
id|aper
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;No aperture&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|size
OL
l_int|32
op_star
l_int|1024
op_star
l_int|1024
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Aperture too small (%d MB)&bslash;n&quot;
comma
id|size
op_rshift
l_int|20
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|aper
op_plus
id|size
OG
l_int|0xffffffff
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Aperture out of bounds&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|pfn
op_assign
id|aper
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_for
c_loop
(paren
id|c
op_assign
l_int|0
suffix:semicolon
id|c
OL
id|size
op_div
id|PAGE_SIZE
suffix:semicolon
id|c
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pfn_valid
c_func
(paren
id|pfn
op_plus
id|c
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageReserved
c_func
(paren
id|pfn_to_page
c_func
(paren
id|pfn
op_plus
id|c
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Aperture pointing to RAM&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* Request the Aperture. This catches cases when someone else&n;&t;   already put a mapping in there - happens with some very broken BIOS &n;&n;&t;   Maybe better to use pci_assign_resource/pci_enable_device instead trusting&n;&t;   the bridges? */
r_if
c_cond
(paren
op_logical_neg
id|not_first_call
op_logical_and
id|request_mem_region
c_func
(paren
id|aper
comma
id|size
comma
l_string|&quot;aperture&quot;
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Aperture conflicts with PCI mapping.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|not_first_call
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* &n; * W*s centric BIOS sometimes only set up the aperture in the AGP&n; * bridge, not the northbridge. On AMD64 this is handled early &n; * in aperture.c, but when GART_IOMMU is not enabled or we run&n; * on a 32bit kernel this needs to be redone. &n; * Unfortunately it is impossible to fix the aperture here because it&squot;s too late&n; * to allocate that much memory. But at least error out cleanly instead of&n; * crashing.&n; */
DECL|function|fix_northbridge
r_static
id|__init
r_int
id|fix_northbridge
c_func
(paren
r_struct
id|pci_dev
op_star
id|nb
comma
r_struct
id|pci_dev
op_star
id|agp
comma
id|u16
id|cap
)paren
(brace
id|u32
id|aper_low
comma
id|aper_hi
suffix:semicolon
id|u64
id|aper
comma
id|nb_aper
suffix:semicolon
r_int
id|order
op_assign
l_int|0
suffix:semicolon
id|u32
id|nb_order
comma
id|nb_base
suffix:semicolon
id|u16
id|apsize
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|nb
comma
l_int|0x90
comma
op_amp
id|nb_order
)paren
suffix:semicolon
id|nb_order
op_assign
(paren
id|nb_order
op_rshift
l_int|1
)paren
op_amp
l_int|7
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|nb
comma
l_int|0x94
comma
op_amp
id|nb_base
)paren
suffix:semicolon
id|nb_aper
op_assign
id|nb_base
op_lshift
l_int|25
suffix:semicolon
r_if
c_cond
(paren
id|aperture_valid
c_func
(paren
id|nb_aper
comma
(paren
l_int|32
op_star
l_int|1024
op_star
l_int|1024
)paren
op_lshift
id|nb_order
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Northbridge seems to contain crap. Try the AGP bridge. */
id|pci_read_config_word
c_func
(paren
id|agp
comma
id|cap
op_plus
l_int|0x14
comma
op_amp
id|apsize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|apsize
op_eq
l_int|0xffff
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|apsize
op_and_assign
l_int|0xfff
suffix:semicolon
multiline_comment|/* Some BIOS use weird encodings not in the AGPv3 table. */
r_if
c_cond
(paren
id|apsize
op_amp
l_int|0xff
)paren
id|apsize
op_or_assign
l_int|0xf00
suffix:semicolon
id|order
op_assign
l_int|7
op_minus
id|hweight16
c_func
(paren
id|apsize
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|agp
comma
l_int|0x10
comma
op_amp
id|aper_low
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|agp
comma
l_int|0x14
comma
op_amp
id|aper_hi
)paren
suffix:semicolon
id|aper
op_assign
(paren
id|aper_low
op_amp
op_complement
(paren
(paren
l_int|1
op_lshift
l_int|22
)paren
op_minus
l_int|1
)paren
)paren
op_or
(paren
(paren
id|u64
)paren
id|aper_hi
op_lshift
l_int|32
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Aperture from AGP @ %Lx size %u MB&bslash;n&quot;
comma
id|aper
comma
l_int|32
op_lshift
id|order
)paren
suffix:semicolon
r_if
c_cond
(paren
id|order
OL
l_int|0
op_logical_or
op_logical_neg
id|aperture_valid
c_func
(paren
id|aper
comma
(paren
l_int|32
op_star
l_int|1024
op_star
l_int|1024
)paren
op_lshift
id|order
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|nb
comma
l_int|0x90
comma
id|order
op_lshift
l_int|1
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|nb
comma
l_int|0x94
comma
id|aper
op_rshift
l_int|25
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cache_nbs
r_static
id|__init
r_int
id|cache_nbs
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
id|u32
id|cap_ptr
)paren
(brace
r_struct
id|pci_dev
op_star
id|loop_dev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* cache pci_devs of northbridges. */
r_while
c_loop
(paren
(paren
id|loop_dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_AMD
comma
l_int|0x1103
comma
id|loop_dev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|fix_northbridge
c_func
(paren
id|loop_dev
comma
id|pdev
comma
id|cap_ptr
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;No usable aperture found.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef __x86_64__ 
multiline_comment|/* should port this to i386 */
id|printk
c_func
(paren
l_string|&quot;Consider rebooting with iommu=memaper=2 to get a good aperture.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif 
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|hammers
(braket
id|i
op_increment
)braket
op_assign
id|loop_dev
suffix:semicolon
id|nr_garts
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|MAX_HAMMER_GARTS
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Too many northbridges for AGP&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_return
id|i
op_eq
l_int|0
ques
c_cond
op_minus
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|agp_amd64_probe
r_static
r_int
id|__init
id|agp_amd64_probe
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_const
r_struct
id|pci_device_id
op_star
id|ent
)paren
(brace
r_struct
id|agp_bridge_data
op_star
id|bridge
suffix:semicolon
id|u8
id|rev_id
suffix:semicolon
id|u8
id|cap_ptr
suffix:semicolon
r_char
op_star
id|revstring
op_assign
l_int|NULL
suffix:semicolon
id|cap_ptr
op_assign
id|pci_find_capability
c_func
(paren
id|pdev
comma
id|PCI_CAP_ID_AGP
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cap_ptr
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* Could check for AGPv3 here */
id|bridge
op_assign
id|agp_alloc_bridge
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bridge
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|pdev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_AMD
op_logical_and
id|pdev-&gt;device
op_eq
id|PCI_DEVICE_ID_AMD_8151_0
)paren
(brace
id|pci_read_config_byte
c_func
(paren
id|pdev
comma
id|PCI_REVISION_ID
comma
op_amp
id|rev_id
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|rev_id
)paren
(brace
r_case
l_int|0x01
suffix:colon
id|revstring
op_assign
l_string|&quot;A0&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x02
suffix:colon
id|revstring
op_assign
l_string|&quot;A1&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x11
suffix:colon
id|revstring
op_assign
l_string|&quot;B0&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x12
suffix:colon
id|revstring
op_assign
l_string|&quot;B1&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x13
suffix:colon
id|revstring
op_assign
l_string|&quot;B2&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|revstring
op_assign
l_string|&quot;??&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Detected AMD 8151 AGP Bridge rev %s&bslash;n&quot;
comma
id|revstring
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Work around errata.&n;&t;&t; * Chips before B2 stepping incorrectly reporting v3.5&n;&t;&t; */
r_if
c_cond
(paren
id|rev_id
OL
l_int|0x13
)paren
(brace
id|printk
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Correcting AGP revision (reports 3.5, is really 3.0)&bslash;n&quot;
)paren
suffix:semicolon
id|bridge-&gt;major_version
op_assign
l_int|3
suffix:semicolon
id|bridge-&gt;minor_version
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Detected AGP bridge %x&bslash;n&quot;
comma
id|pdev-&gt;devfn
)paren
suffix:semicolon
)brace
id|bridge-&gt;driver
op_assign
op_amp
id|amd_8151_driver
suffix:semicolon
id|bridge-&gt;dev
op_assign
id|pdev
suffix:semicolon
id|bridge-&gt;capndx
op_assign
id|cap_ptr
suffix:semicolon
multiline_comment|/* Fill in the mode register */
id|pci_read_config_dword
c_func
(paren
id|pdev
comma
id|bridge-&gt;capndx
op_plus
id|PCI_AGP_STATUS
comma
op_amp
id|bridge-&gt;mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cache_nbs
c_func
(paren
id|pdev
comma
id|cap_ptr
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|agp_put_bridge
c_func
(paren
id|bridge
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|pci_set_drvdata
c_func
(paren
id|pdev
comma
id|bridge
)paren
suffix:semicolon
r_return
id|agp_add_bridge
c_func
(paren
id|bridge
)paren
suffix:semicolon
)brace
DECL|function|agp_amd64_remove
r_static
r_void
id|__devexit
id|agp_amd64_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
r_struct
id|agp_bridge_data
op_star
id|bridge
op_assign
id|pci_get_drvdata
c_func
(paren
id|pdev
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|virt_to_phys
c_func
(paren
id|bridge-&gt;gatt_table_real
)paren
comma
id|amd64_aperture_sizes
(braket
id|bridge-&gt;aperture_size_idx
)braket
dot
id|size
)paren
suffix:semicolon
id|agp_remove_bridge
c_func
(paren
id|bridge
)paren
suffix:semicolon
id|agp_put_bridge
c_func
(paren
id|bridge
)paren
suffix:semicolon
)brace
DECL|variable|agp_amd64_pci_table
r_static
r_struct
id|pci_device_id
id|agp_amd64_pci_table
(braket
)braket
op_assign
(brace
(brace
dot
r_class
op_assign
(paren
id|PCI_CLASS_BRIDGE_HOST
op_lshift
l_int|8
)paren
comma
dot
id|class_mask
op_assign
op_complement
l_int|0
comma
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_AMD
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_AMD_8151_0
comma
dot
id|subvendor
op_assign
id|PCI_ANY_ID
comma
dot
id|subdevice
op_assign
id|PCI_ANY_ID
comma
)brace
comma
multiline_comment|/* VIA K8T800 */
(brace
dot
r_class
op_assign
(paren
id|PCI_CLASS_BRIDGE_HOST
op_lshift
l_int|8
)paren
comma
dot
id|class_mask
op_assign
op_complement
l_int|0
comma
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_VIA
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_VIA_8385_0
comma
dot
id|subvendor
op_assign
id|PCI_ANY_ID
comma
dot
id|subdevice
op_assign
id|PCI_ANY_ID
comma
)brace
comma
multiline_comment|/* VIA K8M800 / K8N800 */
(brace
dot
r_class
op_assign
(paren
id|PCI_CLASS_BRIDGE_HOST
op_lshift
l_int|8
)paren
comma
dot
id|class_mask
op_assign
op_complement
l_int|0
comma
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_VIA
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_VIA_8380_0
comma
dot
id|subvendor
op_assign
id|PCI_ANY_ID
comma
dot
id|subdevice
op_assign
id|PCI_ANY_ID
comma
)brace
comma
(brace
dot
r_class
op_assign
(paren
id|PCI_CLASS_BRIDGE_HOST
op_lshift
l_int|8
)paren
comma
dot
id|class_mask
op_assign
op_complement
l_int|0
comma
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_SI
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_SI_755
comma
dot
id|subvendor
op_assign
id|PCI_ANY_ID
comma
dot
id|subdevice
op_assign
id|PCI_ANY_ID
comma
)brace
comma
(brace
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|agp_amd64_pci_table
)paren
suffix:semicolon
DECL|variable|agp_amd64_pci_driver
r_static
r_struct
id|pci_driver
id|agp_amd64_pci_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;agpgart-amd64&quot;
comma
dot
id|id_table
op_assign
id|agp_amd64_pci_table
comma
dot
id|probe
op_assign
id|agp_amd64_probe
comma
dot
id|remove
op_assign
id|agp_amd64_remove
comma
)brace
suffix:semicolon
multiline_comment|/* Not static due to IOMMU code calling it early. */
DECL|function|agp_amd64_init
r_int
id|__init
id|agp_amd64_init
c_func
(paren
r_void
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|agp_off
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|pci_module_init
c_func
(paren
op_amp
id|agp_amd64_pci_driver
)paren
op_eq
l_int|0
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|agp_try_unsupported
op_logical_and
op_logical_neg
id|agp_try_unsupported_boot
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;No supported AGP bridge found.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef MODULE&t;&t;&t;
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;You can try agp_try_unsupported=1&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;You can boot with agp=try_unsupported&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* First check that we have at least one AMD64 NB */
r_if
c_cond
(paren
op_logical_neg
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_AMD
comma
l_int|0x1103
comma
l_int|NULL
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* Look for any AGP bridge */
id|dev
op_assign
l_int|NULL
suffix:semicolon
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_while
c_loop
(paren
(paren
id|dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|dev
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pci_find_capability
c_func
(paren
id|dev
comma
id|PCI_CAP_ID_AGP
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* Only one bridge supported right now */
r_if
c_cond
(paren
id|agp_amd64_probe
c_func
(paren
id|dev
comma
l_int|NULL
)paren
op_eq
l_int|0
)paren
(brace
id|err
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|agp_amd64_cleanup
r_static
r_void
id|__exit
id|agp_amd64_cleanup
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|agp_amd64_pci_driver
)paren
suffix:semicolon
)brace
multiline_comment|/* On AMD64 the PCI driver needs to initialize this driver early&n;   for the IOMMU, so it has to be called via a backdoor. */
macro_line|#ifndef CONFIG_GART_IOMMU
DECL|variable|agp_amd64_init
id|module_init
c_func
(paren
id|agp_amd64_init
)paren
suffix:semicolon
DECL|variable|agp_amd64_cleanup
id|module_exit
c_func
(paren
id|agp_amd64_cleanup
)paren
suffix:semicolon
macro_line|#endif
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Dave Jones &lt;davej@codemonkey.org.uk&gt;, Andi Kleen&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|agp_try_unsupported
comma
l_string|&quot;1i&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL and additional rights&quot;
)paren
suffix:semicolon
eof
