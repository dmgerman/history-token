multiline_comment|/*&n; * This code largely moved from arch/i386/kernel/time.c.&n; * See comments there for proper credits.&n; */
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/mpspec.h&gt;
macro_line|#include &lt;asm/timer.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/arch_hooks.h&gt;
r_extern
id|spinlock_t
id|i8259A_lock
suffix:semicolon
r_extern
id|spinlock_t
id|i8253_lock
suffix:semicolon
macro_line|#include &quot;do_timer.h&quot;
macro_line|#include &quot;io_ports.h&quot;
DECL|variable|count_p
r_static
r_int
id|count_p
suffix:semicolon
multiline_comment|/* counter in get_offset_pit() */
DECL|function|init_pit
r_static
r_int
id|__init
id|init_pit
c_func
(paren
r_char
op_star
id|override
)paren
(brace
multiline_comment|/* check clock override */
r_if
c_cond
(paren
id|override
(braket
l_int|0
)braket
op_logical_and
id|strncmp
c_func
(paren
id|override
comma
l_string|&quot;pit&quot;
comma
l_int|3
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Warning: clock= override failed. Defaulting to PIT&bslash;n&quot;
)paren
suffix:semicolon
id|count_p
op_assign
id|LATCH
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mark_offset_pit
r_static
r_void
id|mark_offset_pit
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* nothing needed */
)brace
DECL|function|monotonic_clock_pit
r_static
r_int
r_int
r_int
id|monotonic_clock_pit
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|delay_pit
r_static
r_void
id|delay_pit
c_func
(paren
r_int
r_int
id|loops
)paren
(brace
r_int
id|d0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;tjmp 1f&bslash;n&quot;
l_string|&quot;.align 16&bslash;n&quot;
l_string|&quot;1:&bslash;tjmp 2f&bslash;n&quot;
l_string|&quot;.align 16&bslash;n&quot;
l_string|&quot;2:&bslash;tdecl %0&bslash;n&bslash;tjns 2b&quot;
suffix:colon
l_string|&quot;=&amp;a&quot;
(paren
id|d0
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|loops
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* This function must be called with xtime_lock held.&n; * It was inspired by Steve McCanne&squot;s microtime-i386 for BSD.  -- jrs&n; * &n; * However, the pc-audio speaker driver changes the divisor so that&n; * it gets interrupted rather more often - it loads 64 into the&n; * counter rather than 11932! This has an adverse impact on&n; * do_gettimeoffset() -- it stops working! What is also not&n; * good is that the interval that our timer function gets called&n; * is no longer 10.0002 ms, but 9.9767 ms. To get around this&n; * would require using a different timing source. Maybe someone&n; * could use the RTC - I know that this can interrupt at frequencies&n; * ranging from 8192Hz to 2Hz. If I had the energy, I&squot;d somehow fix&n; * it so that at startup, the timer code in sched.c would select&n; * using either the RTC or the 8253 timer. The decision would be&n; * based on whether there was any other device around that needed&n; * to trample on the 8253. I&squot;d set up the RTC to interrupt at 1024 Hz,&n; * and then do some jiggery to have a version of do_timer that &n; * advanced the clock by 1/1024 s. Every time that reached over 1/100&n; * of a second, then do all the old code. If the time was kept correct&n; * then do_gettimeoffset could just return 0 - there is no low order&n; * divider that can be accessed.&n; *&n; * Ideally, you would be able to use the RTC for the speaker driver,&n; * but it appears that the speaker driver really needs interrupt more&n; * often than every 120 us or so.&n; *&n; * Anyway, this needs more thought....&t;&t;pjsg (1993-08-28)&n; * &n; * If you are really that interested, you should be reading&n; * comp.protocols.time.ntp!&n; */
DECL|function|get_offset_pit
r_static
r_int
r_int
id|get_offset_pit
c_func
(paren
r_void
)paren
(brace
r_int
id|count
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_static
r_int
r_int
id|jiffies_p
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * cache volatile jiffies temporarily; we have xtime_lock. &n;&t; */
r_int
r_int
id|jiffies_t
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|i8253_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* timer count may underflow right here */
id|outb_p
c_func
(paren
l_int|0x00
comma
id|PIT_MODE
)paren
suffix:semicolon
multiline_comment|/* latch the count ASAP */
id|count
op_assign
id|inb_p
c_func
(paren
id|PIT_CH0
)paren
suffix:semicolon
multiline_comment|/* read the latched count */
multiline_comment|/*&n;&t; * We do this guaranteed double memory access instead of a _p &n;&t; * postfix in the previous port access. Wheee, hackady hack&n;&t; */
id|jiffies_t
op_assign
id|jiffies
suffix:semicolon
id|count
op_or_assign
id|inb_p
c_func
(paren
id|PIT_CH0
)paren
op_lshift
l_int|8
suffix:semicolon
multiline_comment|/* VIA686a test code... reset the latch if count &gt; max + 1 */
r_if
c_cond
(paren
id|count
OG
id|LATCH
)paren
(brace
id|outb_p
c_func
(paren
l_int|0x34
comma
id|PIT_MODE
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|LATCH
op_amp
l_int|0xff
comma
id|PIT_CH0
)paren
suffix:semicolon
id|outb
c_func
(paren
id|LATCH
op_rshift
l_int|8
comma
id|PIT_CH0
)paren
suffix:semicolon
id|count
op_assign
id|LATCH
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * avoiding timer inconsistencies (they are rare, but they happen)...&n;&t; * there are two kinds of problems that must be avoided here:&n;&t; *  1. the timer counter underflows&n;&t; *  2. hardware problem with the timer, not giving us continuous time,&n;&t; *     the counter does small &quot;jumps&quot; upwards on some Pentium systems,&n;&t; *     (see c&squot;t 95/10 page 335 for Neptun bug.)&n;&t; */
r_if
c_cond
(paren
id|jiffies_t
op_eq
id|jiffies_p
)paren
(brace
r_if
c_cond
(paren
id|count
OG
id|count_p
)paren
(brace
multiline_comment|/* the nutcase */
id|count
op_assign
id|do_timer_overflow
c_func
(paren
id|count
)paren
suffix:semicolon
)brace
)brace
r_else
id|jiffies_p
op_assign
id|jiffies_t
suffix:semicolon
id|count_p
op_assign
id|count
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|i8253_lock
comma
id|flags
)paren
suffix:semicolon
id|count
op_assign
(paren
(paren
id|LATCH
op_minus
l_int|1
)paren
op_minus
id|count
)paren
op_star
id|TICK_SIZE
suffix:semicolon
id|count
op_assign
(paren
id|count
op_plus
id|LATCH
op_div
l_int|2
)paren
op_div
id|LATCH
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/* tsc timer_opts struct */
DECL|variable|timer_pit
r_struct
id|timer_opts
id|timer_pit
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;pit&quot;
comma
dot
id|mark_offset
op_assign
id|mark_offset_pit
comma
dot
id|get_offset
op_assign
id|get_offset_pit
comma
dot
id|monotonic_clock
op_assign
id|monotonic_clock_pit
comma
dot
id|delay
op_assign
id|delay_pit
comma
)brace
suffix:semicolon
DECL|variable|timer_pit_init
r_struct
id|init_timer_opts
id|__initdata
id|timer_pit_init
op_assign
(brace
dot
id|init
op_assign
id|init_pit
comma
dot
id|opts
op_assign
op_amp
id|timer_pit
comma
)brace
suffix:semicolon
DECL|function|setup_pit_timer
r_void
id|setup_pit_timer
c_func
(paren
r_void
)paren
(brace
r_extern
id|spinlock_t
id|i8253_lock
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|i8253_lock
comma
id|flags
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x34
comma
id|PIT_MODE
)paren
suffix:semicolon
multiline_comment|/* binary, mode 2, LSB/MSB, ch 0 */
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|LATCH
op_amp
l_int|0xff
comma
id|PIT_CH0
)paren
suffix:semicolon
multiline_comment|/* LSB */
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|outb
c_func
(paren
id|LATCH
op_rshift
l_int|8
comma
id|PIT_CH0
)paren
suffix:semicolon
multiline_comment|/* MSB */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|i8253_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|timer_resume
r_static
r_int
id|timer_resume
c_func
(paren
r_struct
id|sys_device
op_star
id|dev
)paren
(brace
id|setup_pit_timer
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|timer_sysclass
r_static
r_struct
id|sysdev_class
id|timer_sysclass
op_assign
(brace
id|set_kset_name
c_func
(paren
l_string|&quot;timer_pit&quot;
)paren
comma
dot
id|resume
op_assign
id|timer_resume
comma
)brace
suffix:semicolon
DECL|variable|device_timer
r_static
r_struct
id|sys_device
id|device_timer
op_assign
(brace
dot
id|id
op_assign
l_int|0
comma
dot
id|cls
op_assign
op_amp
id|timer_sysclass
comma
)brace
suffix:semicolon
DECL|function|init_timer_sysfs
r_static
r_int
id|__init
id|init_timer_sysfs
c_func
(paren
r_void
)paren
(brace
r_int
id|error
op_assign
id|sysdev_class_register
c_func
(paren
op_amp
id|timer_sysclass
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|sysdev_register
c_func
(paren
op_amp
id|device_timer
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|variable|init_timer_sysfs
id|device_initcall
c_func
(paren
id|init_timer_sysfs
)paren
suffix:semicolon
eof
