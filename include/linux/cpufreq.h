multiline_comment|/*&n; *  linux/include/linux/cpufreq.h&n; *&n; *  Copyright (C) 2001 Russell King&n; *            (C) 2002 Dominik Brodowski &lt;linux@brodo.de&gt;&n; *            &n; *&n; * $Id: cpufreq.h,v 1.26 2002/09/21 09:05:29 db Exp $&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef _LINUX_CPUFREQ_H
DECL|macro|_LINUX_CPUFREQ_H
mdefine_line|#define _LINUX_CPUFREQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
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
multiline_comment|/* values here are CPU kHz so that hardware which doesn&squot;t run with some&n; * frequencies can complain without having to guess what per cent / per&n; * mille means. */
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
DECL|member|policy
r_int
r_int
id|policy
suffix:semicolon
multiline_comment|/* see above */
DECL|member|max_cpu_freq
r_int
r_int
id|max_cpu_freq
suffix:semicolon
multiline_comment|/* for information */
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
multiline_comment|/*********************************************************************&n; *                      DYNAMIC CPUFREQ INTERFACE                    *&n; *********************************************************************/
macro_line|#ifdef CONFIG_CPU_FREQ_DYNAMIC
multiline_comment|/* TBD */
macro_line|#endif /* CONFIG_CPU_FREQ_DYNAMIC */
multiline_comment|/*********************************************************************&n; *                      CPUFREQ DRIVER INTERFACE                     *&n; *********************************************************************/
DECL|typedef|cpufreq_policy_t
r_typedef
r_void
(paren
op_star
id|cpufreq_policy_t
)paren
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
suffix:semicolon
DECL|struct|cpufreq_driver
r_struct
id|cpufreq_driver
(brace
multiline_comment|/* needed by all drivers */
DECL|member|verify
id|cpufreq_policy_t
id|verify
suffix:semicolon
DECL|member|setpolicy
id|cpufreq_policy_t
id|setpolicy
suffix:semicolon
DECL|member|policy
r_struct
id|cpufreq_policy
op_star
id|policy
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_FREQ_DYNAMIC
multiline_comment|/* TBD */
macro_line|#endif
multiline_comment|/* 2.4. compatible API */
macro_line|#ifdef CONFIG_CPU_FREQ_24_API
DECL|member|cpu_min_freq
r_int
r_int
id|cpu_min_freq
suffix:semicolon
DECL|member|cpu_cur_freq
r_int
r_int
id|cpu_cur_freq
(braket
id|NR_CPUS
)braket
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
r_int
id|cpufreq_register
c_func
(paren
r_struct
id|cpufreq_driver
op_star
id|driver_data
)paren
suffix:semicolon
r_int
id|cpufreq_unregister
c_func
(paren
r_void
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
macro_line|#ifdef CONFIG_CPU_FREQ_26_API
macro_line|#ifdef CONFIG_PM
r_int
id|cpufreq_restore
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#endif /* _LINUX_CPUFREQ_H */
eof
