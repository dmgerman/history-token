multiline_comment|/*&n; * P4 specific Machine Check Exception Reporting&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/processor.h&gt; 
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &quot;mce.h&quot;
DECL|variable|mce_timer
r_static
r_struct
id|timer_list
id|mce_timer
suffix:semicolon
DECL|variable|timerset
r_static
r_int
id|timerset
suffix:semicolon
DECL|macro|MCE_RATE
mdefine_line|#define MCE_RATE&t;15*HZ&t;/* timer rate is 15s */
DECL|function|mce_checkregs
r_static
r_void
id|mce_checkregs
(paren
r_void
op_star
id|info
)paren
(brace
id|u32
id|low
comma
id|high
suffix:semicolon
r_int
id|i
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
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
id|nr_mce_banks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rdmsr
(paren
id|MSR_IA32_MC0_STATUS
op_plus
id|i
op_star
l_int|4
comma
id|low
comma
id|high
)paren
suffix:semicolon
r_if
c_cond
(paren
id|high
op_amp
(paren
l_int|1
op_lshift
l_int|31
)paren
)paren
(brace
id|printk
(paren
id|KERN_EMERG
l_string|&quot;MCE: The hardware reports a non fatal, correctable incident occured on CPU %d.&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|printk
(paren
id|KERN_EMERG
l_string|&quot;Bank %d: %08x%08x&bslash;n&quot;
comma
id|i
comma
id|high
comma
id|low
)paren
suffix:semicolon
multiline_comment|/* Scrub the error so we don&squot;t pick it up in MCE_RATE seconds time. */
id|wrmsr
(paren
id|MSR_IA32_MC0_STATUS
op_plus
id|i
op_star
l_int|4
comma
l_int|0UL
comma
l_int|0UL
)paren
suffix:semicolon
multiline_comment|/* Serialize */
id|wmb
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|do_mce_timer
r_static
r_void
id|do_mce_timer
c_func
(paren
r_void
op_star
id|data
)paren
(brace
id|smp_call_function
(paren
id|mce_checkregs
comma
l_int|NULL
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
)brace
r_static
id|DECLARE_WORK
c_func
(paren
id|mce_work
comma
id|do_mce_timer
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|mce_timerfunc
r_static
r_void
id|mce_timerfunc
(paren
r_int
r_int
id|data
)paren
(brace
id|mce_checkregs
(paren
l_int|NULL
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
id|num_online_cpus
c_func
(paren
)paren
OG
l_int|1
)paren
id|schedule_work
(paren
op_amp
id|mce_work
)paren
suffix:semicolon
macro_line|#endif
id|mce_timer.expires
op_assign
id|jiffies
op_plus
id|MCE_RATE
suffix:semicolon
id|add_timer
(paren
op_amp
id|mce_timer
)paren
suffix:semicolon
)brace
DECL|function|init_nonfatal_mce_checker
r_void
id|init_nonfatal_mce_checker
c_func
(paren
)paren
(brace
r_if
c_cond
(paren
id|timerset
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Set the timer to check for non-fatal&n;&t;&t;   errors every MCE_RATE seconds */
id|init_timer
(paren
op_amp
id|mce_timer
)paren
suffix:semicolon
id|mce_timer.expires
op_assign
id|jiffies
op_plus
id|MCE_RATE
suffix:semicolon
id|mce_timer.data
op_assign
l_int|0
suffix:semicolon
id|mce_timer.function
op_assign
op_amp
id|mce_timerfunc
suffix:semicolon
id|add_timer
(paren
op_amp
id|mce_timer
)paren
suffix:semicolon
id|timerset
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Machine check exception polling timer started.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
eof
