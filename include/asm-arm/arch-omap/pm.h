multiline_comment|/*&n; * linux/include/asm/arch-omap/pm.h&n; *&n; * Header file for OMAP Power Management Routines&n; *&n; * Author: MontaVista Software, Inc.&n; *&t;   support@mvista.com&n; *&n; * Copyright 2002 MontaVista Software Inc.&n; *&n; * Cleanup 2004 for Linux 2.6 by Dirk Behme &lt;dirk.behme@de.bosch.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n; * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF&n; * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __ASM_ARCH_OMAP_PM_H
DECL|macro|__ASM_ARCH_OMAP_PM_H
mdefine_line|#define __ASM_ARCH_OMAP_PM_H
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * Register and offset definitions to be used in PM assembler code&n; * ----------------------------------------------------------------------------&n; */
DECL|macro|CLKGEN_REG_ASM_BASE
mdefine_line|#define CLKGEN_REG_ASM_BASE&t;&t;io_p2v(0xfffece00)
DECL|macro|ARM_IDLECT1_ASM_OFFSET
mdefine_line|#define ARM_IDLECT1_ASM_OFFSET&t;&t;0x04
DECL|macro|ARM_IDLECT2_ASM_OFFSET
mdefine_line|#define ARM_IDLECT2_ASM_OFFSET&t;&t;0x08
DECL|macro|TCMIF_ASM_BASE
mdefine_line|#define TCMIF_ASM_BASE&t;&t;&t;io_p2v(0xfffecc00)
DECL|macro|EMIFS_CONFIG_ASM_OFFSET
mdefine_line|#define EMIFS_CONFIG_ASM_OFFSET&t;&t;0x0c
DECL|macro|EMIFF_SDRAM_CONFIG_ASM_OFFSET
mdefine_line|#define EMIFF_SDRAM_CONFIG_ASM_OFFSET&t;0x20
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * Powermanagement bitmasks&n; * ----------------------------------------------------------------------------&n; */
DECL|macro|IDLE_WAIT_CYCLES
mdefine_line|#define IDLE_WAIT_CYCLES&t;&t;0x00000fff
DECL|macro|PERIPHERAL_ENABLE
mdefine_line|#define PERIPHERAL_ENABLE&t;&t;0x2
DECL|macro|SELF_REFRESH_MODE
mdefine_line|#define SELF_REFRESH_MODE&t;&t;0x0c000001
DECL|macro|IDLE_EMIFS_REQUEST
mdefine_line|#define IDLE_EMIFS_REQUEST&t;&t;0xc
DECL|macro|MODEM_32K_EN
mdefine_line|#define MODEM_32K_EN&t;&t;&t;0x1
DECL|macro|PER_EN
mdefine_line|#define PER_EN&t;&t;&t;&t;0x1
DECL|macro|CPU_SUSPEND_SIZE
mdefine_line|#define CPU_SUSPEND_SIZE&t;&t;200
DECL|macro|ULPD_LOW_POWER_EN
mdefine_line|#define ULPD_LOW_POWER_EN&t;&t;0x0001
DECL|macro|DSP_IDLE_DELAY
mdefine_line|#define DSP_IDLE_DELAY&t;&t;&t;10
DECL|macro|DSP_IDLE
mdefine_line|#define DSP_IDLE&t;&t;&t;0x0040
DECL|macro|DSP_RST
mdefine_line|#define DSP_RST&t;&t;&t;&t;0x0004
DECL|macro|DSP_ENABLE
mdefine_line|#define DSP_ENABLE&t;&t;&t;0x0002
DECL|macro|SUFFICIENT_DSP_RESET_TIME
mdefine_line|#define SUFFICIENT_DSP_RESET_TIME&t;1000
DECL|macro|DEFAULT_MPUI_CONFIG
mdefine_line|#define DEFAULT_MPUI_CONFIG&t;&t;0x05cf
DECL|macro|ENABLE_XORCLK
mdefine_line|#define ENABLE_XORCLK&t;&t;&t;0x2
DECL|macro|DSP_CLOCK_ENABLE
mdefine_line|#define DSP_CLOCK_ENABLE&t;&t;0x2000
DECL|macro|DSP_IDLE_MODE
mdefine_line|#define DSP_IDLE_MODE&t;&t;&t;0x2
DECL|macro|TC_IDLE_REQUEST
mdefine_line|#define TC_IDLE_REQUEST&t;&t;&t;(0x0000000c)
DECL|macro|IRQ_LEVEL2
mdefine_line|#define IRQ_LEVEL2&t;&t;&t;(1&lt;&lt;0)
DECL|macro|IRQ_KEYBOARD
mdefine_line|#define IRQ_KEYBOARD&t;&t;&t;(1&lt;&lt;1)
DECL|macro|IRQ_UART2
mdefine_line|#define IRQ_UART2&t;&t;&t;(1&lt;&lt;15)
DECL|macro|PDE_BIT
mdefine_line|#define PDE_BIT&t;&t;&t;&t;0x08
DECL|macro|PWD_EN_BIT
mdefine_line|#define PWD_EN_BIT&t;&t;&t;0x04
DECL|macro|EN_PERCK_BIT
mdefine_line|#define EN_PERCK_BIT&t;&t;&t;0x04
DECL|macro|OMAP1510_DEEP_SLEEP_REQUEST
mdefine_line|#define OMAP1510_DEEP_SLEEP_REQUEST&t;0x0ec7
DECL|macro|OMAP1510_BIG_SLEEP_REQUEST
mdefine_line|#define OMAP1510_BIG_SLEEP_REQUEST&t;0x0cc5
DECL|macro|OMAP1510_IDLE_LOOP_REQUEST
mdefine_line|#define OMAP1510_IDLE_LOOP_REQUEST&t;0x0c00
DECL|macro|OMAP1510_IDLE_CLOCK_DOMAINS
mdefine_line|#define OMAP1510_IDLE_CLOCK_DOMAINS&t;0x2
DECL|macro|OMAP1510_ULPD_LOW_POWER_REQ
mdefine_line|#define OMAP1510_ULPD_LOW_POWER_REQ&t;0x0001
DECL|macro|OMAP1610_DEEP_SLEEP_REQUEST
mdefine_line|#define OMAP1610_DEEP_SLEEP_REQUEST&t;0x17c7
DECL|macro|OMAP1610_BIG_SLEEP_REQUEST
mdefine_line|#define OMAP1610_BIG_SLEEP_REQUEST&t;TBD
DECL|macro|OMAP1610_IDLE_LOOP_REQUEST
mdefine_line|#define OMAP1610_IDLE_LOOP_REQUEST&t;0x0400
DECL|macro|OMAP1610_IDLE_CLOCK_DOMAINS
mdefine_line|#define OMAP1610_IDLE_CLOCK_DOMAINS&t;0x09c7
DECL|macro|OMAP1610_ULPD_LOW_POWER_REQ
mdefine_line|#define OMAP1610_ULPD_LOW_POWER_REQ&t;0x3
macro_line|#ifndef OMAP1510_SRAM_IDLE_SUSPEND
DECL|macro|OMAP1510_SRAM_IDLE_SUSPEND
mdefine_line|#define OMAP1510_SRAM_IDLE_SUSPEND 0
macro_line|#endif
macro_line|#ifndef OMAP1610_SRAM_IDLE_SUSPEND
DECL|macro|OMAP1610_SRAM_IDLE_SUSPEND
mdefine_line|#define OMAP1610_SRAM_IDLE_SUSPEND 0
macro_line|#endif
macro_line|#ifndef OMAP5912_SRAM_IDLE_SUSPEND
DECL|macro|OMAP5912_SRAM_IDLE_SUSPEND
mdefine_line|#define OMAP5912_SRAM_IDLE_SUSPEND 0
macro_line|#endif
macro_line|#ifndef OMAP1510_SRAM_API_SUSPEND
DECL|macro|OMAP1510_SRAM_API_SUSPEND
mdefine_line|#define OMAP1510_SRAM_API_SUSPEND 0
macro_line|#endif
macro_line|#ifndef OMAP1610_SRAM_API_SUSPEND
DECL|macro|OMAP1610_SRAM_API_SUSPEND
mdefine_line|#define OMAP1610_SRAM_API_SUSPEND 0
macro_line|#endif
macro_line|#ifndef OMAP5912_SRAM_API_SUSPEND
DECL|macro|OMAP5912_SRAM_API_SUSPEND
mdefine_line|#define OMAP5912_SRAM_API_SUSPEND 0
macro_line|#endif
macro_line|#if     !defined(CONFIG_ARCH_OMAP1510) &amp;&amp; &bslash;&n;&t;!defined(CONFIG_ARCH_OMAP16XX)
macro_line|#error &quot;Power management for this processor not implemented yet&quot;
macro_line|#endif
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
id|omap1510_cpu_suspend
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
id|omap1610_cpu_suspend
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
id|omap1510_idle_loop_suspend
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|omap1610_idle_loop_suspend
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|omap1510_cpu_suspend_sz
suffix:semicolon
r_extern
r_int
r_int
id|omap1510_idle_loop_suspend_sz
suffix:semicolon
r_extern
r_int
r_int
id|omap1610_cpu_suspend_sz
suffix:semicolon
r_extern
r_int
r_int
id|omap1610_idle_loop_suspend_sz
suffix:semicolon
DECL|macro|ARM_SAVE
mdefine_line|#define ARM_SAVE(x) arm_sleep_save[ARM_SLEEP_SAVE_##x] = omap_readl(x)
DECL|macro|ARM_RESTORE
mdefine_line|#define ARM_RESTORE(x) omap_writel((arm_sleep_save[ARM_SLEEP_SAVE_##x]), (x))
DECL|macro|ARM_SHOW
mdefine_line|#define ARM_SHOW(x) arm_sleep_save[ARM_SLEEP_SAVE_##x]
DECL|macro|ULPD_SAVE
mdefine_line|#define ULPD_SAVE(x) ulpd_sleep_save[ULPD_SLEEP_SAVE_##x] = omap_readw(x)
DECL|macro|ULPD_RESTORE
mdefine_line|#define ULPD_RESTORE(x) omap_writew((ulpd_sleep_save[ULPD_SLEEP_SAVE_##x]), (x))
DECL|macro|ULPD_SHOW
mdefine_line|#define ULPD_SHOW(x) ulpd_sleep_save[ULPD_SLEEP_SAVE_##x]
DECL|macro|MPUI1510_SAVE
mdefine_line|#define MPUI1510_SAVE(x) mpui1510_sleep_save[MPUI1510_SLEEP_SAVE_##x] = omap_readl(x)
DECL|macro|MPUI1510_RESTORE
mdefine_line|#define MPUI1510_RESTORE(x) omap_writel((mpui1510_sleep_save[MPUI1510_SLEEP_SAVE_##x]), (x))
DECL|macro|MPUI1510_SHOW
mdefine_line|#define MPUI1510_SHOW(x) mpui1510_sleep_save[MPUI1510_SLEEP_SAVE_##x]
DECL|macro|MPUI1610_SAVE
mdefine_line|#define MPUI1610_SAVE(x) mpui1610_sleep_save[MPUI1610_SLEEP_SAVE_##x] = omap_readl(x)
DECL|macro|MPUI1610_RESTORE
mdefine_line|#define MPUI1610_RESTORE(x) omap_writel((mpui1610_sleep_save[MPUI1610_SLEEP_SAVE_##x]), (x))
DECL|macro|MPUI1610_SHOW
mdefine_line|#define MPUI1610_SHOW(x) mpui1610_sleep_save[MPUI1610_SLEEP_SAVE_##x]
multiline_comment|/*&n; * List of global OMAP registers to preserve.&n; * More ones like CP and general purpose register values are preserved&n; * with the stack pointer in sleep.S.&n; */
DECL|enum|arm_save_state
r_enum
id|arm_save_state
(brace
DECL|enumerator|ARM_SLEEP_SAVE_START
id|ARM_SLEEP_SAVE_START
op_assign
l_int|0
comma
multiline_comment|/*&n;&t; * MPU control registers 32 bits&n;&t; */
DECL|enumerator|ARM_SLEEP_SAVE_ARM_CKCTL
id|ARM_SLEEP_SAVE_ARM_CKCTL
comma
DECL|enumerator|ARM_SLEEP_SAVE_ARM_IDLECT1
id|ARM_SLEEP_SAVE_ARM_IDLECT1
comma
DECL|enumerator|ARM_SLEEP_SAVE_ARM_IDLECT2
id|ARM_SLEEP_SAVE_ARM_IDLECT2
comma
DECL|enumerator|ARM_SLEEP_SAVE_ARM_EWUPCT
id|ARM_SLEEP_SAVE_ARM_EWUPCT
comma
DECL|enumerator|ARM_SLEEP_SAVE_ARM_RSTCT1
id|ARM_SLEEP_SAVE_ARM_RSTCT1
comma
DECL|enumerator|ARM_SLEEP_SAVE_ARM_RSTCT2
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
multiline_comment|/*&n;&t; * ULPD registers 16 bits&n;&t; */
DECL|enumerator|ULPD_SLEEP_SAVE_ULPD_IT_STATUS
id|ULPD_SLEEP_SAVE_ULPD_IT_STATUS
comma
DECL|enumerator|ULPD_SLEEP_SAVE_ULPD_CLOCK_CTRL
id|ULPD_SLEEP_SAVE_ULPD_CLOCK_CTRL
comma
DECL|enumerator|ULPD_SLEEP_SAVE_ULPD_SOFT_REQ
id|ULPD_SLEEP_SAVE_ULPD_SOFT_REQ
comma
DECL|enumerator|ULPD_SLEEP_SAVE_ULPD_STATUS_REQ
id|ULPD_SLEEP_SAVE_ULPD_STATUS_REQ
comma
DECL|enumerator|ULPD_SLEEP_SAVE_ULPD_DPLL_CTRL
id|ULPD_SLEEP_SAVE_ULPD_DPLL_CTRL
comma
DECL|enumerator|ULPD_SLEEP_SAVE_ULPD_POWER_CTRL
id|ULPD_SLEEP_SAVE_ULPD_POWER_CTRL
comma
DECL|enumerator|ULPD_SLEEP_SAVE_SIZE
id|ULPD_SLEEP_SAVE_SIZE
)brace
suffix:semicolon
DECL|enum|mpui1510_save_state
r_enum
id|mpui1510_save_state
(brace
DECL|enumerator|MPUI1510_SLEEP_SAVE_START
id|MPUI1510_SLEEP_SAVE_START
op_assign
l_int|0
comma
multiline_comment|/*&n;&t; * MPUI registers 32 bits&n;&t; */
DECL|enumerator|MPUI1510_SLEEP_SAVE_MPUI_CTRL
id|MPUI1510_SLEEP_SAVE_MPUI_CTRL
comma
DECL|enumerator|MPUI1510_SLEEP_SAVE_MPUI_DSP_BOOT_CONFIG
id|MPUI1510_SLEEP_SAVE_MPUI_DSP_BOOT_CONFIG
comma
DECL|enumerator|MPUI1510_SLEEP_SAVE_MPUI_DSP_API_CONFIG
id|MPUI1510_SLEEP_SAVE_MPUI_DSP_API_CONFIG
comma
DECL|enumerator|MPUI1510_SLEEP_SAVE_MPUI_DSP_STATUS
id|MPUI1510_SLEEP_SAVE_MPUI_DSP_STATUS
comma
DECL|enumerator|MPUI1510_SLEEP_SAVE_EMIFF_SDRAM_CONFIG
id|MPUI1510_SLEEP_SAVE_EMIFF_SDRAM_CONFIG
comma
DECL|enumerator|MPUI1510_SLEEP_SAVE_EMIFS_CONFIG
id|MPUI1510_SLEEP_SAVE_EMIFS_CONFIG
comma
DECL|enumerator|MPUI1510_SLEEP_SAVE_OMAP_IH1_MIR
id|MPUI1510_SLEEP_SAVE_OMAP_IH1_MIR
comma
DECL|enumerator|MPUI1510_SLEEP_SAVE_OMAP_IH2_MIR
id|MPUI1510_SLEEP_SAVE_OMAP_IH2_MIR
comma
macro_line|#if defined(CONFIG_ARCH_OMAP1510)
DECL|enumerator|MPUI1510_SLEEP_SAVE_SIZE
id|MPUI1510_SLEEP_SAVE_SIZE
macro_line|#else
id|MPUI1510_SLEEP_SAVE_SIZE
op_assign
l_int|0
macro_line|#endif
)brace
suffix:semicolon
DECL|enum|mpui1610_save_state
r_enum
id|mpui1610_save_state
(brace
DECL|enumerator|MPUI1610_SLEEP_SAVE_START
id|MPUI1610_SLEEP_SAVE_START
op_assign
l_int|0
comma
multiline_comment|/*&n;&t; * MPUI registers 32 bits&n;&t; */
DECL|enumerator|MPUI1610_SLEEP_SAVE_MPUI_CTRL
id|MPUI1610_SLEEP_SAVE_MPUI_CTRL
comma
DECL|enumerator|MPUI1610_SLEEP_SAVE_MPUI_DSP_BOOT_CONFIG
id|MPUI1610_SLEEP_SAVE_MPUI_DSP_BOOT_CONFIG
comma
DECL|enumerator|MPUI1610_SLEEP_SAVE_MPUI_DSP_API_CONFIG
id|MPUI1610_SLEEP_SAVE_MPUI_DSP_API_CONFIG
comma
DECL|enumerator|MPUI1610_SLEEP_SAVE_MPUI_DSP_STATUS
id|MPUI1610_SLEEP_SAVE_MPUI_DSP_STATUS
comma
DECL|enumerator|MPUI1610_SLEEP_SAVE_EMIFF_SDRAM_CONFIG
id|MPUI1610_SLEEP_SAVE_EMIFF_SDRAM_CONFIG
comma
DECL|enumerator|MPUI1610_SLEEP_SAVE_EMIFS_CONFIG
id|MPUI1610_SLEEP_SAVE_EMIFS_CONFIG
comma
DECL|enumerator|MPUI1610_SLEEP_SAVE_OMAP_IH1_MIR
id|MPUI1610_SLEEP_SAVE_OMAP_IH1_MIR
comma
DECL|enumerator|MPUI1610_SLEEP_SAVE_OMAP_IH2_0_MIR
id|MPUI1610_SLEEP_SAVE_OMAP_IH2_0_MIR
comma
DECL|enumerator|MPUI1610_SLEEP_SAVE_OMAP_IH2_1_MIR
id|MPUI1610_SLEEP_SAVE_OMAP_IH2_1_MIR
comma
DECL|enumerator|MPUI1610_SLEEP_SAVE_OMAP_IH2_2_MIR
id|MPUI1610_SLEEP_SAVE_OMAP_IH2_2_MIR
comma
DECL|enumerator|MPUI1610_SLEEP_SAVE_OMAP_IH2_3_MIR
id|MPUI1610_SLEEP_SAVE_OMAP_IH2_3_MIR
comma
macro_line|#if defined(CONFIG_ARCH_OMAP16XX)
DECL|enumerator|MPUI1610_SLEEP_SAVE_SIZE
id|MPUI1610_SLEEP_SAVE_SIZE
macro_line|#else
id|MPUI1610_SLEEP_SAVE_SIZE
op_assign
l_int|0
macro_line|#endif
)brace
suffix:semicolon
macro_line|#endif /* ASSEMBLER */
macro_line|#endif /* __ASM_ARCH_OMAP_PM_H */
eof
