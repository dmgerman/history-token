macro_line|#ifndef VIA82CXXX_H
DECL|macro|VIA82CXXX_H
mdefine_line|#define VIA82CXXX_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
DECL|macro|DISPLAY_VIA_TIMINGS
mdefine_line|#define DISPLAY_VIA_TIMINGS
macro_line|#if defined(DISPLAY_VIA_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS)
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
DECL|variable|via_proc
r_static
id|u8
id|via_proc
suffix:semicolon
r_static
r_int
id|via_get_info
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
DECL|variable|__initdata
r_static
id|ide_pci_host_proc_t
id|via_procs
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|name
suffix:colon
l_string|&quot;via&quot;
comma
id|set
suffix:colon
l_int|1
comma
id|get_info
suffix:colon
id|via_get_info
comma
id|parent
suffix:colon
l_int|NULL
comma
)brace
comma
)brace
suffix:semicolon
macro_line|#endif /* DISPLAY_VIA_TIMINGS &amp;&amp; CONFIG_PROC_FS */
r_static
r_int
r_int
id|init_chipset_via82cxxx
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
id|init_hwif_via82cxxx
c_func
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
r_static
r_void
id|init_dma_via82cxxx
c_func
(paren
id|ide_hwif_t
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|variable|__devinitdata
r_static
id|ide_pci_device_t
id|via82cxxx_chipsets
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
multiline_comment|/* 0 */
id|vendor
suffix:colon
id|PCI_VENDOR_ID_VIA
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_VIA_82C576_1
comma
id|name
suffix:colon
l_string|&quot;VP_IDE&quot;
comma
id|init_chipset
suffix:colon
id|init_chipset_via82cxxx
comma
id|init_iops
suffix:colon
l_int|NULL
comma
id|init_hwif
suffix:colon
id|init_hwif_via82cxxx
comma
id|init_dma
suffix:colon
id|init_dma_via82cxxx
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
l_int|0x40
comma
l_int|0x02
comma
l_int|0x02
)brace
comma
(brace
l_int|0x40
comma
l_int|0x01
comma
l_int|0x01
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
multiline_comment|/* 1 */
id|vendor
suffix:colon
id|PCI_VENDOR_ID_VIA
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_VIA_82C586_1
comma
id|name
suffix:colon
l_string|&quot;VP_IDE&quot;
comma
id|init_chipset
suffix:colon
id|init_chipset_via82cxxx
comma
id|init_iops
suffix:colon
l_int|NULL
comma
id|init_hwif
suffix:colon
id|init_hwif_via82cxxx
comma
id|init_dma
suffix:colon
id|init_dma_via82cxxx
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
l_int|0x40
comma
l_int|0x02
comma
l_int|0x02
)brace
comma
(brace
l_int|0x40
comma
l_int|0x01
comma
l_int|0x01
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
macro_line|#endif /* VIA82CXXX_H */
eof
