macro_line|#ifndef CS5530_H
DECL|macro|CS5530_H
mdefine_line|#define CS5530_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
DECL|macro|DISPLAY_CS5530_TIMINGS
mdefine_line|#define DISPLAY_CS5530_TIMINGS
r_static
r_int
r_int
id|init_chipset_cs5530
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
id|init_hwif_cs5530
c_func
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
DECL|variable|__devinitdata
r_static
id|ide_pci_device_t
id|cs5530_chipsets
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
multiline_comment|/* 0 */
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_CYRIX
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_CYRIX_5530_IDE
comma
dot
id|name
op_assign
l_string|&quot;CS5530&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_cs5530
comma
dot
id|init_hwif
op_assign
id|init_hwif_cs5530
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
macro_line|#endif /* CS5530_H */
eof
