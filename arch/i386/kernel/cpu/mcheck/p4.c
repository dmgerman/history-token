multiline_comment|/*&n; * P4 specific Machine Check Exception Reporting&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/processor.h&gt; 
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/apic.h&gt;
macro_line|#include &quot;mce.h&quot;
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
DECL|variable|mce_num_extended_msrs
r_static
r_int
id|mce_num_extended_msrs
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_X86_MCE_P4THERMAL
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
multiline_comment|/* P4/Xeon Thermal transition interrupt handler */
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
multiline_comment|/* Thermal interrupt handler for this CPU setup */
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
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
id|vendor_thermal_interrupt
c_func
(paren
op_amp
id|regs
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
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
(paren
id|MSR_IA32_THERM_INTERRUPT
comma
id|l
comma
id|h
)paren
suffix:semicolon
id|wrmsr
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
(paren
id|MSR_IA32_MISC_ENABLE
comma
id|l
comma
id|h
)paren
suffix:semicolon
id|wrmsr
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
(paren
id|APIC_LVTTHMR
)paren
suffix:semicolon
id|apic_write_around
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
r_inline
r_int
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
(paren
id|MSR_IA32_MCG_EAX
comma
id|r-&gt;eax
comma
id|h
)paren
suffix:semicolon
id|rdmsr
(paren
id|MSR_IA32_MCG_EBX
comma
id|r-&gt;ebx
comma
id|h
)paren
suffix:semicolon
id|rdmsr
(paren
id|MSR_IA32_MCG_ECX
comma
id|r-&gt;ecx
comma
id|h
)paren
suffix:semicolon
id|rdmsr
(paren
id|MSR_IA32_MCG_EDX
comma
id|r-&gt;edx
comma
id|h
)paren
suffix:semicolon
id|rdmsr
(paren
id|MSR_IA32_MCG_ESI
comma
id|r-&gt;esi
comma
id|h
)paren
suffix:semicolon
id|rdmsr
(paren
id|MSR_IA32_MCG_EDI
comma
id|r-&gt;edi
comma
id|h
)paren
suffix:semicolon
id|rdmsr
(paren
id|MSR_IA32_MCG_EBP
comma
id|r-&gt;ebp
comma
id|h
)paren
suffix:semicolon
id|rdmsr
(paren
id|MSR_IA32_MCG_ESP
comma
id|r-&gt;esp
comma
id|h
)paren
suffix:semicolon
id|rdmsr
(paren
id|MSR_IA32_MCG_EFLAGS
comma
id|r-&gt;eflags
comma
id|h
)paren
suffix:semicolon
id|rdmsr
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
multiline_comment|/* Recoverable ? */
id|recover
op_assign
l_int|0
suffix:semicolon
id|printk
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
id|nr_mce_banks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rdmsr
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
id|recover
op_or_assign
l_int|1
suffix:semicolon
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
id|recover
op_or_assign
l_int|2
suffix:semicolon
id|printk
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
(paren
l_string|&quot;&bslash;n&quot;
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
id|panic
(paren
l_string|&quot;CPU context corrupt&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|recover
op_amp
l_int|1
)paren
id|panic
(paren
l_string|&quot;Unable to continue&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;Attempting to continue.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Do not clear the MSR_IA32_MCi_STATUS if the error is not &n;&t; * recoverable/continuable.This will allow BIOS to look at the MSRs&n;&t; * for errors if the OS could not log the error.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nr_mce_banks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|u32
id|msr
suffix:semicolon
id|msr
op_assign
id|MSR_IA32_MC0_STATUS
op_plus
id|i
op_star
l_int|4
suffix:semicolon
id|rdmsr
(paren
id|msr
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
multiline_comment|/* Clear it */
id|wrmsr
c_func
(paren
id|msr
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
(paren
id|MSR_IA32_MCG_STATUS
comma
id|mcgstl
comma
id|mcgsth
)paren
suffix:semicolon
)brace
DECL|function|intel_p4_mcheck_init
r_void
id|__init
id|intel_p4_mcheck_init
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
id|machine_check_vector
op_assign
id|intel_machine_check
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|printk
(paren
id|KERN_INFO
l_string|&quot;Intel machine check architecture supported.&bslash;n&quot;
)paren
suffix:semicolon
id|rdmsr
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
multiline_comment|/* Control register present ? */
id|wrmsr
(paren
id|MSR_IA32_MCG_CTL
comma
l_int|0xffffffff
comma
l_int|0xffffffff
)paren
suffix:semicolon
id|nr_mce_banks
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
id|nr_mce_banks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|wrmsr
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
id|wrmsr
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
(paren
id|X86_CR4_MCE
)paren
suffix:semicolon
id|printk
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
multiline_comment|/* Check for P4/Xeon extended MCE MSRs */
id|rdmsr
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
macro_line|#ifdef CONFIG_X86_MCE_NONFATAL
id|init_nonfatal_mce_checker
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
