multiline_comment|/*&n; *  linux/drivers/ide/rz1000.c&t;&t;Version 0.05&t;December 8, 1997&n; *&n; *  Copyright (C) 1995-1998  Linus Torvalds &amp; author (see below)&n; */
multiline_comment|/*&n; *  Principal Author:  mlord@pobox.com (Mark Lord)&n; *&n; *  See linux/MAINTAINERS for address of current maintainer.&n; *&n; *  This file provides support for disabling the buggy read-ahead&n; *  mode of the RZ1000 IDE chipset, commonly used on Intel motherboards.&n; *&n; *  Dunno if this fixes both ports, or only the primary port (?).&n; */
DECL|macro|REALLY_SLOW_IO
macro_line|#undef REALLY_SLOW_IO&t;&t;/* most systems can safely undef this */
macro_line|#include &lt;linux/config.h&gt; /* for CONFIG_BLK_DEV_IDEPCI */
macro_line|#include &lt;linux/types.h&gt;
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
macro_line|#ifdef CONFIG_BLK_DEV_IDEPCI
DECL|function|ide_init_rz1000
r_void
id|__init
id|ide_init_rz1000
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
multiline_comment|/* called from ide-pci.c */
(brace
r_int
r_int
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
l_string|&quot;%s: serialized, disabled unmasking &quot;
l_string|&quot;(buggy RZ1000/RZ1001)&bslash;n&quot;
comma
id|hwif-&gt;name
)paren
suffix:semicolon
)brace
)brace
macro_line|#else
DECL|function|init_rz1000
r_static
r_void
id|__init
id|init_rz1000
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_int
r_int
id|reg
comma
id|h
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_read_config_word
(paren
id|dev
comma
id|PCI_COMMAND
comma
op_amp
id|reg
)paren
op_logical_and
op_logical_neg
(paren
id|reg
op_amp
id|PCI_COMMAND_IO
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: buggy IDE controller disabled (BIOS)&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
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
l_string|&quot;IDE: disabled chipset read-ahead (buggy %s)&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|h
op_assign
l_int|0
suffix:semicolon
id|h
OL
id|MAX_HWIFS
suffix:semicolon
op_increment
id|h
)paren
(brace
id|ide_hwif_t
op_star
id|hwif
op_assign
op_amp
id|ide_hwifs
(braket
id|h
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|hwif-&gt;io_ports
(braket
id|IDE_DATA_OFFSET
)braket
op_eq
l_int|0x1f0
op_logical_or
id|hwif-&gt;io_ports
(braket
id|IDE_DATA_OFFSET
)braket
op_eq
l_int|0x170
)paren
op_logical_and
(paren
id|hwif-&gt;chipset
op_eq
id|ide_unknown
op_logical_or
id|hwif-&gt;chipset
op_eq
id|ide_generic
)paren
)paren
(brace
id|hwif-&gt;chipset
op_assign
id|ide_rz1000
suffix:semicolon
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
r_if
c_cond
(paren
id|hwif-&gt;io_ports
(braket
id|IDE_DATA_OFFSET
)braket
op_eq
l_int|0x170
)paren
id|hwif-&gt;channel
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: serialized, disabled unmasking &quot;
l_string|&quot;(buggy %s)&bslash;n&quot;
comma
id|hwif-&gt;name
comma
id|name
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|ide_probe_for_rz100x
r_void
id|__init
id|ide_probe_for_rz100x
(paren
r_void
)paren
multiline_comment|/* called from ide.c */
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
l_int|NULL
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
id|PCI_VENDOR_ID_PCTECH
comma
id|PCI_DEVICE_ID_PCTECH_RZ1000
comma
id|dev
)paren
)paren
op_ne
l_int|NULL
)paren
id|init_rz1000
(paren
id|dev
comma
l_string|&quot;RZ1000&quot;
)paren
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
id|PCI_VENDOR_ID_PCTECH
comma
id|PCI_DEVICE_ID_PCTECH_RZ1001
comma
id|dev
)paren
)paren
op_ne
l_int|NULL
)paren
id|init_rz1000
(paren
id|dev
comma
l_string|&quot;RZ1001&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_BLK_DEV_IDEPCI */
eof
