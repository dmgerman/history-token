macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &quot;cpu.h&quot;
DECL|function|init_rise
r_static
r_void
id|__init
id|init_rise
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;CPU: Rise iDragon&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;x86_model
OG
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot; II&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Unhide possibly hidden capability flags&n;&t;   The mp6 iDragon family don&squot;t have MSRs.&n;&t;   We switch on extra features with this cpuid weirdness: */
id|__asm__
(paren
l_string|&quot;movl $0x6363452a, %%eax&bslash;n&bslash;t&quot;
l_string|&quot;movl $0x3231206c, %%ecx&bslash;n&bslash;t&quot;
l_string|&quot;movl $0x2a32313a, %%edx&bslash;n&bslash;t&quot;
l_string|&quot;cpuid&bslash;n&bslash;t&quot;
l_string|&quot;movl $0x63634523, %%eax&bslash;n&bslash;t&quot;
l_string|&quot;movl $0x32315f6c, %%ecx&bslash;n&bslash;t&quot;
l_string|&quot;movl $0x2333313a, %%edx&bslash;n&bslash;t&quot;
l_string|&quot;cpuid&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;eax&quot;
comma
l_string|&quot;ebx&quot;
comma
l_string|&quot;ecx&quot;
comma
l_string|&quot;edx&quot;
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|X86_FEATURE_CX8
comma
id|c-&gt;x86_capability
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|cpu_dev
id|rise_cpu_dev
id|__initdata
op_assign
(brace
id|c_vendor
suffix:colon
l_string|&quot;Rise&quot;
comma
id|c_ident
suffix:colon
(brace
l_string|&quot;RiseRiseRise&quot;
)brace
comma
id|c_models
suffix:colon
(brace
(brace
id|X86_VENDOR_RISE
comma
l_int|5
comma
(brace
(braket
l_int|0
)braket
l_string|&quot;iDragon&quot;
comma
(braket
l_int|2
)braket
l_string|&quot;iDragon&quot;
comma
(braket
l_int|8
)braket
l_string|&quot;iDragon II&quot;
comma
(braket
l_int|9
)braket
l_string|&quot;iDragon II&quot;
)brace
)brace
comma
)brace
comma
id|c_init
suffix:colon
id|init_rise
comma
)brace
suffix:semicolon
DECL|function|rise_init_cpu
r_int
id|__init
id|rise_init_cpu
c_func
(paren
r_void
)paren
(brace
id|cpu_devs
(braket
id|X86_VENDOR_RISE
)braket
op_assign
op_amp
id|rise_cpu_dev
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
singleline_comment|//early_arch_initcall(rise_init_cpu);
eof
