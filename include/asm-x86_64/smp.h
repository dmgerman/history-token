macro_line|#ifndef __ASM_SMP_H
DECL|macro|__ASM_SMP_H
mdefine_line|#define __ASM_SMP_H
multiline_comment|/*&n; * We need the APIC definitions automatically as part of &squot;smp.h&squot;&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/cpumask.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
r_extern
r_int
id|disable_apic
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;asm/mpspec.h&gt;
macro_line|#ifdef CONFIG_X86_IO_APIC
macro_line|#include &lt;asm/io_apic.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/apic.h&gt;
macro_line|#include &lt;asm/thread_info.h&gt;
macro_line|#endif
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
macro_line|#ifndef ASSEMBLY
macro_line|#include &lt;asm/pda.h&gt;
r_struct
id|pt_regs
suffix:semicolon
multiline_comment|/*&n; * Private routines/data&n; */
r_extern
r_void
id|smp_alloc_memory
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|cpumask_t
id|cpu_online_map
suffix:semicolon
r_extern
r_volatile
r_int
r_int
id|smp_invalidate_needed
suffix:semicolon
r_extern
r_int
id|pic_mode
suffix:semicolon
r_extern
r_int
id|smp_num_siblings
suffix:semicolon
r_extern
r_void
id|smp_flush_tlb
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|smp_message_irq
c_func
(paren
r_int
id|cpl
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|smp_send_reschedule
c_func
(paren
r_int
id|cpu
)paren
suffix:semicolon
r_extern
r_void
id|smp_invalidate_rcv
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Process an NMI */
r_extern
r_void
(paren
op_star
id|mtrr_hook
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|zap_low_mappings
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|smp_stop_cpu
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|cpumask_t
id|cpu_sibling_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
id|u8
id|phys_proc_id
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|SMP_TRAMPOLINE_BASE
mdefine_line|#define SMP_TRAMPOLINE_BASE 0x6000
multiline_comment|/*&n; * On x86 all CPUs are mapped 1:1 to the APIC space.&n; * This simplifies scheduling and IPI sending and&n; * compresses data structures.&n; */
r_extern
id|cpumask_t
id|cpu_callout_map
suffix:semicolon
r_extern
id|cpumask_t
id|cpu_callin_map
suffix:semicolon
DECL|macro|cpu_possible_map
mdefine_line|#define cpu_possible_map cpu_callout_map
DECL|function|num_booting_cpus
r_static
r_inline
r_int
id|num_booting_cpus
c_func
(paren
r_void
)paren
(brace
r_return
id|cpus_weight
c_func
(paren
id|cpu_callout_map
)paren
suffix:semicolon
)brace
DECL|macro|__smp_processor_id
mdefine_line|#define __smp_processor_id() read_pda(cpunumber)
DECL|function|hard_smp_processor_id
r_extern
id|__inline
r_int
id|hard_smp_processor_id
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* we don&squot;t want to mark this access volatile - bad code generation */
r_return
id|GET_APIC_ID
c_func
(paren
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|APIC_BASE
op_plus
id|APIC_ID
)paren
)paren
suffix:semicolon
)brace
DECL|macro|safe_smp_processor_id
mdefine_line|#define safe_smp_processor_id() (disable_apic ? 0 : x86_apicid_to_cpu(hard_smp_processor_id()))
macro_line|#endif /* !ASSEMBLY */
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID&t;&t;0xFF&t;&t;/* No processor magic marker */
macro_line|#endif
macro_line|#ifndef ASSEMBLY
multiline_comment|/*&n; * Some lowlevel functions might want to know about&n; * the real APIC ID &lt;-&gt; CPU # mapping.&n; */
r_extern
id|u8
id|x86_cpu_to_apicid
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/* physical ID */
r_extern
id|u8
id|x86_cpu_to_log_apicid
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
id|u8
id|bios_cpu_apicid
(braket
)braket
suffix:semicolon
DECL|function|cpu_mask_to_apicid
r_static
r_inline
r_int
r_int
id|cpu_mask_to_apicid
c_func
(paren
id|cpumask_t
id|cpumask
)paren
(brace
r_return
id|cpus_addr
c_func
(paren
id|cpumask
)paren
(braket
l_int|0
)braket
suffix:semicolon
)brace
DECL|function|x86_apicid_to_cpu
r_static
r_inline
r_int
id|x86_apicid_to_cpu
c_func
(paren
id|u8
id|apicid
)paren
(brace
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
id|NR_CPUS
suffix:semicolon
op_increment
id|i
)paren
r_if
c_cond
(paren
id|x86_cpu_to_apicid
(braket
id|i
)braket
op_eq
id|apicid
)paren
r_return
id|i
suffix:semicolon
multiline_comment|/* No entries in x86_cpu_to_apicid?  Either no MPS|ACPI,&n;&t; * or called too early.  Either way, we must be CPU 0. */
r_if
c_cond
(paren
id|x86_cpu_to_apicid
(braket
l_int|0
)braket
op_eq
id|BAD_APICID
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|cpu_present_to_apicid
r_static
r_inline
r_int
id|cpu_present_to_apicid
c_func
(paren
r_int
id|mps_cpu
)paren
(brace
r_if
c_cond
(paren
id|mps_cpu
OL
id|NR_CPUS
)paren
r_return
(paren
r_int
)paren
id|bios_cpu_apicid
(braket
id|mps_cpu
)braket
suffix:semicolon
r_else
r_return
id|BAD_APICID
suffix:semicolon
)brace
macro_line|#endif /* !ASSEMBLY */
macro_line|#ifndef CONFIG_SMP
DECL|macro|stack_smp_processor_id
mdefine_line|#define stack_smp_processor_id() 0
DECL|macro|safe_smp_processor_id
mdefine_line|#define safe_smp_processor_id() 0
DECL|macro|cpu_logical_map
mdefine_line|#define cpu_logical_map(x) (x)
macro_line|#else
macro_line|#include &lt;asm/thread_info.h&gt;
DECL|macro|stack_smp_processor_id
mdefine_line|#define stack_smp_processor_id() &bslash;&n;({ &t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct thread_info *ti;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__(&quot;andq %%rsp,%0; &quot;:&quot;=r&quot; (ti) : &quot;0&quot; (CURRENT_MASK));&t;&bslash;&n;&t;ti-&gt;cpu;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
DECL|function|logical_smp_processor_id
r_static
id|__inline
r_int
id|logical_smp_processor_id
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* we don&squot;t want to mark this access volatile - bad code generation */
r_return
id|GET_APIC_LOGICAL_ID
c_func
(paren
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|APIC_BASE
op_plus
id|APIC_LDR
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
eof
