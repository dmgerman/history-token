multiline_comment|/*&n; *  linux/kernel/cpufreq.c&n; *&n; *  Copyright (C) 2001 Russell King&n; *            (C) 2002 Dominik Brodowski &lt;linux@brodo.de&gt;&n; *&n; *  $Id: cpufreq.c,v 1.43 2002/09/21 09:05:29 db Exp $&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#ifdef CONFIG_CPU_FREQ_26_API
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#endif
multiline_comment|/**&n; * The &quot;cpufreq driver&quot; - the arch- or hardware-dependend low&n; * level driver of CPUFreq support, and its locking mutex. &n; * cpu_max_freq is in kHz.&n; */
DECL|variable|cpufreq_driver
r_static
r_struct
id|cpufreq_driver
op_star
id|cpufreq_driver
suffix:semicolon
r_static
id|DECLARE_MUTEX
(paren
id|cpufreq_driver_sem
)paren
suffix:semicolon
multiline_comment|/**&n; * Two notifier lists: the &quot;policy&quot; list is involved in the &n; * validation process for a new CPU frequency policy; the &n; * &quot;transition&quot; list for kernel code that needs to handle&n; * changes to devices when the CPU clock speed changes.&n; * The mutex locks both lists. If both cpufreq_driver_sem&n; * and cpufreq_notifier_sem need to be hold, get cpufreq_driver_sem&n; * first.&n; */
DECL|variable|cpufreq_policy_notifier_list
r_static
r_struct
id|notifier_block
op_star
id|cpufreq_policy_notifier_list
suffix:semicolon
DECL|variable|cpufreq_transition_notifier_list
r_static
r_struct
id|notifier_block
op_star
id|cpufreq_transition_notifier_list
suffix:semicolon
r_static
id|DECLARE_MUTEX
(paren
id|cpufreq_notifier_sem
)paren
suffix:semicolon
multiline_comment|/**&n; * The cpufreq default policy. Can be set by a &quot;cpufreq=...&quot; command&n; * line option.&n; */
DECL|variable|default_policy
r_static
r_struct
id|cpufreq_policy
id|default_policy
op_assign
(brace
dot
id|cpu
op_assign
id|CPUFREQ_ALL_CPUS
comma
dot
id|min
op_assign
l_int|0
comma
dot
id|max
op_assign
l_int|0
comma
dot
id|policy
op_assign
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/*********************************************************************&n; *                              2.6. API                             *&n; *********************************************************************/
multiline_comment|/**&n; * cpufreq_parse_policy - parse a policy string&n; * @input_string: the string to parse.&n; * @policy: the policy written inside input_string&n; *&n; * This function parses a &quot;policy string&quot; - something the user echo&squot;es into&n; * /proc/cpufreq or gives as boot parameter - into a struct cpufreq_policy.&n; * If there are invalid/missing entries, they are replaced with current&n; * cpufreq policy.&n; */
DECL|function|cpufreq_parse_policy
r_static
r_int
id|cpufreq_parse_policy
c_func
(paren
r_char
id|input_string
(braket
l_int|42
)braket
comma
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_int
r_int
id|min
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|max
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|cpu
op_assign
l_int|0
suffix:semicolon
r_char
id|policy_string
(braket
l_int|42
)braket
op_assign
(brace
l_char|&squot;&bslash;0&squot;
)brace
suffix:semicolon
r_struct
id|cpufreq_policy
id|current_policy
suffix:semicolon
r_int
r_int
id|result
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_int
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|policy
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|policy-&gt;min
op_assign
l_int|0
suffix:semicolon
id|policy-&gt;max
op_assign
l_int|0
suffix:semicolon
id|policy-&gt;policy
op_assign
l_int|0
suffix:semicolon
id|policy-&gt;cpu
op_assign
id|CPUFREQ_ALL_CPUS
suffix:semicolon
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|input_string
comma
l_string|&quot;%d:%d:%d:%s&quot;
comma
op_amp
id|cpu
comma
op_amp
id|min
comma
op_amp
id|max
comma
id|policy_string
)paren
op_eq
l_int|4
)paren
(brace
id|policy-&gt;min
op_assign
id|min
suffix:semicolon
id|policy-&gt;max
op_assign
id|max
suffix:semicolon
id|policy-&gt;cpu
op_assign
id|cpu
suffix:semicolon
id|result
op_assign
l_int|0
suffix:semicolon
r_goto
id|scan_policy
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|input_string
comma
l_string|&quot;%d%%%d%%%d%%%s&quot;
comma
op_amp
id|cpu
comma
op_amp
id|min
comma
op_amp
id|max
comma
id|policy_string
)paren
op_eq
l_int|4
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cpufreq_get_policy
c_func
(paren
op_amp
id|current_policy
comma
id|cpu
)paren
)paren
(brace
id|policy-&gt;min
op_assign
(paren
id|min
op_star
id|current_policy.max_cpu_freq
)paren
op_div
l_int|100
suffix:semicolon
id|policy-&gt;max
op_assign
(paren
id|max
op_star
id|current_policy.max_cpu_freq
)paren
op_div
l_int|100
suffix:semicolon
id|policy-&gt;cpu
op_assign
id|cpu
suffix:semicolon
id|result
op_assign
l_int|0
suffix:semicolon
r_goto
id|scan_policy
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|input_string
comma
l_string|&quot;%d:%d:%s&quot;
comma
op_amp
id|min
comma
op_amp
id|max
comma
id|policy_string
)paren
op_eq
l_int|3
)paren
(brace
id|policy-&gt;min
op_assign
id|min
suffix:semicolon
id|policy-&gt;max
op_assign
id|max
suffix:semicolon
id|result
op_assign
l_int|0
suffix:semicolon
r_goto
id|scan_policy
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|input_string
comma
l_string|&quot;%d%%%d%%%s&quot;
comma
op_amp
id|min
comma
op_amp
id|max
comma
id|policy_string
)paren
op_eq
l_int|3
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cpufreq_get_policy
c_func
(paren
op_amp
id|current_policy
comma
id|cpu
)paren
)paren
(brace
id|policy-&gt;min
op_assign
(paren
id|min
op_star
id|current_policy.max_cpu_freq
)paren
op_div
l_int|100
suffix:semicolon
id|policy-&gt;max
op_assign
(paren
id|max
op_star
id|current_policy.max_cpu_freq
)paren
op_div
l_int|100
suffix:semicolon
id|result
op_assign
l_int|0
suffix:semicolon
r_goto
id|scan_policy
suffix:semicolon
)brace
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
id|scan_policy
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
r_sizeof
(paren
id|policy_string
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|policy_string
(braket
id|i
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_break
suffix:semicolon
id|policy_string
(braket
id|i
)braket
op_assign
id|tolower
c_func
(paren
id|policy_string
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|policy_string
comma
l_string|&quot;powersave&quot;
comma
l_int|6
)paren
op_logical_or
op_logical_neg
id|strncmp
c_func
(paren
id|policy_string
comma
l_string|&quot;eco&quot;
comma
l_int|3
)paren
op_logical_or
op_logical_neg
id|strncmp
c_func
(paren
id|policy_string
comma
l_string|&quot;batter&quot;
comma
l_int|6
)paren
op_logical_or
op_logical_neg
id|strncmp
c_func
(paren
id|policy_string
comma
l_string|&quot;low&quot;
comma
l_int|3
)paren
)paren
(brace
id|result
op_assign
l_int|0
suffix:semicolon
id|policy-&gt;policy
op_assign
id|CPUFREQ_POLICY_POWERSAVE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|policy_string
comma
l_string|&quot;performance&quot;
comma
l_int|6
)paren
op_logical_or
op_logical_neg
id|strncmp
c_func
(paren
id|policy_string
comma
l_string|&quot;high&quot;
comma
l_int|4
)paren
op_logical_or
op_logical_neg
id|strncmp
c_func
(paren
id|policy_string
comma
l_string|&quot;full&quot;
comma
l_int|4
)paren
)paren
(brace
id|result
op_assign
l_int|0
suffix:semicolon
id|policy-&gt;policy
op_assign
id|CPUFREQ_POLICY_PERFORMANCE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|cpufreq_get_policy
c_func
(paren
op_amp
id|current_policy
comma
id|policy-&gt;cpu
)paren
)paren
(brace
id|policy-&gt;policy
op_assign
id|current_policy.policy
suffix:semicolon
)brace
r_else
(brace
id|policy-&gt;policy
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * cpufreq command line parameter.  Must be hard values (kHz)&n; *  cpufreq=1000000:2000000:PERFORMANCE   &n; * to set the default CPUFreq policy.&n; */
DECL|function|cpufreq_setup
r_static
r_int
id|__init
id|cpufreq_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|cpufreq_parse_policy
c_func
(paren
id|str
comma
op_amp
id|default_policy
)paren
suffix:semicolon
id|default_policy.cpu
op_assign
id|CPUFREQ_ALL_CPUS
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;cpufreq=&quot;
comma
id|cpufreq_setup
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_FREQ_26_API
macro_line|#ifdef CONFIG_PROC_FS
multiline_comment|/**&n; * cpufreq_proc_read - read /proc/cpufreq&n; *&n; * This function prints out the current cpufreq policy.&n; */
DECL|function|cpufreq_proc_read
r_static
r_int
id|cpufreq_proc_read
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_char
op_star
id|p
op_assign
id|page
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_struct
id|cpufreq_policy
id|policy
suffix:semicolon
r_int
r_int
id|min_pctg
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|max_pctg
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|off
op_ne
l_int|0
)paren
r_goto
id|end
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;          minimum CPU frequency  -  maximum CPU frequency  -  policy&bslash;n&quot;
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
(brace
r_if
c_cond
(paren
op_logical_neg
id|cpu_online
c_func
(paren
id|i
)paren
)paren
r_continue
suffix:semicolon
id|cpufreq_get_policy
c_func
(paren
op_amp
id|policy
comma
id|i
)paren
suffix:semicolon
id|min_pctg
op_assign
(paren
id|policy.min
op_star
l_int|100
)paren
op_div
id|policy.max_cpu_freq
suffix:semicolon
id|max_pctg
op_assign
(paren
id|policy.max
op_star
l_int|100
)paren
op_div
id|policy.max_cpu_freq
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;CPU%3d    %9d kHz (%3d %%)  -  %9d kHz (%3d %%)  -  &quot;
comma
id|i
comma
id|policy.min
comma
id|min_pctg
comma
id|policy.max
comma
id|max_pctg
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|policy.policy
)paren
(brace
r_case
id|CPUFREQ_POLICY_POWERSAVE
suffix:colon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;powersave&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPUFREQ_POLICY_PERFORMANCE
suffix:colon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;performance&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;INVALID&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|end
suffix:colon
id|len
op_assign
(paren
id|p
op_minus
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
id|off
op_plus
id|count
)paren
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
id|off
suffix:semicolon
id|len
op_sub_assign
id|off
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|count
)paren
id|len
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/**&n; * cpufreq_proc_write - handles writing into /proc/cpufreq&n; *&n; * This function calls the parsing script and then sets the policy&n; * accordingly.&n; */
DECL|function|cpufreq_proc_write
r_static
r_int
id|cpufreq_proc_write
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_char
id|proc_string
(braket
l_int|42
)braket
op_assign
(brace
l_char|&squot;&bslash;0&squot;
)brace
suffix:semicolon
r_struct
id|cpufreq_policy
id|policy
suffix:semicolon
r_if
c_cond
(paren
(paren
id|count
OG
r_sizeof
(paren
id|proc_string
)paren
op_minus
l_int|1
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|proc_string
comma
id|buffer
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|proc_string
(braket
id|count
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|result
op_assign
id|cpufreq_parse_policy
c_func
(paren
id|proc_string
comma
op_amp
id|policy
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|cpufreq_set_policy
c_func
(paren
op_amp
id|policy
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/**&n; * cpufreq_proc_init - add &quot;cpufreq&quot; to the /proc root directory&n; *&n; * This function adds &quot;cpufreq&quot; to the /proc root directory.&n; */
DECL|function|cpufreq_proc_init
r_static
r_int
r_int
id|cpufreq_proc_init
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|entry
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* are these acceptable values? */
id|entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;cpufreq&quot;
comma
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
comma
op_amp
id|proc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;unable to create /proc/cpufreq entry&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_else
(brace
id|entry-&gt;read_proc
op_assign
id|cpufreq_proc_read
suffix:semicolon
id|entry-&gt;write_proc
op_assign
id|cpufreq_proc_write
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * cpufreq_proc_exit - removes &quot;cpufreq&quot; from the /proc root directory.&n; *&n; * This function removes &quot;cpufreq&quot; from the /proc root directory.&n; */
DECL|function|cpufreq_proc_exit
r_static
r_void
id|cpufreq_proc_exit
(paren
r_void
)paren
(brace
id|remove_proc_entry
c_func
(paren
l_string|&quot;cpufreq&quot;
comma
op_amp
id|proc_root
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PROC_FS */
macro_line|#endif /* CONFIG_CPU_FREQ_26_API */
multiline_comment|/*********************************************************************&n; *                     NOTIFIER LISTS INTERFACE                      *&n; *********************************************************************/
multiline_comment|/**&n; *&t;cpufreq_register_notifier - register a driver with cpufreq&n; *&t;@nb: notifier function to register&n; *      @list: CPUFREQ_TRANSITION_NOTIFIER or CPUFREQ_POLICY_NOTIFIER&n; *&n; *&t;Add a driver to one of two lists: either a list of drivers that &n; *      are notified about clock rate changes (once before and once after&n; *      the transition), or a list of drivers that are notified about&n; *      changes in cpufreq policy.&n; *&n; *&t;This function may sleep, and has the same return conditions as&n; *&t;notifier_chain_register.&n; */
DECL|function|cpufreq_register_notifier
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
(brace
r_int
id|ret
suffix:semicolon
id|down
c_func
(paren
op_amp
id|cpufreq_notifier_sem
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|list
)paren
(brace
r_case
id|CPUFREQ_TRANSITION_NOTIFIER
suffix:colon
id|ret
op_assign
id|notifier_chain_register
c_func
(paren
op_amp
id|cpufreq_transition_notifier_list
comma
id|nb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPUFREQ_POLICY_NOTIFIER
suffix:colon
id|ret
op_assign
id|notifier_chain_register
c_func
(paren
op_amp
id|cpufreq_policy_notifier_list
comma
id|nb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|cpufreq_notifier_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|cpufreq_register_notifier
id|EXPORT_SYMBOL
c_func
(paren
id|cpufreq_register_notifier
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;cpufreq_unregister_notifier - unregister a driver with cpufreq&n; *&t;@nb: notifier block to be unregistered&n; *      @list: CPUFREQ_TRANSITION_NOTIFIER or CPUFREQ_POLICY_NOTIFIER&n; *&n; *&t;Remove a driver from the CPU frequency notifier list.&n; *&n; *&t;This function may sleep, and has the same return conditions as&n; *&t;notifier_chain_unregister.&n; */
DECL|function|cpufreq_unregister_notifier
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
(brace
r_int
id|ret
suffix:semicolon
id|down
c_func
(paren
op_amp
id|cpufreq_notifier_sem
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|list
)paren
(brace
r_case
id|CPUFREQ_TRANSITION_NOTIFIER
suffix:colon
id|ret
op_assign
id|notifier_chain_unregister
c_func
(paren
op_amp
id|cpufreq_transition_notifier_list
comma
id|nb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPUFREQ_POLICY_NOTIFIER
suffix:colon
id|ret
op_assign
id|notifier_chain_unregister
c_func
(paren
op_amp
id|cpufreq_policy_notifier_list
comma
id|nb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|cpufreq_notifier_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|cpufreq_unregister_notifier
id|EXPORT_SYMBOL
c_func
(paren
id|cpufreq_unregister_notifier
)paren
suffix:semicolon
multiline_comment|/*********************************************************************&n; *                          POLICY INTERFACE                         *&n; *********************************************************************/
multiline_comment|/**&n; * cpufreq_get_policy - get the current cpufreq_policy&n; * @policy: struct cpufreq_policy into which the current cpufreq_policy is written&n; *&n; * Reads the current cpufreq policy.&n; */
DECL|function|cpufreq_get_policy
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
(brace
id|down
c_func
(paren
op_amp
id|cpufreq_driver_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpufreq_driver
op_logical_or
op_logical_neg
id|policy
op_logical_or
(paren
id|cpu
op_ge
id|NR_CPUS
)paren
op_logical_or
(paren
op_logical_neg
id|cpu_online
c_func
(paren
id|cpu
)paren
)paren
)paren
(brace
id|up
c_func
(paren
op_amp
id|cpufreq_driver_sem
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|policy-&gt;min
op_assign
id|cpufreq_driver-&gt;policy
(braket
id|cpu
)braket
dot
id|min
suffix:semicolon
id|policy-&gt;max
op_assign
id|cpufreq_driver-&gt;policy
(braket
id|cpu
)braket
dot
id|max
suffix:semicolon
id|policy-&gt;policy
op_assign
id|cpufreq_driver-&gt;policy
(braket
id|cpu
)braket
dot
id|policy
suffix:semicolon
id|policy-&gt;max_cpu_freq
op_assign
id|cpufreq_driver-&gt;policy
(braket
l_int|0
)braket
dot
id|max_cpu_freq
suffix:semicolon
id|policy-&gt;cpu
op_assign
id|cpu
suffix:semicolon
id|up
c_func
(paren
op_amp
id|cpufreq_driver_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;cpufreq_set_policy - set a new CPUFreq policy&n; *&t;@policy: policy to be set.&n; *&n; *&t;Sets a new CPU frequency and voltage scaling policy.&n; */
DECL|function|cpufreq_set_policy
r_int
id|cpufreq_set_policy
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
id|i
suffix:semicolon
id|down
c_func
(paren
op_amp
id|cpufreq_driver_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpufreq_driver
op_logical_or
op_logical_neg
id|cpufreq_driver-&gt;verify
op_logical_or
op_logical_neg
id|cpufreq_driver-&gt;setpolicy
op_logical_or
op_logical_neg
id|policy
op_logical_or
(paren
id|policy-&gt;cpu
OG
id|NR_CPUS
)paren
)paren
(brace
id|up
c_func
(paren
op_amp
id|cpufreq_driver_sem
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|cpufreq_notifier_sem
)paren
suffix:semicolon
id|policy-&gt;max_cpu_freq
op_assign
id|cpufreq_driver-&gt;policy
(braket
l_int|0
)braket
dot
id|max_cpu_freq
suffix:semicolon
multiline_comment|/* verify the cpu speed can be set within this limit */
id|cpufreq_driver
op_member_access_from_pointer
id|verify
c_func
(paren
id|policy
)paren
suffix:semicolon
multiline_comment|/* adjust if neccessary - all reasons */
id|notifier_call_chain
c_func
(paren
op_amp
id|cpufreq_policy_notifier_list
comma
id|CPUFREQ_ADJUST
comma
id|policy
)paren
suffix:semicolon
multiline_comment|/* adjust if neccessary - hardware incompatibility*/
id|notifier_call_chain
c_func
(paren
op_amp
id|cpufreq_policy_notifier_list
comma
id|CPUFREQ_INCOMPATIBLE
comma
id|policy
)paren
suffix:semicolon
multiline_comment|/* verify the cpu speed can be set within this limit,&n;&t;   which might be different to the first one */
id|cpufreq_driver
op_member_access_from_pointer
id|verify
c_func
(paren
id|policy
)paren
suffix:semicolon
multiline_comment|/* notification of the new policy */
id|notifier_call_chain
c_func
(paren
op_amp
id|cpufreq_policy_notifier_list
comma
id|CPUFREQ_NOTIFY
comma
id|policy
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|cpufreq_notifier_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|policy-&gt;cpu
op_eq
id|CPUFREQ_ALL_CPUS
)paren
(brace
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
(brace
id|cpufreq_driver-&gt;policy
(braket
id|i
)braket
dot
id|min
op_assign
id|policy-&gt;min
suffix:semicolon
id|cpufreq_driver-&gt;policy
(braket
id|i
)braket
dot
id|max
op_assign
id|policy-&gt;max
suffix:semicolon
id|cpufreq_driver-&gt;policy
(braket
id|i
)braket
dot
id|policy
op_assign
id|policy-&gt;policy
suffix:semicolon
)brace
)brace
r_else
(brace
id|cpufreq_driver-&gt;policy
(braket
id|policy-&gt;cpu
)braket
dot
id|min
op_assign
id|policy-&gt;min
suffix:semicolon
id|cpufreq_driver-&gt;policy
(braket
id|policy-&gt;cpu
)braket
dot
id|max
op_assign
id|policy-&gt;max
suffix:semicolon
id|cpufreq_driver-&gt;policy
(braket
id|policy-&gt;cpu
)braket
dot
id|policy
op_assign
id|policy-&gt;policy
suffix:semicolon
)brace
id|cpufreq_driver
op_member_access_from_pointer
id|setpolicy
c_func
(paren
id|policy
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|cpufreq_driver_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cpufreq_set_policy
id|EXPORT_SYMBOL
c_func
(paren
id|cpufreq_set_policy
)paren
suffix:semicolon
multiline_comment|/*********************************************************************&n; *                    DYNAMIC CPUFREQ SWITCHING                      *&n; *********************************************************************/
macro_line|#ifdef CONFIG_CPU_FREQ_DYNAMIC
multiline_comment|/* TBD */
macro_line|#endif /* CONFIG_CPU_FREQ_DYNAMIC */
multiline_comment|/*********************************************************************&n; *            EXTERNALLY AFFECTING FREQUENCY CHANGES                 *&n; *********************************************************************/
multiline_comment|/**&n; * adjust_jiffies - adjust the system &quot;loops_per_jiffy&quot;&n; *&n; * This function alters the system &quot;loops_per_jiffy&quot; for the clock&n; * speed change. Note that loops_per_jiffy is only updated if all&n; * CPUs are affected - else there is a need for per-CPU loops_per_jiffy&n; * values which are provided by various architectures. &n; */
DECL|function|adjust_jiffies
r_static
r_inline
r_void
id|adjust_jiffies
c_func
(paren
r_int
r_int
id|val
comma
r_struct
id|cpufreq_freqs
op_star
id|ci
)paren
(brace
r_if
c_cond
(paren
(paren
id|val
op_eq
id|CPUFREQ_PRECHANGE
op_logical_and
id|ci-&gt;old
OL
id|ci
op_member_access_from_pointer
r_new
)paren
op_logical_or
(paren
id|val
op_eq
id|CPUFREQ_POSTCHANGE
op_logical_and
id|ci-&gt;old
OG
id|ci
op_member_access_from_pointer
r_new
)paren
)paren
r_if
c_cond
(paren
id|ci-&gt;cpu
op_eq
id|CPUFREQ_ALL_CPUS
)paren
id|loops_per_jiffy
op_assign
id|cpufreq_scale
c_func
(paren
id|loops_per_jiffy
comma
id|ci-&gt;old
comma
id|ci
op_member_access_from_pointer
r_new
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * cpufreq_notify_transition - call notifier chain and adjust_jiffies on frequency transition&n; *&n; * This function calls the transition notifiers and the &quot;adjust_jiffies&quot; function. It is called&n; * twice on all CPU frequency changes that have external effects. &n; */
DECL|function|cpufreq_notify_transition
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
(brace
id|down
c_func
(paren
op_amp
id|cpufreq_notifier_sem
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|state
)paren
(brace
r_case
id|CPUFREQ_PRECHANGE
suffix:colon
id|notifier_call_chain
c_func
(paren
op_amp
id|cpufreq_transition_notifier_list
comma
id|CPUFREQ_PRECHANGE
comma
id|freqs
)paren
suffix:semicolon
id|adjust_jiffies
c_func
(paren
id|CPUFREQ_PRECHANGE
comma
id|freqs
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPUFREQ_POSTCHANGE
suffix:colon
id|adjust_jiffies
c_func
(paren
id|CPUFREQ_POSTCHANGE
comma
id|freqs
)paren
suffix:semicolon
id|notifier_call_chain
c_func
(paren
op_amp
id|cpufreq_transition_notifier_list
comma
id|CPUFREQ_POSTCHANGE
comma
id|freqs
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|cpufreq_notifier_sem
)paren
suffix:semicolon
)brace
DECL|variable|cpufreq_notify_transition
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|cpufreq_notify_transition
)paren
suffix:semicolon
multiline_comment|/*********************************************************************&n; *               REGISTER / UNREGISTER CPUFREQ DRIVER                *&n; *********************************************************************/
multiline_comment|/**&n; * cpufreq_register - register a CPU Frequency driver&n; * @driver_data: A struct cpufreq_driver containing the values submitted by the CPU Frequency driver.&n; *&n; *   Registers a CPU Frequency driver to this core code. This code &n; * returns zero on success, -EBUSY when another driver got here first&n; * (and isn&squot;t unregistered in the meantime). &n; *&n; */
DECL|function|cpufreq_register
r_int
id|cpufreq_register
c_func
(paren
r_struct
id|cpufreq_driver
op_star
id|driver_data
)paren
(brace
r_int
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|cpufreq_driver
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|driver_data
op_logical_or
op_logical_neg
id|driver_data-&gt;verify
op_logical_or
op_logical_neg
id|driver_data-&gt;setpolicy
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|down
c_func
(paren
op_amp
id|cpufreq_driver_sem
)paren
suffix:semicolon
id|cpufreq_driver
op_assign
id|driver_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|default_policy.policy
)paren
id|default_policy.policy
op_assign
id|driver_data-&gt;policy
(braket
l_int|0
)braket
dot
id|policy
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|default_policy.min
)paren
id|default_policy.min
op_assign
id|driver_data-&gt;policy
(braket
l_int|0
)braket
dot
id|min
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|default_policy.max
)paren
id|default_policy.max
op_assign
id|driver_data-&gt;policy
(braket
l_int|0
)braket
dot
id|max
suffix:semicolon
id|default_policy.cpu
op_assign
id|CPUFREQ_ALL_CPUS
suffix:semicolon
id|up
c_func
(paren
op_amp
id|cpufreq_driver_sem
)paren
suffix:semicolon
id|ret
op_assign
id|cpufreq_set_policy
c_func
(paren
op_amp
id|default_policy
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_FREQ_26_API
id|cpufreq_proc_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|ret
)paren
(brace
id|down
c_func
(paren
op_amp
id|cpufreq_driver_sem
)paren
suffix:semicolon
id|cpufreq_driver
op_assign
l_int|NULL
suffix:semicolon
id|up
c_func
(paren
op_amp
id|cpufreq_driver_sem
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|cpufreq_register
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|cpufreq_register
)paren
suffix:semicolon
multiline_comment|/**&n; * cpufreq_unregister - unregister the current CPUFreq driver&n; *&n; *    Unregister the current CPUFreq driver. Only call this if you have &n; * the right to do so, i.e. if you have succeeded in initialising before!&n; * Returns zero if successful, and -EINVAL if the cpufreq_driver is&n; * currently not initialised.&n; */
DECL|function|cpufreq_unregister
r_int
id|cpufreq_unregister
c_func
(paren
r_void
)paren
(brace
id|down
c_func
(paren
op_amp
id|cpufreq_driver_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpufreq_driver
)paren
(brace
id|up
c_func
(paren
op_amp
id|cpufreq_driver_sem
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|cpufreq_driver
op_assign
l_int|NULL
suffix:semicolon
id|up
c_func
(paren
op_amp
id|cpufreq_driver_sem
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_FREQ_26_API
id|cpufreq_proc_exit
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cpufreq_unregister
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|cpufreq_unregister
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PM
multiline_comment|/**&n; *&t;cpufreq_restore - restore the CPU clock frequency after resume&n; *&n; *&t;Restore the CPU clock frequency so that our idea of the current&n; *&t;frequency reflects the actual hardware.&n; */
DECL|function|cpufreq_restore
r_int
id|cpufreq_restore
c_func
(paren
r_void
)paren
(brace
r_struct
id|cpufreq_policy
id|policy
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;cpufreq_restore() called from interrupt context!&quot;
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
(brace
r_if
c_cond
(paren
op_logical_neg
id|cpu_online
c_func
(paren
id|i
)paren
)paren
r_continue
suffix:semicolon
id|down
c_func
(paren
op_amp
id|cpufreq_driver_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpufreq_driver
)paren
(brace
id|up
c_func
(paren
op_amp
id|cpufreq_driver_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|policy.min
op_assign
id|cpufreq_driver-&gt;policy
(braket
id|i
)braket
dot
id|min
suffix:semicolon
id|policy.max
op_assign
id|cpufreq_driver-&gt;policy
(braket
id|i
)braket
dot
id|max
suffix:semicolon
id|policy.policy
op_assign
id|cpufreq_driver-&gt;policy
(braket
id|i
)braket
dot
id|policy
suffix:semicolon
id|policy.cpu
op_assign
id|i
suffix:semicolon
id|up
c_func
(paren
op_amp
id|cpufreq_driver_sem
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_FREQ_26_API
id|cpufreq_set_policy
c_func
(paren
op_amp
id|policy
)paren
suffix:semicolon
macro_line|#endif
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cpufreq_restore
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|cpufreq_restore
)paren
suffix:semicolon
macro_line|#else
DECL|macro|cpufreq_restore
mdefine_line|#define cpufreq_restore()
macro_line|#endif /* CONFIG_PM */
eof
