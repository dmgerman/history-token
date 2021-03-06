multiline_comment|/*&n; * mce.c - x86 Machine Check Exception Reporting&n; * (c) 2002 Alan Cox &lt;alan@redhat.com&gt;, Dave Jones &lt;davej@codemonkey.org.uk&gt;&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/thread_info.h&gt;
macro_line|#include &lt;asm/processor.h&gt; 
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &quot;mce.h&quot;
DECL|variable|__initdata
r_int
id|mce_disabled
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|nr_mce_banks
r_int
id|nr_mce_banks
suffix:semicolon
DECL|variable|nr_mce_banks
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|nr_mce_banks
)paren
suffix:semicolon
multiline_comment|/* non-fatal.o */
multiline_comment|/* Handle unconfigured int18 (should never happen) */
DECL|function|unexpected_machine_check
r_static
id|fastcall
r_void
id|unexpected_machine_check
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|error_code
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;CPU#%d: Unexpected int18 (Machine Check).&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Call the installed machine check handler for this CPU setup. */
DECL|variable|machine_check_vector
r_void
id|fastcall
(paren
op_star
id|machine_check_vector
)paren
(paren
r_struct
id|pt_regs
op_star
comma
r_int
id|error_code
)paren
op_assign
id|unexpected_machine_check
suffix:semicolon
multiline_comment|/* This has to be run for each processor */
DECL|function|mcheck_init
r_void
id|__init
id|mcheck_init
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
r_if
c_cond
(paren
id|mce_disabled
op_eq
l_int|1
)paren
r_return
suffix:semicolon
r_switch
c_cond
(paren
id|c-&gt;x86_vendor
)paren
(brace
r_case
id|X86_VENDOR_AMD
suffix:colon
r_if
c_cond
(paren
id|c-&gt;x86
op_eq
l_int|6
op_logical_or
id|c-&gt;x86
op_eq
l_int|15
)paren
id|amd_mcheck_init
c_func
(paren
id|c
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|X86_VENDOR_INTEL
suffix:colon
r_if
c_cond
(paren
id|c-&gt;x86
op_eq
l_int|5
)paren
id|intel_p5_mcheck_init
c_func
(paren
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;x86
op_eq
l_int|6
)paren
id|intel_p6_mcheck_init
c_func
(paren
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;x86
op_eq
l_int|15
)paren
id|intel_p4_mcheck_init
c_func
(paren
id|c
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|X86_VENDOR_CENTAUR
suffix:colon
r_if
c_cond
(paren
id|c-&gt;x86
op_eq
l_int|5
)paren
id|winchip_mcheck_init
c_func
(paren
id|c
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
DECL|function|mcheck_disable
r_static
r_int
id|__init
id|mcheck_disable
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|mce_disabled
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mcheck_enable
r_static
r_int
id|__init
id|mcheck_enable
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|mce_disabled
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;nomce&quot;
comma
id|mcheck_disable
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;mce&quot;
comma
id|mcheck_enable
)paren
suffix:semicolon
eof
