multiline_comment|/*&n; *  arch/m68k/q40/config.c&n; *&n; *  Copyright (C) 1999 Richard Zidlicky&n; *&n; * originally based on:&n; *&n; *  linux/bvme/config.c&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file README.legal in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/serial_reg.h&gt;
macro_line|#include &lt;linux/rtc.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/rtc.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/rtc.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/q40_master.h&gt;
r_extern
r_void
id|floppy_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
suffix:semicolon
r_extern
id|irqreturn_t
id|q40_process_int
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
id|irqreturn_t
(paren
op_star
id|q40_sys_default_handler
(braket
)braket
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
multiline_comment|/* added just for debugging */
r_extern
r_void
id|q40_init_IRQ
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|q40_free_irq
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
id|show_q40_interrupts
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
id|q40_enable_irq
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|q40_disable_irq
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|q40_get_model
c_func
(paren
r_char
op_star
id|model
)paren
suffix:semicolon
r_static
r_int
id|q40_get_hardware_list
c_func
(paren
r_char
op_star
id|buffer
)paren
suffix:semicolon
r_extern
r_int
id|q40_request_irq
c_func
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
id|q40_sched_init
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
id|q40_gettimeoffset
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|q40_hwclk
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
r_int
id|q40_get_ss
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|q40_set_clock_mmss
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_int
id|q40_get_rtc_pll
c_func
(paren
r_struct
id|rtc_pll_info
op_star
id|pll
)paren
suffix:semicolon
r_static
r_int
id|q40_set_rtc_pll
c_func
(paren
r_struct
id|rtc_pll_info
op_star
id|pll
)paren
suffix:semicolon
r_extern
r_void
id|q40_reset
(paren
r_void
)paren
suffix:semicolon
r_void
id|q40_halt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|q40_waitbut
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|q40_set_vectors
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|q40_mksound
c_func
(paren
r_int
r_int
multiline_comment|/*freq*/
comma
r_int
r_int
multiline_comment|/*ticks*/
)paren
suffix:semicolon
r_extern
r_char
op_star
id|saved_command_line
suffix:semicolon
r_extern
r_char
id|m68k_debug_device
(braket
)braket
suffix:semicolon
r_static
r_void
id|q40_mem_console_write
c_func
(paren
r_struct
id|console
op_star
id|co
comma
r_const
r_char
op_star
id|b
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_int
id|ql_ticks
suffix:semicolon
DECL|variable|q40_console_driver
r_static
r_struct
id|console
id|q40_console_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;debug&quot;
comma
dot
id|flags
op_assign
id|CON_PRINTBUFFER
comma
dot
id|index
op_assign
op_minus
l_int|1
comma
)brace
suffix:semicolon
multiline_comment|/* early debugging function:*/
r_extern
r_char
op_star
id|q40_mem_cptr
suffix:semicolon
multiline_comment|/*=(char *)0xff020000;*/
DECL|variable|_cpleft
r_static
r_int
id|_cpleft
suffix:semicolon
DECL|function|q40_mem_console_write
r_static
r_void
id|q40_mem_console_write
c_func
(paren
r_struct
id|console
op_star
id|co
comma
r_const
r_char
op_star
id|s
comma
r_int
r_int
id|count
)paren
(brace
r_char
op_star
id|p
op_assign
(paren
r_char
op_star
)paren
id|s
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
id|_cpleft
)paren
r_while
c_loop
(paren
id|count
op_decrement
OG
l_int|0
)paren
(brace
op_star
id|q40_mem_cptr
op_assign
op_star
id|p
op_increment
suffix:semicolon
id|q40_mem_cptr
op_add_assign
l_int|4
suffix:semicolon
id|_cpleft
op_decrement
suffix:semicolon
)brace
)brace
macro_line|#if 0
r_void
id|printq40
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|l
op_assign
id|strlen
c_func
(paren
id|str
)paren
suffix:semicolon
r_char
op_star
id|p
op_assign
id|q40_mem_cptr
suffix:semicolon
r_while
c_loop
(paren
id|l
op_decrement
OG
l_int|0
op_logical_and
id|_cpleft
op_decrement
OG
l_int|0
)paren
(brace
op_star
id|p
op_assign
op_star
id|str
op_increment
suffix:semicolon
id|p
op_add_assign
l_int|4
suffix:semicolon
)brace
id|q40_mem_cptr
op_assign
id|p
suffix:semicolon
)brace
macro_line|#endif
DECL|variable|halted
r_static
r_int
id|halted
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_HEARTBEAT
DECL|function|q40_heartbeat
r_static
r_void
id|q40_heartbeat
c_func
(paren
r_int
id|on
)paren
(brace
r_if
c_cond
(paren
id|halted
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|on
)paren
id|Q40_LED_ON
c_func
(paren
)paren
suffix:semicolon
r_else
id|Q40_LED_OFF
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|q40_reset
r_void
id|q40_reset
c_func
(paren
)paren
(brace
id|halted
op_assign
l_int|1
suffix:semicolon
id|printk
(paren
l_string|&quot;&bslash;n&bslash;n*******************************************&bslash;n&quot;
l_string|&quot;Called q40_reset : press the RESET button!! &bslash;n&quot;
l_string|&quot;*******************************************&bslash;n&quot;
)paren
suffix:semicolon
id|Q40_LED_ON
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
)brace
DECL|function|q40_halt
r_void
id|q40_halt
c_func
(paren
)paren
(brace
id|halted
op_assign
l_int|1
suffix:semicolon
id|printk
(paren
l_string|&quot;&bslash;n&bslash;n*******************&bslash;n&quot;
l_string|&quot;  Called q40_halt&bslash;n&quot;
l_string|&quot;*******************&bslash;n&quot;
)paren
suffix:semicolon
id|Q40_LED_ON
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
)brace
DECL|function|q40_get_model
r_static
r_void
id|q40_get_model
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
l_string|&quot;Q40&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* No hardware options on Q40? */
DECL|function|q40_get_hardware_list
r_static
r_int
id|q40_get_hardware_list
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
DECL|variable|serports
r_static
r_int
r_int
id|serports
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|function|q40_disable_irqs
r_void
id|q40_disable_irqs
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
id|j
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|i
op_assign
id|serports
(braket
id|j
op_increment
)braket
)paren
)paren
(brace
id|outb
c_func
(paren
l_int|0
comma
id|i
op_plus
id|UART_IER
)paren
suffix:semicolon
)brace
id|master_outb
c_func
(paren
l_int|0
comma
id|EXT_ENABLE_REG
)paren
suffix:semicolon
id|master_outb
c_func
(paren
l_int|0
comma
id|KEY_IRQ_ENABLE_REG
)paren
suffix:semicolon
)brace
DECL|function|config_q40
r_void
id|__init
id|config_q40
c_func
(paren
r_void
)paren
(brace
id|mach_sched_init
op_assign
id|q40_sched_init
suffix:semicolon
id|mach_init_IRQ
op_assign
id|q40_init_IRQ
suffix:semicolon
id|mach_gettimeoffset
op_assign
id|q40_gettimeoffset
suffix:semicolon
id|mach_hwclk
op_assign
id|q40_hwclk
suffix:semicolon
id|mach_get_ss
op_assign
id|q40_get_ss
suffix:semicolon
id|mach_get_rtc_pll
op_assign
id|q40_get_rtc_pll
suffix:semicolon
id|mach_set_rtc_pll
op_assign
id|q40_set_rtc_pll
suffix:semicolon
id|mach_set_clock_mmss
op_assign
id|q40_set_clock_mmss
suffix:semicolon
id|mach_reset
op_assign
id|q40_reset
suffix:semicolon
id|mach_free_irq
op_assign
id|q40_free_irq
suffix:semicolon
id|mach_process_int
op_assign
id|q40_process_int
suffix:semicolon
id|mach_get_irq_list
op_assign
id|show_q40_interrupts
suffix:semicolon
id|mach_request_irq
op_assign
id|q40_request_irq
suffix:semicolon
id|enable_irq
op_assign
id|q40_enable_irq
suffix:semicolon
id|disable_irq
op_assign
id|q40_disable_irq
suffix:semicolon
id|mach_default_handler
op_assign
op_amp
id|q40_sys_default_handler
suffix:semicolon
id|mach_get_model
op_assign
id|q40_get_model
suffix:semicolon
id|mach_get_hardware_list
op_assign
id|q40_get_hardware_list
suffix:semicolon
macro_line|#if defined(CONFIG_INPUT_M68K_BEEP) || defined(CONFIG_INPUT_M68K_BEEP_MODULE)
id|mach_beep
op_assign
id|q40_mksound
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_HEARTBEAT
id|mach_heartbeat
op_assign
id|q40_heartbeat
suffix:semicolon
macro_line|#endif
id|mach_halt
op_assign
id|q40_halt
suffix:semicolon
macro_line|#ifdef CONFIG_DUMMY_CONSOLE
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|#endif
multiline_comment|/* disable a few things that SMSQ might have left enabled */
id|q40_disable_irqs
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* no DMA at all, but ide-scsi requires it.. make sure&n;     * all physical RAM fits into the boundary - otherwise &n;     * allocator may play costly and useless tricks */
id|mach_max_dma_address
op_assign
l_int|1024
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
multiline_comment|/* useful for early debugging stages - writes kernel messages into SRAM */
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|m68k_debug_device
comma
l_string|&quot;mem&quot;
comma
l_int|3
)paren
)paren
(brace
multiline_comment|/*printk(&quot;using NVRAM debug, q40_mem_cptr=%p&bslash;n&quot;,q40_mem_cptr);*/
id|_cpleft
op_assign
l_int|2000
op_minus
(paren
(paren
r_int
)paren
id|q40_mem_cptr
op_minus
l_int|0xff020000
)paren
op_div
l_int|4
suffix:semicolon
id|q40_console_driver.write
op_assign
id|q40_mem_console_write
suffix:semicolon
id|register_console
c_func
(paren
op_amp
id|q40_console_driver
)paren
suffix:semicolon
)brace
)brace
DECL|function|q40_parse_bootinfo
r_int
id|q40_parse_bootinfo
c_func
(paren
r_const
r_struct
id|bi_record
op_star
id|rec
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|bcd2bin
r_static
r_inline
r_int
r_char
id|bcd2bin
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
DECL|function|bin2bcd
r_static
r_inline
r_int
r_char
id|bin2bcd
(paren
r_int
r_char
id|b
)paren
(brace
r_return
(paren
(paren
(paren
id|b
op_div
l_int|10
)paren
op_star
l_int|16
)paren
op_plus
(paren
id|b
op_mod
l_int|10
)paren
)paren
suffix:semicolon
)brace
DECL|function|q40_gettimeoffset
r_int
r_int
id|q40_gettimeoffset
(paren
r_void
)paren
(brace
r_return
l_int|5000
op_star
(paren
id|ql_ticks
op_ne
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Looks like op is non-zero for setting the clock, and zero for&n; * reading the clock.&n; *&n; *  struct hwclk_time {&n; *         unsigned        sec;       0..59&n; *         unsigned        min;       0..59&n; *         unsigned        hour;      0..23&n; *         unsigned        day;       1..31&n; *         unsigned        mon;       0..11&n; *         unsigned        year;      00...&n; *         int             wday;      0..6, 0 is Sunday, -1 means unknown/don&squot;t set&n; * };&n; */
DECL|function|q40_hwclk
r_int
id|q40_hwclk
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
r_if
c_cond
(paren
id|op
)paren
(brace
multiline_comment|/* Write.... */
id|Q40_RTC_CTRL
op_or_assign
id|Q40_RTC_WRITE
suffix:semicolon
id|Q40_RTC_SECS
op_assign
id|bin2bcd
c_func
(paren
id|t-&gt;tm_sec
)paren
suffix:semicolon
id|Q40_RTC_MINS
op_assign
id|bin2bcd
c_func
(paren
id|t-&gt;tm_min
)paren
suffix:semicolon
id|Q40_RTC_HOUR
op_assign
id|bin2bcd
c_func
(paren
id|t-&gt;tm_hour
)paren
suffix:semicolon
id|Q40_RTC_DATE
op_assign
id|bin2bcd
c_func
(paren
id|t-&gt;tm_mday
)paren
suffix:semicolon
id|Q40_RTC_MNTH
op_assign
id|bin2bcd
c_func
(paren
id|t-&gt;tm_mon
op_plus
l_int|1
)paren
suffix:semicolon
id|Q40_RTC_YEAR
op_assign
id|bin2bcd
c_func
(paren
id|t-&gt;tm_year
op_mod
l_int|100
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;tm_wday
op_ge
l_int|0
)paren
id|Q40_RTC_DOW
op_assign
id|bin2bcd
c_func
(paren
id|t-&gt;tm_wday
op_plus
l_int|1
)paren
suffix:semicolon
id|Q40_RTC_CTRL
op_and_assign
op_complement
(paren
id|Q40_RTC_WRITE
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Read....  */
id|Q40_RTC_CTRL
op_or_assign
id|Q40_RTC_READ
suffix:semicolon
id|t-&gt;tm_year
op_assign
id|bcd2bin
(paren
id|Q40_RTC_YEAR
)paren
suffix:semicolon
id|t-&gt;tm_mon
op_assign
id|bcd2bin
(paren
id|Q40_RTC_MNTH
)paren
op_minus
l_int|1
suffix:semicolon
id|t-&gt;tm_mday
op_assign
id|bcd2bin
(paren
id|Q40_RTC_DATE
)paren
suffix:semicolon
id|t-&gt;tm_hour
op_assign
id|bcd2bin
(paren
id|Q40_RTC_HOUR
)paren
suffix:semicolon
id|t-&gt;tm_min
op_assign
id|bcd2bin
(paren
id|Q40_RTC_MINS
)paren
suffix:semicolon
id|t-&gt;tm_sec
op_assign
id|bcd2bin
(paren
id|Q40_RTC_SECS
)paren
suffix:semicolon
id|Q40_RTC_CTRL
op_and_assign
op_complement
(paren
id|Q40_RTC_READ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;tm_year
OL
l_int|70
)paren
id|t-&gt;tm_year
op_add_assign
l_int|100
suffix:semicolon
id|t-&gt;tm_wday
op_assign
id|bcd2bin
c_func
(paren
id|Q40_RTC_DOW
)paren
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|q40_get_ss
r_int
r_int
id|q40_get_ss
c_func
(paren
)paren
(brace
r_return
id|bcd2bin
c_func
(paren
id|Q40_RTC_SECS
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set the minutes and seconds from seconds value &squot;nowtime&squot;.  Fail if&n; * clock is out by &gt; 30 minutes.  Logic lifted from atari code.&n; */
DECL|function|q40_set_clock_mmss
r_int
id|q40_set_clock_mmss
(paren
r_int
r_int
id|nowtime
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
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
r_int
id|rtc_minutes
suffix:semicolon
id|rtc_minutes
op_assign
id|bcd2bin
(paren
id|Q40_RTC_MINS
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rtc_minutes
OL
id|real_minutes
ques
c_cond
id|real_minutes
op_minus
id|rtc_minutes
suffix:colon
id|rtc_minutes
op_minus
id|real_minutes
)paren
OL
l_int|30
)paren
(brace
id|Q40_RTC_CTRL
op_or_assign
id|Q40_RTC_WRITE
suffix:semicolon
id|Q40_RTC_MINS
op_assign
id|bin2bcd
c_func
(paren
id|real_minutes
)paren
suffix:semicolon
id|Q40_RTC_SECS
op_assign
id|bin2bcd
c_func
(paren
id|real_seconds
)paren
suffix:semicolon
id|Q40_RTC_CTRL
op_and_assign
op_complement
(paren
id|Q40_RTC_WRITE
)paren
suffix:semicolon
)brace
r_else
id|retval
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* get and set PLL calibration of RTC clock */
DECL|macro|Q40_RTC_PLL_MASK
mdefine_line|#define Q40_RTC_PLL_MASK ((1&lt;&lt;5)-1)
DECL|macro|Q40_RTC_PLL_SIGN
mdefine_line|#define Q40_RTC_PLL_SIGN (1&lt;&lt;5)
DECL|function|q40_get_rtc_pll
r_static
r_int
id|q40_get_rtc_pll
c_func
(paren
r_struct
id|rtc_pll_info
op_star
id|pll
)paren
(brace
r_int
id|tmp
op_assign
id|Q40_RTC_CTRL
suffix:semicolon
id|pll-&gt;pll_value
op_assign
id|tmp
op_amp
id|Q40_RTC_PLL_MASK
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|Q40_RTC_PLL_SIGN
)paren
id|pll-&gt;pll_value
op_assign
op_minus
id|pll-&gt;pll_value
suffix:semicolon
id|pll-&gt;pll_max
op_assign
l_int|31
suffix:semicolon
id|pll-&gt;pll_min
op_assign
op_minus
l_int|31
suffix:semicolon
id|pll-&gt;pll_posmult
op_assign
l_int|512
suffix:semicolon
id|pll-&gt;pll_negmult
op_assign
l_int|256
suffix:semicolon
id|pll-&gt;pll_clock
op_assign
l_int|125829120
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|q40_set_rtc_pll
r_static
r_int
id|q40_set_rtc_pll
c_func
(paren
r_struct
id|rtc_pll_info
op_star
id|pll
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pll-&gt;pll_ctrl
)paren
(brace
multiline_comment|/* the docs are a bit unclear so I am doublesetting */
multiline_comment|/* RTC_WRITE here ... */
r_int
id|tmp
op_assign
(paren
id|pll-&gt;pll_value
op_amp
l_int|31
)paren
op_or
(paren
id|pll-&gt;pll_value
OL
l_int|0
ques
c_cond
l_int|32
suffix:colon
l_int|0
)paren
op_or
id|Q40_RTC_WRITE
suffix:semicolon
id|Q40_RTC_CTRL
op_or_assign
id|Q40_RTC_WRITE
suffix:semicolon
id|Q40_RTC_CTRL
op_assign
id|tmp
suffix:semicolon
id|Q40_RTC_CTRL
op_and_assign
op_complement
(paren
id|Q40_RTC_WRITE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
eof
