multiline_comment|/*&n; *  linux/include/linux/cpufreq.h&n; *&n; *  Copyright (C) 2001 Russell King&n; *            (C) 2002 - 2003 Dominik Brodowski &lt;linux@brodo.de&gt;&n; *            &n; *&n; * $Id: cpufreq.h,v 1.36 2003/01/20 17:31:48 db Exp $&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef _LINUX_CPUFREQ_H
DECL|macro|_LINUX_CPUFREQ_H
mdefine_line|#define _LINUX_CPUFREQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &lt;linux/sysfs.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;linux/cpumask.h&gt;
DECL|macro|CPUFREQ_NAME_LEN
mdefine_line|#define CPUFREQ_NAME_LEN 16
multiline_comment|/*********************************************************************&n; *                     CPUFREQ NOTIFIER INTERFACE                    *&n; *********************************************************************/
r_int
id|cpufreq_register_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
comma
r_int
r_int
id|list
)paren
suffix:semicolon
r_int
id|cpufreq_unregister_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
comma
r_int
r_int
id|list
)paren
suffix:semicolon
DECL|macro|CPUFREQ_TRANSITION_NOTIFIER
mdefine_line|#define CPUFREQ_TRANSITION_NOTIFIER&t;(0)
DECL|macro|CPUFREQ_POLICY_NOTIFIER
mdefine_line|#define CPUFREQ_POLICY_NOTIFIER&t;&t;(1)
multiline_comment|/* if (cpufreq_driver-&gt;target) exists, the -&gt;governor decides what frequency&n; * within the limits is used. If (cpufreq_driver-&gt;setpolicy&gt; exists, these&n; * two generic policies are available:&n; */
DECL|macro|CPUFREQ_POLICY_POWERSAVE
mdefine_line|#define CPUFREQ_POLICY_POWERSAVE&t;(1)
DECL|macro|CPUFREQ_POLICY_PERFORMANCE
mdefine_line|#define CPUFREQ_POLICY_PERFORMANCE&t;(2)
multiline_comment|/* Frequency values here are CPU kHz so that hardware which doesn&squot;t run &n; * with some frequencies can complain without having to guess what per &n; * cent / per mille means. &n; * Maximum transition latency is in microseconds - if it&squot;s unknown,&n; * CPUFREQ_ETERNAL shall be used.&n; */
r_struct
id|cpufreq_governor
suffix:semicolon
DECL|macro|CPUFREQ_ETERNAL
mdefine_line|#define CPUFREQ_ETERNAL&t;&t;&t;(-1)
DECL|struct|cpufreq_cpuinfo
r_struct
id|cpufreq_cpuinfo
(brace
DECL|member|max_freq
r_int
r_int
id|max_freq
suffix:semicolon
DECL|member|min_freq
r_int
r_int
id|min_freq
suffix:semicolon
DECL|member|transition_latency
r_int
r_int
id|transition_latency
suffix:semicolon
multiline_comment|/* in 10^(-9) s = nanoseconds */
)brace
suffix:semicolon
DECL|struct|cpufreq_real_policy
r_struct
id|cpufreq_real_policy
(brace
DECL|member|min
r_int
r_int
id|min
suffix:semicolon
multiline_comment|/* in kHz */
DECL|member|max
r_int
r_int
id|max
suffix:semicolon
multiline_comment|/* in kHz */
DECL|member|policy
r_int
r_int
id|policy
suffix:semicolon
multiline_comment|/* see above */
DECL|member|governor
r_struct
id|cpufreq_governor
op_star
id|governor
suffix:semicolon
multiline_comment|/* see below */
)brace
suffix:semicolon
DECL|struct|cpufreq_policy
r_struct
id|cpufreq_policy
(brace
DECL|member|cpus
id|cpumask_t
id|cpus
suffix:semicolon
multiline_comment|/* affected CPUs */
DECL|member|cpu
r_int
r_int
id|cpu
suffix:semicolon
multiline_comment|/* cpu nr of registered CPU */
DECL|member|cpuinfo
r_struct
id|cpufreq_cpuinfo
id|cpuinfo
suffix:semicolon
multiline_comment|/* see above */
DECL|member|min
r_int
r_int
id|min
suffix:semicolon
multiline_comment|/* in kHz */
DECL|member|max
r_int
r_int
id|max
suffix:semicolon
multiline_comment|/* in kHz */
DECL|member|cur
r_int
r_int
id|cur
suffix:semicolon
multiline_comment|/* in kHz, only needed if cpufreq&n;&t;&t;&t;&t;&t; * governors are used */
DECL|member|policy
r_int
r_int
id|policy
suffix:semicolon
multiline_comment|/* see above */
DECL|member|governor
r_struct
id|cpufreq_governor
op_star
id|governor
suffix:semicolon
multiline_comment|/* see below */
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
multiline_comment|/* CPU -&gt;setpolicy or -&gt;target may&n;&t;&t;&t;&t;&t;   only be called once a time */
DECL|member|update
r_struct
id|work_struct
id|update
suffix:semicolon
multiline_comment|/* if update_policy() needs to be&n;&t;&t;&t;&t;&t; * called, but you&squot;re in IRQ context */
DECL|member|user_policy
r_struct
id|cpufreq_real_policy
id|user_policy
suffix:semicolon
DECL|member|kobj
r_struct
id|kobject
id|kobj
suffix:semicolon
DECL|member|kobj_unregister
r_struct
id|completion
id|kobj_unregister
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CPUFREQ_ADJUST
mdefine_line|#define CPUFREQ_ADJUST&t;&t;(0)
DECL|macro|CPUFREQ_INCOMPATIBLE
mdefine_line|#define CPUFREQ_INCOMPATIBLE&t;(1)
DECL|macro|CPUFREQ_NOTIFY
mdefine_line|#define CPUFREQ_NOTIFY&t;&t;(2)
multiline_comment|/******************** cpufreq transition notifiers *******************/
DECL|macro|CPUFREQ_PRECHANGE
mdefine_line|#define CPUFREQ_PRECHANGE&t;(0)
DECL|macro|CPUFREQ_POSTCHANGE
mdefine_line|#define CPUFREQ_POSTCHANGE&t;(1)
DECL|macro|CPUFREQ_RESUMECHANGE
mdefine_line|#define CPUFREQ_RESUMECHANGE&t;(8)
DECL|struct|cpufreq_freqs
r_struct
id|cpufreq_freqs
(brace
DECL|member|cpu
r_int
r_int
id|cpu
suffix:semicolon
multiline_comment|/* cpu nr */
DECL|member|old
r_int
r_int
id|old
suffix:semicolon
DECL|member|new
r_int
r_int
r_new
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
multiline_comment|/* flags of cpufreq_driver, see below. */
)brace
suffix:semicolon
multiline_comment|/**&n; * cpufreq_scale - &quot;old * mult / div&quot; calculation for large values (32-bit-arch safe)&n; * @old:   old value&n; * @div:   divisor&n; * @mult:  multiplier&n; *&n; *&n; *    new = old * mult / div&n; */
DECL|function|cpufreq_scale
r_static
r_inline
r_int
r_int
id|cpufreq_scale
c_func
(paren
r_int
r_int
id|old
comma
id|u_int
id|div
comma
id|u_int
id|mult
)paren
(brace
macro_line|#if BITS_PER_LONG == 32
id|u64
id|result
op_assign
(paren
(paren
id|u64
)paren
id|old
)paren
op_star
(paren
(paren
id|u64
)paren
id|mult
)paren
suffix:semicolon
id|do_div
c_func
(paren
id|result
comma
id|div
)paren
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
id|result
suffix:semicolon
macro_line|#elif BITS_PER_LONG == 64
r_int
r_int
id|result
op_assign
id|old
op_star
(paren
(paren
id|u64
)paren
id|mult
)paren
suffix:semicolon
id|result
op_div_assign
id|div
suffix:semicolon
r_return
id|result
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/*********************************************************************&n; *                          CPUFREQ GOVERNORS                        *&n; *********************************************************************/
DECL|macro|CPUFREQ_GOV_START
mdefine_line|#define CPUFREQ_GOV_START  1
DECL|macro|CPUFREQ_GOV_STOP
mdefine_line|#define CPUFREQ_GOV_STOP   2
DECL|macro|CPUFREQ_GOV_LIMITS
mdefine_line|#define CPUFREQ_GOV_LIMITS 3
DECL|struct|cpufreq_governor
r_struct
id|cpufreq_governor
(brace
DECL|member|name
r_char
id|name
(braket
id|CPUFREQ_NAME_LEN
)braket
suffix:semicolon
DECL|member|governor
r_int
(paren
op_star
id|governor
)paren
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
suffix:semicolon
DECL|member|governor_list
r_struct
id|list_head
id|governor_list
suffix:semicolon
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* pass a target to the cpufreq driver &n; */
r_extern
r_int
id|cpufreq_driver_target
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
suffix:semicolon
r_extern
r_int
id|__cpufreq_driver_target
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
suffix:semicolon
multiline_comment|/* pass an event to the cpufreq governor */
r_int
id|cpufreq_governor
c_func
(paren
r_int
r_int
id|cpu
comma
r_int
r_int
id|event
)paren
suffix:semicolon
r_int
id|cpufreq_register_governor
c_func
(paren
r_struct
id|cpufreq_governor
op_star
id|governor
)paren
suffix:semicolon
r_void
id|cpufreq_unregister_governor
c_func
(paren
r_struct
id|cpufreq_governor
op_star
id|governor
)paren
suffix:semicolon
multiline_comment|/*********************************************************************&n; *                      CPUFREQ DRIVER INTERFACE                     *&n; *********************************************************************/
DECL|macro|CPUFREQ_RELATION_L
mdefine_line|#define CPUFREQ_RELATION_L 0  /* lowest frequency at or above target */
DECL|macro|CPUFREQ_RELATION_H
mdefine_line|#define CPUFREQ_RELATION_H 1  /* highest frequency below or at target */
r_struct
id|freq_attr
suffix:semicolon
DECL|struct|cpufreq_driver
r_struct
id|cpufreq_driver
(brace
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|CPUFREQ_NAME_LEN
)braket
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
multiline_comment|/* needed by all drivers */
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
suffix:semicolon
DECL|member|verify
r_int
(paren
op_star
id|verify
)paren
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
suffix:semicolon
multiline_comment|/* define one out of two */
DECL|member|setpolicy
r_int
(paren
op_star
id|setpolicy
)paren
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
suffix:semicolon
DECL|member|target
r_int
(paren
op_star
id|target
)paren
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
suffix:semicolon
multiline_comment|/* should be defined, if possible */
DECL|member|get
r_int
r_int
(paren
op_star
id|get
)paren
(paren
r_int
r_int
id|cpu
)paren
suffix:semicolon
multiline_comment|/* optional */
DECL|member|exit
r_int
(paren
op_star
m_exit
)paren
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
suffix:semicolon
DECL|member|resume
r_int
(paren
op_star
id|resume
)paren
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
suffix:semicolon
DECL|member|attr
r_struct
id|freq_attr
op_star
op_star
id|attr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* flags */
DECL|macro|CPUFREQ_STICKY
mdefine_line|#define CPUFREQ_STICKY&t;&t;0x01&t;/* the driver isn&squot;t removed even if &n;&t;&t;&t;&t;&t; * all -&gt;init() calls failed */
DECL|macro|CPUFREQ_CONST_LOOPS
mdefine_line|#define CPUFREQ_CONST_LOOPS &t;0x02&t;/* loops_per_jiffy or other kernel&n;&t;&t;&t;&t;&t; * &quot;constants&quot; aren&squot;t affected by&n;&t;&t;&t;&t;&t; * frequency transitions */
r_int
id|cpufreq_register_driver
c_func
(paren
r_struct
id|cpufreq_driver
op_star
id|driver_data
)paren
suffix:semicolon
r_int
id|cpufreq_unregister_driver
c_func
(paren
r_struct
id|cpufreq_driver
op_star
id|driver_data
)paren
suffix:semicolon
r_void
id|cpufreq_notify_transition
c_func
(paren
r_struct
id|cpufreq_freqs
op_star
id|freqs
comma
r_int
r_int
id|state
)paren
suffix:semicolon
DECL|function|cpufreq_verify_within_limits
r_static
r_inline
r_void
id|cpufreq_verify_within_limits
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
comma
r_int
r_int
id|min
comma
r_int
r_int
id|max
)paren
(brace
r_if
c_cond
(paren
id|policy-&gt;min
OL
id|min
)paren
id|policy-&gt;min
op_assign
id|min
suffix:semicolon
r_if
c_cond
(paren
id|policy-&gt;max
OL
id|min
)paren
id|policy-&gt;max
op_assign
id|min
suffix:semicolon
r_if
c_cond
(paren
id|policy-&gt;min
OG
id|max
)paren
id|policy-&gt;min
op_assign
id|max
suffix:semicolon
r_if
c_cond
(paren
id|policy-&gt;max
OG
id|max
)paren
id|policy-&gt;max
op_assign
id|max
suffix:semicolon
r_if
c_cond
(paren
id|policy-&gt;min
OG
id|policy-&gt;max
)paren
id|policy-&gt;min
op_assign
id|policy-&gt;max
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|struct|freq_attr
r_struct
id|freq_attr
(brace
DECL|member|attr
r_struct
id|attribute
id|attr
suffix:semicolon
DECL|member|show
id|ssize_t
(paren
op_star
id|show
)paren
(paren
r_struct
id|cpufreq_policy
op_star
comma
r_char
op_star
)paren
suffix:semicolon
DECL|member|store
id|ssize_t
(paren
op_star
id|store
)paren
(paren
r_struct
id|cpufreq_policy
op_star
comma
r_const
r_char
op_star
comma
r_int
id|count
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*********************************************************************&n; *                        CPUFREQ 2.6. INTERFACE                     *&n; *********************************************************************/
r_int
id|cpufreq_set_policy
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
suffix:semicolon
r_int
id|cpufreq_get_policy
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
comma
r_int
r_int
id|cpu
)paren
suffix:semicolon
r_int
id|cpufreq_update_policy
c_func
(paren
r_int
r_int
id|cpu
)paren
suffix:semicolon
multiline_comment|/* query the current CPU frequency (in kHz). If zero, cpufreq couldn&squot;t detect it */
r_int
r_int
id|cpufreq_get
c_func
(paren
r_int
r_int
id|cpu
)paren
suffix:semicolon
multiline_comment|/* the proc_intf.c needs this */
r_int
id|cpufreq_parse_governor
(paren
r_char
op_star
id|str_governor
comma
r_int
r_int
op_star
id|policy
comma
r_struct
id|cpufreq_governor
op_star
op_star
id|governor
)paren
suffix:semicolon
multiline_comment|/*********************************************************************&n; *                      CPUFREQ USERSPACE GOVERNOR                   *&n; *********************************************************************/
macro_line|#ifdef CONFIG_CPU_FREQ_24_API
r_int
id|__deprecated
id|cpufreq_setmax
c_func
(paren
r_int
r_int
id|cpu
)paren
suffix:semicolon
r_int
id|__deprecated
id|cpufreq_set
c_func
(paren
r_int
r_int
id|kHz
comma
r_int
r_int
id|cpu
)paren
suffix:semicolon
multiline_comment|/* /proc/sys/cpu */
r_enum
(brace
DECL|enumerator|CPU_NR
id|CPU_NR
op_assign
l_int|1
comma
multiline_comment|/* compatibilty reasons */
DECL|enumerator|CPU_NR_0
id|CPU_NR_0
op_assign
l_int|1
comma
DECL|enumerator|CPU_NR_1
id|CPU_NR_1
op_assign
l_int|2
comma
DECL|enumerator|CPU_NR_2
id|CPU_NR_2
op_assign
l_int|3
comma
DECL|enumerator|CPU_NR_3
id|CPU_NR_3
op_assign
l_int|4
comma
DECL|enumerator|CPU_NR_4
id|CPU_NR_4
op_assign
l_int|5
comma
DECL|enumerator|CPU_NR_5
id|CPU_NR_5
op_assign
l_int|6
comma
DECL|enumerator|CPU_NR_6
id|CPU_NR_6
op_assign
l_int|7
comma
DECL|enumerator|CPU_NR_7
id|CPU_NR_7
op_assign
l_int|8
comma
DECL|enumerator|CPU_NR_8
id|CPU_NR_8
op_assign
l_int|9
comma
DECL|enumerator|CPU_NR_9
id|CPU_NR_9
op_assign
l_int|10
comma
DECL|enumerator|CPU_NR_10
id|CPU_NR_10
op_assign
l_int|11
comma
DECL|enumerator|CPU_NR_11
id|CPU_NR_11
op_assign
l_int|12
comma
DECL|enumerator|CPU_NR_12
id|CPU_NR_12
op_assign
l_int|13
comma
DECL|enumerator|CPU_NR_13
id|CPU_NR_13
op_assign
l_int|14
comma
DECL|enumerator|CPU_NR_14
id|CPU_NR_14
op_assign
l_int|15
comma
DECL|enumerator|CPU_NR_15
id|CPU_NR_15
op_assign
l_int|16
comma
DECL|enumerator|CPU_NR_16
id|CPU_NR_16
op_assign
l_int|17
comma
DECL|enumerator|CPU_NR_17
id|CPU_NR_17
op_assign
l_int|18
comma
DECL|enumerator|CPU_NR_18
id|CPU_NR_18
op_assign
l_int|19
comma
DECL|enumerator|CPU_NR_19
id|CPU_NR_19
op_assign
l_int|20
comma
DECL|enumerator|CPU_NR_20
id|CPU_NR_20
op_assign
l_int|21
comma
DECL|enumerator|CPU_NR_21
id|CPU_NR_21
op_assign
l_int|22
comma
DECL|enumerator|CPU_NR_22
id|CPU_NR_22
op_assign
l_int|23
comma
DECL|enumerator|CPU_NR_23
id|CPU_NR_23
op_assign
l_int|24
comma
DECL|enumerator|CPU_NR_24
id|CPU_NR_24
op_assign
l_int|25
comma
DECL|enumerator|CPU_NR_25
id|CPU_NR_25
op_assign
l_int|26
comma
DECL|enumerator|CPU_NR_26
id|CPU_NR_26
op_assign
l_int|27
comma
DECL|enumerator|CPU_NR_27
id|CPU_NR_27
op_assign
l_int|28
comma
DECL|enumerator|CPU_NR_28
id|CPU_NR_28
op_assign
l_int|29
comma
DECL|enumerator|CPU_NR_29
id|CPU_NR_29
op_assign
l_int|30
comma
DECL|enumerator|CPU_NR_30
id|CPU_NR_30
op_assign
l_int|31
comma
DECL|enumerator|CPU_NR_31
id|CPU_NR_31
op_assign
l_int|32
comma
)brace
suffix:semicolon
multiline_comment|/* /proc/sys/cpu/{0,1,...,(NR_CPUS-1)} */
r_enum
(brace
DECL|enumerator|CPU_NR_FREQ_MAX
id|CPU_NR_FREQ_MAX
op_assign
l_int|1
comma
DECL|enumerator|CPU_NR_FREQ_MIN
id|CPU_NR_FREQ_MIN
op_assign
l_int|2
comma
DECL|enumerator|CPU_NR_FREQ
id|CPU_NR_FREQ
op_assign
l_int|3
comma
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_CPU_FREQ_24_API */
multiline_comment|/*********************************************************************&n; *                       CPUFREQ DEFAULT GOVERNOR                    *&n; *********************************************************************/
macro_line|#ifdef CONFIG_CPU_FREQ_DEFAULT_GOV_PERFORMANCE
r_extern
r_struct
id|cpufreq_governor
id|cpufreq_gov_performance
suffix:semicolon
DECL|macro|CPUFREQ_DEFAULT_GOVERNOR
mdefine_line|#define CPUFREQ_DEFAULT_GOVERNOR&t;&amp;cpufreq_gov_performance
macro_line|#elif defined(CONFIG_CPU_FREQ_DEFAULT_GOV_USERSPACE)
r_extern
r_struct
id|cpufreq_governor
id|cpufreq_gov_userspace
suffix:semicolon
DECL|macro|CPUFREQ_DEFAULT_GOVERNOR
mdefine_line|#define CPUFREQ_DEFAULT_GOVERNOR&t;&amp;cpufreq_gov_userspace
macro_line|#endif
multiline_comment|/*********************************************************************&n; *                     FREQUENCY TABLE HELPERS                       *&n; *********************************************************************/
DECL|macro|CPUFREQ_ENTRY_INVALID
mdefine_line|#define CPUFREQ_ENTRY_INVALID ~0
DECL|macro|CPUFREQ_TABLE_END
mdefine_line|#define CPUFREQ_TABLE_END     ~1
DECL|struct|cpufreq_frequency_table
r_struct
id|cpufreq_frequency_table
(brace
DECL|member|index
r_int
r_int
id|index
suffix:semicolon
multiline_comment|/* any */
DECL|member|frequency
r_int
r_int
id|frequency
suffix:semicolon
multiline_comment|/* kHz - doesn&squot;t need to be in ascending&n;&t;&t;&t;&t;    * order */
)brace
suffix:semicolon
r_int
id|cpufreq_frequency_table_cpuinfo
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
comma
r_struct
id|cpufreq_frequency_table
op_star
id|table
)paren
suffix:semicolon
r_int
id|cpufreq_frequency_table_verify
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
comma
r_struct
id|cpufreq_frequency_table
op_star
id|table
)paren
suffix:semicolon
r_int
id|cpufreq_frequency_table_target
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
comma
r_struct
id|cpufreq_frequency_table
op_star
id|table
comma
r_int
r_int
id|target_freq
comma
r_int
r_int
id|relation
comma
r_int
r_int
op_star
id|index
)paren
suffix:semicolon
multiline_comment|/* the following 3 funtions are for cpufreq core use only */
r_struct
id|cpufreq_frequency_table
op_star
id|cpufreq_frequency_get_table
c_func
(paren
r_int
r_int
id|cpu
)paren
suffix:semicolon
r_struct
id|cpufreq_policy
op_star
id|cpufreq_cpu_get
c_func
(paren
r_int
r_int
id|cpu
)paren
suffix:semicolon
r_void
id|cpufreq_cpu_put
(paren
r_struct
id|cpufreq_policy
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/* the following are really really optional */
r_extern
r_struct
id|freq_attr
id|cpufreq_freq_attr_scaling_available_freqs
suffix:semicolon
r_void
id|cpufreq_frequency_table_get_attr
c_func
(paren
r_struct
id|cpufreq_frequency_table
op_star
id|table
comma
r_int
r_int
id|cpu
)paren
suffix:semicolon
r_void
id|cpufreq_frequency_table_put_attr
c_func
(paren
r_int
r_int
id|cpu
)paren
suffix:semicolon
multiline_comment|/*********************************************************************&n; *                     UNIFIED DEBUG HELPERS                         *&n; *********************************************************************/
DECL|macro|CPUFREQ_DEBUG_CORE
mdefine_line|#define CPUFREQ_DEBUG_CORE&t;1
DECL|macro|CPUFREQ_DEBUG_DRIVER
mdefine_line|#define CPUFREQ_DEBUG_DRIVER&t;2
DECL|macro|CPUFREQ_DEBUG_GOVERNOR
mdefine_line|#define CPUFREQ_DEBUG_GOVERNOR&t;4
macro_line|#ifdef CONFIG_CPU_FREQ_DEBUG
r_extern
r_void
id|cpufreq_debug_printk
c_func
(paren
r_int
r_int
id|type
comma
r_const
r_char
op_star
id|prefix
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
macro_line|#else
DECL|macro|cpufreq_debug_printk
mdefine_line|#define cpufreq_debug_printk(msg...) do { } while(0)
macro_line|#endif /* CONFIG_CPU_FREQ_DEBUG */
macro_line|#endif /* _LINUX_CPUFREQ_H */
eof
