multiline_comment|/*&n; * FILE NAME include/asm/arch-omap/pm.h&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&n; * Author: MontaVista Software, Inc.&n; *&t;   support@mvista.com&n; *&n; * Copyright 2002 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n; * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF&n; * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/*&n; * List of global OMAP registers to preserve.  All registers are 16 bits&n; * and must be accessed with 16 read/writes.&n; * More ones like CP and general purpose register values are preserved&n; * with the stack pointer in sleep.S.&n; */
macro_line|#ifndef __ASM_ARCH_OMAP_PM_H
DECL|macro|__ASM_ARCH_OMAP_PM_H
mdefine_line|#define __ASM_ARCH_OMAP_PM_H
DECL|macro|ARM_REG_BASE
mdefine_line|#define ARM_REG_BASE&t;&t;(0xfffece00)
DECL|macro|ARM_ASM_IDLECT1
mdefine_line|#define ARM_ASM_IDLECT1&t;&t;(ARM_REG_BASE + 0x4)
DECL|macro|ARM_ASM_IDLECT2
mdefine_line|#define ARM_ASM_IDLECT2&t;&t;(ARM_REG_BASE + 0x8)
DECL|macro|ARM_ASM_RSTCT1
mdefine_line|#define ARM_ASM_RSTCT1&t;&t;(ARM_REG_BASE + 0x10)
DECL|macro|ARM_ASM_RSTCT2
mdefine_line|#define ARM_ASM_RSTCT2&t;&t;(ARM_REG_BASE + 0x14)
DECL|macro|ARM_ASM_SYSST
mdefine_line|#define ARM_ASM_SYSST&t;&t;(ARM_REG_BASE + 0x18)
multiline_comment|/*&n; * Traffic Controller Memory Interface Registers&n; */
DECL|macro|TCMIF_BASE
mdefine_line|#define TCMIF_BASE&t;&t;0xfffecc00
DECL|macro|EMIFS_ASM_CONFIG_REG
mdefine_line|#define EMIFS_ASM_CONFIG_REG&t;(TCMIF_BASE + 0x0c)
DECL|macro|EMIFF_ASM_SDRAM_CONFIG
mdefine_line|#define EMIFF_ASM_SDRAM_CONFIG&t;(TCMIF_BASE + 0x20)
DECL|macro|IRQ_MIR1
mdefine_line|#define IRQ_MIR1&t;&t;(OMAP_IH1_BASE + IRQ_MIR)
macro_line|#ifdef CONFIG_ARCH_OMAP1510
DECL|macro|IRQ_MIR2
mdefine_line|#define IRQ_MIR2&t;&t;(OMAP_IH2_BASE + IRQ_MIR)
macro_line|#else /* CONFIG_ARCH_OMAP1610 */
DECL|macro|IRQ_MIR2_0
mdefine_line|#define IRQ_MIR2_0&t;&t;(OMAP_IH2_0_BASE + IRQ_MIR)
DECL|macro|IRQ_MIR2_1
mdefine_line|#define IRQ_MIR2_1&t;&t;(OMAP_IH2_1_BASE + IRQ_MIR)
DECL|macro|IRQ_MIR2_2
mdefine_line|#define IRQ_MIR2_2&t;&t;(OMAP_IH2_2_BASE + IRQ_MIR)
DECL|macro|IRQ_MIR2_3
mdefine_line|#define IRQ_MIR2_3&t;&t;(OMAP_IH2_3_BASE + IRQ_MIR)
macro_line|#endif
DECL|macro|IDLE_WAIT_CYCLES
mdefine_line|#define IDLE_WAIT_CYCLES&t;&t;0x00000fff
DECL|macro|PERIPHERAL_ENABLE
mdefine_line|#define PERIPHERAL_ENABLE&t;&t;0x2
macro_line|#ifdef CONFIG_ARCH_OMAP1510
DECL|macro|DEEP_SLEEP_REQUEST
mdefine_line|#define DEEP_SLEEP_REQUEST&t;&t;0x0ec7
DECL|macro|BIG_SLEEP_REQUEST
mdefine_line|#define BIG_SLEEP_REQUEST&t;&t;0x0cc5
DECL|macro|IDLE_LOOP_REQUEST
mdefine_line|#define IDLE_LOOP_REQUEST&t;&t;0x0c00
DECL|macro|IDLE_CLOCK_DOMAINS
mdefine_line|#define IDLE_CLOCK_DOMAINS&t;&t;0x2
macro_line|#else /* CONFIG_ARCH_OMAP1610 */
DECL|macro|DEEP_SLEEP_REQUEST
mdefine_line|#define DEEP_SLEEP_REQUEST&t;&t;0x17c7
DECL|macro|BIG_SLEEP_REQUEST
mdefine_line|#define BIG_SLEEP_REQUEST&t;&t;TBD
DECL|macro|IDLE_LOOP_REQUEST
mdefine_line|#define IDLE_LOOP_REQUEST&t;&t;0x0400
DECL|macro|IDLE_CLOCK_DOMAINS
mdefine_line|#define IDLE_CLOCK_DOMAINS&t;&t;0x09c7
macro_line|#endif
DECL|macro|SELF_REFRESH_MODE
mdefine_line|#define SELF_REFRESH_MODE&t;&t;0x0c000001
DECL|macro|IDLE_EMIFS_REQUEST
mdefine_line|#define IDLE_EMIFS_REQUEST&t;&t;0xc
DECL|macro|MODEM_32K_EN
mdefine_line|#define MODEM_32K_EN&t;&t;&t;0x1
macro_line|#ifndef __ASSEMBLER__
r_extern
r_void
id|omap_pm_idle
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|omap_pm_suspend
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|omap_cpu_suspend
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|omap_idle_loop_suspend
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ARCH_OMAP1510
DECL|macro|OMAP_SRAM_IDLE_SUSPEND
mdefine_line|#define OMAP_SRAM_IDLE_SUSPEND&t;0xd002F000
DECL|macro|OMAP_SRAM_API_SUSPEND
mdefine_line|#define OMAP_SRAM_API_SUSPEND&t;0xd002F200
macro_line|#else /* CONFIG_ARCH_OMAP1610 */
DECL|macro|OMAP_SRAM_IDLE_SUSPEND
mdefine_line|#define OMAP_SRAM_IDLE_SUSPEND&t;0xd0000400
DECL|macro|OMAP_SRAM_API_SUSPEND
mdefine_line|#define OMAP_SRAM_API_SUSPEND&t;0xd0000600
macro_line|#endif
DECL|macro|CPU_SUSPEND_SIZE
mdefine_line|#define CPU_SUSPEND_SIZE&t;200
DECL|macro|ARM_REG_BASE
mdefine_line|#define ARM_REG_BASE&t;&t;(0xfffece00)
DECL|macro|ARM_ASM_IDLECT1
mdefine_line|#define ARM_ASM_IDLECT1&t;&t;(ARM_REG_BASE + 0x4)
DECL|macro|ARM_ASM_IDLECT2
mdefine_line|#define ARM_ASM_IDLECT2&t;&t;(ARM_REG_BASE + 0x8)
DECL|macro|ARM_ASM_RSTCT1
mdefine_line|#define ARM_ASM_RSTCT1&t;&t;(ARM_REG_BASE + 0x10)
DECL|macro|ARM_ASM_RSTCT2
mdefine_line|#define ARM_ASM_RSTCT2&t;&t;(ARM_REG_BASE + 0x14)
DECL|macro|ARM_ASM_SYSST
mdefine_line|#define ARM_ASM_SYSST&t;&t;(ARM_REG_BASE + 0x18)
DECL|macro|TCMIF_BASE
mdefine_line|#define TCMIF_BASE&t;&t;0xfffecc00
DECL|macro|PM_EMIFS_CONFIG_REG
mdefine_line|#define PM_EMIFS_CONFIG_REG&t;(TCMIF_BASE + 0x0c)
DECL|macro|PM_EMIFF_SDRAM_CONFIG
mdefine_line|#define PM_EMIFF_SDRAM_CONFIG&t;(TCMIF_BASE + 0x20)
DECL|macro|FUNC_MUX_CTRL_LOW_PWR
mdefine_line|#define FUNC_MUX_CTRL_LOW_PWR&t;(0xfffe1020)
macro_line|#ifdef CONFIG_ARCH_OMAP1510
DECL|macro|ULPD_LOW_POWER_REQ
mdefine_line|#define ULPD_LOW_POWER_REQ             0x0001
macro_line|#else /* CONFIG_ARCH_OMAP1610 */
DECL|macro|ULPD_LOW_POWER_REQ
mdefine_line|#define ULPD_LOW_POWER_REQ             0x3
macro_line|#endif
DECL|macro|ULPD_LOW_PWR
mdefine_line|#define ULPD_LOW_PWR                   0x1000
DECL|macro|ULPD_LOW_POWER_EN
mdefine_line|#define ULPD_LOW_POWER_EN              0x0001
DECL|macro|DSP_IDLE_DELAY
mdefine_line|#define DSP_IDLE_DELAY&t;&t;&t;10
DECL|macro|DSP_IDLE
mdefine_line|#define DSP_IDLE&t;&t;&t;0x0040
DECL|macro|DSP_ENABLE
mdefine_line|#define DSP_ENABLE&t;&t;&t;0x0002
DECL|macro|SUFFICIENT_DSP_RESET_TIME
mdefine_line|#define SUFFICIENT_DSP_RESET_TIME&t;1000
DECL|macro|DEFAULT_MPUI_CONFIG
mdefine_line|#define DEFAULT_MPUI_CONFIG&t;&t;0x05cf
DECL|macro|ENABLE_XORCLK
mdefine_line|#define ENABLE_XORCLK&t;&t;&t;0x2
DECL|macro|DSP_RESET
mdefine_line|#define DSP_RESET&t;&t;&t;0x2000
DECL|macro|TC_IDLE_REQUEST
mdefine_line|#define TC_IDLE_REQUEST&t;&t;&t;(0x0000000c)
DECL|macro|EMIFF_CONFIG_REG
mdefine_line|#define EMIFF_CONFIG_REG&t;&t;EMIFF_SDRAM_CONFIG
DECL|macro|ARM_SAVE
mdefine_line|#define ARM_SAVE(x) arm_sleep_save[ARM_SLEEP_SAVE_##x] = omap_readw(x)
DECL|macro|ARM_RESTORE
mdefine_line|#define ARM_RESTORE(x) omap_writew((unsigned short)arm_sleep_save[ARM_SLEEP_SAVE_##x], x)
DECL|macro|ARM_SHOW
mdefine_line|#define ARM_SHOW(x) arm_sleep_save[ARM_SLEEP_SAVE_##x]
DECL|macro|ULPD_SAVE
mdefine_line|#define ULPD_SAVE(x) ulpd_sleep_save[ULPD_SLEEP_SAVE_##x] = omap_readw(x)
DECL|macro|ULPD_RESTORE
mdefine_line|#define ULPD_RESTORE(x) omap_writew((unsigned short)ulpd_sleep_save[ULPD_SLEEP_SAVE_##x], x)
DECL|macro|ULPD_SHOW
mdefine_line|#define ULPD_SHOW(x) ulpd_sleep_save[ULPD_SLEEP_SAVE_##x]
DECL|macro|MPUI_SAVE
mdefine_line|#define MPUI_SAVE(x) mpui_sleep_save[MPUI_SLEEP_SAVE_##x] = omap_readl(x)
DECL|macro|MPUI_RESTORE
mdefine_line|#define MPUI_RESTORE(x) omap_writel((unsigned int)mpui_sleep_save[MPUI_SLEEP_SAVE_##x], x)
DECL|macro|MPUI_SHOW
mdefine_line|#define MPUI_SHOW(x) (unsigned int)mpui_sleep_save[MPUI_SLEEP_SAVE_##x]
DECL|enum|arm_save_state
r_enum
id|arm_save_state
(brace
DECL|enumerator|ARM_SLEEP_SAVE_START
id|ARM_SLEEP_SAVE_START
op_assign
l_int|0
comma
multiline_comment|/*&n;&t; * 9 MPU control registers, all 16 bits&n;&t; */
DECL|enumerator|ARM_SLEEP_SAVE_ARM_CKCTL
DECL|enumerator|ARM_SLEEP_SAVE_ARM_IDLECT1
id|ARM_SLEEP_SAVE_ARM_CKCTL
comma
id|ARM_SLEEP_SAVE_ARM_IDLECT1
comma
DECL|enumerator|ARM_SLEEP_SAVE_ARM_IDLECT2
DECL|enumerator|ARM_SLEEP_SAVE_ARM_EWUPCT
id|ARM_SLEEP_SAVE_ARM_IDLECT2
comma
id|ARM_SLEEP_SAVE_ARM_EWUPCT
comma
DECL|enumerator|ARM_SLEEP_SAVE_ARM_RSTCT1
DECL|enumerator|ARM_SLEEP_SAVE_ARM_RSTCT2
id|ARM_SLEEP_SAVE_ARM_RSTCT1
comma
id|ARM_SLEEP_SAVE_ARM_RSTCT2
comma
DECL|enumerator|ARM_SLEEP_SAVE_ARM_SYSST
id|ARM_SLEEP_SAVE_ARM_SYSST
comma
DECL|enumerator|ARM_SLEEP_SAVE_SIZE
id|ARM_SLEEP_SAVE_SIZE
)brace
suffix:semicolon
DECL|enum|ulpd_save_state
r_enum
id|ulpd_save_state
(brace
DECL|enumerator|ULPD_SLEEP_SAVE_START
id|ULPD_SLEEP_SAVE_START
op_assign
l_int|0
comma
DECL|enumerator|ULPD_SLEEP_SAVE_ULPD_IT_STATUS_REG
DECL|enumerator|ULPD_SLEEP_SAVE_ULPD_CLOCK_CTRL_REG
id|ULPD_SLEEP_SAVE_ULPD_IT_STATUS_REG
comma
id|ULPD_SLEEP_SAVE_ULPD_CLOCK_CTRL_REG
comma
DECL|enumerator|ULPD_SLEEP_SAVE_ULPD_SOFT_REQ_REG
DECL|enumerator|ULPD_SLEEP_SAVE_ULPD_STATUS_REQ_REG
id|ULPD_SLEEP_SAVE_ULPD_SOFT_REQ_REG
comma
id|ULPD_SLEEP_SAVE_ULPD_STATUS_REQ_REG
comma
DECL|enumerator|ULPD_SLEEP_SAVE_ULPD_DPLL_CTRL_REG
DECL|enumerator|ULPD_SLEEP_SAVE_ULPD_POWER_CTRL_REG
id|ULPD_SLEEP_SAVE_ULPD_DPLL_CTRL_REG
comma
id|ULPD_SLEEP_SAVE_ULPD_POWER_CTRL_REG
comma
DECL|enumerator|ULPD_SLEEP_SAVE_SIZE
id|ULPD_SLEEP_SAVE_SIZE
)brace
suffix:semicolon
DECL|enum|mpui_save_state
r_enum
id|mpui_save_state
(brace
multiline_comment|/*&n;&t; * MPUI registers 32 bits&n;&t; */
DECL|enumerator|MPUI_SLEEP_SAVE_MPUI_CTRL_REG
DECL|enumerator|MPUI_SLEEP_SAVE_MPUI_DSP_BOOT_CONFIG
id|MPUI_SLEEP_SAVE_MPUI_CTRL_REG
comma
id|MPUI_SLEEP_SAVE_MPUI_DSP_BOOT_CONFIG
comma
DECL|enumerator|MPUI_SLEEP_SAVE_MPUI_DSP_API_CONFIG
id|MPUI_SLEEP_SAVE_MPUI_DSP_API_CONFIG
comma
DECL|enumerator|MPUI_SLEEP_SAVE_MPUI_DSP_STATUS_REG
id|MPUI_SLEEP_SAVE_MPUI_DSP_STATUS_REG
comma
DECL|enumerator|MPUI_SLEEP_SAVE_PM_EMIFF_SDRAM_CONFIG
id|MPUI_SLEEP_SAVE_PM_EMIFF_SDRAM_CONFIG
comma
DECL|enumerator|MPUI_SLEEP_SAVE_PM_EMIFS_CONFIG_REG
id|MPUI_SLEEP_SAVE_PM_EMIFS_CONFIG_REG
comma
DECL|enumerator|MPUI_SLEEP_SAVE_IRQ_MIR1
id|MPUI_SLEEP_SAVE_IRQ_MIR1
comma
macro_line|#ifdef CONFIG_ARCH_OMAP1510
DECL|enumerator|MPUI_SLEEP_SAVE_IRQ_MIR2
id|MPUI_SLEEP_SAVE_IRQ_MIR2
comma
macro_line|#else /* CONFIG_ARCH_OMAP1610 */
id|MPUI_SLEEP_SAVE_IRQ_MIR2_0
comma
id|MPUI_SLEEP_SAVE_IRQ_MIR2_1
comma
id|MPUI_SLEEP_SAVE_IRQ_MIR2_2
comma
id|MPUI_SLEEP_SAVE_IRQ_MIR2_3
comma
macro_line|#endif
DECL|enumerator|MPUI_SLEEP_SAVE_SIZE
id|MPUI_SLEEP_SAVE_SIZE
)brace
suffix:semicolon
macro_line|#endif&t;/* ASSEMBLER */
macro_line|#endif
eof
