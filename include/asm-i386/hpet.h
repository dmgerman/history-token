macro_line|#ifndef _I386_HPET_H
DECL|macro|_I386_HPET_H
mdefine_line|#define _I386_HPET_H
macro_line|#ifdef CONFIG_HPET_TIMER
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/mpspec.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
multiline_comment|/*&n; * Documentation on HPET can be found at:&n; *      http://www.intel.com/ial/home/sp/pcmmspec.htm&n; *      ftp://download.intel.com/ial/home/sp/mmts098.pdf&n; */
DECL|macro|HPET_MMAP_SIZE
mdefine_line|#define HPET_MMAP_SIZE&t;1024
DECL|macro|HPET_ID
mdefine_line|#define HPET_ID&t;&t;0x000
DECL|macro|HPET_PERIOD
mdefine_line|#define HPET_PERIOD&t;0x004
DECL|macro|HPET_CFG
mdefine_line|#define HPET_CFG&t;0x010
DECL|macro|HPET_STATUS
mdefine_line|#define HPET_STATUS&t;0x020
DECL|macro|HPET_COUNTER
mdefine_line|#define HPET_COUNTER&t;0x0f0
DECL|macro|HPET_T0_CFG
mdefine_line|#define HPET_T0_CFG&t;0x100
DECL|macro|HPET_T0_CMP
mdefine_line|#define HPET_T0_CMP&t;0x108
DECL|macro|HPET_T0_ROUTE
mdefine_line|#define HPET_T0_ROUTE&t;0x110
DECL|macro|HPET_T1_CFG
mdefine_line|#define HPET_T1_CFG&t;0x120
DECL|macro|HPET_T1_CMP
mdefine_line|#define HPET_T1_CMP&t;0x128
DECL|macro|HPET_T1_ROUTE
mdefine_line|#define HPET_T1_ROUTE&t;0x130
DECL|macro|HPET_T2_CFG
mdefine_line|#define HPET_T2_CFG&t;0x140
DECL|macro|HPET_T2_CMP
mdefine_line|#define HPET_T2_CMP&t;0x148
DECL|macro|HPET_T2_ROUTE
mdefine_line|#define HPET_T2_ROUTE&t;0x150
DECL|macro|HPET_ID_LEGSUP
mdefine_line|#define HPET_ID_LEGSUP&t;0x00008000
DECL|macro|HPET_ID_NUMBER
mdefine_line|#define HPET_ID_NUMBER&t;0x00001f00
DECL|macro|HPET_ID_REV
mdefine_line|#define HPET_ID_REV&t;0x000000ff
DECL|macro|HPET_ID_NUMBER_SHIFT
mdefine_line|#define&t;HPET_ID_NUMBER_SHIFT&t;8
DECL|macro|HPET_CFG_ENABLE
mdefine_line|#define HPET_CFG_ENABLE&t;0x001
DECL|macro|HPET_CFG_LEGACY
mdefine_line|#define HPET_CFG_LEGACY&t;0x002
DECL|macro|HPET_LEGACY_8254
mdefine_line|#define&t;HPET_LEGACY_8254&t;2
DECL|macro|HPET_LEGACY_RTC
mdefine_line|#define&t;HPET_LEGACY_RTC&t;&t;8
DECL|macro|HPET_TN_ENABLE
mdefine_line|#define HPET_TN_ENABLE&t;&t;0x004
DECL|macro|HPET_TN_PERIODIC
mdefine_line|#define HPET_TN_PERIODIC&t;0x008
DECL|macro|HPET_TN_PERIODIC_CAP
mdefine_line|#define HPET_TN_PERIODIC_CAP&t;0x010
DECL|macro|HPET_TN_SETVAL
mdefine_line|#define HPET_TN_SETVAL&t;&t;0x040
DECL|macro|HPET_TN_32BIT
mdefine_line|#define HPET_TN_32BIT&t;&t;0x100
multiline_comment|/* Use our own asm for 64 bit multiply/divide */
DECL|macro|ASM_MUL64_REG
mdefine_line|#define ASM_MUL64_REG(eax_out,edx_out,reg_in,eax_in) &t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&quot;mull %2&quot; &t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;:&quot;=a&quot; (eax_out), &quot;=d&quot; (edx_out) &t;&bslash;&n;&t;&t;&t;&t;:&quot;r&quot; (reg_in), &quot;0&quot; (eax_in))
DECL|macro|ASM_DIV64_REG
mdefine_line|#define ASM_DIV64_REG(eax_out,edx_out,reg_in,eax_in,edx_in) &t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&quot;divl %2&quot; &t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;:&quot;=a&quot; (eax_out), &quot;=d&quot; (edx_out) &t;&bslash;&n;&t;&t;&t;&t;:&quot;r&quot; (reg_in), &quot;0&quot; (eax_in), &quot;1&quot; (edx_in))
DECL|macro|KERNEL_TICK_USEC
mdefine_line|#define KERNEL_TICK_USEC &t;(1000000UL/HZ)&t;/* tick value in microsec */
multiline_comment|/* Max HPET Period is 10^8 femto sec as in HPET spec */
DECL|macro|HPET_MAX_PERIOD
mdefine_line|#define HPET_MAX_PERIOD (100000000UL)
multiline_comment|/*&n; * Min HPET period is 10^5 femto sec just for safety. If it is less than this,&n; * then 32 bit HPET counter wrapsaround in less than 0.5 sec.&n; */
DECL|macro|HPET_MIN_PERIOD
mdefine_line|#define HPET_MIN_PERIOD (100000UL)
r_extern
r_int
r_int
id|hpet_period
suffix:semicolon
multiline_comment|/* fsecs / HPET clock */
r_extern
r_int
r_int
id|hpet_tick
suffix:semicolon
multiline_comment|/* hpet clks count per tick */
r_extern
r_int
r_int
id|hpet_address
suffix:semicolon
multiline_comment|/* hpet memory map physical address */
r_extern
r_int
id|hpet_rtc_timer_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|hpet_enable
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|hpet_reenable
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|is_hpet_enabled
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|is_hpet_capable
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|hpet_readl
c_func
(paren
r_int
r_int
id|a
)paren
suffix:semicolon
r_extern
r_void
id|hpet_writel
c_func
(paren
r_int
r_int
id|d
comma
r_int
r_int
id|a
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HPET_EMULATE_RTC
r_extern
r_int
id|hpet_mask_rtc_irq_bit
c_func
(paren
r_int
r_int
id|bit_mask
)paren
suffix:semicolon
r_extern
r_int
id|hpet_set_rtc_irq_bit
c_func
(paren
r_int
r_int
id|bit_mask
)paren
suffix:semicolon
r_extern
r_int
id|hpet_set_alarm_time
c_func
(paren
r_int
r_char
id|hrs
comma
r_int
r_char
id|min
comma
r_int
r_char
id|sec
)paren
suffix:semicolon
r_extern
r_int
id|hpet_set_periodic_freq
c_func
(paren
r_int
r_int
id|freq
)paren
suffix:semicolon
r_extern
r_int
id|hpet_rtc_dropped_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|hpet_rtc_timer_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|irqreturn_t
id|hpet_rtc_interrupt
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
suffix:semicolon
macro_line|#endif /* CONFIG_HPET_EMULATE_RTC */
macro_line|#endif /* CONFIG_HPET_TIMER */
macro_line|#endif /* _I386_HPET_H */
eof
