multiline_comment|/* linux/drivers/mtd/maps/scx200_docflash.c &n;&n;   Copyright (c) 2001,2002 Christer Weinigel &lt;wingel@nano-system.com&gt;&n;&n;   $Id: scx200_docflash.c,v 1.9 2004/11/16 18:29:02 dwmw2 Exp $ &n;&n;   National Semiconductor SCx200 flash mapped with DOCCS&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/scx200.h&gt;
DECL|macro|NAME
mdefine_line|#define NAME &quot;scx200_docflash&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Christer Weinigel &lt;wingel@hack.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;NatSemi SCx200 DOCCS Flash Driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/* Set this to one if you want to partition the flash */
DECL|macro|PARTITION
mdefine_line|#define PARTITION 1
id|MODULE_PARM
c_func
(paren
id|probe
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|probe
comma
l_string|&quot;Probe for a BIOS mapping&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|size
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|size
comma
l_string|&quot;Size of the flash mapping&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|width
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|width
comma
l_string|&quot;Data width of the flash mapping (8/16)&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|flashtype
comma
l_string|&quot;s&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|flashtype
comma
l_string|&quot;Type of MTD probe to do&quot;
)paren
suffix:semicolon
DECL|variable|probe
r_static
r_int
id|probe
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Don&squot;t autoprobe */
DECL|variable|size
r_static
r_int
id|size
op_assign
l_int|0x1000000
suffix:semicolon
multiline_comment|/* 16 MiB the whole ISA address space */
DECL|variable|width
r_static
r_int
id|width
op_assign
l_int|8
suffix:semicolon
multiline_comment|/* Default to 8 bits wide */
DECL|variable|flashtype
r_static
r_char
op_star
id|flashtype
op_assign
l_string|&quot;cfi_probe&quot;
suffix:semicolon
DECL|variable|docmem
r_static
r_struct
id|resource
id|docmem
op_assign
(brace
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
dot
id|name
op_assign
l_string|&quot;NatSemi SCx200 DOCCS Flash&quot;
comma
)brace
suffix:semicolon
DECL|variable|mymtd
r_static
r_struct
id|mtd_info
op_star
id|mymtd
suffix:semicolon
macro_line|#if PARTITION
DECL|variable|partition_info
r_static
r_struct
id|mtd_partition
id|partition_info
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;DOCCS Boot kernel&quot;
comma
dot
id|offset
op_assign
l_int|0
comma
dot
id|size
op_assign
l_int|0xc0000
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;DOCCS Low BIOS&quot;
comma
dot
id|offset
op_assign
l_int|0xc0000
comma
dot
id|size
op_assign
l_int|0x40000
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;DOCCS File system&quot;
comma
dot
id|offset
op_assign
l_int|0x100000
comma
dot
id|size
op_assign
op_complement
l_int|0
multiline_comment|/* calculate from flash size */
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;DOCCS High BIOS&quot;
comma
dot
id|offset
op_assign
op_complement
l_int|0
comma
multiline_comment|/* calculate from flash size */
dot
id|size
op_assign
l_int|0x80000
)brace
comma
)brace
suffix:semicolon
DECL|macro|NUM_PARTITIONS
mdefine_line|#define NUM_PARTITIONS (sizeof(partition_info)/sizeof(partition_info[0]))
macro_line|#endif
DECL|variable|scx200_docflash_map
r_static
r_struct
id|map_info
id|scx200_docflash_map
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;NatSemi SCx200 DOCCS Flash&quot;
comma
)brace
suffix:semicolon
DECL|function|init_scx200_docflash
r_static
r_int
id|__init
id|init_scx200_docflash
c_func
(paren
r_void
)paren
(brace
r_int
id|u
suffix:semicolon
r_int
id|base
suffix:semicolon
r_int
id|ctrl
suffix:semicolon
r_int
id|pmr
suffix:semicolon
r_struct
id|pci_dev
op_star
id|bridge
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
id|NAME
l_string|&quot;: NatSemi SCx200 DOCCS Flash Driver&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bridge
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_NS
comma
id|PCI_DEVICE_ID_NS_SCx200_BRIDGE
comma
l_int|NULL
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scx200_cb_probe
c_func
(paren
id|SCx200_CB_BASE
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|NAME
l_string|&quot;: no configuration block found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|probe
)paren
(brace
multiline_comment|/* Try to use the present flash mapping if any */
id|pci_read_config_dword
c_func
(paren
id|bridge
comma
id|SCx200_DOCCS_BASE
comma
op_amp
id|base
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|bridge
comma
id|SCx200_DOCCS_CTRL
comma
op_amp
id|ctrl
)paren
suffix:semicolon
id|pmr
op_assign
id|inl
c_func
(paren
id|SCx200_CB_BASE
op_plus
id|SCx200_PMR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|base
op_eq
l_int|0
op_logical_or
(paren
id|ctrl
op_amp
l_int|0x07000000
)paren
op_ne
l_int|0x07000000
op_logical_or
(paren
id|ctrl
op_amp
l_int|0x0007ffff
)paren
op_eq
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|size
op_assign
(paren
(paren
id|ctrl
op_amp
l_int|0x1fff
)paren
op_lshift
l_int|13
)paren
op_plus
(paren
l_int|1
op_lshift
l_int|13
)paren
suffix:semicolon
r_for
c_loop
(paren
id|u
op_assign
id|size
suffix:semicolon
id|u
OG
l_int|1
suffix:semicolon
id|u
op_rshift_assign
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|u
op_ne
l_int|1
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|pmr
op_amp
(paren
l_int|1
op_lshift
l_int|6
)paren
)paren
id|width
op_assign
l_int|16
suffix:semicolon
r_else
id|width
op_assign
l_int|8
suffix:semicolon
id|docmem.start
op_assign
id|base
suffix:semicolon
id|docmem.end
op_assign
id|base
op_plus
id|size
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
id|docmem
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|NAME
l_string|&quot;: unable to allocate memory for flash mapping&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
)brace
r_else
(brace
r_for
c_loop
(paren
id|u
op_assign
id|size
suffix:semicolon
id|u
OG
l_int|1
suffix:semicolon
id|u
op_rshift_assign
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|u
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|NAME
l_string|&quot;: invalid size for flash mapping&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|width
op_ne
l_int|8
op_logical_and
id|width
op_ne
l_int|16
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|NAME
l_string|&quot;: invalid bus width for flash mapping&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|allocate_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|docmem
comma
id|size
comma
l_int|0xc0000000
comma
l_int|0xffffffff
comma
id|size
comma
l_int|NULL
comma
l_int|NULL
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|NAME
l_string|&quot;: unable to allocate memory for flash mapping&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|ctrl
op_assign
l_int|0x07000000
op_or
(paren
(paren
id|size
op_minus
l_int|1
)paren
op_rshift
l_int|13
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;DOCCS BASE=0x%08lx, CTRL=0x%08lx&bslash;n&quot;
comma
(paren
r_int
)paren
id|docmem.start
comma
(paren
r_int
)paren
id|ctrl
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|bridge
comma
id|SCx200_DOCCS_BASE
comma
id|docmem.start
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|bridge
comma
id|SCx200_DOCCS_CTRL
comma
id|ctrl
)paren
suffix:semicolon
id|pmr
op_assign
id|inl
c_func
(paren
id|SCx200_CB_BASE
op_plus
id|SCx200_PMR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|width
op_eq
l_int|8
)paren
(brace
id|pmr
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|6
)paren
suffix:semicolon
)brace
r_else
(brace
id|pmr
op_or_assign
(paren
l_int|1
op_lshift
l_int|6
)paren
suffix:semicolon
)brace
id|outl
c_func
(paren
id|pmr
comma
id|SCx200_CB_BASE
op_plus
id|SCx200_PMR
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
id|NAME
l_string|&quot;: DOCCS mapped at 0x%lx-0x%lx, width %d&bslash;n&quot;
comma
id|docmem.start
comma
id|docmem.end
comma
id|width
)paren
suffix:semicolon
id|scx200_docflash_map.size
op_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|width
op_eq
l_int|8
)paren
id|scx200_docflash_map.bankwidth
op_assign
l_int|1
suffix:semicolon
r_else
id|scx200_docflash_map.bankwidth
op_assign
l_int|2
suffix:semicolon
id|simple_map_init
c_func
(paren
op_amp
id|scx200_docflash_map
)paren
suffix:semicolon
id|scx200_docflash_map.phys
op_assign
id|docmem.start
suffix:semicolon
id|scx200_docflash_map.virt
op_assign
id|ioremap
c_func
(paren
id|docmem.start
comma
id|scx200_docflash_map.size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scx200_docflash_map.virt
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|NAME
l_string|&quot;: failed to ioremap the flash&bslash;n&quot;
)paren
suffix:semicolon
id|release_resource
c_func
(paren
op_amp
id|docmem
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|mymtd
op_assign
id|do_map_probe
c_func
(paren
id|flashtype
comma
op_amp
id|scx200_docflash_map
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mymtd
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|NAME
l_string|&quot;: unable to detect flash&bslash;n&quot;
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|scx200_docflash_map.virt
)paren
suffix:semicolon
id|release_resource
c_func
(paren
op_amp
id|docmem
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|size
OL
id|mymtd-&gt;size
)paren
id|printk
c_func
(paren
id|KERN_WARNING
id|NAME
l_string|&quot;: warning, flash mapping is smaller than flash size&bslash;n&quot;
)paren
suffix:semicolon
id|mymtd-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
macro_line|#if PARTITION
id|partition_info
(braket
l_int|3
)braket
dot
id|offset
op_assign
id|mymtd-&gt;size
op_minus
id|partition_info
(braket
l_int|3
)braket
dot
id|size
suffix:semicolon
id|partition_info
(braket
l_int|2
)braket
dot
id|size
op_assign
id|partition_info
(braket
l_int|3
)braket
dot
id|offset
op_minus
id|partition_info
(braket
l_int|2
)braket
dot
id|offset
suffix:semicolon
id|add_mtd_partitions
c_func
(paren
id|mymtd
comma
id|partition_info
comma
id|NUM_PARTITIONS
)paren
suffix:semicolon
macro_line|#else
id|add_mtd_device
c_func
(paren
id|mymtd
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_scx200_docflash
r_static
r_void
id|__exit
id|cleanup_scx200_docflash
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|mymtd
)paren
(brace
macro_line|#if PARTITION
id|del_mtd_partitions
c_func
(paren
id|mymtd
)paren
suffix:semicolon
macro_line|#else
id|del_mtd_device
c_func
(paren
id|mymtd
)paren
suffix:semicolon
macro_line|#endif
id|map_destroy
c_func
(paren
id|mymtd
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|scx200_docflash_map.virt
)paren
(brace
id|iounmap
c_func
(paren
id|scx200_docflash_map.virt
)paren
suffix:semicolon
id|release_resource
c_func
(paren
op_amp
id|docmem
)paren
suffix:semicolon
)brace
)brace
DECL|variable|init_scx200_docflash
id|module_init
c_func
(paren
id|init_scx200_docflash
)paren
suffix:semicolon
DECL|variable|cleanup_scx200_docflash
id|module_exit
c_func
(paren
id|cleanup_scx200_docflash
)paren
suffix:semicolon
multiline_comment|/*&n;    Local variables:&n;        compile-command: &quot;make -k -C ../../.. SUBDIRS=drivers/mtd/maps modules&quot;&n;        c-basic-offset: 8&n;    End:&n;*/
eof
