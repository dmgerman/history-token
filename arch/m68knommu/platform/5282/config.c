multiline_comment|/***************************************************************************/
multiline_comment|/*&n; *&t;linux/arch/m68knommu/platform/5282/config.c&n; *&n; *&t;Sub-architcture dependant initialization code for the Motorola&n; *&t;5282 CPU.&n; *&n; *&t;Copyright (C) 1999-2003, Greg Ungerer (gerg@snapgear.com)&n; *&t;Copyright (C) 2001-2003, SnapGear Inc. (www.snapgear.com)&n; */
multiline_comment|/***************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/coldfire.h&gt;
macro_line|#include &lt;asm/mcfsim.h&gt;
macro_line|#include &lt;asm/mcfdma.h&gt;
multiline_comment|/***************************************************************************/
r_void
id|coldfire_pit_tick
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|coldfire_pit_init
c_func
(paren
r_void
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
id|coldfire_pit_offset
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
multiline_comment|/***************************************************************************/
DECL|function|mcf_disableall
r_void
id|mcf_disableall
c_func
(paren
r_void
)paren
(brace
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|MCF_IPSBAR
op_plus
id|MCFICM_INTC0
op_plus
id|MCFINTC_IMRH
)paren
)paren
op_assign
l_int|0xffffffff
suffix:semicolon
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|MCF_IPSBAR
op_plus
id|MCFICM_INTC0
op_plus
id|MCFINTC_IMRL
)paren
)paren
op_assign
l_int|0xffffffff
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
id|mcf_disableall
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BOOTPARAM
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
id|mach_sched_init
op_assign
id|coldfire_pit_init
suffix:semicolon
id|mach_tick
op_assign
id|coldfire_pit_tick
suffix:semicolon
id|mach_gettimeoffset
op_assign
id|coldfire_pit_offset
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
