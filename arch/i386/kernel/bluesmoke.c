multiline_comment|/*&n; * arch/i386/kernel/bluesmoke.c - x86 Machine Check Exception Reporting&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#include &lt;asm/processor.h&gt; 
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/apic.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#ifdef CONFIG_X86_MCE
multiline_comment|/* as supported by the P4/Xeon family */
DECL|struct|intel_mce_extended_msrs
r_struct
id|intel_mce_extended_msrs
(brace
DECL|member|eax
id|u32
id|eax
suffix:semicolon
DECL|member|ebx
id|u32
id|ebx
suffix:semicolon
DECL|member|ecx
id|u32
id|ecx
suffix:semicolon
DECL|member|edx
id|u32
id|edx
suffix:semicolon
DECL|member|esi
id|u32
id|esi
suffix:semicolon
DECL|member|edi
id|u32
id|edi
suffix:semicolon
DECL|member|ebp
id|u32
id|ebp
suffix:semicolon
DECL|member|esp
id|u32
id|esp
suffix:semicolon
DECL|member|eflags
id|u32
id|eflags
suffix:semicolon
DECL|member|eip
id|u32
id|eip
suffix:semicolon
multiline_comment|/* u32 *reserved[]; */
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|mce_disabled
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|mce_num_extended_msrs
r_static
r_int
id|mce_num_extended_msrs
op_assign
l_int|0
suffix:semicolon
DECL|variable|banks
r_static
r_int
id|banks
suffix:semicolon
macro_line|#ifdef CONFIG_X86_MCE_P4THERMAL
multiline_comment|/*&n; *&t;P4/Xeon Thermal transition interrupt handler&n; */
DECL|function|intel_thermal_interrupt
r_static
r_void
id|intel_thermal_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|u32
id|l
comma
id|h
suffix:semicolon
r_int
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|ack_APIC_irq
c_func
(paren
)paren
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_THERM_STATUS
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
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;CPU#%d: Temperature above threshold&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;CPU#%d: Running in modulated clock mode&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CPU#%d: Temperature/speed normal&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
)brace
)brace
DECL|function|unexpected_thermal_interrupt
r_static
r_void
id|unexpected_thermal_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;CPU#%d: Unexpected LVT TMR interrupt!&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Thermal interrupt handler for this CPU setup&n; */
DECL|variable|vendor_thermal_interrupt
r_static
r_void
(paren
op_star
id|vendor_thermal_interrupt
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
op_assign
id|unexpected_thermal_interrupt
suffix:semicolon
DECL|function|smp_thermal_interrupt
id|asmlinkage
r_void
id|smp_thermal_interrupt
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
(brace
id|vendor_thermal_interrupt
c_func
(paren
op_amp
id|regs
)paren
suffix:semicolon
)brace
multiline_comment|/* P4/Xeon Thermal regulation detect and init */
DECL|function|intel_init_thermal
r_static
r_void
id|__init
id|intel_init_thermal
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
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Thermal monitoring */
r_if
c_cond
(paren
op_logical_neg
id|cpu_has
c_func
(paren
id|c
comma
id|X86_FEATURE_ACPI
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* -ENODEV */
multiline_comment|/* Clock modulation */
r_if
c_cond
(paren
op_logical_neg
id|cpu_has
c_func
(paren
id|c
comma
id|X86_FEATURE_ACC
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* -ENODEV */
multiline_comment|/* first check if its enabled already, in which case there might&n;&t; * be some SMM goo which handles it, so we can&squot;t even put a handler&n;&t; * since it might be delivered via SMI already -zwanem.&n;&t; */
id|rdmsr
c_func
(paren
id|MSR_IA32_MISC_ENABLE
comma
id|l
comma
id|h
)paren
suffix:semicolon
id|h
op_assign
id|apic_read
c_func
(paren
id|APIC_LVTTHMR
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|l
op_amp
(paren
l_int|1
op_lshift
l_int|3
)paren
)paren
op_logical_and
(paren
id|h
op_amp
id|APIC_DM_SMI
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;CPU#%d: Thermal monitoring handled by SMI&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* -EBUSY */
)brace
multiline_comment|/* check whether a vector already exists, temporarily masked? */
r_if
c_cond
(paren
id|h
op_amp
id|APIC_VECTOR_MASK
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;CPU#%d: Thermal LVT vector (%#x) already installed&bslash;n&quot;
comma
id|cpu
comma
(paren
id|h
op_amp
id|APIC_VECTOR_MASK
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* -EBUSY */
)brace
multiline_comment|/* The temperature transition interrupt handler setup */
id|h
op_assign
id|THERMAL_APIC_VECTOR
suffix:semicolon
multiline_comment|/* our delivery vector */
id|h
op_or_assign
(paren
id|APIC_DM_FIXED
op_or
id|APIC_LVT_MASKED
)paren
suffix:semicolon
multiline_comment|/* we&squot;ll mask till we&squot;re ready */
id|apic_write_around
c_func
(paren
id|APIC_LVTTHMR
comma
id|h
)paren
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_THERM_INTERRUPT
comma
id|l
comma
id|h
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_IA32_THERM_INTERRUPT
comma
id|l
op_or
l_int|0x03
comma
id|h
)paren
suffix:semicolon
multiline_comment|/* ok we&squot;re good to go... */
id|vendor_thermal_interrupt
op_assign
id|intel_thermal_interrupt
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_MISC_ENABLE
comma
id|l
comma
id|h
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_IA32_MISC_ENABLE
comma
id|l
op_or
(paren
l_int|1
op_lshift
l_int|3
)paren
comma
id|h
)paren
suffix:semicolon
id|l
op_assign
id|apic_read
c_func
(paren
id|APIC_LVTTHMR
)paren
suffix:semicolon
id|apic_write_around
c_func
(paren
id|APIC_LVTTHMR
comma
id|l
op_amp
op_complement
id|APIC_LVT_MASKED
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CPU#%d: Thermal monitoring enabled&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_X86_MCE_P4THERMAL */
multiline_comment|/* P4/Xeon Extended MCE MSR retrieval, return 0 if unsupported */
DECL|function|intel_get_extended_msrs
r_static
r_int
r_inline
id|intel_get_extended_msrs
c_func
(paren
r_struct
id|intel_mce_extended_msrs
op_star
id|r
)paren
(brace
id|u32
id|h
suffix:semicolon
r_if
c_cond
(paren
id|mce_num_extended_msrs
op_eq
l_int|0
)paren
r_goto
id|done
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_MCG_EAX
comma
id|r-&gt;eax
comma
id|h
)paren
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_MCG_EBX
comma
id|r-&gt;ebx
comma
id|h
)paren
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_MCG_ECX
comma
id|r-&gt;ecx
comma
id|h
)paren
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_MCG_EDX
comma
id|r-&gt;edx
comma
id|h
)paren
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_MCG_ESI
comma
id|r-&gt;esi
comma
id|h
)paren
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_MCG_EDI
comma
id|r-&gt;edi
comma
id|h
)paren
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_MCG_EBP
comma
id|r-&gt;ebp
comma
id|h
)paren
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_MCG_ESP
comma
id|r-&gt;esp
comma
id|h
)paren
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_MCG_EFLAGS
comma
id|r-&gt;eflags
comma
id|h
)paren
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_IA32_MCG_EIP
comma
id|r-&gt;eip
comma
id|h
)paren
suffix:semicolon
multiline_comment|/* can we rely on kmalloc to do a dynamic&n;&t; * allocation for the reserved registers?&n;&t; */
id|done
suffix:colon
r_return
id|mce_num_extended_msrs
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Machine Check Handler For PII/PIII&n; */
DECL|function|intel_machine_check
r_static
r_void
id|intel_machine_check
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
r_struct
id|intel_mce_extended_msrs
id|dbg
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
r_if
c_cond
(paren
id|intel_get_extended_msrs
c_func
(paren
op_amp
id|dbg
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;CPU %d: EIP: %08x EFLAGS: %08x&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|dbg.eip
comma
id|dbg.eflags
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;&bslash;teax: %08x ebx: %08x ecx: %08x edx: %08x&bslash;n&quot;
comma
id|dbg.eax
comma
id|dbg.ebx
comma
id|dbg.ecx
comma
id|dbg.edx
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;&bslash;tesi: %08x edi: %08x ebp: %08x esp: %08x&bslash;n&quot;
comma
id|dbg.esi
comma
id|dbg.edi
comma
id|dbg.ebp
comma
id|dbg.esp
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
multiline_comment|/*&n; *&t;Machine check handler for Pentium class Intel&n; */
DECL|function|pentium_machine_check
r_static
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
)brace
multiline_comment|/*&n; *&t;Machine check handler for WinChip C6&n; */
DECL|function|winchip_machine_check
r_static
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
l_string|&quot;CPU#%d: Machine Check Exception.&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
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
DECL|function|do_mce_timer
r_static
r_void
id|do_mce_timer
c_func
(paren
r_void
op_star
id|data
)paren
(brace
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|mce_checkregs
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|smp_call_function
(paren
id|mce_checkregs
comma
l_int|NULL
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
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
DECL|variable|mce_task
r_static
r_struct
id|tq_struct
id|mce_task
op_assign
(brace
id|routine
suffix:colon
id|do_mce_timer
)brace
suffix:semicolon
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
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
id|num_online_cpus
c_func
(paren
)paren
OG
l_int|1
)paren
(brace
id|schedule_task
c_func
(paren
op_amp
id|mce_task
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
id|mce_checkregs
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
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
DECL|function|intel_mcheck_init
r_static
r_void
id|__init
id|intel_mcheck_init
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
multiline_comment|/*&n;&t; *&t;Pentium machine check&n;&t; */
r_if
c_cond
(paren
id|c-&gt;x86
op_eq
l_int|5
)paren
(brace
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
l_string|&quot;Intel old style machine check architecture supported.&bslash;n&quot;
)paren
suffix:semicolon
)brace
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
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Check for PPro style MCA&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|cpu_has
c_func
(paren
id|c
comma
id|X86_FEATURE_MCA
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Ok machine check is available */
id|machine_check_vector
op_assign
id|intel_machine_check
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
l_string|&quot;Intel machine check architecture supported.&bslash;n&quot;
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
multiline_comment|/* Don&squot;t enable bank 0 on intel P6 cores, it goes bang quickly. */
r_if
c_cond
(paren
id|c-&gt;x86_vendor
op_eq
id|X86_VENDOR_INTEL
op_logical_and
id|c-&gt;x86
op_eq
l_int|6
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
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
)brace
r_else
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
l_string|&quot;Intel machine check reporting enabled on CPU#%d.&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Check for P4/Xeon specific MCE extensions&n;&t; */
r_if
c_cond
(paren
id|c-&gt;x86_vendor
op_eq
id|X86_VENDOR_INTEL
op_logical_and
id|c-&gt;x86
op_eq
l_int|15
)paren
(brace
multiline_comment|/* Check for P4/Xeon extended MCE MSRs */
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
l_int|9
)paren
)paren
(brace
multiline_comment|/* MCG_EXT_P */
id|mce_num_extended_msrs
op_assign
(paren
id|l
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CPU#%d: Intel P4/Xeon Extended MCE MSRs (%d) available&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|mce_num_extended_msrs
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_X86_MCE_P4THERMAL
multiline_comment|/* Check for P4/Xeon Thermal monitor */
id|intel_init_thermal
c_func
(paren
id|c
)paren
suffix:semicolon
macro_line|#endif
)brace
id|done
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Set up machine check reporting on the Winchip C6 series&n; */
DECL|function|winchip_mcheck_init
r_static
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
multiline_comment|/* Not supported on C3 */
r_if
c_cond
(paren
id|c-&gt;x86
op_ne
l_int|5
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Winchip C6 */
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
l_string|&quot;Winchip machine check reporting enabled on CPU#%d.&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
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
multiline_comment|/* AMD K7 machine check is Intel like */
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
(brace
id|intel_mcheck_init
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
multiline_comment|/* Set the timer to check for non-fatal&n;&t;&t;&t;&t;&t;   errors every MCE_RATE seconds */
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
)brace
r_break
suffix:semicolon
r_case
id|X86_VENDOR_INTEL
suffix:colon
id|intel_mcheck_init
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
DECL|function|smp_thermal_interrupt
id|asmlinkage
r_void
id|smp_thermal_interrupt
c_func
(paren
r_struct
id|pt_regs
id|regs
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
