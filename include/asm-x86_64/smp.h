macro_line|#ifndef __ASM_SMP_H
DECL|macro|__ASM_SMP_H
mdefine_line|#define __ASM_SMP_H
multiline_comment|/*&n; * We need the APIC definitions automatically as part of &squot;smp.h&squot;&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
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
multiline_comment|/*&n; * On x86 all CPUs are mapped 1:1 to the APIC space.&n; * This simplifies scheduling and IPI sending and&n; * compresses data structures.&n; */
r_extern
r_volatile
r_int
r_int
id|cpu_callout_map
suffix:semicolon
DECL|macro|cpu_possible
mdefine_line|#define cpu_possible(cpu) (cpu_callout_map &amp; (1&lt;&lt;(cpu)))
DECL|function|cpu_logical_map
r_extern
r_inline
r_int
id|cpu_logical_map
c_func
(paren
r_int
id|cpu
)paren
(brace
r_return
id|cpu
suffix:semicolon
)brace
DECL|function|cpu_number_map
r_extern
r_inline
r_int
id|cpu_number_map
c_func
(paren
r_int
id|cpu
)paren
(brace
r_return
id|cpu
suffix:semicolon
)brace
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
DECL|function|find_next_cpu
r_extern
r_inline
r_int
id|find_next_cpu
c_func
(paren
r_int
id|cpu
)paren
(brace
r_int
r_int
id|left
op_assign
id|cpu_online_map
op_rshift
(paren
id|cpu
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|left
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
id|ffz
c_func
(paren
op_complement
id|left
)paren
op_plus
id|cpu
suffix:semicolon
)brace
DECL|function|find_first_cpu
r_extern
r_inline
r_int
id|find_first_cpu
c_func
(paren
r_void
)paren
(brace
r_return
id|ffz
c_func
(paren
op_complement
id|cpu_online_map
)paren
suffix:semicolon
)brace
multiline_comment|/* RED-PEN different from i386 */
DECL|macro|for_each_cpu
mdefine_line|#define for_each_cpu(i) &bslash;&n;&t;for((i) = find_first_cpu(); (i)&gt;=0; (i)=find_next_cpu(i))
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
r_extern
r_volatile
r_int
r_int
id|cpu_callout_map
suffix:semicolon
multiline_comment|/*&n; * Some lowlevel functions might want to know about&n; * the real APIC ID &lt;-&gt; CPU # mapping.&n; */
r_extern
r_volatile
r_int
id|x86_apicid_to_cpu
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_volatile
r_int
id|x86_cpu_to_apicid
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/*&n; * This function is needed by all SMP systems. It must _always_ be valid&n; * from the initial startup. We map APIC_BASE very early in page_setup(),&n; * so this is correct in the x86 case.&n; */
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id() read_pda(cpunumber)
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
DECL|macro|cpu_online
mdefine_line|#define cpu_online(cpu) (cpu_online_map &amp; (1&lt;&lt;(cpu)))
macro_line|#endif /* !ASSEMBLY */
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID&t;&t;0xFF&t;&t;/* No processor magic marker */
macro_line|#endif
DECL|macro|INT_DELIVERY_MODE
mdefine_line|#define INT_DELIVERY_MODE 1     /* logical delivery */
DECL|macro|TARGET_CPUS
mdefine_line|#define TARGET_CPUS 1
macro_line|#ifndef CONFIG_SMP
DECL|macro|stack_smp_processor_id
mdefine_line|#define stack_smp_processor_id() 0
DECL|macro|for_each_cpu
mdefine_line|#define for_each_cpu(x) (x)=0;
DECL|macro|cpu_logical_map
mdefine_line|#define cpu_logical_map(x) (x)
macro_line|#else
macro_line|#include &lt;asm/thread_info.h&gt;
DECL|macro|stack_smp_processor_id
mdefine_line|#define stack_smp_processor_id() &bslash;&n;({ &t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct thread_info *ti;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__(&quot;andq %%rsp,%0; &quot;:&quot;=r&quot; (ti) : &quot;0&quot; (~8191UL));&t;&bslash;&n;&t;ti-&gt;cpu;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
macro_line|#endif
eof
