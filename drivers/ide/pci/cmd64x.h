macro_line|#ifndef CMD64X_H
DECL|macro|CMD64X_H
mdefine_line|#define CMD64X_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
DECL|macro|DISPLAY_CMD64X_TIMINGS
mdefine_line|#define DISPLAY_CMD64X_TIMINGS
DECL|macro|CMD_DEBUG
mdefine_line|#define CMD_DEBUG 0
macro_line|#if CMD_DEBUG
DECL|macro|cmdprintk
mdefine_line|#define cmdprintk(x...)&t;printk(x)
macro_line|#else
DECL|macro|cmdprintk
mdefine_line|#define cmdprintk(x...)
macro_line|#endif
multiline_comment|/*&n; * CMD64x specific registers definition.&n; */
DECL|macro|CFR
mdefine_line|#define CFR&t;&t;0x50
DECL|macro|CFR_INTR_CH0
mdefine_line|#define   CFR_INTR_CH0&t;&t;0x02
DECL|macro|CNTRL
mdefine_line|#define CNTRL&t;&t;0x51
DECL|macro|CNTRL_DIS_RA0
mdefine_line|#define&t;  CNTRL_DIS_RA0&t;&t;0x40
DECL|macro|CNTRL_DIS_RA1
mdefine_line|#define   CNTRL_DIS_RA1&t;&t;0x80
DECL|macro|CNTRL_ENA_2ND
mdefine_line|#define&t;  CNTRL_ENA_2ND&t;&t;0x08
DECL|macro|CMDTIM
mdefine_line|#define&t;CMDTIM&t;&t;0x52
DECL|macro|ARTTIM0
mdefine_line|#define&t;ARTTIM0&t;&t;0x53
DECL|macro|DRWTIM0
mdefine_line|#define&t;DRWTIM0&t;&t;0x54
DECL|macro|ARTTIM1
mdefine_line|#define ARTTIM1 &t;0x55
DECL|macro|DRWTIM1
mdefine_line|#define DRWTIM1&t;&t;0x56
DECL|macro|ARTTIM23
mdefine_line|#define ARTTIM23&t;0x57
DECL|macro|ARTTIM23_DIS_RA2
mdefine_line|#define   ARTTIM23_DIS_RA2&t;0x04
DECL|macro|ARTTIM23_DIS_RA3
mdefine_line|#define   ARTTIM23_DIS_RA3&t;0x08
DECL|macro|ARTTIM23_INTR_CH1
mdefine_line|#define   ARTTIM23_INTR_CH1&t;0x10
DECL|macro|ARTTIM2
mdefine_line|#define ARTTIM2&t;&t;0x57
DECL|macro|ARTTIM3
mdefine_line|#define ARTTIM3&t;&t;0x57
DECL|macro|DRWTIM23
mdefine_line|#define DRWTIM23&t;0x58
DECL|macro|DRWTIM2
mdefine_line|#define DRWTIM2&t;&t;0x58
DECL|macro|BRST
mdefine_line|#define BRST&t;&t;0x59
DECL|macro|DRWTIM3
mdefine_line|#define DRWTIM3&t;&t;0x5b
DECL|macro|BMIDECR0
mdefine_line|#define BMIDECR0&t;0x70
DECL|macro|MRDMODE
mdefine_line|#define MRDMODE&t;&t;0x71
DECL|macro|MRDMODE_INTR_CH0
mdefine_line|#define   MRDMODE_INTR_CH0&t;0x04
DECL|macro|MRDMODE_INTR_CH1
mdefine_line|#define   MRDMODE_INTR_CH1&t;0x08
DECL|macro|MRDMODE_BLK_CH0
mdefine_line|#define   MRDMODE_BLK_CH0&t;0x10
DECL|macro|MRDMODE_BLK_CH1
mdefine_line|#define   MRDMODE_BLK_CH1&t;0x20
DECL|macro|BMIDESR0
mdefine_line|#define BMIDESR0&t;0x72
DECL|macro|UDIDETCR0
mdefine_line|#define UDIDETCR0&t;0x73
DECL|macro|DTPR0
mdefine_line|#define DTPR0&t;&t;0x74
DECL|macro|BMIDECR1
mdefine_line|#define BMIDECR1&t;0x78
DECL|macro|BMIDECSR
mdefine_line|#define BMIDECSR&t;0x79
DECL|macro|BMIDESR1
mdefine_line|#define BMIDESR1&t;0x7A
DECL|macro|UDIDETCR1
mdefine_line|#define UDIDETCR1&t;0x7B
DECL|macro|DTPR1
mdefine_line|#define DTPR1&t;&t;0x7C
r_static
r_int
r_int
id|init_chipset_cmd64x
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
id|init_hwif_cmd64x
c_func
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
DECL|variable|__devinitdata
r_static
id|ide_pci_device_t
id|cmd64x_chipsets
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
l_string|&quot;CMD643&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_cmd64x
comma
dot
id|init_hwif
op_assign
id|init_hwif_cmd64x
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
id|bootable
op_assign
id|ON_BOARD
comma
)brace
comma
(brace
multiline_comment|/* 1 */
dot
id|name
op_assign
l_string|&quot;CMD646&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_cmd64x
comma
dot
id|init_hwif
op_assign
id|init_hwif_cmd64x
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
l_int|0x51
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
(brace
multiline_comment|/* 2 */
dot
id|name
op_assign
l_string|&quot;CMD648&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_cmd64x
comma
dot
id|init_hwif
op_assign
id|init_hwif_cmd64x
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
id|bootable
op_assign
id|ON_BOARD
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;CMD649&quot;
comma
dot
id|init_chipset
op_assign
id|init_chipset_cmd64x
comma
dot
id|init_hwif
op_assign
id|init_hwif_cmd64x
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
id|bootable
op_assign
id|ON_BOARD
comma
)brace
)brace
suffix:semicolon
macro_line|#endif /* CMD64X_H */
eof
