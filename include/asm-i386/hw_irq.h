macro_line|#ifndef _ASM_HW_IRQ_H
DECL|macro|_ASM_HW_IRQ_H
mdefine_line|#define _ASM_HW_IRQ_H
multiline_comment|/*&n; *&t;linux/include/asm/hw_irq.h&n; *&n; *&t;(C) 1992, 1993 Linus Torvalds, (C) 1997 Ingo Molnar&n; *&n; *&t;moved some of the old arch/i386/kernel/irq.h to here. VY&n; *&n; *&t;IRQ/IPI changes taken from work by Thomas Radke&n; *&t;&lt;tomsoft@informatik.tu-chemnitz.de&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/profile.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/*&n; * Various low-level irq details needed by irq.c, process.c,&n; * time.c, io_apic.c and smp.c&n; *&n; * Interrupt entry/exit code at both C and assembly level&n; */
r_extern
r_int
id|irq_vector
(braket
id|NR_IRQS
)braket
suffix:semicolon
DECL|macro|IO_APIC_VECTOR
mdefine_line|#define IO_APIC_VECTOR(irq)&t;irq_vector[irq]
r_extern
r_void
(paren
op_star
id|interrupt
(braket
id|NR_IRQS
)braket
)paren
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_extern
id|asmlinkage
r_void
id|reschedule_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|invalidate_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|call_function_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
r_extern
id|asmlinkage
r_void
id|apic_timer_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|error_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|spurious_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|thermal_interrupt
c_func
(paren
r_struct
id|pt_regs
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_void
id|mask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|unmask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|disable_8259A_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|enable_8259A_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_int
id|i8259A_irq_pending
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|make_8259A_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|init_8259A
c_func
(paren
r_int
id|aeoi
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|send_IPI_self
c_func
(paren
r_int
id|vector
)paren
)paren
suffix:semicolon
r_extern
r_void
id|init_VISWS_APIC_irqs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|setup_IO_APIC
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|disable_IO_APIC
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|print_IO_APIC
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|IO_APIC_get_PCI_irq_vector
c_func
(paren
r_int
id|bus
comma
r_int
id|slot
comma
r_int
id|fn
)paren
suffix:semicolon
r_extern
r_void
id|send_IPI
c_func
(paren
r_int
id|dest
comma
r_int
id|vector
)paren
suffix:semicolon
r_extern
r_int
r_int
id|io_apic_irqs
suffix:semicolon
r_extern
id|atomic_t
id|irq_err_count
suffix:semicolon
r_extern
id|atomic_t
id|irq_mis_count
suffix:semicolon
r_extern
r_char
id|_stext
comma
id|_etext
suffix:semicolon
DECL|macro|IO_APIC_IRQ
mdefine_line|#define IO_APIC_IRQ(x) (((x) &gt;= 16) || ((1&lt;&lt;(x)) &amp; io_apic_irqs))
multiline_comment|/*&n; * The profiling function is SMP safe. (nothing can mess&n; * around with &quot;current&quot;, and the profiling counters are&n; * updated with atomic operations). This is especially&n; * useful with a profiling multiplier != 1&n; */
DECL|function|x86_do_profile
r_static
r_inline
r_void
id|x86_do_profile
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|eip
suffix:semicolon
r_extern
r_int
r_int
id|prof_cpu_mask
suffix:semicolon
id|profile_hook
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prof_buffer
)paren
r_return
suffix:semicolon
id|eip
op_assign
id|regs-&gt;eip
suffix:semicolon
multiline_comment|/*&n;&t; * Only measure the CPUs specified by /proc/irq/prof_cpu_mask.&n;&t; * (default is all CPUs.)&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
l_int|1
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
op_amp
id|prof_cpu_mask
)paren
)paren
r_return
suffix:semicolon
id|eip
op_sub_assign
(paren
r_int
r_int
)paren
op_amp
id|_stext
suffix:semicolon
id|eip
op_rshift_assign
id|prof_shift
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t ignore out-of-bounds EIP values silently,&n;&t; * put them into the last histogram slot, so if&n;&t; * present, they will show up as a sharp peak.&n;&t; */
r_if
c_cond
(paren
id|eip
OG
id|prof_len
op_minus
l_int|1
)paren
id|eip
op_assign
id|prof_len
op_minus
l_int|1
suffix:semicolon
id|atomic_inc
c_func
(paren
(paren
id|atomic_t
op_star
)paren
op_amp
id|prof_buffer
(braket
id|eip
)braket
)paren
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_X86_IO_APIC) &amp;&amp; defined(CONFIG_SMP)
DECL|function|hw_resend_irq
r_static
r_inline
r_void
id|hw_resend_irq
c_func
(paren
r_struct
id|hw_interrupt_type
op_star
id|h
comma
r_int
r_int
id|i
)paren
(brace
r_if
c_cond
(paren
id|IO_APIC_IRQ
c_func
(paren
id|i
)paren
)paren
id|send_IPI_self
c_func
(paren
id|IO_APIC_VECTOR
c_func
(paren
id|i
)paren
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|hw_resend_irq
r_static
r_inline
r_void
id|hw_resend_irq
c_func
(paren
r_struct
id|hw_interrupt_type
op_star
id|h
comma
r_int
r_int
id|i
)paren
(brace
)brace
macro_line|#endif
macro_line|#endif /* _ASM_HW_IRQ_H */
eof
