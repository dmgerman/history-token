macro_line|#ifndef PDC_ADMA_H
DECL|macro|PDC_ADMA_H
mdefine_line|#define PDC_ADMA_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
DECL|macro|DISPLAY_PDCADMA_TIMINGS
macro_line|#undef DISPLAY_PDCADMA_TIMINGS
macro_line|#if defined(DISPLAY_PDCADMA_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS)
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
DECL|variable|pdcadma_proc
r_static
id|u8
id|pdcadma_proc
suffix:semicolon
r_static
r_int
id|pdcadma_get_info
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
id|pdcadma_procs
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|name
suffix:colon
l_string|&quot;pdcadma&quot;
comma
id|set
suffix:colon
l_int|1
comma
id|get_info
suffix:colon
id|pdcadma_get_info
comma
id|parent
suffix:colon
l_int|NULL
comma
)brace
comma
)brace
suffix:semicolon
macro_line|#endif  /* defined(DISPLAY_PDCADMA_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS) */
r_static
r_void
id|init_setup_pdcadma
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
r_int
r_int
id|init_chipset_pdcadma
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
id|init_hwif_pdcadma
c_func
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
r_static
r_void
id|init_dma_pdcadma
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
id|pdcadma_chipsets
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|vendor
suffix:colon
id|PCI_VENDOR_ID_PDC
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_PDC_1841
comma
id|name
suffix:colon
l_string|&quot;PDCADMA&quot;
comma
id|init_setup
suffix:colon
id|init_setup_pdcadma
comma
id|init_chipset
suffix:colon
id|init_chipset_pdcadma
comma
id|init_iops
suffix:colon
l_int|NULL
comma
id|init_hwif
suffix:colon
id|init_hwif_pdcadma
comma
id|init_dma
suffix:colon
id|init_dma_pdcadma
comma
id|channels
suffix:colon
l_int|2
comma
id|autodma
suffix:colon
id|NODMA
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
id|OFF_BOARD
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
macro_line|#endif /* PDC_ADMA_H */
eof
