macro_line|#ifndef PIIX_H
DECL|macro|PIIX_H
mdefine_line|#define PIIX_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
DECL|macro|PIIX_DEBUG_DRIVE_INFO
mdefine_line|#define PIIX_DEBUG_DRIVE_INFO&t;&t;0
DECL|macro|DISPLAY_PIIX_TIMINGS
mdefine_line|#define DISPLAY_PIIX_TIMINGS
r_static
r_void
id|init_setup_piix
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
id|__devinit
id|init_chipset_piix
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
id|init_hwif_piix
c_func
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
DECL|macro|DECLARE_PIIX_DEV
mdefine_line|#define DECLARE_PIIX_DEV(pci_id, name_str) &bslash;&n;&t;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.vendor&t;&t;= PCI_VENDOR_ID_INTEL,&t;&bslash;&n;&t;&t;.device&t;&t;= pci_id,&t;&t;&bslash;&n;&t;&t;.name&t;&t;= name_str,&t;&t;&bslash;&n;&t;&t;.init_setup&t;= init_setup_piix,&t;&bslash;&n;&t;&t;.init_chipset&t;= init_chipset_piix,&t;&bslash;&n;&t;&t;.init_hwif&t;= init_hwif_piix,&t;&bslash;&n;&t;&t;.channels&t;= 2,&t;&t;&t;&bslash;&n;&t;&t;.autodma&t;= AUTODMA,&t;&t;&bslash;&n;&t;&t;.enablebits&t;= {{0x41,0x80,0x80}, {0x43,0x80,0x80}}, &bslash;&n;&t;&t;.bootable&t;= ON_BOARD,&t;&t;&bslash;&n;&t;}
multiline_comment|/*&n; *&t;Table of the various PIIX capability blocks&n; *&n; */
DECL|variable|__devinitdata
r_static
id|ide_pci_device_t
id|piix_pci_info
(braket
)braket
id|__devinitdata
op_assign
(brace
multiline_comment|/* 0  */
id|DECLARE_PIIX_DEV
c_func
(paren
id|PCI_DEVICE_ID_INTEL_82371FB_0
comma
l_string|&quot;PIIXa&quot;
)paren
comma
multiline_comment|/* 1  */
id|DECLARE_PIIX_DEV
c_func
(paren
id|PCI_DEVICE_ID_INTEL_82371FB_1
comma
l_string|&quot;PIIXb&quot;
)paren
comma
(brace
multiline_comment|/* 2 */
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_INTEL
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_INTEL_82371MX
comma
dot
id|name
op_assign
l_string|&quot;MPIIX&quot;
comma
dot
id|init_setup
op_assign
id|init_setup_piix
comma
dot
id|init_hwif
op_assign
id|init_hwif_piix
comma
dot
id|channels
op_assign
l_int|2
comma
dot
id|autodma
op_assign
id|NODMA
comma
dot
id|enablebits
op_assign
(brace
(brace
l_int|0x6D
comma
l_int|0x80
comma
l_int|0x80
)brace
comma
(brace
l_int|0x6F
comma
l_int|0x80
comma
l_int|0x80
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
multiline_comment|/* 3  */
id|DECLARE_PIIX_DEV
c_func
(paren
id|PCI_DEVICE_ID_INTEL_82371SB_1
comma
l_string|&quot;PIIX3&quot;
)paren
comma
multiline_comment|/* 4  */
id|DECLARE_PIIX_DEV
c_func
(paren
id|PCI_DEVICE_ID_INTEL_82371AB
comma
l_string|&quot;PIIX4&quot;
)paren
comma
multiline_comment|/* 5  */
id|DECLARE_PIIX_DEV
c_func
(paren
id|PCI_DEVICE_ID_INTEL_82801AB_1
comma
l_string|&quot;ICH0&quot;
)paren
comma
multiline_comment|/* 6  */
id|DECLARE_PIIX_DEV
c_func
(paren
id|PCI_DEVICE_ID_INTEL_82443MX_1
comma
l_string|&quot;PIIX4&quot;
)paren
comma
multiline_comment|/* 7  */
id|DECLARE_PIIX_DEV
c_func
(paren
id|PCI_DEVICE_ID_INTEL_82801AA_1
comma
l_string|&quot;ICH&quot;
)paren
comma
multiline_comment|/* 8  */
id|DECLARE_PIIX_DEV
c_func
(paren
id|PCI_DEVICE_ID_INTEL_82372FB_1
comma
l_string|&quot;PIIX4&quot;
)paren
comma
multiline_comment|/* 9  */
id|DECLARE_PIIX_DEV
c_func
(paren
id|PCI_DEVICE_ID_INTEL_82451NX
comma
l_string|&quot;PIIX4&quot;
)paren
comma
multiline_comment|/* 10 */
id|DECLARE_PIIX_DEV
c_func
(paren
id|PCI_DEVICE_ID_INTEL_82801BA_9
comma
l_string|&quot;ICH2&quot;
)paren
comma
multiline_comment|/* 11 */
id|DECLARE_PIIX_DEV
c_func
(paren
id|PCI_DEVICE_ID_INTEL_82801BA_8
comma
l_string|&quot;ICH2M&quot;
)paren
comma
multiline_comment|/* 12 */
id|DECLARE_PIIX_DEV
c_func
(paren
id|PCI_DEVICE_ID_INTEL_82801CA_10
comma
l_string|&quot;ICH3M&quot;
)paren
comma
multiline_comment|/* 13 */
id|DECLARE_PIIX_DEV
c_func
(paren
id|PCI_DEVICE_ID_INTEL_82801CA_11
comma
l_string|&quot;ICH3&quot;
)paren
comma
multiline_comment|/* 14 */
id|DECLARE_PIIX_DEV
c_func
(paren
id|PCI_DEVICE_ID_INTEL_82801DB_11
comma
l_string|&quot;ICH4&quot;
)paren
comma
multiline_comment|/* 15 */
id|DECLARE_PIIX_DEV
c_func
(paren
id|PCI_DEVICE_ID_INTEL_82801EB_11
comma
l_string|&quot;ICH5&quot;
)paren
comma
multiline_comment|/* 16 */
id|DECLARE_PIIX_DEV
c_func
(paren
id|PCI_DEVICE_ID_INTEL_82801E_11
comma
l_string|&quot;C-ICH&quot;
)paren
comma
multiline_comment|/* 17 */
id|DECLARE_PIIX_DEV
c_func
(paren
id|PCI_DEVICE_ID_INTEL_82801DB_10
comma
l_string|&quot;ICH4&quot;
)paren
comma
multiline_comment|/* 18 */
id|DECLARE_PIIX_DEV
c_func
(paren
id|PCI_DEVICE_ID_INTEL_82801EB_1
comma
l_string|&quot;ICH5-SATA&quot;
)paren
comma
multiline_comment|/* 19 */
id|DECLARE_PIIX_DEV
c_func
(paren
id|PCI_DEVICE_ID_INTEL_ESB_2
comma
l_string|&quot;ICH5&quot;
)paren
comma
multiline_comment|/* 20 */
id|DECLARE_PIIX_DEV
c_func
(paren
id|PCI_DEVICE_ID_INTEL_ICH6_19
comma
l_string|&quot;ICH6&quot;
)paren
)brace
suffix:semicolon
macro_line|#endif /* PIIX_H */
eof
