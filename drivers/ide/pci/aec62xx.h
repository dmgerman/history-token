macro_line|#ifndef AEC62XX_H
DECL|macro|AEC62XX_H
mdefine_line|#define AEC62XX_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
DECL|macro|DISPLAY_AEC62XX_TIMINGS
mdefine_line|#define DISPLAY_AEC62XX_TIMINGS
DECL|struct|chipset_bus_clock_list_entry
r_struct
id|chipset_bus_clock_list_entry
(brace
DECL|member|xfer_speed
id|byte
id|xfer_speed
suffix:semicolon
DECL|member|chipset_settings
id|byte
id|chipset_settings
suffix:semicolon
DECL|member|ultra_settings
id|byte
id|ultra_settings
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|aec6xxx_33_base
r_struct
id|chipset_bus_clock_list_entry
id|aec6xxx_33_base
(braket
)braket
op_assign
(brace
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
(brace
id|XFER_UDMA_6
comma
l_int|0x31
comma
l_int|0x07
)brace
comma
(brace
id|XFER_UDMA_5
comma
l_int|0x31
comma
l_int|0x06
)brace
comma
(brace
id|XFER_UDMA_4
comma
l_int|0x31
comma
l_int|0x05
)brace
comma
(brace
id|XFER_UDMA_3
comma
l_int|0x31
comma
l_int|0x04
)brace
comma
(brace
id|XFER_UDMA_2
comma
l_int|0x31
comma
l_int|0x03
)brace
comma
(brace
id|XFER_UDMA_1
comma
l_int|0x31
comma
l_int|0x02
)brace
comma
(brace
id|XFER_UDMA_0
comma
l_int|0x31
comma
l_int|0x01
)brace
comma
(brace
id|XFER_MW_DMA_2
comma
l_int|0x31
comma
l_int|0x00
)brace
comma
(brace
id|XFER_MW_DMA_1
comma
l_int|0x31
comma
l_int|0x00
)brace
comma
(brace
id|XFER_MW_DMA_0
comma
l_int|0x0a
comma
l_int|0x00
)brace
comma
macro_line|#endif /* CONFIG_BLK_DEV_IDEDMA */
(brace
id|XFER_PIO_4
comma
l_int|0x31
comma
l_int|0x00
)brace
comma
(brace
id|XFER_PIO_3
comma
l_int|0x33
comma
l_int|0x00
)brace
comma
(brace
id|XFER_PIO_2
comma
l_int|0x08
comma
l_int|0x00
)brace
comma
(brace
id|XFER_PIO_1
comma
l_int|0x0a
comma
l_int|0x00
)brace
comma
(brace
id|XFER_PIO_0
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
(brace
l_int|0
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
suffix:semicolon
DECL|variable|aec6xxx_34_base
r_struct
id|chipset_bus_clock_list_entry
id|aec6xxx_34_base
(braket
)braket
op_assign
(brace
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA
(brace
id|XFER_UDMA_6
comma
l_int|0x41
comma
l_int|0x06
)brace
comma
(brace
id|XFER_UDMA_5
comma
l_int|0x41
comma
l_int|0x05
)brace
comma
(brace
id|XFER_UDMA_4
comma
l_int|0x41
comma
l_int|0x04
)brace
comma
(brace
id|XFER_UDMA_3
comma
l_int|0x41
comma
l_int|0x03
)brace
comma
(brace
id|XFER_UDMA_2
comma
l_int|0x41
comma
l_int|0x02
)brace
comma
(brace
id|XFER_UDMA_1
comma
l_int|0x41
comma
l_int|0x01
)brace
comma
(brace
id|XFER_UDMA_0
comma
l_int|0x41
comma
l_int|0x01
)brace
comma
(brace
id|XFER_MW_DMA_2
comma
l_int|0x41
comma
l_int|0x00
)brace
comma
(brace
id|XFER_MW_DMA_1
comma
l_int|0x42
comma
l_int|0x00
)brace
comma
(brace
id|XFER_MW_DMA_0
comma
l_int|0x7a
comma
l_int|0x00
)brace
comma
macro_line|#endif /* CONFIG_BLK_DEV_IDEDMA */
(brace
id|XFER_PIO_4
comma
l_int|0x41
comma
l_int|0x00
)brace
comma
(brace
id|XFER_PIO_3
comma
l_int|0x43
comma
l_int|0x00
)brace
comma
(brace
id|XFER_PIO_2
comma
l_int|0x78
comma
l_int|0x00
)brace
comma
(brace
id|XFER_PIO_1
comma
l_int|0x7a
comma
l_int|0x00
)brace
comma
(brace
id|XFER_PIO_0
comma
l_int|0x70
comma
l_int|0x00
)brace
comma
(brace
l_int|0
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
suffix:semicolon
macro_line|#ifndef HIGH_4
DECL|macro|HIGH_4
mdefine_line|#define HIGH_4(H)&t;&t;((H)=(H&gt;&gt;4))
macro_line|#endif
macro_line|#ifndef LOW_4
DECL|macro|LOW_4
mdefine_line|#define LOW_4(L)&t;&t;((L)=(L-((L&gt;&gt;4)&lt;&lt;4)))
macro_line|#endif
macro_line|#ifndef SPLIT_BYTE
DECL|macro|SPLIT_BYTE
mdefine_line|#define SPLIT_BYTE(B,H,L)&t;((H)=(B&gt;&gt;4), (L)=(B-((B&gt;&gt;4)&lt;&lt;4)))
macro_line|#endif
macro_line|#ifndef MAKE_WORD
DECL|macro|MAKE_WORD
mdefine_line|#define MAKE_WORD(W,HB,LB)&t;((W)=((HB&lt;&lt;8)+LB))
macro_line|#endif
DECL|macro|BUSCLOCK
mdefine_line|#define BUSCLOCK(D)&t;&bslash;&n;&t;((struct chipset_bus_clock_list_entry *) pci_get_drvdata((D)))
macro_line|#if defined(DISPLAY_AEC62XX_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS)
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
DECL|variable|aec62xx_proc
r_static
id|u8
id|aec62xx_proc
suffix:semicolon
r_static
r_int
id|aec62xx_get_info
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
id|aec62xx_procs
(braket
)braket
id|__initdata
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;aec62xx&quot;
comma
dot
id|set
op_assign
l_int|1
comma
dot
id|get_info
op_assign
id|aec62xx_get_info
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
macro_line|#endif /* DISPLAY_AEC62XX_TIMINGS &amp;&amp; CONFIG_PROC_FS */
r_static
r_void
id|init_setup_aec6x80
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
r_void
id|init_setup_aec62xx
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
id|init_chipset_aec62xx
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
id|init_hwif_aec62xx
c_func
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
r_static
r_void
id|init_dma_aec62xx
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
id|aec62xx_chipsets
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
id|PCI_VENDOR_ID_ARTOP
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_ARTOP_ATP850UF
comma
dot
id|name
op_assign
l_string|&quot;AEC6210&quot;
comma
dot
id|init_setup
op_assign
id|init_setup_aec62xx
comma
dot
id|init_chipset
op_assign
id|init_chipset_aec62xx
comma
dot
id|init_iops
op_assign
l_int|NULL
comma
dot
id|init_hwif
op_assign
id|init_hwif_aec62xx
comma
dot
id|init_dma
op_assign
id|init_dma_aec62xx
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
dot
id|bootable
op_assign
id|OFF_BOARD
comma
dot
id|extra
op_assign
l_int|0
comma
)brace
comma
(brace
multiline_comment|/* 1 */
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_ARTOP
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_ARTOP_ATP860
comma
dot
id|name
op_assign
l_string|&quot;AEC6260&quot;
comma
dot
id|init_setup
op_assign
id|init_setup_aec62xx
comma
dot
id|init_chipset
op_assign
id|init_chipset_aec62xx
comma
dot
id|init_iops
op_assign
l_int|NULL
comma
dot
id|init_hwif
op_assign
id|init_hwif_aec62xx
comma
dot
id|init_dma
op_assign
id|init_dma_aec62xx
comma
dot
id|channels
op_assign
l_int|2
comma
dot
id|autodma
op_assign
id|NOAUTODMA
comma
dot
id|enablebits
op_assign
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
dot
id|bootable
op_assign
id|OFF_BOARD
comma
dot
id|extra
op_assign
l_int|0
comma
)brace
comma
(brace
multiline_comment|/* 2 */
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_ARTOP
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_ARTOP_ATP860R
comma
dot
id|name
op_assign
l_string|&quot;AEC6260R&quot;
comma
dot
id|init_setup
op_assign
id|init_setup_aec62xx
comma
dot
id|init_chipset
op_assign
id|init_chipset_aec62xx
comma
dot
id|init_iops
op_assign
l_int|NULL
comma
dot
id|init_hwif
op_assign
id|init_hwif_aec62xx
comma
dot
id|init_dma
op_assign
id|init_dma_aec62xx
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
dot
id|bootable
op_assign
id|NEVER_BOARD
comma
dot
id|extra
op_assign
l_int|0
comma
)brace
comma
(brace
multiline_comment|/* 3 */
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_ARTOP
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_ARTOP_ATP865
comma
dot
id|name
op_assign
l_string|&quot;AEC6X80&quot;
comma
dot
id|init_setup
op_assign
id|init_setup_aec6x80
comma
dot
id|init_chipset
op_assign
id|init_chipset_aec62xx
comma
dot
id|init_iops
op_assign
l_int|NULL
comma
dot
id|init_hwif
op_assign
id|init_hwif_aec62xx
comma
dot
id|init_dma
op_assign
id|init_dma_aec62xx
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
dot
id|bootable
op_assign
id|OFF_BOARD
comma
dot
id|extra
op_assign
l_int|0
comma
)brace
comma
(brace
multiline_comment|/* 4 */
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_ARTOP
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_ARTOP_ATP865R
comma
dot
id|name
op_assign
l_string|&quot;AEC6X80R&quot;
comma
dot
id|init_setup
op_assign
id|init_setup_aec6x80
comma
dot
id|init_chipset
op_assign
id|init_chipset_aec62xx
comma
dot
id|init_iops
op_assign
l_int|NULL
comma
dot
id|init_hwif
op_assign
id|init_hwif_aec62xx
comma
dot
id|init_dma
op_assign
id|init_dma_aec62xx
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
dot
id|bootable
op_assign
id|OFF_BOARD
comma
dot
id|extra
op_assign
l_int|0
comma
)brace
)brace
suffix:semicolon
macro_line|#endif /* AEC62XX_H */
eof
