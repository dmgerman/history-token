macro_line|#ifndef TRM290_H
DECL|macro|TRM290_H
mdefine_line|#define TRM290_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
r_extern
r_void
id|init_hwif_trm290
c_func
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
DECL|variable|__initdata
r_static
id|ide_pci_device_t
id|trm290_chipsets
(braket
)braket
id|__initdata
op_assign
(brace
(brace
multiline_comment|/* 0 */
id|vendor
suffix:colon
id|PCI_VENDOR_ID_TEKRAM
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_TEKRAM_DC290
comma
id|name
suffix:colon
l_string|&quot;TRM290&quot;
comma
id|init_chipset
suffix:colon
l_int|NULL
comma
id|init_iops
suffix:colon
l_int|NULL
comma
id|init_hwif
suffix:colon
id|init_hwif_trm290
comma
id|init_dma
suffix:colon
l_int|NULL
comma
id|channels
suffix:colon
l_int|2
comma
id|autodma
suffix:colon
id|NOAUTODMA
comma
id|enablebits
suffix:colon
(brace
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
comma
id|bootable
suffix:colon
id|ON_BOARD
comma
id|extra
suffix:colon
l_int|0
comma
)brace
comma
(brace
id|vendor
suffix:colon
l_int|0
comma
id|device
suffix:colon
l_int|0
comma
id|channels
suffix:colon
l_int|0
comma
id|bootable
suffix:colon
id|EOL
comma
)brace
)brace
suffix:semicolon
macro_line|#endif /* TRM290_H */
eof