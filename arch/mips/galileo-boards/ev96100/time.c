multiline_comment|/*&n; * BRIEF MODULE DESCRIPTION&n; *&t;Galileo EV96100 rtc routines.&n; *&n; * Copyright 2000 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; * This file was derived from Carsten Langgaard&squot;s&n; * arch/mips/mips-boards/atlas/atlas_rtc.c.&n; *&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 1999,2000 MIPS Technologies, Inc.  All rights reserved.&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/time.h&gt;
DECL|macro|ALLINTS
mdefine_line|#define ALLINTS (IE_IRQ0 | IE_IRQ1 | IE_IRQ2 | IE_IRQ3 | IE_IRQ4 | IE_IRQ5)
r_extern
r_volatile
r_int
r_int
id|wall_jiffies
suffix:semicolon
DECL|variable|missed_heart_beats
r_int
r_int
id|missed_heart_beats
op_assign
l_int|0
suffix:semicolon
DECL|variable|r4k_offset
r_static
r_int
r_int
id|r4k_offset
suffix:semicolon
multiline_comment|/* Amount to increment compare reg each time */
DECL|variable|r4k_cur
r_static
r_int
r_int
id|r4k_cur
suffix:semicolon
multiline_comment|/* What counter should be at next timer irq */
DECL|function|ack_r4ktimer
r_static
r_inline
r_void
id|ack_r4ktimer
c_func
(paren
r_int
r_int
id|newval
)paren
(brace
id|write_c0_compare
c_func
(paren
id|newval
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * There are a lot of conceptually broken versions of the MIPS timer interrupt&n; * handler floating around.  This one is rather different, but the algorithm&n; * is probably more robust.&n; */
DECL|function|mips_timer_interrupt
r_void
id|mips_timer_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|irq
op_assign
l_int|7
suffix:semicolon
multiline_comment|/* FIX ME */
r_if
c_cond
(paren
id|r4k_offset
op_eq
l_int|0
)paren
(brace
r_goto
id|null
suffix:semicolon
)brace
r_do
(brace
id|kstat_this_cpu.irqs
(braket
id|irq
)braket
op_increment
suffix:semicolon
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
id|update_process_times
c_func
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
macro_line|#endif
id|r4k_cur
op_add_assign
id|r4k_offset
suffix:semicolon
id|ack_r4ktimer
c_func
(paren
id|r4k_cur
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
(paren
r_int
r_int
)paren
id|read_c0_count
c_func
(paren
)paren
op_minus
id|r4k_cur
)paren
OL
l_int|0x7fffffff
)paren
suffix:semicolon
r_return
suffix:semicolon
id|null
suffix:colon
id|ack_r4ktimer
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
eof
