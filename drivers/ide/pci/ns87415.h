macro_line|#ifndef NS87415_H
DECL|macro|NS87415_H
mdefine_line|#define NS87415_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
r_static
r_void
id|init_hwif_ns87415
c_func
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
DECL|variable|__devinitdata
r_static
id|ide_pci_device_t
id|ns87415_chipsets
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
l_string|&quot;NS87415&quot;
comma
dot
id|init_hwif
op_assign
id|init_hwif_ns87415
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
id|bootable
op_assign
id|ON_BOARD
comma
)brace
)brace
suffix:semicolon
macro_line|#endif /* NS87415_H */
eof
