multiline_comment|/*&n; *  $Id: powernow-k6.c,v 1.31 2002/09/21 09:05:29 db Exp $&n; *  This file was part of Powertweak Linux (http://powertweak.sf.net)&n; *  and is shared with the Linux Kernel module.&n; *&n; *  (C) 2000-2002  Dave Jones, Arjan van de Ven, Janne P&#xfffd;nk&#xfffd;l&#xfffd;, Dominik Brodowski.&n; *&n; *  Licensed under the terms of the GNU GPL License version 2.&n; *&n; *  BIG FAT DISCLAIMER: Work in progress code. Possibly *dangerous*&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt; 
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/timex.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|POWERNOW_IOPORT
mdefine_line|#define POWERNOW_IOPORT 0xfff0         /* it doesn&squot;t matter where, as long&n;&t;&t;&t;&t;&t;  as it is unused */
DECL|variable|powernow_driver
r_static
r_struct
id|cpufreq_driver
op_star
id|powernow_driver
suffix:semicolon
DECL|variable|busfreq
r_static
r_int
r_int
id|busfreq
suffix:semicolon
multiline_comment|/* FSB, in 10 kHz */
DECL|variable|max_multiplier
r_static
r_int
r_int
id|max_multiplier
suffix:semicolon
multiline_comment|/* Clock ratio multiplied by 10 - see table 27 in AMD#23446 */
DECL|variable|clock_ratio
r_static
r_int
id|clock_ratio
(braket
l_int|8
)braket
op_assign
(brace
l_int|45
comma
multiline_comment|/* 000 -&gt; 4.5x */
l_int|50
comma
multiline_comment|/* 001 -&gt; 5.0x */
l_int|40
comma
multiline_comment|/* 010 -&gt; 4.0x */
l_int|55
comma
multiline_comment|/* 011 -&gt; 5.5x */
l_int|20
comma
multiline_comment|/* 100 -&gt; 2.0x */
l_int|30
comma
multiline_comment|/* 101 -&gt; 3.0x */
l_int|60
comma
multiline_comment|/* 110 -&gt; 6.0x */
l_int|35
multiline_comment|/* 111 -&gt; 3.5x */
)brace
suffix:semicolon
multiline_comment|/**&n; * powernow_k6_get_cpu_multiplier - returns the current FSB multiplier&n; *&n; *   Returns the current setting of the frequency multiplier. Core clock&n; * speed is frequency of the Front-Side Bus multiplied with this value.&n; */
DECL|function|powernow_k6_get_cpu_multiplier
r_static
r_int
id|powernow_k6_get_cpu_multiplier
c_func
(paren
r_void
)paren
(brace
id|u64
id|invalue
op_assign
l_int|0
suffix:semicolon
id|u32
id|msrval
suffix:semicolon
id|msrval
op_assign
id|POWERNOW_IOPORT
op_plus
l_int|0x1
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_K6_EPMR
comma
id|msrval
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* enable the PowerNow port */
id|invalue
op_assign
id|inl
c_func
(paren
id|POWERNOW_IOPORT
op_plus
l_int|0x8
)paren
suffix:semicolon
id|msrval
op_assign
id|POWERNOW_IOPORT
op_plus
l_int|0x0
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_K6_EPMR
comma
id|msrval
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* disable it again */
r_return
id|clock_ratio
(braket
(paren
id|invalue
op_rshift
l_int|5
)paren
op_amp
l_int|7
)braket
suffix:semicolon
)brace
multiline_comment|/**&n; * powernow_k6_set_state - set the PowerNow! multiplier&n; * @best_i: clock_ratio[best_i] is the target multiplier&n; *&n; *   Tries to change the PowerNow! multiplier&n; */
DECL|function|powernow_k6_set_state
r_static
r_void
id|powernow_k6_set_state
(paren
r_int
r_int
id|best_i
)paren
(brace
r_int
r_int
id|outvalue
op_assign
l_int|0
comma
id|invalue
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|msrval
suffix:semicolon
r_struct
id|cpufreq_freqs
id|freqs
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|powernow_driver
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cpufreq: initialization problem or invalid target frequency&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|freqs.old
op_assign
id|busfreq
op_star
id|powernow_k6_get_cpu_multiplier
c_func
(paren
)paren
suffix:semicolon
id|freqs
dot
r_new
op_assign
id|busfreq
op_star
id|clock_ratio
(braket
id|best_i
)braket
suffix:semicolon
id|freqs.cpu
op_assign
id|CPUFREQ_ALL_CPUS
suffix:semicolon
multiline_comment|/* powernow-k6.c is UP only driver */
id|cpufreq_notify_transition
c_func
(paren
op_amp
id|freqs
comma
id|CPUFREQ_PRECHANGE
)paren
suffix:semicolon
multiline_comment|/* we now need to transform best_i to the BVC format, see AMD#23446 */
id|outvalue
op_assign
(paren
l_int|1
op_lshift
l_int|12
)paren
op_or
(paren
l_int|1
op_lshift
l_int|10
)paren
op_or
(paren
l_int|1
op_lshift
l_int|9
)paren
op_or
(paren
id|best_i
op_lshift
l_int|5
)paren
suffix:semicolon
id|msrval
op_assign
id|POWERNOW_IOPORT
op_plus
l_int|0x1
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_K6_EPMR
comma
id|msrval
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* enable the PowerNow port */
id|invalue
op_assign
id|inl
c_func
(paren
id|POWERNOW_IOPORT
op_plus
l_int|0x8
)paren
suffix:semicolon
id|invalue
op_assign
id|invalue
op_amp
l_int|0xf
suffix:semicolon
id|outvalue
op_assign
id|outvalue
op_or
id|invalue
suffix:semicolon
id|outl
c_func
(paren
id|outvalue
comma
(paren
id|POWERNOW_IOPORT
op_plus
l_int|0x8
)paren
)paren
suffix:semicolon
id|msrval
op_assign
id|POWERNOW_IOPORT
op_plus
l_int|0x0
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_K6_EPMR
comma
id|msrval
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* disable it again */
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
suffix:semicolon
)brace
multiline_comment|/**&n; * powernow_k6_verify - verifies a new CPUfreq policy&n; * @policy: new policy&n; *&n; * Policy must be within lowest and highest possible CPU Frequency,&n; * and at least one possible state must be within min and max.&n; */
DECL|function|powernow_k6_verify
r_static
r_void
id|powernow_k6_verify
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
id|number_states
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|policy
op_logical_or
op_logical_neg
id|busfreq
)paren
r_return
suffix:semicolon
id|policy-&gt;cpu
op_assign
l_int|0
suffix:semicolon
id|cpufreq_verify_within_limits
c_func
(paren
id|policy
comma
(paren
l_int|20
op_star
id|busfreq
)paren
comma
(paren
id|max_multiplier
op_star
id|busfreq
)paren
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|policy-&gt;min
op_le
(paren
id|busfreq
op_star
id|clock_ratio
(braket
id|i
)braket
)paren
)paren
op_logical_and
(paren
id|policy-&gt;max
op_ge
(paren
id|busfreq
op_star
id|clock_ratio
(braket
id|i
)braket
)paren
)paren
)paren
id|number_states
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|number_states
)paren
r_return
suffix:semicolon
multiline_comment|/* no state is available within range -- find next larger state */
id|j
op_assign
l_int|6
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
r_if
c_cond
(paren
(paren
(paren
id|clock_ratio
(braket
id|i
)braket
op_star
id|busfreq
)paren
op_ge
id|policy-&gt;min
)paren
op_logical_and
(paren
id|clock_ratio
(braket
id|i
)braket
OL
id|clock_ratio
(braket
id|j
)braket
)paren
)paren
id|j
op_assign
id|i
suffix:semicolon
id|policy-&gt;max
op_assign
id|clock_ratio
(braket
id|j
)braket
op_star
id|busfreq
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/**&n; * powernow_k6_setpolicy - sets a new CPUFreq policy&n; * @policy - new policy&n; *&n; * sets a new CPUFreq policy&n; */
DECL|function|powernow_k6_setpolicy
r_static
r_void
id|powernow_k6_setpolicy
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_int
r_int
id|number_states
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|i
comma
id|j
op_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|powernow_driver
)paren
r_return
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
r_if
c_cond
(paren
(paren
id|policy-&gt;min
op_le
(paren
id|busfreq
op_star
id|clock_ratio
(braket
id|i
)braket
)paren
)paren
op_logical_and
(paren
id|policy-&gt;max
op_ge
(paren
id|busfreq
op_star
id|clock_ratio
(braket
id|i
)braket
)paren
)paren
)paren
(brace
id|number_states
op_increment
suffix:semicolon
id|j
op_assign
id|i
suffix:semicolon
)brace
r_if
c_cond
(paren
id|number_states
op_eq
l_int|1
)paren
(brace
multiline_comment|/* if only one state is within the limit borders, it&n;&t;&t;   is easily detected and set */
id|powernow_k6_set_state
c_func
(paren
id|j
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* more than one state within limit */
r_switch
c_cond
(paren
id|policy-&gt;policy
)paren
(brace
r_case
id|CPUFREQ_POLICY_POWERSAVE
suffix:colon
id|j
op_assign
l_int|6
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
r_if
c_cond
(paren
(paren
id|policy-&gt;min
op_le
(paren
id|busfreq
op_star
id|clock_ratio
(braket
id|i
)braket
)paren
)paren
op_logical_and
(paren
id|policy-&gt;max
op_ge
(paren
id|busfreq
op_star
id|clock_ratio
(braket
id|i
)braket
)paren
)paren
op_logical_and
(paren
id|clock_ratio
(braket
id|i
)braket
OL
id|clock_ratio
(braket
id|j
)braket
)paren
)paren
id|j
op_assign
id|i
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPUFREQ_POLICY_PERFORMANCE
suffix:colon
id|j
op_assign
l_int|4
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
r_if
c_cond
(paren
(paren
id|policy-&gt;min
op_le
(paren
id|busfreq
op_star
id|clock_ratio
(braket
id|i
)braket
)paren
)paren
op_logical_and
(paren
id|policy-&gt;max
op_ge
(paren
id|busfreq
op_star
id|clock_ratio
(braket
id|i
)braket
)paren
)paren
op_logical_and
(paren
id|clock_ratio
(braket
id|i
)braket
OG
id|clock_ratio
(braket
id|j
)braket
)paren
)paren
id|j
op_assign
id|i
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|clock_ratio
(braket
id|i
)braket
OG
id|max_multiplier
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|powernow_k6_set_state
c_func
(paren
id|j
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/**&n; * powernow_k6_init - initializes the k6 PowerNow! CPUFreq driver&n; *&n; *   Initializes the K6 PowerNow! support. Returns -ENODEV on unsupported&n; * devices, -EINVAL or -ENOMEM on problems during initiatization, and zero&n; * on success.&n; */
DECL|function|powernow_k6_init
r_static
r_int
id|__init
id|powernow_k6_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|cpuinfo_x86
op_star
id|c
op_assign
id|cpu_data
suffix:semicolon
r_struct
id|cpufreq_driver
op_star
id|driver
suffix:semicolon
r_int
r_int
id|result
suffix:semicolon
r_if
c_cond
(paren
(paren
id|c-&gt;x86_vendor
op_ne
id|X86_VENDOR_AMD
)paren
op_logical_or
(paren
id|c-&gt;x86
op_ne
l_int|5
)paren
op_logical_or
(paren
(paren
id|c-&gt;x86_model
op_ne
l_int|12
)paren
op_logical_and
(paren
id|c-&gt;x86_model
op_ne
l_int|13
)paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|max_multiplier
op_assign
id|powernow_k6_get_cpu_multiplier
c_func
(paren
)paren
suffix:semicolon
id|busfreq
op_assign
id|cpu_khz
op_div
id|max_multiplier
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|POWERNOW_IOPORT
comma
l_int|16
comma
l_string|&quot;PowerNow!&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;cpufreq: PowerNow IOPORT region already used.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/* initialization of main &quot;cpufreq&quot; code*/
id|driver
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|cpufreq_driver
)paren
op_plus
id|NR_CPUS
op_star
r_sizeof
(paren
r_struct
id|cpufreq_freqs
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|driver
)paren
(brace
id|release_region
(paren
id|POWERNOW_IOPORT
comma
l_int|16
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|driver-&gt;policy
op_assign
(paren
r_struct
id|cpufreq_policy
op_star
)paren
(paren
id|driver
op_plus
r_sizeof
(paren
r_struct
id|cpufreq_driver
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_FREQ_24_API
id|driver-&gt;cpu_min_freq
op_assign
id|busfreq
op_star
l_int|20
suffix:semicolon
id|driver-&gt;cpu_cur_freq
(braket
l_int|0
)braket
op_assign
id|busfreq
op_star
id|max_multiplier
suffix:semicolon
macro_line|#endif
id|driver-&gt;verify
op_assign
op_amp
id|powernow_k6_verify
suffix:semicolon
id|driver-&gt;setpolicy
op_assign
op_amp
id|powernow_k6_setpolicy
suffix:semicolon
id|driver-&gt;policy
(braket
l_int|0
)braket
dot
id|cpu
op_assign
l_int|0
suffix:semicolon
id|driver-&gt;policy
(braket
l_int|0
)braket
dot
id|min
op_assign
id|busfreq
op_star
l_int|20
suffix:semicolon
id|driver-&gt;policy
(braket
l_int|0
)braket
dot
id|max
op_assign
id|busfreq
op_star
id|max_multiplier
suffix:semicolon
id|driver-&gt;policy
(braket
l_int|0
)braket
dot
id|policy
op_assign
id|CPUFREQ_POLICY_PERFORMANCE
suffix:semicolon
id|driver-&gt;policy
(braket
l_int|0
)braket
dot
id|max_cpu_freq
op_assign
id|busfreq
op_star
id|max_multiplier
suffix:semicolon
id|result
op_assign
id|cpufreq_register
c_func
(paren
id|driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|release_region
(paren
id|POWERNOW_IOPORT
comma
l_int|16
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|driver
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|powernow_driver
op_assign
id|driver
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * powernow_k6_exit - unregisters AMD K6-2+/3+ PowerNow! support&n; *&n; *   Unregisters AMD K6-2+ / K6-3+ PowerNow! support.&n; */
DECL|function|powernow_k6_exit
r_static
r_void
id|__exit
id|powernow_k6_exit
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|powernow_driver
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|clock_ratio
(braket
id|i
)braket
op_eq
id|max_multiplier
)paren
id|powernow_k6_set_state
c_func
(paren
id|i
)paren
suffix:semicolon
id|cpufreq_unregister
c_func
(paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|powernow_driver
)paren
suffix:semicolon
)brace
)brace
id|MODULE_AUTHOR
(paren
l_string|&quot;Arjan van de Ven &lt;arjanv@redhat.com&gt;, Dave Jones &lt;davej@suse.de&gt;, Dominik Brodowski &lt;linux@brodo.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
(paren
l_string|&quot;PowerNow! driver for AMD K6-2+ / K6-3+ processors.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|powernow_k6_init
id|module_init
c_func
(paren
id|powernow_k6_init
)paren
suffix:semicolon
DECL|variable|powernow_k6_exit
id|module_exit
c_func
(paren
id|powernow_k6_exit
)paren
suffix:semicolon
eof
