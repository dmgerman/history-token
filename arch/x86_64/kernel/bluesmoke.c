multiline_comment|/*&n; * arch/x86_64/kernel/bluesmoke.c - x86-64 Machine Check Exception Reporting&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/processor.h&gt; 
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/apic.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#ifdef CONFIG_X86_MCE
DECL|variable|__initdata
r_static
r_int
id|mce_disabled
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|banks
r_static
r_int
id|banks
suffix:semicolon
multiline_comment|/*&n; *&t;Machine Check Handler For Hammer&n; */
DECL|function|hammer_machine_check
r_static
r_void
id|hammer_machine_check
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
r_int
id|recover
op_assign
l_int|1
suffix:semicolon
id|u32
id|alow
comma
id|ahigh
comma
id|high
comma
id|low
suffix:semicolon
id|u32
id|mcgstl
comma
id|mcgsth
suffix:semicolon
r_int
id|i
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_MCG_STATUS
comma
id|mcgstl
comma
id|mcgsth
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mcgstl
op_amp
(paren
l_int|1
op_lshift
l_int|0
)paren
)paren
(brace
multiline_comment|/* Recoverable ? */
id|recover
op_assign
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;CPU %d: Machine Check Exception: %08x%08x&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|mcgsth
comma
id|mcgstl
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
id|banks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rdmsr
c_func
(paren
id|MSR_IA32_MC0_STATUS
op_plus
id|i
op_star
l_int|4
comma
id|low
comma
id|high
)paren
suffix:semicolon
r_if
c_cond
(paren
id|high
op_amp
(paren
l_int|1
op_lshift
l_int|31
)paren
)paren
(brace
r_if
c_cond
(paren
id|high
op_amp
(paren
l_int|1
op_lshift
l_int|29
)paren
)paren
(brace
id|recover
op_or_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|high
op_amp
(paren
l_int|1
op_lshift
l_int|25
)paren
)paren
(brace
id|recover
op_or_assign
l_int|2
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Bank %d: %08x%08x&quot;
comma
id|i
comma
id|high
comma
id|low
)paren
suffix:semicolon
id|high
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|31
)paren
suffix:semicolon
r_if
c_cond
(paren
id|high
op_amp
(paren
l_int|1
op_lshift
l_int|27
)paren
)paren
(brace
id|rdmsr
c_func
(paren
id|MSR_IA32_MC0_MISC
op_plus
id|i
op_star
l_int|4
comma
id|alow
comma
id|ahigh
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;[%08x%08x]&quot;
comma
id|ahigh
comma
id|alow
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|high
op_amp
(paren
l_int|1
op_lshift
l_int|26
)paren
)paren
(brace
id|rdmsr
c_func
(paren
id|MSR_IA32_MC0_ADDR
op_plus
id|i
op_star
l_int|4
comma
id|alow
comma
id|ahigh
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; at %08x%08x&quot;
comma
id|ahigh
comma
id|alow
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Clear it */
id|wrmsr
c_func
(paren
id|MSR_IA32_MC0_STATUS
op_plus
id|i
op_star
l_int|4
comma
l_int|0UL
comma
l_int|0UL
)paren
suffix:semicolon
multiline_comment|/* Serialize */
id|wmb
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|recover
op_amp
l_int|2
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;CPU context corrupt&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|recover
op_amp
l_int|1
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Unable to continue&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Attempting to continue.&bslash;n&quot;
)paren
suffix:semicolon
id|mcgstl
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|2
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_IA32_MCG_STATUS
comma
id|mcgstl
comma
id|mcgsth
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Handle unconfigured int18 (should never happen)&n; */
DECL|function|unexpected_machine_check
r_static
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
multiline_comment|/*&n; *&t;Call the installed machine check handler for this CPU setup.&n; */
DECL|variable|machine_check_vector
r_static
r_void
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
DECL|function|do_machine_check
id|asmlinkage
r_void
id|do_machine_check
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
id|machine_check_vector
c_func
(paren
id|regs
comma
id|error_code
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_X86_MCE_NONFATAL
DECL|variable|mce_timer
r_static
r_struct
id|timer_list
id|mce_timer
suffix:semicolon
DECL|variable|timerset
r_static
r_int
id|timerset
op_assign
l_int|0
suffix:semicolon
DECL|macro|MCE_RATE
mdefine_line|#define MCE_RATE&t;15*HZ&t;/* timer rate is 15s */
DECL|function|mce_checkregs
r_static
r_void
id|mce_checkregs
(paren
r_void
op_star
id|info
)paren
(brace
id|u32
id|low
comma
id|high
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
op_star
id|cpu
op_assign
id|info
suffix:semicolon
id|BUG_ON
(paren
op_star
id|cpu
op_ne
id|smp_processor_id
c_func
(paren
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
id|banks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rdmsr
c_func
(paren
id|MSR_IA32_MC0_STATUS
op_plus
id|i
op_star
l_int|4
comma
id|low
comma
id|high
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|low
op_or
id|high
)paren
op_ne
l_int|0
)paren
(brace
id|printk
(paren
id|KERN_EMERG
l_string|&quot;MCE: The hardware reports a non fatal, correctable incident occured on CPU %d.&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|printk
(paren
id|KERN_EMERG
l_string|&quot;Bank %d: %08x%08x&bslash;n&quot;
comma
id|i
comma
id|high
comma
id|low
)paren
suffix:semicolon
multiline_comment|/* Scrub the error so we don&squot;t pick it up in MCE_RATE seconds time. */
id|wrmsr
c_func
(paren
id|MSR_IA32_MC0_STATUS
op_plus
id|i
op_star
l_int|4
comma
l_int|0UL
comma
l_int|0UL
)paren
suffix:semicolon
multiline_comment|/* Serialize */
id|wmb
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|mce_timerfunc
r_static
r_void
id|mce_timerfunc
(paren
r_int
r_int
id|data
)paren
(brace
r_int
r_int
id|i
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
id|smp_num_cpus
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
op_eq
id|smp_processor_id
c_func
(paren
)paren
)paren
id|mce_checkregs
c_func
(paren
op_amp
id|i
)paren
suffix:semicolon
r_else
id|smp_call_function
(paren
id|mce_checkregs
comma
op_amp
id|i
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Refresh the timer. */
id|mce_timer.expires
op_assign
id|jiffies
op_plus
id|MCE_RATE
suffix:semicolon
id|add_timer
(paren
op_amp
id|mce_timer
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; *&t;Set up machine check reporting for processors with Intel style MCE&n; */
DECL|function|hammer_mcheck_init
r_static
r_void
id|__init
id|hammer_mcheck_init
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
r_int
id|i
suffix:semicolon
r_static
r_int
id|done
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Check for MCE support&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|X86_FEATURE_MCE
comma
id|c-&gt;x86_capability
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Check for PPro style MCA */
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|X86_FEATURE_MCA
comma
id|c-&gt;x86_capability
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Ok machine check is available */
id|machine_check_vector
op_assign
id|hammer_machine_check
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|done
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Machine check architecture supported.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|rdmsr
c_func
(paren
id|MSR_IA32_MCG_CAP
comma
id|l
comma
id|h
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l
op_amp
(paren
l_int|1
op_lshift
l_int|8
)paren
)paren
(brace
multiline_comment|/* Control register present ? */
id|wrmsr
c_func
(paren
id|MSR_IA32_MCG_CTL
comma
l_int|0xffffffff
comma
l_int|0xffffffff
)paren
suffix:semicolon
)brace
id|banks
op_assign
id|l
op_amp
l_int|0xff
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
id|banks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|wrmsr
c_func
(paren
id|MSR_IA32_MC0_CTL
op_plus
l_int|4
op_star
id|i
comma
l_int|0xffffffff
comma
l_int|0xffffffff
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|banks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|wrmsr
c_func
(paren
id|MSR_IA32_MC0_STATUS
op_plus
l_int|4
op_star
id|i
comma
l_int|0x0
comma
l_int|0x0
)paren
suffix:semicolon
)brace
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
l_string|&quot;Machine check reporting enabled on CPU#%d.&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|done
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This has to be run for each processor&n; */
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
(brace
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|c-&gt;x86_vendor
)paren
(brace
r_case
id|X86_VENDOR_AMD
suffix:colon
id|hammer_mcheck_init
c_func
(paren
id|c
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_X86_MCE_NONFATAL
r_if
c_cond
(paren
id|timerset
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Set the timer to check for non-fatal&n;&t;&t;&t;&t;   errors every MCE_RATE seconds */
id|init_timer
(paren
op_amp
id|mce_timer
)paren
suffix:semicolon
id|mce_timer.expires
op_assign
id|jiffies
op_plus
id|MCE_RATE
suffix:semicolon
id|mce_timer.data
op_assign
l_int|0
suffix:semicolon
id|mce_timer.function
op_assign
op_amp
id|mce_timerfunc
suffix:semicolon
id|add_timer
(paren
op_amp
id|mce_timer
)paren
suffix:semicolon
id|timerset
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Machine check exception polling timer started.&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
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
macro_line|#else
DECL|function|do_machine_check
id|asmlinkage
r_void
id|do_machine_check
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
)brace
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
)brace
macro_line|#endif
eof
