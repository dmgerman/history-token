multiline_comment|/*&n; * (C) 2002 - 2003  Dominik Brodowski &lt;linux@brodo.de&gt;&n; *&n; *  Licensed under the terms of the GNU GPL License version 2.&n; *&n; *  BIG FAT DISCLAIMER: Work in progress code. Possibly *dangerous*&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt; 
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/timex.h&gt;
DECL|variable|longrun_driver
r_static
r_struct
id|cpufreq_driver
id|longrun_driver
suffix:semicolon
multiline_comment|/**&n; * longrun_{low,high}_freq is needed for the conversion of cpufreq kHz &n; * values into per cent values. In TMTA microcode, the following is valid:&n; * performance_pctg = (current_freq - low_freq)/(high_freq - low_freq)&n; */
DECL|variable|longrun_low_freq
DECL|variable|longrun_high_freq
r_static
r_int
r_int
id|longrun_low_freq
comma
id|longrun_high_freq
suffix:semicolon
multiline_comment|/**&n; * longrun_get_policy - get the current LongRun policy&n; * @policy: struct cpufreq_policy where current policy is written into&n; *&n; * Reads the current LongRun policy by access to MSR_TMTA_LONGRUN_FLAGS&n; * and MSR_TMTA_LONGRUN_CTRL&n; */
DECL|function|longrun_get_policy
r_static
r_void
id|__init
id|longrun_get_policy
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
id|u32
id|msr_lo
comma
id|msr_hi
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_TMTA_LONGRUN_FLAGS
comma
id|msr_lo
comma
id|msr_hi
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msr_lo
op_amp
l_int|0x01
)paren
id|policy-&gt;policy
op_assign
id|CPUFREQ_POLICY_PERFORMANCE
suffix:semicolon
r_else
id|policy-&gt;policy
op_assign
id|CPUFREQ_POLICY_POWERSAVE
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_TMTA_LONGRUN_CTRL
comma
id|msr_lo
comma
id|msr_hi
)paren
suffix:semicolon
id|msr_lo
op_and_assign
l_int|0x0000007F
suffix:semicolon
id|msr_hi
op_and_assign
l_int|0x0000007F
suffix:semicolon
id|policy-&gt;min
op_assign
id|longrun_low_freq
op_plus
id|msr_lo
op_star
(paren
(paren
id|longrun_high_freq
op_minus
id|longrun_low_freq
)paren
op_div
l_int|100
)paren
suffix:semicolon
id|policy-&gt;max
op_assign
id|longrun_low_freq
op_plus
id|msr_hi
op_star
(paren
(paren
id|longrun_high_freq
op_minus
id|longrun_low_freq
)paren
op_div
l_int|100
)paren
suffix:semicolon
id|policy-&gt;cpu
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * longrun_set_policy - sets a new CPUFreq policy&n; * @policy - new policy&n; *&n; * Sets a new CPUFreq policy on LongRun-capable processors. This function&n; * has to be called with cpufreq_driver locked.&n; */
DECL|function|longrun_set_policy
r_static
r_int
id|longrun_set_policy
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
id|u32
id|msr_lo
comma
id|msr_hi
suffix:semicolon
id|u32
id|pctg_lo
comma
id|pctg_hi
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
id|pctg_lo
op_assign
(paren
id|policy-&gt;min
op_minus
id|longrun_low_freq
)paren
op_div
(paren
(paren
id|longrun_high_freq
op_minus
id|longrun_low_freq
)paren
op_div
l_int|100
)paren
suffix:semicolon
id|pctg_hi
op_assign
(paren
id|policy-&gt;max
op_minus
id|longrun_low_freq
)paren
op_div
(paren
(paren
id|longrun_high_freq
op_minus
id|longrun_low_freq
)paren
op_div
l_int|100
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pctg_hi
OG
l_int|100
)paren
id|pctg_hi
op_assign
l_int|100
suffix:semicolon
r_if
c_cond
(paren
id|pctg_lo
OG
id|pctg_hi
)paren
id|pctg_lo
op_assign
id|pctg_hi
suffix:semicolon
multiline_comment|/* performance or economy mode */
id|rdmsr
c_func
(paren
id|MSR_TMTA_LONGRUN_FLAGS
comma
id|msr_lo
comma
id|msr_hi
)paren
suffix:semicolon
id|msr_lo
op_and_assign
l_int|0xFFFFFFFE
suffix:semicolon
r_switch
c_cond
(paren
id|policy-&gt;policy
)paren
(brace
r_case
id|CPUFREQ_POLICY_PERFORMANCE
suffix:colon
id|msr_lo
op_or_assign
l_int|0x00000001
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPUFREQ_POLICY_POWERSAVE
suffix:colon
r_break
suffix:semicolon
)brace
id|wrmsr
c_func
(paren
id|MSR_TMTA_LONGRUN_FLAGS
comma
id|msr_lo
comma
id|msr_hi
)paren
suffix:semicolon
multiline_comment|/* lower and upper boundary */
id|rdmsr
c_func
(paren
id|MSR_TMTA_LONGRUN_CTRL
comma
id|msr_lo
comma
id|msr_hi
)paren
suffix:semicolon
id|msr_lo
op_and_assign
l_int|0xFFFFFF80
suffix:semicolon
id|msr_hi
op_and_assign
l_int|0xFFFFFF80
suffix:semicolon
id|msr_lo
op_or_assign
id|pctg_lo
suffix:semicolon
id|msr_hi
op_or_assign
id|pctg_hi
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_TMTA_LONGRUN_CTRL
comma
id|msr_lo
comma
id|msr_hi
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * longrun_verify_poliy - verifies a new CPUFreq policy&n; *&n; * Validates a new CPUFreq policy. This function has to be called with &n; * cpufreq_driver locked.&n; */
DECL|function|longrun_verify_policy
r_static
r_int
id|longrun_verify_policy
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
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
id|policy-&gt;cpu
op_assign
l_int|0
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
r_if
c_cond
(paren
(paren
id|policy-&gt;policy
op_ne
id|CPUFREQ_POLICY_POWERSAVE
)paren
op_logical_and
(paren
id|policy-&gt;policy
op_ne
id|CPUFREQ_POLICY_PERFORMANCE
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * longrun_determine_freqs - determines the lowest and highest possible core frequency&n; *&n; * Determines the lowest and highest possible core frequencies on this CPU.&n; * This is necessary to calculate the performance percentage according to&n; * TMTA rules:&n; * performance_pctg = (target_freq - low_freq)/(high_freq - low_freq)&n; */
DECL|function|longrun_determine_freqs
r_static
r_int
r_int
id|__init
id|longrun_determine_freqs
c_func
(paren
r_int
r_int
op_star
id|low_freq
comma
r_int
r_int
op_star
id|high_freq
)paren
(brace
id|u32
id|msr_lo
comma
id|msr_hi
suffix:semicolon
id|u32
id|save_lo
comma
id|save_hi
suffix:semicolon
id|u32
id|eax
comma
id|ebx
comma
id|ecx
comma
id|edx
suffix:semicolon
r_struct
id|cpuinfo_x86
op_star
id|c
op_assign
id|cpu_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|low_freq
op_logical_or
op_logical_neg
id|high_freq
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|cpu_has
c_func
(paren
id|c
comma
id|X86_FEATURE_LRTI
)paren
)paren
(brace
multiline_comment|/* if the LongRun Table Interface is present, the&n;&t;&t; * detection is a bit easier: &n;&t;&t; * For minimum frequency, read out the maximum&n;&t;&t; * level (msr_hi), write that into &quot;currently &n;&t;&t; * selected level&quot;, and read out the frequency.&n;&t;&t; * For maximum frequency, read out level zero.&n;&t;&t; */
multiline_comment|/* minimum */
id|rdmsr
c_func
(paren
id|MSR_TMTA_LRTI_READOUT
comma
id|msr_lo
comma
id|msr_hi
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_TMTA_LRTI_READOUT
comma
id|msr_hi
comma
id|msr_hi
)paren
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_TMTA_LRTI_VOLT_MHZ
comma
id|msr_lo
comma
id|msr_hi
)paren
suffix:semicolon
op_star
id|low_freq
op_assign
id|msr_lo
op_star
l_int|1000
suffix:semicolon
multiline_comment|/* to kHz */
multiline_comment|/* maximum */
id|wrmsr
c_func
(paren
id|MSR_TMTA_LRTI_READOUT
comma
l_int|0
comma
id|msr_hi
)paren
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_TMTA_LRTI_VOLT_MHZ
comma
id|msr_lo
comma
id|msr_hi
)paren
suffix:semicolon
op_star
id|high_freq
op_assign
id|msr_lo
op_star
l_int|1000
suffix:semicolon
multiline_comment|/* to kHz */
r_if
c_cond
(paren
op_star
id|low_freq
OG
op_star
id|high_freq
)paren
op_star
id|low_freq
op_assign
op_star
id|high_freq
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* set the upper border to the value determined during TSC init */
op_star
id|high_freq
op_assign
(paren
id|cpu_khz
op_div
l_int|1000
)paren
suffix:semicolon
op_star
id|high_freq
op_assign
op_star
id|high_freq
op_star
l_int|1000
suffix:semicolon
multiline_comment|/* get current borders */
id|rdmsr
c_func
(paren
id|MSR_TMTA_LONGRUN_CTRL
comma
id|msr_lo
comma
id|msr_hi
)paren
suffix:semicolon
id|save_lo
op_assign
id|msr_lo
op_amp
l_int|0x0000007F
suffix:semicolon
id|save_hi
op_assign
id|msr_hi
op_amp
l_int|0x0000007F
suffix:semicolon
multiline_comment|/* if current perf_pctg is larger than 90%, we need to decrease the&n;&t; * upper limit to make the calculation more accurate.&n;&t; */
id|cpuid
c_func
(paren
l_int|0x80860007
comma
op_amp
id|eax
comma
op_amp
id|ebx
comma
op_amp
id|ecx
comma
op_amp
id|edx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ecx
OG
l_int|90
)paren
(brace
multiline_comment|/* set to 0 to 80 perf_pctg */
id|msr_lo
op_and_assign
l_int|0xFFFFFF80
suffix:semicolon
id|msr_hi
op_and_assign
l_int|0xFFFFFF80
suffix:semicolon
id|msr_lo
op_or_assign
l_int|0
suffix:semicolon
id|msr_hi
op_or_assign
l_int|80
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_TMTA_LONGRUN_CTRL
comma
id|msr_lo
comma
id|msr_hi
)paren
suffix:semicolon
multiline_comment|/* read out current core MHz and current perf_pctg */
id|cpuid
c_func
(paren
l_int|0x80860007
comma
op_amp
id|eax
comma
op_amp
id|ebx
comma
op_amp
id|ecx
comma
op_amp
id|edx
)paren
suffix:semicolon
multiline_comment|/* restore values */
id|wrmsr
c_func
(paren
id|MSR_TMTA_LONGRUN_CTRL
comma
id|save_lo
comma
id|save_hi
)paren
suffix:semicolon
)brace
multiline_comment|/* performance_pctg = (current_freq - low_freq)/(high_freq - low_freq)&n;&t; * eqals&n;&t; * low_freq * ( 1 - perf_pctg) = (cur_freq - high_freq * perf_pctg)&n;&t; *&n;&t; * high_freq * perf_pctg is stored tempoarily into &quot;ebx&quot;.&n;&t; */
id|ebx
op_assign
(paren
(paren
(paren
id|cpu_khz
op_div
l_int|1000
)paren
op_star
id|ecx
)paren
op_div
l_int|100
)paren
suffix:semicolon
multiline_comment|/* to MHz */
r_if
c_cond
(paren
(paren
id|ecx
OG
l_int|95
)paren
op_logical_or
(paren
id|ecx
op_eq
l_int|0
)paren
op_logical_or
(paren
id|eax
OL
id|ebx
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|edx
op_assign
(paren
id|eax
op_minus
id|ebx
)paren
op_div
(paren
l_int|100
op_minus
id|ecx
)paren
suffix:semicolon
op_star
id|low_freq
op_assign
id|edx
op_star
l_int|1000
suffix:semicolon
multiline_comment|/* back to kHz */
r_if
c_cond
(paren
op_star
id|low_freq
OG
op_star
id|high_freq
)paren
op_star
id|low_freq
op_assign
op_star
id|high_freq
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|longrun_cpu_init
r_static
r_int
id|__init
id|longrun_cpu_init
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* capability check */
r_if
c_cond
(paren
id|policy-&gt;cpu
op_ne
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* detect low and high frequency */
id|result
op_assign
id|longrun_determine_freqs
c_func
(paren
op_amp
id|longrun_low_freq
comma
op_amp
id|longrun_high_freq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
multiline_comment|/* cpuinfo and default policy values */
id|policy-&gt;cpuinfo.min_freq
op_assign
id|longrun_low_freq
suffix:semicolon
id|policy-&gt;cpuinfo.max_freq
op_assign
id|longrun_high_freq
suffix:semicolon
id|policy-&gt;cpuinfo.transition_latency
op_assign
id|CPUFREQ_ETERNAL
suffix:semicolon
id|longrun_get_policy
c_func
(paren
id|policy
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|longrun_driver
r_static
r_struct
id|cpufreq_driver
id|longrun_driver
op_assign
(brace
dot
id|verify
op_assign
id|longrun_verify_policy
comma
dot
id|setpolicy
op_assign
id|longrun_set_policy
comma
dot
id|init
op_assign
id|longrun_cpu_init
comma
dot
id|name
op_assign
l_string|&quot;longrun&quot;
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
multiline_comment|/**&n; * longrun_init - initializes the Transmeta Crusoe LongRun CPUFreq driver&n; *&n; * Initializes the LongRun support.&n; */
DECL|function|longrun_init
r_static
r_int
id|__init
id|longrun_init
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
r_if
c_cond
(paren
id|c-&gt;x86_vendor
op_ne
id|X86_VENDOR_TRANSMETA
op_logical_or
op_logical_neg
id|cpu_has
c_func
(paren
id|c
comma
id|X86_FEATURE_LONGRUN
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_return
id|cpufreq_register_driver
c_func
(paren
op_amp
id|longrun_driver
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * longrun_exit - unregisters LongRun support&n; */
DECL|function|longrun_exit
r_static
r_void
id|__exit
id|longrun_exit
c_func
(paren
r_void
)paren
(brace
id|cpufreq_unregister_driver
c_func
(paren
op_amp
id|longrun_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
(paren
l_string|&quot;Dominik Brodowski &lt;linux@brodo.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
(paren
l_string|&quot;LongRun driver for Transmeta Crusoe processors.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|longrun_init
id|module_init
c_func
(paren
id|longrun_init
)paren
suffix:semicolon
DECL|variable|longrun_exit
id|module_exit
c_func
(paren
id|longrun_exit
)paren
suffix:semicolon
eof
