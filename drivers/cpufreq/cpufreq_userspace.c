multiline_comment|/*&n; *  linux/drivers/cpufreq/cpufreq_userspace.c&n; *&n; *  Copyright (C)  2001 Russell King&n; *            (C)  2002 - 2004 Dominik Brodowski &lt;linux@brodo.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sysfs.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|CTL_CPU_VARS_SPEED_MAX
mdefine_line|#define CTL_CPU_VARS_SPEED_MAX(cpunr) { &bslash;&n;                .ctl_name&t;= CPU_NR_FREQ_MAX, &bslash;&n;                .data&t;&t;= &amp;cpu_max_freq[cpunr], &bslash;&n;                .procname&t;= &quot;speed-max&quot;, &bslash;&n;                .maxlen&t;&t;= sizeof(cpu_max_freq[cpunr]),&bslash;&n;                .mode&t;&t;= 0444, &bslash;&n;                .proc_handler&t;= proc_dointvec, }
DECL|macro|CTL_CPU_VARS_SPEED_MIN
mdefine_line|#define CTL_CPU_VARS_SPEED_MIN(cpunr) { &bslash;&n;                .ctl_name&t;= CPU_NR_FREQ_MIN, &bslash;&n;                .data&t;&t;= &amp;cpu_min_freq[cpunr], &bslash;&n;                .procname&t;= &quot;speed-min&quot;, &bslash;&n;                .maxlen&t;&t;= sizeof(cpu_min_freq[cpunr]),&bslash;&n;                .mode&t;&t;= 0444, &bslash;&n;                .proc_handler&t;= proc_dointvec, }
DECL|macro|CTL_CPU_VARS_SPEED
mdefine_line|#define CTL_CPU_VARS_SPEED(cpunr) { &bslash;&n;                .ctl_name&t;= CPU_NR_FREQ, &bslash;&n;                .procname&t;= &quot;speed&quot;, &bslash;&n;                .mode&t;&t;= 0644, &bslash;&n;                .proc_handler&t;= cpufreq_procctl, &bslash;&n;                .strategy&t;= cpufreq_sysctl, &bslash;&n;                .extra1&t;&t;= (void*) (cpunr), }
DECL|macro|CTL_TABLE_CPU_VARS
mdefine_line|#define CTL_TABLE_CPU_VARS(cpunr) static ctl_table ctl_cpu_vars_##cpunr[] = {&bslash;&n;                CTL_CPU_VARS_SPEED_MAX(cpunr), &bslash;&n;                CTL_CPU_VARS_SPEED_MIN(cpunr), &bslash;&n;                CTL_CPU_VARS_SPEED(cpunr),  &bslash;&n;                { .ctl_name = 0, }, }
multiline_comment|/* the ctl_table entry for each CPU */
DECL|macro|CPU_ENUM
mdefine_line|#define CPU_ENUM(s) { &bslash;&n;                .ctl_name&t;= (CPU_NR + s), &bslash;&n;                .procname&t;= #s, &bslash;&n;                .mode&t;&t;= 0555, &bslash;&n;                .child&t;&t;= ctl_cpu_vars_##s }
multiline_comment|/**&n; * A few values needed by the userspace governor&n; */
DECL|variable|cpu_max_freq
r_static
r_int
r_int
id|cpu_max_freq
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|cpu_min_freq
r_static
r_int
r_int
id|cpu_min_freq
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|cpu_cur_freq
r_static
r_int
r_int
id|cpu_cur_freq
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|cpu_is_managed
r_static
r_int
r_int
id|cpu_is_managed
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|current_policy
r_static
r_struct
id|cpufreq_policy
id|current_policy
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_static
id|DECLARE_MUTEX
(paren
id|userspace_sem
)paren
suffix:semicolon
multiline_comment|/* keep track of frequency transitions */
r_static
r_int
DECL|function|userspace_cpufreq_notifier
id|userspace_cpufreq_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
comma
r_int
r_int
id|val
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|cpufreq_freqs
op_star
id|freq
op_assign
id|data
suffix:semicolon
multiline_comment|/* Don&squot;t update cur_freq if CPU is managed and we&squot;re&n;&t; * waking up: else we won&squot;t remember what frequency &n;&t; * we need to set the CPU to.&n;&t; */
r_if
c_cond
(paren
id|cpu_is_managed
(braket
id|freq-&gt;cpu
)braket
op_logical_and
(paren
id|val
op_eq
id|CPUFREQ_RESUMECHANGE
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|cpu_cur_freq
(braket
id|freq-&gt;cpu
)braket
op_assign
id|freq
op_member_access_from_pointer
r_new
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|userspace_cpufreq_notifier_block
r_static
r_struct
id|notifier_block
id|userspace_cpufreq_notifier_block
op_assign
(brace
dot
id|notifier_call
op_assign
id|userspace_cpufreq_notifier
)brace
suffix:semicolon
multiline_comment|/** &n; * cpufreq_set - set the CPU frequency&n; * @freq: target frequency in kHz&n; * @cpu: CPU for which the frequency is to be set&n; *&n; * Sets the CPU frequency to freq.&n; */
DECL|function|cpufreq_set
r_int
id|cpufreq_set
c_func
(paren
r_int
r_int
id|freq
comma
r_int
r_int
id|cpu
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|down
c_func
(paren
op_amp
id|userspace_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu_is_managed
(braket
id|cpu
)braket
)paren
r_goto
id|err
suffix:semicolon
r_if
c_cond
(paren
id|freq
OL
id|cpu_min_freq
(braket
id|cpu
)braket
)paren
id|freq
op_assign
id|cpu_min_freq
(braket
id|cpu
)braket
suffix:semicolon
r_if
c_cond
(paren
id|freq
OG
id|cpu_max_freq
(braket
id|cpu
)braket
)paren
id|freq
op_assign
id|cpu_max_freq
(braket
id|cpu
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * We&squot;re safe from concurrent calls to -&gt;target() here&n;&t; * as we hold the userspace_sem lock. If we were calling&n;&t; * cpufreq_driver_target, a deadlock situation might occur:&n;&t; * A: cpufreq_set (lock userspace_sem) -&gt; cpufreq_driver_target(lock policy-&gt;lock)&n;&t; * B: cpufreq_set_policy(lock policy-&gt;lock) -&gt; __cpufreq_governor -&gt; cpufreq_governor_userspace (lock userspace_sem)&n;&t; */
id|ret
op_assign
id|__cpufreq_driver_target
c_func
(paren
op_amp
id|current_policy
(braket
id|cpu
)braket
comma
id|freq
comma
id|CPUFREQ_RELATION_L
)paren
suffix:semicolon
id|err
suffix:colon
id|up
c_func
(paren
op_amp
id|userspace_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|cpufreq_set
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|cpufreq_set
)paren
suffix:semicolon
multiline_comment|/** &n; * cpufreq_setmax - set the CPU to the maximum frequency&n; * @cpu - affected cpu;&n; *&n; * Sets the CPU frequency to the maximum frequency supported by&n; * this CPU.&n; */
DECL|function|cpufreq_setmax
r_int
id|cpufreq_setmax
c_func
(paren
r_int
r_int
id|cpu
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cpu_is_managed
(braket
id|cpu
)braket
op_logical_or
op_logical_neg
id|cpu_online
c_func
(paren
id|cpu
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|cpufreq_set
c_func
(paren
id|cpu_max_freq
(braket
id|cpu
)braket
comma
id|cpu
)paren
suffix:semicolon
)brace
DECL|variable|cpufreq_setmax
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|cpufreq_setmax
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_FREQ_24_API
macro_line|#warning The /proc/sys/cpu/ and sysctl interface to cpufreq will be removed from the 2.6. kernel series soon after 2005-01-01
DECL|variable|warning_print
r_static
r_int
r_int
id|warning_print
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*********************** cpufreq_sysctl interface ********************/
r_static
r_int
DECL|function|cpufreq_procctl
id|cpufreq_procctl
c_func
(paren
id|ctl_table
op_star
id|ctl
comma
r_int
id|write
comma
r_struct
id|file
op_star
id|filp
comma
r_void
id|__user
op_star
id|buffer
comma
r_int
op_star
id|lenp
)paren
(brace
r_char
id|buf
(braket
l_int|16
)braket
comma
op_star
id|p
suffix:semicolon
r_int
id|cpu
op_assign
(paren
r_int
)paren
id|ctl-&gt;extra1
suffix:semicolon
r_int
r_int
id|len
comma
id|left
op_assign
op_star
id|lenp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|left
op_logical_or
(paren
id|filp-&gt;f_pos
op_logical_and
op_logical_neg
id|write
)paren
op_logical_or
op_logical_neg
id|cpu_online
c_func
(paren
id|cpu
)paren
)paren
(brace
op_star
id|lenp
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|warning_print
)paren
(brace
id|warning_print
op_increment
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Access to /proc/sys/cpu/ is deprecated and &quot;
l_string|&quot;will be removed from (new) 2.6. kernels soon &quot;
l_string|&quot;after 2005-01-01&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|write
)paren
(brace
r_int
r_int
id|freq
suffix:semicolon
id|len
op_assign
id|left
suffix:semicolon
r_if
c_cond
(paren
id|left
OG
r_sizeof
(paren
id|buf
)paren
)paren
id|left
op_assign
r_sizeof
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|buf
comma
id|buffer
comma
id|left
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|buf
(braket
r_sizeof
(paren
id|buf
)paren
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|freq
op_assign
id|simple_strtoul
c_func
(paren
id|buf
comma
op_amp
id|p
comma
l_int|0
)paren
suffix:semicolon
id|cpufreq_set
c_func
(paren
id|freq
comma
id|cpu
)paren
suffix:semicolon
)brace
r_else
(brace
id|len
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|cpufreq_get
c_func
(paren
id|cpu
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|left
)paren
id|len
op_assign
id|left
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buffer
comma
id|buf
comma
id|len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
op_star
id|lenp
op_assign
id|len
suffix:semicolon
id|filp-&gt;f_pos
op_add_assign
id|len
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|cpufreq_sysctl
id|cpufreq_sysctl
c_func
(paren
id|ctl_table
op_star
id|table
comma
r_int
id|__user
op_star
id|name
comma
r_int
id|nlen
comma
r_void
id|__user
op_star
id|oldval
comma
r_int
id|__user
op_star
id|oldlenp
comma
r_void
id|__user
op_star
id|newval
comma
r_int
id|newlen
comma
r_void
op_star
op_star
id|context
)paren
(brace
r_int
id|cpu
op_assign
(paren
r_int
)paren
id|table-&gt;extra1
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
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|warning_print
)paren
(brace
id|warning_print
op_increment
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Access to /proc/sys/cpu/ is deprecated and &quot;
l_string|&quot;will be removed from (new) 2.6. kernels soon &quot;
l_string|&quot;after 2005-01-01&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|oldval
op_logical_and
id|oldlenp
)paren
(brace
r_int
id|oldlen
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|oldlen
comma
id|oldlenp
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|oldlen
op_ne
r_sizeof
(paren
r_int
r_int
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|cpufreq_get
c_func
(paren
id|cpu
)paren
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|oldval
)paren
op_logical_or
id|put_user
c_func
(paren
r_sizeof
(paren
r_int
r_int
)paren
comma
id|oldlenp
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|newval
op_logical_and
id|newlen
)paren
(brace
r_int
r_int
id|freq
suffix:semicolon
r_if
c_cond
(paren
id|newlen
op_ne
r_sizeof
(paren
r_int
r_int
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|freq
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|newval
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|cpufreq_set
c_func
(paren
id|freq
comma
id|cpu
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* ctl_table ctl_cpu_vars_{0,1,...,(NR_CPUS-1)} */
multiline_comment|/* due to NR_CPUS tweaking, a lot of if/endifs are required, sorry */
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#if NR_CPUS &gt; 1
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|1
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 2
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|2
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 3
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|3
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 4
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|4
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 5
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|5
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 6
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|6
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 7
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|7
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 8
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|8
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 9
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|9
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 10
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|10
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 11
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|11
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 12
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|12
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 13
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|13
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 14
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|14
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 15
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|15
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 16
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|16
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 17
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|17
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 18
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|18
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 19
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|19
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 20
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|20
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 21
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|21
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 22
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|22
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 23
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|23
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 24
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|24
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 25
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|25
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 26
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|26
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 27
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|27
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 28
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|28
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 29
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|29
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 30
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|30
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 31
id|CTL_TABLE_CPU_VARS
c_func
(paren
l_int|31
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if NR_CPUS &gt; 32
macro_line|#error please extend CPU enumeration
macro_line|#endif
multiline_comment|/* due to NR_CPUS tweaking, a lot of if/endifs are required, sorry */
DECL|variable|ctl_cpu_table
r_static
id|ctl_table
id|ctl_cpu_table
(braket
id|NR_CPUS
op_plus
l_int|1
)braket
op_assign
(brace
id|CPU_ENUM
c_func
(paren
l_int|0
)paren
comma
macro_line|#if NR_CPUS &gt; 1
id|CPU_ENUM
c_func
(paren
l_int|1
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 2
id|CPU_ENUM
c_func
(paren
l_int|2
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 3
id|CPU_ENUM
c_func
(paren
l_int|3
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 4
id|CPU_ENUM
c_func
(paren
l_int|4
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 5
id|CPU_ENUM
c_func
(paren
l_int|5
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 6
id|CPU_ENUM
c_func
(paren
l_int|6
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 7
id|CPU_ENUM
c_func
(paren
l_int|7
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 8
id|CPU_ENUM
c_func
(paren
l_int|8
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 9
id|CPU_ENUM
c_func
(paren
l_int|9
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 10
id|CPU_ENUM
c_func
(paren
l_int|10
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 11
id|CPU_ENUM
c_func
(paren
l_int|11
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 12
id|CPU_ENUM
c_func
(paren
l_int|12
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 13
id|CPU_ENUM
c_func
(paren
l_int|13
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 14
id|CPU_ENUM
c_func
(paren
l_int|14
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 15
id|CPU_ENUM
c_func
(paren
l_int|15
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 16
id|CPU_ENUM
c_func
(paren
l_int|16
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 17
id|CPU_ENUM
c_func
(paren
l_int|17
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 18
id|CPU_ENUM
c_func
(paren
l_int|18
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 19
id|CPU_ENUM
c_func
(paren
l_int|19
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 20
id|CPU_ENUM
c_func
(paren
l_int|20
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 21
id|CPU_ENUM
c_func
(paren
l_int|21
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 22
id|CPU_ENUM
c_func
(paren
l_int|22
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 23
id|CPU_ENUM
c_func
(paren
l_int|23
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 24
id|CPU_ENUM
c_func
(paren
l_int|24
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 25
id|CPU_ENUM
c_func
(paren
l_int|25
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 26
id|CPU_ENUM
c_func
(paren
l_int|26
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 27
id|CPU_ENUM
c_func
(paren
l_int|27
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 28
id|CPU_ENUM
c_func
(paren
l_int|28
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 29
id|CPU_ENUM
c_func
(paren
l_int|29
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 30
id|CPU_ENUM
c_func
(paren
l_int|30
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 31
id|CPU_ENUM
c_func
(paren
l_int|31
)paren
comma
macro_line|#endif
macro_line|#if NR_CPUS &gt; 32
macro_line|#error please extend CPU enumeration
macro_line|#endif
(brace
dot
id|ctl_name
op_assign
l_int|0
comma
)brace
)brace
suffix:semicolon
DECL|variable|ctl_cpu
r_static
id|ctl_table
id|ctl_cpu
(braket
l_int|2
)braket
op_assign
(brace
(brace
dot
id|ctl_name
op_assign
id|CTL_CPU
comma
dot
id|procname
op_assign
l_string|&quot;cpu&quot;
comma
dot
id|mode
op_assign
l_int|0555
comma
dot
id|child
op_assign
id|ctl_cpu_table
comma
)brace
comma
(brace
dot
id|ctl_name
op_assign
l_int|0
comma
)brace
)brace
suffix:semicolon
DECL|variable|cpufreq_sysctl_table
r_struct
id|ctl_table_header
op_star
id|cpufreq_sysctl_table
suffix:semicolon
DECL|function|cpufreq_sysctl_init
r_static
r_inline
r_void
id|cpufreq_sysctl_init
c_func
(paren
r_void
)paren
(brace
id|cpufreq_sysctl_table
op_assign
id|register_sysctl_table
c_func
(paren
id|ctl_cpu
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|cpufreq_sysctl_exit
r_static
r_inline
r_void
id|cpufreq_sysctl_exit
c_func
(paren
r_void
)paren
(brace
id|unregister_sysctl_table
c_func
(paren
id|cpufreq_sysctl_table
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|cpufreq_sysctl_init
mdefine_line|#define cpufreq_sysctl_init() do {} while(0)
DECL|macro|cpufreq_sysctl_exit
mdefine_line|#define cpufreq_sysctl_exit() do {} while(0)
macro_line|#endif /* CONFIG_CPU_FREQ_24API */
multiline_comment|/************************** sysfs interface ************************/
DECL|function|show_speed
r_static
id|ssize_t
id|show_speed
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
id|cpu_cur_freq
(braket
id|policy-&gt;cpu
)braket
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|store_speed
id|store_speed
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
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
id|freq
op_assign
l_int|0
suffix:semicolon
r_int
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
id|freq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|cpufreq_set
c_func
(paren
id|freq
comma
id|policy-&gt;cpu
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|variable|freq_attr_scaling_setspeed
r_static
r_struct
id|freq_attr
id|freq_attr_scaling_setspeed
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;scaling_setspeed&quot;
comma
dot
id|mode
op_assign
l_int|0644
)brace
comma
dot
id|show
op_assign
id|show_speed
comma
dot
id|store
op_assign
id|store_speed
comma
)brace
suffix:semicolon
DECL|function|cpufreq_governor_userspace
r_static
r_int
id|cpufreq_governor_userspace
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
id|try_module_get
c_func
(paren
id|THIS_MODULE
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|policy-&gt;cur
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|userspace_sem
)paren
suffix:semicolon
id|cpu_is_managed
(braket
id|cpu
)braket
op_assign
l_int|1
suffix:semicolon
id|cpu_min_freq
(braket
id|cpu
)braket
op_assign
id|policy-&gt;min
suffix:semicolon
id|cpu_max_freq
(braket
id|cpu
)braket
op_assign
id|policy-&gt;max
suffix:semicolon
id|cpu_cur_freq
(braket
id|cpu
)braket
op_assign
id|policy-&gt;cur
suffix:semicolon
id|sysfs_create_file
(paren
op_amp
id|policy-&gt;kobj
comma
op_amp
id|freq_attr_scaling_setspeed.attr
)paren
suffix:semicolon
id|memcpy
(paren
op_amp
id|current_policy
(braket
id|cpu
)braket
comma
id|policy
comma
r_sizeof
(paren
r_struct
id|cpufreq_policy
)paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|userspace_sem
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
id|userspace_sem
)paren
suffix:semicolon
id|cpu_is_managed
(braket
id|cpu
)braket
op_assign
l_int|0
suffix:semicolon
id|cpu_min_freq
(braket
id|cpu
)braket
op_assign
l_int|0
suffix:semicolon
id|cpu_max_freq
(braket
id|cpu
)braket
op_assign
l_int|0
suffix:semicolon
id|sysfs_remove_file
(paren
op_amp
id|policy-&gt;kobj
comma
op_amp
id|freq_attr_scaling_setspeed.attr
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|userspace_sem
)paren
suffix:semicolon
id|module_put
c_func
(paren
id|THIS_MODULE
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
id|userspace_sem
)paren
suffix:semicolon
id|cpu_min_freq
(braket
id|cpu
)braket
op_assign
id|policy-&gt;min
suffix:semicolon
id|cpu_max_freq
(braket
id|cpu
)braket
op_assign
id|policy-&gt;max
suffix:semicolon
r_if
c_cond
(paren
id|policy-&gt;max
OL
id|cpu_cur_freq
(braket
id|cpu
)braket
)paren
id|__cpufreq_driver_target
c_func
(paren
op_amp
id|current_policy
(braket
id|cpu
)braket
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
id|cpu_cur_freq
(braket
id|cpu
)braket
)paren
id|__cpufreq_driver_target
c_func
(paren
op_amp
id|current_policy
(braket
id|cpu
)braket
comma
id|policy-&gt;min
comma
id|CPUFREQ_RELATION_L
)paren
suffix:semicolon
r_else
id|__cpufreq_driver_target
c_func
(paren
op_amp
id|current_policy
(braket
id|cpu
)braket
comma
id|cpu_cur_freq
(braket
id|cpu
)braket
comma
id|CPUFREQ_RELATION_L
)paren
suffix:semicolon
id|memcpy
(paren
op_amp
id|current_policy
(braket
id|cpu
)braket
comma
id|policy
comma
r_sizeof
(paren
r_struct
id|cpufreq_policy
)paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|userspace_sem
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cpufreq_gov_userspace
r_struct
id|cpufreq_governor
id|cpufreq_gov_userspace
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;userspace&quot;
comma
dot
id|governor
op_assign
id|cpufreq_governor_userspace
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|variable|cpufreq_gov_userspace
id|EXPORT_SYMBOL
c_func
(paren
id|cpufreq_gov_userspace
)paren
suffix:semicolon
DECL|function|cpufreq_gov_userspace_init
r_static
r_int
id|__init
id|cpufreq_gov_userspace_init
c_func
(paren
r_void
)paren
(brace
id|cpufreq_sysctl_init
c_func
(paren
)paren
suffix:semicolon
id|cpufreq_register_notifier
c_func
(paren
op_amp
id|userspace_cpufreq_notifier_block
comma
id|CPUFREQ_TRANSITION_NOTIFIER
)paren
suffix:semicolon
r_return
id|cpufreq_register_governor
c_func
(paren
op_amp
id|cpufreq_gov_userspace
)paren
suffix:semicolon
)brace
DECL|function|cpufreq_gov_userspace_exit
r_static
r_void
id|__exit
id|cpufreq_gov_userspace_exit
c_func
(paren
r_void
)paren
(brace
id|cpufreq_unregister_governor
c_func
(paren
op_amp
id|cpufreq_gov_userspace
)paren
suffix:semicolon
id|cpufreq_unregister_notifier
c_func
(paren
op_amp
id|userspace_cpufreq_notifier_block
comma
id|CPUFREQ_TRANSITION_NOTIFIER
)paren
suffix:semicolon
id|cpufreq_sysctl_exit
c_func
(paren
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
(paren
l_string|&quot;Dominik Brodowski &lt;linux@brodo.de&gt;, Russell King &lt;rmk@arm.linux.org.uk&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
(paren
l_string|&quot;CPUfreq policy governor &squot;userspace&squot;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|cpufreq_gov_userspace_init
id|fs_initcall
c_func
(paren
id|cpufreq_gov_userspace_init
)paren
suffix:semicolon
DECL|variable|cpufreq_gov_userspace_exit
id|module_exit
c_func
(paren
id|cpufreq_gov_userspace_exit
)paren
suffix:semicolon
eof
