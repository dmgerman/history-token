macro_line|#ifndef __ASM_SMP_H
DECL|macro|__ASM_SMP_H
mdefine_line|#define __ASM_SMP_H
multiline_comment|/*&n; * We need the APIC definitions automatically as part of &squot;smp.h&squot;&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/mpspec.h&gt;
macro_line|#ifdef CONFIG_X86_IO_APIC
macro_line|#include &lt;asm/io_apic.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/apic.h&gt;
macro_line|#endif
macro_line|#endif
macro_line|#ifdef CONFIG_CLUSTERED_APIC
DECL|macro|INT_DELIVERY_MODE
mdefine_line|#define INT_DELIVERY_MODE 0     /* physical delivery on LOCAL quad */
macro_line|#else
DECL|macro|INT_DELIVERY_MODE
mdefine_line|#define INT_DELIVERY_MODE 1     /* logical delivery broadcast to all procs */
macro_line|#endif
macro_line|#ifndef clustered_apic_mode
macro_line|#ifdef CONFIG_CLUSTERED_APIC
DECL|macro|clustered_apic_mode
mdefine_line|#define clustered_apic_mode (1)
DECL|macro|esr_disable
mdefine_line|#define esr_disable (1)
macro_line|#else /* !CONFIG_CLUSTERED_APIC */
DECL|macro|clustered_apic_mode
mdefine_line|#define clustered_apic_mode (0)
DECL|macro|esr_disable
mdefine_line|#define esr_disable (0)
macro_line|#endif /* CONFIG_CLUSTERED_APIC */
macro_line|#endif 
macro_line|#ifdef CONFIG_SMP
macro_line|#ifndef __ASSEMBLY__
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
r_int
r_int
id|phys_cpu_present_map
suffix:semicolon
r_extern
r_int
r_int
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
r_int
id|cpu_sibling_map
(braket
)braket
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
id|smp_send_reschedule_all
c_func
(paren
r_void
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
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Some lowlevel functions might want to know about&n; * the real APIC ID &lt;-&gt; CPU # mapping.&n; */
DECL|macro|MAX_APICID
mdefine_line|#define MAX_APICID 256
r_extern
r_volatile
r_int
id|cpu_to_physical_apicid
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_volatile
r_int
id|physical_apicid_to_cpu
(braket
id|MAX_APICID
)braket
suffix:semicolon
r_extern
r_volatile
r_int
id|cpu_to_logical_apicid
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_volatile
r_int
id|logical_apicid_to_cpu
(braket
id|MAX_APICID
)braket
suffix:semicolon
multiline_comment|/*&n; * This function is needed by all SMP systems. It must _always_ be valid&n; * from the initial startup. We map APIC_BASE very early in page_setup(),&n; * so this is correct in the x86 case.&n; */
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id() (current_thread_info()-&gt;cpu)
r_extern
r_volatile
r_int
r_int
id|cpu_callout_map
suffix:semicolon
DECL|macro|cpu_possible
mdefine_line|#define cpu_possible(cpu) (cpu_callout_map &amp; (1&lt;&lt;(cpu)))
DECL|macro|cpu_online
mdefine_line|#define cpu_online(cpu) (cpu_online_map &amp; (1&lt;&lt;(cpu)))
DECL|function|num_online_cpus
r_extern
r_inline
r_int
r_int
id|num_online_cpus
c_func
(paren
r_void
)paren
(brace
r_return
id|hweight32
c_func
(paren
id|cpu_online_map
)paren
suffix:semicolon
)brace
DECL|function|any_online_cpu
r_extern
r_inline
r_int
id|any_online_cpu
c_func
(paren
r_int
r_int
id|mask
)paren
(brace
r_if
c_cond
(paren
id|mask
op_amp
id|cpu_online_map
)paren
r_return
id|__ffs
c_func
(paren
id|mask
op_amp
id|cpu_online_map
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|hard_smp_processor_id
r_static
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
multiline_comment|/* We don&squot;t mark CPUs online until __cpu_up(), so we need another measure */
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
id|hweight32
c_func
(paren
id|cpu_callout_map
)paren
suffix:semicolon
)brace
macro_line|#endif /* !__ASSEMBLY__ */
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID&t;&t;0xFF&t;&t;/* No processor magic marker */
macro_line|#endif
macro_line|#endif
eof
