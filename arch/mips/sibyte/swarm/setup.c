multiline_comment|/*&n; * Copyright (C) 2000, 2001, 2002, 2003 Broadcom Corporation&n; * Copyright (C) 2004 by Ralf Baechle (ralf@linux-mips.org)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
multiline_comment|/*&n; * Setup code for the SWARM board&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_regs.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_genbus.h&gt;
macro_line|#include &lt;asm/sibyte/board.h&gt;
r_extern
r_void
id|sb1250_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|xicor_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|xicor_set_time
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|xicor_get_time
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|m41t81_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|m41t81_set_time
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|m41t81_get_time
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|get_system_type
r_const
r_char
op_star
id|get_system_type
c_func
(paren
r_void
)paren
(brace
r_return
l_string|&quot;SiByte &quot;
id|SIBYTE_BOARD_NAME
suffix:semicolon
)brace
DECL|function|swarm_timer_setup
r_void
id|__init
id|swarm_timer_setup
c_func
(paren
r_struct
id|irqaction
op_star
id|irq
)paren
(brace
multiline_comment|/*&n;         * we don&squot;t set up irqaction, because we will deliver timer&n;         * interrupts through low-level (direct) meachanism.&n;         */
multiline_comment|/* We only need to setup the generic timer */
id|sb1250_time_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|swarm_be_handler
r_int
id|swarm_be_handler
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|is_fixup
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|is_fixup
op_logical_and
(paren
id|regs-&gt;cp0_cause
op_amp
l_int|4
)paren
)paren
(brace
multiline_comment|/* Data bus error - print PA */
macro_line|#ifdef CONFIG_MIPS64
id|printk
c_func
(paren
l_string|&quot;DBE physical address: %010lx&bslash;n&quot;
comma
id|__read_64bit_c0_register
c_func
(paren
"$"
l_int|26
comma
l_int|1
)paren
)paren
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
l_string|&quot;DBE physical address: %010llx&bslash;n&quot;
comma
id|__read_64bit_c0_split
c_func
(paren
"$"
l_int|26
comma
l_int|1
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_return
(paren
id|is_fixup
ques
c_cond
id|MIPS_BE_FIXUP
suffix:colon
id|MIPS_BE_FATAL
)paren
suffix:semicolon
)brace
DECL|function|swarm_setup
r_static
r_int
id|__init
id|swarm_setup
c_func
(paren
r_void
)paren
(brace
r_extern
r_int
id|panic_timeout
suffix:semicolon
id|sb1250_setup
c_func
(paren
)paren
suffix:semicolon
id|panic_timeout
op_assign
l_int|5
suffix:semicolon
multiline_comment|/* For debug.  */
id|board_timer_setup
op_assign
id|swarm_timer_setup
suffix:semicolon
id|board_be_handler
op_assign
id|swarm_be_handler
suffix:semicolon
r_if
c_cond
(paren
id|xicor_probe
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;swarm setup: Xicor 1241 RTC detected.&bslash;n&quot;
)paren
suffix:semicolon
id|rtc_get_time
op_assign
id|xicor_get_time
suffix:semicolon
id|rtc_set_time
op_assign
id|xicor_set_time
suffix:semicolon
)brace
r_if
c_cond
(paren
id|m41t81_probe
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;swarm setup: M41T81 RTC detected.&bslash;n&quot;
)paren
suffix:semicolon
id|rtc_get_time
op_assign
id|m41t81_get_time
suffix:semicolon
id|rtc_set_time
op_assign
id|m41t81_set_time
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;This kernel optimized for &quot;
macro_line|#ifdef CONFIG_SIMULATION
l_string|&quot;simulation&quot;
macro_line|#else
l_string|&quot;board&quot;
macro_line|#endif
l_string|&quot; runs &quot;
macro_line|#ifdef CONFIG_SIBYTE_CFE
l_string|&quot;with&quot;
macro_line|#else
l_string|&quot;without&quot;
macro_line|#endif
l_string|&quot; CFE&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_VT
id|screen_info
op_assign
(paren
r_struct
id|screen_info
)paren
(brace
l_int|0
comma
l_int|0
comma
multiline_comment|/* orig-x, orig-y */
l_int|0
comma
multiline_comment|/* unused */
l_int|52
comma
multiline_comment|/* orig_video_page */
l_int|3
comma
multiline_comment|/* orig_video_mode */
l_int|80
comma
multiline_comment|/* orig_video_cols */
l_int|4626
comma
l_int|3
comma
l_int|9
comma
multiline_comment|/* unused, ega_bx, unused */
l_int|25
comma
multiline_comment|/* orig_video_lines */
l_int|0x22
comma
multiline_comment|/* orig_video_isVGA */
l_int|16
multiline_comment|/* orig_video_points */
)brace
suffix:semicolon
multiline_comment|/* XXXKW for CFE, get lines/cols from environment */
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|swarm_setup
id|early_initcall
c_func
(paren
id|swarm_setup
)paren
suffix:semicolon
macro_line|#ifdef LEDS_PHYS
macro_line|#ifdef CONFIG_SIBYTE_CARMEL
multiline_comment|/* XXXKW need to detect Monterey/LittleSur/etc */
DECL|macro|LEDS_PHYS
macro_line|#undef LEDS_PHYS
DECL|macro|LEDS_PHYS
mdefine_line|#define LEDS_PHYS MLEDS_PHYS
macro_line|#endif
DECL|macro|setled
mdefine_line|#define setled(index, c) &bslash;&n;  ((unsigned char *)(IOADDR(LEDS_PHYS)+0x20))[(3-(index))&lt;&lt;3] = (c)
DECL|function|setleds
r_void
id|setleds
c_func
(paren
r_char
op_star
id|str
)paren
(brace
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|str
(braket
id|i
)braket
)paren
(brace
id|setled
c_func
(paren
id|i
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|setled
c_func
(paren
id|i
comma
id|str
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif
eof
