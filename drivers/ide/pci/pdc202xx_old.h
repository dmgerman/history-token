macro_line|#ifndef PDC202XX_H
DECL|macro|PDC202XX_H
mdefine_line|#define PDC202XX_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#ifndef SPLIT_BYTE
DECL|macro|SPLIT_BYTE
mdefine_line|#define SPLIT_BYTE(B,H,L)&t;((H)=(B&gt;&gt;4), (L)=(B-((B&gt;&gt;4)&lt;&lt;4)))
macro_line|#endif
DECL|macro|PDC202XX_DEBUG_DRIVE_INFO
mdefine_line|#define PDC202XX_DEBUG_DRIVE_INFO&t;&t;0
DECL|variable|pdc_quirk_drives
r_static
r_const
r_char
op_star
id|pdc_quirk_drives
(braket
)braket
op_assign
(brace
l_string|&quot;QUANTUM FIREBALLlct08 08&quot;
comma
l_string|&quot;QUANTUM FIREBALLP KA6.4&quot;
comma
l_string|&quot;QUANTUM FIREBALLP KA9.1&quot;
comma
l_string|&quot;QUANTUM FIREBALLP LM20.4&quot;
comma
l_string|&quot;QUANTUM FIREBALLP KX13.6&quot;
comma
l_string|&quot;QUANTUM FIREBALLP KX20.5&quot;
comma
l_string|&quot;QUANTUM FIREBALLP KX27.3&quot;
comma
l_string|&quot;QUANTUM FIREBALLP LM20.5&quot;
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/* A Register */
DECL|macro|SYNC_ERRDY_EN
mdefine_line|#define&t;SYNC_ERRDY_EN&t;0xC0
DECL|macro|SYNC_IN
mdefine_line|#define&t;SYNC_IN&t;&t;0x80&t;/* control bit, different for master vs. slave drives */
DECL|macro|ERRDY_EN
mdefine_line|#define&t;ERRDY_EN&t;0x40&t;/* control bit, different for master vs. slave drives */
DECL|macro|IORDY_EN
mdefine_line|#define&t;IORDY_EN&t;0x20&t;/* PIO: IOREADY */
DECL|macro|PREFETCH_EN
mdefine_line|#define&t;PREFETCH_EN&t;0x10&t;/* PIO: PREFETCH */
DECL|macro|PA3
mdefine_line|#define&t;PA3&t;&t;0x08&t;/* PIO&quot;A&quot; timing */
DECL|macro|PA2
mdefine_line|#define&t;PA2&t;&t;0x04&t;/* PIO&quot;A&quot; timing */
DECL|macro|PA1
mdefine_line|#define&t;PA1&t;&t;0x02&t;/* PIO&quot;A&quot; timing */
DECL|macro|PA0
mdefine_line|#define&t;PA0&t;&t;0x01&t;/* PIO&quot;A&quot; timing */
multiline_comment|/* B Register */
DECL|macro|MB2
mdefine_line|#define&t;MB2&t;&t;0x80&t;/* DMA&quot;B&quot; timing */
DECL|macro|MB1
mdefine_line|#define&t;MB1&t;&t;0x40&t;/* DMA&quot;B&quot; timing */
DECL|macro|MB0
mdefine_line|#define&t;MB0&t;&t;0x20&t;/* DMA&quot;B&quot; timing */
DECL|macro|PB4
mdefine_line|#define&t;PB4&t;&t;0x10&t;/* PIO_FORCE 1:0 */
DECL|macro|PB3
mdefine_line|#define&t;PB3&t;&t;0x08&t;/* PIO&quot;B&quot; timing */&t;/* PIO flow Control mode */
DECL|macro|PB2
mdefine_line|#define&t;PB2&t;&t;0x04&t;/* PIO&quot;B&quot; timing */&t;/* PIO 4 */
DECL|macro|PB1
mdefine_line|#define&t;PB1&t;&t;0x02&t;/* PIO&quot;B&quot; timing */&t;/* PIO 3 half */
DECL|macro|PB0
mdefine_line|#define&t;PB0&t;&t;0x01&t;/* PIO&quot;B&quot; timing */&t;/* PIO 3 other half */
multiline_comment|/* C Register */
DECL|macro|IORDYp_NO_SPEED
mdefine_line|#define&t;IORDYp_NO_SPEED&t;0x4F
DECL|macro|SPEED_DIS
mdefine_line|#define&t;SPEED_DIS&t;0x0F
DECL|macro|DMARQp
mdefine_line|#define&t;DMARQp&t;&t;0x80
DECL|macro|IORDYp
mdefine_line|#define&t;IORDYp&t;&t;0x40
DECL|macro|DMAR_EN
mdefine_line|#define&t;DMAR_EN&t;&t;0x20
DECL|macro|DMAW_EN
mdefine_line|#define&t;DMAW_EN&t;&t;0x10
DECL|macro|MC3
mdefine_line|#define&t;MC3&t;&t;0x08&t;/* DMA&quot;C&quot; timing */
DECL|macro|MC2
mdefine_line|#define&t;MC2&t;&t;0x04&t;/* DMA&quot;C&quot; timing */
DECL|macro|MC1
mdefine_line|#define&t;MC1&t;&t;0x02&t;/* DMA&quot;C&quot; timing */
DECL|macro|MC0
mdefine_line|#define&t;MC0&t;&t;0x01&t;/* DMA&quot;C&quot; timing */
r_static
r_int
id|init_setup_pdc202ata4
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|ide_pci_device_t
op_star
id|d
)paren
suffix:semicolon
r_static
r_int
id|init_setup_pdc20265
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
id|init_setup_pdc202xx
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
id|init_chipset_pdc202xx
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
id|init_hwif_pdc202xx
c_func
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
r_static
r_void
id|init_dma_pdc202xx
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
id|pdc202xx_chipsets
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
multiline_comment|/* 0 */
dot
id|name
op_assign
l_string|&quot;PDC20246&quot;
comma
dot
id|init_setup
op_assign
id|init_setup_pdc202ata4
comma
dot
id|init_chipset
op_assign
id|init_chipset_pdc202xx
comma
dot
id|init_hwif
op_assign
id|init_hwif_pdc202xx
comma
dot
id|init_dma
op_assign
id|init_dma_pdc202xx
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
macro_line|#ifndef CONFIG_PDC202XX_FORCE
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
l_int|0x04
comma
l_int|0x04
)brace
)brace
comma
macro_line|#endif
dot
id|bootable
op_assign
id|OFF_BOARD
comma
dot
id|extra
op_assign
l_int|16
comma
)brace
comma
(brace
multiline_comment|/* 1 */
dot
id|name
op_assign
l_string|&quot;PDC20262&quot;
comma
dot
id|init_setup
op_assign
id|init_setup_pdc202ata4
comma
dot
id|init_chipset
op_assign
id|init_chipset_pdc202xx
comma
dot
id|init_hwif
op_assign
id|init_hwif_pdc202xx
comma
dot
id|init_dma
op_assign
id|init_dma_pdc202xx
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
macro_line|#ifndef CONFIG_PDC202XX_FORCE
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
l_int|0x04
comma
l_int|0x04
)brace
)brace
comma
macro_line|#endif
dot
id|bootable
op_assign
id|OFF_BOARD
comma
dot
id|extra
op_assign
l_int|48
comma
dot
id|flags
op_assign
id|IDEPCI_FLAG_FORCE_PDC
comma
)brace
comma
(brace
multiline_comment|/* 2 */
dot
id|name
op_assign
l_string|&quot;PDC20263&quot;
comma
dot
id|init_setup
op_assign
id|init_setup_pdc202ata4
comma
dot
id|init_chipset
op_assign
id|init_chipset_pdc202xx
comma
dot
id|init_hwif
op_assign
id|init_hwif_pdc202xx
comma
dot
id|init_dma
op_assign
id|init_dma_pdc202xx
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
macro_line|#ifndef CONFIG_PDC202XX_FORCE
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
l_int|0x04
comma
l_int|0x04
)brace
)brace
comma
macro_line|#endif
dot
id|bootable
op_assign
id|OFF_BOARD
comma
dot
id|extra
op_assign
l_int|48
comma
)brace
comma
(brace
multiline_comment|/* 3 */
dot
id|name
op_assign
l_string|&quot;PDC20265&quot;
comma
dot
id|init_setup
op_assign
id|init_setup_pdc20265
comma
dot
id|init_chipset
op_assign
id|init_chipset_pdc202xx
comma
dot
id|init_hwif
op_assign
id|init_hwif_pdc202xx
comma
dot
id|init_dma
op_assign
id|init_dma_pdc202xx
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
macro_line|#ifndef CONFIG_PDC202XX_FORCE
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
l_int|0x04
comma
l_int|0x04
)brace
)brace
comma
macro_line|#endif
dot
id|bootable
op_assign
id|OFF_BOARD
comma
dot
id|extra
op_assign
l_int|48
comma
dot
id|flags
op_assign
id|IDEPCI_FLAG_FORCE_PDC
comma
)brace
comma
(brace
multiline_comment|/* 4 */
dot
id|name
op_assign
l_string|&quot;PDC20267&quot;
comma
dot
id|init_setup
op_assign
id|init_setup_pdc202xx
comma
dot
id|init_chipset
op_assign
id|init_chipset_pdc202xx
comma
dot
id|init_hwif
op_assign
id|init_hwif_pdc202xx
comma
dot
id|init_dma
op_assign
id|init_dma_pdc202xx
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
macro_line|#ifndef CONFIG_PDC202XX_FORCE
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
l_int|0x04
comma
l_int|0x04
)brace
)brace
comma
macro_line|#endif
dot
id|bootable
op_assign
id|OFF_BOARD
comma
dot
id|extra
op_assign
l_int|48
comma
)brace
)brace
suffix:semicolon
macro_line|#endif /* PDC202XX_H */
eof
