multiline_comment|/*&n; *&t;Pentium 4/Xeon CPU on demand clock modulation/speed scaling&n; *&t;(C) 2002 - 2003 Dominik Brodowski &lt;linux@brodo.de&gt;&n; *&t;(C) 2002 Zwane Mwaikambo &lt;zwane@commfireservices.com&gt;&n; *&t;(C) 2002 Arjan van de Ven &lt;arjanv@redhat.com&gt;&n; *&t;(C) 2002 Tora T. Engstad&n; *&t;All Rights Reserved&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; *&n; *      The author(s) of this software shall not be held liable for damages&n; *      of any nature resulting due to the use of this software. This&n; *      software is provided AS-IS with no warranties.&n; *&t;&n; *&t;Date&t;&t;Errata&t;&t;&t;Description&n; *&t;20020525&t;N44, O17&t;12.5% or 25% DC causes lockup&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt; 
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/cpumask.h&gt;
macro_line|#include &lt;asm/processor.h&gt; 
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/timex.h&gt;
macro_line|#include &quot;speedstep-lib.h&quot;
DECL|macro|PFX
mdefine_line|#define PFX&t;&quot;p4-clockmod: &quot;
DECL|macro|dprintk
mdefine_line|#define dprintk(msg...) cpufreq_debug_printk(CPUFREQ_DEBUG_DRIVER, &quot;p4-clockmod&quot;, msg)
multiline_comment|/*&n; * Duty Cycle (3bits), note DC_DISABLE is not specified in&n; * intel docs i just use it to mean disable&n; */
r_enum
(brace
DECL|enumerator|DC_RESV
DECL|enumerator|DC_DFLT
DECL|enumerator|DC_25PT
DECL|enumerator|DC_38PT
DECL|enumerator|DC_50PT
id|DC_RESV
comma
id|DC_DFLT
comma
id|DC_25PT
comma
id|DC_38PT
comma
id|DC_50PT
comma
DECL|enumerator|DC_64PT
DECL|enumerator|DC_75PT
DECL|enumerator|DC_88PT
DECL|enumerator|DC_DISABLE
id|DC_64PT
comma
id|DC_75PT
comma
id|DC_88PT
comma
id|DC_DISABLE
)brace
suffix:semicolon
DECL|macro|DC_ENTRIES
mdefine_line|#define DC_ENTRIES&t;8
DECL|variable|has_N44_O17_errata
r_static
r_int
id|has_N44_O17_errata
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|stock_freq
r_static
r_int
r_int
id|stock_freq
suffix:semicolon
DECL|variable|p4clockmod_driver
r_static
r_struct
id|cpufreq_driver
id|p4clockmod_driver
suffix:semicolon
r_static
r_int
r_int
id|cpufreq_p4_get
c_func
(paren
r_int
r_int
id|cpu
)paren
suffix:semicolon
DECL|function|cpufreq_p4_setdc
r_static
r_int
id|cpufreq_p4_setdc
c_func
(paren
r_int
r_int
id|cpu
comma
r_int
r_int
id|newstate
)paren
(brace
id|u32
id|l
comma
id|h
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu_online
c_func
(paren
id|cpu
)paren
op_logical_or
(paren
id|newstate
OG
id|DC_DISABLE
)paren
op_logical_or
(paren
id|newstate
op_eq
id|DC_RESV
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_THERM_STATUS
comma
id|l
comma
id|h
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l
op_amp
l_int|0x01
)paren
id|dprintk
c_func
(paren
l_string|&quot;CPU#%d currently thermal throttled&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|has_N44_O17_errata
(braket
id|cpu
)braket
op_logical_and
(paren
id|newstate
op_eq
id|DC_25PT
op_logical_or
id|newstate
op_eq
id|DC_DFLT
)paren
)paren
id|newstate
op_assign
id|DC_38PT
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_THERM_CONTROL
comma
id|l
comma
id|h
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newstate
op_eq
id|DC_DISABLE
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;CPU#%d disabling modulation&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_IA32_THERM_CONTROL
comma
id|l
op_amp
op_complement
(paren
l_int|1
op_lshift
l_int|4
)paren
comma
id|h
)paren
suffix:semicolon
)brace
r_else
(brace
id|dprintk
c_func
(paren
l_string|&quot;CPU#%d setting duty cycle to %d%%&bslash;n&quot;
comma
id|cpu
comma
(paren
(paren
l_int|125
op_star
id|newstate
)paren
op_div
l_int|10
)paren
)paren
suffix:semicolon
multiline_comment|/* bits 63 - 5&t;: reserved &n;&t;&t; * bit  4&t;: enable/disable&n;&t;&t; * bits 3-1&t;: duty cycle&n;&t;&t; * bit  0&t;: reserved&n;&t;&t; */
id|l
op_assign
(paren
id|l
op_amp
op_complement
l_int|14
)paren
suffix:semicolon
id|l
op_assign
id|l
op_or
(paren
l_int|1
op_lshift
l_int|4
)paren
op_or
(paren
(paren
id|newstate
op_amp
l_int|0x7
)paren
op_lshift
l_int|1
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_IA32_THERM_CONTROL
comma
id|l
comma
id|h
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|p4clockmod_table
r_static
r_struct
id|cpufreq_frequency_table
id|p4clockmod_table
(braket
)braket
op_assign
(brace
(brace
id|DC_RESV
comma
id|CPUFREQ_ENTRY_INVALID
)brace
comma
(brace
id|DC_DFLT
comma
l_int|0
)brace
comma
(brace
id|DC_25PT
comma
l_int|0
)brace
comma
(brace
id|DC_38PT
comma
l_int|0
)brace
comma
(brace
id|DC_50PT
comma
l_int|0
)brace
comma
(brace
id|DC_64PT
comma
l_int|0
)brace
comma
(brace
id|DC_75PT
comma
l_int|0
)brace
comma
(brace
id|DC_88PT
comma
l_int|0
)brace
comma
(brace
id|DC_DISABLE
comma
l_int|0
)brace
comma
(brace
id|DC_RESV
comma
id|CPUFREQ_TABLE_END
)brace
comma
)brace
suffix:semicolon
DECL|function|cpufreq_p4_target
r_static
r_int
id|cpufreq_p4_target
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
comma
r_int
r_int
id|target_freq
comma
r_int
r_int
id|relation
)paren
(brace
r_int
r_int
id|newstate
op_assign
id|DC_RESV
suffix:semicolon
r_struct
id|cpufreq_freqs
id|freqs
suffix:semicolon
id|cpumask_t
id|cpus_allowed
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|cpufreq_frequency_table_target
c_func
(paren
id|policy
comma
op_amp
id|p4clockmod_table
(braket
l_int|0
)braket
comma
id|target_freq
comma
id|relation
comma
op_amp
id|newstate
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|freqs.old
op_assign
id|cpufreq_p4_get
c_func
(paren
id|policy-&gt;cpu
)paren
suffix:semicolon
id|freqs
dot
r_new
op_assign
id|stock_freq
op_star
id|p4clockmod_table
(braket
id|newstate
)braket
dot
id|index
op_div
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|freqs
dot
r_new
op_eq
id|freqs.old
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* notifiers */
id|for_each_cpu_mask
c_func
(paren
id|i
comma
id|policy-&gt;cpus
)paren
(brace
id|freqs.cpu
op_assign
id|i
suffix:semicolon
id|cpufreq_notify_transition
c_func
(paren
op_amp
id|freqs
comma
id|CPUFREQ_PRECHANGE
)paren
suffix:semicolon
)brace
multiline_comment|/* run on each logical CPU, see section 13.15.3 of IA32 Intel Architecture Software&n;&t; * Developer&squot;s Manual, Volume 3 &n;&t; */
id|cpus_allowed
op_assign
id|current-&gt;cpus_allowed
suffix:semicolon
id|for_each_cpu_mask
c_func
(paren
id|i
comma
id|policy-&gt;cpus
)paren
(brace
id|cpumask_t
id|this_cpu
op_assign
id|cpumask_of_cpu
c_func
(paren
id|i
)paren
suffix:semicolon
id|set_cpus_allowed
c_func
(paren
id|current
comma
id|this_cpu
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
op_ne
id|i
)paren
suffix:semicolon
id|cpufreq_p4_setdc
c_func
(paren
id|i
comma
id|p4clockmod_table
(braket
id|newstate
)braket
dot
id|index
)paren
suffix:semicolon
)brace
id|set_cpus_allowed
c_func
(paren
id|current
comma
id|cpus_allowed
)paren
suffix:semicolon
multiline_comment|/* notifiers */
id|for_each_cpu_mask
c_func
(paren
id|i
comma
id|policy-&gt;cpus
)paren
(brace
id|freqs.cpu
op_assign
id|i
suffix:semicolon
id|cpufreq_notify_transition
c_func
(paren
op_amp
id|freqs
comma
id|CPUFREQ_POSTCHANGE
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cpufreq_p4_verify
r_static
r_int
id|cpufreq_p4_verify
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_return
id|cpufreq_frequency_table_verify
c_func
(paren
id|policy
comma
op_amp
id|p4clockmod_table
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
DECL|function|cpufreq_p4_get_frequency
r_static
r_int
r_int
id|cpufreq_p4_get_frequency
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
r_if
c_cond
(paren
(paren
id|c-&gt;x86
op_eq
l_int|0x06
)paren
op_logical_and
(paren
id|c-&gt;x86_model
op_eq
l_int|0x09
)paren
)paren
(brace
multiline_comment|/* Pentium M (Banias) */
id|printk
c_func
(paren
id|KERN_WARNING
id|PFX
l_string|&quot;Warning: Pentium M detected. &quot;
l_string|&quot;The speedstep_centrino module offers voltage scaling&quot;
l_string|&quot; in addition of frequency scaling. You should use &quot;
l_string|&quot;that instead of p4-clockmod, if possible.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|speedstep_get_processor_frequency
c_func
(paren
id|SPEEDSTEP_PROCESSOR_PM
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|c-&gt;x86
op_eq
l_int|0x06
)paren
op_logical_and
(paren
id|c-&gt;x86_model
op_eq
l_int|0x0D
)paren
)paren
(brace
multiline_comment|/* Pentium M (Dothan) */
id|printk
c_func
(paren
id|KERN_WARNING
id|PFX
l_string|&quot;Warning: Pentium M detected. &quot;
l_string|&quot;The speedstep_centrino module offers voltage scaling&quot;
l_string|&quot; in addition of frequency scaling. You should use &quot;
l_string|&quot;that instead of p4-clockmod, if possible.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* on P-4s, the TSC runs with constant frequency independent whether&n;&t;&t; * throttling is active or not. */
id|p4clockmod_driver.flags
op_or_assign
id|CPUFREQ_CONST_LOOPS
suffix:semicolon
r_return
id|speedstep_get_processor_frequency
c_func
(paren
id|SPEEDSTEP_PROCESSOR_PM
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c-&gt;x86
op_ne
l_int|0xF
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PFX
l_string|&quot;Unknown p4-clockmod-capable CPU. Please send an e-mail to &lt;linux@brodo.de&gt;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* on P-4s, the TSC runs with constant frequency independent whether&n;&t; * throttling is active or not. */
id|p4clockmod_driver.flags
op_or_assign
id|CPUFREQ_CONST_LOOPS
suffix:semicolon
r_if
c_cond
(paren
id|speedstep_detect_processor
c_func
(paren
)paren
op_eq
id|SPEEDSTEP_PROCESSOR_P4M
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PFX
l_string|&quot;Warning: Pentium 4-M detected. &quot;
l_string|&quot;The speedstep-ich or acpi cpufreq modules offer &quot;
l_string|&quot;voltage scaling in addition of frequency scaling. &quot;
l_string|&quot;You should use either one instead of p4-clockmod, &quot;
l_string|&quot;if possible.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|speedstep_get_processor_frequency
c_func
(paren
id|SPEEDSTEP_PROCESSOR_P4M
)paren
suffix:semicolon
)brace
r_return
id|speedstep_get_processor_frequency
c_func
(paren
id|SPEEDSTEP_PROCESSOR_P4D
)paren
suffix:semicolon
)brace
DECL|function|cpufreq_p4_cpu_init
r_static
r_int
id|cpufreq_p4_cpu_init
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_struct
id|cpuinfo_x86
op_star
id|c
op_assign
op_amp
id|cpu_data
(braket
id|policy-&gt;cpu
)braket
suffix:semicolon
r_int
id|cpuid
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|policy-&gt;cpus
op_assign
id|cpu_sibling_map
(braket
id|policy-&gt;cpu
)braket
suffix:semicolon
macro_line|#endif
multiline_comment|/* Errata workaround */
id|cpuid
op_assign
(paren
id|c-&gt;x86
op_lshift
l_int|8
)paren
op_or
(paren
id|c-&gt;x86_model
op_lshift
l_int|4
)paren
op_or
id|c-&gt;x86_mask
suffix:semicolon
r_switch
c_cond
(paren
id|cpuid
)paren
(brace
r_case
l_int|0x0f07
suffix:colon
r_case
l_int|0x0f0a
suffix:colon
r_case
l_int|0x0f11
suffix:colon
r_case
l_int|0x0f12
suffix:colon
id|has_N44_O17_errata
(braket
id|policy-&gt;cpu
)braket
op_assign
l_int|1
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;has errata -- disabling low frequencies&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* get max frequency */
id|stock_freq
op_assign
id|cpufreq_p4_get_frequency
c_func
(paren
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stock_freq
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* table init */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
(paren
id|p4clockmod_table
(braket
id|i
)braket
dot
id|frequency
op_ne
id|CPUFREQ_TABLE_END
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|i
OL
l_int|2
)paren
op_logical_and
(paren
id|has_N44_O17_errata
(braket
id|policy-&gt;cpu
)braket
)paren
)paren
id|p4clockmod_table
(braket
id|i
)braket
dot
id|frequency
op_assign
id|CPUFREQ_ENTRY_INVALID
suffix:semicolon
r_else
id|p4clockmod_table
(braket
id|i
)braket
dot
id|frequency
op_assign
(paren
id|stock_freq
op_star
id|i
)paren
op_div
l_int|8
suffix:semicolon
)brace
id|cpufreq_frequency_table_get_attr
c_func
(paren
id|p4clockmod_table
comma
id|policy-&gt;cpu
)paren
suffix:semicolon
multiline_comment|/* cpuinfo and default policy values */
id|policy-&gt;governor
op_assign
id|CPUFREQ_DEFAULT_GOVERNOR
suffix:semicolon
id|policy-&gt;cpuinfo.transition_latency
op_assign
l_int|1000000
suffix:semicolon
multiline_comment|/* assumed */
id|policy-&gt;cur
op_assign
id|stock_freq
suffix:semicolon
r_return
id|cpufreq_frequency_table_cpuinfo
c_func
(paren
id|policy
comma
op_amp
id|p4clockmod_table
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
DECL|function|cpufreq_p4_cpu_exit
r_static
r_int
id|cpufreq_p4_cpu_exit
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
id|cpufreq_frequency_table_put_attr
c_func
(paren
id|policy-&gt;cpu
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cpufreq_p4_get
r_static
r_int
r_int
id|cpufreq_p4_get
c_func
(paren
r_int
r_int
id|cpu
)paren
(brace
id|cpumask_t
id|cpus_allowed
suffix:semicolon
id|u32
id|l
comma
id|h
suffix:semicolon
id|cpus_allowed
op_assign
id|current-&gt;cpus_allowed
suffix:semicolon
id|set_cpus_allowed
c_func
(paren
id|current
comma
id|cpumask_of_cpu
c_func
(paren
id|cpu
)paren
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
op_ne
id|cpu
)paren
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_THERM_CONTROL
comma
id|l
comma
id|h
)paren
suffix:semicolon
id|set_cpus_allowed
c_func
(paren
id|current
comma
id|cpus_allowed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l
op_amp
l_int|0x10
)paren
(brace
id|l
op_assign
id|l
op_rshift
l_int|1
suffix:semicolon
id|l
op_and_assign
l_int|0x7
suffix:semicolon
)brace
r_else
id|l
op_assign
id|DC_DISABLE
suffix:semicolon
r_if
c_cond
(paren
id|l
op_ne
id|DC_DISABLE
)paren
r_return
(paren
id|stock_freq
op_star
id|l
op_div
l_int|8
)paren
suffix:semicolon
r_return
id|stock_freq
suffix:semicolon
)brace
DECL|variable|p4clockmod_attr
r_static
r_struct
id|freq_attr
op_star
id|p4clockmod_attr
(braket
)braket
op_assign
(brace
op_amp
id|cpufreq_freq_attr_scaling_available_freqs
comma
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|p4clockmod_driver
r_static
r_struct
id|cpufreq_driver
id|p4clockmod_driver
op_assign
(brace
dot
id|verify
op_assign
id|cpufreq_p4_verify
comma
dot
id|target
op_assign
id|cpufreq_p4_target
comma
dot
id|init
op_assign
id|cpufreq_p4_cpu_init
comma
dot
m_exit
op_assign
id|cpufreq_p4_cpu_exit
comma
dot
id|get
op_assign
id|cpufreq_p4_get
comma
dot
id|name
op_assign
l_string|&quot;p4-clockmod&quot;
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|attr
op_assign
id|p4clockmod_attr
comma
)brace
suffix:semicolon
DECL|function|cpufreq_p4_init
r_static
r_int
id|__init
id|cpufreq_p4_init
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
id|cpu_data
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/*&n;&t; * THERM_CONTROL is architectural for IA32 now, so &n;&t; * we can rely on the capability checks&n;&t; */
r_if
c_cond
(paren
id|c-&gt;x86_vendor
op_ne
id|X86_VENDOR_INTEL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|X86_FEATURE_ACPI
comma
id|c-&gt;x86_capability
)paren
op_logical_or
op_logical_neg
id|test_bit
c_func
(paren
id|X86_FEATURE_ACC
comma
id|c-&gt;x86_capability
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|ret
op_assign
id|cpufreq_register_driver
c_func
(paren
op_amp
id|p4clockmod_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|printk
c_func
(paren
id|KERN_INFO
id|PFX
l_string|&quot;P4/Xeon(TM) CPU On-Demand Clock Modulation available&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
id|ret
)paren
suffix:semicolon
)brace
DECL|function|cpufreq_p4_exit
r_static
r_void
id|__exit
id|cpufreq_p4_exit
c_func
(paren
r_void
)paren
(brace
id|cpufreq_unregister_driver
c_func
(paren
op_amp
id|p4clockmod_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
(paren
l_string|&quot;Zwane Mwaikambo &lt;zwane@commfireservices.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
(paren
l_string|&quot;cpufreq driver for Pentium(TM) 4/Xeon(TM)&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|cpufreq_p4_init
id|late_initcall
c_func
(paren
id|cpufreq_p4_init
)paren
suffix:semicolon
DECL|variable|cpufreq_p4_exit
id|module_exit
c_func
(paren
id|cpufreq_p4_exit
)paren
suffix:semicolon
eof
