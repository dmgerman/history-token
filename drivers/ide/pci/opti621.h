macro_line|#ifndef OPTI621_H
DECL|macro|OPTI621_H
mdefine_line|#define OPTI621_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
r_static
r_void
id|init_setup_opti621
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
r_static
r_void
id|init_hwif_opti621
c_func
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
DECL|variable|__devinitdata
r_static
id|ide_pci_device_t
id|opti621_chipsets
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
multiline_comment|/* 0 */
dot
id|name
op_assign
l_string|&quot;OPTI621&quot;
comma
dot
id|init_setup
op_assign
id|init_setup_opti621
comma
dot
id|init_hwif
op_assign
id|init_hwif_opti621
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
l_int|0x45
comma
l_int|0x80
comma
l_int|0x00
)brace
comma
(brace
l_int|0x40
comma
l_int|0x08
comma
l_int|0x00
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
multiline_comment|/* 1 */
dot
id|name
op_assign
l_string|&quot;OPTI621X&quot;
comma
dot
id|init_setup
op_assign
id|init_setup_opti621
comma
dot
id|init_hwif
op_assign
id|init_hwif_opti621
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
l_int|0x45
comma
l_int|0x80
comma
l_int|0x00
)brace
comma
(brace
l_int|0x40
comma
l_int|0x08
comma
l_int|0x00
)brace
)brace
comma
dot
id|bootable
op_assign
id|ON_BOARD
comma
)brace
)brace
suffix:semicolon
macro_line|#endif /* OPTI621_H */
eof
