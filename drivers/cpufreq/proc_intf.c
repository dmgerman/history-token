multiline_comment|/*&n; * linux/drivers/cpufreq/proc_intf.c&n; *&n; * Copyright (C) 2002 - 2003 Dominik Brodowski&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
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
id|str_governor
(braket
l_int|16
)braket
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
l_string|&quot;%d:%d:%d:%15s&quot;
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
id|str_governor
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
l_string|&quot;%d%%%d%%%d%%%15s&quot;
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
id|str_governor
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
id|current_policy.cpuinfo.max_freq
)paren
op_div
l_int|100
suffix:semicolon
id|policy-&gt;max
op_assign
(paren
id|max
op_star
id|current_policy.cpuinfo.max_freq
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
l_string|&quot;%d:%d:%15s&quot;
comma
op_amp
id|min
comma
op_amp
id|max
comma
id|str_governor
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
l_string|&quot;%d%%%d%%%15s&quot;
comma
op_amp
id|min
comma
op_amp
id|max
comma
id|str_governor
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
id|current_policy.cpuinfo.max_freq
)paren
op_div
l_int|100
suffix:semicolon
id|policy-&gt;max
op_assign
(paren
id|max
op_star
id|current_policy.cpuinfo.max_freq
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
id|result
op_assign
id|cpufreq_parse_governor
c_func
(paren
id|str_governor
comma
op_amp
id|policy-&gt;policy
comma
op_amp
id|policy-&gt;governor
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|cpufreq_get_policy
c_func
(paren
op_amp
id|policy
comma
id|i
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|policy.cpuinfo.max_freq
)paren
r_continue
suffix:semicolon
id|min_pctg
op_assign
(paren
id|policy.min
op_star
l_int|100
)paren
op_div
id|policy.cpuinfo.max_freq
suffix:semicolon
id|max_pctg
op_assign
(paren
id|policy.max
op_star
l_int|100
)paren
op_div
id|policy.cpuinfo.max_freq
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
r_case
id|CPUFREQ_POLICY_GOVERNOR
suffix:colon
id|p
op_add_assign
id|snprintf
c_func
(paren
id|p
comma
id|CPUFREQ_NAME_LEN
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|policy.governor-&gt;name
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
r_int
r_int
id|i
op_assign
l_int|0
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
r_if
c_cond
(paren
id|policy.cpu
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
id|policy.cpu
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|cpu_online
c_func
(paren
id|i
)paren
)paren
id|cpufreq_set_policy
c_func
(paren
op_amp
id|policy
)paren
suffix:semicolon
)brace
)brace
r_else
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
id|__init
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
id|__exit
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
id|MODULE_AUTHOR
(paren
l_string|&quot;Dominik Brodowski &lt;linux@brodo.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
(paren
l_string|&quot;CPUfreq /proc/cpufreq interface&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|cpufreq_proc_init
id|module_init
c_func
(paren
id|cpufreq_proc_init
)paren
suffix:semicolon
DECL|variable|cpufreq_proc_exit
id|module_exit
c_func
(paren
id|cpufreq_proc_exit
)paren
suffix:semicolon
eof
