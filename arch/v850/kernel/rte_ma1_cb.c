multiline_comment|/*&n; * arch/v850/kernel/rte_ma1_cb.c -- Midas labs RTE-V850E/MA1-CB board&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/ma1.h&gt;
macro_line|#include &lt;asm/rte_ma1_cb.h&gt;
macro_line|#include &lt;asm/v850e_timer_c.h&gt;
macro_line|#include &quot;mach.h&quot;
multiline_comment|/* SRAM and SDRAM are almost contiguous (with a small hole in between;&n;   see mach_reserve_bootmem for details), so just use both as one big area.  */
DECL|macro|RAM_START
mdefine_line|#define RAM_START &t;SRAM_ADDR
DECL|macro|RAM_END
mdefine_line|#define RAM_END&t;&t;(SDRAM_ADDR + SDRAM_SIZE)
DECL|function|mach_early_init
r_void
id|__init
id|mach_early_init
(paren
r_void
)paren
(brace
id|rte_cb_early_init
(paren
)paren
suffix:semicolon
)brace
DECL|function|mach_get_physical_ram
r_void
id|__init
id|mach_get_physical_ram
(paren
r_int
r_int
op_star
id|ram_start
comma
r_int
r_int
op_star
id|ram_len
)paren
(brace
op_star
id|ram_start
op_assign
id|RAM_START
suffix:semicolon
op_star
id|ram_len
op_assign
id|RAM_END
op_minus
id|RAM_START
suffix:semicolon
)brace
DECL|function|mach_reserve_bootmem
r_void
id|__init
id|mach_reserve_bootmem
(paren
)paren
(brace
macro_line|#ifdef CONFIG_RTE_CB_MULTI
multiline_comment|/* Prevent the kernel from touching the monitor&squot;s scratch RAM.  */
id|reserve_bootmem
(paren
id|MON_SCRATCH_ADDR
comma
id|MON_SCRATCH_SIZE
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* The space between SRAM and SDRAM is filled with duplicate&n;&t;   images of SRAM.  Prevent the kernel from using them.  */
id|reserve_bootmem
(paren
id|SRAM_ADDR
op_plus
id|SRAM_SIZE
comma
id|SDRAM_ADDR
op_minus
(paren
id|SRAM_ADDR
op_plus
id|SRAM_SIZE
)paren
)paren
suffix:semicolon
)brace
DECL|function|mach_gettimeofday
r_void
id|mach_gettimeofday
(paren
r_struct
id|timespec
op_star
id|tv
)paren
(brace
id|tv-&gt;tv_sec
op_assign
l_int|0
suffix:semicolon
id|tv-&gt;tv_nsec
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Called before configuring an on-chip UART.  */
DECL|function|rte_ma1_cb_uart_pre_configure
r_void
id|rte_ma1_cb_uart_pre_configure
(paren
r_int
id|chan
comma
r_int
id|cflags
comma
r_int
id|baud
)paren
(brace
multiline_comment|/* The RTE-MA1-CB connects some general-purpose I/O pins on the&n;&t;   CPU to the RTS/CTS lines of UART 0&squot;s serial connection.&n;&t;   I/O pins P42 and P43 are RTS and CTS respectively.  */
r_if
c_cond
(paren
id|chan
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Put P42 &amp; P43 in I/O port mode.  */
id|MA_PORT4_PMC
op_and_assign
op_complement
l_int|0xC
suffix:semicolon
multiline_comment|/* Make P42 an output, and P43 an input.  */
id|MA_PORT4_PM
op_assign
(paren
id|MA_PORT4_PM
op_amp
op_complement
l_int|0xC
)paren
op_or
l_int|0x8
suffix:semicolon
)brace
multiline_comment|/* Do pre-configuration for the actual UART.  */
id|ma_uart_pre_configure
(paren
id|chan
comma
id|cflags
comma
id|baud
)paren
suffix:semicolon
)brace
DECL|function|mach_init_irqs
r_void
id|__init
id|mach_init_irqs
(paren
r_void
)paren
(brace
r_int
id|tc
suffix:semicolon
multiline_comment|/* Initialize interrupts.  */
id|ma_init_irqs
(paren
)paren
suffix:semicolon
id|rte_cb_init_irqs
(paren
)paren
suffix:semicolon
multiline_comment|/* Use falling-edge-sensitivity for interrupts .  */
id|V850E_TIMER_C_SESC
(paren
l_int|0
)paren
op_and_assign
op_complement
l_int|0xC
suffix:semicolon
id|V850E_TIMER_C_SESC
(paren
l_int|1
)paren
op_and_assign
op_complement
l_int|0xF
suffix:semicolon
multiline_comment|/* INTP000-INTP011 are shared with `Timer C&squot;, so we have to set&n;&t;   up Timer C to pass them through as raw interrupts.  */
r_for
c_loop
(paren
id|tc
op_assign
l_int|0
suffix:semicolon
id|tc
OL
l_int|2
suffix:semicolon
id|tc
op_increment
)paren
multiline_comment|/* Turn on the timer.  */
id|V850E_TIMER_C_TMCC0
(paren
id|tc
)paren
op_or_assign
id|V850E_TIMER_C_TMCC0_CAE
suffix:semicolon
multiline_comment|/* Make sure the relevant port0/port1 pins are assigned&n;&t;   interrupt duty.  We used INTP001-INTP011 (don&squot;t screw with&n;&t;   INTP000 because the monitor uses it).  */
id|MA_PORT0_PMC
op_or_assign
l_int|0x4
suffix:semicolon
multiline_comment|/* P02 (INTP001) in IRQ mode.  */
id|MA_PORT1_PMC
op_or_assign
l_int|0x6
suffix:semicolon
multiline_comment|/* P11 (INTP010) &amp; P12 (INTP011) in IRQ mode.*/
)brace
eof
