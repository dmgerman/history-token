multiline_comment|/*&n; * linux/drivers/cpufreq/freq_table.c&n; *&n; * Copyright (C) 2002 - 2003 Dominik Brodowski&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
DECL|macro|dprintk
mdefine_line|#define dprintk(msg...) cpufreq_debug_printk(CPUFREQ_DEBUG_CORE, &quot;freq-table&quot;, msg)
multiline_comment|/*********************************************************************&n; *                     FREQUENCY TABLE HELPERS                       *&n; *********************************************************************/
DECL|function|cpufreq_frequency_table_cpuinfo
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
(brace
r_int
r_int
id|min_freq
op_assign
op_complement
l_int|0
suffix:semicolon
r_int
r_int
id|max_freq
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|table
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
r_int
r_int
id|freq
op_assign
id|table
(braket
id|i
)braket
dot
id|frequency
suffix:semicolon
r_if
c_cond
(paren
id|freq
op_eq
id|CPUFREQ_ENTRY_INVALID
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;table entry %u is invalid, skipping&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;table entry %u: %u kHz, %u index&bslash;n&quot;
comma
id|i
comma
id|freq
comma
id|table
(braket
id|i
)braket
dot
id|index
)paren
suffix:semicolon
r_if
c_cond
(paren
id|freq
OL
id|min_freq
)paren
id|min_freq
op_assign
id|freq
suffix:semicolon
r_if
c_cond
(paren
id|freq
OG
id|max_freq
)paren
id|max_freq
op_assign
id|freq
suffix:semicolon
)brace
id|policy-&gt;min
op_assign
id|policy-&gt;cpuinfo.min_freq
op_assign
id|min_freq
suffix:semicolon
id|policy-&gt;max
op_assign
id|policy-&gt;cpuinfo.max_freq
op_assign
id|max_freq
suffix:semicolon
r_if
c_cond
(paren
id|policy-&gt;min
op_eq
op_complement
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cpufreq_frequency_table_cpuinfo
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|cpufreq_frequency_table_cpuinfo
)paren
suffix:semicolon
DECL|function|cpufreq_frequency_table_verify
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
(brace
r_int
r_int
id|next_larger
op_assign
op_complement
l_int|0
suffix:semicolon
r_int
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|count
op_assign
l_int|0
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;request for verification of policy (%u - %u kHz) for cpu %u&bslash;n&quot;
comma
id|policy-&gt;min
comma
id|policy-&gt;max
comma
id|policy-&gt;cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu_online
c_func
(paren
id|policy-&gt;cpu
)paren
)paren
r_return
op_minus
id|EINVAL
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|table
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
r_int
r_int
id|freq
op_assign
id|table
(braket
id|i
)braket
dot
id|frequency
suffix:semicolon
r_if
c_cond
(paren
id|freq
op_eq
id|CPUFREQ_ENTRY_INVALID
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|freq
op_ge
id|policy-&gt;min
)paren
op_logical_and
(paren
id|freq
op_le
id|policy-&gt;max
)paren
)paren
id|count
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|next_larger
OG
id|freq
)paren
op_logical_and
(paren
id|freq
OG
id|policy-&gt;max
)paren
)paren
id|next_larger
op_assign
id|freq
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
id|policy-&gt;max
op_assign
id|next_larger
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
id|dprintk
c_func
(paren
l_string|&quot;verification lead to (%u - %u kHz) for cpu %u&bslash;n&quot;
comma
id|policy-&gt;min
comma
id|policy-&gt;max
comma
id|policy-&gt;cpu
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cpufreq_frequency_table_verify
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|cpufreq_frequency_table_verify
)paren
suffix:semicolon
DECL|function|cpufreq_frequency_table_target
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
(brace
r_struct
id|cpufreq_frequency_table
id|optimal
op_assign
(brace
dot
id|index
op_assign
op_complement
l_int|0
comma
)brace
suffix:semicolon
r_struct
id|cpufreq_frequency_table
id|suboptimal
op_assign
(brace
dot
id|index
op_assign
op_complement
l_int|0
comma
)brace
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;request for target %u kHz (relation: %u) for cpu %u&bslash;n&quot;
comma
id|target_freq
comma
id|relation
comma
id|policy-&gt;cpu
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|relation
)paren
(brace
r_case
id|CPUFREQ_RELATION_H
suffix:colon
id|optimal.frequency
op_assign
l_int|0
suffix:semicolon
id|suboptimal.frequency
op_assign
op_complement
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPUFREQ_RELATION_L
suffix:colon
id|optimal.frequency
op_assign
op_complement
l_int|0
suffix:semicolon
id|suboptimal.frequency
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cpu_online
c_func
(paren
id|policy-&gt;cpu
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|table
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
r_int
r_int
id|freq
op_assign
id|table
(braket
id|i
)braket
dot
id|frequency
suffix:semicolon
r_if
c_cond
(paren
id|freq
op_eq
id|CPUFREQ_ENTRY_INVALID
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|freq
OL
id|policy-&gt;min
)paren
op_logical_or
(paren
id|freq
OG
id|policy-&gt;max
)paren
)paren
r_continue
suffix:semicolon
r_switch
c_cond
(paren
id|relation
)paren
(brace
r_case
id|CPUFREQ_RELATION_H
suffix:colon
r_if
c_cond
(paren
id|freq
op_le
id|target_freq
)paren
(brace
r_if
c_cond
(paren
id|freq
op_ge
id|optimal.frequency
)paren
(brace
id|optimal.frequency
op_assign
id|freq
suffix:semicolon
id|optimal.index
op_assign
id|i
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|freq
op_le
id|suboptimal.frequency
)paren
(brace
id|suboptimal.frequency
op_assign
id|freq
suffix:semicolon
id|suboptimal.index
op_assign
id|i
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|CPUFREQ_RELATION_L
suffix:colon
r_if
c_cond
(paren
id|freq
op_ge
id|target_freq
)paren
(brace
r_if
c_cond
(paren
id|freq
op_le
id|optimal.frequency
)paren
(brace
id|optimal.frequency
op_assign
id|freq
suffix:semicolon
id|optimal.index
op_assign
id|i
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|freq
op_ge
id|suboptimal.frequency
)paren
(brace
id|suboptimal.frequency
op_assign
id|freq
suffix:semicolon
id|suboptimal.index
op_assign
id|i
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|optimal.index
OG
id|i
)paren
(brace
r_if
c_cond
(paren
id|suboptimal.index
OG
id|i
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
op_star
id|index
op_assign
id|suboptimal.index
suffix:semicolon
)brace
r_else
op_star
id|index
op_assign
id|optimal.index
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;target is %u (%u kHz, %u)&bslash;n&quot;
comma
op_star
id|index
comma
id|table
(braket
op_star
id|index
)braket
dot
id|frequency
comma
id|table
(braket
op_star
id|index
)braket
dot
id|index
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cpufreq_frequency_table_target
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|cpufreq_frequency_table_target
)paren
suffix:semicolon
DECL|variable|show_table
r_static
r_struct
id|cpufreq_frequency_table
op_star
id|show_table
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/**&n; * show_scaling_governor - show the current policy for the specified CPU&n; */
DECL|function|show_available_freqs
r_static
id|ssize_t
id|show_available_freqs
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
r_int
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|cpu
op_assign
id|policy-&gt;cpu
suffix:semicolon
id|ssize_t
id|count
op_assign
l_int|0
suffix:semicolon
r_struct
id|cpufreq_frequency_table
op_star
id|table
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|show_table
(braket
id|cpu
)braket
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|table
op_assign
id|show_table
(braket
id|cpu
)braket
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|table
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
id|table
(braket
id|i
)braket
dot
id|frequency
op_eq
id|CPUFREQ_ENTRY_INVALID
)paren
r_continue
suffix:semicolon
id|count
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|count
)braket
comma
l_string|&quot;%d &quot;
comma
id|table
(braket
id|i
)braket
dot
id|frequency
)paren
suffix:semicolon
)brace
id|count
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|count
)braket
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|variable|cpufreq_freq_attr_scaling_available_freqs
r_struct
id|freq_attr
id|cpufreq_freq_attr_scaling_available_freqs
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;scaling_available_frequencies&quot;
comma
dot
id|mode
op_assign
l_int|0444
comma
dot
id|owner
op_assign
id|THIS_MODULE
)brace
comma
dot
id|show
op_assign
id|show_available_freqs
comma
)brace
suffix:semicolon
DECL|variable|cpufreq_freq_attr_scaling_available_freqs
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|cpufreq_freq_attr_scaling_available_freqs
)paren
suffix:semicolon
multiline_comment|/*&n; * if you use these, you must assure that the frequency table is valid&n; * all the time between get_attr and put_attr!&n; */
DECL|function|cpufreq_frequency_table_get_attr
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
(brace
id|dprintk
c_func
(paren
l_string|&quot;setting show_table for cpu %u to %p&bslash;n&quot;
comma
id|cpu
comma
id|table
)paren
suffix:semicolon
id|show_table
(braket
id|cpu
)braket
op_assign
id|table
suffix:semicolon
)brace
DECL|variable|cpufreq_frequency_table_get_attr
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|cpufreq_frequency_table_get_attr
)paren
suffix:semicolon
DECL|function|cpufreq_frequency_table_put_attr
r_void
id|cpufreq_frequency_table_put_attr
c_func
(paren
r_int
r_int
id|cpu
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;clearing show_table for cpu %u&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
id|show_table
(braket
id|cpu
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|variable|cpufreq_frequency_table_put_attr
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|cpufreq_frequency_table_put_attr
)paren
suffix:semicolon
DECL|function|cpufreq_frequency_get_table
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
(brace
r_return
id|show_table
(braket
id|cpu
)braket
suffix:semicolon
)brace
DECL|variable|cpufreq_frequency_get_table
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|cpufreq_frequency_get_table
)paren
suffix:semicolon
id|MODULE_AUTHOR
(paren
l_string|&quot;Dominik Brodowski &lt;linux@brodo.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
(paren
l_string|&quot;CPUfreq frequency table helpers&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
