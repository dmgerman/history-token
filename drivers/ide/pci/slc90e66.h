macro_line|#ifndef SLC90E66_H
DECL|macro|SLC90E66_H
mdefine_line|#define SLC90E66_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
DECL|macro|DISPLAY_SLC90E66_TIMINGS
mdefine_line|#define DISPLAY_SLC90E66_TIMINGS
DECL|macro|SLC90E66_DEBUG_DRIVE_INFO
mdefine_line|#define SLC90E66_DEBUG_DRIVE_INFO&t;0
macro_line|#if defined(DISPLAY_SLC90E66_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS)
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
DECL|variable|slc90e66_proc
r_static
id|u8
id|slc90e66_proc
suffix:semicolon
r_static
r_int
id|slc90e66_get_info
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
id|slc90e66_procs
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|name
suffix:colon
l_string|&quot;slc90e66&quot;
comma
id|set
suffix:colon
l_int|1
comma
id|get_info
suffix:colon
id|slc90e66_get_info
comma
id|parent
suffix:colon
l_int|NULL
comma
)brace
comma
)brace
suffix:semicolon
macro_line|#endif&t;/* defined(DISPLAY_SLC90E66_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS) */
r_static
r_void
id|init_setup_slc90e66
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
id|init_chipset_slc90e66
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
id|init_hwif_slc90e66
c_func
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
r_static
r_void
id|init_dma_slc90e66
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
id|slc90e66_chipsets
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|vendor
suffix:colon
id|PCI_VENDOR_ID_EFAR
comma
id|device
suffix:colon
id|PCI_DEVICE_ID_EFAR_SLC90E66_1
comma
id|name
suffix:colon
l_string|&quot;SLC90E66&quot;
comma
id|init_setup
suffix:colon
id|init_setup_slc90e66
comma
id|init_chipset
suffix:colon
id|init_chipset_slc90e66
comma
id|init_iops
suffix:colon
l_int|NULL
comma
id|init_hwif
suffix:colon
id|init_hwif_slc90e66
comma
id|init_dma
suffix:colon
id|init_dma_slc90e66
comma
id|channels
suffix:colon
l_int|2
comma
id|autodma
suffix:colon
id|AUTODMA
comma
id|enablebits
suffix:colon
(brace
(brace
l_int|0x41
comma
l_int|0x80
comma
l_int|0x80
)brace
comma
(brace
l_int|0x43
comma
l_int|0x80
comma
l_int|0x80
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
macro_line|#endif /* SLC90E66_H */
eof
