multiline_comment|/*&n; *  drivers/cpufreq/cpufreq_ondemand.c&n; *&n; *  Copyright (C)  2001 Russell King&n; *            (C)  2003 Venkatesh Pallipadi &lt;venkatesh.pallipadi@intel.com&gt;.&n; *                      Jun Nakajima &lt;jun.nakajima@intel.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sysfs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/percpu.h&gt;
multiline_comment|/*&n; * dbs is used in this file as a shortform for demandbased switching&n; * It helps to keep variable names smaller, simpler&n; */
DECL|macro|DEF_FREQUENCY_UP_THRESHOLD
mdefine_line|#define DEF_FREQUENCY_UP_THRESHOLD&t;&t;(80)
DECL|macro|MIN_FREQUENCY_UP_THRESHOLD
mdefine_line|#define MIN_FREQUENCY_UP_THRESHOLD&t;&t;(0)
DECL|macro|MAX_FREQUENCY_UP_THRESHOLD
mdefine_line|#define MAX_FREQUENCY_UP_THRESHOLD&t;&t;(100)
DECL|macro|DEF_FREQUENCY_DOWN_THRESHOLD
mdefine_line|#define DEF_FREQUENCY_DOWN_THRESHOLD&t;&t;(20)
DECL|macro|MIN_FREQUENCY_DOWN_THRESHOLD
mdefine_line|#define MIN_FREQUENCY_DOWN_THRESHOLD&t;&t;(0)
DECL|macro|MAX_FREQUENCY_DOWN_THRESHOLD
mdefine_line|#define MAX_FREQUENCY_DOWN_THRESHOLD&t;&t;(100)
multiline_comment|/* &n; * The polling frequency of this governor depends on the capability of &n; * the processor. Default polling frequency is 1000 times the transition&n; * latency of the processor. The governor will work on any processor with &n; * transition latency &lt;= 10mS, using appropriate sampling &n; * rate.&n; * For CPUs with transition latency &gt; 10mS (mostly drivers with CPUFREQ_ETERNAL)&n; * this governor will not work.&n; * All times here are in uS.&n; */
DECL|variable|def_sampling_rate
r_static
r_int
r_int
id|def_sampling_rate
suffix:semicolon
DECL|macro|MIN_SAMPLING_RATE
mdefine_line|#define MIN_SAMPLING_RATE&t;&t;&t;(def_sampling_rate / 2)
DECL|macro|MAX_SAMPLING_RATE
mdefine_line|#define MAX_SAMPLING_RATE&t;&t;&t;(500 * def_sampling_rate)
DECL|macro|DEF_SAMPLING_RATE_LATENCY_MULTIPLIER
mdefine_line|#define DEF_SAMPLING_RATE_LATENCY_MULTIPLIER&t;(1000)
DECL|macro|DEF_SAMPLING_DOWN_FACTOR
mdefine_line|#define DEF_SAMPLING_DOWN_FACTOR&t;&t;(10)
DECL|macro|TRANSITION_LATENCY_LIMIT
mdefine_line|#define TRANSITION_LATENCY_LIMIT&t;&t;(10 * 1000)
DECL|macro|sampling_rate_in_HZ
mdefine_line|#define sampling_rate_in_HZ(x)&t;&t;&t;(((x * HZ) &lt; (1000 * 1000))?1:((x * HZ) / (1000 * 1000)))
r_static
r_void
id|do_dbs_timer
c_func
(paren
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|struct|cpu_dbs_info_s
r_struct
id|cpu_dbs_info_s
(brace
DECL|member|cur_policy
r_struct
id|cpufreq_policy
op_star
id|cur_policy
suffix:semicolon
DECL|member|prev_cpu_idle_up
r_int
r_int
id|prev_cpu_idle_up
suffix:semicolon
DECL|member|prev_cpu_idle_down
r_int
r_int
id|prev_cpu_idle_down
suffix:semicolon
DECL|member|enable
r_int
r_int
id|enable
suffix:semicolon
)brace
suffix:semicolon
r_static
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|cpu_dbs_info_s
comma
id|cpu_dbs_info
)paren
suffix:semicolon
DECL|variable|dbs_enable
r_static
r_int
r_int
id|dbs_enable
suffix:semicolon
multiline_comment|/* number of CPUs using this policy */
r_static
id|DECLARE_MUTEX
(paren
id|dbs_sem
)paren
suffix:semicolon
r_static
id|DECLARE_WORK
(paren
id|dbs_work
comma
id|do_dbs_timer
comma
l_int|NULL
)paren
suffix:semicolon
DECL|struct|dbs_tuners
r_struct
id|dbs_tuners
(brace
DECL|member|sampling_rate
r_int
r_int
id|sampling_rate
suffix:semicolon
DECL|member|sampling_down_factor
r_int
r_int
id|sampling_down_factor
suffix:semicolon
DECL|member|up_threshold
r_int
r_int
id|up_threshold
suffix:semicolon
DECL|member|down_threshold
r_int
r_int
id|down_threshold
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|dbs_tuners_ins
r_static
r_struct
id|dbs_tuners
id|dbs_tuners_ins
op_assign
(brace
dot
id|up_threshold
op_assign
id|DEF_FREQUENCY_UP_THRESHOLD
comma
dot
id|down_threshold
op_assign
id|DEF_FREQUENCY_DOWN_THRESHOLD
comma
dot
id|sampling_down_factor
op_assign
id|DEF_SAMPLING_DOWN_FACTOR
comma
)brace
suffix:semicolon
multiline_comment|/************************** sysfs interface ************************/
DECL|function|show_sampling_rate_max
r_static
id|ssize_t
id|show_sampling_rate_max
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
comma
r_char
op_star
id|buf
)paren
(brace
r_return
id|sprintf
(paren
id|buf
comma
l_string|&quot;%u&bslash;n&quot;
comma
id|MAX_SAMPLING_RATE
)paren
suffix:semicolon
)brace
DECL|function|show_sampling_rate_min
r_static
id|ssize_t
id|show_sampling_rate_min
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
comma
r_char
op_star
id|buf
)paren
(brace
r_return
id|sprintf
(paren
id|buf
comma
l_string|&quot;%u&bslash;n&quot;
comma
id|MIN_SAMPLING_RATE
)paren
suffix:semicolon
)brace
DECL|macro|define_one_ro
mdefine_line|#define define_one_ro(_name) &t;&t;&t;&t;&t;&bslash;&n;static struct freq_attr _name =  &t;&t;&t;&t;&bslash;&n;__ATTR(_name, 0444, show_##_name, NULL)
DECL|variable|sampling_rate_max
id|define_one_ro
c_func
(paren
id|sampling_rate_max
)paren
suffix:semicolon
DECL|variable|sampling_rate_min
id|define_one_ro
c_func
(paren
id|sampling_rate_min
)paren
suffix:semicolon
multiline_comment|/* cpufreq_ondemand Governor Tunables */
DECL|macro|show_one
mdefine_line|#define show_one(file_name, object)&t;&t;&t;&t;&t;&bslash;&n;static ssize_t show_##file_name&t;&t;&t;&t;&t;&t;&bslash;&n;(struct cpufreq_policy *unused, char *buf)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return sprintf(buf, &quot;%u&bslash;n&quot;, dbs_tuners_ins.object);&t;&t;&bslash;&n;}
id|show_one
c_func
(paren
id|sampling_rate
comma
id|sampling_rate
)paren
suffix:semicolon
id|show_one
c_func
(paren
id|sampling_down_factor
comma
id|sampling_down_factor
)paren
suffix:semicolon
id|show_one
c_func
(paren
id|up_threshold
comma
id|up_threshold
)paren
suffix:semicolon
id|show_one
c_func
(paren
id|down_threshold
comma
id|down_threshold
)paren
suffix:semicolon
DECL|function|store_sampling_down_factor
r_static
id|ssize_t
id|store_sampling_down_factor
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|unused
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
r_int
id|input
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|sscanf
(paren
id|buf
comma
l_string|&quot;%u&quot;
comma
op_amp
id|input
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dbs_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|1
)paren
r_goto
id|out
suffix:semicolon
id|dbs_tuners_ins.sampling_down_factor
op_assign
id|input
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|dbs_sem
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|store_sampling_rate
r_static
id|ssize_t
id|store_sampling_rate
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|unused
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
r_int
id|input
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|sscanf
(paren
id|buf
comma
l_string|&quot;%u&quot;
comma
op_amp
id|input
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dbs_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|1
op_logical_or
id|input
OG
id|MAX_SAMPLING_RATE
op_logical_or
id|input
OL
id|MIN_SAMPLING_RATE
)paren
r_goto
id|out
suffix:semicolon
id|dbs_tuners_ins.sampling_rate
op_assign
id|input
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|dbs_sem
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|store_up_threshold
r_static
id|ssize_t
id|store_up_threshold
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|unused
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
r_int
id|input
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|sscanf
(paren
id|buf
comma
l_string|&quot;%u&quot;
comma
op_amp
id|input
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dbs_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|1
op_logical_or
id|input
OG
id|MAX_FREQUENCY_UP_THRESHOLD
op_logical_or
id|input
OL
id|MIN_FREQUENCY_UP_THRESHOLD
op_logical_or
id|input
op_le
id|dbs_tuners_ins.down_threshold
)paren
r_goto
id|out
suffix:semicolon
id|dbs_tuners_ins.up_threshold
op_assign
id|input
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|dbs_sem
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|store_down_threshold
r_static
id|ssize_t
id|store_down_threshold
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|unused
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
r_int
id|input
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|sscanf
(paren
id|buf
comma
l_string|&quot;%u&quot;
comma
op_amp
id|input
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dbs_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|1
op_logical_or
id|input
OG
id|MAX_FREQUENCY_DOWN_THRESHOLD
op_logical_or
id|input
OL
id|MIN_FREQUENCY_DOWN_THRESHOLD
op_logical_or
id|input
op_ge
id|dbs_tuners_ins.up_threshold
)paren
r_goto
id|out
suffix:semicolon
id|dbs_tuners_ins.down_threshold
op_assign
id|input
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|dbs_sem
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|macro|define_one_rw
mdefine_line|#define define_one_rw(_name) &bslash;&n;static struct freq_attr _name = &bslash;&n;__ATTR(_name, 0644, show_##_name, store_##_name)
DECL|variable|sampling_rate
id|define_one_rw
c_func
(paren
id|sampling_rate
)paren
suffix:semicolon
DECL|variable|sampling_down_factor
id|define_one_rw
c_func
(paren
id|sampling_down_factor
)paren
suffix:semicolon
DECL|variable|up_threshold
id|define_one_rw
c_func
(paren
id|up_threshold
)paren
suffix:semicolon
DECL|variable|down_threshold
id|define_one_rw
c_func
(paren
id|down_threshold
)paren
suffix:semicolon
DECL|variable|dbs_attributes
r_static
r_struct
id|attribute
op_star
id|dbs_attributes
(braket
)braket
op_assign
(brace
op_amp
id|sampling_rate_max.attr
comma
op_amp
id|sampling_rate_min.attr
comma
op_amp
id|sampling_rate.attr
comma
op_amp
id|sampling_down_factor.attr
comma
op_amp
id|up_threshold.attr
comma
op_amp
id|down_threshold.attr
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|dbs_attr_group
r_static
r_struct
id|attribute_group
id|dbs_attr_group
op_assign
(brace
dot
id|attrs
op_assign
id|dbs_attributes
comma
dot
id|name
op_assign
l_string|&quot;ondemand&quot;
comma
)brace
suffix:semicolon
multiline_comment|/************************** sysfs end ************************/
DECL|function|dbs_check_cpu
r_static
r_void
id|dbs_check_cpu
c_func
(paren
r_int
id|cpu
)paren
(brace
r_int
r_int
id|idle_ticks
comma
id|up_idle_ticks
comma
id|down_idle_ticks
suffix:semicolon
r_int
r_int
id|total_idle_ticks
suffix:semicolon
r_int
r_int
id|freq_down_step
suffix:semicolon
r_int
r_int
id|freq_down_sampling_rate
suffix:semicolon
r_static
r_int
id|down_skip
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_struct
id|cpu_dbs_info_s
op_star
id|this_dbs_info
suffix:semicolon
id|this_dbs_info
op_assign
op_amp
id|per_cpu
c_func
(paren
id|cpu_dbs_info
comma
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|this_dbs_info-&gt;enable
)paren
r_return
suffix:semicolon
multiline_comment|/* &n;&t; * The default safe range is 20% to 80% &n;&t; * Every sampling_rate, we check&n;&t; * &t;- If current idle time is less than 20%, then we try to &n;&t; * &t;  increase frequency&n;&t; * Every sampling_rate*sampling_down_factor, we check&n;&t; * &t;- If current idle time is more than 80%, then we try to&n;&t; * &t;  decrease frequency&n;&t; *&n;&t; * Any frequency increase takes it to the maximum frequency. &n;&t; * Frequency reduction happens at minimum steps of &n;&t; * 5% of max_frequency &n;&t; */
multiline_comment|/* Check for frequency increase */
id|total_idle_ticks
op_assign
id|kstat_cpu
c_func
(paren
id|cpu
)paren
dot
id|cpustat.idle
op_plus
id|kstat_cpu
c_func
(paren
id|cpu
)paren
dot
id|cpustat.iowait
suffix:semicolon
id|idle_ticks
op_assign
id|total_idle_ticks
op_minus
id|this_dbs_info-&gt;prev_cpu_idle_up
suffix:semicolon
id|this_dbs_info-&gt;prev_cpu_idle_up
op_assign
id|total_idle_ticks
suffix:semicolon
multiline_comment|/* Scale idle ticks by 100 and compare with up and down ticks */
id|idle_ticks
op_mul_assign
l_int|100
suffix:semicolon
id|up_idle_ticks
op_assign
(paren
l_int|100
op_minus
id|dbs_tuners_ins.up_threshold
)paren
op_star
id|sampling_rate_in_HZ
c_func
(paren
id|dbs_tuners_ins.sampling_rate
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idle_ticks
OL
id|up_idle_ticks
)paren
(brace
id|__cpufreq_driver_target
c_func
(paren
id|this_dbs_info-&gt;cur_policy
comma
id|this_dbs_info-&gt;cur_policy-&gt;max
comma
id|CPUFREQ_RELATION_H
)paren
suffix:semicolon
id|down_skip
(braket
id|cpu
)braket
op_assign
l_int|0
suffix:semicolon
id|this_dbs_info-&gt;prev_cpu_idle_down
op_assign
id|total_idle_ticks
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Check for frequency decrease */
id|down_skip
(braket
id|cpu
)braket
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|down_skip
(braket
id|cpu
)braket
OL
id|dbs_tuners_ins.sampling_down_factor
)paren
r_return
suffix:semicolon
id|idle_ticks
op_assign
id|total_idle_ticks
op_minus
id|this_dbs_info-&gt;prev_cpu_idle_down
suffix:semicolon
multiline_comment|/* Scale idle ticks by 100 and compare with up and down ticks */
id|idle_ticks
op_mul_assign
l_int|100
suffix:semicolon
id|down_skip
(braket
id|cpu
)braket
op_assign
l_int|0
suffix:semicolon
id|this_dbs_info-&gt;prev_cpu_idle_down
op_assign
id|total_idle_ticks
suffix:semicolon
id|freq_down_sampling_rate
op_assign
id|dbs_tuners_ins.sampling_rate
op_star
id|dbs_tuners_ins.sampling_down_factor
suffix:semicolon
id|down_idle_ticks
op_assign
(paren
l_int|100
op_minus
id|dbs_tuners_ins.down_threshold
)paren
op_star
id|sampling_rate_in_HZ
c_func
(paren
id|freq_down_sampling_rate
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idle_ticks
OG
id|down_idle_ticks
)paren
(brace
id|freq_down_step
op_assign
(paren
l_int|5
op_star
id|this_dbs_info-&gt;cur_policy-&gt;max
)paren
op_div
l_int|100
suffix:semicolon
multiline_comment|/* max freq cannot be less than 100. But who knows.... */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|freq_down_step
op_eq
l_int|0
)paren
)paren
id|freq_down_step
op_assign
l_int|5
suffix:semicolon
id|__cpufreq_driver_target
c_func
(paren
id|this_dbs_info-&gt;cur_policy
comma
id|this_dbs_info-&gt;cur_policy-&gt;cur
op_minus
id|freq_down_step
comma
id|CPUFREQ_RELATION_H
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
DECL|function|do_dbs_timer
r_static
r_void
id|do_dbs_timer
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_int
id|i
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dbs_sem
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
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|cpu_online
c_func
(paren
id|i
)paren
)paren
id|dbs_check_cpu
c_func
(paren
id|i
)paren
suffix:semicolon
id|schedule_delayed_work
c_func
(paren
op_amp
id|dbs_work
comma
id|sampling_rate_in_HZ
c_func
(paren
id|dbs_tuners_ins.sampling_rate
)paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dbs_sem
)paren
suffix:semicolon
)brace
DECL|function|dbs_timer_init
r_static
r_inline
r_void
id|dbs_timer_init
c_func
(paren
r_void
)paren
(brace
id|INIT_WORK
c_func
(paren
op_amp
id|dbs_work
comma
id|do_dbs_timer
comma
l_int|NULL
)paren
suffix:semicolon
id|schedule_work
c_func
(paren
op_amp
id|dbs_work
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|dbs_timer_exit
r_static
r_inline
r_void
id|dbs_timer_exit
c_func
(paren
r_void
)paren
(brace
id|cancel_delayed_work
c_func
(paren
op_amp
id|dbs_work
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|cpufreq_governor_dbs
r_static
r_int
id|cpufreq_governor_dbs
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
comma
r_int
r_int
id|event
)paren
(brace
r_int
r_int
id|cpu
op_assign
id|policy-&gt;cpu
suffix:semicolon
r_struct
id|cpu_dbs_info_s
op_star
id|this_dbs_info
suffix:semicolon
id|this_dbs_info
op_assign
op_amp
id|per_cpu
c_func
(paren
id|cpu_dbs_info
comma
id|cpu
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|CPUFREQ_GOV_START
suffix:colon
r_if
c_cond
(paren
(paren
op_logical_neg
id|cpu_online
c_func
(paren
id|cpu
)paren
)paren
op_logical_or
(paren
op_logical_neg
id|policy-&gt;cur
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|policy-&gt;cpuinfo.transition_latency
OG
(paren
id|TRANSITION_LATENCY_LIMIT
op_star
l_int|1000
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|this_dbs_info-&gt;enable
)paren
multiline_comment|/* Already enabled */
r_break
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dbs_sem
)paren
suffix:semicolon
id|this_dbs_info-&gt;cur_policy
op_assign
id|policy
suffix:semicolon
id|this_dbs_info-&gt;prev_cpu_idle_up
op_assign
id|kstat_cpu
c_func
(paren
id|cpu
)paren
dot
id|cpustat.idle
op_plus
id|kstat_cpu
c_func
(paren
id|cpu
)paren
dot
id|cpustat.iowait
suffix:semicolon
id|this_dbs_info-&gt;prev_cpu_idle_down
op_assign
id|kstat_cpu
c_func
(paren
id|cpu
)paren
dot
id|cpustat.idle
op_plus
id|kstat_cpu
c_func
(paren
id|cpu
)paren
dot
id|cpustat.iowait
suffix:semicolon
id|this_dbs_info-&gt;enable
op_assign
l_int|1
suffix:semicolon
id|sysfs_create_group
c_func
(paren
op_amp
id|policy-&gt;kobj
comma
op_amp
id|dbs_attr_group
)paren
suffix:semicolon
id|dbs_enable
op_increment
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Start the timerschedule work, when this governor&n;&t;&t; * is used for first time&n;&t;&t; */
r_if
c_cond
(paren
id|dbs_enable
op_eq
l_int|1
)paren
(brace
r_int
r_int
id|latency
suffix:semicolon
multiline_comment|/* policy latency is in nS. Convert it to uS first */
id|latency
op_assign
id|policy-&gt;cpuinfo.transition_latency
suffix:semicolon
r_if
c_cond
(paren
id|latency
OL
l_int|1000
)paren
id|latency
op_assign
l_int|1000
suffix:semicolon
id|def_sampling_rate
op_assign
(paren
id|latency
op_div
l_int|1000
)paren
op_star
id|DEF_SAMPLING_RATE_LATENCY_MULTIPLIER
suffix:semicolon
id|dbs_tuners_ins.sampling_rate
op_assign
id|def_sampling_rate
suffix:semicolon
id|dbs_timer_init
c_func
(paren
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|dbs_sem
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPUFREQ_GOV_STOP
suffix:colon
id|down
c_func
(paren
op_amp
id|dbs_sem
)paren
suffix:semicolon
id|this_dbs_info-&gt;enable
op_assign
l_int|0
suffix:semicolon
id|sysfs_remove_group
c_func
(paren
op_amp
id|policy-&gt;kobj
comma
op_amp
id|dbs_attr_group
)paren
suffix:semicolon
id|dbs_enable
op_decrement
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Stop the timerschedule work, when this governor&n;&t;&t; * is used for first time&n;&t;&t; */
r_if
c_cond
(paren
id|dbs_enable
op_eq
l_int|0
)paren
id|dbs_timer_exit
c_func
(paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dbs_sem
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPUFREQ_GOV_LIMITS
suffix:colon
id|down
c_func
(paren
op_amp
id|dbs_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|policy-&gt;max
OL
id|this_dbs_info-&gt;cur_policy-&gt;cur
)paren
id|__cpufreq_driver_target
c_func
(paren
id|this_dbs_info-&gt;cur_policy
comma
id|policy-&gt;max
comma
id|CPUFREQ_RELATION_H
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|policy-&gt;min
OG
id|this_dbs_info-&gt;cur_policy-&gt;cur
)paren
id|__cpufreq_driver_target
c_func
(paren
id|this_dbs_info-&gt;cur_policy
comma
id|policy-&gt;min
comma
id|CPUFREQ_RELATION_L
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dbs_sem
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cpufreq_gov_dbs
r_struct
id|cpufreq_governor
id|cpufreq_gov_dbs
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ondemand&quot;
comma
dot
id|governor
op_assign
id|cpufreq_governor_dbs
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|variable|cpufreq_gov_dbs
id|EXPORT_SYMBOL
c_func
(paren
id|cpufreq_gov_dbs
)paren
suffix:semicolon
DECL|function|cpufreq_gov_dbs_init
r_static
r_int
id|__init
id|cpufreq_gov_dbs_init
c_func
(paren
r_void
)paren
(brace
r_return
id|cpufreq_register_governor
c_func
(paren
op_amp
id|cpufreq_gov_dbs
)paren
suffix:semicolon
)brace
DECL|function|cpufreq_gov_dbs_exit
r_static
r_void
id|__exit
id|cpufreq_gov_dbs_exit
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Make sure that the scheduled work is indeed not running */
id|flush_scheduled_work
c_func
(paren
)paren
suffix:semicolon
id|cpufreq_unregister_governor
c_func
(paren
op_amp
id|cpufreq_gov_dbs
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
(paren
l_string|&quot;Venkatesh Pallipadi &lt;venkatesh.pallipadi@intel.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
(paren
l_string|&quot;&squot;cpufreq_ondemand&squot; - A dynamic cpufreq governor for &quot;
l_string|&quot;Low Latency Frequency Transition capable processors&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|cpufreq_gov_dbs_init
id|module_init
c_func
(paren
id|cpufreq_gov_dbs_init
)paren
suffix:semicolon
DECL|variable|cpufreq_gov_dbs_exit
id|module_exit
c_func
(paren
id|cpufreq_gov_dbs_exit
)paren
suffix:semicolon
eof
