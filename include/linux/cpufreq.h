multiline_comment|/*&n; *  linux/include/linux/cpufreq.h&n; *&n; *  Copyright (C) 2001 Russell King&n; *            (C) 2002 - 2003 Dominik Brodowski &lt;linux@brodo.de&gt;&n; *            &n; *&n; * $Id: cpufreq.h,v 1.36 2003/01/20 17:31:48 db Exp $&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef _LINUX_CPUFREQ_H
DECL|macro|_LINUX_CPUFREQ_H
mdefine_line|#define _LINUX_CPUFREQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/device.h&gt;
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
mdefine_line|#define CPUFREQ_TRANSITION_NOTIFIER     (0)
DECL|macro|CPUFREQ_POLICY_NOTIFIER
mdefine_line|#define CPUFREQ_POLICY_NOTIFIER         (1)
DECL|macro|CPUFREQ_ALL_CPUS
mdefine_line|#define CPUFREQ_ALL_CPUS        ((NR_CPUS))
multiline_comment|/********************** cpufreq policy notifiers *********************/
DECL|macro|CPUFREQ_POLICY_POWERSAVE
mdefine_line|#define CPUFREQ_POLICY_POWERSAVE        (1)
DECL|macro|CPUFREQ_POLICY_PERFORMANCE
mdefine_line|#define CPUFREQ_POLICY_PERFORMANCE      (2)
DECL|macro|CPUFREQ_POLICY_GOVERNOR
mdefine_line|#define CPUFREQ_POLICY_GOVERNOR         (3)
multiline_comment|/* Frequency values here are CPU kHz so that hardware which doesn&squot;t run &n; * with some frequencies can complain without having to guess what per &n; * cent / per mille means. &n; * Maximum transition latency is in microseconds - if it&squot;s unknown,&n; * CPUFREQ_ETERNAL shall be used.&n; */
r_struct
id|cpufreq_governor
suffix:semicolon
DECL|macro|CPUFREQ_ETERNAL
mdefine_line|#define CPUFREQ_ETERNAL (-1)
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
)brace
suffix:semicolon
DECL|struct|cpufreq_policy
r_struct
id|cpufreq_policy
(brace
DECL|member|cpu
r_int
r_int
id|cpu
suffix:semicolon
multiline_comment|/* cpu nr or CPUFREQ_ALL_CPUS */
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
DECL|member|cpuinfo
r_struct
id|cpufreq_cpuinfo
id|cpuinfo
suffix:semicolon
multiline_comment|/* see above */
DECL|member|intf
r_struct
id|intf_data
id|intf
suffix:semicolon
multiline_comment|/* interface data */
)brace
suffix:semicolon
DECL|macro|CPUFREQ_ADJUST
mdefine_line|#define CPUFREQ_ADJUST          (0)
DECL|macro|CPUFREQ_INCOMPATIBLE
mdefine_line|#define CPUFREQ_INCOMPATIBLE    (1)
DECL|macro|CPUFREQ_NOTIFY
mdefine_line|#define CPUFREQ_NOTIFY          (2)
multiline_comment|/******************** cpufreq transition notifiers *******************/
DECL|macro|CPUFREQ_PRECHANGE
mdefine_line|#define CPUFREQ_PRECHANGE&t;(0)
DECL|macro|CPUFREQ_POSTCHANGE
mdefine_line|#define CPUFREQ_POSTCHANGE&t;(1)
DECL|struct|cpufreq_freqs
r_struct
id|cpufreq_freqs
(brace
DECL|member|cpu
r_int
r_int
id|cpu
suffix:semicolon
multiline_comment|/* cpu nr or CPUFREQ_ALL_CPUS */
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
)brace
suffix:semicolon
multiline_comment|/**&n; * cpufreq_scale - &quot;old * mult / div&quot; calculation for large values (32-bit-arch safe)&n; * @old:   old value&n; * @div:   divisor&n; * @mult:  multiplier&n; *&n; * Needed for loops_per_jiffy and similar calculations.  We do it &n; * this way to avoid math overflow on 32-bit machines.  This will&n; * become architecture dependent once high-resolution-timer is&n; * merged (or any other thing that introduces sc_math.h).&n; *&n; *    new = old * mult / div&n; */
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
r_int
r_int
id|val
comma
id|carry
suffix:semicolon
id|mult
op_div_assign
l_int|100
suffix:semicolon
id|div
op_div_assign
l_int|100
suffix:semicolon
id|val
op_assign
(paren
id|old
op_div
id|div
)paren
op_star
id|mult
suffix:semicolon
id|carry
op_assign
id|old
op_mod
id|div
suffix:semicolon
id|carry
op_assign
id|carry
op_star
id|mult
op_div
id|div
suffix:semicolon
r_return
id|carry
op_plus
id|val
suffix:semicolon
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
multiline_comment|/* pass a target to the cpufreq driver &n; * _l : (cpufreq_driver_sem is not held)&n; */
r_inline
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
r_inline
r_int
id|cpufreq_driver_target_l
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
id|cpufreq_governor_l
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
DECL|struct|cpufreq_driver
r_struct
id|cpufreq_driver
(brace
multiline_comment|/* needed by all drivers */
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
DECL|member|policy
r_struct
id|cpufreq_policy
op_star
id|policy
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|CPUFREQ_NAME_LEN
)braket
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
multiline_comment|/* optional, for the moment */
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
)brace
suffix:semicolon
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
multiline_comment|/* deprecated */
DECL|macro|cpufreq_register
mdefine_line|#define cpufreq_register(x)   cpufreq_register_driver(x)
DECL|macro|cpufreq_unregister
mdefine_line|#define cpufreq_unregister() cpufreq_unregister_driver(NULL)
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
macro_line|#ifdef CONFIG_PM
r_int
id|cpufreq_restore
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
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
macro_line|#if defined(CONFIG_CPU_FREQ_GOV_USERSPACE) || defined(CONFIG_CPU_FREQ_GOV_USERSPACE_MODULE)
multiline_comment|/*********************************************************************&n; *                      CPUFREQ USERSPACE GOVERNOR                   *&n; *********************************************************************/
r_extern
r_struct
id|cpufreq_governor
id|cpufreq_gov_userspace
suffix:semicolon
r_int
id|cpufreq_gov_userspace_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|cpufreq_setmax
c_func
(paren
r_int
r_int
id|cpu
)paren
suffix:semicolon
r_int
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
macro_line|#ifdef CONFIG_CPU_FREQ_24_API
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
macro_line|#endif /* CONFIG_CPU_FREQ_GOV_USERSPACE */
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
macro_line|#if defined(CONFIG_CPU_FREQ_TABLE) || defined(CONFIG_CPU_FREQ_TABLE_MODULE)
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
id|cpufreq_frequency_table_setpolicy
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
op_star
id|index
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
macro_line|#endif /* CONFIG_CPU_FREQ_TABLE */
macro_line|#endif /* _LINUX_CPUFREQ_H */
eof
