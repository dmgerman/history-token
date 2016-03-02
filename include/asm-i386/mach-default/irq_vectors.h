multiline_comment|/*&n; * This file should contain #defines for all of the interrupt vector&n; * numbers used by this architecture.&n; *&n; * In addition, there are some standard defines:&n; *&n; *&t;FIRST_EXTERNAL_VECTOR:&n; *&t;&t;The first free place for external interrupts&n; *&n; *&t;SYSCALL_VECTOR:&n; *&t;&t;The IRQ vector a syscall makes the user to kernel transition&n; *&t;&t;under.&n; *&n; *&t;TIMER_IRQ:&n; *&t;&t;The IRQ number the timer interrupt comes in at.&n; *&n; *&t;NR_IRQS:&n; *&t;&t;The total number of interrupt vectors (including all the&n; *&t;&t;architecture specific interrupts) needed.&n; *&n; */
macro_line|#ifndef _ASM_IRQ_VECTORS_H
DECL|macro|_ASM_IRQ_VECTORS_H
mdefine_line|#define _ASM_IRQ_VECTORS_H
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
DECL|macro|THERMAL_APIC_VECTOR
mdefine_line|#define THERMAL_APIC_VECTOR&t;0xf0
multiline_comment|/*&n; * Local APIC timer IRQ vector is on a different priority level,&n; * to work around the &squot;lost local interrupt if more than 2 IRQ&n; * sources per level&squot; errata.&n; */
DECL|macro|LOCAL_TIMER_VECTOR
mdefine_line|#define LOCAL_TIMER_VECTOR&t;0xef
multiline_comment|/*&n; * First APIC vector available to drivers: (vectors 0x30-0xee)&n; * we start at 0x31 to spread out vectors evenly between priority&n; * levels. (0x80 is the syscall vector)&n; */
DECL|macro|FIRST_DEVICE_VECTOR
mdefine_line|#define FIRST_DEVICE_VECTOR&t;0x31
DECL|macro|FIRST_SYSTEM_VECTOR
mdefine_line|#define FIRST_SYSTEM_VECTOR&t;0xef
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ 0
multiline_comment|/*&n; * 16 8259A IRQ&squot;s, 208 potential APIC interrupt sources.&n; * Right now the APIC is mostly only used for SMP.&n; * 256 vectors is an architectural limit. (we can have&n; * more than 256 devices theoretically, but they will&n; * have to use shared interrupts)&n; * Since vectors 0x00-0x1f are used/reserved for the CPU,&n; * the usable vector space is 0x20-0xff (224 vectors)&n; */
multiline_comment|/*&n; * The maximum number of vectors supported by i386 processors&n; * is limited to 256. For processors other than i386, NR_VECTORS&n; * should be changed accordingly.&n; */
DECL|macro|NR_VECTORS
mdefine_line|#define NR_VECTORS 256
macro_line|#ifdef CONFIG_PCI_USE_VECTOR
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS FIRST_SYSTEM_VECTOR
DECL|macro|NR_IRQ_VECTORS
mdefine_line|#define NR_IRQ_VECTORS NR_IRQS
macro_line|#else
macro_line|#ifdef CONFIG_X86_IO_APIC
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 224
macro_line|# if (224 &gt;= 32 * NR_CPUS)
DECL|macro|NR_IRQ_VECTORS
macro_line|# define NR_IRQ_VECTORS NR_IRQS
macro_line|# else
DECL|macro|NR_IRQ_VECTORS
macro_line|# define NR_IRQ_VECTORS (32 * NR_CPUS)
macro_line|# endif
macro_line|#else
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 16
DECL|macro|NR_IRQ_VECTORS
mdefine_line|#define NR_IRQ_VECTORS NR_IRQS
macro_line|#endif
macro_line|#endif
DECL|macro|FPU_IRQ
mdefine_line|#define FPU_IRQ&t;&t;&t;13
DECL|macro|FIRST_VM86_IRQ
mdefine_line|#define&t;FIRST_VM86_IRQ&t;&t;3
DECL|macro|LAST_VM86_IRQ
mdefine_line|#define LAST_VM86_IRQ&t;&t;15
DECL|macro|invalid_vm86_irq
mdefine_line|#define invalid_vm86_irq(irq)&t;((irq) &lt; 3 || (irq) &gt; 15)
macro_line|#endif /* _ASM_IRQ_VECTORS_H */
eof
