macro_line|#ifndef HPT34X_H
DECL|macro|HPT34X_H
mdefine_line|#define HPT34X_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
DECL|macro|HPT343_DEBUG_DRIVE_INFO
mdefine_line|#define HPT343_DEBUG_DRIVE_INFO&t;&t;0
macro_line|#ifndef SPLIT_BYTE
DECL|macro|SPLIT_BYTE
mdefine_line|#define SPLIT_BYTE(B,H,L)&t;((H)=(B&gt;&gt;4), (L)=(B-((B&gt;&gt;4)&lt;&lt;4)))
macro_line|#endif
DECL|macro|DISPLAY_HPT34X_TIMINGS
macro_line|#undef DISPLAY_HPT34X_TIMINGS
macro_line|#if defined(DISPLAY_HPT34X_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS)
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
DECL|variable|hpt34x_proc
r_static
id|u8
id|hpt34x_proc
suffix:semicolon
r_static
r_int
id|hpt34x_get_info
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
id|hpt34x_procs
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|name
suffix:colon
l_string|&quot;hpt34x&quot;
comma
id|set
suffix:colon
l_int|1
comma
id|get_info
suffix:colon
id|hpt34x_get_info
comma
id|parent
suffix:colon
l_int|NULL
comma
)brace
comma
)brace
suffix:semicolon
macro_line|#endif  /* defined(DISPLAY_HPT34X_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS) */
r_static
r_int
r_int
id|init_chipset_hpt34x
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
id|init_hwif_hpt34x
c_func
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
r_static
r_void
id|init_dma_hpt34x
c_func
(paren
id|ide_hwif_t
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|variable|__initdata
r_static
id|ide_pci_device_t
id|hpt34x_chipsets
(braket
)braket
id|__initdata
op_assign
(brace
(brace
multiline_comment|/* 0 */
id|vendor
suffix:colon
id|PCI_VENDOR_ID_TTI
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_TTI_HPT343
comma
id|name
suffix:colon
l_string|&quot;HPT34X&quot;
comma
id|init_chipset
suffix:colon
id|init_chipset_hpt34x
comma
id|init_iops
suffix:colon
l_int|NULL
comma
id|init_hwif
suffix:colon
id|init_hwif_hpt34x
comma
id|init_dma
suffix:colon
id|init_dma_hpt34x
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
id|NEVER_BOARD
comma
id|extra
suffix:colon
l_int|16
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
macro_line|#endif /* HPT34X_H */
eof