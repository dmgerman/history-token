multiline_comment|/*&n; *  linux/arch/arm/mach-integrator/cpu.c&n; *&n; *  Copyright (C) 2001-2002 Deep Blue Solutions Ltd.&n; *&n; *  $Id: cpu.c,v 1.6 2002/07/18 13:58:51 rmk Exp $&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * CPU support functions&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|variable|integrator_driver
r_static
r_struct
id|cpufreq_driver
id|integrator_driver
suffix:semicolon
DECL|macro|CM_ID
mdefine_line|#define CM_ID  &t;(IO_ADDRESS(INTEGRATOR_HDR_BASE)+INTEGRATOR_HDR_ID_OFFSET)
DECL|macro|CM_OSC
mdefine_line|#define CM_OSC&t;(IO_ADDRESS(INTEGRATOR_HDR_BASE)+INTEGRATOR_HDR_OSC_OFFSET)
DECL|macro|CM_STAT
mdefine_line|#define CM_STAT (IO_ADDRESS(INTEGRATOR_HDR_BASE)+INTEGRATOR_HDR_STAT_OFFSET)
DECL|macro|CM_LOCK
mdefine_line|#define CM_LOCK (IO_ADDRESS(INTEGRATOR_HDR_BASE)+INTEGRATOR_HDR_LOCK_OFFSET)
DECL|struct|vco
r_struct
id|vco
(brace
DECL|member|vdw
r_int
r_char
id|vdw
suffix:semicolon
DECL|member|od
r_int
r_char
id|od
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Divisors for each OD setting.&n; */
DECL|variable|cc_divisor
r_static
r_int
r_char
id|cc_divisor
(braket
l_int|8
)braket
op_assign
(brace
l_int|10
comma
l_int|2
comma
l_int|8
comma
l_int|4
comma
l_int|5
comma
l_int|7
comma
l_int|9
comma
l_int|6
)brace
suffix:semicolon
DECL|function|vco_to_freq
r_static
r_int
r_int
id|vco_to_freq
c_func
(paren
r_struct
id|vco
id|vco
comma
r_int
id|factor
)paren
(brace
r_return
l_int|2000
op_star
(paren
id|vco.vdw
op_plus
l_int|8
)paren
op_div
id|cc_divisor
(braket
id|vco.od
)braket
op_div
id|factor
suffix:semicolon
)brace
multiline_comment|/*&n; * Divisor indexes in ascending divisor order&n; */
DECL|variable|s2od
r_static
r_int
r_char
id|s2od
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|3
comma
l_int|4
comma
l_int|7
comma
l_int|5
comma
l_int|2
comma
l_int|6
comma
l_int|0
)brace
suffix:semicolon
DECL|function|freq_to_vco
r_static
r_struct
id|vco
id|freq_to_vco
c_func
(paren
r_int
r_int
id|freq_khz
comma
r_int
id|factor
)paren
(brace
r_struct
id|vco
id|vco
op_assign
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
r_int
id|i
comma
id|f
suffix:semicolon
id|freq_khz
op_mul_assign
id|factor
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|f
op_assign
id|freq_khz
op_star
id|cc_divisor
(braket
id|s2od
(braket
id|i
)braket
)braket
suffix:semicolon
multiline_comment|/* f must be between 10MHz and 320MHz */
r_if
c_cond
(paren
id|f
OG
l_int|10000
op_logical_and
id|f
op_le
l_int|320000
)paren
r_break
suffix:semicolon
)brace
id|vco.od
op_assign
id|s2od
(braket
id|i
)braket
suffix:semicolon
id|vco.vdw
op_assign
id|f
op_div
l_int|2000
op_minus
l_int|8
suffix:semicolon
r_return
id|vco
suffix:semicolon
)brace
multiline_comment|/*&n; * Validate the speed policy.&n; */
DECL|function|integrator_verify_policy
r_static
r_int
id|integrator_verify_policy
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_struct
id|vco
id|vco
suffix:semicolon
id|cpufreq_verify_within_limits
c_func
(paren
id|policy
comma
id|policy-&gt;cpuinfo.min_freq
comma
id|policy-&gt;cpuinfo.max_freq
)paren
suffix:semicolon
id|vco
op_assign
id|freq_to_vco
c_func
(paren
id|policy-&gt;max
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vco.vdw
OL
l_int|4
)paren
id|vco.vdw
op_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|vco.vdw
OG
l_int|152
)paren
id|vco.vdw
op_assign
l_int|152
suffix:semicolon
id|policy-&gt;max
op_assign
id|vco_to_freq
c_func
(paren
id|vco
comma
l_int|1
)paren
suffix:semicolon
id|vco
op_assign
id|freq_to_vco
c_func
(paren
id|policy-&gt;min
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vco.vdw
OL
l_int|4
)paren
id|vco.vdw
op_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|vco.vdw
OG
l_int|152
)paren
id|vco.vdw
op_assign
l_int|152
suffix:semicolon
id|policy-&gt;min
op_assign
id|vco_to_freq
c_func
(paren
id|vco
comma
l_int|1
)paren
suffix:semicolon
id|cpufreq_verify_within_limits
c_func
(paren
id|policy
comma
id|policy-&gt;cpuinfo.min_freq
comma
id|policy-&gt;cpuinfo.max_freq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|integrator_set_target
r_static
r_int
id|integrator_set_target
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
id|cpus_allowed
suffix:semicolon
r_int
id|cpu
op_assign
id|policy-&gt;cpu
suffix:semicolon
r_struct
id|vco
id|vco
suffix:semicolon
r_struct
id|cpufreq_freqs
id|freqs
suffix:semicolon
id|u_int
id|cm_osc
suffix:semicolon
multiline_comment|/*&n;&t; * Save this threads cpus_allowed mask.&n;&t; */
id|cpus_allowed
op_assign
id|current-&gt;cpus_allowed
suffix:semicolon
multiline_comment|/*&n;&t; * Bind to the specified CPU.  When this call returns,&n;&t; * we should be running on the right CPU.&n;&t; */
id|set_cpus_allowed
c_func
(paren
id|current
comma
l_int|1
op_lshift
id|cpu
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|cpu
op_ne
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/* get current setting */
id|cm_osc
op_assign
id|__raw_readl
c_func
(paren
id|CM_OSC
)paren
suffix:semicolon
id|vco.od
op_assign
(paren
id|cm_osc
op_rshift
l_int|8
)paren
op_amp
l_int|7
suffix:semicolon
id|vco.vdw
op_assign
id|cm_osc
op_amp
l_int|255
suffix:semicolon
id|freqs.old
op_assign
id|vco_to_freq
c_func
(paren
id|vco
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* freq_to_vco rounds down -- so we need the next larger freq in&n;&t; * case of CPUFREQ_RELATION_L.&n;&t; */
r_if
c_cond
(paren
id|relation
op_eq
id|CPUFREQ_RELATION_L
)paren
id|target_freq
op_add_assign
l_int|1999
suffix:semicolon
r_if
c_cond
(paren
id|target_freq
OG
id|policy-&gt;max
)paren
id|target_freq
op_assign
id|policy-&gt;max
suffix:semicolon
id|vco
op_assign
id|freq_to_vco
c_func
(paren
id|target_freq
comma
l_int|1
)paren
suffix:semicolon
id|freqs
dot
r_new
op_assign
id|vco_to_freq
c_func
(paren
id|vco
comma
l_int|1
)paren
suffix:semicolon
id|freqs.cpu
op_assign
id|policy-&gt;cpu
suffix:semicolon
r_if
c_cond
(paren
id|freqs.old
op_eq
id|freqs
dot
r_new
)paren
(brace
id|set_cpus_allowed
c_func
(paren
id|current
comma
id|cpus_allowed
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|cpufreq_notify_transition
c_func
(paren
op_amp
id|freqs
comma
id|CPUFREQ_PRECHANGE
)paren
suffix:semicolon
id|cm_osc
op_assign
id|__raw_readl
c_func
(paren
id|CM_OSC
)paren
suffix:semicolon
id|cm_osc
op_and_assign
l_int|0xfffff800
suffix:semicolon
id|cm_osc
op_or_assign
id|vco.vdw
op_or
id|vco.od
op_lshift
l_int|8
suffix:semicolon
id|__raw_writel
c_func
(paren
l_int|0xa05f
comma
id|CM_LOCK
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
id|cm_osc
comma
id|CM_OSC
)paren
suffix:semicolon
id|__raw_writel
c_func
(paren
l_int|0
comma
id|CM_LOCK
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Restore the CPUs allowed mask.&n;&t; */
id|set_cpus_allowed
c_func
(paren
id|current
comma
id|cpus_allowed
)paren
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|integrator_cpufreq_init
r_static
r_int
id|integrator_cpufreq_init
c_func
(paren
r_struct
id|cpufreq
op_star
id|policy
)paren
(brace
r_int
r_int
id|cus_allowed
suffix:semicolon
r_int
r_int
id|cpu
op_assign
id|policy-&gt;cpu
suffix:semicolon
id|u_int
id|cm_osc
comma
id|cm_stat
comma
id|mem_freq_khz
suffix:semicolon
r_struct
id|vco
id|vco
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
l_int|1
op_lshift
id|cpu
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|cpu
op_ne
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/* detect memory etc. */
id|cm_stat
op_assign
id|__raw_readl
c_func
(paren
id|CM_STAT
)paren
suffix:semicolon
id|cm_osc
op_assign
id|__raw_readl
c_func
(paren
id|CM_OSC
)paren
suffix:semicolon
id|vco.od
op_assign
(paren
id|cm_osc
op_rshift
l_int|20
)paren
op_amp
l_int|7
suffix:semicolon
id|vco.vdw
op_assign
(paren
id|cm_osc
op_rshift
l_int|12
)paren
op_amp
l_int|255
suffix:semicolon
id|mem_freq_khz
op_assign
id|vco_to_freq
c_func
(paren
id|vco
comma
l_int|2
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CPU%d: Module id: %d&bslash;n&quot;
comma
id|cpu
comma
id|cm_stat
op_amp
l_int|255
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CPU%d: Memory clock = %d.%03d MHz&bslash;n&quot;
comma
id|cpu
comma
id|mem_freq_khz
op_div
l_int|1000
comma
id|mem_freq_khz
op_mod
l_int|1000
)paren
suffix:semicolon
id|vco.od
op_assign
(paren
id|cm_osc
op_rshift
l_int|8
)paren
op_amp
l_int|7
suffix:semicolon
id|vco.vdw
op_assign
id|cm_osc
op_amp
l_int|255
suffix:semicolon
multiline_comment|/* set default policy and cpuinfo */
id|policy-&gt;policy
op_assign
id|CPUFREQ_POLICY_PERFORMANCE
suffix:semicolon
id|policy-&gt;cpuinfo.max_freq
op_assign
l_int|160000
suffix:semicolon
id|policy-&gt;cpuinfo.min_freq
op_assign
l_int|12000
suffix:semicolon
id|policy-&gt;cpuinfo.transition_latency
op_assign
l_int|1000
suffix:semicolon
multiline_comment|/* 1 ms, assumed */
id|policy-&gt;cur
op_assign
id|policy-&gt;min
op_assign
id|policy-&gt;max
op_assign
id|vco_to_freq
c_func
(paren
id|vco
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* current freq */
id|set_cpus_allowed
c_func
(paren
id|current
comma
id|cpus_allowed
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|integrator_driver
r_static
r_struct
id|cpufreq_driver
id|integrator_driver
op_assign
(brace
dot
id|verify
op_assign
id|integrator_verify_policy
comma
dot
id|target
op_assign
id|integrator_set_target
comma
dot
id|init
op_assign
id|integrator_cpufreq_init
comma
dot
id|name
op_assign
l_string|&quot;integrator&quot;
comma
)brace
suffix:semicolon
DECL|function|integrator_cpu_init
r_static
r_int
id|__init
id|integrator_cpu_init
c_func
(paren
r_void
)paren
(brace
r_return
id|cpufreq_register_driver
c_func
(paren
op_amp
id|integrator_driver
)paren
suffix:semicolon
)brace
DECL|function|integrator_cpu_exit
r_static
r_void
id|__exit
id|integrator_cpu_exit
c_func
(paren
r_void
)paren
(brace
id|cpufreq_unregister_driver
c_func
(paren
op_amp
id|integrator_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
(paren
l_string|&quot;Russell M. King&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
(paren
l_string|&quot;cpufreq driver for ARM Integrator CPUs&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|integrator_cpu_init
id|module_init
c_func
(paren
id|integrator_cpu_init
)paren
suffix:semicolon
DECL|variable|integrator_cpu_exit
id|module_exit
c_func
(paren
id|integrator_cpu_exit
)paren
suffix:semicolon
eof
