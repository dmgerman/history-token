multiline_comment|/*&n; * linux/include/asm-arm/arch-omap/hardware.h&n; *&n; * Hardware definitions for TI OMAP processors and boards&n; *&n; * NOTE: Please put device driver specific defines into a separate header&n; *&t; file for each driver.&n; *&n; * Copyright (C) 2001 RidgeRun, Inc.&n; * Author: RidgeRun, Inc. Greg Lonnon &lt;glonnon@ridgerun.com&gt;&n; *&n; * Reorganized for Linux-2.6 by Tony Lindgren &lt;tony@atomide.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n; * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF&n; * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __ASM_ARCH_OMAP_HARDWARE_H
DECL|macro|__ASM_ARCH_OMAP_HARDWARE_H
mdefine_line|#define __ASM_ARCH_OMAP_HARDWARE_H
macro_line|#include &lt;asm/sizes.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef __ASSEMBLER__
macro_line|#include &lt;asm/types.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/mach-types.h&gt;
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * I/O mapping&n; * ----------------------------------------------------------------------------&n; */
DECL|macro|IO_PHYS
mdefine_line|#define IO_PHYS&t;&t;&t;0xFFFB0000
DECL|macro|IO_OFFSET
mdefine_line|#define IO_OFFSET&t;&t;0x01000000&t;/* Virtual IO = 0xfefb0000 */
DECL|macro|IO_VIRT
mdefine_line|#define IO_VIRT&t;&t;&t;(IO_PHYS - IO_OFFSET)
DECL|macro|IO_SIZE
mdefine_line|#define IO_SIZE&t;&t;&t;0x40000
DECL|macro|IO_ADDRESS
mdefine_line|#define IO_ADDRESS(x)&t;&t;((x) - IO_OFFSET)
DECL|macro|PCIO_BASE
mdefine_line|#define PCIO_BASE&t;&t;0
DECL|macro|io_p2v
mdefine_line|#define io_p2v(x)               ((x) - IO_OFFSET)
DECL|macro|io_v2p
mdefine_line|#define io_v2p(x)               ((x) + IO_OFFSET)
macro_line|#ifndef __ASSEMBLER__
multiline_comment|/* 16 bit uses LDRH/STRH, base +/- offset_8 */
DECL|member|offset
DECL|typedef|__regbase16
r_typedef
r_struct
(brace
r_volatile
id|u16
id|offset
(braket
l_int|256
)braket
suffix:semicolon
)brace
id|__regbase16
suffix:semicolon
DECL|macro|__REGV16
mdefine_line|#define __REGV16(vaddr)&t;&t;((__regbase16 *)((vaddr)&amp;~0xff)) &bslash;&n;&t;&t;&t;&t;&t;-&gt;offset[((vaddr)&amp;0xff)&gt;&gt;1]
DECL|macro|__REG16
mdefine_line|#define __REG16(paddr)          __REGV16(io_p2v(paddr))
multiline_comment|/* 8/32 bit uses LDR/STR, base +/- offset_12 */
DECL|member|offset
DECL|typedef|__regbase8
r_typedef
r_struct
(brace
r_volatile
id|u8
id|offset
(braket
l_int|4096
)braket
suffix:semicolon
)brace
id|__regbase8
suffix:semicolon
DECL|macro|__REGV8
mdefine_line|#define __REGV8(vaddr)&t;&t;((__regbase8  *)((paddr)&amp;~4095)) &bslash;&n;&t;&t;&t;&t;&t;-&gt;offset[((paddr)&amp;4095)&gt;&gt;0]
DECL|macro|__REG8
mdefine_line|#define __REG8(paddr)&t;&t;__REGV8(io_p2v(paddr))
DECL|member|offset
DECL|typedef|__regbase32
r_typedef
r_struct
(brace
r_volatile
id|u32
id|offset
(braket
l_int|4096
)braket
suffix:semicolon
)brace
id|__regbase32
suffix:semicolon
DECL|macro|__REGV32
mdefine_line|#define __REGV32(vaddr)&t;&t;((__regbase32 *)((vaddr)&amp;~4095)) &bslash;&n;&t;&t;&t;&t;&t;-&gt;offset[((vaddr)&amp;4095)&gt;&gt;2]
DECL|macro|__REG32
mdefine_line|#define __REG32(paddr)&t;&t;__REGV32(io_p2v(paddr))
macro_line|#else
DECL|macro|__REG8
mdefine_line|#define __REG8(paddr)&t;&t;io_p2v(paddr)
DECL|macro|__REG16
mdefine_line|#define __REG16(paddr)&t;&t;io_p2v(paddr)
DECL|macro|__REG32
mdefine_line|#define __REG32(paddr)&t;&t;io_p2v(paddr)
macro_line|#endif
multiline_comment|/*&n; * ---------------------------------------------------------------------------&n; * Common definitions for all OMAP processors&n; * NOTE: Put all processor or board specific parts to the special header&n; *&t; files.&n; * ---------------------------------------------------------------------------&n; */
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * Clocks&n; * ----------------------------------------------------------------------------&n; */
DECL|macro|CLKGEN_RESET_BASE
mdefine_line|#define CLKGEN_RESET_BASE&t;(0xfffece00)
DECL|macro|ARM_CKCTL
mdefine_line|#define ARM_CKCTL&t;&t;(CLKGEN_RESET_BASE + 0x0)
DECL|macro|ARM_IDLECT1
mdefine_line|#define ARM_IDLECT1&t;&t;(CLKGEN_RESET_BASE + 0x4)
DECL|macro|ARM_IDLECT2
mdefine_line|#define ARM_IDLECT2&t;&t;(CLKGEN_RESET_BASE + 0x8)
DECL|macro|ARM_EWUPCT
mdefine_line|#define ARM_EWUPCT&t;&t;(CLKGEN_RESET_BASE + 0xC)
DECL|macro|ARM_RSTCT1
mdefine_line|#define ARM_RSTCT1&t;&t;(CLKGEN_RESET_BASE + 0x10)
DECL|macro|ARM_RSTCT2
mdefine_line|#define ARM_RSTCT2&t;&t;(CLKGEN_RESET_BASE + 0x14)
DECL|macro|ARM_SYSST
mdefine_line|#define ARM_SYSST&t;&t;(CLKGEN_RESET_BASE + 0x18)
DECL|macro|CK_RATEF
mdefine_line|#define CK_RATEF&t;&t;1
DECL|macro|CK_IDLEF
mdefine_line|#define CK_IDLEF&t;&t;2
DECL|macro|CK_ENABLEF
mdefine_line|#define CK_ENABLEF&t;&t;4
DECL|macro|CK_SELECTF
mdefine_line|#define CK_SELECTF&t;&t;8
DECL|macro|SETARM_IDLE_SHIFT
mdefine_line|#define SETARM_IDLE_SHIFT
multiline_comment|/* DPLL control registers */
DECL|macro|DPLL_CTL_REG
mdefine_line|#define DPLL_CTL_REG&t;&t;(0xfffecf00)
DECL|macro|CK_DPLL1
mdefine_line|#define CK_DPLL1&t;&t;(0xfffecf00)
multiline_comment|/* ULPD */
DECL|macro|ULPD_REG_BASE
mdefine_line|#define ULPD_REG_BASE&t;&t;(0xfffe0800)
DECL|macro|ULPD_IT_STATUS_REG
mdefine_line|#define ULPD_IT_STATUS_REG&t;(ULPD_REG_BASE + 0x14)
DECL|macro|ULPD_CLOCK_CTRL_REG
mdefine_line|#define ULPD_CLOCK_CTRL_REG&t;(ULPD_REG_BASE + 0x30)
DECL|macro|ULPD_SOFT_REQ_REG
mdefine_line|#define ULPD_SOFT_REQ_REG&t;(ULPD_REG_BASE + 0x34)
DECL|macro|ULPD_DPLL_CTRL_REG
mdefine_line|#define ULPD_DPLL_CTRL_REG&t;(ULPD_REG_BASE + 0x3c)
DECL|macro|ULPD_STATUS_REQ_REG
mdefine_line|#define ULPD_STATUS_REQ_REG&t;(ULPD_REG_BASE + 0x40)
DECL|macro|ULPD_APLL_CTRL_REG
mdefine_line|#define ULPD_APLL_CTRL_REG&t;(ULPD_REG_BASE + 0x4c)
DECL|macro|ULPD_POWER_CTRL_REG
mdefine_line|#define ULPD_POWER_CTRL_REG&t;(ULPD_REG_BASE + 0x50)
DECL|macro|ULPD_CAM_CLK_CTRL_REG
mdefine_line|#define ULPD_CAM_CLK_CTRL_REG&t;(ULPD_REG_BASE + 0x7c)
multiline_comment|/*&n; * ---------------------------------------------------------------------------&n; * Timers&n; * ---------------------------------------------------------------------------&n; */
DECL|macro|OMAP_32kHz_TIMER_BASE
mdefine_line|#define OMAP_32kHz_TIMER_BASE 0xfffb9000
multiline_comment|/* 32k Timer Registers */
DECL|macro|TIMER32k_CR
mdefine_line|#define TIMER32k_CR&t;&t;0x08
DECL|macro|TIMER32k_TVR
mdefine_line|#define TIMER32k_TVR&t;&t;0x00
DECL|macro|TIMER32k_TCR
mdefine_line|#define TIMER32k_TCR&t;&t;0x04
multiline_comment|/* 32k Timer Control Register definition */
DECL|macro|TIMER32k_TSS
mdefine_line|#define TIMER32k_TSS&t;&t;(1&lt;&lt;0)
DECL|macro|TIMER32k_TRB
mdefine_line|#define TIMER32k_TRB&t;&t;(1&lt;&lt;1)
DECL|macro|TIMER32k_INT
mdefine_line|#define TIMER32k_INT&t;&t;(1&lt;&lt;2)
DECL|macro|TIMER32k_ARL
mdefine_line|#define TIMER32k_ARL&t;&t;(1&lt;&lt;3)
multiline_comment|/* MPU Timer base addresses */
DECL|macro|OMAP_MPUTIMER_BASE
mdefine_line|#define OMAP_MPUTIMER_BASE&t;0xfffec500
DECL|macro|OMAP_MPUTIMER_OFF
mdefine_line|#define OMAP_MPUTIMER_OFF&t;0x00000100
DECL|macro|OMAP_TIMER1_BASE
mdefine_line|#define OMAP_TIMER1_BASE&t;0xfffec500
DECL|macro|OMAP_TIMER2_BASE
mdefine_line|#define OMAP_TIMER2_BASE&t;0xfffec600
DECL|macro|OMAP_TIMER3_BASE
mdefine_line|#define OMAP_TIMER3_BASE&t;0xfffec700
DECL|macro|OMAP_WATCHDOG_BASE
mdefine_line|#define OMAP_WATCHDOG_BASE&t;0xfffec800
multiline_comment|/* MPU Timer Registers */
DECL|macro|CNTL_TIMER
mdefine_line|#define CNTL_TIMER&t;&t;0
DECL|macro|LOAD_TIM
mdefine_line|#define LOAD_TIM&t;&t;4
DECL|macro|READ_TIM
mdefine_line|#define READ_TIM&t;&t;8
multiline_comment|/* CNTL_TIMER register bits */
DECL|macro|MPUTIM_FREE
mdefine_line|#define MPUTIM_FREE&t;&t;(1&lt;&lt;6)
DECL|macro|MPUTIM_CLOCK_ENABLE
mdefine_line|#define MPUTIM_CLOCK_ENABLE&t;(1&lt;&lt;5)
DECL|macro|MPUTIM_PTV_MASK
mdefine_line|#define MPUTIM_PTV_MASK&t;&t;(0x7&lt;&lt;PTV_BIT)
DECL|macro|MPUTIM_PTV_BIT
mdefine_line|#define MPUTIM_PTV_BIT&t;&t;2
DECL|macro|MPUTIM_AR
mdefine_line|#define MPUTIM_AR&t;&t;(1&lt;&lt;1)
DECL|macro|MPUTIM_ST
mdefine_line|#define MPUTIM_ST&t;&t;(1&lt;&lt;0)
multiline_comment|/*&n; * ---------------------------------------------------------------------------&n; * Interrupts&n; * ---------------------------------------------------------------------------&n; */
DECL|macro|OMAP_IH1_BASE
mdefine_line|#define OMAP_IH1_BASE&t;&t;0xfffecb00
DECL|macro|OMAP_IH2_BASE
mdefine_line|#define OMAP_IH2_BASE&t;&t;0xfffe0000
DECL|macro|OMAP_ITR
mdefine_line|#define OMAP_ITR&t;&t;0x0
DECL|macro|OMAP_MASK
mdefine_line|#define OMAP_MASK&t;&t;0x4
DECL|macro|IRQ_ITR
mdefine_line|#define IRQ_ITR&t;&t;&t;0x00
DECL|macro|IRQ_MIR
mdefine_line|#define IRQ_MIR&t;&t;&t;0x04
DECL|macro|IRQ_SIR_IRQ
mdefine_line|#define IRQ_SIR_IRQ&t;&t;0x10
DECL|macro|IRQ_SIR_FIQ
mdefine_line|#define IRQ_SIR_FIQ&t;&t;0x14
DECL|macro|IRQ_CONTROL_REG
mdefine_line|#define IRQ_CONTROL_REG&t;&t;0x18
DECL|macro|IRQ_ISR
mdefine_line|#define IRQ_ISR&t;&t;&t;0x9c
DECL|macro|IRQ_ILR0
mdefine_line|#define IRQ_ILR0&t;&t;0x1c
multiline_comment|/* OMAP-1610 specific interrupt handler registers */
DECL|macro|OMAP_IH2_SECT1
mdefine_line|#define OMAP_IH2_SECT1&t;&t;(OMAP_IH2_BASE)
DECL|macro|OMAP_IH2_SECT2
mdefine_line|#define OMAP_IH2_SECT2&t;&t;(OMAP_IH2_BASE + 0x100)
DECL|macro|OMAP_IH2_SECT3
mdefine_line|#define OMAP_IH2_SECT3&t;&t;(OMAP_IH2_BASE + 0x200)
DECL|macro|OMAP_IH2_SECT4
mdefine_line|#define OMAP_IH2_SECT4&t;&t;(OMAP_IH2_BASE + 0x300)
multiline_comment|/*&n; * ---------------------------------------------------------------------------&n; * Traffic controller memory interface&n; * ---------------------------------------------------------------------------&n; */
DECL|macro|TCMIF_BASE
mdefine_line|#define TCMIF_BASE&t;&t;0xfffecc00
DECL|macro|IMIF_PRIO
mdefine_line|#define IMIF_PRIO&t;&t;(TCMIF_BASE + 0x00)
DECL|macro|EMIFS_PRIO_REG
mdefine_line|#define EMIFS_PRIO_REG&t;&t;(TCMIF_BASE + 0x04)
DECL|macro|EMIFF_PRIO_REG
mdefine_line|#define EMIFF_PRIO_REG&t;&t;(TCMIF_BASE + 0x08)
DECL|macro|EMIFS_CONFIG_REG
mdefine_line|#define EMIFS_CONFIG_REG&t;(TCMIF_BASE + 0x0c)
DECL|macro|EMIFS_CS0_CONFIG
mdefine_line|#define EMIFS_CS0_CONFIG&t;(TCMIF_BASE + 0x10)
DECL|macro|EMIFS_CS1_CONFIG
mdefine_line|#define EMIFS_CS1_CONFIG&t;(TCMIF_BASE + 0x14)
DECL|macro|EMIFS_CS2_CONFIG
mdefine_line|#define EMIFS_CS2_CONFIG&t;(TCMIF_BASE + 0x18)
DECL|macro|EMIFS_CS3_CONFIG
mdefine_line|#define EMIFS_CS3_CONFIG&t;(TCMIF_BASE + 0x1c)
DECL|macro|EMIFF_SDRAM_CONFIG
mdefine_line|#define EMIFF_SDRAM_CONFIG&t;(TCMIF_BASE + 0x20)
DECL|macro|EMIFF_MRS
mdefine_line|#define EMIFF_MRS&t;&t;(TCMIF_BASE + 0x24)
DECL|macro|TC_TIMEOUT1
mdefine_line|#define TC_TIMEOUT1&t;&t;(TCMIF_BASE + 0x28)
DECL|macro|TC_TIMEOUT2
mdefine_line|#define TC_TIMEOUT2&t;&t;(TCMIF_BASE + 0x2c)
DECL|macro|TC_TIMEOUT3
mdefine_line|#define TC_TIMEOUT3&t;&t;(TCMIF_BASE + 0x30)
DECL|macro|TC_ENDIANISM
mdefine_line|#define TC_ENDIANISM&t;&t;(TCMIF_BASE + 0x34)
DECL|macro|EMIFF_SDRAM_CONFIG_2
mdefine_line|#define EMIFF_SDRAM_CONFIG_2&t;(TCMIF_BASE + 0x3c)
DECL|macro|EMIF_CFG_DYNAMIC_WS
mdefine_line|#define EMIF_CFG_DYNAMIC_WS&t;(TCMIF_BASE + 0x40)
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * System control registers&n; * ----------------------------------------------------------------------------&n; */
DECL|macro|MOD_CONF_CTRL_0
mdefine_line|#define MOD_CONF_CTRL_0&t;&t;0xfffe1080
DECL|macro|MOD_CONF_CTRL_1
mdefine_line|#define MOD_CONF_CTRL_1&t;&t;0xfffe1110
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * Pin multiplexing registers&n; * ----------------------------------------------------------------------------&n; */
DECL|macro|FUNC_MUX_CTRL_0
mdefine_line|#define FUNC_MUX_CTRL_0&t;&t;0xfffe1000
DECL|macro|FUNC_MUX_CTRL_1
mdefine_line|#define FUNC_MUX_CTRL_1&t;&t;0xfffe1004
DECL|macro|FUNC_MUX_CTRL_2
mdefine_line|#define FUNC_MUX_CTRL_2&t;&t;0xfffe1008
DECL|macro|COMP_MODE_CTRL_0
mdefine_line|#define COMP_MODE_CTRL_0&t;0xfffe100c
DECL|macro|FUNC_MUX_CTRL_3
mdefine_line|#define FUNC_MUX_CTRL_3&t;&t;0xfffe1010
DECL|macro|FUNC_MUX_CTRL_4
mdefine_line|#define FUNC_MUX_CTRL_4&t;&t;0xfffe1014
DECL|macro|FUNC_MUX_CTRL_5
mdefine_line|#define FUNC_MUX_CTRL_5&t;&t;0xfffe1018
DECL|macro|FUNC_MUX_CTRL_6
mdefine_line|#define FUNC_MUX_CTRL_6&t;&t;0xfffe101C
DECL|macro|FUNC_MUX_CTRL_7
mdefine_line|#define FUNC_MUX_CTRL_7&t;&t;0xfffe1020
DECL|macro|FUNC_MUX_CTRL_8
mdefine_line|#define FUNC_MUX_CTRL_8&t;&t;0xfffe1024
DECL|macro|FUNC_MUX_CTRL_9
mdefine_line|#define FUNC_MUX_CTRL_9&t;&t;0xfffe1028
DECL|macro|FUNC_MUX_CTRL_A
mdefine_line|#define FUNC_MUX_CTRL_A&t;&t;0xfffe102C
DECL|macro|FUNC_MUX_CTRL_B
mdefine_line|#define FUNC_MUX_CTRL_B&t;&t;0xfffe1030
DECL|macro|FUNC_MUX_CTRL_C
mdefine_line|#define FUNC_MUX_CTRL_C&t;&t;0xfffe1034
DECL|macro|FUNC_MUX_CTRL_D
mdefine_line|#define FUNC_MUX_CTRL_D&t;&t;0xfffe1038
DECL|macro|PULL_DWN_CTRL_0
mdefine_line|#define PULL_DWN_CTRL_0&t;&t;0xfffe1040
DECL|macro|PULL_DWN_CTRL_1
mdefine_line|#define PULL_DWN_CTRL_1&t;&t;0xfffe1044
DECL|macro|PULL_DWN_CTRL_2
mdefine_line|#define PULL_DWN_CTRL_2&t;&t;0xfffe1048
DECL|macro|PULL_DWN_CTRL_3
mdefine_line|#define PULL_DWN_CTRL_3&t;&t;0xfffe104c
multiline_comment|/* OMAP-1610 specific multiplexing registers */
DECL|macro|FUNC_MUX_CTRL_E
mdefine_line|#define FUNC_MUX_CTRL_E&t;&t;0xfffe1090
DECL|macro|FUNC_MUX_CTRL_F
mdefine_line|#define FUNC_MUX_CTRL_F&t;&t;0xfffe1094
DECL|macro|FUNC_MUX_CTRL_10
mdefine_line|#define FUNC_MUX_CTRL_10&t;0xfffe1098
DECL|macro|FUNC_MUX_CTRL_11
mdefine_line|#define FUNC_MUX_CTRL_11&t;0xfffe109c
DECL|macro|FUNC_MUX_CTRL_12
mdefine_line|#define FUNC_MUX_CTRL_12&t;0xfffe10a0
DECL|macro|PU_PD_SEL_0
mdefine_line|#define PU_PD_SEL_0&t;&t;0xfffe10b4
DECL|macro|PU_PD_SEL_1
mdefine_line|#define PU_PD_SEL_1&t;&t;0xfffe10b8
DECL|macro|PU_PD_SEL_2
mdefine_line|#define PU_PD_SEL_2&t;&t;0xfffe10bc
DECL|macro|PU_PD_SEL_3
mdefine_line|#define PU_PD_SEL_3&t;&t;0xfffe10c0
DECL|macro|PU_PD_SEL_4
mdefine_line|#define PU_PD_SEL_4&t;&t;0xfffe10c4
multiline_comment|/*&n; * ---------------------------------------------------------------------------&n; * TIPB bus interface&n; * ---------------------------------------------------------------------------&n; */
DECL|macro|TIPB_PUBLIC_CNTL_BASE
mdefine_line|#define TIPB_PUBLIC_CNTL_BASE&t;&t;0xfffed300
DECL|macro|MPU_PUBLIC_TIPB_CNTL_REG
mdefine_line|#define MPU_PUBLIC_TIPB_CNTL_REG&t;(TIPB_PUBLIC_CNTL_BASE + 0x8)
DECL|macro|TIPB_PRIVATE_CNTL_BASE
mdefine_line|#define TIPB_PRIVATE_CNTL_BASE&t;&t;0xfffeca00
DECL|macro|MPU_PRIVATE_TIPB_CNTL_REG
mdefine_line|#define MPU_PRIVATE_TIPB_CNTL_REG&t;(TIPB_PRIVATE_CNTL_BASE + 0x8)
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * DSP control registers&n; * ----------------------------------------------------------------------------&n; */
multiline_comment|/*  MPUI Interface Registers */
DECL|macro|MPUI_CTRL_REG
mdefine_line|#define MPUI_CTRL_REG&t;&t;(0xfffec900)
DECL|macro|MPUI_DEBUG_ADDR
mdefine_line|#define MPUI_DEBUG_ADDR&t;&t;(0xfffec904)
DECL|macro|MPUI_DEBUG_DATA
mdefine_line|#define MPUI_DEBUG_DATA&t;&t;(0xfffec908)
DECL|macro|MPUI_DEBUG_FLAG
mdefine_line|#define MPUI_DEBUG_FLAG&t;&t;(0xfffec90c)
DECL|macro|MPUI_STATUS_REG
mdefine_line|#define MPUI_STATUS_REG&t;&t;(0xfffec910)
DECL|macro|MPUI_DSP_STATUS_REG
mdefine_line|#define MPUI_DSP_STATUS_REG&t;(0xfffec914)
DECL|macro|MPUI_DSP_BOOT_CONFIG
mdefine_line|#define MPUI_DSP_BOOT_CONFIG&t;(0xfffec918)
DECL|macro|MPUI_DSP_API_CONFIG
mdefine_line|#define MPUI_DSP_API_CONFIG&t;(0xfffec91c)
macro_line|#ifndef __ASSEMBLER__
multiline_comment|/*&n; * ---------------------------------------------------------------------------&n; * Processor differentiation&n; * ---------------------------------------------------------------------------&n; */
DECL|macro|OMAP_ID_REG
mdefine_line|#define OMAP_ID_REG&t;&t;__REG32(0xfffed404)
macro_line|#ifdef CONFIG_ARCH_OMAP730
macro_line|#include &quot;omap730.h&quot;
DECL|macro|cpu_is_omap730
mdefine_line|#define cpu_is_omap730()&t;(((OMAP_ID_REG &gt;&gt; 12) &amp; 0xffff) == 0xB55F)
macro_line|#else
DECL|macro|cpu_is_omap730
mdefine_line|#define cpu_is_omap730()&t;0
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_OMAP1510
macro_line|#include &quot;omap1510.h&quot;
DECL|macro|cpu_is_omap1510
mdefine_line|#define cpu_is_omap1510()&t;(((OMAP_ID_REG &gt;&gt; 12) &amp; 0xffff) == 0xB470)
macro_line|#else
DECL|macro|cpu_is_omap1510
mdefine_line|#define cpu_is_omap1510()&t;0
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_OMAP1610
macro_line|#include &quot;omap1610.h&quot;
DECL|macro|cpu_is_omap1710
mdefine_line|#define cpu_is_omap1710()       (((OMAP_ID_REG &gt;&gt; 12) &amp; 0xffff) == 0xB5F7)
multiline_comment|/* Detect 1710 as 1610 for now */
DECL|macro|cpu_is_omap1610
mdefine_line|#define cpu_is_omap1610()&t;(((OMAP_ID_REG &gt;&gt; 12) &amp; 0xffff) == 0xB576 || &bslash;&n;&t;&t;&t;&t; cpu_is_omap1710())
macro_line|#else
DECL|macro|cpu_is_omap1610
mdefine_line|#define cpu_is_omap1610()&t;0
DECL|macro|cpu_is_omap1710
mdefine_line|#define cpu_is_omap1710()&t;0
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_OMAP5912
macro_line|#include &quot;omap5912.h&quot;
DECL|macro|cpu_is_omap5912
mdefine_line|#define cpu_is_omap5912()&t;(((OMAP_ID_REG &gt;&gt; 12) &amp; 0xffff) == 0xB58C)
macro_line|#else
DECL|macro|cpu_is_omap5912
mdefine_line|#define cpu_is_omap5912()&t;0
macro_line|#endif
multiline_comment|/*&n; * ---------------------------------------------------------------------------&n; * Board differentiation&n; * ---------------------------------------------------------------------------&n; */
macro_line|#ifdef CONFIG_MACH_OMAP_INNOVATOR
macro_line|#include &quot;board-innovator.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_MACH_OMAP_H2
macro_line|#include &quot;board-h2.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_MACH_OMAP_PERSEUS2
macro_line|#include &quot;board-perseus2.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_MACH_OMAP_H3
macro_line|#include &quot;board-h3.h&quot;
macro_line|#error &quot;Support for H3 board not yet implemented.&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_MACH_OMAP_H4
macro_line|#include &quot;board-h4.h&quot;
macro_line|#error &quot;Support for H4 board not yet implemented.&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_MACH_OMAP_OSK
macro_line|#include &quot;board-osk.h&quot;
macro_line|#endif
macro_line|#endif /* !__ASSEMBLER__ */
macro_line|#endif&t;/* __ASM_ARCH_OMAP_HARDWARE_H */
eof
