multiline_comment|/*&n; * cirrus.h 1.4 1999/10/25 20:03:34&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License. &n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dhinds@pcmcia.sourceforge.org&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU Public License version 2 (the &quot;GPL&quot;), in which&n; * case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use&n; * your version of this file under the MPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the MPL or the GPL.&n; */
macro_line|#ifndef _LINUX_CIRRUS_H
DECL|macro|_LINUX_CIRRUS_H
mdefine_line|#define _LINUX_CIRRUS_H
macro_line|#ifndef PCI_VENDOR_ID_CIRRUS
DECL|macro|PCI_VENDOR_ID_CIRRUS
mdefine_line|#define PCI_VENDOR_ID_CIRRUS&t;&t;0x1013
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_CIRRUS_6729
DECL|macro|PCI_DEVICE_ID_CIRRUS_6729
mdefine_line|#define PCI_DEVICE_ID_CIRRUS_6729&t;0x1100
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_CIRRUS_6832
DECL|macro|PCI_DEVICE_ID_CIRRUS_6832
mdefine_line|#define PCI_DEVICE_ID_CIRRUS_6832&t;0x1110
macro_line|#endif
DECL|macro|PD67_MISC_CTL_1
mdefine_line|#define PD67_MISC_CTL_1&t;&t;0x16&t;/* Misc control 1 */
DECL|macro|PD67_FIFO_CTL
mdefine_line|#define PD67_FIFO_CTL&t;&t;0x17&t;/* FIFO control */
DECL|macro|PD67_MISC_CTL_2
mdefine_line|#define PD67_MISC_CTL_2&t;&t;0x1E&t;/* Misc control 2 */
DECL|macro|PD67_CHIP_INFO
mdefine_line|#define PD67_CHIP_INFO&t;&t;0x1f&t;/* Chip information */
DECL|macro|PD67_ATA_CTL
mdefine_line|#define PD67_ATA_CTL&t;&t;0x026&t;/* 6730: ATA control */
DECL|macro|PD67_EXT_INDEX
mdefine_line|#define PD67_EXT_INDEX&t;&t;0x2e&t;/* Extension index */
DECL|macro|PD67_EXT_DATA
mdefine_line|#define PD67_EXT_DATA&t;&t;0x2f&t;/* Extension data */
multiline_comment|/* PD6722 extension registers -- indexed in PD67_EXT_INDEX */
DECL|macro|PD67_DATA_MASK0
mdefine_line|#define PD67_DATA_MASK0&t;&t;0x01&t;/* Data mask 0 */
DECL|macro|PD67_DATA_MASK1
mdefine_line|#define PD67_DATA_MASK1&t;&t;0x02&t;/* Data mask 1 */
DECL|macro|PD67_DMA_CTL
mdefine_line|#define PD67_DMA_CTL&t;&t;0x03&t;/* DMA control */
multiline_comment|/* PD6730 extension registers -- indexed in PD67_EXT_INDEX */
DECL|macro|PD67_EXT_CTL_1
mdefine_line|#define PD67_EXT_CTL_1&t;&t;0x03&t;/* Extension control 1 */
DECL|macro|PD67_MEM_PAGE
mdefine_line|#define PD67_MEM_PAGE(n)&t;((n)+5)&t;/* PCI window bits 31:24 */
DECL|macro|PD67_EXTERN_DATA
mdefine_line|#define PD67_EXTERN_DATA&t;0x0a
DECL|macro|PD67_MISC_CTL_3
mdefine_line|#define PD67_MISC_CTL_3&t;&t;0x25
DECL|macro|PD67_SMB_PWR_CTL
mdefine_line|#define PD67_SMB_PWR_CTL&t;0x26
multiline_comment|/* I/O window address offset */
DECL|macro|PD67_IO_OFF
mdefine_line|#define PD67_IO_OFF(w)&t;&t;(0x36+((w)&lt;&lt;1))
multiline_comment|/* Timing register sets */
DECL|macro|PD67_TIME_SETUP
mdefine_line|#define PD67_TIME_SETUP(n)&t;(0x3a + 3*(n))
DECL|macro|PD67_TIME_CMD
mdefine_line|#define PD67_TIME_CMD(n)&t;(0x3b + 3*(n))
DECL|macro|PD67_TIME_RECOV
mdefine_line|#define PD67_TIME_RECOV(n)&t;(0x3c + 3*(n))
multiline_comment|/* Flags for PD67_MISC_CTL_1 */
DECL|macro|PD67_MC1_5V_DET
mdefine_line|#define PD67_MC1_5V_DET&t;&t;0x01&t;/* 5v detect */
DECL|macro|PD67_MC1_MEDIA_ENA
mdefine_line|#define PD67_MC1_MEDIA_ENA&t;0x01&t;/* 6730: Multimedia enable */
DECL|macro|PD67_MC1_VCC_3V
mdefine_line|#define PD67_MC1_VCC_3V&t;&t;0x02&t;/* 3.3v Vcc */
DECL|macro|PD67_MC1_PULSE_MGMT
mdefine_line|#define PD67_MC1_PULSE_MGMT&t;0x04
DECL|macro|PD67_MC1_PULSE_IRQ
mdefine_line|#define PD67_MC1_PULSE_IRQ&t;0x08
DECL|macro|PD67_MC1_SPKR_ENA
mdefine_line|#define PD67_MC1_SPKR_ENA&t;0x10
DECL|macro|PD67_MC1_INPACK_ENA
mdefine_line|#define PD67_MC1_INPACK_ENA&t;0x80
multiline_comment|/* Flags for PD67_FIFO_CTL */
DECL|macro|PD67_FIFO_EMPTY
mdefine_line|#define PD67_FIFO_EMPTY&t;&t;0x80
multiline_comment|/* Flags for PD67_MISC_CTL_2 */
DECL|macro|PD67_MC2_FREQ_BYPASS
mdefine_line|#define PD67_MC2_FREQ_BYPASS&t;0x01
DECL|macro|PD67_MC2_DYNAMIC_MODE
mdefine_line|#define PD67_MC2_DYNAMIC_MODE&t;0x02
DECL|macro|PD67_MC2_SUSPEND
mdefine_line|#define PD67_MC2_SUSPEND&t;0x04
DECL|macro|PD67_MC2_5V_CORE
mdefine_line|#define PD67_MC2_5V_CORE&t;0x08
DECL|macro|PD67_MC2_LED_ENA
mdefine_line|#define PD67_MC2_LED_ENA&t;0x10&t;/* IRQ 12 is LED enable */
DECL|macro|PD67_MC2_FAST_PCI
mdefine_line|#define PD67_MC2_FAST_PCI&t;0x10&t;/* 6729: PCI bus &gt; 25 MHz */
DECL|macro|PD67_MC2_3STATE_BIT7
mdefine_line|#define PD67_MC2_3STATE_BIT7&t;0x20&t;/* Floppy change bit */
DECL|macro|PD67_MC2_DMA_MODE
mdefine_line|#define PD67_MC2_DMA_MODE&t;0x40
DECL|macro|PD67_MC2_IRQ15_RI
mdefine_line|#define PD67_MC2_IRQ15_RI&t;0x80&t;/* IRQ 15 is ring enable */
multiline_comment|/* Flags for PD67_CHIP_INFO */
DECL|macro|PD67_INFO_SLOTS
mdefine_line|#define PD67_INFO_SLOTS&t;&t;0x20&t;/* 0 = 1 slot, 1 = 2 slots */
DECL|macro|PD67_INFO_CHIP_ID
mdefine_line|#define PD67_INFO_CHIP_ID&t;0xc0
DECL|macro|PD67_INFO_REV
mdefine_line|#define PD67_INFO_REV&t;&t;0x1c
multiline_comment|/* Fields in PD67_TIME_* registers */
DECL|macro|PD67_TIME_SCALE
mdefine_line|#define PD67_TIME_SCALE&t;&t;0xc0
DECL|macro|PD67_TIME_SCALE_1
mdefine_line|#define PD67_TIME_SCALE_1&t;0x00
DECL|macro|PD67_TIME_SCALE_16
mdefine_line|#define PD67_TIME_SCALE_16&t;0x40
DECL|macro|PD67_TIME_SCALE_256
mdefine_line|#define PD67_TIME_SCALE_256&t;0x80
DECL|macro|PD67_TIME_SCALE_4096
mdefine_line|#define PD67_TIME_SCALE_4096&t;0xc0
DECL|macro|PD67_TIME_MULT
mdefine_line|#define PD67_TIME_MULT&t;&t;0x3f
multiline_comment|/* Fields in PD67_DMA_CTL */
DECL|macro|PD67_DMA_MODE
mdefine_line|#define PD67_DMA_MODE&t;&t;0xc0
DECL|macro|PD67_DMA_OFF
mdefine_line|#define PD67_DMA_OFF&t;&t;0x00
DECL|macro|PD67_DMA_DREQ_INPACK
mdefine_line|#define PD67_DMA_DREQ_INPACK&t;0x40
DECL|macro|PD67_DMA_DREQ_WP
mdefine_line|#define PD67_DMA_DREQ_WP&t;0x80
DECL|macro|PD67_DMA_DREQ_BVD2
mdefine_line|#define PD67_DMA_DREQ_BVD2&t;0xc0
DECL|macro|PD67_DMA_PULLUP
mdefine_line|#define PD67_DMA_PULLUP&t;&t;0x20&t;/* Disable socket pullups? */
multiline_comment|/* Fields in PD67_EXT_CTL_1 */
DECL|macro|PD67_EC1_VCC_PWR_LOCK
mdefine_line|#define PD67_EC1_VCC_PWR_LOCK&t;0x01
DECL|macro|PD67_EC1_AUTO_PWR_CLEAR
mdefine_line|#define PD67_EC1_AUTO_PWR_CLEAR&t;0x02
DECL|macro|PD67_EC1_LED_ENA
mdefine_line|#define PD67_EC1_LED_ENA&t;0x04
DECL|macro|PD67_EC1_INV_CARD_IRQ
mdefine_line|#define PD67_EC1_INV_CARD_IRQ&t;0x08
DECL|macro|PD67_EC1_INV_MGMT_IRQ
mdefine_line|#define PD67_EC1_INV_MGMT_IRQ&t;0x10
DECL|macro|PD67_EC1_PULLUP_CTL
mdefine_line|#define PD67_EC1_PULLUP_CTL&t;0x20
multiline_comment|/* Fields in PD67_MISC_CTL_3 */
DECL|macro|PD67_MC3_IRQ_MASK
mdefine_line|#define PD67_MC3_IRQ_MASK&t;0x03
DECL|macro|PD67_MC3_IRQ_PCPCI
mdefine_line|#define PD67_MC3_IRQ_PCPCI&t;0x00
DECL|macro|PD67_MC3_IRQ_EXTERN
mdefine_line|#define PD67_MC3_IRQ_EXTERN&t;0x01
DECL|macro|PD67_MC3_IRQ_PCIWAY
mdefine_line|#define PD67_MC3_IRQ_PCIWAY&t;0x02
DECL|macro|PD67_MC3_IRQ_PCI
mdefine_line|#define PD67_MC3_IRQ_PCI&t;0x03
DECL|macro|PD67_MC3_PWR_MASK
mdefine_line|#define PD67_MC3_PWR_MASK&t;0x0c
DECL|macro|PD67_MC3_PWR_SERIAL
mdefine_line|#define PD67_MC3_PWR_SERIAL&t;0x00
DECL|macro|PD67_MC3_PWR_TI2202
mdefine_line|#define PD67_MC3_PWR_TI2202&t;0x08
DECL|macro|PD67_MC3_PWR_SMB
mdefine_line|#define PD67_MC3_PWR_SMB&t;0x0c
multiline_comment|/* Register definitions for Cirrus PD6832 PCI-to-CardBus bridge */
multiline_comment|/* PD6832 extension registers -- indexed in PD67_EXT_INDEX */
DECL|macro|PD68_EXT_CTL_2
mdefine_line|#define PD68_EXT_CTL_2&t;&t;&t;0x0b
DECL|macro|PD68_PCI_SPACE
mdefine_line|#define PD68_PCI_SPACE&t;&t;&t;0x22
DECL|macro|PD68_PCCARD_SPACE
mdefine_line|#define PD68_PCCARD_SPACE&t;&t;0x23
DECL|macro|PD68_WINDOW_TYPE
mdefine_line|#define PD68_WINDOW_TYPE&t;&t;0x24
DECL|macro|PD68_EXT_CSC
mdefine_line|#define PD68_EXT_CSC&t;&t;&t;0x2e
DECL|macro|PD68_MISC_CTL_4
mdefine_line|#define PD68_MISC_CTL_4&t;&t;&t;0x2f
DECL|macro|PD68_MISC_CTL_5
mdefine_line|#define PD68_MISC_CTL_5&t;&t;&t;0x30
DECL|macro|PD68_MISC_CTL_6
mdefine_line|#define PD68_MISC_CTL_6&t;&t;&t;0x31
multiline_comment|/* Extra flags in PD67_MISC_CTL_3 */
DECL|macro|PD68_MC3_HW_SUSP
mdefine_line|#define PD68_MC3_HW_SUSP&t;&t;0x10
DECL|macro|PD68_MC3_MM_EXPAND
mdefine_line|#define PD68_MC3_MM_EXPAND&t;&t;0x40
DECL|macro|PD68_MC3_MM_ARM
mdefine_line|#define PD68_MC3_MM_ARM&t;&t;&t;0x80
multiline_comment|/* Bridge Control Register */
DECL|macro|PD6832_BCR_MGMT_IRQ_ENA
mdefine_line|#define  PD6832_BCR_MGMT_IRQ_ENA&t;0x0800
multiline_comment|/* Socket Number Register */
DECL|macro|PD6832_SOCKET_NUMBER
mdefine_line|#define PD6832_SOCKET_NUMBER&t;&t;0x004c&t;/* 8 bit */
macro_line|#endif /* _LINUX_CIRRUS_H */
eof
