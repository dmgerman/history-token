macro_line|#ifndef AMD74XX_H
DECL|macro|AMD74XX_H
mdefine_line|#define AMD74XX_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
DECL|macro|DISPLAY_AMD_TIMINGS
mdefine_line|#define DISPLAY_AMD_TIMINGS
macro_line|#if defined(DISPLAY_AMD_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS)
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
DECL|variable|amd74xx_proc
r_static
id|u8
id|amd74xx_proc
suffix:semicolon
r_static
r_int
id|amd74xx_get_info
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
id|amd74xx_procs
(braket
)braket
id|__initdata
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;amd74xx&quot;
comma
dot
id|set
op_assign
l_int|1
comma
dot
id|get_info
op_assign
id|amd74xx_get_info
comma
dot
id|parent
op_assign
l_int|NULL
comma
)brace
comma
)brace
suffix:semicolon
macro_line|#endif  /* defined(DISPLAY_AMD_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS) */
r_static
r_int
r_int
id|init_chipset_amd74xx
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
id|init_hwif_amd74xx
c_func
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
DECL|variable|__devinitdata
r_static
id|ide_pci_device_t
id|amd74xx_chipsets
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
id|PCI_VENDOR_ID_AMD
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_AMD_COBRA_7401
comma
dot
id|name
op_assign
l_string|&quot;AMD7401&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_amd74xx
comma
dot
id|init_hwif
op_assign
id|init_hwif_amd74xx
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
dot
id|bootable
op_assign
id|ON_BOARD
comma
dot
id|extra
op_assign
l_int|0
)brace
comma
(brace
multiline_comment|/* 1 */
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_AMD
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_AMD_VIPER_7409
comma
dot
id|name
op_assign
l_string|&quot;AMD7409&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_amd74xx
comma
dot
id|init_hwif
op_assign
id|init_hwif_amd74xx
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
dot
id|bootable
op_assign
id|ON_BOARD
comma
dot
id|extra
op_assign
l_int|0
)brace
comma
(brace
multiline_comment|/* 2 */
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_AMD
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_AMD_VIPER_7411
comma
dot
id|name
op_assign
l_string|&quot;AMD7411&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_amd74xx
comma
dot
id|init_hwif
op_assign
id|init_hwif_amd74xx
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
dot
id|bootable
op_assign
id|ON_BOARD
comma
dot
id|extra
op_assign
l_int|0
)brace
comma
(brace
multiline_comment|/* 3 */
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_AMD
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_AMD_OPUS_7441
comma
dot
id|name
op_assign
l_string|&quot;AMD7441&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_amd74xx
comma
dot
id|init_hwif
op_assign
id|init_hwif_amd74xx
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
dot
id|bootable
op_assign
id|ON_BOARD
comma
dot
id|extra
op_assign
l_int|0
)brace
comma
(brace
multiline_comment|/* 4 */
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_AMD
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_AMD_8111_IDE
comma
dot
id|name
op_assign
l_string|&quot;AMD8111&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_amd74xx
comma
dot
id|init_hwif
op_assign
id|init_hwif_amd74xx
comma
dot
id|autodma
op_assign
id|AUTODMA
comma
dot
id|channels
op_assign
l_int|2
comma
dot
id|enablebits
op_assign
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
dot
id|bootable
op_assign
id|ON_BOARD
comma
dot
id|extra
op_assign
l_int|0
)brace
comma
(brace
multiline_comment|/* 5 */
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_NVIDIA
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_NVIDIA_NFORCE_IDE
comma
dot
id|name
op_assign
l_string|&quot;NFORCE&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_amd74xx
comma
dot
id|init_hwif
op_assign
id|init_hwif_amd74xx
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
l_int|0x50
comma
l_int|0x02
comma
l_int|0x02
)brace
comma
(brace
l_int|0x50
comma
l_int|0x01
comma
l_int|0x01
)brace
)brace
comma
dot
id|bootable
op_assign
id|ON_BOARD
comma
dot
id|extra
op_assign
l_int|0
comma
)brace
comma
(brace
multiline_comment|/* 6 */
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_NVIDIA
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_NVIDIA_NFORCE2_IDE
comma
dot
id|name
op_assign
l_string|&quot;NFORCE2&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_amd74xx
comma
dot
id|init_hwif
op_assign
id|init_hwif_amd74xx
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
l_int|0x50
comma
l_int|0x02
comma
l_int|0x02
)brace
comma
(brace
l_int|0x50
comma
l_int|0x01
comma
l_int|0x01
)brace
)brace
comma
dot
id|bootable
op_assign
id|ON_BOARD
comma
dot
id|extra
op_assign
l_int|0
comma
)brace
comma
(brace
multiline_comment|/* 7 */
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_NVIDIA
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_NVIDIA_NFORCE2S_IDE
comma
dot
id|name
op_assign
l_string|&quot;NFORCE2S&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_amd74xx
comma
dot
id|init_hwif
op_assign
id|init_hwif_amd74xx
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
l_int|0x50
comma
l_int|0x02
comma
l_int|0x02
)brace
comma
(brace
l_int|0x50
comma
l_int|0x01
comma
l_int|0x01
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
multiline_comment|/* 8 */
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_NVIDIA
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_NVIDIA_NFORCE2S_SATA
comma
dot
id|name
op_assign
l_string|&quot;NFORCE2S-SATA&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_amd74xx
comma
dot
id|init_hwif
op_assign
id|init_hwif_amd74xx
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
l_int|0x50
comma
l_int|0x02
comma
l_int|0x02
)brace
comma
(brace
l_int|0x50
comma
l_int|0x01
comma
l_int|0x01
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
multiline_comment|/* 9 */
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_NVIDIA
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_NVIDIA_NFORCE3_IDE
comma
dot
id|name
op_assign
l_string|&quot;NFORCE3&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_amd74xx
comma
dot
id|init_hwif
op_assign
id|init_hwif_amd74xx
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
l_int|0x50
comma
l_int|0x02
comma
l_int|0x02
)brace
comma
(brace
l_int|0x50
comma
l_int|0x01
comma
l_int|0x01
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
multiline_comment|/* 10 */
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_NVIDIA
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_NVIDIA_NFORCE3S_IDE
comma
dot
id|name
op_assign
l_string|&quot;NFORCE3S&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_amd74xx
comma
dot
id|init_hwif
op_assign
id|init_hwif_amd74xx
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
l_int|0x50
comma
l_int|0x02
comma
l_int|0x02
)brace
comma
(brace
l_int|0x50
comma
l_int|0x01
comma
l_int|0x01
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
multiline_comment|/* 11 */
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_NVIDIA
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_NVIDIA_NFORCE3S_SATA
comma
dot
id|name
op_assign
l_string|&quot;NFORCE3S-SATA&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_amd74xx
comma
dot
id|init_hwif
op_assign
id|init_hwif_amd74xx
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
l_int|0x50
comma
l_int|0x02
comma
l_int|0x02
)brace
comma
(brace
l_int|0x50
comma
l_int|0x01
comma
l_int|0x01
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
multiline_comment|/* 12 */
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_NVIDIA
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_NVIDIA_NFORCE3S_SATA2
comma
dot
id|name
op_assign
l_string|&quot;NFORCE3S-SATA2&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_amd74xx
comma
dot
id|init_hwif
op_assign
id|init_hwif_amd74xx
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
l_int|0x50
comma
l_int|0x02
comma
l_int|0x02
)brace
comma
(brace
l_int|0x50
comma
l_int|0x01
comma
l_int|0x01
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
dot
id|vendor
op_assign
l_int|0
comma
dot
id|device
op_assign
l_int|0
comma
dot
id|channels
op_assign
l_int|0
comma
dot
id|bootable
op_assign
id|EOL
comma
)brace
)brace
suffix:semicolon
macro_line|#endif /* AMD74XX_H */
eof
