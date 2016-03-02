multiline_comment|/*&n; *  linux/arch/$(ARCH)/platform/$(PLATFORM)/config.c&n; *&n; *  Copyright (C) 1993 Hamish Macdonald&n; *  Copyright (C) 1999 D. Jeff Dionne&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; *&n; * VZ Support/Fixes             Evan Stawnyczy &lt;e@lineo.ca&gt;&n; */
macro_line|#include &lt;asm/dbg.h&gt;
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/current.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/MC68328.h&gt;
DECL|function|BSP_sched_init
r_void
id|BSP_sched_init
c_func
(paren
id|irqreturn_t
(paren
op_star
id|timer_routine
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
(brace
macro_line|#ifdef CONFIG_XCOPILOT_BUGS
multiline_comment|/*&n;   * The only thing I know is that CLK32 is not available on Xcopilot&n;   * I have little idea about what frequency SYSCLK has on Xcopilot. &n;   * The values for prescaler and compare registers were simply &n;   * taken from the original source&n;   */
multiline_comment|/* Restart mode, Enable int, SYSCLK, Enable timer */
id|TCTL2
op_assign
id|TCTL_OM
op_or
id|TCTL_IRQEN
op_or
id|TCTL_CLKSOURCE_SYSCLK
op_or
id|TCTL_TEN
suffix:semicolon
multiline_comment|/* Set prescaler */
id|TPRER2
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* Set compare register */
id|TCMP2
op_assign
l_int|0xd7e4
suffix:semicolon
macro_line|#else
multiline_comment|/* Restart mode, Enable int, 32KHz, Enable timer */
id|TCTL2
op_assign
id|TCTL_OM
op_or
id|TCTL_IRQEN
op_or
id|TCTL_CLKSOURCE_32KHZ
op_or
id|TCTL_TEN
suffix:semicolon
multiline_comment|/* Set prescaler (Divide 32KHz by 32)*/
id|TPRER2
op_assign
l_int|31
suffix:semicolon
multiline_comment|/* Set compare register  32Khz / 32 / 10 = 100 */
id|TCMP2
op_assign
l_int|10
suffix:semicolon
macro_line|#endif
id|request_irq
c_func
(paren
id|TMR2_IRQ_NUM
comma
id|timer_routine
comma
id|IRQ_FLG_LOCK
comma
l_string|&quot;timer&quot;
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|BSP_tick
r_void
id|BSP_tick
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Reset Timer2 */
id|TSTAT2
op_and_assign
l_int|0
suffix:semicolon
)brace
DECL|function|BSP_gettimeoffset
r_int
r_int
id|BSP_gettimeoffset
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|BSP_gettod
r_void
id|BSP_gettod
(paren
r_int
op_star
id|yearp
comma
r_int
op_star
id|monp
comma
r_int
op_star
id|dayp
comma
r_int
op_star
id|hourp
comma
r_int
op_star
id|minp
comma
r_int
op_star
id|secp
)paren
(brace
)brace
DECL|function|BSP_hwclk
r_int
id|BSP_hwclk
c_func
(paren
r_int
id|op
comma
r_struct
id|hwclk_time
op_star
id|t
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|op
)paren
(brace
multiline_comment|/* read */
)brace
r_else
(brace
multiline_comment|/* write */
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|BSP_set_clock_mmss
r_int
id|BSP_set_clock_mmss
(paren
r_int
r_int
id|nowtime
)paren
(brace
macro_line|#if 0
r_int
id|real_seconds
op_assign
id|nowtime
op_mod
l_int|60
comma
id|real_minutes
op_assign
(paren
id|nowtime
op_div
l_int|60
)paren
op_mod
l_int|60
suffix:semicolon
id|tod-&gt;second1
op_assign
id|real_seconds
op_div
l_int|10
suffix:semicolon
id|tod-&gt;second2
op_assign
id|real_seconds
op_mod
l_int|10
suffix:semicolon
id|tod-&gt;minute1
op_assign
id|real_minutes
op_div
l_int|10
suffix:semicolon
id|tod-&gt;minute2
op_assign
id|real_minutes
op_mod
l_int|10
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|BSP_reset
r_void
id|BSP_reset
(paren
r_void
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;moveal #0x10c00000, %a0;&bslash;n&bslash;t&quot;
l_string|&quot;moveb #0, 0xFFFFF300;&bslash;n&bslash;t&quot;
l_string|&quot;moveal 0(%a0), %sp;&bslash;n&bslash;t&quot;
l_string|&quot;moveal 4(%a0), %a0;&bslash;n&bslash;t&quot;
l_string|&quot;jmp (%a0);&quot;
)paren
suffix:semicolon
)brace
DECL|function|config_BSP
r_void
id|config_BSP
c_func
(paren
r_char
op_star
id|command
comma
r_int
id|len
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;&bslash;n68328 support D. Jeff Dionne &lt;jeff@uclinux.org&gt;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;68328 support Kenneth Albanowski &lt;kjahds@kjshds.com&gt;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;68328/Pilot support Bernhard Kuhn &lt;kuhn@lpr.e-technik.tu-muenchen.de&gt;&bslash;n&quot;
)paren
suffix:semicolon
id|mach_sched_init
op_assign
id|BSP_sched_init
suffix:semicolon
id|mach_tick
op_assign
id|BSP_tick
suffix:semicolon
id|mach_gettimeoffset
op_assign
id|BSP_gettimeoffset
suffix:semicolon
id|mach_gettod
op_assign
id|BSP_gettod
suffix:semicolon
id|mach_hwclk
op_assign
l_int|NULL
suffix:semicolon
id|mach_set_clock_mmss
op_assign
l_int|NULL
suffix:semicolon
id|mach_reset
op_assign
id|BSP_reset
suffix:semicolon
op_star
id|command
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
eof
