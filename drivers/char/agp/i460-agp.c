multiline_comment|/*&n; * For documentation on the i460 AGP interface, see Chapter 7 (AGP Subsystem) of&n; * the &quot;Intel 460GTX Chipset Software Developer&squot;s Manual&quot;:&n; * http://developer.intel.com/design/itanium/downloads/24870401s.htm&n; */
multiline_comment|/*&n; * 460GX support by Chris Ahna &lt;christopher.j.ahna@intel.com&gt;&n; * Clean up &amp; simplification by David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/agp_backend.h&gt;
macro_line|#include &quot;agp.h&quot;
multiline_comment|/*&n; * The i460 can operate with large (4MB) pages, but there is no sane way to support this&n; * within the current kernel/DRM environment, so we disable the relevant code for now.&n; * See also comments in ia64_alloc_page()...&n; */
DECL|macro|I460_LARGE_IO_PAGES
mdefine_line|#define I460_LARGE_IO_PAGES&t;&t;0
macro_line|#if I460_LARGE_IO_PAGES
DECL|macro|I460_IO_PAGE_SHIFT
macro_line|# define I460_IO_PAGE_SHIFT&t;&t;i460.io_page_shift
macro_line|#else
DECL|macro|I460_IO_PAGE_SHIFT
macro_line|# define I460_IO_PAGE_SHIFT&t;&t;12
macro_line|#endif
DECL|macro|I460_IOPAGES_PER_KPAGE
mdefine_line|#define I460_IOPAGES_PER_KPAGE&t;&t;(PAGE_SIZE &gt;&gt; I460_IO_PAGE_SHIFT)
DECL|macro|I460_KPAGES_PER_IOPAGE
mdefine_line|#define I460_KPAGES_PER_IOPAGE&t;&t;(1 &lt;&lt; (I460_IO_PAGE_SHIFT - PAGE_SHIFT))
DECL|macro|I460_SRAM_IO_DISABLE
mdefine_line|#define I460_SRAM_IO_DISABLE&t;&t;(1 &lt;&lt; 4)
DECL|macro|I460_BAPBASE_ENABLE
mdefine_line|#define I460_BAPBASE_ENABLE&t;&t;(1 &lt;&lt; 3)
DECL|macro|I460_AGPSIZ_MASK
mdefine_line|#define I460_AGPSIZ_MASK&t;&t;0x7
DECL|macro|I460_4M_PS
mdefine_line|#define I460_4M_PS&t;&t;&t;(1 &lt;&lt; 1)
multiline_comment|/* Control bits for Out-Of-GART coherency and Burst Write Combining */
DECL|macro|I460_GXBCTL_OOG
mdefine_line|#define I460_GXBCTL_OOG&t;&t;(1UL &lt;&lt; 0)
DECL|macro|I460_GXBCTL_BWC
mdefine_line|#define I460_GXBCTL_BWC&t;&t;(1UL &lt;&lt; 2)
multiline_comment|/*&n; * gatt_table entries are 32-bits wide on the i460; the generic code ought to declare the&n; * gatt_table and gatt_table_real pointers a &quot;void *&quot;...&n; */
DECL|macro|RD_GATT
mdefine_line|#define RD_GATT(index)&t;&t;readl((u32 *) i460.gatt + (index))
DECL|macro|WR_GATT
mdefine_line|#define WR_GATT(index, val)&t;writel((val), (u32 *) i460.gatt + (index))
multiline_comment|/*&n; * The 460 spec says we have to read the last location written to make sure that all&n; * writes have taken effect&n; */
DECL|macro|WR_FLUSH_GATT
mdefine_line|#define WR_FLUSH_GATT(index)&t;RD_GATT(index)
DECL|macro|log2
mdefine_line|#define log2(x)&t;&t;&t;ffz(~(x))
r_static
r_struct
(brace
DECL|member|gatt
r_void
op_star
id|gatt
suffix:semicolon
multiline_comment|/* ioremap&squot;d GATT area */
multiline_comment|/* i460 supports multiple GART page sizes, so GART pageshift is dynamic: */
DECL|member|io_page_shift
id|u8
id|io_page_shift
suffix:semicolon
multiline_comment|/* BIOS configures chipset to one of 2 possible apbase values: */
DECL|member|dynamic_apbase
id|u8
id|dynamic_apbase
suffix:semicolon
multiline_comment|/* structure for tracking partial use of 4MB GART pages: */
DECL|struct|lp_desc
r_struct
id|lp_desc
(brace
DECL|member|alloced_map
r_int
r_int
op_star
id|alloced_map
suffix:semicolon
multiline_comment|/* bitmap of kernel-pages in use */
DECL|member|refcount
r_int
id|refcount
suffix:semicolon
multiline_comment|/* number of kernel pages using the large page */
DECL|member|paddr
id|u64
id|paddr
suffix:semicolon
multiline_comment|/* physical address of large page */
DECL|member|lp_desc
)brace
op_star
id|lp_desc
suffix:semicolon
DECL|variable|i460
)brace
id|i460
suffix:semicolon
DECL|variable|i460_sizes
r_static
r_struct
id|aper_size_info_8
id|i460_sizes
(braket
l_int|3
)braket
op_assign
(brace
multiline_comment|/*&n;&t; * The 32GB aperture is only available with a 4M GART page size.  Due to the&n;&t; * dynamic GART page size, we can&squot;t figure out page_order or num_entries until&n;&t; * runtime.&n;&t; */
(brace
l_int|32768
comma
l_int|0
comma
l_int|0
comma
l_int|4
)brace
comma
(brace
l_int|1024
comma
l_int|0
comma
l_int|0
comma
l_int|2
)brace
comma
(brace
l_int|256
comma
l_int|0
comma
l_int|0
comma
l_int|1
)brace
)brace
suffix:semicolon
DECL|variable|i460_masks
r_static
r_struct
id|gatt_mask
id|i460_masks
(braket
)braket
op_assign
(brace
(brace
dot
id|mask
op_assign
id|INTEL_I460_GATT_VALID
op_or
id|INTEL_I460_GATT_COHERENT
comma
dot
id|type
op_assign
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|i460_fetch_size
r_static
r_int
id|i460_fetch_size
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|u8
id|temp
suffix:semicolon
r_struct
id|aper_size_info_8
op_star
id|values
suffix:semicolon
multiline_comment|/* Determine the GART page size */
id|pci_read_config_byte
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|INTEL_I460_GXBCTL
comma
op_amp
id|temp
)paren
suffix:semicolon
id|i460.io_page_shift
op_assign
(paren
id|temp
op_amp
id|I460_4M_PS
)paren
ques
c_cond
l_int|22
suffix:colon
l_int|12
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;i460_fetch_size: io_page_shift=%d&bslash;n&quot;
comma
id|i460.io_page_shift
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i460.io_page_shift
op_ne
id|I460_IO_PAGE_SHIFT
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;I/O (GART) page-size %ZuKB doesn&squot;t match expected size %ZuKB&bslash;n&quot;
comma
l_int|1UL
op_lshift
(paren
id|i460.io_page_shift
op_minus
l_int|10
)paren
comma
l_int|1UL
op_lshift
(paren
id|I460_IO_PAGE_SHIFT
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|values
op_assign
id|A_SIZE_8
c_func
(paren
id|agp_bridge-&gt;driver-&gt;aperture_sizes
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|INTEL_I460_AGPSIZ
comma
op_amp
id|temp
)paren
suffix:semicolon
multiline_comment|/* Exit now if the IO drivers for the GART SRAMS are turned off */
r_if
c_cond
(paren
id|temp
op_amp
id|I460_SRAM_IO_DISABLE
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;GART SRAMS disabled on 460GX chipset&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;AGPGART operation not possible&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Make sure we don&squot;t try to create an 2 ^ 23 entry GATT */
r_if
c_cond
(paren
(paren
id|i460.io_page_shift
op_eq
l_int|0
)paren
op_logical_and
(paren
(paren
id|temp
op_amp
id|I460_AGPSIZ_MASK
)paren
op_eq
l_int|4
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;We can&squot;t have a 32GB aperture with 4KB GART pages&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Determine the proper APBASE register */
r_if
c_cond
(paren
id|temp
op_amp
id|I460_BAPBASE_ENABLE
)paren
id|i460.dynamic_apbase
op_assign
id|INTEL_I460_BAPBASE
suffix:semicolon
r_else
id|i460.dynamic_apbase
op_assign
id|INTEL_I460_APBASE
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
multiline_comment|/*&n;&t;&t; * Dynamically calculate the proper num_entries and page_order values for&n;&t;&t; * the define aperture sizes. Take care not to shift off the end of&n;&t;&t; * values[i].size.&n;&t;&t; */
id|values
(braket
id|i
)braket
dot
id|num_entries
op_assign
(paren
id|values
(braket
id|i
)braket
dot
id|size
op_lshift
l_int|8
)paren
op_rshift
(paren
id|I460_IO_PAGE_SHIFT
op_minus
l_int|12
)paren
suffix:semicolon
id|values
(braket
id|i
)braket
dot
id|page_order
op_assign
id|log2
c_func
(paren
(paren
r_sizeof
(paren
id|u32
)paren
op_star
id|values
(braket
id|i
)braket
dot
id|num_entries
)paren
op_rshift
id|PAGE_SHIFT
)paren
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
id|agp_bridge-&gt;driver-&gt;num_aperture_sizes
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Neglect control bits when matching up size_value */
r_if
c_cond
(paren
(paren
id|temp
op_amp
id|I460_AGPSIZ_MASK
)paren
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
multiline_comment|/* There isn&squot;t anything to do here since 460 has no GART TLB. */
DECL|function|i460_tlb_flush
r_static
r_void
id|i460_tlb_flush
(paren
id|agp_memory
op_star
id|mem
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * This utility function is needed to prevent corruption of the control bits&n; * which are stored along with the aperture size in 460&squot;s AGPSIZ register&n; */
DECL|function|i460_write_agpsiz
r_static
r_void
id|i460_write_agpsiz
(paren
id|u8
id|size_value
)paren
(brace
id|u8
id|temp
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|INTEL_I460_AGPSIZ
comma
op_amp
id|temp
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|INTEL_I460_AGPSIZ
comma
(paren
(paren
id|temp
op_amp
op_complement
id|I460_AGPSIZ_MASK
)paren
op_or
id|size_value
)paren
)paren
suffix:semicolon
)brace
DECL|function|i460_cleanup
r_static
r_void
id|i460_cleanup
(paren
r_void
)paren
(brace
r_struct
id|aper_size_info_8
op_star
id|previous_size
suffix:semicolon
id|previous_size
op_assign
id|A_SIZE_8
c_func
(paren
id|agp_bridge-&gt;previous_size
)paren
suffix:semicolon
id|i460_write_agpsiz
c_func
(paren
id|previous_size-&gt;size_value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|I460_IO_PAGE_SHIFT
OG
id|PAGE_SHIFT
)paren
id|kfree
c_func
(paren
id|i460.lp_desc
)paren
suffix:semicolon
)brace
DECL|function|i460_configure
r_static
r_int
id|i460_configure
(paren
r_void
)paren
(brace
r_union
(brace
id|u32
id|small
(braket
l_int|2
)braket
suffix:semicolon
id|u64
id|large
suffix:semicolon
)brace
id|temp
suffix:semicolon
r_int
id|size
suffix:semicolon
id|u8
id|scratch
suffix:semicolon
r_struct
id|aper_size_info_8
op_star
id|current_size
suffix:semicolon
id|temp.large
op_assign
l_int|0
suffix:semicolon
id|current_size
op_assign
id|A_SIZE_8
c_func
(paren
id|agp_bridge-&gt;current_size
)paren
suffix:semicolon
id|i460_write_agpsiz
c_func
(paren
id|current_size-&gt;size_value
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Do the necessary rigmarole to read all eight bytes of APBASE.&n;&t; * This has to be done since the AGP aperture can be above 4GB on&n;&t; * 460 based systems.&n;&t; */
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|i460.dynamic_apbase
comma
op_amp
(paren
id|temp.small
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|i460.dynamic_apbase
op_plus
l_int|4
comma
op_amp
(paren
id|temp.small
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
multiline_comment|/* Clear BAR control bits */
id|agp_bridge-&gt;gart_bus_addr
op_assign
id|temp.large
op_amp
op_complement
(paren
(paren
l_int|1UL
op_lshift
l_int|3
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|INTEL_I460_GXBCTL
comma
op_amp
id|scratch
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|agp_bridge-&gt;dev
comma
id|INTEL_I460_GXBCTL
comma
(paren
id|scratch
op_amp
l_int|0x02
)paren
op_or
id|I460_GXBCTL_OOG
op_or
id|I460_GXBCTL_BWC
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize partial allocation trackers if a GART page is bigger than a kernel&n;&t; * page.&n;&t; */
r_if
c_cond
(paren
id|I460_IO_PAGE_SHIFT
OG
id|PAGE_SHIFT
)paren
(brace
id|size
op_assign
id|current_size-&gt;num_entries
op_star
r_sizeof
(paren
id|i460.lp_desc
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|i460.lp_desc
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i460.lp_desc
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|i460.lp_desc
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i460_create_gatt_table
r_static
r_int
id|i460_create_gatt_table
(paren
r_void
)paren
(brace
r_int
id|page_order
comma
id|num_entries
comma
id|i
suffix:semicolon
r_void
op_star
id|temp
suffix:semicolon
multiline_comment|/*&n;&t; * Load up the fixed address of the GART SRAMS which hold our GATT table.&n;&t; */
id|temp
op_assign
id|agp_bridge-&gt;current_size
suffix:semicolon
id|page_order
op_assign
id|A_SIZE_8
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|page_order
suffix:semicolon
id|num_entries
op_assign
id|A_SIZE_8
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|num_entries
suffix:semicolon
id|i460.gatt
op_assign
id|ioremap
c_func
(paren
id|INTEL_I460_ATTBASE
comma
id|PAGE_SIZE
op_lshift
id|page_order
)paren
suffix:semicolon
multiline_comment|/* These are no good, the should be removed from the agp_bridge strucure... */
id|agp_bridge-&gt;gatt_table_real
op_assign
l_int|NULL
suffix:semicolon
id|agp_bridge-&gt;gatt_table
op_assign
l_int|NULL
suffix:semicolon
id|agp_bridge-&gt;gatt_bus_addr
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
id|num_entries
suffix:semicolon
op_increment
id|i
)paren
id|WR_GATT
c_func
(paren
id|i
comma
l_int|0
)paren
suffix:semicolon
id|WR_FLUSH_GATT
c_func
(paren
id|i
op_minus
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i460_free_gatt_table
r_static
r_int
id|i460_free_gatt_table
(paren
r_void
)paren
(brace
r_int
id|num_entries
comma
id|i
suffix:semicolon
r_void
op_star
id|temp
suffix:semicolon
id|temp
op_assign
id|agp_bridge-&gt;current_size
suffix:semicolon
id|num_entries
op_assign
id|A_SIZE_8
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|num_entries
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
id|num_entries
suffix:semicolon
op_increment
id|i
)paren
id|WR_GATT
c_func
(paren
id|i
comma
l_int|0
)paren
suffix:semicolon
id|WR_FLUSH_GATT
c_func
(paren
id|num_entries
op_minus
l_int|1
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|i460.gatt
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * The following functions are called when the I/O (GART) page size is smaller than&n; * PAGE_SIZE.&n; */
DECL|function|i460_insert_memory_small_io_page
r_static
r_int
id|i460_insert_memory_small_io_page
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
r_int
id|paddr
comma
id|io_pg_start
comma
id|io_page_size
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|k
comma
id|num_entries
suffix:semicolon
r_void
op_star
id|temp
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;i460_insert_memory_small_io_page(mem=%p, pg_start=%ld, type=%d, paddr0=0x%lx)&bslash;n&quot;
comma
id|mem
comma
id|pg_start
comma
id|type
comma
id|mem-&gt;memory
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|io_pg_start
op_assign
id|I460_IOPAGES_PER_KPAGE
op_star
id|pg_start
suffix:semicolon
id|temp
op_assign
id|agp_bridge-&gt;current_size
suffix:semicolon
id|num_entries
op_assign
id|A_SIZE_8
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|num_entries
suffix:semicolon
r_if
c_cond
(paren
(paren
id|io_pg_start
op_plus
id|I460_IOPAGES_PER_KPAGE
op_star
id|mem-&gt;page_count
)paren
OG
id|num_entries
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Looks like we&squot;re out of AGP memory&bslash;n&quot;
)paren
suffix:semicolon
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
id|I460_IOPAGES_PER_KPAGE
op_star
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
id|RD_GATT
c_func
(paren
id|j
)paren
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;i460_insert_memory_small_io_page: GATT[%d]=0x%x is busy&bslash;n&quot;
comma
id|j
comma
id|RD_GATT
c_func
(paren
id|j
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|j
op_increment
suffix:semicolon
)brace
id|io_page_size
op_assign
l_int|1UL
op_lshift
id|I460_IO_PAGE_SHIFT
suffix:semicolon
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
id|I460_IOPAGES_PER_KPAGE
suffix:semicolon
id|k
op_increment
comma
id|j
op_increment
comma
id|paddr
op_add_assign
id|io_page_size
)paren
id|WR_GATT
c_func
(paren
id|j
comma
id|agp_bridge-&gt;driver
op_member_access_from_pointer
id|mask_memory
c_func
(paren
id|paddr
comma
id|mem-&gt;type
)paren
)paren
suffix:semicolon
)brace
id|WR_FLUSH_GATT
c_func
(paren
id|j
op_minus
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i460_remove_memory_small_io_page
r_static
r_int
id|i460_remove_memory_small_io_page
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
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;i460_remove_memory_small_io_page(mem=%p, pg_start=%ld, type=%d)&bslash;n&quot;
comma
id|mem
comma
id|pg_start
comma
id|type
)paren
suffix:semicolon
id|pg_start
op_assign
id|I460_IOPAGES_PER_KPAGE
op_star
id|pg_start
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|pg_start
suffix:semicolon
id|i
OL
(paren
id|pg_start
op_plus
id|I460_IOPAGES_PER_KPAGE
op_star
id|mem-&gt;page_count
)paren
suffix:semicolon
id|i
op_increment
)paren
id|WR_GATT
c_func
(paren
id|i
comma
l_int|0
)paren
suffix:semicolon
id|WR_FLUSH_GATT
c_func
(paren
id|i
op_minus
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if I460_LARGE_IO_PAGES
multiline_comment|/*&n; * These functions are called when the I/O (GART) page size exceeds PAGE_SIZE.&n; *&n; * This situation is interesting since AGP memory allocations that are smaller than a&n; * single GART page are possible.  The i460.lp_desc array tracks partial allocation of the&n; * large GART pages to work around this issue.&n; *&n; * i460.lp_desc[pg_num].refcount tracks the number of kernel pages in use within GART page&n; * pg_num.  i460.lp_desc[pg_num].paddr is the physical address of the large page and&n; * i460.lp_desc[pg_num].alloced_map is a bitmap of kernel pages that are in use (allocated).&n; */
DECL|function|i460_alloc_large_page
r_static
r_int
id|i460_alloc_large_page
(paren
r_struct
id|lp_desc
op_star
id|lp
)paren
(brace
r_int
r_int
id|order
op_assign
id|I460_IO_PAGE_SHIFT
op_minus
id|PAGE_SHIFT
suffix:semicolon
r_int
id|map_size
suffix:semicolon
r_void
op_star
id|lpage
suffix:semicolon
id|lpage
op_assign
(paren
r_void
op_star
)paren
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
id|order
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lpage
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Couldn&squot;t alloc 4M GART page...&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|map_size
op_assign
(paren
(paren
id|I460_KPAGES_PER_IOPAGE
op_plus
id|BITS_PER_LONG
op_minus
l_int|1
)paren
op_amp
op_minus
id|BITS_PER_LONG
)paren
op_div
l_int|8
suffix:semicolon
id|lp-&gt;alloced_map
op_assign
id|kmalloc
c_func
(paren
id|map_size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lp-&gt;alloced_map
)paren
(brace
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|lpage
comma
id|order
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Out of memory, we&squot;re in trouble...&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|lp-&gt;alloced_map
comma
l_int|0
comma
id|map_size
)paren
suffix:semicolon
id|lp-&gt;paddr
op_assign
id|virt_to_phys
c_func
(paren
id|lpage
)paren
suffix:semicolon
id|lp-&gt;refcount
op_assign
l_int|0
suffix:semicolon
id|atomic_add
c_func
(paren
id|I460_KPAGES_PER_IOPAGE
comma
op_amp
id|agp_bridge-&gt;current_memory_agp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i460_free_large_page
r_static
r_void
id|i460_free_large_page
(paren
r_struct
id|lp_desc
op_star
id|lp
)paren
(brace
id|kfree
c_func
(paren
id|lp-&gt;alloced_map
)paren
suffix:semicolon
id|lp-&gt;alloced_map
op_assign
l_int|NULL
suffix:semicolon
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|phys_to_virt
c_func
(paren
id|lp-&gt;paddr
)paren
comma
id|I460_IO_PAGE_SHIFT
op_minus
id|PAGE_SHIFT
)paren
suffix:semicolon
id|atomic_sub
c_func
(paren
id|I460_KPAGES_PER_IOPAGE
comma
op_amp
id|agp_bridge-&gt;current_memory_agp
)paren
suffix:semicolon
)brace
DECL|function|i460_insert_memory_large_io_page
r_static
r_int
id|i460_insert_memory_large_io_page
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
id|start_offset
comma
id|end_offset
comma
id|idx
comma
id|pg
comma
id|num_entries
suffix:semicolon
r_struct
id|lp_desc
op_star
id|start
comma
op_star
id|end
comma
op_star
id|lp
suffix:semicolon
r_void
op_star
id|temp
suffix:semicolon
id|temp
op_assign
id|agp_bridge-&gt;current_size
suffix:semicolon
id|num_entries
op_assign
id|A_SIZE_8
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|num_entries
suffix:semicolon
multiline_comment|/* Figure out what pg_start means in terms of our large GART pages */
id|start
op_assign
op_amp
id|i460.lp_desc
(braket
id|pg_start
op_div
id|I460_KPAGES_PER_IOPAGE
)braket
suffix:semicolon
id|end
op_assign
op_amp
id|i460.lp_desc
(braket
(paren
id|pg_start
op_plus
id|mem-&gt;page_count
op_minus
l_int|1
)paren
op_div
id|I460_KPAGES_PER_IOPAGE
)braket
suffix:semicolon
id|start_offset
op_assign
id|pg_start
op_mod
id|I460_KPAGES_PER_IOPAGE
suffix:semicolon
id|end_offset
op_assign
(paren
id|pg_start
op_plus
id|mem-&gt;page_count
op_minus
l_int|1
)paren
op_mod
id|I460_KPAGES_PER_IOPAGE
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|i460.lp_desc
op_plus
id|num_entries
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Looks like we&squot;re out of AGP memory&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Check if the requested region of the aperture is free */
r_for
c_loop
(paren
id|lp
op_assign
id|start
suffix:semicolon
id|lp
op_le
id|end
suffix:semicolon
op_increment
id|lp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|lp-&gt;alloced_map
)paren
r_continue
suffix:semicolon
multiline_comment|/* OK, the entire large page is available... */
r_for
c_loop
(paren
id|idx
op_assign
(paren
(paren
id|lp
op_eq
id|start
)paren
ques
c_cond
id|start_offset
suffix:colon
l_int|0
)paren
suffix:semicolon
id|idx
OL
(paren
(paren
id|lp
op_eq
id|end
)paren
ques
c_cond
(paren
id|end_offset
op_plus
l_int|1
)paren
suffix:colon
id|I460_KPAGES_PER_IOPAGE
)paren
suffix:semicolon
id|idx
op_increment
)paren
(brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|idx
comma
id|lp-&gt;alloced_map
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|lp
op_assign
id|start
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|lp
op_le
id|end
suffix:semicolon
op_increment
id|lp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|lp-&gt;alloced_map
)paren
(brace
multiline_comment|/* Allocate new GART pages... */
r_if
c_cond
(paren
id|i460_alloc_large_page
c_func
(paren
id|lp
)paren
OL
l_int|0
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|pg
op_assign
id|lp
op_minus
id|i460.lp_desc
suffix:semicolon
id|WR_GATT
c_func
(paren
id|pg
comma
id|agp_bridge-&gt;driver
op_member_access_from_pointer
id|mask_memory
c_func
(paren
id|lp-&gt;paddr
comma
l_int|0
)paren
)paren
suffix:semicolon
id|WR_FLUSH_GATT
c_func
(paren
id|pg
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|idx
op_assign
(paren
(paren
id|lp
op_eq
id|start
)paren
ques
c_cond
id|start_offset
suffix:colon
l_int|0
)paren
suffix:semicolon
id|idx
OL
(paren
(paren
id|lp
op_eq
id|end
)paren
ques
c_cond
(paren
id|end_offset
op_plus
l_int|1
)paren
suffix:colon
id|I460_KPAGES_PER_IOPAGE
)paren
suffix:semicolon
id|idx
op_increment
comma
id|i
op_increment
)paren
(brace
id|mem-&gt;memory
(braket
id|i
)braket
op_assign
id|lp-&gt;paddr
op_plus
id|idx
op_star
id|PAGE_SIZE
suffix:semicolon
id|__set_bit
c_func
(paren
id|idx
comma
id|lp-&gt;alloced_map
)paren
suffix:semicolon
op_increment
id|lp-&gt;refcount
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i460_remove_memory_large_io_page
r_static
r_int
id|i460_remove_memory_large_io_page
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
id|pg
comma
id|start_offset
comma
id|end_offset
comma
id|idx
comma
id|num_entries
suffix:semicolon
r_struct
id|lp_desc
op_star
id|start
comma
op_star
id|end
comma
op_star
id|lp
suffix:semicolon
r_void
op_star
id|temp
suffix:semicolon
id|temp
op_assign
id|agp_bridge-&gt;driver-&gt;current_size
suffix:semicolon
id|num_entries
op_assign
id|A_SIZE_8
c_func
(paren
id|temp
)paren
op_member_access_from_pointer
id|num_entries
suffix:semicolon
multiline_comment|/* Figure out what pg_start means in terms of our large GART pages */
id|start
op_assign
op_amp
id|i460.lp_desc
(braket
id|pg_start
op_div
id|I460_KPAGES_PER_IOPAGE
)braket
suffix:semicolon
id|end
op_assign
op_amp
id|i460.lp_desc
(braket
(paren
id|pg_start
op_plus
id|mem-&gt;page_count
op_minus
l_int|1
)paren
op_div
id|I460_KPAGES_PER_IOPAGE
)braket
suffix:semicolon
id|start_offset
op_assign
id|pg_start
op_mod
id|I460_KPAGES_PER_IOPAGE
suffix:semicolon
id|end_offset
op_assign
(paren
id|pg_start
op_plus
id|mem-&gt;page_count
op_minus
l_int|1
)paren
op_mod
id|I460_KPAGES_PER_IOPAGE
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|lp
op_assign
id|start
suffix:semicolon
id|lp
op_le
id|end
suffix:semicolon
op_increment
id|lp
)paren
(brace
r_for
c_loop
(paren
id|idx
op_assign
(paren
(paren
id|lp
op_eq
id|start
)paren
ques
c_cond
id|start_offset
suffix:colon
l_int|0
)paren
suffix:semicolon
id|idx
OL
(paren
(paren
id|lp
op_eq
id|end
)paren
ques
c_cond
(paren
id|end_offset
op_plus
l_int|1
)paren
suffix:colon
id|I460_KPAGES_PER_IOPAGE
)paren
suffix:semicolon
id|idx
op_increment
comma
id|i
op_increment
)paren
(brace
id|mem-&gt;memory
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|__clear_bit
c_func
(paren
id|idx
comma
id|lp-&gt;alloced_map
)paren
suffix:semicolon
op_decrement
id|lp-&gt;refcount
suffix:semicolon
)brace
multiline_comment|/* Free GART pages if they are unused */
r_if
c_cond
(paren
id|lp-&gt;refcount
op_eq
l_int|0
)paren
(brace
id|pg
op_assign
id|lp
op_minus
id|i460.lp_desc
suffix:semicolon
id|WR_GATT
c_func
(paren
id|pg
comma
l_int|0
)paren
suffix:semicolon
id|WR_FLUSH_GATT
c_func
(paren
id|pg
)paren
suffix:semicolon
id|i460_free_large_page
c_func
(paren
id|lp
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Wrapper routines to call the approriate {small_io_page,large_io_page} function */
DECL|function|i460_insert_memory
r_static
r_int
id|i460_insert_memory
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
r_if
c_cond
(paren
id|I460_IO_PAGE_SHIFT
op_le
id|PAGE_SHIFT
)paren
r_return
id|i460_insert_memory_small_io_page
c_func
(paren
id|mem
comma
id|pg_start
comma
id|type
)paren
suffix:semicolon
r_else
r_return
id|i460_insert_memory_large_io_page
c_func
(paren
id|mem
comma
id|pg_start
comma
id|type
)paren
suffix:semicolon
)brace
DECL|function|i460_remove_memory
r_static
r_int
id|i460_remove_memory
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
r_if
c_cond
(paren
id|I460_IO_PAGE_SHIFT
op_le
id|PAGE_SHIFT
)paren
r_return
id|i460_remove_memory_small_io_page
c_func
(paren
id|mem
comma
id|pg_start
comma
id|type
)paren
suffix:semicolon
r_else
r_return
id|i460_remove_memory_large_io_page
c_func
(paren
id|mem
comma
id|pg_start
comma
id|type
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * If the I/O (GART) page size is bigger than the kernel page size, we don&squot;t want to&n; * allocate memory until we know where it is to be bound in the aperture (a&n; * multi-kernel-page alloc might fit inside of an already allocated GART page).&n; *&n; * Let&squot;s just hope nobody counts on the allocated AGP memory being there before bind time&n; * (I don&squot;t think current drivers do)...&n; */
DECL|function|i460_alloc_page
r_static
r_void
op_star
id|i460_alloc_page
(paren
r_void
)paren
(brace
r_void
op_star
id|page
suffix:semicolon
r_if
c_cond
(paren
id|I460_IO_PAGE_SHIFT
op_le
id|PAGE_SHIFT
)paren
id|page
op_assign
id|agp_generic_alloc_page
c_func
(paren
)paren
suffix:semicolon
r_else
multiline_comment|/* Returning NULL would cause problems */
multiline_comment|/* AK: really dubious code. */
id|page
op_assign
(paren
r_void
op_star
)paren
op_complement
l_int|0UL
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
DECL|function|i460_destroy_page
r_static
r_void
id|i460_destroy_page
(paren
r_void
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
id|I460_IO_PAGE_SHIFT
op_le
id|PAGE_SHIFT
)paren
id|agp_generic_destroy_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
macro_line|#endif /* I460_LARGE_IO_PAGES */
DECL|function|i460_mask_memory
r_static
r_int
r_int
id|i460_mask_memory
(paren
r_int
r_int
id|addr
comma
r_int
id|type
)paren
(brace
multiline_comment|/* Make sure the returned address is a valid GATT entry */
r_return
(paren
id|agp_bridge-&gt;driver-&gt;masks
(braket
l_int|0
)braket
dot
id|mask
op_or
(paren
(paren
(paren
id|addr
op_amp
op_complement
(paren
(paren
l_int|1
op_lshift
id|I460_IO_PAGE_SHIFT
)paren
op_minus
l_int|1
)paren
)paren
op_amp
l_int|0xffffff000
)paren
op_rshift
l_int|12
)paren
)paren
suffix:semicolon
)brace
DECL|variable|intel_i460_driver
r_struct
id|agp_bridge_driver
id|intel_i460_driver
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|masks
op_assign
id|i460_masks
comma
dot
id|aperture_sizes
op_assign
id|i460_sizes
comma
dot
id|size_type
op_assign
id|U8_APER_SIZE
comma
dot
id|num_aperture_sizes
op_assign
l_int|3
comma
dot
id|configure
op_assign
id|i460_configure
comma
dot
id|fetch_size
op_assign
id|i460_fetch_size
comma
dot
id|cleanup
op_assign
id|i460_cleanup
comma
dot
id|tlb_flush
op_assign
id|i460_tlb_flush
comma
dot
id|mask_memory
op_assign
id|i460_mask_memory
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
id|i460_create_gatt_table
comma
dot
id|free_gatt_table
op_assign
id|i460_free_gatt_table
comma
macro_line|#if I460_LARGE_IO_PAGES
dot
id|insert_memory
op_assign
id|i460_insert_memory
comma
dot
id|remove_memory
op_assign
id|i460_remove_memory
comma
dot
id|agp_alloc_page
op_assign
id|i460_alloc_page
comma
dot
id|agp_destroy_page
op_assign
id|i460_destroy_page
comma
macro_line|#else
dot
id|insert_memory
op_assign
id|i460_insert_memory_small_io_page
comma
dot
id|remove_memory
op_assign
id|i460_remove_memory_small_io_page
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
macro_line|#endif
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
id|suspend
op_assign
id|agp_generic_suspend
comma
dot
id|resume
op_assign
id|agp_generic_resume
comma
dot
id|cant_use_aperture
op_assign
l_int|1
comma
)brace
suffix:semicolon
DECL|function|agp_intel_i460_probe
r_static
r_int
id|__init
id|agp_intel_i460_probe
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
id|cap_ptr
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
id|bridge-&gt;driver
op_assign
op_amp
id|intel_i460_driver
suffix:semicolon
id|bridge-&gt;dev
op_assign
id|pdev
suffix:semicolon
id|bridge-&gt;capndx
op_assign
id|cap_ptr
suffix:semicolon
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
DECL|function|agp_intel_i460_remove
r_static
r_void
id|__devexit
id|agp_intel_i460_remove
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
DECL|variable|__initdata
r_static
r_struct
id|pci_device_id
id|agp_intel_i460_pci_table
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
id|PCI_VENDOR_ID_INTEL
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_INTEL_84460GX
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
id|agp_intel_i460_pci_table
)paren
suffix:semicolon
DECL|variable|agp_intel_i460_pci_driver
r_static
r_struct
id|__initdata
id|pci_driver
id|agp_intel_i460_pci_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;agpgart-intel-i460&quot;
comma
dot
id|id_table
op_assign
id|agp_intel_i460_pci_table
comma
dot
id|probe
op_assign
id|agp_intel_i460_probe
comma
dot
id|remove
op_assign
id|agp_intel_i460_remove
comma
)brace
suffix:semicolon
DECL|function|agp_intel_i460_init
r_static
r_int
id|__init
id|agp_intel_i460_init
c_func
(paren
r_void
)paren
(brace
r_return
id|pci_module_init
c_func
(paren
op_amp
id|agp_intel_i460_pci_driver
)paren
suffix:semicolon
)brace
DECL|function|agp_intel_i460_cleanup
r_static
r_void
id|__exit
id|agp_intel_i460_cleanup
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|agp_intel_i460_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|agp_intel_i460_init
id|module_init
c_func
(paren
id|agp_intel_i460_init
)paren
suffix:semicolon
DECL|variable|agp_intel_i460_cleanup
id|module_exit
c_func
(paren
id|agp_intel_i460_cleanup
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Chris Ahna &lt;Christopher.J.Ahna@intel.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL and additional rights&quot;
)paren
suffix:semicolon
eof
