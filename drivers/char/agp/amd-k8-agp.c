multiline_comment|/* &n; * Copyright 2001,2002 SuSE Labs&n; * Distributed under the GNU public license, v2.&n; * &n; * This is a GART driver for the AMD K8 northbridge and the AMD 8151 &n; * AGP bridge. The main work is done in the northbridge. The configuration&n; * is only mirrored in the 8151 for compatibility (could be likely&n; * removed now).&n; */
multiline_comment|/*&n; * On x86-64 the AGP driver needs to be initialized early by the IOMMU &n; * code.  When you use this driver as a template for a new K8 AGP bridge&n; * driver don&squot;t forget to change arch/x86_64/kernel/pci-gart.c too -AK.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/agp_backend.h&gt;
macro_line|#include &quot;agp.h&quot;
DECL|function|pci_read64
r_static
id|u_int64_t
id|pci_read64
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|reg
)paren
(brace
r_union
(brace
id|u64
id|full
suffix:semicolon
r_struct
(brace
id|u32
id|high
suffix:semicolon
id|u32
id|low
suffix:semicolon
)brace
id|split
suffix:semicolon
)brace
id|tmp
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|reg
comma
op_amp
id|tmp.split.high
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|reg
op_plus
l_int|4
comma
op_amp
id|tmp.split.low
)paren
suffix:semicolon
r_return
id|tmp.full
suffix:semicolon
)brace
DECL|function|pci_write64
r_static
r_void
id|pci_write64
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|reg
comma
id|u64
id|value
)paren
(brace
r_union
(brace
id|u64
id|full
suffix:semicolon
r_struct
(brace
id|u32
id|high
suffix:semicolon
id|u32
id|low
suffix:semicolon
)brace
id|split
suffix:semicolon
)brace
id|tmp
suffix:semicolon
id|tmp.full
op_assign
id|value
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|reg
comma
id|tmp.split.high
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|reg
op_plus
l_int|4
comma
id|tmp.split.low
)paren
suffix:semicolon
)brace
DECL|function|x86_64_insert_memory
r_static
r_int
id|x86_64_insert_memory
c_func
(paren
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
id|u64
id|addr
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
id|CACHE_FLUSH
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
id|addr
op_assign
id|agp_bridge
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
id|tmp
op_assign
id|addr
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
l_int|1
op_lshift
l_int|1
op_or
l_int|1
op_lshift
l_int|0
suffix:semicolon
id|agp_bridge-&gt;gatt_table
(braket
id|j
)braket
op_assign
id|pte
suffix:semicolon
)brace
id|agp_bridge
op_member_access_from_pointer
id|tlb_flush
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
DECL|variable|x86_64_aperture_sizes
r_static
r_struct
id|aper_size_info_32
id|x86_64_aperture_sizes
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
DECL|function|amd_x86_64_fetch_size
r_static
r_int
id|amd_x86_64_fetch_size
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
id|pci_for_each_dev
c_func
(paren
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;number
op_eq
l_int|0
op_logical_and
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
op_eq
l_int|3
op_logical_and
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
op_ge
l_int|24
op_logical_and
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
op_le
l_int|31
)paren
(brace
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|AMD_X86_64_GARTAPERTURECTL
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
id|x86_64_aperture_sizes
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
id|agp_bridge-&gt;num_aperture_sizes
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
)brace
)brace
multiline_comment|/* erk, couldn&squot;t find an x86-64 ? */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|flush_x86_64_tlb
r_static
r_void
id|flush_x86_64_tlb
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
id|AMD_X86_64_GARTCACHECTL
comma
op_amp
id|tmp
)paren
suffix:semicolon
id|tmp
op_or_assign
l_int|1
op_lshift
l_int|0
suffix:semicolon
id|pci_write_config_dword
(paren
id|dev
comma
id|AMD_X86_64_GARTCACHECTL
comma
id|tmp
)paren
suffix:semicolon
)brace
DECL|function|amd_x86_64_tlbflush
r_static
r_void
id|amd_x86_64_tlbflush
c_func
(paren
id|agp_memory
op_star
id|temp
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
id|pci_for_each_dev
c_func
(paren
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;number
op_eq
l_int|0
op_logical_and
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
op_eq
l_int|3
op_logical_and
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
op_ge
l_int|24
op_logical_and
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
op_le
l_int|31
)paren
(brace
id|flush_x86_64_tlb
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * In a multiprocessor x86-64 system, this function gets&n; * called once for each CPU.&n; */
DECL|function|amd_x86_64_configure
r_static
id|u64
id|amd_x86_64_configure
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
id|AMD_X86_64_GARTAPERTUREBASE
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
id|AMD_X86_64_GARTTABLEBASE
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
id|AMD_X86_64_GARTAPERTURECTL
comma
op_amp
id|tmp
)paren
suffix:semicolon
id|tmp
op_and_assign
l_int|0x3f
suffix:semicolon
id|tmp
op_or_assign
l_int|1
op_lshift
l_int|0
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|hammer
comma
id|AMD_X86_64_GARTAPERTURECTL
comma
id|tmp
)paren
suffix:semicolon
multiline_comment|/* keep CPU&squot;s coherent. */
id|flush_x86_64_tlb
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
r_struct
id|pci_dev
op_star
id|dev
comma
op_star
id|hammer
op_assign
l_int|NULL
suffix:semicolon
r_int
id|current_size
suffix:semicolon
r_int
id|tmp
comma
id|tmp2
comma
id|i
suffix:semicolon
id|u64
id|aperbar
suffix:semicolon
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
id|pci_for_each_dev
c_func
(paren
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;number
op_eq
l_int|0
op_logical_and
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
op_eq
l_int|3
op_logical_and
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
op_ge
l_int|24
op_logical_and
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
op_le
l_int|31
)paren
(brace
id|agp_bridge-&gt;gart_bus_addr
op_assign
id|amd_x86_64_configure
c_func
(paren
id|dev
comma
id|gatt_bus
)paren
suffix:semicolon
id|hammer
op_assign
id|dev
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * TODO: Cache pci_dev&squot;s of x86-64&squot;s in private struct to save us&n;&t;&t;&t; * having to scan the pci list each time.&n;&t;&t;&t; */
)brace
)brace
r_if
c_cond
(paren
id|hammer
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* Shadow x86-64 registers into 8151 registers. */
id|dev
op_assign
id|agp_bridge-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|current_size
op_assign
id|amd_x86_64_fetch_size
c_func
(paren
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|AMD_8151_APERTURESIZE
comma
op_amp
id|tmp
)paren
suffix:semicolon
id|tmp
op_and_assign
op_complement
(paren
l_int|0xfff
)paren
suffix:semicolon
multiline_comment|/* translate x86-64 size bits to 8151 size bits*/
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|7
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|amd_8151_sizes
(braket
id|i
)braket
dot
id|size
op_eq
id|current_size
)paren
id|tmp
op_or_assign
(paren
id|amd_8151_sizes
(braket
id|i
)braket
dot
id|size_value
)paren
op_lshift
l_int|3
suffix:semicolon
)brace
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|AMD_8151_APERTURESIZE
comma
id|tmp
)paren
suffix:semicolon
id|pci_read_config_dword
(paren
id|hammer
comma
id|AMD_X86_64_GARTAPERTUREBASE
comma
op_amp
id|tmp
)paren
suffix:semicolon
id|aperbar
op_assign
id|pci_read64
(paren
id|dev
comma
id|AMD_8151_VMAPERTURE
)paren
suffix:semicolon
id|aperbar
op_or_assign
(paren
id|tmp
op_amp
l_int|0x7fff
)paren
op_lshift
l_int|25
suffix:semicolon
id|aperbar
op_and_assign
l_int|0x000000ffffffffff
suffix:semicolon
id|aperbar
op_or_assign
l_int|1
op_lshift
l_int|2
suffix:semicolon
multiline_comment|/* This address is a 64bit ptr FIXME: Make conditional in 32bit mode */
id|pci_write64
(paren
id|dev
comma
id|AMD_8151_VMAPERTURE
comma
id|aperbar
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|AMD_8151_AGP_CTL
comma
op_amp
id|tmp
)paren
suffix:semicolon
id|tmp
op_and_assign
op_complement
(paren
id|AMD_8151_GTLBEN
op_or
id|AMD_8151_APEREN
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|hammer
comma
id|AMD_X86_64_GARTAPERTURECTL
comma
op_amp
id|tmp2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp2
op_amp
id|AMD_X86_64_GARTEN
)paren
id|tmp
op_or_assign
id|AMD_8151_APEREN
suffix:semicolon
singleline_comment|// FIXME: bit 7 of AMD_8151_AGP_CTL (GTLBEN) must be copied if set.
singleline_comment|// But where is it set ?
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|AMD_8151_AGP_CTL
comma
id|tmp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|amd_8151_cleanup
r_static
r_void
id|amd_8151_cleanup
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
id|u32
id|tmp
suffix:semicolon
id|pci_for_each_dev
c_func
(paren
id|dev
)paren
(brace
multiline_comment|/* disable gart translation */
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;number
op_eq
l_int|0
op_logical_and
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
op_eq
l_int|3
op_logical_and
(paren
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
op_ge
l_int|24
)paren
op_logical_and
(paren
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
op_le
l_int|31
)paren
)paren
(brace
id|pci_read_config_dword
(paren
id|dev
comma
id|AMD_X86_64_GARTAPERTURECTL
comma
op_amp
id|tmp
)paren
suffix:semicolon
id|tmp
op_and_assign
op_complement
(paren
id|AMD_X86_64_GARTEN
)paren
suffix:semicolon
id|pci_write_config_dword
(paren
id|dev
comma
id|AMD_X86_64_GARTAPERTURECTL
comma
id|tmp
)paren
suffix:semicolon
)brace
multiline_comment|/* Now shadow the disable in the 8151 */
r_if
c_cond
(paren
id|dev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_AMD
op_logical_and
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_AMD_8151_0
)paren
(brace
id|pci_read_config_dword
(paren
id|dev
comma
id|AMD_8151_AGP_CTL
comma
op_amp
id|tmp
)paren
suffix:semicolon
id|tmp
op_and_assign
op_complement
(paren
id|AMD_8151_APEREN
)paren
suffix:semicolon
id|pci_write_config_dword
(paren
id|dev
comma
id|AMD_8151_AGP_CTL
comma
id|tmp
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|amd_8151_mask_memory
r_static
r_int
r_int
id|amd_8151_mask_memory
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|type
)paren
(brace
r_return
id|addr
op_or
id|agp_bridge-&gt;masks
(braket
l_int|0
)braket
dot
id|mask
suffix:semicolon
)brace
DECL|variable|amd_8151_masks
r_static
r_struct
id|gatt_mask
id|amd_8151_masks
(braket
)braket
op_assign
(brace
(brace
l_int|0x00000001
comma
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * Try to configure an AGP v3 capable setup.&n; * If we fail (typically because we don&squot;t have an AGP v3&n; * card in the system) we fall back to the generic AGP v2&n; * routines.&n; */
DECL|function|agp_x86_64_agp_enable
r_static
r_void
id|agp_x86_64_agp_enable
c_func
(paren
id|u32
id|mode
)paren
(brace
r_struct
id|pci_dev
op_star
id|device
op_assign
l_int|NULL
suffix:semicolon
id|u32
id|command
comma
id|scratch
suffix:semicolon
id|u8
id|cap_ptr
suffix:semicolon
id|u8
id|v3_devs
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* FIXME: If &squot;mode&squot; is x1/x2/x4 should we call the AGPv2 routines directly ?&n;&t; * Messy, as some AGPv3 cards can only do x4 as a minimum.&n;&t; */
multiline_comment|/* PASS1: Count # of devs capable of AGPv3 mode. */
id|pci_for_each_dev
c_func
(paren
id|device
)paren
(brace
id|cap_ptr
op_assign
id|pci_find_capability
c_func
(paren
id|device
comma
id|PCI_CAP_ID_AGP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cap_ptr
op_ne
l_int|0x00
)paren
(brace
id|pci_read_config_dword
c_func
(paren
id|device
comma
id|cap_ptr
comma
op_amp
id|scratch
)paren
suffix:semicolon
id|scratch
op_and_assign
(paren
l_int|1
op_lshift
l_int|20
op_or
l_int|1
op_lshift
l_int|21
op_or
l_int|1
op_lshift
l_int|22
op_or
l_int|1
op_lshift
l_int|23
)paren
suffix:semicolon
id|scratch
op_assign
id|scratch
op_rshift
l_int|20
suffix:semicolon
multiline_comment|/* AGP v3 capable ? */
r_if
c_cond
(paren
id|scratch
op_ge
l_int|3
)paren
(brace
id|v3_devs
op_increment
suffix:semicolon
id|printk
(paren
id|KERN_INFO
l_string|&quot;AGP: Found AGPv3 capable device at %d:%d:%d&bslash;n&quot;
comma
id|device-&gt;bus-&gt;number
comma
id|PCI_FUNC
c_func
(paren
id|device-&gt;devfn
)paren
comma
id|PCI_SLOT
c_func
(paren
id|device-&gt;devfn
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;AGP: Meh. version %x AGP device found.&bslash;n&quot;
comma
id|scratch
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* If not enough, go to AGP v2 setup */
r_if
c_cond
(paren
id|v3_devs
OL
l_int|2
)paren
(brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;AGP: Only %d devices found, not enough, trying AGPv2&bslash;n&quot;
comma
id|v3_devs
)paren
suffix:semicolon
r_return
id|agp_generic_agp_enable
c_func
(paren
id|mode
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;AGP: Enough AGPv3 devices found, setting up...&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|agp_bridge-&gt;capndx
op_plus
id|PCI_AGP_STATUS
comma
op_amp
id|command
)paren
suffix:semicolon
id|command
op_assign
id|agp_collect_device_status
c_func
(paren
id|mode
comma
id|command
)paren
suffix:semicolon
id|command
op_or_assign
l_int|0x100
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|agp_bridge-&gt;capndx
op_plus
id|PCI_AGP_COMMAND
comma
id|command
)paren
suffix:semicolon
id|agp_device_command
c_func
(paren
id|command
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|amd_8151_setup
r_static
r_int
id|__init
id|amd_8151_setup
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
id|agp_bridge-&gt;masks
op_assign
id|amd_8151_masks
suffix:semicolon
id|agp_bridge-&gt;aperture_sizes
op_assign
(paren
r_void
op_star
)paren
id|amd_8151_sizes
suffix:semicolon
id|agp_bridge-&gt;size_type
op_assign
id|U32_APER_SIZE
suffix:semicolon
id|agp_bridge-&gt;num_aperture_sizes
op_assign
l_int|7
suffix:semicolon
id|agp_bridge-&gt;dev_private_data
op_assign
l_int|NULL
suffix:semicolon
id|agp_bridge-&gt;needs_scratch_page
op_assign
id|FALSE
suffix:semicolon
id|agp_bridge-&gt;configure
op_assign
id|amd_8151_configure
suffix:semicolon
id|agp_bridge-&gt;fetch_size
op_assign
id|amd_x86_64_fetch_size
suffix:semicolon
id|agp_bridge-&gt;cleanup
op_assign
id|amd_8151_cleanup
suffix:semicolon
id|agp_bridge-&gt;tlb_flush
op_assign
id|amd_x86_64_tlbflush
suffix:semicolon
id|agp_bridge-&gt;mask_memory
op_assign
id|amd_8151_mask_memory
suffix:semicolon
id|agp_bridge-&gt;agp_enable
op_assign
id|agp_x86_64_agp_enable
suffix:semicolon
id|agp_bridge-&gt;cache_flush
op_assign
id|global_cache_flush
suffix:semicolon
id|agp_bridge-&gt;create_gatt_table
op_assign
id|agp_generic_create_gatt_table
suffix:semicolon
id|agp_bridge-&gt;free_gatt_table
op_assign
id|agp_generic_free_gatt_table
suffix:semicolon
id|agp_bridge-&gt;insert_memory
op_assign
id|x86_64_insert_memory
suffix:semicolon
id|agp_bridge-&gt;remove_memory
op_assign
id|agp_generic_remove_memory
suffix:semicolon
id|agp_bridge-&gt;alloc_by_type
op_assign
id|agp_generic_alloc_by_type
suffix:semicolon
id|agp_bridge-&gt;free_by_type
op_assign
id|agp_generic_free_by_type
suffix:semicolon
id|agp_bridge-&gt;agp_alloc_page
op_assign
id|agp_generic_alloc_page
suffix:semicolon
id|agp_bridge-&gt;agp_destroy_page
op_assign
id|agp_generic_destroy_page
suffix:semicolon
id|agp_bridge-&gt;suspend
op_assign
id|agp_generic_suspend
suffix:semicolon
id|agp_bridge-&gt;resume
op_assign
id|agp_generic_resume
suffix:semicolon
id|agp_bridge-&gt;cant_use_aperture
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|amd_k8_agp_driver
r_static
r_struct
id|agp_driver
id|amd_k8_agp_driver
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|function|agp_amdk8_probe
r_static
r_int
id|__init
id|agp_amdk8_probe
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_struct
id|pci_device_id
op_star
id|ent
)paren
(brace
id|u8
id|cap_ptr
op_assign
l_int|0
suffix:semicolon
id|cap_ptr
op_assign
id|pci_find_capability
c_func
(paren
id|dev
comma
id|PCI_CAP_ID_AGP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cap_ptr
op_eq
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|agp_bridge-&gt;dev
op_assign
id|dev
suffix:semicolon
id|agp_bridge-&gt;capndx
op_assign
id|cap_ptr
suffix:semicolon
multiline_comment|/* Fill in the mode register */
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|agp_bridge-&gt;capndx
op_plus
id|PCI_AGP_STATUS
comma
op_amp
id|agp_bridge-&gt;mode
)paren
suffix:semicolon
id|amd_8151_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
id|amd_k8_agp_driver.dev
op_assign
id|dev
suffix:semicolon
id|agp_register_driver
c_func
(paren
op_amp
id|amd_k8_agp_driver
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|pci_device_id
id|agp_amdk8_pci_table
(braket
)braket
id|__initdata
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
(brace
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|agp_amdk8_pci_table
)paren
suffix:semicolon
DECL|variable|agp_amdk8_pci_driver
r_static
r_struct
id|__initdata
id|pci_driver
id|agp_amdk8_pci_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;agpgart-amd-k8&quot;
comma
dot
id|id_table
op_assign
id|agp_amdk8_pci_table
comma
dot
id|probe
op_assign
id|agp_amdk8_probe
comma
)brace
suffix:semicolon
multiline_comment|/* Not static due to IOMMU code calling it early. */
DECL|function|agp_amdk8_init
r_int
id|__init
id|agp_amdk8_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret_val
suffix:semicolon
id|ret_val
op_assign
id|pci_module_init
c_func
(paren
op_amp
id|agp_amdk8_pci_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret_val
)paren
id|agp_bridge-&gt;type
op_assign
id|NOT_SUPPORTED
suffix:semicolon
id|agp_bridge-&gt;type
op_assign
id|AMD_8151
suffix:semicolon
r_return
id|ret_val
suffix:semicolon
)brace
DECL|function|agp_amdk8_cleanup
r_static
r_void
id|__exit
id|agp_amdk8_cleanup
c_func
(paren
r_void
)paren
(brace
id|agp_unregister_driver
c_func
(paren
op_amp
id|amd_k8_agp_driver
)paren
suffix:semicolon
id|pci_unregister_driver
c_func
(paren
op_amp
id|agp_amdk8_pci_driver
)paren
suffix:semicolon
)brace
multiline_comment|/* On x86-64 the PCI driver needs to initialize this driver early&n;   for the IOMMU, so it has to be called via a backdoor. */
macro_line|#ifndef CONFIG_GART_IOMMU
DECL|variable|agp_amdk8_init
id|module_init
c_func
(paren
id|agp_amdk8_init
)paren
suffix:semicolon
DECL|variable|agp_amdk8_cleanup
id|module_exit
c_func
(paren
id|agp_amdk8_cleanup
)paren
suffix:semicolon
macro_line|#endif
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Dave Jones &lt;davej@codemonkey.org.uk&gt;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL and additional rights&quot;
)paren
suffix:semicolon
eof
