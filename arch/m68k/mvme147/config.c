multiline_comment|/*&n; *  arch/m68k/mvme147/config.c&n; *&n; *  Copyright (C) 1996 Dave Frascone [chaos@mindspring.com]&n; *  Cloned from        Richard Hirst [richard@sleepie.demon.co.uk]&n; *&n; * Based on:&n; *&n; *  Copyright (C) 1993 Hamish Macdonald&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file README.legal in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/rtc.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/rtc.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/mvme147hw.h&gt;
r_extern
id|irqreturn_t
id|mvme147_process_int
(paren
r_int
id|level
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|mvme147_init_IRQ
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mvme147_free_irq
(paren
r_int
r_int
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|show_mvme147_interrupts
(paren
r_struct
id|seq_file
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|mvme147_enable_irq
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|mvme147_disable_irq
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|mvme147_get_model
c_func
(paren
r_char
op_star
id|model
)paren
suffix:semicolon
r_static
r_int
id|mvme147_get_hardware_list
c_func
(paren
r_char
op_star
id|buffer
)paren
suffix:semicolon
r_extern
r_int
id|mvme147_request_irq
(paren
r_int
r_int
id|irq
comma
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
comma
r_int
r_int
id|flags
comma
r_const
r_char
op_star
id|devname
comma
r_void
op_star
id|dev_id
)paren
suffix:semicolon
r_extern
r_void
id|mvme147_sched_init
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
r_extern
r_int
r_int
id|mvme147_gettimeoffset
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|mvme147_hwclk
(paren
r_int
comma
r_struct
id|rtc_time
op_star
)paren
suffix:semicolon
r_extern
r_int
id|mvme147_set_clock_mmss
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|mvme147_reset
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mvme147_waitbut
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|bcd2int
(paren
r_int
r_char
id|b
)paren
suffix:semicolon
multiline_comment|/* Save tick handler routine pointer, will point to do_timer() in&n; * kernel/sched.c, called via mvme147_process_int() */
DECL|variable|tick_handler
id|irqreturn_t
(paren
op_star
id|tick_handler
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
suffix:semicolon
DECL|function|mvme147_parse_bootinfo
r_int
id|mvme147_parse_bootinfo
c_func
(paren
r_const
r_struct
id|bi_record
op_star
id|bi
)paren
(brace
r_if
c_cond
(paren
id|bi-&gt;tag
op_eq
id|BI_VME_TYPE
op_logical_or
id|bi-&gt;tag
op_eq
id|BI_VME_BRDINFO
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|mvme147_reset
r_void
id|mvme147_reset
c_func
(paren
)paren
(brace
id|printk
(paren
l_string|&quot;&bslash;r&bslash;n&bslash;nCalled mvme147_reset&bslash;r&bslash;n&quot;
)paren
suffix:semicolon
id|m147_pcc-&gt;watchdog
op_assign
l_int|0x0a
suffix:semicolon
multiline_comment|/* Clear timer */
id|m147_pcc-&gt;watchdog
op_assign
l_int|0xa5
suffix:semicolon
multiline_comment|/* Enable watchdog - 100ms to reset */
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|mvme147_get_model
r_static
r_void
id|mvme147_get_model
c_func
(paren
r_char
op_star
id|model
)paren
(brace
id|sprintf
c_func
(paren
id|model
comma
l_string|&quot;Motorola MVME147&quot;
)paren
suffix:semicolon
)brace
DECL|function|mvme147_get_hardware_list
r_static
r_int
id|mvme147_get_hardware_list
c_func
(paren
r_char
op_star
id|buffer
)paren
(brace
op_star
id|buffer
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|config_mvme147
r_void
id|__init
id|config_mvme147
c_func
(paren
r_void
)paren
(brace
id|mach_max_dma_address
op_assign
l_int|0x01000000
suffix:semicolon
id|mach_sched_init
op_assign
id|mvme147_sched_init
suffix:semicolon
id|mach_init_IRQ
op_assign
id|mvme147_init_IRQ
suffix:semicolon
id|mach_gettimeoffset
op_assign
id|mvme147_gettimeoffset
suffix:semicolon
id|mach_hwclk
op_assign
id|mvme147_hwclk
suffix:semicolon
id|mach_set_clock_mmss
op_assign
id|mvme147_set_clock_mmss
suffix:semicolon
id|mach_reset
op_assign
id|mvme147_reset
suffix:semicolon
id|mach_free_irq
op_assign
id|mvme147_free_irq
suffix:semicolon
id|mach_process_int
op_assign
id|mvme147_process_int
suffix:semicolon
id|mach_get_irq_list
op_assign
id|show_mvme147_interrupts
suffix:semicolon
id|mach_request_irq
op_assign
id|mvme147_request_irq
suffix:semicolon
id|enable_irq
op_assign
id|mvme147_enable_irq
suffix:semicolon
id|disable_irq
op_assign
id|mvme147_disable_irq
suffix:semicolon
id|mach_get_model
op_assign
id|mvme147_get_model
suffix:semicolon
id|mach_get_hardware_list
op_assign
id|mvme147_get_hardware_list
suffix:semicolon
multiline_comment|/* Board type is only set by newer versions of vmelilo/tftplilo */
r_if
c_cond
(paren
op_logical_neg
id|vme_brdtype
)paren
id|vme_brdtype
op_assign
id|VME_TYPE_MVME147
suffix:semicolon
)brace
multiline_comment|/* Using pcc tick timer 1 */
DECL|function|mvme147_timer_int
r_static
id|irqreturn_t
id|mvme147_timer_int
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
id|fp
)paren
(brace
id|m147_pcc-&gt;t1_int_cntrl
op_assign
id|PCC_TIMER_INT_CLR
suffix:semicolon
id|m147_pcc-&gt;t1_int_cntrl
op_assign
id|PCC_INT_ENAB
op_or
id|PCC_LEVEL_TIMER1
suffix:semicolon
r_return
id|tick_handler
c_func
(paren
id|irq
comma
id|dev_id
comma
id|fp
)paren
suffix:semicolon
)brace
DECL|function|mvme147_sched_init
r_void
id|mvme147_sched_init
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
id|tick_handler
op_assign
id|timer_routine
suffix:semicolon
id|request_irq
(paren
id|PCC_IRQ_TIMER1
comma
id|mvme147_timer_int
comma
id|IRQ_FLG_REPLACE
comma
l_string|&quot;timer 1&quot;
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Init the clock with a value */
multiline_comment|/* our clock goes off every 6.25us */
id|m147_pcc-&gt;t1_preload
op_assign
id|PCC_TIMER_PRELOAD
suffix:semicolon
id|m147_pcc-&gt;t1_cntrl
op_assign
l_int|0x0
suffix:semicolon
multiline_comment|/* clear timer */
id|m147_pcc-&gt;t1_cntrl
op_assign
l_int|0x3
suffix:semicolon
multiline_comment|/* start timer */
id|m147_pcc-&gt;t1_int_cntrl
op_assign
id|PCC_TIMER_INT_CLR
suffix:semicolon
multiline_comment|/* clear pending ints */
id|m147_pcc-&gt;t1_int_cntrl
op_assign
id|PCC_INT_ENAB
op_or
id|PCC_LEVEL_TIMER1
suffix:semicolon
)brace
multiline_comment|/* This is always executed with interrupts disabled.  */
multiline_comment|/* XXX There are race hazards in this code XXX */
DECL|function|mvme147_gettimeoffset
r_int
r_int
id|mvme147_gettimeoffset
(paren
r_void
)paren
(brace
r_volatile
r_int
r_int
op_star
id|cp
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
l_int|0xfffe1012
suffix:semicolon
r_int
r_int
id|n
suffix:semicolon
id|n
op_assign
op_star
id|cp
suffix:semicolon
r_while
c_loop
(paren
id|n
op_ne
op_star
id|cp
)paren
id|n
op_assign
op_star
id|cp
suffix:semicolon
id|n
op_sub_assign
id|PCC_TIMER_PRELOAD
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
id|n
op_star
l_int|25
op_div
l_int|4
suffix:semicolon
)brace
DECL|function|bcd2int
r_static
r_int
id|bcd2int
(paren
r_int
r_char
id|b
)paren
(brace
r_return
(paren
(paren
id|b
op_rshift
l_int|4
)paren
op_star
l_int|10
op_plus
(paren
id|b
op_amp
l_int|15
)paren
)paren
suffix:semicolon
)brace
DECL|function|mvme147_hwclk
r_int
id|mvme147_hwclk
c_func
(paren
r_int
id|op
comma
r_struct
id|rtc_time
op_star
id|t
)paren
(brace
macro_line|#warning check me!
r_if
c_cond
(paren
op_logical_neg
id|op
)paren
(brace
id|m147_rtc-&gt;ctrl
op_assign
id|RTC_READ
suffix:semicolon
id|t-&gt;tm_year
op_assign
id|bcd2int
(paren
id|m147_rtc-&gt;bcd_year
)paren
suffix:semicolon
id|t-&gt;tm_mon
op_assign
id|bcd2int
(paren
id|m147_rtc-&gt;bcd_mth
)paren
suffix:semicolon
id|t-&gt;tm_mday
op_assign
id|bcd2int
(paren
id|m147_rtc-&gt;bcd_dom
)paren
suffix:semicolon
id|t-&gt;tm_hour
op_assign
id|bcd2int
(paren
id|m147_rtc-&gt;bcd_hr
)paren
suffix:semicolon
id|t-&gt;tm_min
op_assign
id|bcd2int
(paren
id|m147_rtc-&gt;bcd_min
)paren
suffix:semicolon
id|t-&gt;tm_sec
op_assign
id|bcd2int
(paren
id|m147_rtc-&gt;bcd_sec
)paren
suffix:semicolon
id|m147_rtc-&gt;ctrl
op_assign
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mvme147_set_clock_mmss
r_int
id|mvme147_set_clock_mmss
(paren
r_int
r_int
id|nowtime
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*-------------------  Serial console stuff ------------------------*/
DECL|function|scc_delay
r_static
r_void
id|scc_delay
(paren
r_void
)paren
(brace
r_int
id|n
suffix:semicolon
r_volatile
r_int
id|trash
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
l_int|20
suffix:semicolon
id|n
op_increment
)paren
id|trash
op_assign
id|n
suffix:semicolon
)brace
DECL|function|scc_write
r_static
r_void
id|scc_write
(paren
r_char
id|ch
)paren
(brace
r_volatile
r_char
op_star
id|p
op_assign
(paren
r_volatile
r_char
op_star
)paren
id|M147_SCC_A_ADDR
suffix:semicolon
r_do
(brace
id|scc_delay
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
(paren
op_star
id|p
op_amp
l_int|4
)paren
)paren
suffix:semicolon
id|scc_delay
c_func
(paren
)paren
suffix:semicolon
op_star
id|p
op_assign
l_int|8
suffix:semicolon
id|scc_delay
c_func
(paren
)paren
suffix:semicolon
op_star
id|p
op_assign
id|ch
suffix:semicolon
)brace
DECL|function|m147_scc_write
r_void
id|m147_scc_write
(paren
r_struct
id|console
op_star
id|co
comma
r_const
r_char
op_star
id|str
comma
r_int
id|count
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
r_if
c_cond
(paren
op_star
id|str
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|scc_write
(paren
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
id|scc_write
(paren
op_star
id|str
op_increment
)paren
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|mvme147_init_console_port
r_void
id|mvme147_init_console_port
(paren
r_struct
id|console
op_star
id|co
comma
r_int
id|cflag
)paren
(brace
id|co-&gt;write
op_assign
id|m147_scc_write
suffix:semicolon
)brace
eof
