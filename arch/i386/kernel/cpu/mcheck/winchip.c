multiline_comment|/*&n; * IDT Winchip specific Machine Check Exception Reporting&n; * (C) Copyright 2002 Alan Cox &lt;alan@redhat.com&gt;&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/processor.h&gt; 
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &quot;mce.h&quot;
multiline_comment|/* Machine check handler for WinChip C6 */
DECL|function|winchip_machine_check
r_static
id|fastcall
r_void
id|winchip_machine_check
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
id|KERN_EMERG
l_string|&quot;CPU0: Machine Check Exception.&bslash;n&quot;
)paren
suffix:semicolon
id|add_taint
c_func
(paren
id|TAINT_MACHINE_CHECK
)paren
suffix:semicolon
)brace
multiline_comment|/* Set up machine check reporting on the Winchip C6 series */
DECL|function|winchip_mcheck_init
r_void
id|__init
id|winchip_mcheck_init
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
id|u32
id|lo
comma
id|hi
suffix:semicolon
id|machine_check_vector
op_assign
id|winchip_machine_check
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IDT_FCR1
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
id|lo
op_or_assign
(paren
l_int|1
op_lshift
l_int|2
)paren
suffix:semicolon
multiline_comment|/* Enable EIERRINT (int 18 MCE) */
id|lo
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|4
)paren
suffix:semicolon
multiline_comment|/* Enable MCE */
id|wrmsr
c_func
(paren
id|MSR_IDT_FCR1
comma
id|lo
comma
id|hi
)paren
suffix:semicolon
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
l_string|&quot;Winchip machine check reporting enabled on CPU#0.&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
