multiline_comment|/*&n; *  linux/drivers/ide/pci/rz1000.c&t;Version 0.06&t;January 12, 2003&n; *&n; *  Copyright (C) 1995-1998  Linus Torvalds &amp; author (see below)&n; */
multiline_comment|/*&n; *  Principal Author:  mlord@pobox.com (Mark Lord)&n; *&n; *  See linux/MAINTAINERS for address of current maintainer.&n; *&n; *  This file provides support for disabling the buggy read-ahead&n; *  mode of the RZ1000 IDE chipset, commonly used on Intel motherboards.&n; *&n; *  Dunno if this fixes both ports, or only the primary port (?).&n; */
DECL|macro|REALLY_SLOW_IO
macro_line|#undef REALLY_SLOW_IO&t;&t;/* most systems can safely undef this */
macro_line|#include &lt;linux/config.h&gt; /* for CONFIG_BLK_DEV_IDEPCI */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;rz1000.h&quot;
DECL|function|init_hwif_rz1000
r_static
r_void
id|__init
id|init_hwif_rz1000
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
id|u16
id|reg
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
id|hwif-&gt;chipset
op_assign
id|ide_rz1000
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_read_config_word
(paren
id|dev
comma
l_int|0x40
comma
op_amp
id|reg
)paren
op_logical_and
op_logical_neg
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x40
comma
id|reg
op_amp
l_int|0xdfff
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: disabled chipset read-ahead &quot;
l_string|&quot;(buggy RZ1000/RZ1001)&bslash;n&quot;
comma
id|hwif-&gt;name
)paren
suffix:semicolon
)brace
r_else
(brace
id|hwif-&gt;serialized
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|0
)braket
dot
id|no_unmask
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|1
)braket
dot
id|no_unmask
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: serialized, disabled unmasking &quot;
l_string|&quot;(buggy RZ1000/RZ1001)&bslash;n&quot;
comma
id|hwif-&gt;name
)paren
suffix:semicolon
)brace
)brace
r_extern
r_void
id|ide_setup_pci_device
c_func
(paren
r_struct
id|pci_dev
op_star
comma
id|ide_pci_device_t
op_star
)paren
suffix:semicolon
DECL|function|rz1000_init_one
r_static
r_int
id|__devinit
id|rz1000_init_one
c_func
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
id|id
)paren
(brace
id|ide_pci_device_t
op_star
id|d
op_assign
op_amp
id|rz1000_chipsets
(braket
id|id-&gt;driver_data
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;device
op_ne
id|d-&gt;device
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|ide_setup_pci_device
c_func
(paren
id|dev
comma
id|d
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|rz1000_pci_tbl
r_static
r_struct
id|pci_device_id
id|rz1000_pci_tbl
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_PCTECH
comma
id|PCI_DEVICE_ID_PCTECH_RZ1000
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
id|PCI_VENDOR_ID_PCTECH
comma
id|PCI_DEVICE_ID_PCTECH_RZ1001
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|1
)brace
comma
(brace
l_int|0
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|driver
r_static
r_struct
id|pci_driver
id|driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;RZ1000 IDE&quot;
comma
dot
id|id_table
op_assign
id|rz1000_pci_tbl
comma
dot
id|probe
op_assign
id|rz1000_init_one
comma
)brace
suffix:semicolon
DECL|function|rz1000_ide_init
r_static
r_int
id|rz1000_ide_init
c_func
(paren
r_void
)paren
(brace
r_return
id|ide_pci_register_driver
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
)brace
DECL|variable|rz1000_ide_init
id|module_init
c_func
(paren
id|rz1000_ide_init
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Andre Hedrick&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;PCI driver module for RZ1000 IDE&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
