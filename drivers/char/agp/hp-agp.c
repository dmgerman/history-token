multiline_comment|/*&n; * HP AGPGART routines. &n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/agp_backend.h&gt;
macro_line|#include &quot;agp.h&quot;
macro_line|#ifndef log2
DECL|macro|log2
mdefine_line|#define log2(x)&t;&t;ffz(~(x))
macro_line|#endif
DECL|macro|HP_ZX1_IOVA_BASE
mdefine_line|#define HP_ZX1_IOVA_BASE&t;GB(1UL)
DECL|macro|HP_ZX1_IOVA_SIZE
mdefine_line|#define HP_ZX1_IOVA_SIZE&t;GB(1UL)
DECL|macro|HP_ZX1_GART_SIZE
mdefine_line|#define HP_ZX1_GART_SIZE&t;(HP_ZX1_IOVA_SIZE / 2)
DECL|macro|HP_ZX1_SBA_IOMMU_COOKIE
mdefine_line|#define HP_ZX1_SBA_IOMMU_COOKIE&t;0x0000badbadc0ffeeUL
DECL|macro|HP_ZX1_PDIR_VALID_BIT
mdefine_line|#define HP_ZX1_PDIR_VALID_BIT&t;0x8000000000000000UL
DECL|macro|HP_ZX1_IOVA_TO_PDIR
mdefine_line|#define HP_ZX1_IOVA_TO_PDIR(va)&t;((va - hp_private.iova_base) &gt;&gt; hp_private.io_tlb_shift)
DECL|variable|hp_zx1_sizes
r_static
r_struct
id|aper_size_info_fixed
id|hp_zx1_sizes
(braket
)braket
op_assign
(brace
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* filled in by hp_zx1_fetch_size() */
)brace
suffix:semicolon
DECL|variable|hp_zx1_masks
r_static
r_struct
id|gatt_mask
id|hp_zx1_masks
(braket
)braket
op_assign
(brace
(brace
dot
id|mask
op_assign
id|HP_ZX1_PDIR_VALID_BIT
comma
dot
id|type
op_assign
l_int|0
)brace
)brace
suffix:semicolon
DECL|struct|_hp_private
r_static
r_struct
id|_hp_private
(brace
DECL|member|ioc
r_struct
id|pci_dev
op_star
id|ioc
suffix:semicolon
DECL|member|registers
r_volatile
id|u8
op_star
id|registers
suffix:semicolon
DECL|member|io_pdir
id|u64
op_star
id|io_pdir
suffix:semicolon
singleline_comment|// PDIR for entire IOVA
DECL|member|gatt
id|u64
op_star
id|gatt
suffix:semicolon
singleline_comment|// PDIR just for GART (subset of above)
DECL|member|gatt_entries
id|u64
id|gatt_entries
suffix:semicolon
DECL|member|iova_base
id|u64
id|iova_base
suffix:semicolon
DECL|member|gart_base
id|u64
id|gart_base
suffix:semicolon
DECL|member|gart_size
id|u64
id|gart_size
suffix:semicolon
DECL|member|io_pdir_size
id|u64
id|io_pdir_size
suffix:semicolon
DECL|member|io_pdir_owner
r_int
id|io_pdir_owner
suffix:semicolon
singleline_comment|// do we own it, or share it with sba_iommu?
DECL|member|io_page_size
r_int
id|io_page_size
suffix:semicolon
DECL|member|io_tlb_shift
r_int
id|io_tlb_shift
suffix:semicolon
DECL|member|io_tlb_ps
r_int
id|io_tlb_ps
suffix:semicolon
singleline_comment|// IOC ps config
DECL|member|io_pages_per_kpage
r_int
id|io_pages_per_kpage
suffix:semicolon
DECL|variable|hp_private
)brace
id|hp_private
suffix:semicolon
DECL|function|hp_zx1_ioc_shared
r_static
r_int
id|__init
id|hp_zx1_ioc_shared
c_func
(paren
r_void
)paren
(brace
r_struct
id|_hp_private
op_star
id|hp
op_assign
op_amp
id|hp_private
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;HP ZX1 IOC: IOPDIR shared with sba_iommu&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * IOC already configured by sba_iommu module; just use&n;&t; * its setup.  We assume:&n;&t; * &t;- IOVA space is 1Gb in size&n;&t; * &t;- first 512Mb is IOMMU, second 512Mb is GART&n;&t; */
id|hp-&gt;io_tlb_ps
op_assign
id|INREG64
c_func
(paren
id|hp-&gt;registers
comma
id|HP_ZX1_TCNFG
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|hp-&gt;io_tlb_ps
)paren
(brace
r_case
l_int|0
suffix:colon
id|hp-&gt;io_tlb_shift
op_assign
l_int|12
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|hp-&gt;io_tlb_shift
op_assign
l_int|13
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|hp-&gt;io_tlb_shift
op_assign
l_int|14
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|hp-&gt;io_tlb_shift
op_assign
l_int|16
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Invalid IOTLB page size &quot;
l_string|&quot;configuration 0x%x&bslash;n&quot;
comma
id|hp-&gt;io_tlb_ps
)paren
suffix:semicolon
id|hp-&gt;gatt
op_assign
l_int|0
suffix:semicolon
id|hp-&gt;gatt_entries
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|hp-&gt;io_page_size
op_assign
l_int|1
op_lshift
id|hp-&gt;io_tlb_shift
suffix:semicolon
id|hp-&gt;io_pages_per_kpage
op_assign
id|PAGE_SIZE
op_div
id|hp-&gt;io_page_size
suffix:semicolon
id|hp-&gt;iova_base
op_assign
id|INREG64
c_func
(paren
id|hp-&gt;registers
comma
id|HP_ZX1_IBASE
)paren
op_amp
op_complement
l_int|0x1
suffix:semicolon
id|hp-&gt;gart_base
op_assign
id|hp-&gt;iova_base
op_plus
id|HP_ZX1_IOVA_SIZE
op_minus
id|HP_ZX1_GART_SIZE
suffix:semicolon
id|hp-&gt;gart_size
op_assign
id|HP_ZX1_GART_SIZE
suffix:semicolon
id|hp-&gt;gatt_entries
op_assign
id|hp-&gt;gart_size
op_div
id|hp-&gt;io_page_size
suffix:semicolon
id|hp-&gt;io_pdir
op_assign
id|phys_to_virt
c_func
(paren
id|INREG64
c_func
(paren
id|hp-&gt;registers
comma
id|HP_ZX1_PDIR_BASE
)paren
)paren
suffix:semicolon
id|hp-&gt;gatt
op_assign
op_amp
id|hp-&gt;io_pdir
(braket
id|HP_ZX1_IOVA_TO_PDIR
c_func
(paren
id|hp-&gt;gart_base
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hp-&gt;gatt
(braket
l_int|0
)braket
op_ne
id|HP_ZX1_SBA_IOMMU_COOKIE
)paren
(brace
id|hp-&gt;gatt
op_assign
l_int|0
suffix:semicolon
id|hp-&gt;gatt_entries
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;No reserved IO PDIR entry found; &quot;
l_string|&quot;GART disabled&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hp_zx1_ioc_owner
r_static
r_int
id|__init
id|hp_zx1_ioc_owner
c_func
(paren
id|u8
id|ioc_rev
)paren
(brace
r_struct
id|_hp_private
op_star
id|hp
op_assign
op_amp
id|hp_private
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;HP ZX1 IOC: IOPDIR dedicated to GART&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Select an IOV page size no larger than system page size.&n;&t; */
r_if
c_cond
(paren
id|PAGE_SIZE
op_ge
id|KB
c_func
(paren
l_int|64
)paren
)paren
(brace
id|hp-&gt;io_tlb_shift
op_assign
l_int|16
suffix:semicolon
id|hp-&gt;io_tlb_ps
op_assign
l_int|3
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|PAGE_SIZE
op_ge
id|KB
c_func
(paren
l_int|16
)paren
)paren
(brace
id|hp-&gt;io_tlb_shift
op_assign
l_int|14
suffix:semicolon
id|hp-&gt;io_tlb_ps
op_assign
l_int|2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|PAGE_SIZE
op_ge
id|KB
c_func
(paren
l_int|8
)paren
)paren
(brace
id|hp-&gt;io_tlb_shift
op_assign
l_int|13
suffix:semicolon
id|hp-&gt;io_tlb_ps
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|hp-&gt;io_tlb_shift
op_assign
l_int|12
suffix:semicolon
id|hp-&gt;io_tlb_ps
op_assign
l_int|0
suffix:semicolon
)brace
id|hp-&gt;io_page_size
op_assign
l_int|1
op_lshift
id|hp-&gt;io_tlb_shift
suffix:semicolon
id|hp-&gt;io_pages_per_kpage
op_assign
id|PAGE_SIZE
op_div
id|hp-&gt;io_page_size
suffix:semicolon
id|hp-&gt;iova_base
op_assign
id|HP_ZX1_IOVA_BASE
suffix:semicolon
id|hp-&gt;gart_size
op_assign
id|HP_ZX1_GART_SIZE
suffix:semicolon
id|hp-&gt;gart_base
op_assign
id|hp-&gt;iova_base
op_plus
id|HP_ZX1_IOVA_SIZE
op_minus
id|hp-&gt;gart_size
suffix:semicolon
id|hp-&gt;gatt_entries
op_assign
id|hp-&gt;gart_size
op_div
id|hp-&gt;io_page_size
suffix:semicolon
id|hp-&gt;io_pdir_size
op_assign
(paren
id|HP_ZX1_IOVA_SIZE
op_div
id|hp-&gt;io_page_size
)paren
op_star
r_sizeof
(paren
id|u64
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hp_zx1_ioc_init
r_static
r_int
id|__init
id|hp_zx1_ioc_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|_hp_private
op_star
id|hp
op_assign
op_amp
id|hp_private
suffix:semicolon
r_struct
id|pci_dev
op_star
id|ioc
suffix:semicolon
r_int
id|i
suffix:semicolon
id|u8
id|ioc_rev
suffix:semicolon
id|ioc
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_HP
comma
id|PCI_DEVICE_ID_HP_ZX1_IOC
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ioc
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Detected HP ZX1 AGP bridge but no IOC&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|hp-&gt;ioc
op_assign
id|ioc
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|ioc
comma
id|PCI_REVISION_ID
comma
op_amp
id|ioc_rev
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
id|PCI_NUM_RESOURCES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pci_resource_flags
c_func
(paren
id|ioc
comma
id|i
)paren
op_eq
id|IORESOURCE_MEM
)paren
(brace
id|hp-&gt;registers
op_assign
(paren
id|u8
op_star
)paren
id|ioremap
c_func
(paren
id|pci_resource_start
c_func
(paren
id|ioc
comma
id|i
)paren
comma
id|pci_resource_len
c_func
(paren
id|ioc
comma
id|i
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|hp-&gt;registers
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Detected HP ZX1 AGP bridge but no CSRs&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If the IOTLB is currently disabled, we can take it over.&n;&t; * Otherwise, we have to share with sba_iommu.&n;&t; */
id|hp-&gt;io_pdir_owner
op_assign
(paren
id|INREG64
c_func
(paren
id|hp-&gt;registers
comma
id|HP_ZX1_IBASE
)paren
op_amp
l_int|0x1
)paren
op_eq
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|hp-&gt;io_pdir_owner
)paren
r_return
id|hp_zx1_ioc_owner
c_func
(paren
id|ioc_rev
)paren
suffix:semicolon
r_return
id|hp_zx1_ioc_shared
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|hp_zx1_fetch_size
r_static
r_int
id|hp_zx1_fetch_size
c_func
(paren
r_void
)paren
(brace
r_int
id|size
suffix:semicolon
id|size
op_assign
id|hp_private.gart_size
op_div
id|MB
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|hp_zx1_sizes
(braket
l_int|0
)braket
dot
id|size
op_assign
id|size
suffix:semicolon
id|agp_bridge.current_size
op_assign
(paren
r_void
op_star
)paren
op_amp
id|hp_zx1_sizes
(braket
l_int|0
)braket
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
DECL|function|hp_zx1_configure
r_static
r_int
id|hp_zx1_configure
c_func
(paren
r_void
)paren
(brace
r_struct
id|_hp_private
op_star
id|hp
op_assign
op_amp
id|hp_private
suffix:semicolon
id|agp_bridge.gart_bus_addr
op_assign
id|hp-&gt;gart_base
suffix:semicolon
id|agp_bridge.capndx
op_assign
id|pci_find_capability
c_func
(paren
id|agp_bridge.dev
comma
id|PCI_CAP_ID_AGP
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|agp_bridge.dev
comma
id|agp_bridge.capndx
op_plus
id|PCI_AGP_STATUS
comma
op_amp
id|agp_bridge.mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hp-&gt;io_pdir_owner
)paren
(brace
id|OUTREG64
c_func
(paren
id|hp-&gt;registers
comma
id|HP_ZX1_PDIR_BASE
comma
id|virt_to_phys
c_func
(paren
id|hp-&gt;io_pdir
)paren
)paren
suffix:semicolon
id|OUTREG64
c_func
(paren
id|hp-&gt;registers
comma
id|HP_ZX1_TCNFG
comma
id|hp-&gt;io_tlb_ps
)paren
suffix:semicolon
id|OUTREG64
c_func
(paren
id|hp-&gt;registers
comma
id|HP_ZX1_IMASK
comma
op_complement
(paren
id|HP_ZX1_IOVA_SIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|OUTREG64
c_func
(paren
id|hp-&gt;registers
comma
id|HP_ZX1_IBASE
comma
id|hp-&gt;iova_base
op_or
l_int|0x1
)paren
suffix:semicolon
id|OUTREG64
c_func
(paren
id|hp-&gt;registers
comma
id|HP_ZX1_PCOM
comma
id|hp-&gt;iova_base
op_or
id|log2
c_func
(paren
id|HP_ZX1_IOVA_SIZE
)paren
)paren
suffix:semicolon
id|INREG64
c_func
(paren
id|hp-&gt;registers
comma
id|HP_ZX1_PCOM
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hp_zx1_cleanup
r_static
r_void
id|hp_zx1_cleanup
c_func
(paren
r_void
)paren
(brace
r_struct
id|_hp_private
op_star
id|hp
op_assign
op_amp
id|hp_private
suffix:semicolon
r_if
c_cond
(paren
id|hp-&gt;io_pdir_owner
)paren
id|OUTREG64
c_func
(paren
id|hp-&gt;registers
comma
id|HP_ZX1_IBASE
comma
l_int|0
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|hp-&gt;registers
)paren
suffix:semicolon
)brace
DECL|function|hp_zx1_tlbflush
r_static
r_void
id|hp_zx1_tlbflush
c_func
(paren
id|agp_memory
op_star
id|mem
)paren
(brace
r_struct
id|_hp_private
op_star
id|hp
op_assign
op_amp
id|hp_private
suffix:semicolon
id|OUTREG64
c_func
(paren
id|hp-&gt;registers
comma
id|HP_ZX1_PCOM
comma
id|hp-&gt;gart_base
op_or
id|log2
c_func
(paren
id|hp-&gt;gart_size
)paren
)paren
suffix:semicolon
id|INREG64
c_func
(paren
id|hp-&gt;registers
comma
id|HP_ZX1_PCOM
)paren
suffix:semicolon
)brace
DECL|function|hp_zx1_create_gatt_table
r_static
r_int
id|hp_zx1_create_gatt_table
c_func
(paren
r_void
)paren
(brace
r_struct
id|_hp_private
op_star
id|hp
op_assign
op_amp
id|hp_private
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|hp-&gt;io_pdir_owner
)paren
(brace
id|hp-&gt;io_pdir
op_assign
(paren
id|u64
op_star
)paren
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
id|get_order
c_func
(paren
id|hp-&gt;io_pdir_size
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hp-&gt;io_pdir
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Couldn&squot;t allocate contiguous &quot;
l_string|&quot;memory for I/O PDIR&bslash;n&quot;
)paren
suffix:semicolon
id|hp-&gt;gatt
op_assign
l_int|0
suffix:semicolon
id|hp-&gt;gatt_entries
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|hp-&gt;io_pdir
comma
l_int|0
comma
id|hp-&gt;io_pdir_size
)paren
suffix:semicolon
id|hp-&gt;gatt
op_assign
op_amp
id|hp-&gt;io_pdir
(braket
id|HP_ZX1_IOVA_TO_PDIR
c_func
(paren
id|hp-&gt;gart_base
)paren
)braket
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
id|hp-&gt;gatt_entries
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hp-&gt;gatt
(braket
id|i
)braket
op_assign
(paren
r_int
r_int
)paren
id|agp_bridge.scratch_page
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hp_zx1_free_gatt_table
r_static
r_int
id|hp_zx1_free_gatt_table
c_func
(paren
r_void
)paren
(brace
r_struct
id|_hp_private
op_star
id|hp
op_assign
op_amp
id|hp_private
suffix:semicolon
r_if
c_cond
(paren
id|hp-&gt;io_pdir_owner
)paren
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|hp-&gt;io_pdir
comma
id|get_order
c_func
(paren
id|hp-&gt;io_pdir_size
)paren
)paren
suffix:semicolon
r_else
id|hp-&gt;gatt
(braket
l_int|0
)braket
op_assign
id|HP_ZX1_SBA_IOMMU_COOKIE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hp_zx1_insert_memory
r_static
r_int
id|hp_zx1_insert_memory
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
r_struct
id|_hp_private
op_star
id|hp
op_assign
op_amp
id|hp_private
suffix:semicolon
r_int
id|i
comma
id|k
suffix:semicolon
id|off_t
id|j
comma
id|io_pg_start
suffix:semicolon
r_int
id|io_pg_count
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
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|io_pg_start
op_assign
id|hp-&gt;io_pages_per_kpage
op_star
id|pg_start
suffix:semicolon
id|io_pg_count
op_assign
id|hp-&gt;io_pages_per_kpage
op_star
id|mem-&gt;page_count
suffix:semicolon
r_if
c_cond
(paren
(paren
id|io_pg_start
op_plus
id|io_pg_count
)paren
OG
id|hp-&gt;gatt_entries
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|j
op_assign
id|io_pg_start
suffix:semicolon
r_while
c_loop
(paren
id|j
OL
(paren
id|io_pg_start
op_plus
id|io_pg_count
)paren
)paren
(brace
r_if
c_cond
(paren
id|hp-&gt;gatt
(braket
id|j
)braket
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
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
id|io_pg_start
suffix:semicolon
id|i
OL
id|mem-&gt;page_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|paddr
suffix:semicolon
id|paddr
op_assign
id|mem-&gt;memory
(braket
id|i
)braket
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|hp-&gt;io_pages_per_kpage
suffix:semicolon
id|k
op_increment
comma
id|j
op_increment
comma
id|paddr
op_add_assign
id|hp-&gt;io_page_size
)paren
(brace
id|hp-&gt;gatt
(braket
id|j
)braket
op_assign
id|agp_bridge
dot
id|mask_memory
c_func
(paren
id|paddr
comma
id|type
)paren
suffix:semicolon
)brace
)brace
id|agp_bridge
dot
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
DECL|function|hp_zx1_remove_memory
r_static
r_int
id|hp_zx1_remove_memory
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
r_struct
id|_hp_private
op_star
id|hp
op_assign
op_amp
id|hp_private
suffix:semicolon
r_int
id|i
comma
id|io_pg_start
comma
id|io_pg_count
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
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|io_pg_start
op_assign
id|hp-&gt;io_pages_per_kpage
op_star
id|pg_start
suffix:semicolon
id|io_pg_count
op_assign
id|hp-&gt;io_pages_per_kpage
op_star
id|mem-&gt;page_count
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|io_pg_start
suffix:semicolon
id|i
OL
id|io_pg_count
op_plus
id|io_pg_start
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hp-&gt;gatt
(braket
id|i
)braket
op_assign
id|agp_bridge.scratch_page
suffix:semicolon
)brace
id|agp_bridge
dot
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
DECL|function|hp_zx1_mask_memory
r_static
r_int
r_int
id|hp_zx1_mask_memory
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
id|HP_ZX1_PDIR_VALID_BIT
op_or
id|addr
suffix:semicolon
)brace
DECL|function|hp_zx1_setup
r_static
r_int
id|__init
id|hp_zx1_setup
(paren
r_struct
id|pci_dev
op_star
id|pdev
id|__attribute__
c_func
(paren
(paren
id|unused
)paren
)paren
)paren
(brace
id|agp_bridge.masks
op_assign
id|hp_zx1_masks
suffix:semicolon
id|agp_bridge.num_of_masks
op_assign
l_int|1
suffix:semicolon
id|agp_bridge.dev_private_data
op_assign
l_int|NULL
suffix:semicolon
id|agp_bridge.size_type
op_assign
id|FIXED_APER_SIZE
suffix:semicolon
id|agp_bridge.needs_scratch_page
op_assign
id|FALSE
suffix:semicolon
id|agp_bridge.configure
op_assign
id|hp_zx1_configure
suffix:semicolon
id|agp_bridge.fetch_size
op_assign
id|hp_zx1_fetch_size
suffix:semicolon
id|agp_bridge.cleanup
op_assign
id|hp_zx1_cleanup
suffix:semicolon
id|agp_bridge.tlb_flush
op_assign
id|hp_zx1_tlbflush
suffix:semicolon
id|agp_bridge.mask_memory
op_assign
id|hp_zx1_mask_memory
suffix:semicolon
id|agp_bridge.agp_enable
op_assign
id|agp_generic_agp_enable
suffix:semicolon
id|agp_bridge.cache_flush
op_assign
id|global_cache_flush
suffix:semicolon
id|agp_bridge.create_gatt_table
op_assign
id|hp_zx1_create_gatt_table
suffix:semicolon
id|agp_bridge.free_gatt_table
op_assign
id|hp_zx1_free_gatt_table
suffix:semicolon
id|agp_bridge.insert_memory
op_assign
id|hp_zx1_insert_memory
suffix:semicolon
id|agp_bridge.remove_memory
op_assign
id|hp_zx1_remove_memory
suffix:semicolon
id|agp_bridge.alloc_by_type
op_assign
id|agp_generic_alloc_by_type
suffix:semicolon
id|agp_bridge.free_by_type
op_assign
id|agp_generic_free_by_type
suffix:semicolon
id|agp_bridge.agp_alloc_page
op_assign
id|agp_generic_alloc_page
suffix:semicolon
id|agp_bridge.agp_destroy_page
op_assign
id|agp_generic_destroy_page
suffix:semicolon
id|agp_bridge.cant_use_aperture
op_assign
l_int|1
suffix:semicolon
r_return
id|hp_zx1_ioc_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|agp_find_supported_device
r_static
r_int
id|__init
id|agp_find_supported_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|agp_bridge.dev
op_assign
id|dev
suffix:semicolon
multiline_comment|/* ZX1 LBAs can be either PCI or AGP bridges */
r_if
c_cond
(paren
id|pci_find_capability
c_func
(paren
id|dev
comma
id|PCI_CAP_ID_AGP
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;Detected HP ZX1 AGP chipset at %s&bslash;n&quot;
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
id|agp_bridge.type
op_assign
id|HP_ZX1
suffix:semicolon
id|agp_bridge.dev
op_assign
id|dev
suffix:semicolon
r_return
id|hp_zx1_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
r_static
r_int
id|__init
id|agp_hp_probe
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
r_if
c_cond
(paren
id|agp_find_supported_device
c_func
(paren
id|dev
)paren
op_eq
l_int|0
)paren
(brace
id|agp_register_driver
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_static
r_struct
id|pci_device_id
id|agp_hp_pci_table
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
id|vendor_id
op_assign
id|PCI_VENDOR_ID_HP
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_HP_ZX1_LBA
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
id|agp_pci_table
)paren
suffix:semicolon
r_static
r_struct
id|__initdata
id|pci_driver
id|agp_hp_pci_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;agpgart-hp&quot;
comma
dot
id|id_table
op_assign
id|agp_hp_pci_table
comma
dot
id|probe
op_assign
id|agp_hp_probe
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
id|agp_hp_init
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
id|agp_hp_pci_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret_val
)paren
id|agp_bridge.type
op_assign
id|NOT_SUPPORTED
suffix:semicolon
r_return
id|ret_val
suffix:semicolon
)brace
r_static
r_void
id|__exit
id|agp_hp_cleanup
c_func
(paren
r_void
)paren
(brace
id|agp_unregister_driver
c_func
(paren
)paren
suffix:semicolon
id|pci_unregister_driver
c_func
(paren
op_amp
id|agp_pci_driver
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|agp_hp_init
)paren
suffix:semicolon
id|module_exit
c_func
(paren
id|agp_hp_cleanup
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL and additional rights&quot;
)paren
suffix:semicolon
eof
