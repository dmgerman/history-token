macro_line|#ifndef SC1200_H
DECL|macro|SC1200_H
mdefine_line|#define SC1200_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
DECL|macro|DISPLAY_SC1200_TIMINGS
mdefine_line|#define DISPLAY_SC1200_TIMINGS
r_static
r_int
r_int
id|init_chipset_sc1200
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
id|init_hwif_sc1200
c_func
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
DECL|variable|__devinitdata
r_static
id|ide_pci_device_t
id|sc1200_chipsets
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
l_string|&quot;SC1200&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_sc1200
comma
dot
id|init_hwif
op_assign
id|init_hwif_sc1200
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
macro_line|#endif /* SC1200_H */
eof
