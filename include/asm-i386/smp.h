macro_line|#ifndef __ASM_SMP_H
DECL|macro|__ASM_SMP_H
mdefine_line|#define __ASM_SMP_H
multiline_comment|/*&n; * We need the APIC definitions automatically as part of &squot;smp.h&squot;&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/cpumask.h&gt;
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
DECL|macro|BAD_APICID
mdefine_line|#define BAD_APICID 0xFFu
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
id|pic_mode
suffix:semicolon
r_extern
r_int
id|smp_num_siblings
suffix:semicolon
r_extern
id|cpumask_t
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
DECL|macro|MAX_APICID
mdefine_line|#define MAX_APICID 256
r_extern
id|u8
id|x86_cpu_to_apicid
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * This function is needed by all SMP systems. It must _always_ be valid&n; * from the initial startup. We map APIC_BASE very early in page_setup(),&n; * so this is correct in the x86 case.&n; */
DECL|macro|__smp_processor_id
mdefine_line|#define __smp_processor_id() (current_thread_info()-&gt;cpu)
r_extern
id|cpumask_t
id|cpu_callout_map
suffix:semicolon
DECL|macro|cpu_possible_map
mdefine_line|#define cpu_possible_map cpu_callout_map
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
id|cpus_weight
c_func
(paren
id|cpu_callout_map
)paren
suffix:semicolon
)brace
r_extern
r_void
id|map_cpu_to_logical_apicid
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|unmap_cpu_to_logical_apicid
c_func
(paren
r_int
id|cpu
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
macro_line|#ifdef APIC_DEFINITION
r_extern
r_int
id|hard_smp_processor_id
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
macro_line|#include &lt;mach_apicdef.h&gt;
DECL|function|hard_smp_processor_id
r_static
r_inline
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
macro_line|#endif
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
macro_line|#endif /* !__ASSEMBLY__ */
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID&t;&t;0xFF&t;&t;/* No processor magic marker */
macro_line|#endif
macro_line|#endif
eof
