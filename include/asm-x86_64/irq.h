macro_line|#ifndef _ASM_IRQ_H
DECL|macro|_ASM_IRQ_H
mdefine_line|#define _ASM_IRQ_H
multiline_comment|/*&n; *&t;linux/include/asm/irq.h&n; *&n; *&t;(C) 1992, 1993 Linus Torvalds, (C) 1997 Ingo Molnar&n; *&n; *&t;IRQ/IPI changes taken from work by Thomas Radke&n; *&t;&lt;tomsoft@informatik.tu-chemnitz.de&gt;&n; */
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ 0
multiline_comment|/*&n; * 16 8259A IRQ&squot;s, 208 potential APIC interrupt sources.&n; * Right now the APIC is mostly only used for SMP.&n; * 256 vectors is an architectural limit. (we can have&n; * more than 256 devices theoretically, but they will&n; * have to use shared interrupts)&n; * Since vectors 0x00-0x1f are used/reserved for the CPU,&n; * the usable vector space is 0x20-0xff (224 vectors)&n; */
multiline_comment|/*&n; * The maximum number of vectors supported by x86_64 processors&n; * is limited to 256. For processors other than x86_64, NR_VECTORS&n; * should be changed accordingly.&n; */
DECL|macro|NR_VECTORS
mdefine_line|#define NR_VECTORS 256
DECL|macro|FIRST_SYSTEM_VECTOR
mdefine_line|#define FIRST_SYSTEM_VECTOR&t;0xef   /* duplicated in hw_irq.h */
macro_line|#ifdef CONFIG_PCI_MSI
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS FIRST_SYSTEM_VECTOR
DECL|macro|NR_IRQ_VECTORS
mdefine_line|#define NR_IRQ_VECTORS NR_IRQS
macro_line|#else
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 224
DECL|macro|NR_IRQ_VECTORS
mdefine_line|#define NR_IRQ_VECTORS 1024
macro_line|#endif
DECL|function|irq_canonicalize
r_static
id|__inline__
r_int
id|irq_canonicalize
c_func
(paren
r_int
id|irq
)paren
(brace
r_return
(paren
(paren
id|irq
op_eq
l_int|2
)paren
ques
c_cond
l_int|9
suffix:colon
id|irq
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
DECL|macro|ARCH_HAS_NMI_WATCHDOG
mdefine_line|#define ARCH_HAS_NMI_WATCHDOG&t;&t;/* See include/linux/nmi.h */
macro_line|#endif
r_struct
id|irqaction
suffix:semicolon
r_struct
id|pt_regs
suffix:semicolon
r_int
id|handle_IRQ_event
c_func
(paren
r_int
r_int
comma
r_struct
id|pt_regs
op_star
comma
r_struct
id|irqaction
op_star
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IRQ_H */
eof
