multiline_comment|/*&n; *  linux/arch/m68knommu/platform/MC68VZ328/de2/config.c&n; *&n; *  Copyright (C) 1993 Hamish Macdonald&n; *  Copyright (C) 1999 D. Jeff Dionne&n; *  Copyright (C) 2001 Georges Menie, Ken Desmet&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/kd.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/MC68VZ328.h&gt;
DECL|macro|CLOCK_COMPARE
mdefine_line|#define CLOCK_COMPARE (32768/HZ)
DECL|function|dragen2_sched_init
r_static
r_void
id|dragen2_sched_init
c_func
(paren
r_void
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
multiline_comment|/* disable timer 1 */
id|TCTL
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* set ISR */
id|request_irq
c_func
(paren
id|TMR_IRQ_NUM
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
multiline_comment|/* Restart mode, Enable int, 32KHz */
id|TCTL
op_assign
id|TCTL_OM
op_or
id|TCTL_IRQEN
op_or
id|TCTL_CLKSOURCE_32KHZ
suffix:semicolon
id|TPRER
op_assign
l_int|0
suffix:semicolon
id|TCMP
op_assign
id|CLOCK_COMPARE
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Enable timer 1 */
id|TCTL
op_or_assign
id|TCTL_TEN
suffix:semicolon
)brace
DECL|function|dragen2_tick
r_static
r_void
id|dragen2_tick
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Reset Timer1 */
id|TSTAT
op_and_assign
l_int|0
suffix:semicolon
)brace
DECL|function|dragen2_gettimeoffset
r_static
r_int
r_int
id|dragen2_gettimeoffset
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|ticks
comma
id|offset
op_assign
l_int|0
suffix:semicolon
id|ticks
op_assign
id|TCN
suffix:semicolon
r_if
c_cond
(paren
id|ticks
OG
(paren
id|CLOCK_COMPARE
op_rshift
l_int|1
)paren
)paren
(brace
multiline_comment|/* check for pending interrupt */
r_if
c_cond
(paren
id|ISR
op_amp
(paren
l_int|1
op_lshift
id|TMR_IRQ_NUM
)paren
)paren
id|offset
op_assign
l_int|1000000
op_div
id|HZ
suffix:semicolon
)brace
id|ticks
op_assign
id|CLOCK_COMPARE
op_minus
id|ticks
suffix:semicolon
id|ticks
op_assign
(paren
l_int|1000000
op_div
id|HZ
op_star
id|ticks
)paren
op_div
id|CLOCK_COMPARE
suffix:semicolon
r_return
id|ticks
op_plus
id|offset
suffix:semicolon
)brace
DECL|function|dragen2_gettod
r_static
r_void
id|dragen2_gettod
c_func
(paren
r_int
op_star
id|year
comma
r_int
op_star
id|mon
comma
r_int
op_star
id|day
comma
r_int
op_star
id|hour
comma
r_int
op_star
id|min
comma
r_int
op_star
id|sec
)paren
(brace
r_int
id|now
op_assign
id|RTCTIME
suffix:semicolon
op_star
id|year
op_assign
op_star
id|mon
op_assign
op_star
id|day
op_assign
l_int|1
suffix:semicolon
op_star
id|hour
op_assign
(paren
id|now
op_rshift
l_int|24
)paren
op_mod
l_int|24
suffix:semicolon
op_star
id|min
op_assign
(paren
id|now
op_rshift
l_int|16
)paren
op_mod
l_int|60
suffix:semicolon
op_star
id|sec
op_assign
id|now
op_mod
l_int|60
suffix:semicolon
)brace
DECL|function|dragen2_reset
r_static
r_void
id|dragen2_reset
c_func
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
"&quot;"
id|movel
macro_line|#-1, 0xFFFFF304;
id|moveb
macro_line|#0, 0xFFFFF300;
id|moveal
macro_line|#0x04000000, %a0;
id|moveal
l_int|0
(paren
op_mod
id|a0
)paren
comma
op_mod
id|sp
suffix:semicolon
id|moveal
l_int|4
(paren
op_mod
id|a0
)paren
comma
op_mod
id|a0
suffix:semicolon
id|jmp
(paren
op_mod
id|a0
)paren
suffix:semicolon
"&quot;"
)paren
suffix:semicolon
)brace
DECL|function|dragen2_cs8900_setup
r_int
id|dragen2_cs8900_setup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
multiline_comment|/* Set the ETH hardware address from its flash monitor location */
id|memcpy
c_func
(paren
id|dev-&gt;dev_addr
comma
(paren
r_void
op_star
)paren
l_int|0x400fffa
comma
l_int|6
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|INT1_IRQ_NUM
suffix:semicolon
r_return
id|dev-&gt;base_addr
op_assign
l_int|0x08000041
suffix:semicolon
)brace
DECL|function|init_hardware
r_static
r_void
id|init_hardware
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* CSGB Init */
id|CSGBB
op_assign
l_int|0x4000
suffix:semicolon
id|CSB
op_assign
l_int|0x1a1
suffix:semicolon
multiline_comment|/* CS8900 init */
multiline_comment|/* PK3: hardware sleep function pin, active low */
id|PKSEL
op_or_assign
id|PK
c_func
(paren
l_int|3
)paren
suffix:semicolon
multiline_comment|/* select pin as I/O */
id|PKDIR
op_or_assign
id|PK
c_func
(paren
l_int|3
)paren
suffix:semicolon
multiline_comment|/* select pin as output */
id|PKDATA
op_or_assign
id|PK
c_func
(paren
l_int|3
)paren
suffix:semicolon
multiline_comment|/* set pin high */
multiline_comment|/* PF5: hardware reset function pin, active high */
id|PFSEL
op_or_assign
id|PF
c_func
(paren
l_int|5
)paren
suffix:semicolon
multiline_comment|/* select pin as I/O */
id|PFDIR
op_or_assign
id|PF
c_func
(paren
l_int|5
)paren
suffix:semicolon
multiline_comment|/* select pin as output */
id|PFDATA
op_and_assign
op_complement
id|PF
c_func
(paren
l_int|5
)paren
suffix:semicolon
multiline_comment|/* set pin low */
multiline_comment|/* cs8900 hardware reset */
id|PFDATA
op_or_assign
id|PF
c_func
(paren
l_int|5
)paren
suffix:semicolon
(brace
r_volatile
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|32000
suffix:semicolon
op_increment
id|i
)paren
suffix:semicolon
)brace
id|PFDATA
op_and_assign
op_complement
id|PF
c_func
(paren
l_int|5
)paren
suffix:semicolon
multiline_comment|/* INT1 enable (cs8900 IRQ) */
id|PDPOL
op_and_assign
op_complement
id|PD
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* active high signal */
id|PDIQEG
op_and_assign
op_complement
id|PD
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|PDIRQEN
op_or_assign
id|PD
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* IRQ enabled */
macro_line|#ifdef CONFIG_68328_SERIAL_UART2
multiline_comment|/* Enable RXD TXD port bits to enable UART2 */
id|PJSEL
op_and_assign
op_complement
(paren
id|PJ
c_func
(paren
l_int|5
)paren
op_or
id|PJ
c_func
(paren
l_int|4
)paren
)paren
suffix:semicolon
macro_line|#endif
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
l_string|&quot;68VZ328 DragonBallVZ support (c) 2001 Lineo, Inc.&bslash;n&quot;
)paren
suffix:semicolon
id|command
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/* no specific boot option */
id|init_hardware
c_func
(paren
)paren
suffix:semicolon
id|mach_sched_init
op_assign
id|dragen2_sched_init
suffix:semicolon
id|mach_tick
op_assign
id|dragen2_tick
suffix:semicolon
id|mach_gettimeoffset
op_assign
id|dragen2_gettimeoffset
suffix:semicolon
id|mach_reset
op_assign
id|dragen2_reset
suffix:semicolon
id|mach_gettod
op_assign
id|dragen2_gettod
suffix:semicolon
id|config_M68VZ328_irq
c_func
(paren
)paren
suffix:semicolon
)brace
eof
