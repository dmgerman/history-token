multiline_comment|/*&n; * amd76xrom.c&n; *&n; * Normal mappings of chips in physical memory&n; * $Id: amd76xrom.c,v 1.12 2004/07/14 14:44:31 thayne Exp $&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/pci_ids.h&gt;
DECL|macro|xstr
mdefine_line|#define xstr(s) str(s)
DECL|macro|str
mdefine_line|#define str(s) #s
DECL|macro|MOD_NAME
mdefine_line|#define MOD_NAME xstr(KBUILD_BASENAME)
DECL|macro|MTD_DEV_NAME_LENGTH
mdefine_line|#define MTD_DEV_NAME_LENGTH 16
DECL|struct|amd76xrom_map_info
r_struct
id|amd76xrom_map_info
(brace
DECL|member|map
r_struct
id|map_info
id|map
suffix:semicolon
DECL|member|mtd
r_struct
id|mtd_info
op_star
id|mtd
suffix:semicolon
DECL|member|window_addr
r_int
r_int
id|window_addr
suffix:semicolon
DECL|member|window_start
DECL|member|window_size
id|u32
id|window_start
comma
id|window_size
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|window_rsrc
r_struct
id|resource
id|window_rsrc
suffix:semicolon
DECL|member|rom_rsrc
r_struct
id|resource
id|rom_rsrc
suffix:semicolon
DECL|member|mtd_name
r_char
id|mtd_name
(braket
id|MTD_DEV_NAME_LENGTH
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|amd76xrom_map
r_static
r_struct
id|amd76xrom_map_info
id|amd76xrom_map
op_assign
(brace
dot
id|map
op_assign
(brace
dot
id|name
op_assign
id|MOD_NAME
comma
dot
id|size
op_assign
l_int|0
comma
dot
id|bankwidth
op_assign
l_int|1
comma
)brace
multiline_comment|/* remaining fields of structure are initialized to 0 */
)brace
suffix:semicolon
DECL|function|amd76xrom_cleanup
r_static
r_void
id|amd76xrom_cleanup
c_func
(paren
r_struct
id|amd76xrom_map_info
op_star
id|info
)paren
(brace
id|u8
id|byte
suffix:semicolon
multiline_comment|/* Disable writes through the rom window */
id|pci_read_config_byte
c_func
(paren
id|info-&gt;pdev
comma
l_int|0x40
comma
op_amp
id|byte
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|info-&gt;pdev
comma
l_int|0x40
comma
id|byte
op_amp
op_complement
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;mtd
)paren
(brace
id|del_mtd_device
c_func
(paren
id|info-&gt;mtd
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|info-&gt;mtd
)paren
suffix:semicolon
id|info-&gt;mtd
op_assign
l_int|NULL
suffix:semicolon
id|info-&gt;map.virt
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;rom_rsrc.parent
)paren
id|release_resource
c_func
(paren
op_amp
id|info-&gt;rom_rsrc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;window_rsrc.parent
)paren
id|release_resource
c_func
(paren
op_amp
id|info-&gt;window_rsrc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;window_addr
)paren
(brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|info-&gt;window_addr
)paren
)paren
suffix:semicolon
id|info-&gt;window_addr
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|amd76xrom_init_one
r_static
r_int
id|__devinit
id|amd76xrom_init_one
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
id|rom_window
(brace
id|u32
id|start
suffix:semicolon
id|u32
id|size
suffix:semicolon
id|u8
id|segen_bits
suffix:semicolon
)brace
suffix:semicolon
r_static
r_struct
id|rom_window
id|rom_window
(braket
)braket
op_assign
(brace
multiline_comment|/*&n;&t;&t; * Need the 5MiB window for chips that have block lock/unlock&n;&t;&t; * registers located below 4MiB window.&n;&t;&t; */
(brace
l_int|0xffb00000
comma
l_int|5
op_star
l_int|1024
op_star
l_int|1024
comma
(paren
l_int|1
op_lshift
l_int|7
)paren
op_or
(paren
l_int|1
op_lshift
l_int|6
)paren
comma
)brace
comma
(brace
l_int|0xffc00000
comma
l_int|4
op_star
l_int|1024
op_star
l_int|1024
comma
(paren
l_int|1
op_lshift
l_int|7
)paren
comma
)brace
comma
(brace
l_int|0xffff0000
comma
l_int|64
op_star
l_int|1024
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
r_static
r_const
id|u32
id|rom_probe_sizes
(braket
)braket
op_assign
(brace
l_int|5
op_star
l_int|1024
op_star
l_int|1024
comma
l_int|4
op_star
l_int|1024
op_star
l_int|1024
comma
l_int|2
op_star
l_int|1024
op_star
l_int|1024
comma
l_int|1024
op_star
l_int|1024
comma
l_int|512
op_star
l_int|1024
comma
l_int|256
op_star
l_int|1024
comma
l_int|128
op_star
l_int|1024
comma
l_int|64
op_star
l_int|1024
comma
l_int|0
)brace
suffix:semicolon
r_static
r_char
op_star
id|rom_probe_types
(braket
)braket
op_assign
(brace
l_string|&quot;cfi_probe&quot;
comma
l_string|&quot;jedec_probe&quot;
comma
l_int|NULL
)brace
suffix:semicolon
id|u8
id|byte
suffix:semicolon
r_struct
id|amd76xrom_map_info
op_star
id|info
op_assign
op_amp
id|amd76xrom_map
suffix:semicolon
r_struct
id|rom_window
op_star
id|window
suffix:semicolon
r_int
id|i
suffix:semicolon
id|u32
id|rom_size
suffix:semicolon
id|info-&gt;pdev
op_assign
id|pdev
suffix:semicolon
id|window
op_assign
op_amp
id|rom_window
(braket
l_int|0
)braket
suffix:semicolon
r_while
c_loop
(paren
id|window-&gt;size
)paren
(brace
multiline_comment|/*&n;&t;&t; * Try to reserve the window mem region.  If this fails then&n;&t;&t; * it is likely due to a fragment of the window being&n;&t;&t; * &quot;reseved&quot; by the BIOS.  In the case that the&n;&t;&t; * request_mem_region() fails then once the rom size is&n;&t;&t; * discovered we will try to reserve the unreserved fragment.&n;&t;&t; */
id|info-&gt;window_rsrc.name
op_assign
id|MOD_NAME
suffix:semicolon
id|info-&gt;window_rsrc.start
op_assign
id|window-&gt;start
suffix:semicolon
id|info-&gt;window_rsrc.end
op_assign
id|window-&gt;start
op_plus
id|window-&gt;size
op_minus
l_int|1
suffix:semicolon
id|info-&gt;window_rsrc.flags
op_assign
id|IORESOURCE_MEM
op_or
id|IORESOURCE_BUSY
suffix:semicolon
r_if
c_cond
(paren
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|info-&gt;window_rsrc
)paren
)paren
(brace
id|info-&gt;window_rsrc.parent
op_assign
l_int|NULL
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
id|MOD_NAME
l_string|&quot; %s(): Unable to register resource&quot;
l_string|&quot; 0x%.08lx-0x%.08lx - kernel bug?&bslash;n&quot;
comma
id|__func__
comma
id|info-&gt;window_rsrc.start
comma
id|info-&gt;window_rsrc.end
)paren
suffix:semicolon
)brace
multiline_comment|/* Enable the selected rom window */
id|pci_read_config_byte
c_func
(paren
id|pdev
comma
l_int|0x43
comma
op_amp
id|byte
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|pdev
comma
l_int|0x43
comma
id|byte
op_or
id|window-&gt;segen_bits
)paren
suffix:semicolon
multiline_comment|/* Enable writes through the rom window */
id|pci_read_config_byte
c_func
(paren
id|pdev
comma
l_int|0x40
comma
op_amp
id|byte
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|pdev
comma
l_int|0x40
comma
id|byte
op_or
l_int|1
)paren
suffix:semicolon
multiline_comment|/* FIXME handle registers 0x80 - 0x8C the bios region locks */
id|printk
c_func
(paren
id|KERN_NOTICE
id|MOD_NAME
l_string|&quot; window : %x at %x&bslash;n&quot;
comma
id|window-&gt;size
comma
id|window-&gt;start
)paren
suffix:semicolon
multiline_comment|/* For write accesses caches are useless */
id|info-&gt;window_addr
op_assign
(paren
r_int
r_int
)paren
id|ioremap_nocache
c_func
(paren
id|window-&gt;start
comma
id|window-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;window_addr
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Failed to ioremap&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|info-&gt;mtd
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|rom_size
op_assign
id|rom_probe_sizes
(braket
id|i
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
op_star
op_star
id|chip_type
suffix:semicolon
r_if
c_cond
(paren
id|rom_size
OG
id|window-&gt;size
)paren
(brace
r_continue
suffix:semicolon
)brace
id|info-&gt;map.phys
op_assign
id|window-&gt;start
op_plus
id|window-&gt;size
op_minus
id|rom_size
suffix:semicolon
id|info-&gt;map.virt
op_assign
id|info-&gt;window_addr
op_plus
id|window-&gt;size
op_minus
id|rom_size
suffix:semicolon
id|info-&gt;map.size
op_assign
id|rom_size
suffix:semicolon
id|simple_map_init
c_func
(paren
op_amp
id|info-&gt;map
)paren
suffix:semicolon
id|chip_type
op_assign
id|rom_probe_types
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
op_logical_neg
id|info-&gt;mtd
op_logical_and
op_star
id|chip_type
suffix:semicolon
id|chip_type
op_increment
)paren
(brace
id|info-&gt;mtd
op_assign
id|do_map_probe
c_func
(paren
op_star
id|chip_type
comma
op_amp
id|amd76xrom_map.map
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|info-&gt;mtd
)paren
r_goto
id|found_mtd
suffix:semicolon
)brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|info-&gt;window_addr
)paren
)paren
suffix:semicolon
id|info-&gt;window_addr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Disable writes through the rom window */
id|pci_read_config_byte
c_func
(paren
id|pdev
comma
l_int|0x40
comma
op_amp
id|byte
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|pdev
comma
l_int|0x40
comma
id|byte
op_amp
op_complement
l_int|1
)paren
suffix:semicolon
id|window
op_increment
suffix:semicolon
)brace
r_goto
id|failed
suffix:semicolon
id|found_mtd
suffix:colon
id|printk
c_func
(paren
id|KERN_NOTICE
id|MOD_NAME
l_string|&quot; chip at offset: 0x%x&bslash;n&quot;
comma
id|window-&gt;size
op_minus
id|rom_size
)paren
suffix:semicolon
id|info-&gt;mtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;window_rsrc.parent
)paren
(brace
multiline_comment|/* failed to reserve entire window - try fragments */
id|info-&gt;window_rsrc.name
op_assign
id|MOD_NAME
suffix:semicolon
id|info-&gt;window_rsrc.start
op_assign
id|window-&gt;start
suffix:semicolon
id|info-&gt;window_rsrc.end
op_assign
id|window-&gt;start
op_plus
id|window-&gt;size
op_minus
id|rom_size
op_minus
l_int|1
suffix:semicolon
id|info-&gt;window_rsrc.flags
op_assign
id|IORESOURCE_MEM
op_or
id|IORESOURCE_BUSY
suffix:semicolon
r_if
c_cond
(paren
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|info-&gt;window_rsrc
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|MOD_NAME
l_string|&quot;: cannot reserve window resource fragment&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/*&n;&t;&t;&t; * The BIOS e820 usually reserves this so it isn&squot;t&n;&t;&t;&t; * usually an error.&n;&t;&t;&t; */
r_goto
id|failed
suffix:semicolon
macro_line|#endif
)brace
)brace
id|add_mtd_device
c_func
(paren
id|info-&gt;mtd
)paren
suffix:semicolon
id|info-&gt;window_start
op_assign
id|window-&gt;start
suffix:semicolon
id|info-&gt;window_size
op_assign
id|window-&gt;size
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;window_rsrc.parent
)paren
(brace
multiline_comment|/*&n;&t;&t; * Registering the MTD device in iomem may not be possible&n;&t;&t; * if there is a BIOS &quot;reserved&quot; and BUSY range.  If this&n;&t;&t; * fails then continue anyway.&n;&t;&t; */
id|snprintf
c_func
(paren
id|info-&gt;mtd_name
comma
id|MTD_DEV_NAME_LENGTH
comma
l_string|&quot;mtd%d&quot;
comma
id|info-&gt;mtd-&gt;index
)paren
suffix:semicolon
id|info-&gt;rom_rsrc.name
op_assign
id|info-&gt;mtd_name
suffix:semicolon
id|info-&gt;rom_rsrc.start
op_assign
id|window-&gt;start
op_plus
id|window-&gt;size
op_minus
id|rom_size
suffix:semicolon
id|info-&gt;rom_rsrc.end
op_assign
id|window-&gt;start
op_plus
id|window-&gt;size
op_minus
l_int|1
suffix:semicolon
id|info-&gt;rom_rsrc.flags
op_assign
id|IORESOURCE_MEM
op_or
id|IORESOURCE_BUSY
suffix:semicolon
r_if
c_cond
(paren
id|request_resource
c_func
(paren
op_amp
id|info-&gt;window_rsrc
comma
op_amp
id|info-&gt;rom_rsrc
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|MOD_NAME
l_string|&quot;: cannot reserve MTD resource&bslash;n&quot;
)paren
suffix:semicolon
id|info-&gt;rom_rsrc.parent
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
id|failed
suffix:colon
id|amd76xrom_cleanup
c_func
(paren
id|info
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|amd76xrom_remove_one
r_static
r_void
id|__devexit
id|amd76xrom_remove_one
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
r_struct
id|amd76xrom_map_info
op_star
id|info
op_assign
op_amp
id|amd76xrom_map
suffix:semicolon
id|amd76xrom_cleanup
c_func
(paren
id|info
)paren
suffix:semicolon
)brace
DECL|variable|amd76xrom_pci_tbl
r_static
r_struct
id|pci_device_id
id|amd76xrom_pci_tbl
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_AMD
comma
id|PCI_DEVICE_ID_AMD_VIPER_7410
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
(brace
id|PCI_VENDOR_ID_AMD
comma
id|PCI_DEVICE_ID_AMD_VIPER_7440
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
(brace
id|PCI_VENDOR_ID_AMD
comma
l_int|0x7468
)brace
comma
multiline_comment|/* amd8111 support */
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|amd76xrom_pci_tbl
)paren
suffix:semicolon
macro_line|#if 0
r_static
r_struct
id|pci_driver
id|amd76xrom_driver
op_assign
(brace
dot
id|name
op_assign
id|MOD_NAME
comma
dot
id|id_table
op_assign
id|amd76xrom_pci_tbl
comma
dot
id|probe
op_assign
id|amd76xrom_init_one
comma
dot
id|remove
op_assign
id|amd76xrom_remove_one
comma
)brace
suffix:semicolon
macro_line|#endif
DECL|function|init_amd76xrom
r_int
id|__init
id|init_amd76xrom
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
r_struct
id|pci_device_id
op_star
id|id
suffix:semicolon
id|pdev
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|id
op_assign
id|amd76xrom_pci_tbl
suffix:semicolon
id|id-&gt;vendor
suffix:semicolon
id|id
op_increment
)paren
(brace
id|pdev
op_assign
id|pci_find_device
c_func
(paren
id|id-&gt;vendor
comma
id|id-&gt;device
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pdev
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|pdev
)paren
(brace
id|amd76xrom_map.pdev
op_assign
id|pdev
suffix:semicolon
r_return
id|amd76xrom_init_one
c_func
(paren
id|pdev
comma
op_amp
id|amd76xrom_pci_tbl
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
r_return
op_minus
id|ENXIO
suffix:semicolon
macro_line|#if 0
r_return
id|pci_module_init
c_func
(paren
op_amp
id|amd76xrom_driver
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|cleanup_amd76xrom
r_static
r_void
id|__exit
id|cleanup_amd76xrom
c_func
(paren
r_void
)paren
(brace
id|amd76xrom_remove_one
c_func
(paren
id|amd76xrom_map.pdev
)paren
suffix:semicolon
)brace
DECL|variable|init_amd76xrom
id|module_init
c_func
(paren
id|init_amd76xrom
)paren
suffix:semicolon
DECL|variable|cleanup_amd76xrom
id|module_exit
c_func
(paren
id|cleanup_amd76xrom
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Eric Biederman &lt;ebiederman@lnxi.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MTD map driver for BIOS chips on the AMD76X southbridge&quot;
)paren
suffix:semicolon
eof
