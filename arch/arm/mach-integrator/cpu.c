multiline_comment|/*&n; *  linux/arch/arm/mach-integrator/cpu.c&n; *&n; *  Copyright (C) 2001-2002 Deep Blue Solutions Ltd.&n; *&n; *  $Id: cpu.c,v 1.6 2002/07/18 13:58:51 rmk Exp $&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * CPU support functions&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/hardware/icst525.h&gt;
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
DECL|variable|lclk_params
r_static
r_const
r_struct
id|icst525_params
id|lclk_params
op_assign
(brace
dot
id|ref
op_assign
l_int|24000
comma
dot
id|vco_max
op_assign
l_int|320000
comma
dot
id|vd_min
op_assign
l_int|8
comma
dot
id|vd_max
op_assign
l_int|132
comma
dot
id|rd_min
op_assign
l_int|24
comma
dot
id|rd_max
op_assign
l_int|24
comma
)brace
suffix:semicolon
DECL|variable|cclk_params
r_static
r_const
r_struct
id|icst525_params
id|cclk_params
op_assign
(brace
dot
id|ref
op_assign
l_int|24000
comma
dot
id|vco_max
op_assign
l_int|320000
comma
dot
id|vd_min
op_assign
l_int|12
comma
dot
id|vd_max
op_assign
l_int|160
comma
dot
id|rd_min
op_assign
l_int|24
comma
dot
id|rd_max
op_assign
l_int|24
comma
)brace
suffix:semicolon
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
id|icst525_vco
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
id|icst525_khz_to_vco
c_func
(paren
op_amp
id|cclk_params
comma
id|policy-&gt;max
)paren
suffix:semicolon
id|policy-&gt;max
op_assign
id|icst525_khz
c_func
(paren
op_amp
id|cclk_params
comma
id|vco
)paren
suffix:semicolon
id|vco
op_assign
id|icst525_khz_to_vco
c_func
(paren
op_amp
id|cclk_params
comma
id|policy-&gt;min
)paren
suffix:semicolon
id|policy-&gt;min
op_assign
id|icst525_khz
c_func
(paren
op_amp
id|cclk_params
comma
id|vco
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
id|icst525_vco
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
r_if
c_cond
(paren
id|machine_is_integrator
c_func
(paren
)paren
)paren
(brace
id|vco.s
op_assign
(paren
id|cm_osc
op_rshift
l_int|8
)paren
op_amp
l_int|7
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|machine_is_cintegrator
c_func
(paren
)paren
)paren
(brace
id|vco.s
op_assign
l_int|1
suffix:semicolon
)brace
id|vco.v
op_assign
id|cm_osc
op_amp
l_int|255
suffix:semicolon
id|vco.r
op_assign
l_int|22
suffix:semicolon
id|freqs.old
op_assign
id|icst525_khz
c_func
(paren
op_amp
id|cclk_params
comma
id|vco
)paren
suffix:semicolon
multiline_comment|/* icst525_khz_to_vco rounds down -- so we need the next&n;&t; * larger freq in case of CPUFREQ_RELATION_L.&n;&t; */
r_if
c_cond
(paren
id|relation
op_eq
id|CPUFREQ_RELATION_L
)paren
id|target_freq
op_add_assign
l_int|999
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
id|icst525_khz_to_vco
c_func
(paren
op_amp
id|cclk_params
comma
id|target_freq
)paren
suffix:semicolon
id|freqs
dot
r_new
op_assign
id|icst525_khz
c_func
(paren
op_amp
id|cclk_params
comma
id|vco
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
r_if
c_cond
(paren
id|machine_is_integrator
c_func
(paren
)paren
)paren
(brace
id|cm_osc
op_and_assign
l_int|0xfffff800
suffix:semicolon
id|cm_osc
op_or_assign
id|vco.s
op_lshift
l_int|8
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|machine_is_cintegrator
c_func
(paren
)paren
)paren
(brace
id|cm_osc
op_and_assign
l_int|0xffffff00
suffix:semicolon
)brace
id|cm_osc
op_or_assign
id|vco.v
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
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_int
r_int
id|cpus_allowed
suffix:semicolon
r_int
r_int
id|cpu
op_assign
id|policy-&gt;cpu
suffix:semicolon
id|u_int
id|cm_osc
suffix:semicolon
r_struct
id|icst525_vco
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
id|cm_osc
op_assign
id|__raw_readl
c_func
(paren
id|CM_OSC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_integrator
c_func
(paren
)paren
)paren
(brace
id|vco.s
op_assign
(paren
id|cm_osc
op_rshift
l_int|8
)paren
op_amp
l_int|7
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|machine_is_cintegrator
c_func
(paren
)paren
)paren
(brace
id|vco.s
op_assign
l_int|1
suffix:semicolon
)brace
id|vco.v
op_assign
id|cm_osc
op_amp
l_int|255
suffix:semicolon
id|vco.r
op_assign
l_int|22
suffix:semicolon
multiline_comment|/* set default policy and cpuinfo */
id|policy-&gt;governor
op_assign
id|CPUFREQ_DEFAULT_GOVERNOR
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
l_int|1000000
suffix:semicolon
multiline_comment|/* 1 ms, assumed */
id|policy-&gt;cur
op_assign
id|policy-&gt;min
op_assign
id|policy-&gt;max
op_assign
id|icst525_khz
c_func
(paren
op_amp
id|cclk_params
comma
id|vco
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
