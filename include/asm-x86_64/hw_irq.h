macro_line|#ifndef _ASM_HW_IRQ_H
DECL|macro|_ASM_HW_IRQ_H
mdefine_line|#define _ASM_HW_IRQ_H
multiline_comment|/*&n; *&t;linux/include/asm/hw_irq.h&n; *&n; *&t;(C) 1992, 1993 Linus Torvalds, (C) 1997 Ingo Molnar&n; *&n; *&t;moved some of the old arch/i386/kernel/irq.h to here. VY&n; *&n; *&t;IRQ/IPI changes taken from work by Thomas Radke&n; *&t;&lt;tomsoft@informatik.tu-chemnitz.de&gt;&n; *&n; *&t;hacked by Andi Kleen for x86-64.&n; * &n; *  $Id: hw_irq.h,v 1.24 2001/09/14 20:55:03 vojtech Exp $&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;linux/profile.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
r_struct
id|hw_interrupt_type
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * IDT vectors usable for external interrupt sources start&n; * at 0x20:&n; */
DECL|macro|FIRST_EXTERNAL_VECTOR
mdefine_line|#define FIRST_EXTERNAL_VECTOR&t;0x20
DECL|macro|IA32_SYSCALL_VECTOR
mdefine_line|#define IA32_SYSCALL_VECTOR&t;0x80
multiline_comment|/*&n; * Vectors 0x20-0x2f are used for ISA interrupts.&n; */
multiline_comment|/*&n; * Special IRQ vectors used by the SMP architecture, 0xf0-0xff&n; *&n; *  some of the following vectors are &squot;rare&squot;, they are merged&n; *  into a single vector (CALL_FUNCTION_VECTOR) to save vector space.&n; *  TLB, reschedule and local APIC vectors are performance-critical.&n; *&n; *  Vectors 0xf0-0xf9 are free (reserved for future Linux use).&n; */
DECL|macro|SPURIOUS_APIC_VECTOR
mdefine_line|#define SPURIOUS_APIC_VECTOR&t;0xff
DECL|macro|ERROR_APIC_VECTOR
mdefine_line|#define ERROR_APIC_VECTOR&t;0xfe
DECL|macro|INVALIDATE_TLB_VECTOR
mdefine_line|#define INVALIDATE_TLB_VECTOR&t;0xfd
DECL|macro|RESCHEDULE_VECTOR
mdefine_line|#define RESCHEDULE_VECTOR&t;0xfc
DECL|macro|TASK_MIGRATION_VECTOR
mdefine_line|#define TASK_MIGRATION_VECTOR&t;0xfb
DECL|macro|CALL_FUNCTION_VECTOR
mdefine_line|#define CALL_FUNCTION_VECTOR&t;0xfa
DECL|macro|KDB_VECTOR
mdefine_line|#define KDB_VECTOR&t;0xf9
DECL|macro|THERMAL_APIC_VECTOR
mdefine_line|#define THERMAL_APIC_VECTOR&t;0xf0
multiline_comment|/*&n; * Local APIC timer IRQ vector is on a different priority level,&n; * to work around the &squot;lost local interrupt if more than 2 IRQ&n; * sources per level&squot; errata.&n; */
DECL|macro|LOCAL_TIMER_VECTOR
mdefine_line|#define LOCAL_TIMER_VECTOR&t;0xef
multiline_comment|/*&n; * First APIC vector available to drivers: (vectors 0x30-0xee)&n; * we start at 0x31 to spread out vectors evenly between priority&n; * levels. (0x80 is the syscall vector)&n; */
DECL|macro|FIRST_DEVICE_VECTOR
mdefine_line|#define FIRST_DEVICE_VECTOR&t;0x31
DECL|macro|FIRST_SYSTEM_VECTOR
mdefine_line|#define FIRST_SYSTEM_VECTOR&t;0xef   /* duplicated in irq.h */
macro_line|#ifndef __ASSEMBLY__
r_extern
id|u8
id|irq_vector
(braket
id|NR_IRQ_VECTORS
)braket
suffix:semicolon
DECL|macro|IO_APIC_VECTOR
mdefine_line|#define IO_APIC_VECTOR(irq)&t;(irq_vector[irq])
DECL|macro|AUTO_ASSIGN
mdefine_line|#define AUTO_ASSIGN&t;&t;-1
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
r_void
id|setup_ioapic_dest
c_func
(paren
r_void
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
DECL|macro|IO_APIC_IRQ
mdefine_line|#define IO_APIC_IRQ(x) (((x) &gt;= 16) || ((1&lt;&lt;(x)) &amp; io_apic_irqs))
DECL|macro|__STR
mdefine_line|#define __STR(x) #x
DECL|macro|STR
mdefine_line|#define STR(x) __STR(x)
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|macro|IRQ_NAME2
mdefine_line|#define IRQ_NAME2(nr) nr##_interrupt(void)
DECL|macro|IRQ_NAME
mdefine_line|#define IRQ_NAME(nr) IRQ_NAME2(IRQ##nr)
multiline_comment|/*&n; *&t;SMP has a few special interrupts for IPI messages&n; */
DECL|macro|BUILD_IRQ
mdefine_line|#define BUILD_IRQ(nr) &bslash;&n;asmlinkage void IRQ_NAME(nr); &bslash;&n;__asm__( &bslash;&n;&quot;&bslash;n.p2align&bslash;n&quot; &bslash;&n;&quot;IRQ&quot; #nr &quot;_interrupt:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;push $&quot; #nr &quot;-256 ; &quot; &bslash;&n;&t;&quot;jmp common_interrupt&quot;);
macro_line|#if defined(CONFIG_X86_IO_APIC)
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
DECL|macro|platform_legacy_irq
mdefine_line|#define platform_legacy_irq(irq)&t;((irq) &lt; 16)
macro_line|#endif
macro_line|#endif /* _ASM_HW_IRQ_H */
eof
