multiline_comment|/*&n; * P5 specific Machine Check Exception Reporting&n; * (C) Copyright 2002 Alan Cox &lt;alan@redhat.com&gt;&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/processor.h&gt; 
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &quot;mce.h&quot;
multiline_comment|/* Machine check handler for Pentium class Intel */
DECL|function|pentium_machine_check
r_static
id|fastcall
r_void
id|pentium_machine_check
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
id|u32
id|loaddr
comma
id|hi
comma
id|lotype
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_P5_MC_ADDR
comma
id|loaddr
comma
id|hi
)paren
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_P5_MC_TYPE
comma
id|lotype
comma
id|hi
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;CPU#%d: Machine Check Exception:  0x%8X (type 0x%8X).&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|loaddr
comma
id|lotype
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lotype
op_amp
(paren
l_int|1
op_lshift
l_int|5
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;CPU#%d: Possible thermal failure (CPU on fire ?).&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
id|add_taint
c_func
(paren
id|TAINT_MACHINE_CHECK
)paren
suffix:semicolon
)brace
multiline_comment|/* Set up machine check reporting for processors with Intel style MCE */
DECL|function|intel_p5_mcheck_init
r_void
id|__init
id|intel_p5_mcheck_init
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
id|u32
id|l
comma
id|h
suffix:semicolon
multiline_comment|/*Check for MCE support */
r_if
c_cond
(paren
op_logical_neg
id|cpu_has
c_func
(paren
id|c
comma
id|X86_FEATURE_MCE
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Default P5 to off as its often misconnected */
r_if
c_cond
(paren
id|mce_disabled
op_ne
op_minus
l_int|1
)paren
(brace
r_return
suffix:semicolon
)brace
id|machine_check_vector
op_assign
id|pentium_machine_check
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Read registers before enabling */
id|rdmsr
c_func
(paren
id|MSR_IA32_P5_MC_ADDR
comma
id|l
comma
id|h
)paren
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_P5_MC_TYPE
comma
id|l
comma
id|h
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Intel old style machine check architecture supported.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Enable MCE */
id|set_in_cr4
c_func
(paren
id|X86_CR4_MCE
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Intel old style machine check reporting enabled on CPU#%d.&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
eof
