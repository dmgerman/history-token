multiline_comment|/*&n; * linux/arch/arm/mach-omap/time.c&n; *&n; * OMAP Timers&n; *&n; * Copyright (C) 2004 Nokia Corporation&n; * Partial timer rewrite and additional VST timer support by&n; * Tony Lindgen &lt;tony@atomide.com&gt; and&n; * Tuukka Tikkanen &lt;tuukka.tikkanen@elektrobit.com&gt;&n; *&n; * MPU timer code based on the older MPU timer code for OMAP&n; * Copyright (C) 2000 RidgeRun, Inc.&n; * Author: Greg Lonnon &lt;glonnon@ridgerun.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n; * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF&n; * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the  GNU General Public License along&n; * with this program; if not, write  to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/leds.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/mach/time.h&gt;
DECL|variable|omap_timer
r_struct
id|sys_timer
id|omap_timer
suffix:semicolon
multiline_comment|/*&n; * ---------------------------------------------------------------------------&n; * MPU timer&n; * ---------------------------------------------------------------------------&n; */
DECL|macro|OMAP_MPU_TIMER1_BASE
mdefine_line|#define OMAP_MPU_TIMER1_BASE&t;&t;(0xfffec500)
DECL|macro|OMAP_MPU_TIMER2_BASE
mdefine_line|#define OMAP_MPU_TIMER2_BASE&t;&t;(0xfffec600)
DECL|macro|OMAP_MPU_TIMER3_BASE
mdefine_line|#define OMAP_MPU_TIMER3_BASE&t;&t;(0xfffec700)
DECL|macro|OMAP_MPU_TIMER_BASE
mdefine_line|#define OMAP_MPU_TIMER_BASE&t;&t;OMAP_MPU_TIMER1_BASE
DECL|macro|OMAP_MPU_TIMER_OFFSET
mdefine_line|#define OMAP_MPU_TIMER_OFFSET&t;&t;0x100
DECL|macro|MPU_TIMER_FREE
mdefine_line|#define MPU_TIMER_FREE&t;&t;&t;(1 &lt;&lt; 6)
DECL|macro|MPU_TIMER_CLOCK_ENABLE
mdefine_line|#define MPU_TIMER_CLOCK_ENABLE&t;&t;(1 &lt;&lt; 5)
DECL|macro|MPU_TIMER_AR
mdefine_line|#define MPU_TIMER_AR&t;&t;&t;(1 &lt;&lt; 1)
DECL|macro|MPU_TIMER_ST
mdefine_line|#define MPU_TIMER_ST&t;&t;&t;(1 &lt;&lt; 0)
multiline_comment|/*&n; * MPU_TICKS_PER_SEC must be an even number, otherwise machinecycles_to_usecs&n; * will break. On P2, the timer count rate is 6.5 MHz after programming PTV&n; * with 0. This divides the 13MHz input by 2, and is undocumented.&n; */
macro_line|#ifdef CONFIG_MACH_OMAP_PERSEUS2
multiline_comment|/* REVISIT: This ifdef construct should be replaced by a query to clock&n; * framework to see if timer base frequency is 12.0, 13.0 or 19.2 MHz.&n; */
DECL|macro|MPU_TICKS_PER_SEC
mdefine_line|#define MPU_TICKS_PER_SEC&t;&t;(13000000 / 2)
macro_line|#else
DECL|macro|MPU_TICKS_PER_SEC
mdefine_line|#define MPU_TICKS_PER_SEC&t;&t;(12000000 / 2)
macro_line|#endif
DECL|macro|MPU_TIMER_TICK_PERIOD
mdefine_line|#define MPU_TIMER_TICK_PERIOD&t;&t;((MPU_TICKS_PER_SEC / HZ) - 1)
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
DECL|typedef|omap_mpu_timer_regs_t
)brace
id|omap_mpu_timer_regs_t
suffix:semicolon
DECL|macro|omap_mpu_timer_base
mdefine_line|#define omap_mpu_timer_base(n)&t;&t;&t;&t;&t;&t;&bslash;&n;((volatile omap_mpu_timer_regs_t*)IO_ADDRESS(OMAP_MPU_TIMER_BASE +&t;&bslash;&n;&t;&t;&t;&t; (n)*OMAP_MPU_TIMER_OFFSET))
DECL|function|omap_mpu_timer_read
r_static
r_inline
r_int
r_int
id|omap_mpu_timer_read
c_func
(paren
r_int
id|nr
)paren
(brace
r_volatile
id|omap_mpu_timer_regs_t
op_star
id|timer
op_assign
id|omap_mpu_timer_base
c_func
(paren
id|nr
)paren
suffix:semicolon
r_return
id|timer-&gt;read_tim
suffix:semicolon
)brace
DECL|function|omap_mpu_timer_start
r_static
r_inline
r_void
id|omap_mpu_timer_start
c_func
(paren
r_int
id|nr
comma
r_int
r_int
id|load_val
)paren
(brace
r_volatile
id|omap_mpu_timer_regs_t
op_star
id|timer
op_assign
id|omap_mpu_timer_base
c_func
(paren
id|nr
)paren
suffix:semicolon
id|timer-&gt;cntl
op_assign
id|MPU_TIMER_CLOCK_ENABLE
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
id|MPU_TIMER_CLOCK_ENABLE
op_or
id|MPU_TIMER_AR
op_or
id|MPU_TIMER_ST
)paren
suffix:semicolon
)brace
DECL|function|omap_mpu_timer_ticks_to_usecs
r_int
r_int
id|omap_mpu_timer_ticks_to_usecs
c_func
(paren
r_int
r_int
id|nr_ticks
)paren
(brace
multiline_comment|/* Round up to nearest usec */
r_return
(paren
(paren
id|nr_ticks
op_star
l_int|1000
)paren
op_div
(paren
id|MPU_TICKS_PER_SEC
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
multiline_comment|/*&n; * Last processed system timer interrupt&n; */
DECL|variable|omap_mpu_timer_last
r_static
r_int
r_int
id|omap_mpu_timer_last
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * Returns elapsed usecs since last system timer interrupt&n; */
DECL|function|omap_mpu_timer_gettimeoffset
r_static
r_int
r_int
id|omap_mpu_timer_gettimeoffset
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|now
op_assign
l_int|0
op_minus
id|omap_mpu_timer_read
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_int
r_int
id|elapsed
op_assign
id|now
op_minus
id|omap_mpu_timer_last
suffix:semicolon
r_return
id|omap_mpu_timer_ticks_to_usecs
c_func
(paren
id|elapsed
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Elapsed time between interrupts is calculated using timer0.&n; * Latency during the interrupt is calculated using timer1.&n; * Both timer0 and timer1 are counting at 6MHz (P2 6.5MHz).&n; */
DECL|function|omap_mpu_timer_interrupt
r_static
id|irqreturn_t
id|omap_mpu_timer_interrupt
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
id|latency
suffix:semicolon
id|write_seqlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
id|now
op_assign
l_int|0
op_minus
id|omap_mpu_timer_read
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|latency
op_assign
id|MPU_TICKS_PER_SEC
op_div
id|HZ
op_minus
id|omap_mpu_timer_read
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|omap_mpu_timer_last
op_assign
id|now
op_minus
id|latency
suffix:semicolon
id|timer_tick
c_func
(paren
id|regs
)paren
suffix:semicolon
id|write_sequnlock
c_func
(paren
op_amp
id|xtime_lock
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|variable|omap_mpu_timer_irq
r_static
r_struct
id|irqaction
id|omap_mpu_timer_irq
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;mpu timer&quot;
comma
dot
id|flags
op_assign
id|SA_INTERRUPT
comma
dot
id|handler
op_assign
id|omap_mpu_timer_interrupt
)brace
suffix:semicolon
DECL|function|omap_init_mpu_timer
r_static
id|__init
r_void
id|omap_init_mpu_timer
c_func
(paren
r_void
)paren
(brace
id|omap_timer.offset
op_assign
id|omap_mpu_timer_gettimeoffset
suffix:semicolon
id|setup_irq
c_func
(paren
id|INT_TIMER2
comma
op_amp
id|omap_mpu_timer_irq
)paren
suffix:semicolon
id|omap_mpu_timer_start
c_func
(paren
l_int|0
comma
l_int|0xffffffff
)paren
suffix:semicolon
id|omap_mpu_timer_start
c_func
(paren
l_int|1
comma
id|MPU_TIMER_TICK_PERIOD
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * ---------------------------------------------------------------------------&n; * Timer initialization&n; * ---------------------------------------------------------------------------&n; */
DECL|function|omap_timer_init
r_void
id|__init
id|omap_timer_init
c_func
(paren
r_void
)paren
(brace
id|omap_init_mpu_timer
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|omap_timer
r_struct
id|sys_timer
id|omap_timer
op_assign
(brace
dot
id|init
op_assign
id|omap_timer_init
comma
dot
id|offset
op_assign
l_int|NULL
comma
multiline_comment|/* Initialized later */
)brace
suffix:semicolon
eof
