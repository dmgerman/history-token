multiline_comment|/*&n; * include/asm-ppc/mpc52xx.h&n; * &n; * Prototypes, etc. for the Freescale MPC52xx embedded cpu chips&n; * May need to be cleaned as the port goes on ...&n; *&n; *&n; * Maintainer : Sylvain Munaut &lt;tnt@246tNt.com&gt;&n; *&n; * Originally written by Dale Farnsworth &lt;dfarnsworth@mvista.com&gt; &n; * for the 2.4 kernel.&n; *&n; * Copyright (C) 2004-2005 Sylvain Munaut &lt;tnt@246tNt.com&gt;&n; * Copyright (C) 2003 MontaVista, Software, Inc.&n; *&n; * This file is licensed under the terms of the GNU General Public License&n; * version 2. This program is licensed &quot;as is&quot; without any warranty of any&n; * kind, whether express or implied.&n; */
macro_line|#ifndef __ASM_MPC52xx_H__
DECL|macro|__ASM_MPC52xx_H__
mdefine_line|#define __ASM_MPC52xx_H__
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/ppcboot.h&gt;
macro_line|#include &lt;asm/types.h&gt;
r_struct
id|pt_regs
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* ======================================================================== */
multiline_comment|/* PPC Sys devices definition                                               */
multiline_comment|/* ======================================================================== */
DECL|enum|ppc_sys_devices
r_enum
id|ppc_sys_devices
(brace
DECL|enumerator|MPC52xx_MSCAN1
id|MPC52xx_MSCAN1
comma
DECL|enumerator|MPC52xx_MSCAN2
id|MPC52xx_MSCAN2
comma
DECL|enumerator|MPC52xx_SPI
id|MPC52xx_SPI
comma
DECL|enumerator|MPC52xx_USB
id|MPC52xx_USB
comma
DECL|enumerator|MPC52xx_BDLC
id|MPC52xx_BDLC
comma
DECL|enumerator|MPC52xx_PSC1
id|MPC52xx_PSC1
comma
DECL|enumerator|MPC52xx_PSC2
id|MPC52xx_PSC2
comma
DECL|enumerator|MPC52xx_PSC3
id|MPC52xx_PSC3
comma
DECL|enumerator|MPC52xx_PSC4
id|MPC52xx_PSC4
comma
DECL|enumerator|MPC52xx_PSC5
id|MPC52xx_PSC5
comma
DECL|enumerator|MPC52xx_PSC6
id|MPC52xx_PSC6
comma
DECL|enumerator|MPC52xx_FEC
id|MPC52xx_FEC
comma
DECL|enumerator|MPC52xx_ATA
id|MPC52xx_ATA
comma
DECL|enumerator|MPC52xx_I2C1
id|MPC52xx_I2C1
comma
DECL|enumerator|MPC52xx_I2C2
id|MPC52xx_I2C2
comma
)brace
suffix:semicolon
multiline_comment|/* ======================================================================== */
multiline_comment|/* Main registers/struct addresses                                          */
multiline_comment|/* ======================================================================== */
multiline_comment|/* MBAR position */
DECL|macro|MPC52xx_MBAR
mdefine_line|#define MPC52xx_MBAR&t;&t;0xf0000000&t;/* Phys address */
DECL|macro|MPC52xx_MBAR_VIRT
mdefine_line|#define MPC52xx_MBAR_VIRT&t;0xf0000000&t;/* Virt address */
DECL|macro|MPC52xx_MBAR_SIZE
mdefine_line|#define MPC52xx_MBAR_SIZE&t;0x00010000
DECL|macro|MPC52xx_PA
mdefine_line|#define MPC52xx_PA(x)&t;&t;((phys_addr_t)(MPC52xx_MBAR + (x)))
DECL|macro|MPC52xx_VA
mdefine_line|#define MPC52xx_VA(x)&t;&t;((void __iomem *)(MPC52xx_MBAR_VIRT + (x)))
multiline_comment|/* Registers zone offset/size  */
DECL|macro|MPC52xx_MMAP_CTL_OFFSET
mdefine_line|#define MPC52xx_MMAP_CTL_OFFSET&t;&t;0x0000
DECL|macro|MPC52xx_MMAP_CTL_SIZE
mdefine_line|#define MPC52xx_MMAP_CTL_SIZE&t;&t;0x068
DECL|macro|MPC52xx_SDRAM_OFFSET
mdefine_line|#define MPC52xx_SDRAM_OFFSET&t;&t;0x0100
DECL|macro|MPC52xx_SDRAM_SIZE
mdefine_line|#define MPC52xx_SDRAM_SIZE&t;&t;0x010
DECL|macro|MPC52xx_CDM_OFFSET
mdefine_line|#define MPC52xx_CDM_OFFSET&t;&t;0x0200
DECL|macro|MPC52xx_CDM_SIZE
mdefine_line|#define MPC52xx_CDM_SIZE&t;&t;0x038
DECL|macro|MPC52xx_INTR_OFFSET
mdefine_line|#define MPC52xx_INTR_OFFSET&t;&t;0x0500
DECL|macro|MPC52xx_INTR_SIZE
mdefine_line|#define MPC52xx_INTR_SIZE&t;&t;0x04c
DECL|macro|MPC52xx_GPTx_OFFSET
mdefine_line|#define MPC52xx_GPTx_OFFSET(x)&t;&t;(0x0600 + ((x)&lt;&lt;4))
DECL|macro|MPC52xx_GPT_SIZE
mdefine_line|#define MPC52xx_GPT_SIZE&t;&t;0x010
DECL|macro|MPC52xx_RTC_OFFSET
mdefine_line|#define MPC52xx_RTC_OFFSET&t;&t;0x0800
DECL|macro|MPC52xx_RTC_SIZE
mdefine_line|#define MPC52xx_RTC_SIZE&t;&t;0x024
DECL|macro|MPC52xx_GPIO_OFFSET
mdefine_line|#define MPC52xx_GPIO_OFFSET&t;&t;0x0b00
DECL|macro|MPC52xx_GPIO_SIZE
mdefine_line|#define MPC52xx_GPIO_SIZE&t;&t;0x040
DECL|macro|MPC52xx_GPIO_WKUP_OFFSET
mdefine_line|#define MPC52xx_GPIO_WKUP_OFFSET&t;0x0c00
DECL|macro|MPC52xx_GPIO_WKUP_SIZE
mdefine_line|#define MPC52xx_GPIO_WKUP_SIZE&t;&t;0x028
DECL|macro|MPC52xx_PCI_OFFSET
mdefine_line|#define MPC52xx_PCI_OFFSET&t;&t;0x0d00
DECL|macro|MPC52xx_PCI_SIZE
mdefine_line|#define MPC52xx_PCI_SIZE&t;&t;0x100
DECL|macro|MPC52xx_SDMA_OFFSET
mdefine_line|#define MPC52xx_SDMA_OFFSET&t;&t;0x1200
DECL|macro|MPC52xx_SDMA_SIZE
mdefine_line|#define MPC52xx_SDMA_SIZE&t;&t;0x100
DECL|macro|MPC52xx_XLB_OFFSET
mdefine_line|#define MPC52xx_XLB_OFFSET&t;&t;0x1f00
DECL|macro|MPC52xx_XLB_SIZE
mdefine_line|#define MPC52xx_XLB_SIZE&t;&t;0x100
DECL|macro|MPC52xx_PSCx_OFFSET
mdefine_line|#define MPC52xx_PSCx_OFFSET(x)&t;&t;(((x)!=6)?(0x1e00+((x)&lt;&lt;9)):0x2c00)
DECL|macro|MPC52xx_PSC_SIZE
mdefine_line|#define MPC52xx_PSC_SIZE&t;&t;0x0a0
multiline_comment|/* SRAM used for SDMA */
DECL|macro|MPC52xx_SRAM_OFFSET
mdefine_line|#define MPC52xx_SRAM_OFFSET&t;&t;0x8000
DECL|macro|MPC52xx_SRAM_SIZE
mdefine_line|#define MPC52xx_SRAM_SIZE&t;&t;0x4000
multiline_comment|/* ======================================================================== */
multiline_comment|/* IRQ mapping                                                              */
multiline_comment|/* ======================================================================== */
multiline_comment|/* Be sure to look at mpc52xx_pic.h if you wish for whatever reason to change&n; * this&n; */
DECL|macro|MPC52xx_CRIT_IRQ_NUM
mdefine_line|#define MPC52xx_CRIT_IRQ_NUM&t;4
DECL|macro|MPC52xx_MAIN_IRQ_NUM
mdefine_line|#define MPC52xx_MAIN_IRQ_NUM&t;17
DECL|macro|MPC52xx_SDMA_IRQ_NUM
mdefine_line|#define MPC52xx_SDMA_IRQ_NUM&t;17
DECL|macro|MPC52xx_PERP_IRQ_NUM
mdefine_line|#define MPC52xx_PERP_IRQ_NUM&t;23
DECL|macro|MPC52xx_CRIT_IRQ_BASE
mdefine_line|#define MPC52xx_CRIT_IRQ_BASE&t;0
DECL|macro|MPC52xx_MAIN_IRQ_BASE
mdefine_line|#define MPC52xx_MAIN_IRQ_BASE&t;(MPC52xx_CRIT_IRQ_BASE + MPC52xx_CRIT_IRQ_NUM)
DECL|macro|MPC52xx_SDMA_IRQ_BASE
mdefine_line|#define MPC52xx_SDMA_IRQ_BASE&t;(MPC52xx_MAIN_IRQ_BASE + MPC52xx_MAIN_IRQ_NUM)
DECL|macro|MPC52xx_PERP_IRQ_BASE
mdefine_line|#define MPC52xx_PERP_IRQ_BASE&t;(MPC52xx_SDMA_IRQ_BASE + MPC52xx_SDMA_IRQ_NUM)
DECL|macro|MPC52xx_IRQ0
mdefine_line|#define MPC52xx_IRQ0&t;&t;&t;(MPC52xx_CRIT_IRQ_BASE + 0)
DECL|macro|MPC52xx_SLICE_TIMER_0_IRQ
mdefine_line|#define MPC52xx_SLICE_TIMER_0_IRQ&t;(MPC52xx_CRIT_IRQ_BASE + 1)
DECL|macro|MPC52xx_HI_INT_IRQ
mdefine_line|#define MPC52xx_HI_INT_IRQ&t;&t;(MPC52xx_CRIT_IRQ_BASE + 2)
DECL|macro|MPC52xx_CCS_IRQ
mdefine_line|#define MPC52xx_CCS_IRQ&t;&t;&t;(MPC52xx_CRIT_IRQ_BASE + 3)
DECL|macro|MPC52xx_IRQ1
mdefine_line|#define MPC52xx_IRQ1&t;&t;&t;(MPC52xx_MAIN_IRQ_BASE + 1)
DECL|macro|MPC52xx_IRQ2
mdefine_line|#define MPC52xx_IRQ2&t;&t;&t;(MPC52xx_MAIN_IRQ_BASE + 2)
DECL|macro|MPC52xx_IRQ3
mdefine_line|#define MPC52xx_IRQ3&t;&t;&t;(MPC52xx_MAIN_IRQ_BASE + 3)
DECL|macro|MPC52xx_SDMA_IRQ
mdefine_line|#define MPC52xx_SDMA_IRQ&t;&t;(MPC52xx_PERP_IRQ_BASE + 0)
DECL|macro|MPC52xx_PSC1_IRQ
mdefine_line|#define MPC52xx_PSC1_IRQ&t;&t;(MPC52xx_PERP_IRQ_BASE + 1)
DECL|macro|MPC52xx_PSC2_IRQ
mdefine_line|#define MPC52xx_PSC2_IRQ&t;&t;(MPC52xx_PERP_IRQ_BASE + 2)
DECL|macro|MPC52xx_PSC3_IRQ
mdefine_line|#define MPC52xx_PSC3_IRQ&t;&t;(MPC52xx_PERP_IRQ_BASE + 3)
DECL|macro|MPC52xx_PSC6_IRQ
mdefine_line|#define MPC52xx_PSC6_IRQ&t;&t;(MPC52xx_PERP_IRQ_BASE + 4)
DECL|macro|MPC52xx_IRDA_IRQ
mdefine_line|#define MPC52xx_IRDA_IRQ&t;&t;(MPC52xx_PERP_IRQ_BASE + 4)
DECL|macro|MPC52xx_FEC_IRQ
mdefine_line|#define MPC52xx_FEC_IRQ&t;&t;&t;(MPC52xx_PERP_IRQ_BASE + 5)
DECL|macro|MPC52xx_USB_IRQ
mdefine_line|#define MPC52xx_USB_IRQ&t;&t;&t;(MPC52xx_PERP_IRQ_BASE + 6)
DECL|macro|MPC52xx_ATA_IRQ
mdefine_line|#define MPC52xx_ATA_IRQ&t;&t;&t;(MPC52xx_PERP_IRQ_BASE + 7)
DECL|macro|MPC52xx_PCI_CNTRL_IRQ
mdefine_line|#define MPC52xx_PCI_CNTRL_IRQ&t;&t;(MPC52xx_PERP_IRQ_BASE + 8)
DECL|macro|MPC52xx_PCI_SCIRX_IRQ
mdefine_line|#define MPC52xx_PCI_SCIRX_IRQ&t;&t;(MPC52xx_PERP_IRQ_BASE + 9)
DECL|macro|MPC52xx_PCI_SCITX_IRQ
mdefine_line|#define MPC52xx_PCI_SCITX_IRQ&t;&t;(MPC52xx_PERP_IRQ_BASE + 10)
DECL|macro|MPC52xx_PSC4_IRQ
mdefine_line|#define MPC52xx_PSC4_IRQ&t;&t;(MPC52xx_PERP_IRQ_BASE + 11)
DECL|macro|MPC52xx_PSC5_IRQ
mdefine_line|#define MPC52xx_PSC5_IRQ&t;&t;(MPC52xx_PERP_IRQ_BASE + 12)
DECL|macro|MPC52xx_SPI_MODF_IRQ
mdefine_line|#define MPC52xx_SPI_MODF_IRQ&t;&t;(MPC52xx_PERP_IRQ_BASE + 13)
DECL|macro|MPC52xx_SPI_SPIF_IRQ
mdefine_line|#define MPC52xx_SPI_SPIF_IRQ&t;&t;(MPC52xx_PERP_IRQ_BASE + 14)
DECL|macro|MPC52xx_I2C1_IRQ
mdefine_line|#define MPC52xx_I2C1_IRQ&t;&t;(MPC52xx_PERP_IRQ_BASE + 15)
DECL|macro|MPC52xx_I2C2_IRQ
mdefine_line|#define MPC52xx_I2C2_IRQ&t;&t;(MPC52xx_PERP_IRQ_BASE + 16)
DECL|macro|MPC52xx_MSCAN1_IRQ
mdefine_line|#define MPC52xx_MSCAN1_IRQ&t;&t;(MPC52xx_PERP_IRQ_BASE + 17)
DECL|macro|MPC52xx_MSCAN2_IRQ
mdefine_line|#define MPC52xx_MSCAN2_IRQ&t;&t;(MPC52xx_PERP_IRQ_BASE + 18)
DECL|macro|MPC52xx_IR_RX_IRQ
mdefine_line|#define MPC52xx_IR_RX_IRQ&t;&t;(MPC52xx_PERP_IRQ_BASE + 19)
DECL|macro|MPC52xx_IR_TX_IRQ
mdefine_line|#define MPC52xx_IR_TX_IRQ&t;&t;(MPC52xx_PERP_IRQ_BASE + 20)
DECL|macro|MPC52xx_XLB_ARB_IRQ
mdefine_line|#define MPC52xx_XLB_ARB_IRQ&t;&t;(MPC52xx_PERP_IRQ_BASE + 21)
DECL|macro|MPC52xx_BDLC_IRQ
mdefine_line|#define MPC52xx_BDLC_IRQ&t;&t;(MPC52xx_PERP_IRQ_BASE + 22)
multiline_comment|/* ======================================================================== */
multiline_comment|/* Structures mapping of some unit register set                             */
multiline_comment|/* ======================================================================== */
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Memory Mapping Control */
DECL|struct|mpc52xx_mmap_ctl
r_struct
id|mpc52xx_mmap_ctl
(brace
DECL|member|mbar
id|u32
id|mbar
suffix:semicolon
multiline_comment|/* MMAP_CTRL + 0x00 */
DECL|member|cs0_start
id|u32
id|cs0_start
suffix:semicolon
multiline_comment|/* MMAP_CTRL + 0x04 */
DECL|member|cs0_stop
id|u32
id|cs0_stop
suffix:semicolon
multiline_comment|/* MMAP_CTRL + 0x08 */
DECL|member|cs1_start
id|u32
id|cs1_start
suffix:semicolon
multiline_comment|/* MMAP_CTRL + 0x0c */
DECL|member|cs1_stop
id|u32
id|cs1_stop
suffix:semicolon
multiline_comment|/* MMAP_CTRL + 0x10 */
DECL|member|cs2_start
id|u32
id|cs2_start
suffix:semicolon
multiline_comment|/* MMAP_CTRL + 0x14 */
DECL|member|cs2_stop
id|u32
id|cs2_stop
suffix:semicolon
multiline_comment|/* MMAP_CTRL + 0x18 */
DECL|member|cs3_start
id|u32
id|cs3_start
suffix:semicolon
multiline_comment|/* MMAP_CTRL + 0x1c */
DECL|member|cs3_stop
id|u32
id|cs3_stop
suffix:semicolon
multiline_comment|/* MMAP_CTRL + 0x20 */
DECL|member|cs4_start
id|u32
id|cs4_start
suffix:semicolon
multiline_comment|/* MMAP_CTRL + 0x24 */
DECL|member|cs4_stop
id|u32
id|cs4_stop
suffix:semicolon
multiline_comment|/* MMAP_CTRL + 0x28 */
DECL|member|cs5_start
id|u32
id|cs5_start
suffix:semicolon
multiline_comment|/* MMAP_CTRL + 0x2c */
DECL|member|cs5_stop
id|u32
id|cs5_stop
suffix:semicolon
multiline_comment|/* MMAP_CTRL + 0x30 */
DECL|member|sdram0
id|u32
id|sdram0
suffix:semicolon
multiline_comment|/* MMAP_CTRL + 0x34 */
DECL|member|sdram1
id|u32
id|sdram1
suffix:semicolon
multiline_comment|/* MMAP_CTRL + 0X38 */
DECL|member|reserved
id|u32
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* MMAP_CTRL + 0x3c .. 0x48 */
DECL|member|boot_start
id|u32
id|boot_start
suffix:semicolon
multiline_comment|/* MMAP_CTRL + 0x4c */
DECL|member|boot_stop
id|u32
id|boot_stop
suffix:semicolon
multiline_comment|/* MMAP_CTRL + 0x50 */
DECL|member|ipbi_ws_ctrl
id|u32
id|ipbi_ws_ctrl
suffix:semicolon
multiline_comment|/* MMAP_CTRL + 0x54 */
DECL|member|cs6_start
id|u32
id|cs6_start
suffix:semicolon
multiline_comment|/* MMAP_CTRL + 0x58 */
DECL|member|cs6_stop
id|u32
id|cs6_stop
suffix:semicolon
multiline_comment|/* MMAP_CTRL + 0x5c */
DECL|member|cs7_start
id|u32
id|cs7_start
suffix:semicolon
multiline_comment|/* MMAP_CTRL + 0x60 */
DECL|member|cs7_stop
id|u32
id|cs7_stop
suffix:semicolon
multiline_comment|/* MMAP_CTRL + 0x64 */
)brace
suffix:semicolon
multiline_comment|/* SDRAM control */
DECL|struct|mpc52xx_sdram
r_struct
id|mpc52xx_sdram
(brace
DECL|member|mode
id|u32
id|mode
suffix:semicolon
multiline_comment|/* SDRAM + 0x00 */
DECL|member|ctrl
id|u32
id|ctrl
suffix:semicolon
multiline_comment|/* SDRAM + 0x04 */
DECL|member|config1
id|u32
id|config1
suffix:semicolon
multiline_comment|/* SDRAM + 0x08 */
DECL|member|config2
id|u32
id|config2
suffix:semicolon
multiline_comment|/* SDRAM + 0x0c */
)brace
suffix:semicolon
multiline_comment|/* Interrupt controller */
DECL|struct|mpc52xx_intr
r_struct
id|mpc52xx_intr
(brace
DECL|member|per_mask
id|u32
id|per_mask
suffix:semicolon
multiline_comment|/* INTR + 0x00 */
DECL|member|per_pri1
id|u32
id|per_pri1
suffix:semicolon
multiline_comment|/* INTR + 0x04 */
DECL|member|per_pri2
id|u32
id|per_pri2
suffix:semicolon
multiline_comment|/* INTR + 0x08 */
DECL|member|per_pri3
id|u32
id|per_pri3
suffix:semicolon
multiline_comment|/* INTR + 0x0c */
DECL|member|ctrl
id|u32
id|ctrl
suffix:semicolon
multiline_comment|/* INTR + 0x10 */
DECL|member|main_mask
id|u32
id|main_mask
suffix:semicolon
multiline_comment|/* INTR + 0x14 */
DECL|member|main_pri1
id|u32
id|main_pri1
suffix:semicolon
multiline_comment|/* INTR + 0x18 */
DECL|member|main_pri2
id|u32
id|main_pri2
suffix:semicolon
multiline_comment|/* INTR + 0x1c */
DECL|member|reserved1
id|u32
id|reserved1
suffix:semicolon
multiline_comment|/* INTR + 0x20 */
DECL|member|enc_status
id|u32
id|enc_status
suffix:semicolon
multiline_comment|/* INTR + 0x24 */
DECL|member|crit_status
id|u32
id|crit_status
suffix:semicolon
multiline_comment|/* INTR + 0x28 */
DECL|member|main_status
id|u32
id|main_status
suffix:semicolon
multiline_comment|/* INTR + 0x2c */
DECL|member|per_status
id|u32
id|per_status
suffix:semicolon
multiline_comment|/* INTR + 0x30 */
DECL|member|reserved2
id|u32
id|reserved2
suffix:semicolon
multiline_comment|/* INTR + 0x34 */
DECL|member|per_error
id|u32
id|per_error
suffix:semicolon
multiline_comment|/* INTR + 0x38 */
)brace
suffix:semicolon
multiline_comment|/* SDMA */
DECL|struct|mpc52xx_sdma
r_struct
id|mpc52xx_sdma
(brace
DECL|member|taskBar
id|u32
id|taskBar
suffix:semicolon
multiline_comment|/* SDMA + 0x00 */
DECL|member|currentPointer
id|u32
id|currentPointer
suffix:semicolon
multiline_comment|/* SDMA + 0x04 */
DECL|member|endPointer
id|u32
id|endPointer
suffix:semicolon
multiline_comment|/* SDMA + 0x08 */
DECL|member|variablePointer
id|u32
id|variablePointer
suffix:semicolon
multiline_comment|/* SDMA + 0x0c */
DECL|member|IntVect1
id|u8
id|IntVect1
suffix:semicolon
multiline_comment|/* SDMA + 0x10 */
DECL|member|IntVect2
id|u8
id|IntVect2
suffix:semicolon
multiline_comment|/* SDMA + 0x11 */
DECL|member|PtdCntrl
id|u16
id|PtdCntrl
suffix:semicolon
multiline_comment|/* SDMA + 0x12 */
DECL|member|IntPend
id|u32
id|IntPend
suffix:semicolon
multiline_comment|/* SDMA + 0x14 */
DECL|member|IntMask
id|u32
id|IntMask
suffix:semicolon
multiline_comment|/* SDMA + 0x18 */
DECL|member|tcr
id|u16
id|tcr
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* SDMA + 0x1c .. 0x3a */
DECL|member|ipr
id|u8
id|ipr
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* SDMA + 0x3c .. 0x5b */
DECL|member|cReqSelect
id|u32
id|cReqSelect
suffix:semicolon
multiline_comment|/* SDMA + 0x5c */
DECL|member|task_size0
id|u32
id|task_size0
suffix:semicolon
multiline_comment|/* SDMA + 0x60 */
DECL|member|task_size1
id|u32
id|task_size1
suffix:semicolon
multiline_comment|/* SDMA + 0x64 */
DECL|member|MDEDebug
id|u32
id|MDEDebug
suffix:semicolon
multiline_comment|/* SDMA + 0x68 */
DECL|member|ADSDebug
id|u32
id|ADSDebug
suffix:semicolon
multiline_comment|/* SDMA + 0x6c */
DECL|member|Value1
id|u32
id|Value1
suffix:semicolon
multiline_comment|/* SDMA + 0x70 */
DECL|member|Value2
id|u32
id|Value2
suffix:semicolon
multiline_comment|/* SDMA + 0x74 */
DECL|member|Control
id|u32
id|Control
suffix:semicolon
multiline_comment|/* SDMA + 0x78 */
DECL|member|Status
id|u32
id|Status
suffix:semicolon
multiline_comment|/* SDMA + 0x7c */
DECL|member|PTDDebug
id|u32
id|PTDDebug
suffix:semicolon
multiline_comment|/* SDMA + 0x80 */
)brace
suffix:semicolon
multiline_comment|/* GPT */
DECL|struct|mpc52xx_gpt
r_struct
id|mpc52xx_gpt
(brace
DECL|member|mode
id|u32
id|mode
suffix:semicolon
multiline_comment|/* GPTx + 0x00 */
DECL|member|count
id|u32
id|count
suffix:semicolon
multiline_comment|/* GPTx + 0x04 */
DECL|member|pwm
id|u32
id|pwm
suffix:semicolon
multiline_comment|/* GPTx + 0x08 */
DECL|member|status
id|u32
id|status
suffix:semicolon
multiline_comment|/* GPTx + 0X0c */
)brace
suffix:semicolon
multiline_comment|/* RTC */
DECL|struct|mpc52xx_rtc
r_struct
id|mpc52xx_rtc
(brace
DECL|member|time_set
id|u32
id|time_set
suffix:semicolon
multiline_comment|/* RTC + 0x00 */
DECL|member|date_set
id|u32
id|date_set
suffix:semicolon
multiline_comment|/* RTC + 0x04 */
DECL|member|stopwatch
id|u32
id|stopwatch
suffix:semicolon
multiline_comment|/* RTC + 0x08 */
DECL|member|int_enable
id|u32
id|int_enable
suffix:semicolon
multiline_comment|/* RTC + 0x0c */
DECL|member|time
id|u32
id|time
suffix:semicolon
multiline_comment|/* RTC + 0x10 */
DECL|member|date
id|u32
id|date
suffix:semicolon
multiline_comment|/* RTC + 0x14 */
DECL|member|stopwatch_intr
id|u32
id|stopwatch_intr
suffix:semicolon
multiline_comment|/* RTC + 0x18 */
DECL|member|bus_error
id|u32
id|bus_error
suffix:semicolon
multiline_comment|/* RTC + 0x1c */
DECL|member|dividers
id|u32
id|dividers
suffix:semicolon
multiline_comment|/* RTC + 0x20 */
)brace
suffix:semicolon
multiline_comment|/* GPIO */
DECL|struct|mpc52xx_gpio
r_struct
id|mpc52xx_gpio
(brace
DECL|member|port_config
id|u32
id|port_config
suffix:semicolon
multiline_comment|/* GPIO + 0x00 */
DECL|member|simple_gpioe
id|u32
id|simple_gpioe
suffix:semicolon
multiline_comment|/* GPIO + 0x04 */
DECL|member|simple_ode
id|u32
id|simple_ode
suffix:semicolon
multiline_comment|/* GPIO + 0x08 */
DECL|member|simple_ddr
id|u32
id|simple_ddr
suffix:semicolon
multiline_comment|/* GPIO + 0x0c */
DECL|member|simple_dvo
id|u32
id|simple_dvo
suffix:semicolon
multiline_comment|/* GPIO + 0x10 */
DECL|member|simple_ival
id|u32
id|simple_ival
suffix:semicolon
multiline_comment|/* GPIO + 0x14 */
DECL|member|outo_gpioe
id|u8
id|outo_gpioe
suffix:semicolon
multiline_comment|/* GPIO + 0x18 */
DECL|member|reserved1
id|u8
id|reserved1
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* GPIO + 0x19 */
DECL|member|outo_dvo
id|u8
id|outo_dvo
suffix:semicolon
multiline_comment|/* GPIO + 0x1c */
DECL|member|reserved2
id|u8
id|reserved2
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* GPIO + 0x1d */
DECL|member|sint_gpioe
id|u8
id|sint_gpioe
suffix:semicolon
multiline_comment|/* GPIO + 0x20 */
DECL|member|reserved3
id|u8
id|reserved3
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* GPIO + 0x21 */
DECL|member|sint_ode
id|u8
id|sint_ode
suffix:semicolon
multiline_comment|/* GPIO + 0x24 */
DECL|member|reserved4
id|u8
id|reserved4
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* GPIO + 0x25 */
DECL|member|sint_ddr
id|u8
id|sint_ddr
suffix:semicolon
multiline_comment|/* GPIO + 0x28 */
DECL|member|reserved5
id|u8
id|reserved5
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* GPIO + 0x29 */
DECL|member|sint_dvo
id|u8
id|sint_dvo
suffix:semicolon
multiline_comment|/* GPIO + 0x2c */
DECL|member|reserved6
id|u8
id|reserved6
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* GPIO + 0x2d */
DECL|member|sint_inten
id|u8
id|sint_inten
suffix:semicolon
multiline_comment|/* GPIO + 0x30 */
DECL|member|reserved7
id|u8
id|reserved7
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* GPIO + 0x31 */
DECL|member|sint_itype
id|u16
id|sint_itype
suffix:semicolon
multiline_comment|/* GPIO + 0x34 */
DECL|member|reserved8
id|u16
id|reserved8
suffix:semicolon
multiline_comment|/* GPIO + 0x36 */
DECL|member|gpio_control
id|u8
id|gpio_control
suffix:semicolon
multiline_comment|/* GPIO + 0x38 */
DECL|member|reserved9
id|u8
id|reserved9
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* GPIO + 0x39 */
DECL|member|sint_istat
id|u8
id|sint_istat
suffix:semicolon
multiline_comment|/* GPIO + 0x3c */
DECL|member|sint_ival
id|u8
id|sint_ival
suffix:semicolon
multiline_comment|/* GPIO + 0x3d */
DECL|member|bus_errs
id|u8
id|bus_errs
suffix:semicolon
multiline_comment|/* GPIO + 0x3e */
DECL|member|reserved10
id|u8
id|reserved10
suffix:semicolon
multiline_comment|/* GPIO + 0x3f */
)brace
suffix:semicolon
DECL|macro|MPC52xx_GPIO_PSC_CONFIG_UART_WITHOUT_CD
mdefine_line|#define MPC52xx_GPIO_PSC_CONFIG_UART_WITHOUT_CD&t;4
DECL|macro|MPC52xx_GPIO_PSC_CONFIG_UART_WITH_CD
mdefine_line|#define MPC52xx_GPIO_PSC_CONFIG_UART_WITH_CD&t;5
DECL|macro|MPC52xx_GPIO_PCI_DIS
mdefine_line|#define MPC52xx_GPIO_PCI_DIS&t;&t;&t;(1&lt;&lt;15)
multiline_comment|/* GPIO with WakeUp*/
DECL|struct|mpc52xx_gpio_wkup
r_struct
id|mpc52xx_gpio_wkup
(brace
DECL|member|wkup_gpioe
id|u8
id|wkup_gpioe
suffix:semicolon
multiline_comment|/* GPIO_WKUP + 0x00 */
DECL|member|reserved1
id|u8
id|reserved1
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* GPIO_WKUP + 0x03 */
DECL|member|wkup_ode
id|u8
id|wkup_ode
suffix:semicolon
multiline_comment|/* GPIO_WKUP + 0x04 */
DECL|member|reserved2
id|u8
id|reserved2
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* GPIO_WKUP + 0x05 */
DECL|member|wkup_ddr
id|u8
id|wkup_ddr
suffix:semicolon
multiline_comment|/* GPIO_WKUP + 0x08 */
DECL|member|reserved3
id|u8
id|reserved3
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* GPIO_WKUP + 0x09 */
DECL|member|wkup_dvo
id|u8
id|wkup_dvo
suffix:semicolon
multiline_comment|/* GPIO_WKUP + 0x0C */
DECL|member|reserved4
id|u8
id|reserved4
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* GPIO_WKUP + 0x0D */
DECL|member|wkup_inten
id|u8
id|wkup_inten
suffix:semicolon
multiline_comment|/* GPIO_WKUP + 0x10 */
DECL|member|reserved5
id|u8
id|reserved5
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* GPIO_WKUP + 0x11 */
DECL|member|wkup_iinten
id|u8
id|wkup_iinten
suffix:semicolon
multiline_comment|/* GPIO_WKUP + 0x14 */
DECL|member|reserved6
id|u8
id|reserved6
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* GPIO_WKUP + 0x15 */
DECL|member|wkup_itype
id|u16
id|wkup_itype
suffix:semicolon
multiline_comment|/* GPIO_WKUP + 0x18 */
DECL|member|reserved7
id|u8
id|reserved7
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* GPIO_WKUP + 0x1A */
DECL|member|wkup_maste
id|u8
id|wkup_maste
suffix:semicolon
multiline_comment|/* GPIO_WKUP + 0x1C */
DECL|member|reserved8
id|u8
id|reserved8
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* GPIO_WKUP + 0x1D */
DECL|member|wkup_ival
id|u8
id|wkup_ival
suffix:semicolon
multiline_comment|/* GPIO_WKUP + 0x20 */
DECL|member|reserved9
id|u8
id|reserved9
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* GPIO_WKUP + 0x21 */
DECL|member|wkup_istat
id|u8
id|wkup_istat
suffix:semicolon
multiline_comment|/* GPIO_WKUP + 0x24 */
DECL|member|reserved10
id|u8
id|reserved10
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* GPIO_WKUP + 0x25 */
)brace
suffix:semicolon
multiline_comment|/* XLB Bus control */
DECL|struct|mpc52xx_xlb
r_struct
id|mpc52xx_xlb
(brace
DECL|member|reserved
id|u8
id|reserved
(braket
l_int|0x40
)braket
suffix:semicolon
DECL|member|config
id|u32
id|config
suffix:semicolon
multiline_comment|/* XLB + 0x40 */
DECL|member|version
id|u32
id|version
suffix:semicolon
multiline_comment|/* XLB + 0x44 */
DECL|member|status
id|u32
id|status
suffix:semicolon
multiline_comment|/* XLB + 0x48 */
DECL|member|int_enable
id|u32
id|int_enable
suffix:semicolon
multiline_comment|/* XLB + 0x4c */
DECL|member|addr_capture
id|u32
id|addr_capture
suffix:semicolon
multiline_comment|/* XLB + 0x50 */
DECL|member|bus_sig_capture
id|u32
id|bus_sig_capture
suffix:semicolon
multiline_comment|/* XLB + 0x54 */
DECL|member|addr_timeout
id|u32
id|addr_timeout
suffix:semicolon
multiline_comment|/* XLB + 0x58 */
DECL|member|data_timeout
id|u32
id|data_timeout
suffix:semicolon
multiline_comment|/* XLB + 0x5c */
DECL|member|bus_act_timeout
id|u32
id|bus_act_timeout
suffix:semicolon
multiline_comment|/* XLB + 0x60 */
DECL|member|master_pri_enable
id|u32
id|master_pri_enable
suffix:semicolon
multiline_comment|/* XLB + 0x64 */
DECL|member|master_priority
id|u32
id|master_priority
suffix:semicolon
multiline_comment|/* XLB + 0x68 */
DECL|member|base_address
id|u32
id|base_address
suffix:semicolon
multiline_comment|/* XLB + 0x6c */
DECL|member|snoop_window
id|u32
id|snoop_window
suffix:semicolon
multiline_comment|/* XLB + 0x70 */
)brace
suffix:semicolon
DECL|macro|MPC52xx_XLB_CFG_SNOOP
mdefine_line|#define MPC52xx_XLB_CFG_SNOOP&t;&t;(1 &lt;&lt; 15)
multiline_comment|/* Clock Distribution control */
DECL|struct|mpc52xx_cdm
r_struct
id|mpc52xx_cdm
(brace
DECL|member|jtag_id
id|u32
id|jtag_id
suffix:semicolon
multiline_comment|/* CDM + 0x00  reg0 read only */
DECL|member|rstcfg
id|u32
id|rstcfg
suffix:semicolon
multiline_comment|/* CDM + 0x04  reg1 read only */
DECL|member|breadcrumb
id|u32
id|breadcrumb
suffix:semicolon
multiline_comment|/* CDM + 0x08  reg2 */
DECL|member|mem_clk_sel
id|u8
id|mem_clk_sel
suffix:semicolon
multiline_comment|/* CDM + 0x0c  reg3 byte0 */
DECL|member|xlb_clk_sel
id|u8
id|xlb_clk_sel
suffix:semicolon
multiline_comment|/* CDM + 0x0d  reg3 byte1 read only */
DECL|member|ipb_clk_sel
id|u8
id|ipb_clk_sel
suffix:semicolon
multiline_comment|/* CDM + 0x0e  reg3 byte2 */
DECL|member|pci_clk_sel
id|u8
id|pci_clk_sel
suffix:semicolon
multiline_comment|/* CDM + 0x0f  reg3 byte3 */
DECL|member|ext_48mhz_en
id|u8
id|ext_48mhz_en
suffix:semicolon
multiline_comment|/* CDM + 0x10  reg4 byte0 */
DECL|member|fd_enable
id|u8
id|fd_enable
suffix:semicolon
multiline_comment|/* CDM + 0x11  reg4 byte1 */
DECL|member|fd_counters
id|u16
id|fd_counters
suffix:semicolon
multiline_comment|/* CDM + 0x12  reg4 byte2,3 */
DECL|member|clk_enables
id|u32
id|clk_enables
suffix:semicolon
multiline_comment|/* CDM + 0x14  reg5 */
DECL|member|osc_disable
id|u8
id|osc_disable
suffix:semicolon
multiline_comment|/* CDM + 0x18  reg6 byte0 */
DECL|member|reserved0
id|u8
id|reserved0
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* CDM + 0x19  reg6 byte1,2,3 */
DECL|member|ccs_sleep_enable
id|u8
id|ccs_sleep_enable
suffix:semicolon
multiline_comment|/* CDM + 0x1c  reg7 byte0 */
DECL|member|osc_sleep_enable
id|u8
id|osc_sleep_enable
suffix:semicolon
multiline_comment|/* CDM + 0x1d  reg7 byte1 */
DECL|member|reserved1
id|u8
id|reserved1
suffix:semicolon
multiline_comment|/* CDM + 0x1e  reg7 byte2 */
DECL|member|ccs_qreq_test
id|u8
id|ccs_qreq_test
suffix:semicolon
multiline_comment|/* CDM + 0x1f  reg7 byte3 */
DECL|member|soft_reset
id|u8
id|soft_reset
suffix:semicolon
multiline_comment|/* CDM + 0x20  u8 byte0 */
DECL|member|no_ckstp
id|u8
id|no_ckstp
suffix:semicolon
multiline_comment|/* CDM + 0x21  u8 byte0 */
DECL|member|reserved2
id|u8
id|reserved2
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* CDM + 0x22  u8 byte1,2,3 */
DECL|member|pll_lock
id|u8
id|pll_lock
suffix:semicolon
multiline_comment|/* CDM + 0x24  reg9 byte0 */
DECL|member|pll_looselock
id|u8
id|pll_looselock
suffix:semicolon
multiline_comment|/* CDM + 0x25  reg9 byte1 */
DECL|member|pll_sm_lockwin
id|u8
id|pll_sm_lockwin
suffix:semicolon
multiline_comment|/* CDM + 0x26  reg9 byte2 */
DECL|member|reserved3
id|u8
id|reserved3
suffix:semicolon
multiline_comment|/* CDM + 0x27  reg9 byte3 */
DECL|member|reserved4
id|u16
id|reserved4
suffix:semicolon
multiline_comment|/* CDM + 0x28  reg10 byte0,1 */
DECL|member|mclken_div_psc1
id|u16
id|mclken_div_psc1
suffix:semicolon
multiline_comment|/* CDM + 0x2a  reg10 byte2,3 */
DECL|member|reserved5
id|u16
id|reserved5
suffix:semicolon
multiline_comment|/* CDM + 0x2c  reg11 byte0,1 */
DECL|member|mclken_div_psc2
id|u16
id|mclken_div_psc2
suffix:semicolon
multiline_comment|/* CDM + 0x2e  reg11 byte2,3 */
DECL|member|reserved6
id|u16
id|reserved6
suffix:semicolon
multiline_comment|/* CDM + 0x30  reg12 byte0,1 */
DECL|member|mclken_div_psc3
id|u16
id|mclken_div_psc3
suffix:semicolon
multiline_comment|/* CDM + 0x32  reg12 byte2,3 */
DECL|member|reserved7
id|u16
id|reserved7
suffix:semicolon
multiline_comment|/* CDM + 0x34  reg13 byte0,1 */
DECL|member|mclken_div_psc6
id|u16
id|mclken_div_psc6
suffix:semicolon
multiline_comment|/* CDM + 0x36  reg13 byte2,3 */
)brace
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* ========================================================================= */
multiline_comment|/* Prototypes for MPC52xx syslib                                             */
multiline_comment|/* ========================================================================= */
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|mpc52xx_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|mpc52xx_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
r_int
id|mpc52xx_find_end_of_memory
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mpc52xx_set_bat
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mpc52xx_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mpc52xx_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
suffix:semicolon
r_extern
r_void
id|mpc52xx_halt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mpc52xx_power_off
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mpc52xx_progress
c_func
(paren
r_char
op_star
id|s
comma
r_int
r_int
id|hex
)paren
suffix:semicolon
r_extern
r_void
id|mpc52xx_calibrate_decr
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mpc52xx_find_bridges
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Matching of PSC function */
DECL|struct|mpc52xx_psc_func
r_struct
id|mpc52xx_psc_func
(brace
DECL|member|id
r_int
id|id
suffix:semicolon
DECL|member|func
r_char
op_star
id|func
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|mpc52xx_match_psc_function
c_func
(paren
r_int
id|psc_idx
comma
r_const
r_char
op_star
id|func
)paren
suffix:semicolon
r_extern
r_struct
id|mpc52xx_psc_func
id|mpc52xx_psc_functions
(braket
)braket
suffix:semicolon
multiline_comment|/* This array is to be defined in platform file */
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* ========================================================================= */
multiline_comment|/* Platform configuration                                                    */
multiline_comment|/* ========================================================================= */
multiline_comment|/* The U-Boot platform information struct */
r_extern
id|bd_t
id|__res
suffix:semicolon
multiline_comment|/* Platform options */
macro_line|#if defined(CONFIG_LITE5200)
macro_line|#include &lt;platforms/lite5200.h&gt;
macro_line|#endif
macro_line|#endif /* __ASM_MPC52xx_H__ */
eof
