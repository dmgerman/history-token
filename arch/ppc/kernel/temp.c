multiline_comment|/*&n; * temp.c&t;Thermal management for cpu&squot;s with Thermal Assist Units&n; *&n; * Written by Troy Benjegerdes &lt;hozer@drgw.net&gt;&n; *&n; * TODO:&n; * dynamic power management to limit peak CPU temp (using ICTC)&n; * calibration???&n; * &n; * Silly, crazy ideas: use cpu load (from scheduler) and ICTC to extend battery&n; * life in portables, and add a &squot;performance/watt&squot; metric somewhere in /proc&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/nvram.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/8xx_immap.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
DECL|struct|tau_temp
r_static
r_struct
id|tau_temp
(brace
DECL|member|interrupts
r_int
id|interrupts
suffix:semicolon
DECL|member|low
r_int
r_char
id|low
suffix:semicolon
DECL|member|high
r_int
r_char
id|high
suffix:semicolon
DECL|member|grew
r_int
r_char
id|grew
suffix:semicolon
DECL|variable|tau
)brace
id|tau
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|tau_timer
r_struct
id|timer_list
id|tau_timer
suffix:semicolon
DECL|macro|DEBUG
macro_line|#undef DEBUG
multiline_comment|/* TODO: put these in a /proc interface, with some sanity checks, and maybe&n; * dynamic adjustment to minimize # of interrupts */
multiline_comment|/* configurable values for step size and how much to expand the window when&n; * we get an interrupt. These are based on the limit that was out of range */
DECL|macro|step_size
mdefine_line|#define step_size&t;&t;2&t;/* step size when temp goes out of range */
DECL|macro|window_expand
mdefine_line|#define window_expand&t;&t;1&t;/* expand the window by this much */
multiline_comment|/* configurable values for shrinking the window */
DECL|macro|shrink_timer
mdefine_line|#define shrink_timer&t;2*HZ&t;/* period between shrinking the window */
DECL|macro|min_window
mdefine_line|#define min_window&t;2&t;/* minimum window size, degrees C */
DECL|function|set_thresholds
r_void
id|set_thresholds
c_func
(paren
r_int
r_int
id|cpu
)paren
(brace
macro_line|#ifdef CONFIG_TAU_INT
multiline_comment|/*&n;&t; * setup THRM1,&n;&t; * threshold, valid bit, enable interrupts, interrupt when below threshold&n;&t; */
id|mtspr
c_func
(paren
id|SPRN_THRM1
comma
id|THRM1_THRES
c_func
(paren
id|tau
(braket
id|cpu
)braket
dot
id|low
)paren
op_or
id|THRM1_V
op_or
id|THRM1_TIE
op_or
id|THRM1_TID
)paren
suffix:semicolon
multiline_comment|/* setup THRM2,&n;&t; * threshold, valid bit, enable interrupts, interrupt when above threshhold&n;&t; */
id|mtspr
(paren
id|SPRN_THRM2
comma
id|THRM1_THRES
c_func
(paren
id|tau
(braket
id|cpu
)braket
dot
id|high
)paren
op_or
id|THRM1_V
op_or
id|THRM1_TIE
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* same thing but don&squot;t enable interrupts */
id|mtspr
c_func
(paren
id|SPRN_THRM1
comma
id|THRM1_THRES
c_func
(paren
id|tau
(braket
id|cpu
)braket
dot
id|low
)paren
op_or
id|THRM1_V
op_or
id|THRM1_TID
)paren
suffix:semicolon
id|mtspr
c_func
(paren
id|SPRN_THRM2
comma
id|THRM1_THRES
c_func
(paren
id|tau
(braket
id|cpu
)braket
dot
id|high
)paren
op_or
id|THRM1_V
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|TAUupdate
r_void
id|TAUupdate
c_func
(paren
r_int
id|cpu
)paren
(brace
r_int
id|thrm
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;TAUupdate &quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* if both thresholds are crossed, the step_sizes cancel out&n;&t; * and the window winds up getting expanded twice. */
r_if
c_cond
(paren
(paren
id|thrm
op_assign
id|mfspr
c_func
(paren
id|SPRN_THRM1
)paren
)paren
op_amp
id|THRM1_TIV
)paren
(brace
multiline_comment|/* is valid? */
r_if
c_cond
(paren
id|thrm
op_amp
id|THRM1_TIN
)paren
(brace
multiline_comment|/* crossed low threshold */
r_if
c_cond
(paren
id|tau
(braket
id|cpu
)braket
dot
id|low
op_ge
id|step_size
)paren
(brace
id|tau
(braket
id|cpu
)braket
dot
id|low
op_sub_assign
id|step_size
suffix:semicolon
id|tau
(braket
id|cpu
)braket
dot
id|high
op_sub_assign
(paren
id|step_size
op_minus
id|window_expand
)paren
suffix:semicolon
)brace
id|tau
(braket
id|cpu
)braket
dot
id|grew
op_assign
l_int|1
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;low threshold crossed &quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
r_if
c_cond
(paren
(paren
id|thrm
op_assign
id|mfspr
c_func
(paren
id|SPRN_THRM2
)paren
)paren
op_amp
id|THRM1_TIV
)paren
(brace
multiline_comment|/* is valid? */
r_if
c_cond
(paren
id|thrm
op_amp
id|THRM1_TIN
)paren
(brace
multiline_comment|/* crossed high threshold */
r_if
c_cond
(paren
id|tau
(braket
id|cpu
)braket
dot
id|high
op_le
l_int|127
op_minus
id|step_size
)paren
(brace
id|tau
(braket
id|cpu
)braket
dot
id|low
op_add_assign
(paren
id|step_size
op_minus
id|window_expand
)paren
suffix:semicolon
id|tau
(braket
id|cpu
)braket
dot
id|high
op_add_assign
id|step_size
suffix:semicolon
)brace
id|tau
(braket
id|cpu
)braket
dot
id|grew
op_assign
l_int|1
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;high threshold crossed &quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;grew = %d&bslash;n&quot;
comma
id|tau
(braket
id|cpu
)braket
dot
id|grew
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef CONFIG_TAU_INT /* tau_timeout will do this if not using interrupts */
id|set_thresholds
c_func
(paren
id|cpu
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#ifdef CONFIG_TAU_INT
multiline_comment|/*&n; * TAU interrupts - called when we have a thermal assist unit interrupt&n; * with interrupts disabled&n; */
DECL|function|TAUException
r_void
id|TAUException
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
id|tau
(braket
id|cpu
)braket
dot
id|interrupts
op_increment
suffix:semicolon
id|TAUupdate
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_TAU_INT */
DECL|function|tau_timeout
r_static
r_void
id|tau_timeout
c_func
(paren
r_void
op_star
id|info
)paren
(brace
r_int
id|cpu
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|size
suffix:semicolon
r_int
id|shrink
suffix:semicolon
multiline_comment|/* disabling interrupts *should* be okay */
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_TAU_INT
id|TAUupdate
c_func
(paren
id|cpu
)paren
suffix:semicolon
macro_line|#endif
id|size
op_assign
id|tau
(braket
id|cpu
)braket
dot
id|high
op_minus
id|tau
(braket
id|cpu
)braket
dot
id|low
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|min_window
op_logical_and
op_logical_neg
id|tau
(braket
id|cpu
)braket
dot
id|grew
)paren
(brace
multiline_comment|/* do an exponential shrink of half the amount currently over size */
id|shrink
op_assign
(paren
l_int|2
op_plus
id|size
op_minus
id|min_window
)paren
op_div
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|shrink
)paren
(brace
id|tau
(braket
id|cpu
)braket
dot
id|low
op_add_assign
id|shrink
suffix:semicolon
id|tau
(braket
id|cpu
)braket
dot
id|high
op_sub_assign
id|shrink
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* size must have been min_window + 1 */
id|tau
(braket
id|cpu
)braket
dot
id|low
op_add_assign
l_int|1
suffix:semicolon
macro_line|#if 1 /* debug */
r_if
c_cond
(paren
(paren
id|tau
(braket
id|cpu
)braket
dot
id|high
op_minus
id|tau
(braket
id|cpu
)braket
dot
id|low
)paren
op_ne
id|min_window
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;temp.c: line %d, logic error&bslash;n&quot;
comma
id|__LINE__
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
)brace
id|tau
(braket
id|cpu
)braket
dot
id|grew
op_assign
l_int|0
suffix:semicolon
id|set_thresholds
c_func
(paren
id|cpu
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Do the enable every time, since otherwise a bunch of (relatively)&n;&t; * complex sleep code needs to be added. One mtspr every time&n;&t; * tau_timeout is called is probably not a big deal.&n;&t; * &n;&t; * Enable thermal sensor and set up sample interval timer&n;&t; * need 20 us to do the compare.. until a nice &squot;cpu_speed&squot; function&n;&t; * call is implemented, just assume a 500 mhz clock. It doesn&squot;t really&n;&t; * matter if we take too long for a compare since it&squot;s all interrupt &n;&t; * driven anyway. &n;&t; *&n;&t; * use a extra long time.. (60 us @ 500 mhz)&n;&t; */
id|mtspr
c_func
(paren
id|SPRN_THRM3
comma
id|THRM3_SITV
c_func
(paren
l_int|500
op_star
l_int|60
)paren
op_or
id|THRM3_E
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|tau_timeout_smp
r_static
r_void
id|tau_timeout_smp
c_func
(paren
r_int
r_int
id|unused
)paren
(brace
multiline_comment|/* schedule ourselves to be run again */
id|mod_timer
c_func
(paren
op_amp
id|tau_timer
comma
id|jiffies
op_plus
id|shrink_timer
)paren
suffix:semicolon
id|on_each_cpu
c_func
(paren
id|tau_timeout
comma
l_int|NULL
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * setup the TAU&n; * &n; * Set things up to use THRM1 as a temperature lower bound, and THRM2 as an upper bound.&n; * Start off at zero&n; */
DECL|variable|tau_initialized
r_int
id|tau_initialized
op_assign
l_int|0
suffix:semicolon
DECL|function|TAU_init_smp
r_void
id|__init
id|TAU_init_smp
c_func
(paren
r_void
op_star
id|info
)paren
(brace
r_int
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* set these to a reasonable value and let the timer shrink the&n;&t; * window */
id|tau
(braket
id|cpu
)braket
dot
id|low
op_assign
l_int|5
suffix:semicolon
id|tau
(braket
id|cpu
)braket
dot
id|high
op_assign
l_int|120
suffix:semicolon
id|set_thresholds
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
DECL|function|TAU_init
r_int
id|__init
id|TAU_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* We assume in SMP that if one CPU has TAU support, they&n;&t; * all have it --BenH&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|cur_cpu_spec
(braket
l_int|0
)braket
op_member_access_from_pointer
id|cpu_features
op_amp
id|CPU_FTR_TAU
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Thermal assist unit not available&bslash;n&quot;
)paren
suffix:semicolon
id|tau_initialized
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* first, set up the window shrinking timer */
id|init_timer
c_func
(paren
op_amp
id|tau_timer
)paren
suffix:semicolon
id|tau_timer.function
op_assign
id|tau_timeout_smp
suffix:semicolon
id|tau_timer.expires
op_assign
id|jiffies
op_plus
id|shrink_timer
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|tau_timer
)paren
suffix:semicolon
id|on_each_cpu
c_func
(paren
id|TAU_init_smp
comma
l_int|NULL
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Thermal assist unit &quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_TAU_INT
id|printk
c_func
(paren
l_string|&quot;using interrupts, &quot;
)paren
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
l_string|&quot;using timers, &quot;
)paren
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;shrink_timer: %d jiffies&bslash;n&quot;
comma
id|shrink_timer
)paren
suffix:semicolon
id|tau_initialized
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|TAU_init
id|__initcall
c_func
(paren
id|TAU_init
)paren
suffix:semicolon
multiline_comment|/*&n; * return current temp&n; */
DECL|function|cpu_temp_both
id|u32
id|cpu_temp_both
c_func
(paren
r_int
r_int
id|cpu
)paren
(brace
r_return
(paren
(paren
id|tau
(braket
id|cpu
)braket
dot
id|high
op_lshift
l_int|16
)paren
op_or
id|tau
(braket
id|cpu
)braket
dot
id|low
)paren
suffix:semicolon
)brace
DECL|function|cpu_temp
r_int
id|cpu_temp
c_func
(paren
r_int
r_int
id|cpu
)paren
(brace
r_return
(paren
(paren
id|tau
(braket
id|cpu
)braket
dot
id|high
op_plus
id|tau
(braket
id|cpu
)braket
dot
id|low
)paren
op_div
l_int|2
)paren
suffix:semicolon
)brace
DECL|function|tau_interrupts
r_int
id|tau_interrupts
c_func
(paren
r_int
r_int
id|cpu
)paren
(brace
r_return
(paren
id|tau
(braket
id|cpu
)braket
dot
id|interrupts
)paren
suffix:semicolon
)brace
eof
