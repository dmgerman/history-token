macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
multiline_comment|/*&n; *&t;Get CPU information for use by the procfs.&n; */
DECL|function|show_cpuinfo
r_static
r_int
id|show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
(brace
multiline_comment|/* &n;&t; * These flag bits must match the definitions in &lt;asm/cpufeature.h&gt;.&n;&t; * NULL means this bit is undefined or reserved; either way it doesn&squot;t&n;&t; * have meaning as far as Linux is concerned.  Note that it&squot;s important&n;&t; * to realize there is a difference between this table and CPUID -- if&n;&t; * applications want to get the raw CPUID data, they should access&n;&t; * /dev/cpu/&lt;cpu_nr&gt;/cpuid instead.&n;&t; */
r_static
r_char
op_star
id|x86_cap_flags
(braket
)braket
op_assign
(brace
multiline_comment|/* Intel-defined */
l_string|&quot;fpu&quot;
comma
l_string|&quot;vme&quot;
comma
l_string|&quot;de&quot;
comma
l_string|&quot;pse&quot;
comma
l_string|&quot;tsc&quot;
comma
l_string|&quot;msr&quot;
comma
l_string|&quot;pae&quot;
comma
l_string|&quot;mce&quot;
comma
l_string|&quot;cx8&quot;
comma
l_string|&quot;apic&quot;
comma
l_int|NULL
comma
l_string|&quot;sep&quot;
comma
l_string|&quot;mtrr&quot;
comma
l_string|&quot;pge&quot;
comma
l_string|&quot;mca&quot;
comma
l_string|&quot;cmov&quot;
comma
l_string|&quot;pat&quot;
comma
l_string|&quot;pse36&quot;
comma
l_string|&quot;pn&quot;
comma
l_string|&quot;clflush&quot;
comma
l_int|NULL
comma
l_string|&quot;dts&quot;
comma
l_string|&quot;acpi&quot;
comma
l_string|&quot;mmx&quot;
comma
l_string|&quot;fxsr&quot;
comma
l_string|&quot;sse&quot;
comma
l_string|&quot;sse2&quot;
comma
l_string|&quot;ss&quot;
comma
l_string|&quot;ht&quot;
comma
l_string|&quot;tm&quot;
comma
l_string|&quot;ia64&quot;
comma
l_string|&quot;pbe&quot;
comma
multiline_comment|/* AMD-defined */
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_string|&quot;syscall&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_string|&quot;mp&quot;
comma
l_string|&quot;nx&quot;
comma
l_int|NULL
comma
l_string|&quot;mmxext&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_string|&quot;lm&quot;
comma
l_string|&quot;3dnowext&quot;
comma
l_string|&quot;3dnow&quot;
comma
multiline_comment|/* Transmeta-defined */
l_string|&quot;recovery&quot;
comma
l_string|&quot;longrun&quot;
comma
l_int|NULL
comma
l_string|&quot;lrti&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
multiline_comment|/* Other (Linux-defined) */
l_string|&quot;cxmmx&quot;
comma
l_string|&quot;k6_mtrr&quot;
comma
l_string|&quot;cyrix_arr&quot;
comma
l_string|&quot;centaur_mcr&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
multiline_comment|/* Intel-defined (#2) */
l_string|&quot;pni&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
l_string|&quot;monitor&quot;
comma
l_string|&quot;ds_cpl&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
l_string|&quot;est&quot;
comma
l_string|&quot;tm2&quot;
comma
l_int|NULL
comma
l_string|&quot;cid&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_string|&quot;xtpr&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
multiline_comment|/* VIA/Cyrix/Centaur-defined */
l_int|NULL
comma
l_int|NULL
comma
l_string|&quot;rng&quot;
comma
l_string|&quot;rng_en&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
l_string|&quot;ace&quot;
comma
l_string|&quot;ace_en&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
)brace
suffix:semicolon
r_struct
id|cpuinfo_x86
op_star
id|c
op_assign
id|v
suffix:semicolon
r_int
id|i
comma
id|n
op_assign
id|c
op_minus
id|cpu_data
suffix:semicolon
r_int
id|fpu_exception
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
op_logical_neg
id|cpu_online
c_func
(paren
id|n
)paren
)paren
r_return
l_int|0
suffix:semicolon
macro_line|#endif
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;processor&bslash;t: %d&bslash;n&quot;
l_string|&quot;vendor_id&bslash;t: %s&bslash;n&quot;
l_string|&quot;cpu family&bslash;t: %d&bslash;n&quot;
l_string|&quot;model&bslash;t&bslash;t: %d&bslash;n&quot;
l_string|&quot;model name&bslash;t: %s&bslash;n&quot;
comma
id|n
comma
id|c-&gt;x86_vendor_id
(braket
l_int|0
)braket
ques
c_cond
id|c-&gt;x86_vendor_id
suffix:colon
l_string|&quot;unknown&quot;
comma
id|c-&gt;x86
comma
id|c-&gt;x86_model
comma
id|c-&gt;x86_model_id
(braket
l_int|0
)braket
ques
c_cond
id|c-&gt;x86_model_id
suffix:colon
l_string|&quot;unknown&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;x86_mask
op_logical_or
id|c-&gt;cpuid_level
op_ge
l_int|0
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;stepping&bslash;t: %d&bslash;n&quot;
comma
id|c-&gt;x86_mask
)paren
suffix:semicolon
r_else
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;stepping&bslash;t: unknown&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu_has
c_func
(paren
id|c
comma
id|X86_FEATURE_TSC
)paren
)paren
(brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;cpu MHz&bslash;t&bslash;t: %lu.%03lu&bslash;n&quot;
comma
id|cpu_khz
op_div
l_int|1000
comma
(paren
id|cpu_khz
op_mod
l_int|1000
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Cache size */
r_if
c_cond
(paren
id|c-&gt;x86_cache_size
op_ge
l_int|0
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;cache size&bslash;t: %d KB&bslash;n&quot;
comma
id|c-&gt;x86_cache_size
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_X86_HT
r_if
c_cond
(paren
id|cpu_has_ht
)paren
(brace
r_extern
r_int
id|phys_proc_id
(braket
id|NR_CPUS
)braket
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;physical id&bslash;t: %d&bslash;n&quot;
comma
id|phys_proc_id
(braket
id|n
)braket
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;siblings&bslash;t: %d&bslash;n&quot;
comma
id|smp_num_siblings
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* We use exception 16 if we have hardware math and we&squot;ve either seen it or the CPU claims it is internal */
id|fpu_exception
op_assign
id|c-&gt;hard_math
op_logical_and
(paren
id|ignore_fpu_irq
op_logical_or
id|cpu_has_fpu
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;fdiv_bug&bslash;t: %s&bslash;n&quot;
l_string|&quot;hlt_bug&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;f00f_bug&bslash;t: %s&bslash;n&quot;
l_string|&quot;coma_bug&bslash;t: %s&bslash;n&quot;
l_string|&quot;fpu&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;fpu_exception&bslash;t: %s&bslash;n&quot;
l_string|&quot;cpuid level&bslash;t: %d&bslash;n&quot;
l_string|&quot;wp&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;flags&bslash;t&bslash;t:&quot;
comma
id|c-&gt;fdiv_bug
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|c-&gt;hlt_works_ok
ques
c_cond
l_string|&quot;no&quot;
suffix:colon
l_string|&quot;yes&quot;
comma
id|c-&gt;f00f_bug
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|c-&gt;coma_bug
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|c-&gt;hard_math
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|fpu_exception
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|c-&gt;cpuid_level
comma
id|c-&gt;wp_works_ok
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
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
l_int|32
op_star
id|NCAPINTS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|i
comma
id|c-&gt;x86_capability
)paren
op_logical_and
id|x86_cap_flags
(braket
id|i
)braket
op_ne
l_int|NULL
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot; %s&quot;
comma
id|x86_cap_flags
(braket
id|i
)braket
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;&bslash;nbogomips&bslash;t: %lu.%02lu&bslash;n&bslash;n&quot;
comma
id|c-&gt;loops_per_jiffy
op_div
(paren
l_int|500000
op_div
id|HZ
)paren
comma
(paren
id|c-&gt;loops_per_jiffy
op_div
(paren
l_int|5000
op_div
id|HZ
)paren
)paren
op_mod
l_int|100
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|c_start
r_static
r_void
op_star
id|c_start
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_return
op_star
id|pos
OL
id|NR_CPUS
ques
c_cond
id|cpu_data
op_plus
op_star
id|pos
suffix:colon
l_int|NULL
suffix:semicolon
)brace
DECL|function|c_next
r_static
r_void
op_star
id|c_next
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
comma
id|loff_t
op_star
id|pos
)paren
(brace
op_increment
op_star
id|pos
suffix:semicolon
r_return
id|c_start
c_func
(paren
id|m
comma
id|pos
)paren
suffix:semicolon
)brace
DECL|function|c_stop
r_static
r_void
id|c_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
(brace
)brace
DECL|variable|cpuinfo_op
r_struct
id|seq_operations
id|cpuinfo_op
op_assign
(brace
dot
id|start
op_assign
id|c_start
comma
dot
id|next
op_assign
id|c_next
comma
dot
id|stop
op_assign
id|c_stop
comma
dot
id|show
op_assign
id|show_cpuinfo
comma
)brace
suffix:semicolon
eof
