multiline_comment|/*&n; *  linux/include/asm-arm/arch-integrator/time.h&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/leds.h&gt;
multiline_comment|/*&n; * Where is the timer (VA)?&n; */
DECL|macro|TIMER0_VA_BASE
mdefine_line|#define TIMER0_VA_BASE (IO_ADDRESS(INTEGRATOR_CT_BASE)+0x00000000)
DECL|macro|TIMER1_VA_BASE
mdefine_line|#define TIMER1_VA_BASE (IO_ADDRESS(INTEGRATOR_CT_BASE)+0x00000100)
DECL|macro|TIMER2_VA_BASE
mdefine_line|#define TIMER2_VA_BASE (IO_ADDRESS(INTEGRATOR_CT_BASE)+0x00000200)
DECL|macro|VA_IC_BASE
mdefine_line|#define VA_IC_BASE     IO_ADDRESS(INTEGRATOR_IC_BASE) 
multiline_comment|/*&n; * How long is the timer interval?&n; */
DECL|macro|TIMER_INTERVAL
mdefine_line|#define TIMER_INTERVAL&t;(TICKS_PER_uSEC * mSEC_10)
macro_line|#if TIMER_INTERVAL &gt;= 0x100000
DECL|macro|TIMER_RELOAD
mdefine_line|#define TIMER_RELOAD&t;(TIMER_INTERVAL &gt;&gt; 8)&t;&t;/* Divide by 256 */
DECL|macro|TIMER_CTRL
mdefine_line|#define TIMER_CTRL&t;0x88&t;&t;&t;&t;/* Enable, Clock / 256 */
DECL|macro|TICKS2USECS
mdefine_line|#define TICKS2USECS(x)&t;(256 * (x) / TICKS_PER_uSEC)
macro_line|#elif TIMER_INTERVAL &gt;= 0x10000
DECL|macro|TIMER_RELOAD
mdefine_line|#define TIMER_RELOAD&t;(TIMER_INTERVAL &gt;&gt; 4)&t;&t;/* Divide by 16 */
DECL|macro|TIMER_CTRL
mdefine_line|#define TIMER_CTRL&t;0x84&t;&t;&t;&t;/* Enable, Clock / 16 */
DECL|macro|TICKS2USECS
mdefine_line|#define TICKS2USECS(x)&t;(16 * (x) / TICKS_PER_uSEC)
macro_line|#else
DECL|macro|TIMER_RELOAD
mdefine_line|#define TIMER_RELOAD&t;(TIMER_INTERVAL)
DECL|macro|TIMER_CTRL
mdefine_line|#define TIMER_CTRL&t;0x80&t;&t;&t;&t;/* Enable */
DECL|macro|TICKS2USECS
mdefine_line|#define TICKS2USECS(x)&t;((x) / TICKS_PER_uSEC)
macro_line|#endif
multiline_comment|/*&n; * What does it look like?&n; */
DECL|struct|TimerStruct
r_typedef
r_struct
id|TimerStruct
(brace
DECL|member|TimerLoad
r_int
r_int
id|TimerLoad
suffix:semicolon
DECL|member|TimerValue
r_int
r_int
id|TimerValue
suffix:semicolon
DECL|member|TimerControl
r_int
r_int
id|TimerControl
suffix:semicolon
DECL|member|TimerClear
r_int
r_int
id|TimerClear
suffix:semicolon
DECL|typedef|TimerStruct_t
)brace
id|TimerStruct_t
suffix:semicolon
r_extern
r_int
r_int
(paren
op_star
id|gettimeoffset
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Returns number of ms since last clock interrupt.  Note that interrupts&n; * will have been disabled by do_gettimeoffset()&n; */
DECL|function|integrator_gettimeoffset
r_static
r_int
r_int
id|integrator_gettimeoffset
c_func
(paren
r_void
)paren
(brace
r_volatile
id|TimerStruct_t
op_star
id|timer1
op_assign
(paren
id|TimerStruct_t
op_star
)paren
id|TIMER1_VA_BASE
suffix:semicolon
r_int
r_int
id|ticks1
comma
id|ticks2
comma
id|status
suffix:semicolon
multiline_comment|/*&n;&t; * Get the current number of ticks.  Note that there is a race&n;&t; * condition between us reading the timer and checking for&n;&t; * an interrupt.  We get around this by ensuring that the&n;&t; * counter has not reloaded between our two reads.&n;&t; */
id|ticks2
op_assign
id|timer1-&gt;TimerValue
op_amp
l_int|0xffff
suffix:semicolon
r_do
(brace
id|ticks1
op_assign
id|ticks2
suffix:semicolon
id|status
op_assign
id|__raw_readl
c_func
(paren
id|VA_IC_BASE
op_plus
id|IRQ_RAW_STATUS
)paren
suffix:semicolon
id|ticks2
op_assign
id|timer1-&gt;TimerValue
op_amp
l_int|0xffff
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ticks2
OG
id|ticks1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Number of ticks since last interrupt.&n;&t; */
id|ticks1
op_assign
id|TIMER_RELOAD
op_minus
id|ticks2
suffix:semicolon
multiline_comment|/*&n;&t; * Interrupt pending?  If so, we&squot;ve reloaded once already.&n;&t; */
r_if
c_cond
(paren
id|status
op_amp
id|IRQMASK_TIMERINT1
)paren
id|ticks1
op_add_assign
id|TIMER_RELOAD
suffix:semicolon
multiline_comment|/*&n;&t; * Convert the ticks to usecs&n;&t; */
r_return
id|TICKS2USECS
c_func
(paren
id|ticks1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * IRQ handler for the timer&n; */
DECL|function|integrator_timer_interrupt
r_static
r_void
id|integrator_timer_interrupt
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
r_volatile
id|TimerStruct_t
op_star
id|timer1
op_assign
(paren
r_volatile
id|TimerStruct_t
op_star
)paren
id|TIMER1_VA_BASE
suffix:semicolon
singleline_comment|// ...clear the interrupt
id|timer1-&gt;TimerClear
op_assign
l_int|1
suffix:semicolon
id|do_leds
c_func
(paren
)paren
suffix:semicolon
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
id|do_profile
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up timer interrupt, and return the current time in seconds.&n; */
DECL|function|setup_timer
r_extern
id|__inline__
r_void
id|setup_timer
c_func
(paren
r_void
)paren
(brace
r_volatile
id|TimerStruct_t
op_star
id|timer0
op_assign
(paren
r_volatile
id|TimerStruct_t
op_star
)paren
id|TIMER0_VA_BASE
suffix:semicolon
r_volatile
id|TimerStruct_t
op_star
id|timer1
op_assign
(paren
r_volatile
id|TimerStruct_t
op_star
)paren
id|TIMER1_VA_BASE
suffix:semicolon
r_volatile
id|TimerStruct_t
op_star
id|timer2
op_assign
(paren
r_volatile
id|TimerStruct_t
op_star
)paren
id|TIMER2_VA_BASE
suffix:semicolon
id|timer_irq.handler
op_assign
id|integrator_timer_interrupt
suffix:semicolon
multiline_comment|/*&n;&t; * Initialise to a known state (all timers off)&n;&t; */
id|timer0-&gt;TimerControl
op_assign
l_int|0
suffix:semicolon
id|timer1-&gt;TimerControl
op_assign
l_int|0
suffix:semicolon
id|timer2-&gt;TimerControl
op_assign
l_int|0
suffix:semicolon
id|timer1-&gt;TimerLoad
op_assign
id|TIMER_RELOAD
suffix:semicolon
id|timer1-&gt;TimerValue
op_assign
id|TIMER_RELOAD
suffix:semicolon
id|timer1-&gt;TimerControl
op_assign
id|TIMER_CTRL
op_or
l_int|0x40
suffix:semicolon
multiline_comment|/* periodic */
multiline_comment|/* &n;&t; * Make irqs happen for the system timer&n;&t; */
id|setup_arm_irq
c_func
(paren
id|IRQ_TIMERINT1
comma
op_amp
id|timer_irq
)paren
suffix:semicolon
id|gettimeoffset
op_assign
id|integrator_gettimeoffset
suffix:semicolon
)brace
eof
