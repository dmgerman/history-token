macro_line|#ifndef _ASM_HW_IRQ_H
DECL|macro|_ASM_HW_IRQ_H
mdefine_line|#define _ASM_HW_IRQ_H
multiline_comment|/*&n; *&t;linux/include/asm/hw_irq.h&n; *&n; *&t;(C) 1992, 1993 Linus Torvalds, (C) 1997 Ingo Molnar&n; *&n; *&t;moved some of the old arch/i386/kernel/irq.h to here. VY&n; *&n; *&t;IRQ/IPI changes taken from work by Thomas Radke&n; *&t;&lt;tomsoft@informatik.tu-chemnitz.de&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/*&n; * IDT vectors usable for external interrupt sources start&n; * at 0x20:&n; */
DECL|macro|FIRST_EXTERNAL_VECTOR
mdefine_line|#define FIRST_EXTERNAL_VECTOR&t;0x20
DECL|macro|SYSCALL_VECTOR
mdefine_line|#define SYSCALL_VECTOR&t;&t;0x80
multiline_comment|/*&n; * Vectors 0x20-0x2f are used for ISA interrupts.&n; */
multiline_comment|/*&n; * Special IRQ vectors used by the SMP architecture, 0xf0-0xff&n; *&n; *  some of the following vectors are &squot;rare&squot;, they are merged&n; *  into a single vector (CALL_FUNCTION_VECTOR) to save vector space.&n; *  TLB, reschedule and local APIC vectors are performance-critical.&n; *&n; *  Vectors 0xf0-0xfa are free (reserved for future Linux use).&n; */
DECL|macro|SPURIOUS_APIC_VECTOR
mdefine_line|#define SPURIOUS_APIC_VECTOR&t;0xff
DECL|macro|ERROR_APIC_VECTOR
mdefine_line|#define ERROR_APIC_VECTOR&t;0xfe
DECL|macro|INVALIDATE_TLB_VECTOR
mdefine_line|#define INVALIDATE_TLB_VECTOR&t;0xfd
DECL|macro|RESCHEDULE_VECTOR
mdefine_line|#define RESCHEDULE_VECTOR&t;0xfc
DECL|macro|CALL_FUNCTION_VECTOR
mdefine_line|#define CALL_FUNCTION_VECTOR&t;0xfb
multiline_comment|/*&n; * Local APIC timer IRQ vector is on a different priority level,&n; * to work around the &squot;lost local interrupt if more than 2 IRQ&n; * sources per level&squot; errata.&n; */
DECL|macro|LOCAL_TIMER_VECTOR
mdefine_line|#define LOCAL_TIMER_VECTOR&t;0xef
multiline_comment|/*&n; * First APIC vector available to drivers: (vectors 0x30-0xee)&n; * we start at 0x31 to spread out vectors evenly between priority&n; * levels. (0x80 is the syscall vector)&n; */
DECL|macro|FIRST_DEVICE_VECTOR
mdefine_line|#define FIRST_DEVICE_VECTOR&t;0x31
DECL|macro|FIRST_SYSTEM_VECTOR
mdefine_line|#define FIRST_SYSTEM_VECTOR&t;0xef
r_extern
r_int
id|irq_vector
(braket
id|NR_IRQS
)braket
suffix:semicolon
DECL|macro|IO_APIC_VECTOR
mdefine_line|#define IO_APIC_VECTOR(irq)&t;irq_vector[irq]
multiline_comment|/*&n; * Various low-level irq details needed by irq.c, process.c,&n; * time.c, io_apic.c and smp.c&n; *&n; * Interrupt entry/exit code at both C and assembly level&n; */
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
DECL|macro|__STR
mdefine_line|#define __STR(x) #x
DECL|macro|STR
mdefine_line|#define STR(x) __STR(x)
DECL|macro|SAVE_ALL
mdefine_line|#define SAVE_ALL &bslash;&n;&t;&quot;cld&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %es&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %ds&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %ebp&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %edi&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %esi&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %ecx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %ebx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl $&quot; STR(__KERNEL_DS) &quot;,%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl %edx,%ds&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl %edx,%es&bslash;n&bslash;t&quot;
DECL|macro|IRQ_NAME2
mdefine_line|#define IRQ_NAME2(nr) nr##_interrupt(void)
DECL|macro|IRQ_NAME
mdefine_line|#define IRQ_NAME(nr) IRQ_NAME2(IRQ##nr)
DECL|macro|GET_CURRENT
mdefine_line|#define GET_CURRENT &bslash;&n;&t;&quot;movl %esp, %ebx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;andl $-8192, %ebx&bslash;n&bslash;t&quot;
multiline_comment|/*&n; *&t;SMP has a few special interrupts for IPI messages&n; */
multiline_comment|/* there is a second layer of macro just to get the symbolic&n;&t;   name for the vector evaluated. This change is for RTLinux */
DECL|macro|BUILD_SMP_INTERRUPT
mdefine_line|#define BUILD_SMP_INTERRUPT(x,v) XBUILD_SMP_INTERRUPT(x,v)
DECL|macro|XBUILD_SMP_INTERRUPT
mdefine_line|#define XBUILD_SMP_INTERRUPT(x,v)&bslash;&n;asmlinkage void x(void); &bslash;&n;asmlinkage void call_##x(void); &bslash;&n;__asm__( &bslash;&n;&quot;&bslash;n&quot;__ALIGN_STR&quot;&bslash;n&quot; &bslash;&n;SYMBOL_NAME_STR(x) &quot;:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl $&quot;#v&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;SAVE_ALL &bslash;&n;&t;SYMBOL_NAME_STR(call_##x)&quot;:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;call &quot;SYMBOL_NAME_STR(smp_##x)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp ret_from_intr&bslash;n&quot;);
DECL|macro|BUILD_SMP_TIMER_INTERRUPT
mdefine_line|#define BUILD_SMP_TIMER_INTERRUPT(x,v) XBUILD_SMP_TIMER_INTERRUPT(x,v)
DECL|macro|XBUILD_SMP_TIMER_INTERRUPT
mdefine_line|#define XBUILD_SMP_TIMER_INTERRUPT(x,v) &bslash;&n;asmlinkage void x(struct pt_regs * regs); &bslash;&n;asmlinkage void call_##x(void); &bslash;&n;__asm__( &bslash;&n;&quot;&bslash;n&quot;__ALIGN_STR&quot;&bslash;n&quot; &bslash;&n;SYMBOL_NAME_STR(x) &quot;:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl $&quot;#v&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;SAVE_ALL &bslash;&n;&t;&quot;movl %esp,%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %eax&bslash;n&bslash;t&quot; &bslash;&n;&t;SYMBOL_NAME_STR(call_##x)&quot;:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;call &quot;SYMBOL_NAME_STR(smp_##x)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;addl $4,%esp&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp ret_from_intr&bslash;n&quot;);
DECL|macro|BUILD_COMMON_IRQ
mdefine_line|#define BUILD_COMMON_IRQ() &bslash;&n;asmlinkage void call_do_IRQ(void); &bslash;&n;__asm__( &bslash;&n;&t;&quot;&bslash;n&quot; __ALIGN_STR&quot;&bslash;n&quot; &bslash;&n;&t;&quot;common_interrupt:&bslash;n&bslash;t&quot; &bslash;&n;&t;SAVE_ALL &bslash;&n;&t;&quot;pushl $ret_from_intr&bslash;n&bslash;t&quot; &bslash;&n;&t;SYMBOL_NAME_STR(call_do_IRQ)&quot;:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp &quot;SYMBOL_NAME_STR(do_IRQ));
multiline_comment|/* &n; * subtle. orig_eax is used by the signal code to distinct between&n; * system calls and interrupted &squot;random user-space&squot;. Thus we have&n; * to put a negative value into orig_eax here. (the problem is that&n; * both system calls and IRQs want to have small integer numbers in&n; * orig_eax, and the syscall code has won the optimization conflict ;)&n; *&n; * Subtle as a pigs ear.  VY&n; */
DECL|macro|BUILD_IRQ
mdefine_line|#define BUILD_IRQ(nr) &bslash;&n;asmlinkage void IRQ_NAME(nr); &bslash;&n;__asm__( &bslash;&n;&quot;&bslash;n&quot;__ALIGN_STR&quot;&bslash;n&quot; &bslash;&n;SYMBOL_NAME_STR(IRQ) #nr &quot;_interrupt:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl $&quot;#nr&quot;-256&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp common_interrupt&quot;);
r_extern
r_int
r_int
id|prof_cpu_mask
suffix:semicolon
r_extern
r_int
r_int
op_star
id|prof_buffer
suffix:semicolon
r_extern
r_int
r_int
id|prof_len
suffix:semicolon
r_extern
r_int
r_int
id|prof_shift
suffix:semicolon
multiline_comment|/*&n; * x86 profiling function, SMP safe. We might want to do this in&n; * assembly totally?&n; */
DECL|function|x86_do_profile
r_static
r_inline
r_void
id|x86_do_profile
(paren
r_int
r_int
id|eip
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|prof_buffer
)paren
r_return
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
macro_line|#ifdef CONFIG_SMP /*more of this file should probably be ifdefed SMP */
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
