multiline_comment|/***************************************************************************/
multiline_comment|/*&n; *&t;linux/arch/m68knommu/platform/5407/config.c&n; *&n; *&t;Copyright (C) 1999-2002, Greg Ungerer (gerg@snapgear.com)&n; *&t;Copyright (C) 2000, Lineo (www.lineo.com)&n; */
multiline_comment|/***************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/coldfire.h&gt;
macro_line|#include &lt;asm/mcftimer.h&gt;
macro_line|#include &lt;asm/mcfsim.h&gt;
macro_line|#include &lt;asm/mcfdma.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
multiline_comment|/***************************************************************************/
r_void
id|coldfire_tick
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|coldfire_timer_init
c_func
(paren
id|irqreturn_t
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
)paren
suffix:semicolon
r_int
r_int
id|coldfire_timer_offset
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|coldfire_trap_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|coldfire_reset
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|mcf_timervector
suffix:semicolon
r_extern
r_int
r_int
id|mcf_profilevector
suffix:semicolon
r_extern
r_int
r_int
id|mcf_timerlevel
suffix:semicolon
multiline_comment|/***************************************************************************/
multiline_comment|/*&n; *&t;DMA channel base address table.&n; */
DECL|variable|dma_base_addr
r_int
r_int
id|dma_base_addr
(braket
id|MAX_M68K_DMA_CHANNELS
)braket
op_assign
(brace
id|MCF_MBAR
op_plus
id|MCFDMA_BASE0
comma
id|MCF_MBAR
op_plus
id|MCFDMA_BASE1
comma
id|MCF_MBAR
op_plus
id|MCFDMA_BASE2
comma
id|MCF_MBAR
op_plus
id|MCFDMA_BASE3
comma
)brace
suffix:semicolon
DECL|variable|dma_device_address
r_int
r_int
id|dma_device_address
(braket
id|MAX_M68K_DMA_CHANNELS
)braket
suffix:semicolon
multiline_comment|/***************************************************************************/
DECL|function|mcf_autovector
r_void
id|mcf_autovector
c_func
(paren
r_int
r_int
id|vec
)paren
(brace
r_volatile
r_int
r_char
op_star
id|mbar
suffix:semicolon
r_if
c_cond
(paren
(paren
id|vec
op_ge
l_int|25
)paren
op_logical_and
(paren
id|vec
op_le
l_int|31
)paren
)paren
(brace
id|mbar
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
id|MCF_MBAR
suffix:semicolon
id|vec
op_assign
l_int|0x1
op_lshift
(paren
id|vec
op_minus
l_int|24
)paren
suffix:semicolon
op_star
(paren
id|mbar
op_plus
id|MCFSIM_AVR
)paren
op_or_assign
id|vec
suffix:semicolon
id|mcf_setimr
c_func
(paren
id|mcf_getimr
c_func
(paren
)paren
op_amp
op_complement
id|vec
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/***************************************************************************/
DECL|function|mcf_settimericr
r_void
id|mcf_settimericr
c_func
(paren
r_int
r_int
id|timer
comma
r_int
r_int
id|level
)paren
(brace
r_volatile
r_int
r_char
op_star
id|icrp
suffix:semicolon
r_int
r_int
id|icr
comma
id|imr
suffix:semicolon
r_if
c_cond
(paren
id|timer
op_le
l_int|2
)paren
(brace
r_switch
c_cond
(paren
id|timer
)paren
(brace
r_case
l_int|2
suffix:colon
id|icr
op_assign
id|MCFSIM_TIMER2ICR
suffix:semicolon
id|imr
op_assign
id|MCFSIM_IMR_TIMER2
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|icr
op_assign
id|MCFSIM_TIMER1ICR
suffix:semicolon
id|imr
op_assign
id|MCFSIM_IMR_TIMER1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|icrp
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|MCF_MBAR
op_plus
id|icr
)paren
suffix:semicolon
op_star
id|icrp
op_assign
id|MCFSIM_ICR_AUTOVEC
op_or
(paren
id|level
op_lshift
l_int|2
)paren
op_or
id|MCFSIM_ICR_PRI3
suffix:semicolon
id|mcf_setimr
c_func
(paren
id|mcf_getimr
c_func
(paren
)paren
op_amp
op_complement
id|imr
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/***************************************************************************/
DECL|function|mcf_timerirqpending
r_int
id|mcf_timerirqpending
c_func
(paren
r_int
id|timer
)paren
(brace
r_int
r_int
id|imr
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|timer
)paren
(brace
r_case
l_int|1
suffix:colon
id|imr
op_assign
id|MCFSIM_IMR_TIMER1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|imr
op_assign
id|MCFSIM_IMR_TIMER2
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
(paren
id|mcf_getipr
c_func
(paren
)paren
op_amp
id|imr
)paren
suffix:semicolon
)brace
multiline_comment|/***************************************************************************/
DECL|function|config_BSP
r_void
id|config_BSP
c_func
(paren
r_char
op_star
id|commandp
comma
r_int
id|size
)paren
(brace
id|mcf_setimr
c_func
(paren
id|MCFSIM_IMR_MASKALL
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_BOOTPARAM)
id|strncpy
c_func
(paren
id|commandp
comma
id|CONFIG_BOOTPARAM_STRING
comma
id|size
)paren
suffix:semicolon
id|commandp
(braket
id|size
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
macro_line|#else
id|memset
c_func
(paren
id|commandp
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_CLEOPATRA)
multiline_comment|/* Different timer setup - to prevent device clash */
id|mcf_timervector
op_assign
l_int|30
suffix:semicolon
id|mcf_profilevector
op_assign
l_int|31
suffix:semicolon
id|mcf_timerlevel
op_assign
l_int|6
suffix:semicolon
macro_line|#endif
id|mach_sched_init
op_assign
id|coldfire_timer_init
suffix:semicolon
id|mach_tick
op_assign
id|coldfire_tick
suffix:semicolon
id|mach_gettimeoffset
op_assign
id|coldfire_timer_offset
suffix:semicolon
id|mach_trap_init
op_assign
id|coldfire_trap_init
suffix:semicolon
id|mach_reset
op_assign
id|coldfire_reset
suffix:semicolon
)brace
multiline_comment|/***************************************************************************/
eof
