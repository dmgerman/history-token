multiline_comment|/*&n; * arch/arm/mach-omap/time.c&n; *&n; * OMAP Timer Tick &n; *&n; * Copyright (C) 2000 RidgeRun, Inc.&n; * Author: Greg Lonnon &lt;glonnon@ridgerun.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n; * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF&n; * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the  GNU General Public License along&n; * with this program; if not, write  to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/leds.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/mach/time.h&gt;
macro_line|#include &lt;asm/arch/clocks.h&gt;
macro_line|#ifndef __instrument
DECL|macro|__instrument
mdefine_line|#define __instrument
DECL|macro|__noinstrument
mdefine_line|#define __noinstrument __attribute__ ((no_instrument_function))
macro_line|#endif
r_typedef
r_struct
(brace
DECL|member|cntl
id|u32
id|cntl
suffix:semicolon
multiline_comment|/* CNTL_TIMER, R/W */
DECL|member|load_tim
id|u32
id|load_tim
suffix:semicolon
multiline_comment|/* LOAD_TIM,   W */
DECL|member|read_tim
id|u32
id|read_tim
suffix:semicolon
multiline_comment|/* READ_TIM,   R */
DECL|typedef|mputimer_regs_t
)brace
id|mputimer_regs_t
suffix:semicolon
DECL|macro|mputimer_base
mdefine_line|#define mputimer_base(n) &bslash;&n;    ((volatile mputimer_regs_t*)IO_ADDRESS(OMAP_MPUTIMER_BASE + &bslash;&n;&t;&t;&t;&t; (n)*OMAP_MPUTIMER_OFFSET))
DECL|function|timer32k_read
r_static
r_inline
r_int
r_int
id|timer32k_read
c_func
(paren
r_int
id|reg
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|val
op_assign
id|omap_readw
c_func
(paren
id|reg
op_plus
id|OMAP_32kHz_TIMER_BASE
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|timer32k_write
r_static
r_inline
r_void
id|timer32k_write
c_func
(paren
r_int
id|reg
comma
r_int
id|val
)paren
(brace
id|omap_writew
c_func
(paren
id|val
comma
id|reg
op_plus
id|OMAP_32kHz_TIMER_BASE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * How long is the timer interval? 100 HZ, right...&n; * IRQ rate = (TVR + 1) / 32768 seconds&n; * TVR = 32768 * IRQ_RATE -1&n; * IRQ_RATE =  1/100&n; * TVR = 326&n; */
DECL|macro|TIMER32k_PERIOD
mdefine_line|#define TIMER32k_PERIOD 326
singleline_comment|//#define TIMER32k_PERIOD 0x7ff
DECL|function|start_timer32k
r_static
r_inline
r_void
id|start_timer32k
c_func
(paren
r_void
)paren
(brace
id|timer32k_write
c_func
(paren
id|TIMER32k_CR
comma
id|TIMER32k_TSS
op_or
id|TIMER32k_TRB
op_or
id|TIMER32k_INT
op_or
id|TIMER32k_ARL
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MACH_OMAP_PERSEUS2
multiline_comment|/*&n; * After programming PTV with 0 and setting the MPUTIM_CLOCK_ENABLE&n; * (external clock enable)  bit, the timer count rate is 6.5 MHz (13&n; * MHZ input/2). !! The divider by 2 is undocumented !!&n; */
DECL|macro|MPUTICKS_PER_SEC
mdefine_line|#define MPUTICKS_PER_SEC (13000000/2)
macro_line|#else
multiline_comment|/*&n; * After programming PTV with 0, the timer count rate is 6 MHz.&n; * WARNING! this must be an even number, or machinecycles_to_usecs&n; * below will break.&n; */
DECL|macro|MPUTICKS_PER_SEC
mdefine_line|#define MPUTICKS_PER_SEC  (12000000/2)
macro_line|#endif
DECL|variable|mputimer_started
r_static
r_int
id|mputimer_started
(braket
l_int|3
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|function|start_mputimer
r_static
r_inline
r_void
id|__noinstrument
id|start_mputimer
c_func
(paren
r_int
id|n
comma
r_int
r_int
id|load_val
)paren
(brace
r_volatile
id|mputimer_regs_t
op_star
id|timer
op_assign
id|mputimer_base
c_func
(paren
id|n
)paren
suffix:semicolon
id|mputimer_started
(braket
id|n
)braket
op_assign
l_int|0
suffix:semicolon
id|timer-&gt;cntl
op_assign
id|MPUTIM_CLOCK_ENABLE
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|timer-&gt;load_tim
op_assign
id|load_val
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|timer-&gt;cntl
op_assign
(paren
id|MPUTIM_CLOCK_ENABLE
op_or
id|MPUTIM_AR
op_or
id|MPUTIM_ST
)paren
suffix:semicolon
id|mputimer_started
(braket
id|n
)braket
op_assign
l_int|1
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
id|__noinstrument
DECL|function|read_mputimer
id|read_mputimer
c_func
(paren
r_int
id|n
)paren
(brace
r_volatile
id|mputimer_regs_t
op_star
id|timer
op_assign
id|mputimer_base
c_func
(paren
id|n
)paren
suffix:semicolon
r_return
(paren
id|mputimer_started
(braket
id|n
)braket
ques
c_cond
id|timer-&gt;read_tim
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|start_mputimer1
r_void
id|__noinstrument
id|start_mputimer1
c_func
(paren
r_int
r_int
id|load_val
)paren
(brace
id|start_mputimer
c_func
(paren
l_int|0
comma
id|load_val
)paren
suffix:semicolon
)brace
DECL|function|start_mputimer2
r_void
id|__noinstrument
id|start_mputimer2
c_func
(paren
r_int
r_int
id|load_val
)paren
(brace
id|start_mputimer
c_func
(paren
l_int|1
comma
id|load_val
)paren
suffix:semicolon
)brace
DECL|function|start_mputimer3
r_void
id|__noinstrument
id|start_mputimer3
c_func
(paren
r_int
r_int
id|load_val
)paren
(brace
id|start_mputimer
c_func
(paren
l_int|2
comma
id|load_val
)paren
suffix:semicolon
)brace
DECL|function|read_mputimer1
r_int
r_int
id|__noinstrument
id|read_mputimer1
c_func
(paren
r_void
)paren
(brace
r_return
id|read_mputimer
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|read_mputimer2
r_int
r_int
id|__noinstrument
id|read_mputimer2
c_func
(paren
r_void
)paren
(brace
r_return
id|read_mputimer
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|read_mputimer3
r_int
r_int
id|__noinstrument
id|read_mputimer3
c_func
(paren
r_void
)paren
(brace
r_return
id|read_mputimer
c_func
(paren
l_int|2
)paren
suffix:semicolon
)brace
DECL|function|do_getmachinecycles
r_int
r_int
id|__noinstrument
id|do_getmachinecycles
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
op_minus
id|read_mputimer
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|machinecycles_to_usecs
r_int
r_int
id|__noinstrument
id|machinecycles_to_usecs
c_func
(paren
r_int
r_int
id|mputicks
)paren
(brace
multiline_comment|/* Round up to nearest usec */
r_return
(paren
(paren
id|mputicks
op_star
l_int|1000
)paren
op_div
(paren
id|MPUTICKS_PER_SEC
op_div
l_int|2
op_div
l_int|1000
)paren
op_plus
l_int|1
)paren
op_rshift
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * This marks the time of the last system timer interrupt&n; * that was *processed by the ISR* (timer 2).&n; */
DECL|variable|systimer_mark
r_static
r_int
r_int
id|systimer_mark
suffix:semicolon
DECL|function|omap_gettimeoffset
r_static
r_int
r_int
id|omap_gettimeoffset
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Return elapsed usecs since last system timer ISR */
r_return
id|machinecycles_to_usecs
c_func
(paren
id|do_getmachinecycles
c_func
(paren
)paren
op_minus
id|systimer_mark
)paren
suffix:semicolon
)brace
r_static
id|irqreturn_t
DECL|function|omap_timer_interrupt
id|omap_timer_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|now
comma
id|ilatency
suffix:semicolon
multiline_comment|/*&n;&t; * Mark the time at which the timer interrupt ocurred using&n;&t; * timer1. We need to remove interrupt latency, which we can&n;&t; * retrieve from the current system timer2 counter. Both the&n;&t; * offset timer1 and the system timer2 are counting at 6MHz,&n;&t; * so we&squot;re ok.&n;&t; */
id|now
op_assign
l_int|0
op_minus
id|read_mputimer1
c_func
(paren
)paren
suffix:semicolon
id|ilatency
op_assign
id|MPUTICKS_PER_SEC
op_div
l_int|100
op_minus
id|read_mputimer2
c_func
(paren
)paren
suffix:semicolon
id|systimer_mark
op_assign
id|now
op_minus
id|ilatency
suffix:semicolon
id|timer_tick
c_func
(paren
id|regs
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|variable|omap_timer_irq
r_static
r_struct
id|irqaction
id|omap_timer_irq
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;OMAP Timer Tick&quot;
comma
dot
id|flags
op_assign
id|SA_INTERRUPT
comma
dot
id|handler
op_assign
id|omap_timer_interrupt
)brace
suffix:semicolon
DECL|function|omap_init_time
r_void
id|__init
id|omap_init_time
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Since we don&squot;t call request_irq, we must init the structure */
id|gettimeoffset
op_assign
id|omap_gettimeoffset
suffix:semicolon
macro_line|#ifdef OMAP1510_USE_32KHZ_TIMER
id|timer32k_write
c_func
(paren
id|TIMER32k_CR
comma
l_int|0x0
)paren
suffix:semicolon
id|timer32k_write
c_func
(paren
id|TIMER32k_TVR
comma
id|TIMER32k_PERIOD
)paren
suffix:semicolon
id|setup_irq
c_func
(paren
id|INT_OS_32kHz_TIMER
comma
op_amp
id|omap_timer_irq
)paren
suffix:semicolon
id|start_timer32k
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
id|setup_irq
c_func
(paren
id|INT_TIMER2
comma
op_amp
id|omap_timer_irq
)paren
suffix:semicolon
id|start_mputimer2
c_func
(paren
id|MPUTICKS_PER_SEC
op_div
l_int|100
op_minus
l_int|1
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
