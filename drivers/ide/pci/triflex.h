multiline_comment|/* &n; * triflex.h&n; *&n; * Copyright (C) 2002 Hewlett-Packard Development Group, L.P.&n; * Author: Torben Mathiasen &lt;torben.mathiasen@hp.com&gt;&n; *&n; */
macro_line|#ifndef TRIFLEX_H
DECL|macro|TRIFLEX_H
mdefine_line|#define TRIFLEX_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
r_static
r_int
r_int
id|__devinit
id|init_chipset_triflex
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_const
r_char
op_star
)paren
suffix:semicolon
r_static
r_void
id|init_hwif_triflex
c_func
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
r_static
r_int
id|triflex_get_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
DECL|variable|triflex_proc
r_static
id|ide_pci_host_proc_t
id|triflex_proc
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;triflex&quot;
comma
dot
id|set
op_assign
l_int|1
comma
dot
id|get_info
op_assign
id|triflex_get_info
comma
)brace
suffix:semicolon
macro_line|#endif
DECL|variable|__devinitdata
r_static
id|ide_pci_device_t
id|triflex_devices
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_COMPAQ
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_COMPAQ_TRIFLEX_IDE
comma
dot
id|name
op_assign
l_string|&quot;TRIFLEX&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_triflex
comma
dot
id|init_iops
op_assign
l_int|NULL
comma
dot
id|init_hwif
op_assign
id|init_hwif_triflex
comma
dot
id|channels
op_assign
l_int|2
comma
dot
id|autodma
op_assign
id|AUTODMA
comma
dot
id|enablebits
op_assign
(brace
(brace
l_int|0x80
comma
l_int|0x01
comma
l_int|0x01
)brace
comma
(brace
l_int|0x80
comma
l_int|0x02
comma
l_int|0x02
)brace
)brace
comma
dot
id|bootable
op_assign
id|ON_BOARD
comma
)brace
comma
(brace
dot
id|bootable
op_assign
id|EOL
comma
)brace
)brace
suffix:semicolon
DECL|variable|triflex_pci_tbl
r_static
r_struct
id|pci_device_id
id|triflex_pci_tbl
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_COMPAQ
comma
id|PCI_DEVICE_ID_COMPAQ_TRIFLEX_IDE
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
l_int|0
comma
)brace
comma
)brace
suffix:semicolon
macro_line|#endif /* TRIFLEX_H */
eof
