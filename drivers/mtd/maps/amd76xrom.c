multiline_comment|/*&n; * amd76xrom.c&n; *&n; * Normal mappings of chips in physical memory&n; * $Id: amd76xrom.c,v 1.19 2004/11/28 09:40:39 dwmw2 Exp $&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/cfi.h&gt;
macro_line|#include &lt;linux/mtd/flashchip.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/pci_ids.h&gt;
macro_line|#include &lt;linux/list.h&gt;
DECL|macro|xstr
mdefine_line|#define xstr(s) str(s)
DECL|macro|str
mdefine_line|#define str(s) #s
DECL|macro|MOD_NAME
mdefine_line|#define MOD_NAME xstr(KBUILD_BASENAME)
DECL|macro|ADDRESS_NAME_LEN
mdefine_line|#define ADDRESS_NAME_LEN 18
DECL|macro|ROM_PROBE_STEP_SIZE
mdefine_line|#define ROM_PROBE_STEP_SIZE (64*1024) /* 64KiB */
DECL|struct|amd76xrom_window
r_struct
id|amd76xrom_window
(brace
DECL|member|virt
r_void
id|__iomem
op_star
id|virt
suffix:semicolon
DECL|member|phys
r_int
r_int
id|phys
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|maps
r_struct
id|list_head
id|maps
suffix:semicolon
DECL|member|rsrc
r_struct
id|resource
id|rsrc
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|amd76xrom_map_info
r_struct
id|amd76xrom_map_info
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
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
DECL|member|rsrc
r_struct
id|resource
id|rsrc
suffix:semicolon
DECL|member|map_name
r_char
id|map_name
(braket
r_sizeof
(paren
id|MOD_NAME
)paren
op_plus
l_int|2
op_plus
id|ADDRESS_NAME_LEN
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|amd76xrom_window
r_static
r_struct
id|amd76xrom_window
id|amd76xrom_window
op_assign
(brace
dot
id|maps
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|amd76xrom_window.maps
)paren
comma
)brace
suffix:semicolon
DECL|function|amd76xrom_cleanup
r_static
r_void
id|amd76xrom_cleanup
c_func
(paren
r_struct
id|amd76xrom_window
op_star
id|window
)paren
(brace
r_struct
id|amd76xrom_map_info
op_star
id|map
comma
op_star
id|scratch
suffix:semicolon
id|u8
id|byte
suffix:semicolon
r_if
c_cond
(paren
id|window-&gt;pdev
)paren
(brace
multiline_comment|/* Disable writes through the rom window */
id|pci_read_config_byte
c_func
(paren
id|window-&gt;pdev
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
id|window-&gt;pdev
comma
l_int|0x40
comma
id|byte
op_amp
op_complement
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Free all of the mtd devices */
id|list_for_each_entry_safe
c_func
(paren
id|map
comma
id|scratch
comma
op_amp
id|window-&gt;maps
comma
id|list
)paren
(brace
r_if
c_cond
(paren
id|map-&gt;rsrc.parent
)paren
(brace
id|release_resource
c_func
(paren
op_amp
id|map-&gt;rsrc
)paren
suffix:semicolon
)brace
id|del_mtd_device
c_func
(paren
id|map-&gt;mtd
)paren
suffix:semicolon
id|map_destroy
c_func
(paren
id|map-&gt;mtd
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|map-&gt;list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|map
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|window-&gt;rsrc.parent
)paren
id|release_resource
c_func
(paren
op_amp
id|window-&gt;rsrc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|window-&gt;virt
)paren
(brace
id|iounmap
c_func
(paren
id|window-&gt;virt
)paren
suffix:semicolon
id|window-&gt;virt
op_assign
l_int|NULL
suffix:semicolon
id|window-&gt;phys
op_assign
l_int|0
suffix:semicolon
id|window-&gt;size
op_assign
l_int|0
suffix:semicolon
id|window-&gt;pdev
op_assign
l_int|NULL
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
id|amd76xrom_window
op_star
id|window
op_assign
op_amp
id|amd76xrom_window
suffix:semicolon
r_struct
id|amd76xrom_map_info
op_star
id|map
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|map_top
suffix:semicolon
multiline_comment|/* Remember the pci dev I find the window in */
id|window-&gt;pdev
op_assign
id|pdev
suffix:semicolon
multiline_comment|/* Assume the rom window is properly setup, and find it&squot;s size */
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
r_if
c_cond
(paren
(paren
id|byte
op_amp
(paren
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
)paren
)paren
op_eq
(paren
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
)paren
)paren
(brace
id|window-&gt;phys
op_assign
l_int|0xffb00000
suffix:semicolon
multiline_comment|/* 5MiB */
)brace
r_else
r_if
c_cond
(paren
(paren
id|byte
op_amp
(paren
l_int|1
op_lshift
l_int|7
)paren
)paren
op_eq
(paren
l_int|1
op_lshift
l_int|7
)paren
)paren
(brace
id|window-&gt;phys
op_assign
l_int|0xffc00000
suffix:semicolon
multiline_comment|/* 4MiB */
)brace
r_else
(brace
id|window-&gt;phys
op_assign
l_int|0xffff0000
suffix:semicolon
multiline_comment|/* 64KiB */
)brace
id|window-&gt;size
op_assign
l_int|0xffffffffUL
op_minus
id|window-&gt;phys
op_plus
l_int|1UL
suffix:semicolon
multiline_comment|/*&n;&t; * Try to reserve the window mem region.  If this fails then&n;&t; * it is likely due to a fragment of the window being&n;&t; * &quot;reseved&quot; by the BIOS.  In the case that the&n;&t; * request_mem_region() fails then once the rom size is&n;&t; * discovered we will try to reserve the unreserved fragment.&n;&t; */
id|window-&gt;rsrc.name
op_assign
id|MOD_NAME
suffix:semicolon
id|window-&gt;rsrc.start
op_assign
id|window-&gt;phys
suffix:semicolon
id|window-&gt;rsrc.end
op_assign
id|window-&gt;phys
op_plus
id|window-&gt;size
op_minus
l_int|1
suffix:semicolon
id|window-&gt;rsrc.flags
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
id|window-&gt;rsrc
)paren
)paren
(brace
id|window-&gt;rsrc.parent
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
id|window-&gt;rsrc.start
comma
id|window-&gt;rsrc.end
)paren
suffix:semicolon
)brace
macro_line|#if 0
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
id|rwindow-&gt;segen_bits
)paren
suffix:semicolon
macro_line|#endif
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
multiline_comment|/* For write accesses caches are useless */
id|window-&gt;virt
op_assign
id|ioremap_nocache
c_func
(paren
id|window-&gt;phys
comma
id|window-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|window-&gt;virt
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|MOD_NAME
l_string|&quot;: ioremap(%08lx, %08lx) failed&bslash;n&quot;
comma
id|window-&gt;phys
comma
id|window-&gt;size
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Get the first address to look for an rom chip at */
id|map_top
op_assign
id|window-&gt;phys
suffix:semicolon
macro_line|#if 1
multiline_comment|/* The probe sequence run over the firmware hub lock&n;&t; * registers sets them to 0x7 (no access).&n;&t; * Probe at most the last 4M of the address space.&n;&t; */
r_if
c_cond
(paren
id|map_top
OL
l_int|0xffc00000
)paren
(brace
id|map_top
op_assign
l_int|0xffc00000
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Loop  through and look for rom chips */
r_while
c_loop
(paren
(paren
id|map_top
op_minus
l_int|1
)paren
OL
l_int|0xffffffffUL
)paren
(brace
r_struct
id|cfi_private
op_star
id|cfi
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|map
)paren
(brace
id|map
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|map
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|map
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|MOD_NAME
l_string|&quot;: kmalloc failed&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|memset
c_func
(paren
id|map
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|map
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|map-&gt;list
)paren
suffix:semicolon
id|map-&gt;map.name
op_assign
id|map-&gt;map_name
suffix:semicolon
id|map-&gt;map.phys
op_assign
id|map_top
suffix:semicolon
id|offset
op_assign
id|map_top
op_minus
id|window-&gt;phys
suffix:semicolon
id|map-&gt;map.virt
op_assign
(paren
r_void
id|__iomem
op_star
)paren
(paren
(paren
(paren
r_int
r_int
)paren
(paren
id|window-&gt;virt
)paren
)paren
op_plus
id|offset
)paren
suffix:semicolon
id|map-&gt;map.size
op_assign
l_int|0xffffffffUL
op_minus
id|map_top
op_plus
l_int|1UL
suffix:semicolon
multiline_comment|/* Set the name of the map to the address I am trying */
id|sprintf
c_func
(paren
id|map-&gt;map_name
comma
l_string|&quot;%s @%08lx&quot;
comma
id|MOD_NAME
comma
id|map-&gt;map.phys
)paren
suffix:semicolon
multiline_comment|/* There is no generic VPP support */
r_for
c_loop
(paren
id|map-&gt;map.bankwidth
op_assign
l_int|32
suffix:semicolon
id|map-&gt;map.bankwidth
suffix:semicolon
id|map-&gt;map.bankwidth
op_rshift_assign
l_int|1
)paren
(brace
r_char
op_star
op_star
id|probe_type
suffix:semicolon
multiline_comment|/* Skip bankwidths that are not supported */
r_if
c_cond
(paren
op_logical_neg
id|map_bankwidth_supported
c_func
(paren
id|map-&gt;map.bankwidth
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* Setup the map methods */
id|simple_map_init
c_func
(paren
op_amp
id|map-&gt;map
)paren
suffix:semicolon
multiline_comment|/* Try all of the probe methods */
id|probe_type
op_assign
id|rom_probe_types
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
op_star
id|probe_type
suffix:semicolon
id|probe_type
op_increment
)paren
(brace
id|map-&gt;mtd
op_assign
id|do_map_probe
c_func
(paren
op_star
id|probe_type
comma
op_amp
id|map-&gt;map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map-&gt;mtd
)paren
r_goto
id|found
suffix:semicolon
)brace
)brace
id|map_top
op_add_assign
id|ROM_PROBE_STEP_SIZE
suffix:semicolon
r_continue
suffix:semicolon
id|found
suffix:colon
multiline_comment|/* Trim the size if we are larger than the map */
r_if
c_cond
(paren
id|map-&gt;mtd-&gt;size
OG
id|map-&gt;map.size
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|MOD_NAME
l_string|&quot; rom(%u) larger than window(%lu). fixing...&bslash;n&quot;
comma
id|map-&gt;mtd-&gt;size
comma
id|map-&gt;map.size
)paren
suffix:semicolon
id|map-&gt;mtd-&gt;size
op_assign
id|map-&gt;map.size
suffix:semicolon
)brace
r_if
c_cond
(paren
id|window-&gt;rsrc.parent
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Registering the MTD device in iomem may not be possible&n;&t;&t;&t; * if there is a BIOS &quot;reserved&quot; and BUSY range.  If this&n;&t;&t;&t; * fails then continue anyway.&n;&t;&t;&t; */
id|map-&gt;rsrc.name
op_assign
id|map-&gt;map_name
suffix:semicolon
id|map-&gt;rsrc.start
op_assign
id|map-&gt;map.phys
suffix:semicolon
id|map-&gt;rsrc.end
op_assign
id|map-&gt;map.phys
op_plus
id|map-&gt;mtd-&gt;size
op_minus
l_int|1
suffix:semicolon
id|map-&gt;rsrc.flags
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
id|window-&gt;rsrc
comma
op_amp
id|map-&gt;rsrc
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
id|map-&gt;rsrc.parent
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
multiline_comment|/* Make the whole region visible in the map */
id|map-&gt;map.virt
op_assign
id|window-&gt;virt
suffix:semicolon
id|map-&gt;map.phys
op_assign
id|window-&gt;phys
suffix:semicolon
id|cfi
op_assign
id|map-&gt;map.fldrv_priv
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
id|cfi-&gt;numchips
suffix:semicolon
id|i
op_increment
)paren
(brace
id|cfi-&gt;chips
(braket
id|i
)braket
dot
id|start
op_add_assign
id|offset
suffix:semicolon
)brace
multiline_comment|/* Now that the mtd devices is complete claim and export it */
id|map-&gt;mtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
r_if
c_cond
(paren
id|add_mtd_device
c_func
(paren
id|map-&gt;mtd
)paren
)paren
(brace
id|map_destroy
c_func
(paren
id|map-&gt;mtd
)paren
suffix:semicolon
id|map-&gt;mtd
op_assign
l_int|NULL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Calculate the new value of map_top */
id|map_top
op_add_assign
id|map-&gt;mtd-&gt;size
suffix:semicolon
multiline_comment|/* File away the map structure */
id|list_add
c_func
(paren
op_amp
id|map-&gt;list
comma
op_amp
id|window-&gt;maps
)paren
suffix:semicolon
id|map
op_assign
l_int|NULL
suffix:semicolon
)brace
id|out
suffix:colon
multiline_comment|/* Free any left over map structures */
r_if
c_cond
(paren
id|map
)paren
(brace
id|kfree
c_func
(paren
id|map
)paren
suffix:semicolon
)brace
multiline_comment|/* See if I have any map structures */
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|window-&gt;maps
)paren
)paren
(brace
id|amd76xrom_cleanup
c_func
(paren
id|window
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
id|amd76xrom_window
op_star
id|window
op_assign
op_amp
id|amd76xrom_window
suffix:semicolon
id|amd76xrom_cleanup
c_func
(paren
id|window
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
r_static
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
id|amd76xrom_window.pdev
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
