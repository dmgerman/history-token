macro_line|#ifndef SIS5513_H
DECL|macro|SIS5513_H
mdefine_line|#define SIS5513_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
DECL|macro|DISPLAY_SIS_TIMINGS
mdefine_line|#define DISPLAY_SIS_TIMINGS
macro_line|#if defined(DISPLAY_SIS_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS)
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
DECL|variable|sis_proc
r_static
id|u8
id|sis_proc
suffix:semicolon
r_static
r_int
id|sis_get_info
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
id|sis_procs
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|name
suffix:colon
l_string|&quot;sis&quot;
comma
id|set
suffix:colon
l_int|1
comma
id|get_info
suffix:colon
id|sis_get_info
comma
id|parent
suffix:colon
l_int|NULL
comma
)brace
comma
)brace
suffix:semicolon
macro_line|#endif /* defined(DISPLAY_SIS_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS) */
r_static
r_int
r_int
id|init_chipset_sis5513
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
id|init_hwif_sis5513
c_func
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
r_static
r_void
id|init_dma_sis5513
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
id|sis5513_chipsets
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
multiline_comment|/* 0 */
id|vendor
suffix:colon
id|PCI_VENDOR_ID_SI
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_SI_5513
comma
id|name
suffix:colon
l_string|&quot;SIS5513&quot;
comma
id|init_chipset
suffix:colon
id|init_chipset_sis5513
comma
id|init_iops
suffix:colon
l_int|NULL
comma
id|init_hwif
suffix:colon
id|init_hwif_sis5513
comma
id|init_dma
suffix:colon
id|init_dma_sis5513
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
l_int|0x4a
comma
l_int|0x02
comma
l_int|0x02
)brace
comma
(brace
l_int|0x4a
comma
l_int|0x04
comma
l_int|0x04
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
macro_line|#endif /* SIS5513_H */
eof
