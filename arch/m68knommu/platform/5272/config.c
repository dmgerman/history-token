multiline_comment|/***************************************************************************/
multiline_comment|/*&n; *&t;linux/arch/m68knommu/platform/5272/config.c&n; *&n; *&t;Copyright (C) 1999-2002, Greg Ungerer (gerg@snapgear.com)&n; *&t;Copyright (C) 2001-2002, SnapGear Inc. (www.snapgear.com)&n; */
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
DECL|function|mcf_disableall
r_void
id|mcf_disableall
c_func
(paren
r_void
)paren
(brace
r_volatile
r_int
r_int
op_star
id|icrp
suffix:semicolon
id|icrp
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|MCF_MBAR
op_plus
id|MCFSIM_ICR1
)paren
suffix:semicolon
id|icrp
(braket
l_int|0
)braket
op_assign
l_int|0x88888888
suffix:semicolon
id|icrp
(braket
l_int|1
)braket
op_assign
l_int|0x88888888
suffix:semicolon
id|icrp
(braket
l_int|2
)braket
op_assign
l_int|0x88888888
suffix:semicolon
id|icrp
(braket
l_int|3
)braket
op_assign
l_int|0x88888888
suffix:semicolon
)brace
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
multiline_comment|/* Everything is auto-vectored on the 5272 */
)brace
multiline_comment|/***************************************************************************/
DECL|function|mcf_settimericr
r_void
id|mcf_settimericr
c_func
(paren
r_int
id|timer
comma
r_int
id|level
)paren
(brace
r_volatile
r_int
r_int
op_star
id|icrp
suffix:semicolon
r_if
c_cond
(paren
(paren
id|timer
op_ge
l_int|1
)paren
op_logical_and
(paren
id|timer
op_le
l_int|4
)paren
)paren
(brace
id|icrp
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|MCF_MBAR
op_plus
id|MCFSIM_ICR1
)paren
suffix:semicolon
op_star
id|icrp
op_assign
(paren
l_int|0x8
op_or
id|level
)paren
op_lshift
(paren
(paren
l_int|4
op_minus
id|timer
)paren
op_star
l_int|4
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
r_volatile
r_int
r_int
op_star
id|icrp
suffix:semicolon
r_if
c_cond
(paren
(paren
id|timer
op_ge
l_int|1
)paren
op_logical_and
(paren
id|timer
op_le
l_int|4
)paren
)paren
(brace
id|icrp
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|MCF_MBAR
op_plus
id|MCFSIM_ICR1
)paren
suffix:semicolon
r_return
(paren
op_star
id|icrp
op_amp
(paren
l_int|0x8
op_lshift
(paren
(paren
l_int|4
op_minus
id|timer
)paren
op_star
l_int|4
)paren
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
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
macro_line|#if 0
r_volatile
r_int
r_int
op_star
id|pivrp
suffix:semicolon
multiline_comment|/* Set base of device vectors to be 64 */
id|pivrp
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|MCF_MBAR
op_plus
id|MCFSIM_PIVR
)paren
suffix:semicolon
op_star
id|pivrp
op_assign
l_int|0x40
suffix:semicolon
macro_line|#endif
id|mcf_disableall
c_func
(paren
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
macro_line|#elif defined(CONFIG_NETtel)
multiline_comment|/* Copy command line from FLASH to local buffer... */
id|memcpy
c_func
(paren
id|commandp
comma
(paren
r_char
op_star
)paren
l_int|0xf0004000
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
macro_line|#elif defined(CONFIG_MTD_KeyTechnology)
multiline_comment|/* Copy command line from FLASH to local buffer... */
id|memcpy
c_func
(paren
id|commandp
comma
(paren
r_char
op_star
)paren
l_int|0xffe06000
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
id|mcf_timervector
op_assign
l_int|69
suffix:semicolon
id|mcf_profilevector
op_assign
l_int|70
suffix:semicolon
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
