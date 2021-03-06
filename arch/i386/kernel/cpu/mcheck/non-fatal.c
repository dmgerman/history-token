multiline_comment|/*&n; * Non Fatal Machine Check Exception Reporting&n; *&n; * (C) Copyright 2002 Dave Jones. &lt;davej@codemonkey.org.uk&gt;&n; *&n; * This file contains routines to check for non-fatal MCEs every 15s&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/processor.h&gt; 
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &quot;mce.h&quot;
DECL|variable|firstbank
r_static
r_int
id|firstbank
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
r_for
c_loop
(paren
id|i
op_assign
id|firstbank
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
c_func
(paren
id|KERN_INFO
l_string|&quot;MCE: The hardware reports a non &quot;
l_string|&quot;fatal, correctable incident occurred on &quot;
l_string|&quot;CPU %d.&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|printk
(paren
id|KERN_INFO
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
id|add_taint
c_func
(paren
id|TAINT_MACHINE_CHECK
)paren
suffix:semicolon
)brace
)brace
)brace
r_static
r_void
id|mce_work_fn
c_func
(paren
r_void
op_star
id|data
)paren
suffix:semicolon
r_static
id|DECLARE_WORK
c_func
(paren
id|mce_work
comma
id|mce_work_fn
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|mce_work_fn
r_static
r_void
id|mce_work_fn
c_func
(paren
r_void
op_star
id|data
)paren
(brace
id|on_each_cpu
c_func
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
id|schedule_delayed_work
c_func
(paren
op_amp
id|mce_work
comma
id|MCE_RATE
)paren
suffix:semicolon
)brace
DECL|function|init_nonfatal_mce_checker
r_static
r_int
id|__init
id|init_nonfatal_mce_checker
c_func
(paren
r_void
)paren
(brace
r_struct
id|cpuinfo_x86
op_star
id|c
op_assign
op_amp
id|boot_cpu_data
suffix:semicolon
multiline_comment|/* Check for MCE support */
r_if
c_cond
(paren
op_logical_neg
id|cpu_has
c_func
(paren
id|c
comma
id|X86_FEATURE_MCE
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* Check for PPro style MCA */
r_if
c_cond
(paren
op_logical_neg
id|cpu_has
c_func
(paren
id|c
comma
id|X86_FEATURE_MCA
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* Some Athlons misbehave when we frob bank 0 */
r_if
c_cond
(paren
id|boot_cpu_data.x86_vendor
op_eq
id|X86_VENDOR_AMD
op_logical_and
id|boot_cpu_data.x86
op_eq
l_int|6
)paren
id|firstbank
op_assign
l_int|1
suffix:semicolon
r_else
id|firstbank
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Check for non-fatal errors every MCE_RATE s&n;&t; */
id|schedule_delayed_work
c_func
(paren
op_amp
id|mce_work
comma
id|MCE_RATE
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Machine check exception polling timer started.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|init_nonfatal_mce_checker
id|module_init
c_func
(paren
id|init_nonfatal_mce_checker
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
